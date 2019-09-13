#ifndef MACHINE_H
#define MACHINE_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "config.h"
#include "dbg_vrb.h"

typedef enum
{
    IDLE,
    RUNNING,
    ERROR,
}state_machine_t;

typedef struct control_flags
{

}control_flags_t;


uint8_t clk;
uint8_t led_clk_div;
uint8_t buzzer_clk_div;

state_machine_t state_machine;

void machine_init(void);
void machine_run(void);


// tasks
void task_idle(void);
void task_running(void);
void task_error(void);

ISR(TIMER2_COMPA_vect);

#endif /* MACHINE_H */
