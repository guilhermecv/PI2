#include "control.h"

uint8_t led_clk_div;
uint8_t clk;
uint8_t clk_div;
uint8_t machine_state;

enum states
{
    IDDLE,
    RUNNING,
    ERROR,
}states;

void timer_init()
{
    TCCR2A  =   (1 << WGM21) | (0 << WGM20)         // Timer 2 in Mode 2 = CTC (clear on compar  e)
            | (0 << COM2A1) | (0 << COM2A0)         // do nothing with OC2A
            | (0 << COM2B1) | (0 << COM2B0);        // do nothing with OC2B
    TCCR2B  = (0 << WGM22)                          // Timer 0 in Mode 2 = CTC (clear on compar  e)
            | (0 << FOC0A) | (0 << FOC0B)           // dont force outputs
            | (1 << CS22)                           // clock enabled, prescaller = 1024
            | (1 << CS21)
            | (1 << CS20);
    OCR2A   =   80;                                // Valor para igualdade de comparacao A par  a frequencia de 150 Hz
    TIMSK2 |=   (1 << OCIE2A);                      // Ativa a interrupcao na igualdade de comp  aração do TC2 com OCR2A
}

void set_state_error()
{
    machine_state = ERROR;
}

void set_state_running()
{
    machine_state = RUNNING;
}

void set_state_iddle()
{
    machine_state = IDDLE;
}


void system_run()
{
    if(clk)
    {
        clk=0;
        switch (machine_state)
        {
            case IDDLE:
                if(led_clk_div++ > 30)
                {
                    led_clk_div = 0;
                    cpl_led();
                }
                break;
            case RUNNING:
                if(led_clk_div++ > 10)
                {
                    led_clk_div = 0;
                    cpl_led();
                }

                break;

            case ERROR:
                if(led_clk_div++ > 2)
                {
                    led_clk_div = 0;
                    cpl_led();
                }
                break;
        
            default:
                break;
        }
    }
}

void buzzer_bip()
{
    set_buzzer();
    delay(100);
    clr_buzzer();
}

ISR(TIMER2_COMPA_vect)
{
  if(clk_div++ > CLK_DIV_VALUE)
  {
    clk_div = 0;
    if(clk)
    {
      Serial.println("Conflito de clock");
    }
    clk=1;
  }
}