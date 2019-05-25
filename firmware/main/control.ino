#include "configs.h"

/**
 * @brief Teste dos sensores conectados ao sistema
 */
void control_test()
{
  float distance = get_distance();
  debug_msg(Serial.print("Dist: "));
  debug_msg(Serial.println(distance));
  debug_msg(Serial.print("Volume: "));
  debug_msg(Serial.println(calculate_volume()));
}


void control_run()
{
  
}


/**
 * @brief Calcula o volume da garrafa em ml
 */
float calculate_volume()
{
  float h = get_distance() - OFFSET;    // Desconta a altura medida com a garrafa vazia
  float r = 5.1;                        // Raio do cilíndro inferior da garrafa (cm)
  return PI*(r*r)*h;                      
}
