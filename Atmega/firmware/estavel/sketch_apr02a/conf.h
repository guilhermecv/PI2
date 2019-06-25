/**
 * PI 2 - 2019/1
 * Configurações gerais do sistema
 **/

//======= ATIVAÇÃO DOS MÓDULOS =========
#define LCD_ON
#define ULTRASONIC_ON
#define COLOR_ON
//#define TEMPERATURE_ON
#define BUZZER_ON

//========== CONFIGURAÇÕES =============
#define LCD_i2c_address     0x27
#define USART_BAUD          9600
#define CLK_DIV_VALUE       10

//======= DEFINIÇÃO DOS PINOS ==========
/* Ultrassonico */
#define TRIGGER_PIN         10
#define ECHO_PIN            11
/* Sensor de Cor */
#define OUT_TSC230          9
#define TSC_s0              8
#define TSC_s1              7
#define TSC_s2              6
#define TSC_s3              5
/* Sensores de posição */
#define IR_0
#define IR_1
#define IR_2
#define IR_3
#define BUZZER_PIN          4

#define cpl_led()           PORTB^=(1<<PB5)

#ifdef BUZZER_ON
#define set_buzzer()        digitalWrite(BUZZER_PIN,1);
#define clr_buzzer()        digitalWrite(BUZZER_PIN,0);
#else
#define set_buzzer()
#define clr_buzzer()
#endif