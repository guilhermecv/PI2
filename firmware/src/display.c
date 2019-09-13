/**
 * @file display.c
 */

#include "display.h"

#ifdef DISPLAY_ON
/**
 * @brief Initializes display
 */
void display_init()
{
  SSD1306_Init();

  display_test();
}


void display_test(void)
{
  LCD_Fill(1);
  LCD_UpdateScreen();
  LCD_Fill(0);
  LCD_Font(34, 38, "PI 2", big_font, 2, 1);
  LCD_Font(18, 60, "2019/1", big_font, 2, 1);
  LCD_UpdateScreen();
}

/**
 * @brief sends a char array
 * The strings are limited in 255 chars and MUST terminate with '\0'.
 */
void display_send_string(char *s, uint8_t x, uint8_t y)
{
    LCD_Font(x, y, s, normal_font, 2, 1);
}

/**
 * @brief exibe um resumo do sistema
 */
void display_status(uint8_t *control)
{

}

#endif /* DISPLAY_ON */
