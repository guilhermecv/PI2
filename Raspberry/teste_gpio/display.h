#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include "config.h"

#ifndef LCD_I2CADDR
#define LCD_I2CADDR 0x27
#endif

// Define some device constants
#define LCD_CHR  1 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command

#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line

int LCD_BACKLIGHT;
//#define LCD_BACKLIGHT   0x08  // On
// LCD_BACKLIGHT = 0x00  # Off
// LCD_BACKLIGHT = 0x08  # On

#define ENABLE  0b00000100 // Enable bit

int fd;  // seen by all subroutines

void lcd_init();
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

// Modificadas
void display_string(const char *s);
void display_char(char s);
void display_int(int i);
void display_float(float i);
void display_clear();
void display_set_line(int line);

// Interação com o usuário
void display_idle_message();
void display_volume(float vol);
void display_temperature(float temp);
void display_color();
void display_update_status(int t, int p, int r);

// Controle do backlight
void display_backlight_off();
void display_backlight_on();
