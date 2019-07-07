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

#ifdef LED_ON
	printf("LED........... ON!\n");
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);
#else
	printf("LED........... OFF!\n");
#endif // LED_ON

#ifdef TEMPERATURE_ON
	printf("Temperature... ON!\n");
	mlx_init();
#else
	printf("Temperature... OFF!\n");
#endif // TEMPERATURE_ON

#ifdef DISPLAY_ON
	printf("Display....... ON!\n");
	lcd_init();
	display_string("PI 2 - 2019/1");
	display_set_line(LINE2);
	display_string("Iniciando...");
#else
	printf("Display....... OFF!\n");
#endif // DISPLAY_ON

	sleep(1);
#ifdef BUZZER_ON
	printf("Buzzer........ ON!\n");
#else
	printf("Buzzer........ OFF!\n");
#endif

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

#ifdef BARCODE_ON
	printf("Barcode....... ON!\n");
	barcode_init();
#else
	printf("Barcode....... OFF!\n");
#endif

	pinMode(IR_0, INPUT);
	pinMode(IR_1, INPUT);
	pinMode(IR_2, INPUT);
	pinMode(IR_3, INPUT);

#ifdef TEST_MODE
	#ifdef BARCODE_ON
	printf("\nTestando codigo de barras\n");
	sleep(2);
	barcode_get_data();
	printf("\nConferindo...\n");
	printf("%d\n", barcode_check());
	sleep(2);
	#endif
	#ifdef OCR_ON
	printf("\nTestando OCR...\n");
	sleep(2);
	check_ocr();
	#endif
	printf("\nSistema iniciado em MODO TESTE!!");
	printf("\nAs operacoes de verificacao estao suspensas\nPressione <ctrl+c> para encerrar a execucao do programa\n");
#else
	load_file();
	printf("\nSistema iniciado corretamente!");
	sleep(2);
	set_state_idle();
#endif

	while (1)
	{
#ifdef TEST_MODE
		control_test();
#else
		control_run();
#endif

		delay(5);
	}
	return 0;
}
