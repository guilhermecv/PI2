#ifndef MACHINE_H
#define MACHINE_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "conf.h"
#include "dbg_vrb.h"

#ifdef USART_ON
#include "usart.h"
#endif

#ifdef ULTRASSONIC_ON
#include "ultrassonic.h"
#endif

#ifdef BARCODE_ON
#include "barcode.h"
#endif

#ifdef COLOR_ON
#include "tcs230.h"
#endif

typedef enum state_machine
{
  STATE_INITIALIZING,
  STATE_IDLE,
  STATE_RUNNING,
  STATE_ERROR,
}state_machine_t;

uint8_t machine_clk;
state_machine_t state_machine;


void machine_init(void);
void machine_run(void);

//>> TASKS
void task_idle(void);
void task_running(void);
void task_error(void);


ISR(TIMER2_COMPA_vect);

#endif
