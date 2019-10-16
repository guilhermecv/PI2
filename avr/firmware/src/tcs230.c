/**
 * Controle do sensor de cor TCS230/TCS3200
 * Referência: http://www.unihedron.com/projects/darksky/tcs230-e33.pdf
 */
#include "tcs230.h"

/**
 *  Inicializa os pinos utilizados.
 *  Para o atmega328, a saída é geralmente configurada para 20%
 *  S0 -> 1
 *  S1 -> 0
 */
void tcs230_init()
{
    TCS_DDR = (1<<TCS_S0)
            | (1<<TCS_S1)
            | (1<<TCS_S2)
            | (1<<TCS_S3);
    clr_bit(TCS_DDR, TCS_OUT);
    set_bit(TCS_PORT,TCS_S0);
    clr_bit(TCS_PORT,TCS_S1);
}

/**
 *  Ativa o filtro para cor vermelha
 */
void tcs_set_red()
{
    clr_bit(TCS_PORT, TCS_S2);
    clr_bit(TCS_PORT, TCS_S3);
}

/**
 *  Ativa o filtro para cor verde
 */
void tcs_set_green()
{
    set_bit(TCS_PORT, TCS_S2);
    set_bit(TCS_PORT, TCS_S3);
}

/**
 *  Ativa o filtro para cor azul
 */
void tcs_set_blue()
{
    set_bit(TCS_PORT, TCS_S2);
    clr_bit(TCS_PORT, TCS_S3);
}

uint32_t tcs_measure()
{
   //If the function is entered when the level on OUT line was low
   //Then wait for it to become high.
   if(!(TCS_PORT & (1<<TCS_OUT)))
   {
      while(!(TCS_PORT & (1<<TCS_OUT)));   //Wait for rising edge
   }


   while(TCS_PORT & (1<<TCS_OUT));   //Wait for falling edge

   TCNT1=0x0000;//Reset Counter

   TCCR1B=(1<<CS10); //Prescaller = F_CPU/1 (Start Counting)

   while(!(TCS_PORT & (1<<TCS_OUT)));   //Wait for rising edge

   //Stop Timer
   TCCR1B=0x00;

   return ((float)16000000UL/TCNT1);
}
