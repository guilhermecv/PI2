/**
   Controle dos sensores
*/
#include "configs.h"

#ifdef ULTRASSONIC_ON
#include <Ultrasonic.h>
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
#endif


void sensors_init()
{
 
}

/*
 * @brief Mede a distância entre o sensor ultrassonico e o objeto
 */
float get_distance()
{
  #ifdef ULTRASSONIC_ON
  long microsec = ultrasonic.timing();
  float cm = ultrasonic.convert(microsec, Ultrasonic::CM);
  return cm;
  #else
  return 0; // Corresponde ao sensor desativado
  #endif
}

/*
 * @brief Atualiza as cores detectadas pelos sensor
 */
void get_colors()
{
  
}
