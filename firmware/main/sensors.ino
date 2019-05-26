/**
   Controle dos sensores
*/
#include "configs.h"
#include "sensors.h"
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

/*
 * @brief Inicialização dos módulos
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
    debug_msg(Serial.print("FAIL!\n"));
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
#endif

#else
  debug_msg(Serial.print("LCD... OFF!\n"));
#endif

#ifdef TEMPERATURE_ON
  debug_msg(Serial.print("Temperature..."));
  mlx.begin();
  debug_msg(Serial.print(" ON!\n"));
#else
  debug_msg(Serial.print("Temperature... OFF!\n"));
#endif

#ifdef COLOR_ON
  debug_msg(Serial.print("Color... ON\n"));
  tcs_init();
#else
  debug_msg(Serial.print("Color... OFF\n"));
#endif
}


/**
 * @brief Teste dos sensores conectados ao sistema
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
  int backlight_clk_div;
  if(backlight_clk_div++ > 10)
  {
    backlight_clk_div = 0;
    lcd.setBacklight(0);
  }
  lcd.clear();
  lcd.print("PI 2 - 2019/1");
  lcd.setCursor(0,1);
  lcd.print("Em espera");
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

/*
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

/*
 * @brief Inicia o sensor de cor com 20% da frequência nominal
 */
void tcs_init()
{
  #ifdef COLOR_ON
  pinMode(TCS_S0, OUTPUT);  
  pinMode(TCS_S1, OUTPUT);  
  pinMode(TCS_S2, OUTPUT);  
  pinMode(TCS_S3, OUTPUT);  
  pinMode(TCS_OUT, INPUT);
  digitalWrite(TCS_S0, HIGH);  
  digitalWrite(TCS_S1, LOW);
  #endif  
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

