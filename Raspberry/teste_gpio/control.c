/**
 * Projeto Integrador 2 - 2019/1
 * Controle dos processos de verificação
 * Autores: Guilherme Camargo e Jessica Ribeiro
 */

#include "control.h"

/**
 * @brief Carrega os valores para a memória
 */
void load_file()
{
	debug_msg(printf("Buscando arquivo de log...\n"));
	FILE *flog;
	int n;
	flog = fopen(FILENAME, "r");
	if(flog == NULL)
	{
		printf("Falha ao abrir o arquivo");
		exit(1);
	}
	while(1)
	{
		n = fscanf(flog, "%d, %d, %d, , , , , ", &control.total, &control.passed, &control.failed);
		if(n==EOF)
			break;
	}
	fclose(flog);
}

/**
 * @brief Salva as informações do sistema
 */
void save_file()
{
	FILE *flog;
	flog=fopen(FILENAME, "a");
	fprintf(flog, "%d, %d, %d,", control.total, control.passed, control.failed);
	fprintf(flog, "%.2f, %.2f,", control.volume, control.obj_temp);
	fprintf(flog, "%d, %d, %d\n", control.red_color, control.green_color, control.blue_color);
	//fprintf(flog, "%d, %d, %d\n", control.total, control.passed, control.failed);
	//fclose(flog);
	fflush(flog);
}

void set_state_idle()
{
	machine_state = IDLE,
	debug_msg(printf("\n>> Em espera\n"));
	led_div = display_div = 0;
	#ifdef DISPLAY_ON
	display_idle_message();
	#endif	
}

void set_state_running()
{
	machine_state = RUNNING;
	debug_msg(printf("\n>> Iniciando verificação\n"));
	control.total++;
	#ifdef DISPLAY_ON
	display_backlight_on();
	#endif
	#ifdef LED_ON
	digitalWrite(LED_PIN, HIGH);
	#endif
}

void set_state_check_volume()
{
	machine_state = CHECK_VOLUME;
}

void set_state_check_temperature()
{
	machine_state = CHECK_TEMPERATURE;
}

void set_state_check_color()
{
	machine_state = CHECK_COLOR;
}

void set_state_check_ocr()
{
	machine_state = CHECK_OCR;
	debug_msg(printf("\n>> Iniciando leitura OCR\n"));
}

void process_failure()
{
	control.failed++;
	buzzer_process_failed();
	save_file();
	set_state_idle();
}

void process_ok()
{
	control.passed++;
	buzzer_process_passed();
	save_file();
	debug_msg(printf("Verificacao concluida com sucesso!\n"));
}

/**
 * @brief Teste dos sensores instalados, neste modo as outras operações estão suspensas.
 */
void control_test()
{
	#ifdef ULTRASSONIC_ON
	float dist = get_distance();
	delay(10);
    calculate_volume();
	#ifdef DISPLAY_ON
	lcd_init();
	display_set_line(LINE1);
	display_string("Dist ");
	display_float(dist);
	display_string(" cm  ");
	display_set_line(LINE2);
	display_string("Vol: ");
	display_float(control.volume);
	display_string(" ml  ");
	#endif
	debug_msg(printf("\nDist: %.2f cm\nVol: %.2f ml", dist, control.volume));
	debug_msg(printf("\n"));
    delay(800);
	#endif

	#ifdef TEMPERATURE_ON
	float amb_temp = read_amb_temperature();
	delay(1);
	float obj_temp = read_obj_temperature();
	#ifdef DISPLAY_ON
	lcd_init();
	display_clear();
	display_string("Obj Temp:");
	display_float(obj_temp);
	display_set_line(LINE2);
	display_string("Amb Temp:");
	display_float(amb_temp);
	#endif
    debug_msg(printf("\nObj temp: %.2f Amb Temp: %.2f\n\n", obj_temp, amb_temp));
	delay(800);
	#endif

	#ifdef COLOR_ON
	get_color();
	#ifdef DISPLAY_ON
	display_set_line(LINE1);
	display_string("RGB Values     ");
	display_set_line(LINE2);
	display_int(control.red_color);
	display_string(" ");
	display_int(control.green_color);
	display_string(" ");
	display_int(control.blue_color);
	display_string("     ");
	#endif
    debug_msg(printf("\nR:%d G:%d B:%d\n", control.red_color, control.green_color, control.blue_color));
	debug_msg(printf("\n"));
	delay(800);
	#endif
}

/**
 * @brief Máquina de estados para controle dos processos de verificação
 */
void control_run()
{
	switch (machine_state)
	{
		case IDLE:
			if(led_div++ > 300)
			{
				led_div = 0;
				//cpl_led();
				digitalWrite(LED_PIN, HIGH);
				delay(50);
				digitalWrite(LED_PIN, LOW);
			}

			#ifdef DISPLAY_ON
			if(display_div++ > 1000)
			{
				display_div = 0;
				display_backlight_off();
				display_update_status(control.total,control.passed,control.failed);
			}
			#endif

			if(!digitalRead(IR_0))
				set_state_running();
			break;

		case RUNNING:
			delay(TIME_DELAY);
			set_state_check_volume();
			break;

		case CHECK_VOLUME:
			if(check_volume())
			{
				set_state_check_temperature();
			}
			else
			{
				process_failure();
			}
			break;

		case CHECK_TEMPERATURE:
			#ifdef TEMPERATURE_ON
			if(!digitalRead(IR_1))
			{
			   delay(TIME_DELAY);
				// Checa temperatura
				if(check_obj_temp())
				{
					set_state_check_color();
				}
				else
				{
					process_failure();
				}
			}

			#else
			set_state_check_color();
			#endif
			break;

		case CHECK_COLOR:
			#ifdef COLOR_ON
			if(!digitalRead(IR_2))
			{
				delay(TIME_DELAY);
				// Confere os limites de cor
				if(check_color_limits())
					set_state_check_ocr();
				else
					process_failure();
			}
			#else
			set_state_check_ocr();
			#endif
			break;

		case CHECK_OCR:
			#ifdef OCR_ON
			if(!digitalRead(IR_3))
			{
				delay(TIME_DELAY);
				// Faz a leitura OCR
			}
			#else
			process_ok();
			set_state_idle();
			#endif
			break;

		default:
			break;
	}
}

/**
 * @brief Pisca o LED
 */
void cpl_led()
{
	#ifdef LED_ON
	digitalWrite(LED_PIN, HIGH);
	delay(50);
	digitalWrite(LED_PIN, LOW);
	#endif
}

/**
 * @brief Confere se o volume calculado está dentro dos limites
 */
int check_volume()
{
	calculate_volume();
	#ifdef DISPLAY_ON
	display_volume(control.volume);
	#endif
	debug_msg(printf("\n>> Calculando volume total"));

	if(control.volume >= MIN_VOLUME_VALUE)
	{
		debug_msg(printf("\n>> OK"));
		return 1;
		//debug_msg(printf("\n Volume: %.2f ml -> OK", control.volume));
	}
	else
	{
		return 0;
		delay(1);
		debug_msg(printf("\nValor fora do permitido!"));
		debug_msg(printf("\n"));
	}
}

/**
 * @brief Confere se as cores estão dentro dos limites definidos
 */
int check_color_limits()
{
	#ifdef COLOR_ON

	#ifdef DISPLAY_ON
	display_color();
	#endif

	return 1;
	#else
	return 1;
	debug_msg(printf("\n Sensor de cor desativado"));
	debug_msg(printf("\n"));
	#endif
}

/**
 * @brief Confere se a temperatura esta dentro dos limites definidos
 */
int check_obj_temp()
{
	#ifdef TEMPERATURE_ON
	mlx_init();
	control.obj_temp = read_obj_temperature();

	#ifdef DISPLAY_ON
	display_temperature(control.obj_temp);
	#endif

	debug_msg(printf("\n>> Medindo temperatura"));
	if(control.obj_temp <= MAX_OBJ_TEMPERATURE)
	{
		return 1;
		debug_msg(printf("\n"));
		delay(1);
		debug_msg(printf("Temp: %.2f ºC\n", control.obj_temp));
	}
	else
	{
		return 0;
		debug_msg(printf("Valor fora do permitido!\n"));
	}
	#else
	return 1;
	#endif
}

void buzzer_process_passed()
{
	#ifdef BUZZER_ON
	digitalWrite(BUZZER_PIN, HIGH);
	delay(100);
	digitalWrite(BUZZER_PIN, LOW);
	#endif
}

void buzzer_process_failed()
{
	#ifdef BUZZER_ON
	digitalWrite(BUZZER_PIN, HIGH);
	delay(1000);
	digitalWrite(BUZZER_PIN, LOW);
	delay(300);
	digitalWrite(BUZZER_PIN, HIGH);
	delay(100);
	digitalWrite(BUZZER_PIN, LOW);
	delay(100);
	digitalWrite(BUZZER_PIN, HIGH);
	delay(100);
	digitalWrite(BUZZER_PIN, LOW);
	delay(100);
	digitalWrite(BUZZER_PIN, HIGH);
	delay(100);
	digitalWrite(BUZZER_PIN, LOW);
	#endif
}

void buzzer_bip()
{
    #ifdef BUZZER_ON
    digitalWrite(BUZZER_PIN, HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
    #endif
}


// AQUI COMEÇA O CONTROLE DOS SENSORES, TALVEZ VÁ PARA OUTRO ARQUIVO
void ultrassonic_init()
{
	pinMode(ECHO_PIN, INPUT);
	pinMode(TRIGGER_PIN, OUTPUT);
}

/**
 * @brief Retorna a distância medida pelo sensor ultrassônico
 */
float get_distance()
{
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(20);
    digitalWrite(TRIGGER_PIN, LOW);

    while(digitalRead(ECHO_PIN) == LOW);
    long start = micros();
    while(digitalRead(ECHO_PIN) == HIGH);
    long end = micros() - start;

    return end/58;
}

/**
 * @brief Calcula o volume da garrafa
 *		A lógica para escolha do raio não está implementada
 */
void calculate_volume()
{
	const float PI = 3.141592;	// Talvez incluir a biblioteca math.h
	float altura = OFFSET_DISTANCE_VALUE - get_distance();
	#ifdef TEST_MODE
	debug_msg(printf("\nAlt: %.2f cm", altura));
	#endif
	float raio = 4.75; // Raio do cilindro inferior
	float volume;
	
	// Calcula o volume da parte inferior
	volume = PI*raio*raio*altura;
	
	// Se o liquido estiver acima do cilindro, considera-se outra equação
	/* if(altura >= )
	{
		volume+= 1050;
		// Incluir aqui a outra equação
	}*/

	// Em função das variações de leitura do sensor ultrassonico, podemos ter um volume negativo
	// quando a garrafa estiver vazia, então atualizamos apenas os valores positivos
	if(volume > 0)
		control.volume = volume;
}

#ifdef COLOR_ON
/**
 * @brief Inicializa os pinos do sensor de cor
 */
void tcs_init()
{
	pinMode(TCS_S2, OUTPUT);
	pinMode(TCS_S3, OUTPUT);
	pinMode(TCS_OUT, INPUT);
}

/**
 * @brief Ativa o filtro para cor vermelha
 */
void tcs_set_red_filter()
{
	digitalWrite(TCS_S2, LOW);
	digitalWrite(TCS_S3, LOW);
}

/**
 * @brief Ativa o filtro para cor verde
 */
void tcs_set_green_filter()
{
	digitalWrite(TCS_S2, HIGH);
	digitalWrite(TCS_S3, HIGH);
}

/**
 * @brief Ativa o filtro para cor azul
 */
void tcs_set_blue_filter()
{
	digitalWrite(TCS_S2, LOW);
	digitalWrite(TCS_S3, HIGH);
}

/**
 * @brief Desativa os filtros de cor
 */
void tcs_set_no_filter()
{
	digitalWrite(TCS_S2, HIGH);
	digitalWrite(TCS_S3, LOW);
}

/**
 * @brief Mede a duração de um pulso
 */
int pulseIn(int PIN)
{
	while(digitalRead(PIN) == LOW);
	long start = micros();
	while(digitalRead(PIN) == HIGH);
	long end = micros() - start;
	return end;
}

/**
 * @brief Atualiza as cores detectadas pelo sensor.
 */
void get_color()
{
	delay(20);
	tcs_set_red_filter();
	control.red_color = pulseIn(TCS_OUT);
	delay(20);
	tcs_set_green_filter();
	control.green_color = pulseIn(TCS_OUT);
	delay(20);
	tcs_set_blue_filter();
	control.blue_color = pulseIn(TCS_OUT);
}
#endif