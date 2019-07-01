/*
*
* by Lewis Loflin www.bristolwatch.com lewis@bvu.net
* http://www.bristolwatch.com/rpi/i2clcd.htm
* Using wiringPi by Gordon Henderson
*
*
* Port over lcd_i2c.py to C and added improvements.
* Supports 16x2 and 20x4 screens.
* This was to learn now the I2C lcd displays operate.
* There is no warrenty of any kind use at your own risk.
*
*/
#include "display.h"

void lcd_init()   
{
  display_backlight_on();
  if (wiringPiSetup () == -1) exit (1);
  fd = wiringPiI2CSetup(LCD_I2CADDR);
  // Initialise display
  lcd_byte(0x33, LCD_CMD); // Initialise
  lcd_byte(0x32, LCD_CMD); // Initialise
  lcd_byte(0x06, LCD_CMD); // Cursor move direction
  lcd_byte(0x0C, LCD_CMD); // 0x0F On, Blink Off
  lcd_byte(0x28, LCD_CMD); // Data length, number of lines, font size
  lcd_byte(0x01, LCD_CMD); // Clear display
  delayMicroseconds(500);
}

void display_backlight_on()
{
    LCD_BACKLIGHT = 0x08;
}

void display_backlight_off()
{
    LCD_BACKLIGHT = 0x00;
}
/**
 * @brief float to string
 */
void display_float(float i)
{
  char buffer[20];
  sprintf(buffer, "%4.2f",  i);
  display_string(buffer);
}

/**
 * @brief Int to string
 */
void display_int(int i)   {
  char array1[20];
  sprintf(array1, "%d",  i);
  display_string(array1);
}

/**
 * @brief Limpa o display e retorna para a posição inicials
 */
void display_clear()
{
  lcd_byte(0x01, LCD_CMD);
  lcd_byte(0x02, LCD_CMD);
}

/**
 * @brief posiciona o cursor em uma posição específica
 */
void display_set_line(int line)
{
	lcd_byte(line, LCD_CMD);
}

/**
 * @brief Envia uma string para o display
 */
void display_string(const char *s)
{
  // Incluido para teste
  //fd = wiringPiI2CSetup(LCD_I2CADDR);

	while ( *s ) lcd_byte(*(s++), LCD_CHR);
}

/**
 * @brief Escreve um caracter no display
 */
void display_char(char val)
{
	lcd_byte(val, LCD_CHR);
}

/**
 * @brief
 */
void display_idle_message()
{
	display_set_line(LINE1);
	display_string("PI 2 - 2019/1    ");
	display_set_line(LINE2);
	display_string("Em espera...    ");
}

void display_load_message()
{
  display_set_line(LINE1);
	display_string("PI 2 - 2019/1    ");
	display_set_line(LINE2);
	display_string("Buscando log... ");
  delay(1000);
}

void display_volume(float vol)
{
  display_set_line(LINE1);
	display_string("Volume      ");
	display_set_line(LINE2);
	display_float(vol);
	display_string(" ml     ");
}

void display_temperature(float temp)
{
  lcd_init();
  display_set_line(LINE1);
	display_string("Temperatura    ");
	display_set_line(LINE2);
	display_float(temp);
	display_string(" *C         ");
}

void display_color()
{
  display_clear();
  display_string("Conferindo cor");
}

void display_update_status(int t, int p, int r)
{
  display_set_line(LINE1);
  display_string("PI 2 - Status    ");
  display_set_line(LINE2);
  display_char('T');
  display_char(':');
  display_int(t);
  display_char(' ');
  display_char('P');
  display_char(':');
  display_int(p);
  display_char(' ');
  display_char('R');
  display_char(':');
  display_int(r);
}

void lcd_byte(int bits, int mode)   
{
  //Send byte to data pins
  // bits = the data
  // mode = 1 for data, 0 for command
  int bits_high;
  int bits_low;
  // uses the two half byte writes to LCD
  bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
  bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

  // High bits
  wiringPiI2CReadReg8(fd, bits_high);
  lcd_toggle_enable(bits_high);

  // Low bits
  wiringPiI2CReadReg8(fd, bits_low);
  lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int bits)   {
  // Toggle enable pin on LCD display
  // Valor original do delay 500us
  delayMicroseconds(100); 
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(100);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(100);
}
