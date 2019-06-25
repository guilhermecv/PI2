#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include <Wire.h>
#include "conf.h"

void timer_init();
void set_state_error();
void set_state_running();
void set_state_iddle();

void system_run();

void buzzer_bip();

#endif