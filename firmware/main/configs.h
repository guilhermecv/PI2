/*
  Configurações gerais do sistema
*/
//========== ATIVAÇÃO DOS MÓDULOS ============
#define USART_ON
#define ULTRASSONIC_ON
//#define COLOR_ON
//#define TEMPERATURE_ON
//#define DISPLAY_ON
//#define OCR_ON

//========= MODO DE OPERAÇÃO =================
#define TEST_MODE
#define DEBUG_ON
#define USART_BAUD      9600

//=== CONFIGURAÇÕES DO SENSOR ULTRASSONICO ===
#define TRIGGER_PIN     9
#define ECHO_PIN        8
#define OFFSET          0     // Talvez passar isso para uma função




/* controles do sistema, não é necessário alterar estas opções*/
#ifdef DEBUG_ON
#ifndef USART_ON
#define USART_ON
#endif
#define debug_msg(c)    c
#else
#define debug_msg(c)
#endif
