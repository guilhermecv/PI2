#include "control.h" 
#include "defs.h"

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

#ifdef WATCHDOG_ON
#include <avr/wdt.h>
#endif

float distance;
long microsec;
int8_t led_clk_div;
int8_t backlight_clk_div;
int8_t clk;
uint8_t clk_div = 0;
uint8_t machine_state;
int8_t count = 0;

float object_temp;

void init_i2c_display();
void init_ultrasonic_sensor();
void init_color_sensor();
void init_temperature_sensor();
void system_init();
void set_state_iddle();
void set_state_running();
void set_state_error();
void reset();
void system_run();

void process();
void get_color();
void get_distance();
void get_temperature();
void check_ir_sensors();

struct error
{
    uint8_t lcd_i2c     = 0;
    uint8_t ultrasonic  = 0;
    uint8_t temperature = 0;
    uint8_t color       = 0;
    uint8_t ocr         = 1;
    uint8_t critical    = 0;
}error;

struct color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}color;

enum states
{
    IDDLE,
    RUNNING,
    ERROR,
}states;
