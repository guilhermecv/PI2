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
	#ifdef DISPLAY_ON
	display_load_message();
	#endif
	FILE *flog;
	int n;
	flog = fopen(FILENAME, "r");
	if(flog == NULL)
	{
		printf("Erro ao abrir o arquivo");
		#ifdef DISPLAY_ON
		display_clear();
		display_string("   Falha na    ");
		display_set_line(LINE2);
		display_string(" Inicializacao ");
		#endif
		exit(1);
	}
	while(1)
	{
		n = fscanf(flog, "%d, %d, %d, , , , , ", &control.total, &control.passed, &control.failed);
		control.total = control.passed + control.failed;
		if(n=='\0')
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
	flog=fopen(FILENAME, "w");
	fprintf(flog, "%d, %d, %d,", control.total, control.passed, control.failed);
	fprintf(flog, "%.2f, %.2f,", control.volume, control.obj_temp);
	fprintf(flog, "%d, %d, %d\n", control.red_color, control.green_color, control.blue_color);
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
	set_state_idle();
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

void process_delay()
{
	int i;
	for(i=0;i<DELAY;i++)
	{
		delay(500);
		digitalWrite(LED_PIN, HIGH);
		delay(100);
		digitalWrite(LED_PIN, LOW);
		#ifdef BUZZER_ON
		//buzzer_bip();
		#endif
	}
	digitalWrite(LED_PIN, HIGH);
}

/**
 * @brief Máquina de estados para controle dos processos de verificação
 */
void control_run()
{
	switch (machine_state)
	{
		case IDLE:
			buzzer_alive();
			#ifdef LED_ON
			if(led_div++ > 300)
			{
				digitalWrite(LED_PIN, HIGH);
			}
			if(led_div++ > 600)
			{
				led_div = 0;
				digitalWrite(LED_PIN, LOW);
			}
			#endif

			#ifdef DISPLAY_ON
			if(display_div++ > 1000)
			{
				display_div = 0;
				display_backlight_off();
				display_update_status(control.total,control.passed,control.failed);
			}
			#endif

			if(digitalRead(IR_0))
			{
				#ifdef BUZZER_IR_ON
				buzzer_ir_detected();
				#endif
				set_state_running();
				process_delay();
			}
			break;

		case RUNNING:
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
			if(digitalRead(IR_1))
			{
				#ifdef BUZZER_IR_ON
				buzzer_ir_detected();
				#endif
			   	process_delay();
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
			if(digitalRead(IR_2))
			{
				#ifdef BUZZER_IR_ON
				buzzer_ir_detected();
				#endif
				process_delay();
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
			check_ocr();
			#else
			process_ok();
			#endif
			break;

		default:
			break;
	}
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
	}
	else
	{
		debug_msg(printf("\nValor fora do permitido!"));
		return 0;
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
	debug_msg(printf("\n Sensor de cor desativado"));
	debug_msg(printf("\n"));
	return 1;
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
		debug_msg(printf("\n"));
		delay(1);
		debug_msg(printf("Temp: %.2f ºC\n", control.obj_temp));
		return 1;
	}
	else
	{
		debug_msg(printf("Valor fora do permitido!\n"));
		return 0;
	}
	#else
	return 1;
	#endif
}

/**
 * @brief Leitura OCR
 */
void check_ocr()
{
	// Envia comando para salvar imagem
	#ifdef DISPLAY_ON
	display_clear();
	display_string("Leitura OCR");
	display_set_line(LINE2);
	display_string("Aguarde...");
	#endif
	system("fswebcam -r 640x480 --jpeg 100 -D 1 rotulo.jpg");
	// Faz a leitura com o tesseract, este processo pode ser demorado...
	system("tesseract rotulo.jpg rotulo");
	char texto[500];
    int passed;
    FILE *fp;
    fp = fopen("rotulo.txt", "r");
    if(fp == NULL)
    {
        debug_msg(printf("\nNenhum arquivo de rotulo encontrado"));
        process_failure();
		#ifdef DISPLAY_ON
		display_set_line(LINE2);
		display_string("ERRO         ");
		#endif
    }
    else
    {
        while(1)
        {
            if(feof(fp))
                break;
            fgets(texto,sizeof(texto), fp);
            printf("%s", texto);
            passed = strcmp(texto, "suco de uva") || strcmp(texto, "suco") ;
        }
		if(passed == 1)
		{
			process_ok();
			debug_msg(printf("\nLeitura OCR finalizada com sucesso"));
			#ifdef DISPLAY_ON
			display_set_line(LINE2);
			display_string("Rotulo OK      ");
			#endif
		}
		else
		{
			process_failure();
			debug_msg(printf("\nRotulo fora das especificacoes"));
			#ifdef DISPLAY_ON
			display_set_line(LINE2);
			display_string("Falha no rotulo");
			#endif
		}
    }
	sleep(1);
    fclose(fp);
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

void buzzer_ir_detected()
{
	#ifdef BUZZER_ON
	buzzer_bip();
	delay(50);
	buzzer_bip();
	#endif
}

void buzzer_alive()
{
	#ifdef BUZZER_SIGNAL_ON
	#ifdef BUZZER_ON
	if(buzzer_div++ > 2050)
	{
		digitalWrite(BUZZER_PIN, HIGH);
	}
	if(buzzer_div++ > 2060)
	{
		buzzer_div = 0;
		digitalWrite(BUZZER_PIN, LOW);
	}
	#endif
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
	
	// Calcula o volume da parte inferior, considerado um cilindro.
	volume = PI*raio*raio*altura;
	
	// Se o liquido estiver acima do cilindro, considera-se outra equação
	/* if(altura >= )
	{
		volume+= 1050;
		// Incluir aqui a outra equação
	}*/

	if(volume > 0)
		control.volume = volume;
	else
		control.volume = 0;
}

#ifdef COLOR_ON
/**
 * @brief Atualiza as cores detectadas pelo sensor.
 */
void get_color()
{
	delay(20);
	control.red_color = get_red_color();
	delay(20);
	control.green_color = get_green_color();
	delay(20);
	control.blue_color = get_blue_color();
}
#endif
