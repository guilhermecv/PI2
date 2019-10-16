#ifndef ULTRASSONIC_H
#define ULTRASSONIC_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "conf.h"
#include "../lib/bit_utils.h"

uint16_t start_time;
uint16_t distance;

void ultrassonic_init(void);
uint16_t get_distance();

ISR(TIMER1_CAPT_vect);
#endif
