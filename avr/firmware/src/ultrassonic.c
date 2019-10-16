/**
 * @file ultrassonic.c
 *
 * @author Guilherme Camargo Valese
 *
 * @date 15/10/2019
 *
 * Para uso com os sensores ultrassônicos HC-SR04 e JSN
 */

#include "ultrassonic.h"

/**
 * @brief
 */
void ultrassonic_init(void)
{
  TCCR1B = (1<<ICES1)|(1<<CS11);
  TIMSK1 = 1<<ICIE1;

  HC_DDR |= (1 << HC_TRIGGER);
  HC_DDR &=~(1 << HC_ECHO);

  start_time = distance = 0;
}

/**
 * @brief measure distance in cm
 * @return distance
 */
uint16_t get_distance()
{
  HC_PORT |= (1 << HC_TRIGGER);
  _delay_us(10);
  HC_PORT &=~(1 << HC_TRIGGER);

  return distance;
}

ISR(TIMER1_CAPT_vect)
{
  cpl_bit(TCCR1B,ICES1);
	if(!tst_bit(TCCR1B,ICES1))
    start_time = ICR1;
  else
		distance = (ICR1 - start_time)/58;
}
