/**
 * @file IR_Interface.c
 * @brief Source file for the IR sensor interface.
 *
 * This file contains the implementations of the functions declared in IR_Interface.h.

 */

/**
 * @headerfile "STD_TYPES.h"
 * @brief This header file contains the standard data types.
 */
#include "STD_TYPES.h"

/**
 * @headerfile "BIT_MATH.h"
 * @brief This header file contains the bit manipulation macros.
 */
#include "BIT_MATH.h"

/**
 * @headerfile "MCAL_GPIO_Interface.h"
 * @brief This header file contains the interface for GPIO operations.
 */
#include "MCAL_GPIO_Interface.h"


#include"RCC_Interface.h"
/**
 * @headerfile "IR_Config.h"
 * @brief This header file contains the configuration settings for the IR sensor.
 */
#include "IR_Config.h"

/**
 * @headerfile "IR_Interface.h"
 * @brief This header file contains the interface for the IR sensor.
 */
#include "IR_Interface.h"

/**
 * @brief Initializes the IR sensors.
 *
 * This function initializes the IR sensors by setting their GPIO pin modes.
 */
uint8_t IR1=0;
uint8_t IR2=0;
void IR_Init(void) {
	/*Enable RCC*/
	RCC_AHB1EnableCLK(GPIOBEN);

	/*Init IR GPIO PINS*/

	/*IR_R at PortB PIN0*/
	const GPIO_PinConfig_t PB0_pin =
	{
			.Port=PORTB,
			.PinNum=PIN0,
			.Mode=INPUT,
			.OutputType=PUSH_PULL,
			.PullType=PULL_DOWN,
			.Speed=LOW_SPEED
	};
	GPIO_u8PinInit(&PB0_pin);

	/*IR_L at PortB PIN1*/
	const GPIO_PinConfig_t PB1_pin =
	{
			.Port=PORTB,
			.PinNum=PIN1,
			.Mode=INPUT,
			.OutputType=PUSH_PULL,
			.PullType=PULL_DOWN,
			.Speed=LOW_SPEED
	};
	GPIO_u8PinInit(&PB1_pin);
}



/**
 * @brief Reads the value of the right IR sensor.
 *
 * @return The value of the right IR sensor (either HIGH or LOW).
 * The reading must be on global var IR1 --> will be used in service Layer
 * using extern Keyword.
 */
void IR_u8Read_RightIR(void) {
	//return MCL_GPIO_u8GetPinVal(IR_PORT, IR_RIGHT); // Return the value of the right IR sensor
	 GPIO_u8ReadPinValue(IR_PORT,IR_RIGHT,&IR1);
}

/**
 * @brief Reads the value of the left IR sensor.
 *
 * @return The value of the left IR sensor (either HIGH or LOW).
 * The reading must be on global var IR2 --> will be used in service Layer
 * using extern Keyword.
 */
void IR_u8Read_LeftIR(void) {
	 GPIO_u8ReadPinValue(IR_PORT,IR_LEFT,&IR2);
}

