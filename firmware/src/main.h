/**
 * @file main.h
 *
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "config.h"
#include "dbg_vrb.h"

#ifdef WATCHDOG_ON
#include <avr/wdt.h>
#endif /* WATCHDOG_ON */

#ifdef USART_ON
#include "usart.h"
#endif /* USART_ON */
