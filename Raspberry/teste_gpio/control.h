#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <wiringPi.h> 
#include "config.h" 

#ifdef DISPLAY_ON
#include "display.h"
#endif

#ifdef TEMPERATURE_ON
#include "mlx90614.h"
#endif

//const char arquivo[] = "log.csv";

enum states
{
	IDLE,
	RUNNING,
	CHECK_VOLUME,
	CHECK_TEMPERATURE,
	CHECK_COLOR,
	CHECK_OCR,
}states;

struct 
{
	int red_color;
	int green_color;
	int blue_color;
	int total;		// Total de garrafas computadas
	int passed;		// Total de garrafas liberadas
	int failed;		// Total de garrafas não liberadas
}control;

int machine_state;
int backlight_div;

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
void cpl_led();

// Controle do buzzer
void buzzer_process_failed();
void buzzer_process_passed();
void buzzer_bip();

// TALVEZ VÁ PARA OUTRO ARQUIVO
void ultrassonic_init();
float get_distance();
float calculate_volume();
int check_volume();

void tcs_init();
void tcs_set_red_filter();
void tcs_set_green_filter();
void tcs_set_blue_filter();
void tcs_set_no_filter();
int pulseIn(int PIN);
void get_color();

#ifdef DEBUG_ON
#define debug_msg(x)	x
#else
#define debug_msg(x)
#endif
