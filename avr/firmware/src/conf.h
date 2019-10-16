/**
 * @file conf.h
 */

//>> ATIVACAO DOS MODULOS
#define LED_ON
#define USART_ON
// #define BUZZER_ON
// #define DISPLAY_ON
// #define MACHINE_ON
// #define ULTRASSONIC_ON
// #define TEMPERATURE_ON
// #define COLOR_ON
// #define BARCODE_ON


//>> VERBOSE
#define VERBOSE_ON
#define VERBOSE_ON_INIT
#define VERBOSE_ON_ERROR
#define VERBOSE_ON_MACHINE


//############ CONFIGURACOES DE I/O ###############
#define LED_PORT      PORTB
#define LED_DDR       DDRB
#define LED           PB5

#define BUZZER_PORT   PORTB
#define BUZZER_DDR    DDRB
#define BUZZER        PB4

#define HC_PORT       PORTB
#define HC_DDR        DDRB
#define HC_TRIGGER    PB1
#define HC_ECHO       PB0

#define TCS_PORT      PORTC
#define TCS_DDR       DDRC
#define TCS_S0        PC0
#define TCS_S1        PC1
#define TCS_S2        PC2
#define TCS_S3        PC3
#define TCS_OUT       PC4
//#################################################





#ifdef LED_ON
#define cpl_led()     LED_PORT ^= (1 << LED)
#define set_led()     LED_PORT |= (1 << LED)
#define clr_led()     LED_PORT &=~(1 << LED)
#else
#define cpl_led()
#define set_led()
#define clr_led()
#endif

#ifdef BUZZER_ON
#define cpl_buzzer()  BUZZER_PORT ^= (1 << BUZZER)
#define set_buzzer()  BUZZER_PORT |= (1 << BUZZER)
#define clr_buzzer()
#else
#define cpl_buzzer()
#define set_buzzer()
#define clr_buzzer()
#endif
