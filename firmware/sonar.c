//================================================================================ //
// Programa para teste do módulo Sonar HC-SR04 //
//================================================================================ //
#include "sonar.h"

unsigned int Inicio_Sinal, Distancia;
	prog_char mensagem1[] = "Distanc = cm\0";
	prog_char mensagem2[] = "xxx\0";
//------------------------------------------------------------------------------------
	ISR(TIMER1_CAPT_vect) //interrupção por captura do valor do TCNT1
	{
		cpl_bit(TCCR1B,ICES1); //troca a borda de captura do sinal
		if(!tst_bit(TCCR1B,ICES1))//lê o valor de contagem do TC1 na borda de subida do sinal
			Inicio_Sinal = ICR1;//salva a primeira contagem para determinar a largura do pulso
		else //lê o valor de contagem do TC1 na borda de descida do sinal
			Distancia = (ICR1 - Inicio_Sinal)/58;/*agora ICR1 tem o valor do TC1 na borda de
 descida do sinal, então calcula a distância */
	}
uint16_t ultrassonico()
{
 DDRD = 0xFF;
 DDRB = 0b00000010;//somente pino de disparo como saída (PB1), captura no PB0 (ICP1)
 PORTB = 0b11111101;
 TCCR1B = (1<<ICES1)|(1<<CS11); //TC1 com prescaler = 8, captura na borda de subida
 TIMSK1 = 1<<ICIE1; //habilita a interrupção por captura
 sei(); //habilita a chave de interrupções globais
return Distancia;
}


	//=
