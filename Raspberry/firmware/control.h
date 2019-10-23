#ifndef CONTROL_H
#define CONTROL_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>
#include <ctype.h>
#include <string.h>
#include "config.h"

#ifdef DISPLAY_ON
#include "display.h"
#endif

#ifdef TEMPERATURE_ON
#include "mlx90614.h"
#endif

#ifdef COLOR_ON
#include "tcs3200.h"
#endif

#ifdef BARCODE_ON
#include "barcode.h"
#endif

enum states
{
	IDLE,
	RUNNING,
	CHECK_VOLUME,
	CHECK_TEMPERATURE,
	CHECK_COLOR,
	CHECK_OCR,
}states;

struct control
{
	int red_color;
	int green_color;
	int blue_color;
	float volume;
	float obj_temp;
	int total;		// Total de garrafas computadas
	int passed;		// Total de garrafas liberadas
	int failed;		// Total de garrafas não liberadas
}control;

int machine_state;
int display_div;
int led_div;
int buzzer_div;

// Manipulação de arquivos
void load_file();
void save_file();

// Controle dos estados
void set_state_idle();
void set_state_running();
void set_state_check_volume();
void set_state_check_temperature();
void set_state_check_color();
void set_state_check_ocr();

void control_test();
void control_run();

// Controle do buzzer
void buzzer_process_failed();
void buzzer_process_passed();
void buzzer_bip();
void buzzer_alive();
void buzzer_ir_detected();

// Checagem dos parametros
int check_obj_temp();
int check_color_limits();
int check_volume();
void check_ocr();
void check_barcode();

// TALVEZ VÁ PARA OUTRO ARQUIVO
void ultrassonic_init();
float get_distance();
void calculate_volume();

void get_color();


#ifdef DEBUG_ON
#define debug_msg(x)	x
#else
#define debug_msg(x)
#endif


#endif /* CONTROL_H */
