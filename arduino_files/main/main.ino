/**
   @file main.c
*/

#include "main.h"

void setup() {
#ifdef USART_ON
  Serial.begin(9600);
  VERBOSE_MSG_INIT(Serial.print("Usart... OK!\n"));
#endif

#ifdef LED_ON
  LED_DDR |= (1 << LED);
  LED_PORT |= (1 << LED);
#endif

#ifdef WATCHDOG_ON
  VERBOSE_MSG_INIT(Serial.print("Watchdog..."));
  wdt_enable(WDTO_8S);
  wdt_reset();
  VERBOSE_MSG_INIT(Serial.print("OK!\n"));
#else
  VERBOSE_MSG_INIT(Serial.print("Watchdog... OFF!\n"));
#endif

#ifdef ULTRASSONIC_ON
  VERBOSE_MSG_INIT(Serial.print("Ultrassonic..."));

  VERBOSE_MSG_INIT(Serial.print("OK!\n"));
#else
  VERBOSE_MSG_INIT(Serial.print("Ultrassonic... OFF!\n"));
#endif

#ifdef WATCHDOG_ON
  wdt_reset();
#endif

#ifdef TEMPERATURE_ON
  VERBOSE_MSG_INIT(Serial.print("Temperature..."));

  VERBOSE_MSG_INIT(Serial.print("OK!\n"));
#else
  VERBOSE_MSG_INIT(Serial.print("Temperature... OFF!\n"));
#endif

#ifdef WATCHDOG_ON
  wdt_reset();
#endif

#ifdef COLOR_ON
  VERBOSE_MSG_INIT(Serial.print("Color..."));

  VERBOSE_MSG_INIT(Serial.print("OK!\n"));
#else
  VERBOSE_MSG_INIT(Serial.print("Color... OFF!\n"));
#endif

#ifdef WATCHDOG_ON
  wdt_reset();
#endif

#ifdef WATCHDOG_ON
  wdt_reset();
#endif

#ifdef DISPLAY_ON
  VERBOSE_MSG_INIT(Serial.print("Display..."));

  VERBOSE_MSG_INIT(Serial.print("OK!\n"));
#else
  VERBOSE_MSG_INIT(Serial.print("Display... OFF!\n"));
#endif

#ifdef WATCHDOG_ON
  wdt_reset();
#endif

#ifdef BARCODE_ON
  VERBOSE_MSG_INIT(Serial.print("Barcode..."));

  VERBOSE_MSG_INIT(Serial.print("OK!\n"));
#else
  VERBOSE_MSG_INIT(Serial.print("Barcode... OFF!\n"));
#endif

#ifdef WATCHDOG_ON
  wdt_reset();
#endif

#ifdef MACHINE_ON
  VERBOSE_MSG_INIT(Serial.print("Machine..."));
  machine_init();
  set_state_idle();
  VERBOSE_MSG_INIT(Serial.print("OK!\n"));
#else
  VERBOSE_MSG_INIT(Serial.print("Machine... OFF!\n"));
#endif

#ifdef WATCHDOG_ON
  wdt_reset();
#endif

}

void loop() {
#ifdef MACHINE_ON
  machine_run();
#endif

#ifdef WATCHDOG_ON
  wdt_reset();
#endif

}
