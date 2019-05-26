#include "configs.h"
//#include "control.h"

void control_run()
{
  display_idle();
}

/**
 * @brief Calcula o volume da garrafa em ml
 */
float calculate_volume()
{
  float h = OFFSET - get_distance();    // Desconta a altura medida com a garrafa vazia
  float r = 5.1;                        // Raio do cilíndro inferior da garrafa (cm)
  return PI*(r*r)*h;                      
}

