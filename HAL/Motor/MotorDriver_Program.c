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

/*
 * Connections
 * Motor f/b
 * in1->PA1
 * in2->PA4
 * pwm1 Tim2 ch3 -> PB10
 *
 * Motor steering
 * in3->PC0
 * in4->PC1
 * pwm2 Tim3 ch3 -> PC8
 *
 *Ultrasonic
 *
 * Trigger  PORTB : PIN13
 * ECHO     PORTB : PIN14
 * */
#include "stdint.h"



/**
 * @headerfile MCAL_GPIO_Interface.h
 * @brief Header file that contains the interface for GPIO operations.
 */
#include "MCAL_GPIO_Interface.h"
/**
 * @headerfile RCC_Interface.h
 * @brief Header file that contains the interface for RCC operations.
 */
#include"RCC_Interface.h"


/**
 * @headerfile MCAL_TIM_Interface.h
 * @brief Header file that contains the interface for timer operations.
 */

#include "Timer_interface.h"

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

	/*Enable RCC*/
	RCC_AHB1EnableCLK(GPIOBEN);
	RCC_AHB1EnableCLK(GPIOAEN);
	RCC_AHB1EnableCLK(GPIOCEN);
	RCC_APB1EnableCLK(TIM2EN);
	RCC_APB1EnableCLK(TIM3EN);
	RCC_APB1EnableCLK(TIM4EN);


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
    
	/*in4 at PortC PIN1*/
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
	

	/*Configure PWM PINS*/
	/*TIMER2 CH3 Pin-> PB10*/
	/*TIMER3 CH3 Pin-> PC8*/
	/*TIMER4 CH2 Pin-> PB7*/

	/*Timer 2 PWM Mode channel3  PB10 */
	GPIO_PinConfig_t Timer2PWMCh3PB10 =
	{       .AltFunc=AF1,
			.Mode=ALTERNATE_FUNCTION,
			.Speed=HIGH_SPEED,
			.OutputType=PUSH_PULL,
			.PullType=NO_PULL,
			.Port=PORTB,
			.PinNum=PIN10};
	GPIO_u8PinInit(&Timer2PWMCh3PB10);

	/*Timer 3 PWM Mode channel3  PC8 */
	GPIO_PinConfig_t Timer3PWMCh3PC8 =
	{       .AltFunc=AF2,
			.Mode=ALTERNATE_FUNCTION,
			.Speed=HIGH_SPEED,
			.OutputType=PUSH_PULL,
			.PullType=NO_PULL,
			.Port=PORTC,
			.PinNum=PIN8};
	GPIO_u8PinInit(&Timer3PWMCh3PC8);

	/*Timer 4 PWM Mode channel2  PB7 */
	GPIO_PinConfig_t Timer4PWMCh2PB7 =
	{       .AltFunc=AF2,
			.Mode=ALTERNATE_FUNCTION,
			.Speed=HIGH_SPEED,
			.OutputType=PUSH_PULL,
			.PullType=NO_PULL,
			.Port=PORTB,
			.PinNum=PIN7};
	GPIO_u8PinInit(&Timer4PWMCh2PB7);

}
/*End of MotorDriver_voidInit function */



/**
 * @brief Moves the motors forward.
 *
 * This function moves the motors forward.
 * HIGH on IN1 LOW on IN2
 */
void MotorDriver_voidMoveForward(uint8_t Cp_DutyCycle) {
	/*Forward Direction*/  
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN1, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN2, PIN_LOW);
	

	/*Stop steering*/
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN3, PIN_LOW);
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN4, PIN_LOW);

	/*Speed for forward/Backword*/
	//TimerX_PWM(TIMER_2_,CH3,Cp_DutyCycle);
	TimerX_PWM(TIMER_2_,CH3,Cp_DutyCycle);
	
}/*End of MotorDriver_voidMoveForward function */


/**
 * @brief Moves the motors backward.
 *
 * This function moves the motors backward.
 * HIGH on IN2 LOW on IN2
 */
void MotorDriver_voidMoveBackward(uint8_t Cp_DutyCycle) {
	/*Backword Direction*/ 
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN1, PIN_LOW);
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN2, PIN_HIGH);
	
	/*Speed for forward/Backword*/
	TimerX_PWM(TIMER_2_,CH3,Cp_DutyCycle);
	
	/*Stop steering*/
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN3, PIN_LOW);
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN4, PIN_LOW);

}/*End of MotorDriver_voidMoveBackward function */


/**
 * @brief Turns the motors right.
 *
 * This function turns the motors right.
 * Turn right (Move forward + Steering right)
 *
 */
void MotorDriver_voidMoveRight(uint8_t Cp_DutyCycle1,uint8_t Cp_DutyCycle2) {

	/*Forward Direction*/
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN1, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN2, PIN_LOW);

	/*Right Direction*/
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN3, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN4, PIN_LOW);


	/*Speed for forward/Backword*/
	TimerX_PWM(TIMER_2_,CH3,Cp_DutyCycle1);
	/*Speed for steering*/
	TimerX_PWM(TIMER_3_,CH3,Cp_DutyCycle2);
}/*End of MotorDriver_voidMoveRight function */


/**
 * @brief Turns the motors right.
 *
 * This function turns the motors left.
 * Turn right (Move forward + Steering left)
 */
void MotorDriver_voidMoveLeft(uint8_t Cp_DutyCycle1,uint8_t Cp_DutyCycle2) {

	/*Forward Direction*/
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN1, PIN_HIGH);
	GPIO_u8SetPinValue(MOTORDRIVER_PORT, MOTORDRIVER_IN2, PIN_LOW);

	/*Left Direction*/
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN3, PIN_LOW);
	GPIO_u8SetPinValue(MOTORDRIVER_STERING_PORT, MOTORDRIVER_IN4, PIN_HIGH);

	/*Speed for forward/Backword*/
	TimerX_PWM(TIMER_2_,CH3,Cp_DutyCycle1);
	/*Speed for steering*/
	TimerX_PWM(TIMER_3_,CH3,Cp_DutyCycle2);
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
