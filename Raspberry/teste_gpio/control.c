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
	debug_msg(printf("Carregando valores iniciais...\n"));
	
}

/**
 * @brief Salva as informações do sistema
 */
void save_file()
{
	FILE *flog;
	flog=fopen(FILENAME, "a");
	fprintf(flog, "%d, %d, %d", control.total, control.passed, control.failed);
	fprintf(flog, "%d, %d, %d", control.red_color, control.green_color, control.blue_color);
	fflush(flog);
}

void set_state_idle()
{
	machine_state = IDLE,
	debug_msg(printf("\n>> IDLE STATE\n"));
	display_idle_message();
//	buzzer_bip();
}

void set_state_running()
{
	machine_state = RUNNING;
	debug_msg(printf("\n>> RUNNING STATE"));
	debug_msg(printf("\n"));
	control.total++;
//	buzzer_bip();
	display_backlight_on();
}

void set_state_check_volume()
{
	machine_state = CHECK_VOLUME;
	debug_msg(printf("\n>> Checking volume"));
	debug_msg(printf("\n"));
//	buzzer_bip();
}

void set_state_check_temperature()
{
	machine_state = CHECK_TEMPERATURE;
	debug_msg(printf("\n>> Checking temperature"));
	debug_msg(printf("\n"));
//	buzzer_bip();
}

void set_state_check_color()
{
	machine_state = CHECK_COLOR;
	debug_msg(printf("\n>> Checking color limits"));
	debug_msg(printf("\n"));
//	buzzer_bip();
}

void set_state_check_ocr()
{
	machine_state = CHECK_OCR;
	debug_msg(printf("\n>> Checking OCR\n"));
	buzzer_bip();
}

void process_failure()
{
	control.failed++;
	buzzer_process_failed();
	save_file();
	set_state_idle();
	debug_msg(printf("Falha na verificacao do processo!\n"));
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
    	float vol = calculate_volume();
	display_set_line(LINE1);
	display_string("Dist ");
	display_float(dist);
	display_string(" cm  ");
	display_set_line(LINE2);
	display_string("Vol: ");
	display_float(vol);
	display_string(" ml  ");
	debug_msg(printf("\nDist: %.2f cm\nVol: %.2f ml", dist, vol));
	debug_msg(printf("\n"));
        delay(500);
	#endif

	#ifdef TEMPERATURE_ON
	float amb_temp = read_amb_temperature();
	delay(1);
	float obj_temp = read_obj_temperature();
	display_clear();
	display_string("Obj Temp:");
	display_float(obj_temp);
	display_set_line(LINE2);
	display_string("Amb Temp:");
	display_float(amb_temp);
    	debug_msg(printf("\nObj temp: %.2f Amb Temp: %.2f\n\n", obj_temp, amb_temp));
	delay(800);
	#endif

	#ifdef COLOR_ON
	get_color();
	display_set_line(LINE1);
	display_string("RGB Values     ");
	display_set_line(LINE2);
	display_int(control.red_color);
	display_string(" ");
	display_int(control.green_color);
	display_string(" ");
	display_int(control.blue_color);
	display_string("     ");
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
			else	// Se o volume estiver fora do padrão, retorna para o estado inicial
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
			}
			#else
			set_state_check_color();
			#endif
			break;

		case CHECK_COLOR:
			#ifdef COLOR_ON

			#else
			set_state_check_ocr();
			#endif
			break;

		case CHECK_OCR:
			#ifdef OCR_ON

			#else
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
	delay(10);
	digitalWrite(LED_PIN, LOW);
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
    delay(100);
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
 * @brief Confere se o volume calculado está dentro dos limites
 */
int check_volume()
{
	float vol = calculate_volume();
	if(vol >= MIN_VOLUME_VALUE)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
 * @brief Calcula o volume da garrafa
 *		A lógica para escolha do raio não está implementada
 */
float calculate_volume()
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
	
	// Em função das variações de leitura do sensor ultrassonico, podemos ter um volume negativo,
	// então retornamos apenas os valores positivos
	if(volume > 0)
		return volume;
	else
		return 0;
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
	delay(2);
	tcs_set_red_filter();
	control.red_color = pulseIn(TCS_OUT);
	delay(2);
	tcs_set_green_filter();
	control.green_color = pulseIn(TCS_OUT);
	delay(2);
	tcs_set_blue_filter();
	control.blue_color = pulseIn(TCS_OUT);
}
#endif
