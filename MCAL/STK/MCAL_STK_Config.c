#include "../inc/STM32F4xx_Device_Header.h"
#include "../inc/MCAL_STK_Interface.h"

STK_CfgType STK_G_Config = {
		.SysTick_ClkSrc = AHB_8_DIVIDE,
		.SysTick_Exception = DISABLE_EXCEPTION,
};
