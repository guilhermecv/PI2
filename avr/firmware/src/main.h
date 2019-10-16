#ifndef MAIN_H
#define MAIN_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "conf.h"
#include "dbg_vrb.h"

#ifdef USART_ON
#pragma message "USART ON!"
#include "usart.h"
#else
#pragma message "USART OFF!"
#endif

#ifdef MACHINE_ON
#pragma message "MACHINE ON!"
#include "machine.h"
#else
#pragma message "MACHINE OFF!"
#endif

#ifdef ULTRASSONIC_ON
#include "ultrassonic.h"
#pragma message "ULTRASSONIC ON!"
#else
#pragma message "ULTRASSONIC OFF!"
#endif

#ifdef TEMPERATURE_ON
#pragma message "TEMPERATURE ON!"

#else
#pragma message "TEMPERATURE OFF!"
#endif

#ifdef COLOR_ON
#pragma message "COLOR ON!"
#include "tcs230.h"
#else
#pragma message "COLOR OFF!"
#endif

#ifdef BARCODE_ON
#pragma message "BARCODE ON!"
#include "barcode.h"
#else
#pragma message "BARCODE OFF!"
#endif


#endif
