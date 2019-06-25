/**
 * Projeto Integrador 2 - 2019/1
 * IFSC Engenharia Eletrônica
 * Autores: Guilherme Camargo e Jéssica Ribeiro
 */

#include "main.h"

int main()
{
	printf("PI 2 - 2019/1\nIniciando...\n\n");
	wiringPiSetup();
	pinMode(BUZZER_PIN, OUTPUT);
	buzzer_bip();
	sleep(1);

	#ifdef DISPLAY_ON
	printf("Display....... ON!\n");
	lcd_init();
	display_string("PI 2 - 2019/1");
	display_set_line(LINE2);
	display_string("Iniciando...");
	#else
	printf("Display....... OFF!\n");
	#endif // DISPLAY_ON

	#ifdef LED_ON
	printf("LED........... ON!\n");
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
	#else
	printf("LED........... OFF!\n");
	#endif // LED_ON

	#ifdef BUZZER_ON
	printf("Buzzer........ ON!\n");
	#else
	printf("Buzzer........ OFF!\n");
	#endif

	#ifdef TEMPERATURE_ON
	printf("Temperature... ON!\n");
	mlx_init();
	#else
	printf("Temperature... OFF!\n");
	#endif // TEMPERATURE_ON

	#ifdef ULTRASSONIC_ON
	printf("Ultrassonic... ON!\n");
	ultrassonic_init();
	printf("Distancia: %.2f\n", get_distance());
	#else
	printf("Ultrassonic... OFF!\n");
	#endif // ULTRASSONIC_OFF

	#ifdef COLOR_ON
	printf("Color......... ON!\n");
	tcs_init();
	#else
	printf("Color......... OFF!\n");
	#endif // COLOR_ON

	#ifdef OCR_ON
	printf("OCR........... ON!\n");
	#else
	printf("OCR........... OFF!\n");
	#endif // OCR_ON

	pinMode(IR_0, INPUT);
	pinMode(IR_1, INPUT);
	pinMode(IR_2, INPUT);
	pinMode(IR_3, INPUT);

	#ifdef TEST_MODE
	printf("\nSistema iniciado em MODO TESTE!!");
	printf("\nAs operacoes de verificacao estao suspensas\nPressione <ctrl+c> para encerrar a execucao do programa\n");
	#else
	printf("\nSistema iniciado corretamente!");
	printf("\n");
	set_state_idle();
	#endif

	sleep(2);

	while(1)
	{
		cpl_led();

		#ifdef TEST_MODE
		control_test();
		#else
		control_run();
		#endif
	}
	return 0;
}
