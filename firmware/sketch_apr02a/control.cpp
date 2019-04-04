#include "control.h"

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

void buzzer_bip()
{
    set_buzzer();
    _delay_ms(100);
    clr_buzzer();
}

void buzzer_init_ok()
{
  set_buzzer();
  _delay_ms(100);
  clr_buzzer();
  _delay_ms(100);
  set_buzzer();
  _delay_ms(100);
  clr_buzzer();
}

void buzzer_error()
{
  set_buzzer();
  _delay_ms(1000);
  clr_buzzer();
}
