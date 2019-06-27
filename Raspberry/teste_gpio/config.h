/**
 * Projeto Integrador 2 - 2019/1
 * Configurações gerais do projeto
 */ 

//====================================
//======= ATIVAÇÃO DOS MÓDULOS =======
//====================================
#define LED_ON
//#define BUZZER_ON
#define DISPLAY_ON
#define TEMPERATURE_ON
#define ULTRASSONIC_ON
#define COLOR_ON
//#define OCR_ON

#define FILENAME                "log.csv"   // Nome do arquivo de log
#define DEBUG_ON						    // Habilita o envio de mensagens no console
//#define TEST_MODE						    // Habilitando este modo, as outras operações não serão executadas
#define OFFSET_DISTANCE_VALUE	43		    // Distância medida pelo sensor com a garrafa vazia
#define TIME_DELAY				500		    // Tempo em ms para execução do processo apos detecção do sensor

//=====================================
//======== LIMITES DE VALORES =========
//=====================================
// VOLUME
#define MIN_VOLUME_VALUE		900	    
#define MAX_VOLUME_VALUE        1700      
// TEMPERATURA  
#define MAX_OBJ_TEMPERATURE     35         
#define MAX_AMB_TEMPERATURE     35
// COR


//======== DEFINIÇÃO DOS PINOS ========
//						   wPi	Físico
#define LED_PIN				6	// 22
#define BUZZER_PIN			7	// 7

#define IR_0				5	// 18
#define IR_1				4	// 16
#define IR_2				1	// 12
#define IR_3				16	// 10

#define ECHO_PIN			10  // 24
#define TRIGGER_PIN			11  // 26

#define TCS_S2				12	// 19
#define TCS_S3				13	// 21
#define TCS_OUT				14	// 23

//====================================
//========== ENDEREÇOS I2C ===========
//====================================
#define LCD_I2CADDR			0x27
#define MLX_I2CADDR			0x5b
