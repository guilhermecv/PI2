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
int pulsein(int PIN)
{
	while(digitalRead(PIN) == LOW);
	long start = micros();
	while(digitalRead(PIN) == HIGH);
	long end = micros() - start;
	return end;
}

int pulseIn(int pin, int level, int timeout)
{
   struct timeval tn, t0, t1;

   long micros;

   gettimeofday(&t0, NULL);

   micros = 0;

   while (digitalRead(pin) != level)
   {
      gettimeofday(&tn, NULL);

      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros += (tn.tv_usec - t0.tv_usec);

      if (micros > timeout) return 0;
   }

   gettimeofday(&t1, NULL);

   while (digitalRead(pin) == level)
   {
      gettimeofday(&tn, NULL);

      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros = micros + (tn.tv_usec - t0.tv_usec);

      if (micros > timeout) return 0;
   }

   if (tn.tv_sec > t1.tv_sec) micros = 1000000L; else micros = 0;
   micros = micros + (tn.tv_usec - t1.tv_usec);

   return micros;
}

int get_red_color()
{
    tcs_set_red_filter();
    return pulseIn(TCS_OUT, 1, 1000);
}

int get_green_color()
{
    tcs_set_green_filter();
    return pulseIn(TCS_OUT, 1, 1000);
}

int get_blue_color()
{
    tcs_set_blue_filter();
    return pulseIn(TCS_OUT, 1, 1000);
}