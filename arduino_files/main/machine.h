
#include "conf.h"

typedef enum state_machine
{
	INITIALIZING,
	IDLE,
	RUNNING,
	ERROR,
}state_machine_t;

state_machine_t state_machine;
uint8_t machine_clk;

void machine_init();
void machine_run();

void task_idle();
void task_running();
void task_error();
