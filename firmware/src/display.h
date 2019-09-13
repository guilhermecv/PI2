#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"

#ifdef DISPLAY_ON
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "../lib/DISPLAYS/SSD1306_AVR/ssd1306.h"

// fonts
#include "../lib/DISPLAYS/SSD1306_AVR/fonts/Font_8_Default.h"
#include "../lib/DISPLAYS/SSD1306_AVR/fonts/Font_3_Picopixel.h"
#define normal_font _3_PicoPixel
#define big_font    _8_Default

void display_init(void);
void display_test(void);

void display_send_string(char *s, uint8_t x, uint8_t y);

void display_status(int *control);


#endif /* DISPLAY_ON */
#endif /* DISPLAY_H */
