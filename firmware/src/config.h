/**
 * @file config.h
 *
 *
 */

/*>> ATIVAÇÃO DOS MODULOS */
#define USART_ON
#define WATCHDOG_ON
// #define MACHINE_ON
// #define BUZZER_ON
#define LED_ON
#define DISPLAY_ON

/*>>  VERBOSE */
#define DEBUG_ON
#define VERBOSE_ON
#define VERBOSE_ON_INIT
#define VERBOSE_ON_ERROR
//#define VERBOSE_ON_MACHINE

/*>> CONFIGURACOES DO DISPLAY */
#define DISPLAY_IDLE_CLK_DIV    100


/*>> I/Os */
#define LED_PORT                PORTB
#define LED_DDR                 DDRB
#define LED                     PB5



#ifdef LED_ON
#define cpl_led()               cpl_bit(LED_PORT, LED);
#define set_led()               set_bit(LED_PORT, LED);
#define clr_led()               clr_bit(LED_PORT, LED);
#else
#define cpl_led()
#define set_led()
#define clr_led()
#endif /* LED_ON */

#ifdef BUZZER_ON
#define cpl_buzzer()
#define set_buzzer()
#define clr_buzzer()
#else
#define cpl_buzzer()
#define set_buzzer()
#define clr_buzzer()
#endif /* BUZZER_ON */
