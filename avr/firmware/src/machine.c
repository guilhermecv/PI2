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

  state_machine = STATE_INITIALIZING;
}


void machine_run(void)
{
  if(machine_clk)
  {
    machine_clk = 0;
    switch (state_machine) {
      case STATE_INITIALIZING:

      case STATE_IDLE:
        task_idle();
        break;

      case STATE_RUNNING:
        task_running();
        break;

      case STATE_ERROR:
        task_error();
        break;
    }
  }
}

//##################### TASKS ##########################
void task_idle(void)
{
#ifdef LED_ON
  static uint8_t led_clk_div;
  if(led_clk_div++ > 50)
  {
    led_clk_div = 0;
    cpl_led();
  }
#endif

}

void task_running(void)
{
#ifdef LED_ON
  static uint8_t led_clk_div;
  if(led_clk_div++ > 20)
  {
    led_clk_div = 0;
    cpl_led();
  }
#endif
}

void task_error(void)
{
  set_led();
  set_buzzer();
  VERBOSE_MSG_ERROR(usart_send_string("ERROR!\n"));

  for(;;);
}
//#######################################################

ISR(TIMER2_COMPA_vect)
{
  machine_clk = 1;
}
