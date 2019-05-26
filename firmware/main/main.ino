#include "configs.h"

void setup() {
#ifdef USART_ON
  Serial.begin(USART_BAUD);
  debug_msg(Serial.println("PI 2 - 2019/1\n"));
  debug_msg(Serial.println("Usart... OK"));
#endif

  DDRB |= (1 << PB5);
  modules_init();
  delay(1000);
  
#ifdef TEST_MODE
  debug_msg(Serial.print("Sistema iniciado em MODO TESTE!\n"));
#endif
  delay(1000);
}

void loop() {
#ifdef TEST_MODE
  modules_test();
#else
  control_run();
#endif

  delay(500);
  PORTB ^= (1 << PB5); // Complementa o estado do LED
}
