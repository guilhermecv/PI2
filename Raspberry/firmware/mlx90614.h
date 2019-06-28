#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

// Endereços da RAM
#define MLX90614_TA	0x26
#define MLX90614_TOBJ1	0x27



int fd;

void mlx_init();
float read_amb_temperature();
float read_obj_temperature();
float readTemp(int reg);
int read16(int a);
