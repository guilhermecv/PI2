
#ifndef SONAR_H_
#define SONAR_H_

#include <avr/interrupt.h>
#include "def_principais.h" //inclus�o do arquivo com as principais defini��es

#define DISPARO PB1

	ISR(TIMER1_CAPT_vect);
	uint16_t ultrassonico();


#endif /* SONAR_H_ */
