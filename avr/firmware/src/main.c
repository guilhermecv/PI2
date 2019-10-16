/**
 * @file main.c
 */

#include "main.h"

int main()
{
#ifdef USART_ON
  usart_init(MYUBRR, 1, 1);
  usart_send_string("PI2 - 2019/1\n\nUSART... OK!\n");
#endif /* USART_ON */

  _delay_ms(200);

#ifdef BUZZER_ON
  BUZZER_DDR |= (1 << BUZZER);
#endif

#ifdef LED_ON
  LED_DDR |= (1 << LED);
  set_led();
#endif

#ifdef MACHINE_ON
  VERBOSE_MSG_INIT(usart_send_string("Machine... "));
  machine_init();
  VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
#else
  VERBOSE_MSG_INIT(usart_send_string("Machine... OFF!\n"));
#endif /* MACHINE_ON */

#ifdef ULTRASSONIC_ON
  VERBOSE_MSG_INIT(usart_send_string("Ultrassonic... "));
  ultrassonic_init();
  VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
#else
  VERBOSE_MSG_INIT(usart_send_string("Ultrassonic... OFF!\n"));
#endif /* ULTRASSONIC_ON */

#ifdef TEMPERATURE_ON
  VERBOSE_MSG_INIT(usart_send_string("Temperature... "));
  mlx_init();
  VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
#else
  VERBOSE_MSG_INIT(usart_send_string("Temperature... OFF!\n"));
#endif /* TEMPERATURE_ON */

#ifdef DISPLAY_ON
  VERBOSE_MSG_INIT(usart_send_string("Display... "));
  display_init();
  VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
#else
  VERBOSE_MSG_INIT(usart_send_string("Display... OFF!\n"));
#endif /* DISPLAY_ON */

#ifdef COLOR_ON
  VERBOSE_MSG_INIT(usart_send_string("Color... "));
  tcs230_init();
  VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
#else
  VERBOSE_MSG_INIT(usart_send_string("Color... OFF!\n"));
#endif /* COLOR_ON */

#ifdef BARCODE_ON
  VERBOSE_MSG_INIT(usart_send_string("Barcode... "));
  barcode_init();
  VERBOSE_MSG_INIT(usart_send_string("OK!\n"));
#else
  VERBOSE_MSG_INIT(usart_send_string("Barcode... OFF!\n"));
#endif /* BARCODE_ON */

  sei();

  while(1)
  {

#ifdef MACHINE_ON
    machine_run();
#else
    cpl_led();
    _delay_ms(200);

#ifdef ULTRASSONIC_ON
    usart_send_string("\nDistance: ");
    usart_send_uint16(get_distance());
    usart_send_string(" cm");
    _delay_ms(700);
#endif

#ifdef COLOR_ON

#endif

#endif /* MACHINE_ON */


#ifdef WATCHDOG_ON

#endif

  }
}
