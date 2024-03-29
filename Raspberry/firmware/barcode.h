#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "config.h"

#ifdef DISPLAY_ON
#include "display.h"
#endif

#include "control.h"

#define DEVICE  "/dev/ttyACM0"
#define BAUD    9600
#define MAX     13

int code[MAX];

int fd;

void barcode_init();
void barcode_get_data();
int barcode_check();

#ifdef DEBUG_ON
#define debug_msg(x)	x
#else
#define debug_msg(x)
#endif
