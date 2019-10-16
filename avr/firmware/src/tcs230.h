#ifndef TCS230_H
#define TCS230_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../lib/bit_utils.h"
#include "conf.h"

void tcs230_init();
void tcs_set_red();
void tcs_set_green();
void tcs_set_blue();

uint8_t get_red();
uint8_t get_green();
uint8_t get_blue();

uint32_t tcs_measure();

#endif
