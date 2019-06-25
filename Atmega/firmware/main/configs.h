/*
 * PI 2 - 2019/1
 * Configurações gerais do sistema
 */

//========== ATIVAÇÃO DOS MÓDULOS ============
#define USART_ON
//#define ULTRASSONIC_ON
//#define COLOR_ON
//#define TEMPERATURE_ON
//#define DISPLAY_ON
//#define OCR_ON        // FALTA IMPLEMENTAR ESTE MÓDULO
//#define WATCHDOG_ON   // AVALIAR NECESSIDADE DO WATCHDOG

//=========== MODOS DE OPERAÇÃO ==============
//#define TEST_MODE
//#define DEBUG_ON

//============= DEFINIÇÕES ===================
#define USART_BAUD      9600
#define LCD_ADDR        0x27
//#define MLX_ADDR

//=== CONFIGURAÇÕES DO SENSOR ULTRASSONICO ===
#define TRIGGER_PIN     9	// PB1
#define ECHO_PIN        8	// PB0
#define OFFSET          0     // Talvez passar isso para uma função

//===== CONFIGURAÇÕES DO SENSOR DE COR =======
#define TCS_S0          2	// PD2
#define TCS_S1          3	// PD3
#define TCS_S2          4	// PD4
#define TCS_S3          5	// PD5
#define TCS_OUT         6	// PD6

//=== CONFIGURAÇÕES DOS SENSORES DE POSIÇÃO ==
#define IR_0            A0	// PC0
#define IR_1            A1	// PC1
#define IR_2            A2	// PC2
#define IR_3            A3	// PC3

#define menu_button     7
#define BUZZER_PIN      12

//================================================
//==== CONFIGURAÇÕES DE LIMITES DE PARÂMETROS ====
//================================================





/* controles do sistema, não é necessário alterar estas opções*/
#ifdef DEBUG_ON
#ifndef USART_ON
#define USART_ON
#endif
#define debug_msg(c)    c
#else
#define debug_msg(c)
#endif
