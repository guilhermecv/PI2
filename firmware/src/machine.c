/**
* @file machine.c
*/

#include "machine.h"

void machine_init()
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

  LED_PORT |= (1 << LED);

  state_machine = IDLE;

}

void machine_run()
{
    if(clk)
    {
        clk = 0;

        switch (state_machine) {
            case IDLE:
            task_idle();
            break;

            case RUNNING:
            task_running();
            break;

            default:
              for(;;);
            break;
        }
    }
}


void task_idle(void)
{
    if(led_clk_div++ > 50)
    {
        cpl_led();
    }

    if(buzzer_clk_div == 0)
    {
        set_buzzer();
    }
    if(buzzer_clk_div++ > 2)
    {
        clr_buzzer();
    }
    if(buzzer_clk_div++ > 100)
        buzzer_clk_div = 0;

    #ifdef DISPLAY_ON
    static uint8_t display_idle_clk_div;

    if(display_idle_clk_div++ > DISPLAY_IDLE_CLK_DIV)
    {
      display_idle_clk_div = 0;
      // display_status(&control_flags);
    }
    #endif /* DISPLAY_ON */
}

void task_running(void)
{
    if(led_clk_div++ > 20)
    {
        led_clk_div = 0;
        cpl_led();
    }
}

ISR(TIMER2_COMPA_vect)
{
  clk = 1;
}
