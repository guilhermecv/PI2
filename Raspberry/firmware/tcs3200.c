#include "tcs3200.h"

/**
 * @brief Inicializa os pinos do sensor de cor
 */
void tcs_init()
{
	pinMode(TCS_S2, OUTPUT);
	pinMode(TCS_S3, OUTPUT);
	pinMode(TCS_OUT, INPUT);
}

/**
 * @brief Ativa o filtro para cor vermelha
 */
void tcs_set_red_filter()
{
	digitalWrite(TCS_S2, LOW);
	digitalWrite(TCS_S3, LOW);
}

/**
 * @brief Ativa o filtro para cor verde
 */
void tcs_set_green_filter()
{
	digitalWrite(TCS_S2, HIGH);
	digitalWrite(TCS_S3, HIGH);
}

/**
 * @brief Ativa o filtro para cor azul
 */
void tcs_set_blue_filter()
{
	digitalWrite(TCS_S2, LOW);
	digitalWrite(TCS_S3, HIGH);
}

/**
 * @brief Desativa os filtros de cor
 */
void tcs_set_no_filter()
{
	digitalWrite(TCS_S2, HIGH);
	digitalWrite(TCS_S3, LOW);
}

/**
 * @brief Mede a duração de um pulso
 */
int pulseIn(int PIN)
{
	while(digitalRead(PIN) == LOW);
	long start = micros();
	while(digitalRead(PIN) == HIGH);
	long end = micros() - start;
	return end;
}

int get_red_color()
{
    tcs_set_red_filter();
    return pulseIn(TCS_OUT);
}

int get_green_color()
{
    tcs_set_green_filter();
    return pulseIn(TCS_OUT);
}

int get_blue_color()
{
    tcs_set_blue_filter();
    return pulseIn(TCS_OUT);
}