#include <wiringPi.h>
#include "config.h"

void tcs_init();
void tcs_set_red_filter();
void tcs_set_green_filter();
void tcs_set_blue_filter();
void tcs_set_no_filter();

int pulseIn(int PIN);

int get_red_color();
int get_green_color();
int get_blue_color();
