#include "machine.h"

void machine_init(void)
{
  TCCR2A  =   (1 << WGM21) | (0 << WGM20)         // Timer 2 in Mode 2 = CTC (clear on compar  e)
              | (0 << COM2A1) | (0 << COM2A0)         // do nothing with OC2A
              | (0 << COM2B1) | (0 << COM2B0);        // do nothing with OC2B
  TCCR2B  =   (0 << WGM22)                        // Timer 0 in Mode 2 = CTC (clear on compar  e)
              | (0 << FOC0A) | (0 << FOC0B)           // dont force outputs
              | (1 << CS22)                           // clock enabled, prescaller = 1024
              | (1 << CS21)
              | (1 << CS20);
  OCR2A   =   80;                                // Valor para igualdade de comparacao A par  a frequencia de 150 Hz
  TIMSK2 |=   (1 << OCIE2A);                      // Ativa a interrupcao na igualdade de comp  aração do TC2 com OCR2A

  //  state_machine = INITIALIZING;
}

void set_state_idle()
{
  state_machine = IDLE;
//  VERBOSE_MSG_MACHINE(Serial.print("IDLE state\n"));
}

void set_state_running()
{
  state_machine = RUNNING;
//  VERBOSE_MSG_MACHINE(Serial.print("RUNNING state\n"));
}

void set_state_error()
{
  state_machine = ERROR;
}
//############ TASKS ###############
void task_idle()
{
#ifdef LED_ON
  static uint8_t led_clk_div;
  static uint8_t error;

  if(error++ >= 250)
  {
    set_state_error();
  }
  if (led_clk_div++ > 50)
  {
    led_clk_div = 0;
    cpl_led();
  }
#endif
}


void task_error()
{
  VERBOSE_MSG_ERROR(Serial.print("Waiting for a reset\n"));

  for (;;)
  {
    cpl_led();
    cpl_buzzer();
    delay(100);
  }
}

//#################################
void machine_run()
{
  if (machine_clk)
  {
    machine_clk = 0;

    switch (state_machine)
    {
      case INITIALIZING:

        break;

      case IDLE:
        task_idle();
        break;

      case RUNNING:
//        task_running();
        break;

      case ERROR:
        task_error();
        break;
    }
  }
}

ISR(TIMER2_COMPA_vect)
{
  machine_clk = 1;
}
