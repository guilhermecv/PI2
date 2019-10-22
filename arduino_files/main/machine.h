
#include "conf.h"

typedef enum state_machine
{
	INITIALIZING,
	IDLE,
  CHECK_VOLUME,
  CHECK_TEMPERATURE,
  
	RUNNING,
	ERROR,
}state_machine_t;

state_machine_t state_machine;
uint8_t machine_clk;
uint8_t sensor0;
uint8_t sensor1;


void machine_init();
void machine_run();

void task_idle();
void task_running();
void task_error();
