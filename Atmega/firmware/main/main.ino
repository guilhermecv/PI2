#include "configs.h"

void setup() {
  buzzer_delay(100);
  #ifdef USART_ON
  Serial.begin(USART_BAUD);
  debug_msg(Serial.println("PI 2 - 2019/1\n"));
  debug_msg(Serial.println("Usart... OK"));
  #endif /* USART_ON */

  pinMode(menu_button, INPUT_PULLUP);

  #ifndef TEST_MODE
  if(!digitalRead(menu_button)) // Se o sistema for iniciado com o botao pressionado, inicia modo de configuração
  {
    debug_msg(Serial.println("Entrando em modo de configuração..."));
    buzzer_delay(1000);
    configure();
    buzzer_delay(100);
  }
  #endif
  
  DDRB |= (1 << PB5); // PB5 - LED de status
  modules_init();     // Incializa os módulos utilizados
  delay(1000);
  
  #ifdef TEST_MODE
  debug_msg(Serial.print("Sistema iniciado em MODO TESTE!\n"));
  delay(1000);
  #else
  debug_msg(Serial.println("Sistema iniciado corretamente"));
  #endif /* TEST_MODE */
}

void loop() {
  #ifdef TEST_MODE
  modules_test();
  #else
  control_run();
  #endif /* TEST_MODE */
  
  delay(100);
}
