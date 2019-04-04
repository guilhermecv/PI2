/**
   PI 2 - 2019/1 - IFSC Eng Eletrônica
   Autores: Guilherme Camargo e Jessica Ribeiro
 **/

#include "main.h"

//=========INICIALIZAÇÕES DOS MODULOS ========
void init_i2c_display()
{
  Serial.print("Display......");
  Wire.beginTransmission(LCD_i2c_address);
  error.lcd_i2c = Wire.endTransmission();
  if (error.lcd_i2c == 0) //Inicialização OK
  {
    Serial.println(" OK!");
    lcd.begin(16, 2);
    lcd.setBacklight(255);
    lcd.clear();
    lcd.print("PI 2 - 2019/1");
    delay(1200);
    lcd.setCursor(0, 1);
    lcd.print("Autoteste...");
  }
  else          //Erro na inicialização do display
  {
    Serial.println(" FAIL!!!");
  }
}

void init_ultrasonic_sensor()
{
  lcd.setCursor(0, 1);
  lcd.print("Ultrasonic: ");
  Serial.print("Ultrasonic...");
#ifdef ULTRASONIC_ON
  long microsec = ultrasonic.timing();
  distance = ultrasonic.convert(microsec, Ultrasonic::CM);
  if (distance <= 0)
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
  lcd.setCursor(13, 1);
  lcd.print("OFF");
#endif
}

void init_color_sensor()
{
  Serial.print("Color........");
  lcd.clear();
  lcd.print("PI 2 - 2019/1");
  lcd.setCursor(0, 1);
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
  if (error.color)
  {
    Serial.println(" FAIL!");
    lcd.setCursor(12, 1);
    lcd.print("FAIL");
    error.critical = 1;
  }
  else
  {
    Serial.println(" OK!");
    lcd.setCursor(14, 1);
    lcd.print("OK");
  }
#else
  Serial.println(" OFF!");
  lcd.setCursor(13, 1);
  lcd.print("OFF");
#endif

}

void init_temperature_sensor()
{
  Serial.print("Temperature..");
  lcd.clear();
  lcd.print("PI 2 - 2019/1");
  lcd.setCursor(0, 1);
  lcd.print("Temperature ");
#ifdef TEMPERATURE_ON
  mlx.begin();
  if (mlx.readAmbientTempC() > 300)
  {
    error.critical = 1;
    error.temperature = 1;
    Serial.println(" FAIL!");
    lcd.print("FAIL");
  }
  else
  {
    Serial.println(" OK!");
    lcd.setCursor(14, 1);
    lcd.print("OK");
  }
#else
  Serial.println(" OFF!");
  lcd.setCursor(13, 1);
  lcd.print("OFF");
#endif

}

void init_ocr()
{
  Serial.println("OCR..........");
  lcd.clear();
  lcd.print("PI 2 - 2019/1");
  lcd.setCursor(0, 1);
  lcd.print("OCR ");
  // INCLUIR UM TESTE PARA O OCR
  error.ocr = 1;
  if (error.ocr)
  {
    Serial.println(" FAIL!");
    lcd.setCursor(12, 1);
    lcd.print("FAIL");
  }
  else
  {
    Serial.println(" OK!");
    lcd.setCursor(14, 1);
    lcd.print("OK");
  }
}

void system_init()
{
#ifdef WATCHDOG_ON
  wdt_enable(WDTO_8S);  // Habilita o watchdog com um tempo limite de 8 segundos
#else
  Serial.println("Alerta: WATCHDOG DESATIVADO!\n O sistema não será reiniciado em caso de erro\n");
#endif

  DDRB = (1 << PB5);
  Serial.begin(USART_BAUD);
  Wire.begin();
  Serial.println("Iniciando modulos");
  init_i2c_display();
  delay(1000);
#ifdef WATCHDOG_ON
  wdt_reset();
#endif
  init_ultrasonic_sensor();
  delay(1000);
#ifdef WATCHDOG_ON
  wdt_reset();
#endif
  init_color_sensor();
  delay(1000);
#ifdef WATCHDOG_ON
  wdt_reset();
#endif
  init_temperature_sensor();
  delay(1000);
#ifdef WATCHDOG_ON
  wdt_reset();
#endif
  timer_init();
}

//======= CONTROLE DA MÁQUINA DE ESTADOS ======
void set_state_error()
{
  machine_state = ERROR;
}

void set_state_running()
{
  machine_state = RUNNING;
}

void set_state_iddle()
{
  machine_state = IDDLE;
}

void reset()
{
  // TRAVA O SISTEMA FORÇANDO UM RESET DO WATCHDOG
  Serial.println("Aguardando reset...");
  for (;;);
}

//======= CONTROLE DOS PROCESSOS ========
/*
   Retorna a cor do objeto
*/
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

/*
   Verifica a distancia do objeto
*/
void get_distance()
{
#ifdef ULTRASONIC_ON
  long microsec = ultrasonic.timing();
  distance = ultrasonic.convert(microsec, Ultrasonic::CM);
#endif
}

/*
   Verifica a temperatura do líquido
*/
void get_temperature()
{
#ifdef TEMPERATURE_ON
  object_temp = mlx.readObjectTempC();
#endif
}

/*
   Checa os sensores de posição
*/
void check_ir_sensors()
{

}


//====== MÁQUINA DE ESTADOS =======
void system_run()
{
  if (clk)
  {
    clk = 0;
    switch (machine_state)
    {
      case IDDLE:
        if (led_clk_div++ > 30)
        {
          led_clk_div = 0;
          cpl_led();
        }
        break;
      case RUNNING:
        if (led_clk_div++ > 10)
        {
          led_clk_div = 0;
          cpl_led();
        }
        break;

      case ERROR:
        if (led_clk_div++ > 2)
        {
          led_clk_div = 0;
          cpl_led();
        }
#ifdef RESET_ON_ERROR
        reset();
#endif
        break;

      default:
        break;
    }
  }
}

void setup() {
  buzzer_bip();
  delay(1000);
  system_init();

  if (error.critical)
  {
    Serial.println("\nFalhas detectadas na inicialização dos sensores\nSistema não iniciado\nMódulos com erros:");
    if (error.lcd_i2c)     Serial.println(">>LCD 16x02");
    if (error.ultrasonic)  Serial.println(">>HC-SR04");
    if (error.color)       Serial.println(">>TCS 230");
    if (error.temperature) Serial.println(">>MLX90614");
    if (error.ocr)         Serial.println(">>Leitura OCR");
    lcd.clear();
    lcd.print("    FALHA NA    ");
    lcd.setCursor(0, 1);
    lcd.print(" INICIALIZACAO ");
    buzzer_error();
    set_state_error();
  }
  else
  {
#ifdef WATCHDOG_ON
    wdt_reset();
#endif
    Serial.println("\nSistema iniciado corretamente");
    lcd.clear();
    lcd.print("PI 2 - 2019/1");
    lcd.setCursor(0, 1);
    lcd.print("Autoteste OK");
    buzzer_init_ok();
    delay(500);
    set_state_running();
  }
  sei();
}

void loop()
{
#ifdef WATCHDOG_ON
  wdt_reset();
#endif
  system_run();
}

ISR(BADISR_vect)
{
  Serial.println("Fatal error: BAD ISR");
  lcd.clear();
  lcd.print("BAD ISR");
  buzzer_error();
  for (;;);
}

ISR(TIMER2_COMPA_vect)
{
  if (clk_div++ > CLK_DIV_VALUE)
  {
    clk_div = 0;
    if (clk)
    {
      Serial.println("Conflito de clock");
      buzzer_error();
    }
    clk = 1;
  }
}
