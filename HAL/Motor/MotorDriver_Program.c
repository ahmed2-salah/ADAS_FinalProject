/**
 * @file MotorDriver.c
 * @brief Source file for the motor driver.
 *
 * This file contains the implementation of the motor driver functions.
 */

/**
 * @headerfile STD_TYPES.h
 * @brief Header file that contains the standard data types.
 */
#include "STD_TYPES.h"

/**
 * @headerfile BIT_MATH.h
 * @brief Header file that contains bit manipulation macros.
 */
#include "BIT_MATH.h"

/**
 * @headerfile MCAL_GPIO_Interface.h
 * @brief Header file that contains the interface for GPIO operations.
 */
#include "MCAL_GPIO_Interface.h"

/**
 * @headerfile MCAL_TIM_Interface.h
 * @brief Header file that contains the interface for timer operations.
 */
#include "MCAL_TIM_Interface.h"

/**
 * @headerfile MotorDriver_Interface.h
 * @brief Header file that contains the interface for the motor driver.
 */
#include "MotorDriver_Interface.h"

/**
 * @headerfile MotorDriver_Private.h
 * @brief Header file that contains private definitions for the motor driver.
 */
#include "MotorDriver_Private.h"

/**
 * @headerfile MotorDriver_Config.h
 * @brief Header file that contains the configuration for the motor driver.
 */

#include "MotorDriver_Config.h"

void MotorDriver_voidInit(void) {
	/*configure GPIO srtuct -> motor driver in1 in2 in3 in4 */
	
	/*in1 at PortA PIN1*/
	const GPIO_PinConfig_t PA1_pin =
	{
			.Port=PORTA,
			.PinNum=PIN1,
			.Mode=OUTPUT,
			.OutputType=PUSH_PULL,
			.PullType=NO_PULL,
			.Speed=LOW_SPEED
	};
	GPIO_u8PinInit(&PA1_pin);
	
	/*in2 at PortA PIN4*/
	const GPIO_PinConfig_t PA4_pin =
	{
			.Port=PORTA,
			.PinNum=PIN4,
			.Mode=OUTPUT,
			.OutputType=PUSH_PULL,
			.PullType=NO_PULL,
			.Speed=LOW_SPEED
	};
	GPIO_u8PinInit(&PA4_pin);
	
	/*in3 at PortC PIN0*/
	const GPIO_PinConfig_t PC0_pin =
	{
			.Port=PORTC,
			.PinNum=PIN0,
			.Mode=OUTPUT,
			.OutputType=PUSH_PULL,
			.PullType=NO_PULL,
			.Speed=LOW_SPEED
	};
	GPIO_u8PinInit(&PC0_pin);
    
	/*in3 at PortC PIN1*/
	const GPIO_PinConfig_t PC1_pin =
	{
			.Port=PORTC,
			.PinNum=PIN1,
			.Mode=OUTPUT,
			.OutputType=PUSH_PULL,
			.PullType=NO_PULL,
			.Speed=LOW_SPEED
	};
	GPIO_u8PinInit(&PC1_pin);
	
}
/*End of MotorDriver_voidInit function */



/**
 * @brief Moves the motors forward.
 *
 * This function moves the motors forward.
 * HIGH on IN1 LOW on IN2
 */
void MotorDriver_voidMoveForward(Cp_DutyCycle) {
	/*Forward Direction*/  
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN1, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN2, PIN_LOW);
	
	/*Speed for forward/Backword*/
	TIM_PWM_SetDutyCycle(&PWM_htim31, Cp_DutyCycle);
	
}/*End of MotorDriver_voidMoveForward function */


/**
 * @brief Moves the motors backward.
 *
 * This function moves the motors backward.
 * HIGH on IN2 LOW on IN2
 */
void MotorDriver_voidMoveBackward(Cp_DutyCycle) {
	/*Backword Direction*/ 
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN1, PIN_LOW);
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN2, PIN_HIGH);
	
	/*Speed for forward/Backword*/
	TIM_PWM_SetDutyCycle(&PWM_htim31, Cp_DutyCycle);
	
	
}/*End of MotorDriver_voidMoveBackward function */


/**
 * @brief Turns the motors right.
 *
 * This function turns the motors right.
 * Turn right (Move forward + Steering right)
 *
 */
void MotorDriver_voidMoveRight(Cp_DutyCycle1,Cp_DutyCycle2) {
	
	/*Forward Direction*/
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN1, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN2, PIN_LOW);
	
	/*Right Direction*/
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN3, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN4, PIN_LOW);
	

	/*Speed for forward/Backword*/
	TIM_PWM_SetDutyCycle(&PWM_htim31, Cp_DutyCycle1);
	/*Speed for steering*/
	TIM_PWM_SetDutyCycle(&PWM_htim32, Cp_DutyCycle2);
}/*End of MotorDriver_voidMoveRight function */


/**
 * @brief Turns the motors right.
 *
 * This function turns the motors left.
 * Turn right (Move forward + Steering left)
 */
void MotorDriver_voidMoveLeft(Cp_DutyCycle1,Cp_DutyCycle2) {
	
	/*Forward Direction*/
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN1, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN2, PIN_LOW);
	
	/*Left Direction*/
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN3, PIN_LOW);
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN4, PIN_HIGH);
	
	/*Speed for forward/Backword*/
	TIM_PWM_SetDutyCycle(&PWM_htim31, Cp_DutyCycle1);
	/*Speed for steering*/
	TIM_PWM_SetDutyCycle(&PWM_htim32, Cp_DutyCycle2);
}/*End of MotorDriver_voidMoveLeft function */


/**
 * @brief Stops the motors.
 *
 * This function stops the motors.
 */
void MotorDriver_voidStop(void) {
	GPIO_u8SetPinValue(MOTORDRIVER_PORT        , MOTORDRIVER_IN1, PIN_LOW);
	GPIO_u8SetPinValue(MOTORDRIVER_PORT        , MOTORDRIVER_IN2, PIN_LOW);
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN3, PIN_LOW);
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN4, PIN_LOW);
}/*End of MotorDriver_voidStop function */
