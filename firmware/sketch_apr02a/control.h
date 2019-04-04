#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include <util/delay.h>
#include <Wire.h>
#include "conf.h"

void timer_init();
void buzzer_bip();
void buzzer_init_ok();
void buzzer_error();

#endif
