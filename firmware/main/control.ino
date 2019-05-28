#include "configs.h"
#include "control.h"

void set_initial_state()
{
  process.ok = process.n_ok = process.total = 0;  
  display_clk_div = 0;
  set_state_idle();
}

void set_state_idle()
{
  machine_state = WAITING;
  debug_msg(Serial.println(">> IDLE STATE"));
}

void set_state_error()
{
  machine_state = ERROR;
  debug_msg(Serial.println(">> ERROR STATE"));
}

void set_state_running()
{
  machine_state = RUNNING;
  debug_msg(Serial.println(">> RUNNING STATE"));
  display_init_process();
}

/**
 * @brief Controle dos processos do sistema
 */
void control_run()
{
  switch (machine_state)
  {
    case WAITING:
      display_idle();
      if(led_clk_div++ > 20)
      {
        led_clk_div = 0;
        PORTB^= (1<<PB5);
      }
      // Aguarda alguma leitura do primeiro sensor de posição para prosseguir
      // set_state_running();
      break;

    case RUNNING:

      // machine_state = CHECK_VOLUME;
      // debug_msg(Serial.println(">> CHECK VOLUME"));
      break;

    case CHECK_VOLUME:
      if(check_volume())
      {
        machine_state = CHECK_COLOR;
        debug_msg(Serial.println("Volume OK"));
        debug_msg(Serial.println(">> CHECK COLOR"));
        display_update_volume(calculate_volume());
      }
      else
      {
        debug_msg(Serial.println("Volume fora dos padrões"));
        process.n_ok++;
      }
      break;

    case CHECK_COLOR:
      if(check_colors()){
        machine_state = CHECK_TEMP;
        debug_msg(Serial.println("Color OK"));
        debug_msg(Serial.println(">> CHECK TEMPERATURE"));
        display_color_ok();
      }
      else  // Entra aqui se a cor não estiver dentro dos parâmetros
      {
        debug_msg(Serial.println("Cor fora dos padrões"));
        process.n_ok++;
      }
      break;

    case CHECK_TEMP:
      if(check_temp())
      {
        machine_state = CHECK_OCR;
        debug_msg(Serial.println("Temperature OK"));
        debug_msg(Serial.println(">> CHECK OCR"));
      }
      else  // Entra aqui se a temperatura estiver fora dos parâmetros
      {
        debug_msg(Serial.println("Temperatura fora dos padrões"));
        process.n_ok++;
      }
      break;

    case CHECK_OCR:
      if(check_ocr())
      {
        // Se tudo estiver correto, retorna para o estado inicial
        debug_msg(Serial.println("OCR OK"));
        if(display_clk_div++ > 5)
        {
          display_process_status(process.ok,process.n_ok,process.total);
        }
        else if(display_clk_div++ > 10)
        {
          display_clk_div = 0;
          debug_msg(Serial.println(">> IDLE STATE"));
          set_state_idle();
        }
        else
        {
          
        }
        
        process.ok++; // Só chega a este ponto quando todos os parâmetros estão corretos
      }
      else  // Entra aqui se a leitura ocr for inválida
      {
        debug_msg(Serial.println("OCR fora dos padrões"));
        process.n_ok++;
      }
      break;

    case ERROR:
      if(led_clk_div++ > 5)
      {
        led_clk_div = 0;
        PORTB^=(1<<PB5);
      }
      break;
      
    default:
      set_state_error();
      break;
  }
}

//==================== PROCESSOS ==========================
/**
 * @brief Checa se o volume está ok
 */
int check_volume()
{
  float vol = calculate_volume();
  // Implementar teste do volume
  return 1; // Volume OK
}

/**
 * @brief Checa se a temperatura está ok
 */
int check_temp()
{
  // Implementar o teste de temperatura
  return 1; // Temperatura OK
}

/**
 * @brief Checa se a cor está ok
 */
int check_colors()
{
  // Implementar o teste de cor!!
  return 1; // Color OK
}

/**
 * @brief Envia o comando para o leitor OCR
 */
int check_ocr()
{
  // Envia o comando para início de leitura

  // Aguarda o retorno
  return 1; // OCR OK
}

/**
 * @brief Calcula o volume da garrafa em ml
 */
float calculate_volume()
{
  float h = OFFSET - get_distance();    // Desconta a altura medida com a garrafa vazia
  float r = 5.1;                        // Raio do cilíndro inferior da garrafa (cm)
  return PI * (r * r) * h;
}
