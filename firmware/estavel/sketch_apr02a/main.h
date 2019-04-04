#include "control.h" 

#ifdef LCD_ON
#include "LiquidCrystal_PCF8574.h"
LiquidCrystal_PCF8574 lcd(LCD_i2c_address);
#endif

#ifdef ULTRASONIC_ON
#include "Ultrasonic.h"
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
#endif

#ifdef TEMPERATURE_ON
#include "Adafruit_MLX90614.h"
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#endif

float cmMsec;
long microsec;

void init_i2c_display();
void init_ultrasonic_sensor();
void init_color_sensor();
void init_temperature_sensor();
void system_init();
void get_color();

struct error
{
    uint8_t lcd_i2c     = 0;
    uint8_t ultrasonic  = 0;
    uint8_t temperature = 0;
    uint8_t color       = 0;
    uint8_t critical    = 0;
}error;

struct color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}color;