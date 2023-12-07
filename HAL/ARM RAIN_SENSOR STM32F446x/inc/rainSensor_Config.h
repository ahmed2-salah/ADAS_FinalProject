#ifndef _RAINSENSOR_CONFIG_H_
#define _RAINSENSOR_CONFIG_H_

#include "GPIO_Interface.h"
#include "RCC_Private.h"

#define RAIN_STATUS_PIN 		PIN0
#define RAIN_STATUS_GPIO 		PORTA
#define RAIN_STATUS_MODE 		INPUT
#define RAIN_STATUS_SPEED 		HIGH_SPEED
#define RAIN_STATUS_OutputType 	PUSH_PULL
#define RAIN_STATUS_PULLTYPE 	PULL_DOWN
#define RAIN_STATUS_AF			AF0
#define RAIN_PORT_EN			GPIOAEN
#endif
