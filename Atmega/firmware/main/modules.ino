/**
   Controle dos sensores e módulos
*/
#include "configs.h"
#include "modules.h"
#include <Wire.h>

#ifdef ULTRASSONIC_ON
#include <Ultrasonic.h>
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
#endif

#ifdef DISPLAY_ON
#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(LCD_ADDR);
#endif

#ifdef TEMPERATURE_ON
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#endif

/**
   @brief Inicialização dos módulos
*/
void modules_init()
{
#ifdef DISPLAY_ON
  debug_msg(Serial.print("LCD... "));
  Wire.begin();
  Wire.beginTransmission(LCD_ADDR);
  error.lcd = Wire.endTransmission();
  if (error.lcd)
  {
    debug_msg(Serial.print("NOT FOUND!\n"));
  }
  else
  {
    debug_msg(Serial.print("OK!\n"));
  }

  lcd.begin(16, 2);
  lcd.setBacklight(255);
#ifdef TEST_MODE
  lcd.print("** TEST MODE **");
#else
  lcd.print("PI 2 - 2019/1");
  lcd.setCursor(0, 2);
  lcd.print("Iniciando...");
#endif /* TEST_MODE */
#else
  debug_msg(Serial.print("LCD... OFF!\n"));
#endif /* DISPLAY_ON */

#ifdef TEMPERATURE_ON
  debug_msg(Serial.print("Temperature..."));
  mlx.begin();
  debug_msg(Serial.print(" ON!\n"));
#else
  debug_msg(Serial.print("Temperature... OFF!\n"));
#endif /* TEMPERATURE_ON */

#ifdef COLOR_ON
  debug_msg(Serial.print("Color... ON\n"));
  tcs_init();
#else
  debug_msg(Serial.print("Color... OFF\n"));
#endif /* COLOR_ON */

  set_initial_state();
}

/**
   @brief Teste dos sensores conectados ao sistema
*/
void modules_test()
{
#ifdef ULTRASSONIC_ON
  float distance = get_distance();
  debug_msg(Serial.print("Dist: "));
  debug_msg(Serial.println(distance));
  debug_msg(Serial.print("Volume: "));
  debug_msg(Serial.println(calculate_volume()));
#endif

#ifdef TEMPERATURE_ON
  debug_msg(Serial.print("Obj Temp: "));
  debug_msg(Serial.println(get_obj_temperature()));
  debug_msg(Serial.print("Amb Temp: "));
  debug_msg(Serial.println(get_amb_temperature()));
#endif

#ifdef COLOR_ON
  debug_msg(Serial.print("R: "));
  debug_msg(Serial.print(get_red_color()));
  debug_msg(Serial.print(" G: "));
  debug_msg(Serial.print(get_green_color()));
  debug_msg(Serial.print(" B: "));
  debug_msg(Serial.println(get_blue_color()));
#endif
}

void display_idle()
{
#ifdef DISPLAY_ON
  int backlight_clk_div;
  if (backlight_clk_div++ > 10)
  {
    backlight_clk_div = 0;
    lcd.setBacklight(0);
  }
  lcd.clear();
  lcd.print("PI 2 - 2019/1");
  lcd.setCursor(0, 1);
  lcd.print("Em espera");
#endif
}

void display_init_process()
{
#ifdef DISPLAY_ON
  lcd.setBacklight(255);
  lcd.clear();
  lcd.print("Iniciando");
  lcd.setCursor(0, 1);
  lcd.print("Medicoes");
#endif
}

void display_update_volume(float volume)
{
#ifdef DISPLAY_ON
  lcd.clear();
  lcd.print("V: ");
  lcd.print(volume);
#endif
}

void display_color_ok()
{
#ifdef DISPLAY_ON
  lcd.clear();
  lcd.print("PI 2 - 2019/1");
  lcd.setCursor(0, 2);
  lcd.print("Cor -> OK");
#endif
}

/*
   @brief Apresenta um resuma do status do sistema
*/
void display_process_status(int ok, int n_ok, int total)
{
#ifdef DISPLAY_ON
  lcd.clear();
  lcd.print("Total: ");
  lcd.print(total);
  lcd.setCursor(0, 2);
  lcd.print("OK: ");
  lcd.print(ok);
  lcd.print(" N_OK: ");
  lcd.print(n_ok);
#endif
}

/*
   @brief Mede a distância entre o sensor ultrassonico e o objeto
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

/**
   @brief Mede a temperatura do objeto
*/
float get_obj_temperature()
{
#ifdef TEMPERATURE_ON
  return mlx.readObjectTempC();
#else
  return 0;
#endif
}

/*
   @brief Mede a temperatura do ambiente
*/
float get_amb_temperature()
{
#ifdef TEMPERATURE_ON
  return mlx.readAmbientTempC();
#else
  return 0;
#endif
}

/**
   @brief Inicia o sensor de cor com 20% da frequência nominal
*/
void tcs_init()
{
  pinMode(TCS_S0, OUTPUT);
  pinMode(TCS_S1, OUTPUT);
  pinMode(TCS_S2, OUTPUT);
  pinMode(TCS_S3, OUTPUT);
  pinMode(TCS_OUT, INPUT);
  digitalWrite(TCS_S0, HIGH);
  digitalWrite(TCS_S1, LOW);
}

int get_red_color()
{
  digitalWrite(TCS_S2, LOW);
  digitalWrite(TCS_S3, LOW);
  return pulseIn(TCS_OUT, digitalRead(TCS_OUT) == HIGH ? LOW : HIGH);
}

int get_green_color()
{
  digitalWrite(TCS_S2, LOW);
  digitalWrite(TCS_S3, HIGH);
  return pulseIn(TCS_OUT, digitalRead(TCS_OUT) == HIGH ? LOW : HIGH);
}

int get_blue_color()
{
  digitalWrite(TCS_S2, HIGH);
  digitalWrite(TCS_S3, LOW);
  return pulseIn(TCS_OUT, digitalRead(TCS_OUT) == HIGH ? LOW : HIGH);
}

/**
   @brief Teste de um simples menu de configurações
*/
void configure()
{
  #ifdef DISPLAY_ON
  int option = 0;
  while (option != 2)
  {
    switch (option)
    {
      case 0:
        debug_msg(Serial.println("- Configurar offset do sensor ultrassonico"));
        lcd.clear();
        lcd.print("Configuracoes");
        lcd.setCursor(0, 2);
        lcd.print("Offset HCR04");
        if (!digitalRead(menu_button))
        {
          buzzer_delay(100);
          lcd.setCursor(0, 2);
          lcd.print("Calibrando ");
          for(int i=0;i<5;i++)
          {
            lcd.print(".");
            get_distance();   // Por alguma razão as primeiras medidas variam muito, então, consideramos após a quinta leitura
            delay(100);
          }
          // ajusta o offset
          lcd.clear();
          lcd.print("Offset");
          lcd.setCursor(0, 2);
          lcd.print(get_distance());
          debug_msg(Serial.print("Offset: "));
          debug_msg(Serial.println(get_distance()));
          delay(500);
          option = 1;
        }
        break;
      case 1:
        lcd.clear();
        lcd.print("Pressione para");
        lcd.setCursor(0, 2);
        lcd.print("sair");
        if (!digitalRead(menu_button))
        {
          option = 2; // Sai do menu
        }
        break;
    }
  }
  #else
  debug_msg(Serial.println("Ative o display para poder visualizar as configuracoes"));
  #endif
}

void buzzer_delay(uint16_t t)
{
  digitalWrite(BUZZER_PIN, 1);
  delay(t);
  digitalWrite(BUZZER_PIN, 0);
}
