#include "mlx90614.h"

/**
 * @brief Inicializa o sensor MLX90614
 */
void mlx_init()
{
	if(wiringPiSetup() == -1) exit(1);
	fd = wiringPiI2CSetup(MLX_I2CADDR);
}

/**
 * @brief Mede a temperatura ambiente
 */
float read_amb_temperature()
{
	return readTemp(MLX90614_TA);
}

/**
 * @brief Mede a temperatura do objeto em frente ao sensor
 */
float read_obj_temperature()
{
	return readTemp(MLX90614_TOBJ1);
}

/**
 * @brief Faz as conversões necessárias
 */
float readTemp(int reg)
{
	float temp;

	temp = read16(reg);
	temp *= .02;
	temp -= 273.15;

	return temp;
}

/**
 * @brief Faz a leitura dos registradores
 */
int read16(int a)
{
	int ret;
	wiringPiI2CWrite(fd, a);		// Envia o endereço do registrador para leitura

	ret = wiringPiI2CRead(fd);		// Recebe os dados
	ret |= wiringPiI2CRead(fd) << 8;	// Recebe os dados

	return ret;
}
