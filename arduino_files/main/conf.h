// ATIVACAO DOS MODULOS
#define USART_ON
#define WATCHDOG_ON
#define MACHINE_ON
#define LED_ON

// VERBOSE
#define VERBOSE_ON_INIT
#define VERBOSE_ON_ERROR
#define VERBOSE_ON_MACHINE


// CONFIGURACOES DE I/O
#define ULTRASSONIC_TRIGGER
#define ULTRASSONIC_ECHO

#define LED_PORT		PORTB
#define LED_DDR		DDRB
#define LED			PB5




//###################################################
#ifdef VERBOSE_ON_INIT
#define VERBOSE_MSG_INIT(x)	x
#else
#define VERBOSE_MSG_INIT(x)
#endif

#ifdef VERBOSE_ON_ERROR
#define VERBOSE_MSG_ERROR(x)	x
#else
#define VERBOSE_MSG_ERROR(x)
#endif

#ifdef VERBOSE_ON_MACHINE
#define VERBOSE_MSG_MACHINE(x)	x
#else
#define VERBOSE_MSG_MACHINE(x)
#endif

#ifdef LED_ON
#define cpl_led()	LED_PORT ^= (1 << LED)
#else
#define cpl_led()
#endif

#ifdef BUZZER_ON
#define cpl_buzzer()
#else
#define cpl_buzzer()
#endif
