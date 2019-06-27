#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <wiringPi.h> 
#include "config.h" 
#include "control.h"

#ifdef LED_ON
#pragma message "LED ON!"
#else
#pragma message "LED OFF!"
#endif // LED_ON

#ifdef TEMPERATURE_ON
#pragma message "TEMPERATURE... ON"
#include "mlx90614.h"
#else
#pragma message "TEMPERATURE... OFF"
#endif // TEMPERATURE_ON

#ifdef ULTRASSONIC_ON
#pragma message "ULTRASSONIC... ON!"
#else
#pragma message "ULTRASSONIC... OFF!"
#endif // ULTRASSONIC_OFF
	
#ifdef COLOR_ON
#pragma message "COLOR... ON!"
#include "tcs3200.h"
#else
#pragma message "COLOR... OFF!"
#endif // COLOR_ON

#ifdef DISPLAY_ON
#pragma message "DISPLAY... ON!"
#include "display.h"
#else
#pragma message "DISPLAY... OFF!"
#endif

#ifdef OCR_ON
#pragma message "OCR... ON!"
#else
#pragma message "OCR... OFF!"
#endif // OCR_ON