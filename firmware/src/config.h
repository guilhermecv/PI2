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
// #define LED_ON
// #define DISPLAY_ON

/*>> VERBOSE MESSAGE */
#define VERBODE_ON_INIT
#define VERBODE_ON_ERROR




#ifdef LED_ON
#define cpl_led()
#define set_led()
#define clr_led()
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
