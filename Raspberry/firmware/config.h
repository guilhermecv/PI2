/**
 * Projeto Integrador 2 - 2019/1
 * Configurações gerais do projeto
 */

//====================================
//======= ATIVAÇÃO DOS MÓDULOS =======
//====================================
#define LED_ON
#define DISPLAY_ON
#define TEMPERATURE_ON
#define ULTRASSONIC_ON
#define COLOR_ON
#define OCR_ON
// #define BARCODE_ON


#define FILENAME                "log.csv"   // Nome do arquivo de log
#define DEBUG_ON						    // Habilita o envio de mensagens no console
#define TEST_MODE						    // Habilitando este modo, as outras operações não serão executadas
#define OFFSET_DISTANCE_VALUE	  43		    // Distância medida pelo sensor com a garrafa vazia
#define DELAY					          5

// Configurações do Buzzer
#define BUZZER_ON
//#define BUZZER_SIGNAL_ON					// Bips regulares se tudo estiver OK
#define BUZZER_IR_ON						// Bips quando algum sensor for acionado
#defien BUZZER_ON_PROCESS_DELAY

//=====================================
//======== LIMITES DE VALORES =========
//=====================================
//>> VOLUME
#define MIN_VOLUME_VALUE		900
#define MAX_VOLUME_VALUE        1700
//>> TEMPERATURA
#define MAX_OBJ_TEMPERATURE     30
#define MAX_AMB_TEMPERATURE     30
//>> COR
/*
#define MAX_RED_VALUE
#define MAX_GREEN_VALUE
#define MAX_BLUE_VALUE
*/


//======== DEFINIÇÃO DOS PINOS ========
//						   wPi	Físico
#define LED_PIN				11	// 11
#define BUZZER_PIN			7	// 7

#define IR_0				1	// 18
#define IR_1				5	// 16
#define IR_2				4	// 12
#define IR_3				16	// 10

#define ECHO_PIN			6  // 24
#define TRIGGER_PIN			10  // 26

#define TCS_S2				12	// 19
#define TCS_S3				13	// 21
#define TCS_OUT				14	// 23

//====================================
//========== ENDEREÇOS I2C ===========
//====================================
#define LCD_I2CADDR			0x27
#define MLX_I2CADDR			0x5b
