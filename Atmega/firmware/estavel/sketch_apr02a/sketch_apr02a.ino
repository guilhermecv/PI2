/**
 * PI 2 - 2019/1
 **/
#include "main.h"

void init_i2c_display()
{
  Serial.print("Display......");
  Wire.beginTransmission(LCD_i2c_address);
  error.lcd_i2c = Wire.endTransmission();
  if(error.lcd_i2c == 0)  //Inicialização OK
  {
    Serial.println(" OK!");
    lcd.begin(16,2);
    lcd.setBacklight(255);
    lcd.clear();
    lcd.print("PI 2 - 2019/1");
    delay(1200);
    lcd.setCursor(0,1);
    lcd.print("Autoteste...");
  }
  else          //Erro na inicialização do display
  {
    Serial.println(" FAIL!!!");
  }
}

void init_ultrasonic_sensor()
{
  lcd.setCursor(0,1);
  lcd.print("Ultrasonic: ");
  Serial.print("Ultrasonic...");
  #ifdef ULTRASONIC_ON
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  if(cmMsec <=0)
  {
    lcd.print("OK");
    Serial.println(" OK!");
  }
  else
  {
    error.ultrasonic = 1;
    error.critical   = 1;
    lcd.print("FAIL");
    Serial.println(" FAIL!");
  }
  #else
    Serial.println(" OFF!");
    lcd.setCursor(13,1);
    lcd.print("OFF");
  #endif
}

void init_color_sensor()
{
  Serial.print("Color........");
  lcd.clear();
  lcd.print("PI 2 - 2019/1");
  lcd.setCursor(0,1);
  lcd.print("Color ");
  #ifdef COLOR_ON
  pinMode(TSC_s0, OUTPUT);
  pinMode(TSC_s1, OUTPUT);
  pinMode(TSC_s2, OUTPUT);
  pinMode(TSC_s3, OUTPUT);
  pinMode(OUT_TSC230, INPUT);
  digitalWrite(TSC_s0, HIGH);
  digitalWrite(TSC_s1, LOW);

  get_color();
  // incluir teste do sensor de cor
  if(error.color)
  {
    Serial.println(" FAIL!");
    lcd.setCursor(12,1);
    lcd.print("FAIL");
    error.critical = 1;
  }
  else
  {
    Serial.println(" OK!");
    lcd.setCursor(14,1);
    lcd.print("OK");
  }
  #else
    Serial.println(" OFF!");
    lcd.setCursor(13,1);
    lcd.print("OFF");
  #endif
  
}

void init_temperature_sensor()
{
  Serial.print("Temperature..");
  lcd.clear();
  lcd.print("PI 2 - 2019/1");
  lcd.setCursor(0,1);
  lcd.print("Temperature ");
  #ifdef TEMPERATURE_ON
    mlx.begin();
    if(mlx.readAmbientTempC() > 300)
    {
      error.critical = 1;
      error.temperature = 1;
      Serial.println(" FAIL!");
      lcd.print("FAIL");
    }
    else
    { 
      Serial.println(" OK!");
      lcd.setCursor(14,1);
      lcd.print("OK");
    }
  #else
    Serial.println(" OFF!");
    lcd.setCursor(13,1);
    lcd.print("OFF");
  #endif
  
}

void system_init()
{
  DDRB = (1<<PB5);
  Serial.begin(USART_BAUD);
  Wire.begin();
  Serial.println("Iniciando modulos");
  init_i2c_display();
  delay(1000);
  init_ultrasonic_sensor();
  delay(1000);
  init_color_sensor();
  delay(1000);
  init_temperature_sensor();
  delay(1000);
  timer_init();
}

void get_color()
{
  digitalWrite(TSC_s2, LOW);
  digitalWrite(TSC_s3, LOW);
  color.red   = pulseIn(OUT_TSC230, digitalRead(OUT_TSC230) == HIGH ? LOW : HIGH);
  digitalWrite(TSC_s3, HIGH);
  color.green = pulseIn(OUT_TSC230, digitalRead(OUT_TSC230) == HIGH ? LOW : HIGH);
  digitalWrite(TSC_s2, HIGH);
  color.blue  = pulseIn(OUT_TSC230, digitalRead(OUT_TSC230) == HIGH ? LOW : HIGH);
}

void setup() {
  buzzer_bip();
  delay(1000);
  system_init();

  if(error.critical)
  {
    Serial.println("\nFalhas detectadas na inicialização dos sensores\nSistema não iniciado\nMódulos com erros:");
    if(error.ultrasonic)  Serial.println(">>HC-SR04");
    if(error.lcd_i2c)     Serial.println(">>LCD 16x02");
    if(error.color)       Serial.println(">>TCS 230");
    if(error.temperature) Serial.println(">>MLX90614");
    lcd.clear();
    lcd.print("    FALHA NA    ");
    lcd.setCursor(0,1);
    lcd.print(" INICIALIZACAO ");
    #ifdef BUZZER_ON
    set_buzzer();
    delay(1000);
    clr_buzzer();
    #endif
    set_state_error();
  }
  else
  {
    Serial.println("\nSistema iniciado corretamente");
    lcd.clear();
    lcd.print("PI 2 - 2019/1");
    lcd.setCursor(0,1);
    lcd.print("Autoteste OK");
    delay(1200);
    set_state_running();
  }
  sei();
}

void loop()
{
  system_run();
}



ISR(BADISR_vect)
{
  Serial.println("Fatal error: BAD ISR");
  lcd.clear();
  lcd.print("BAD ISR");
  for(;;);
}
