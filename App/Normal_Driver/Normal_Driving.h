#include <stdint.h>
#include "math.h"
#include "ErrTypes.h"
#include "STM32F446xx.h"
#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "SCB_Interface.h"
#include "NVIC_Interface.h"
#include "UART_Interface.h"
#include "Bluetooth_interface.h"
#include "MotorDriver_Interface.h"     //Motor driver including

/***********_Function Prototype_*****************/

//This API used to init all module in which Normal_Driving depend on 
void Normal_Driving_init(void);
//This API used to control the movement of car depend on the value received from mobile application
void Normal_Driving_Alogrithm(void);