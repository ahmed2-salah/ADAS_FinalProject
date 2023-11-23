/*
 ******************************************************************************
 * @file           : GPIO_Interface.h
 * @Author         : Hassan_Elgabas
 * @brief          : Main program body
 * @Date           : May 5, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

/* ======================================================================
 * GPIO Option Enums
 * ====================================================================== */

/* *************
 *  @Port_t
 *
 *
 **/
typedef enum
{
	PORTA = 0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG,
	PORTH
} Port_t;

/* *************
 *  @Pin_t
 *
 *
 **/
typedef enum
{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15
} Pin_t;

/* *************
 *  @Mode_t
 *
 *
 **/
typedef enum
{
	INPUT = 0,
	OUTPUT,
	ALTERNATE_FUNCTION,
	ANALOG
} Mode_t;

/* *************
 *  @OutputSpeed_t
 *
 *
 **/
typedef enum
{
	LOW_SPEED = 0,
	MEDIUM_SPEED,
	FAST_SPEED,
	HIGH_SPEED
} OutputSpeed_t;

/* *************
 *  @OutputType_t
 *
 *
 **/
typedef enum
{
	PUSH_PULL = 0,
	OPEN_DRAIN
} OutputType_t;

/* *************
 *  @PullType_t
 *
 *
 **/
typedef enum
{
	NO_PULL = 0,
	PULL_UP,
	PULL_DOWN
} PullType_t;

/* *************
 *  @AltFunc_t
 *
 *
 **/
typedef enum
{
	AF0 = 0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
} AltFunc_t;

/* *************
 *  @PinValue_t
 *
 *
 **/
typedef enum
{
	PIN_LOW = 0,
	PIN_HIGH
} PinValue_t;

/* ----------------------------------------------------------------------------------------- */
/* ------------------------------- GPIO Pin Config Structure ------------------------------- */
/* ----------------------------------------------------------------------------------------- */

typedef struct
{
	Port_t Port;
	Pin_t PinNum;
	Mode_t Mode;
	OutputSpeed_t Speed;
	OutputType_t OutputType;
	PullType_t PullType;
	AltFunc_t AltFunc;

} GPIO_PinConfig_t;

/* ------------------------------------------------------------------------------------------------ */
/* ------------------------------- FUCTION PROTOTYPES SECTION START ------------------------------- */
/* ------------------------------------------------------------------------------------------------ */

/**
 * @fn			         : GPIO_u8PinInit
 * @brief		         : Function Initializes A GPIO Pin According to the Input Parameters
 * @param[in] PinConfig  : Initialization Values of the Pin @GPIO_PinConfig_t
 * @retval		         : Error Status
 *                           -> OK , NOK , NULL_POINTER
 **/

ERRORS_t GPIO_u8PinInit(const GPIO_PinConfig_t *PinConfig);

/**
 * @fn			         : GPIO_u8SetPinValue
 * @brief		         : Function To Set A GPIO Pin to A Certain Value
 * @param[in] Port       : The Port Number ,get options @Port_t enum
 * @param[in] PinNum     : The Pin Number , get options  @Pin_t enum
 * @param[in] PinValue   : The Output Value , get options  @PinValue_t enum
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

ERRORS_t GPIO_u8SetPinValue(Port_t Port, Pin_t PinNum, PinValue_t PinValue);

/**
 * @fn			         : GPIO_u8TogglePinValue
 * @brief		         : Function To Toggle A GPIO Pin Value ( From High to Low or Vice Versa )
 * @param[in] Port       : The Port Number , get options @Port_t
 * @param[in] PinNum     : The Pin Number , get options @Pin_t
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

ERRORS_t GPIO_u8TogglePinValue(Port_t Port, Pin_t PinNum);

/**
 * @fn			         : GPIO_u8ReadPinValue
 * @brief		         : Function To Read GPIO Pin and Return in Pointer the Value on the Pin
 * @param[in] Port       : The Port Number ,  get options  @Port_t
 * @param[in] PinNum     : the Pin Number , get options  @Pin_t
 * @param[in] PinValue   : Pointer To Put the Result init , Values -> @PinValue_t
 * @retval		         : Error Status
 *                           -> OK , NOK , NULL_POINTER
 **/

ERRORS_t GPIO_u8ReadPinValue(Port_t Port, Pin_t PinNum, PinValue_t *PinValue);

/**
 * @fn			         : GPIO_u8PinsInit
 * @brief		         : Function To Initialize a Group Of Pins
 * @param[in] Config     : Pointer To Sturct @GPIO_PinConfig_t
 * @param[in] PinsNumber : Number Of Pins Used
 * @retval		         : Error Status
 *                           -> OK , NOK , GPIO_NOK , NULL_POINTER
 * @note			     : To Use Fuction Make in Application  Array of  Structs
 *                         and Fill it With Pins Configurations , Size of Array is the  "PinsNumber" Parameter
 **/

ERRORS_t GPIO_u8PinsInit(const GPIO_PinConfig_t *Config, uint8_t PinsNumber);

/* ---------------------------------------------------------------------------------------------- */
/* ------------------------------- FUCTION PROTOTYPES SECTION END ------------------------------- */
/* ---------------------------------------------------------------------------------------------- */

#endif /* GPIO_INTERFACE_H_ */
