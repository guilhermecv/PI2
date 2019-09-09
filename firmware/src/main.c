/**
* @file main.c
*
*
*/

#include "main.h"

int main()
{
    #ifdef USART_ON
    usart_init(MYUBRR, 1, 1);
    #endif /* USART_ON */

    _delay_ms(200);

    #ifdef WATCHDOG_ON
    VERBOSE_MSG_INIT(usart_send_string("WATCHDOG... "));
    // wdt_init(WDT0_4S);
    VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
    #else
    VERBOSE_MSG_INIT(usart_send_string("WATCHDOG... OFF!\n"));
    #endif /* WATCHDOG_ON */

    #ifdef DISPLAY_ON
    VERBOSE_MSG_INIT(usart_send_string("DISPLAY... "));

    VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
    #else
    VERBOSE_MSG_INIT(usart_send_string("DISPLAY... OFF!\n"));
    #endif /* DISPLAY_ON */

    #ifdef MACHINE_ON
    VERBOSE_MSG_INIT(usart_send_string("MACHINE... "));
    machine_init();
    VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
    #else
    VERBOSE_MSG_INIT(usart_send_string("MACHINE... OFF!\n"));
    #endif /* MACHINE_ON */

    #ifdef WATCHDOG_ON
    wdt_reset();
    #endif /* WATCHDOG_ON */

    #ifdef BARCODE_ON
    VERBOSE_MSG_INIT(usart_send_string("BARCODE... "));
    barcode_init();
    VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
    #else
    VERBOSE_MSG_INIT(usart_send_string("BARCODE... OFF!\n"));
    #endif /* BARCODE_ON */

    #ifdef ULTRASSONIC_ON
    VERBOSE_MSG_INIT(usart_send_string("ULTRASSONIC... "));
    ultrassonic_init();
    VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
    #else
    VERBOSE_MSG_INIT(usart_send_string("ULTRASSONIC... OFF!\n"));
    #endif /* ULTRASSONIC_ON */

    #ifdef WATCHDOG_ON
    wdt_reset();
    #endif /* WATCHDOG_ON */

    #ifdef MLX_ON
    VERBOSE_MSG_INIT(usart_send_string("MLX... "));
    mlx_init();
    VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
    #else
    VERBOSE_MSG_INIT(usart_send_string("MLX... OFF!\n"));
    #endif /* MLX_ON */


    while(1)
    {
        #ifdef WATCHDOG_ON
        wdt_reset();
        #endif /* WATCHDOG_ON */

        #ifdef MACHINE_ON
        machine_run();
        #endif /* MACHINE_ON */
    }
}
