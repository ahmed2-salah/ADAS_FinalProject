/*
 ******************************************************************************
 * @file           : GPIO_Program.c
 * @Author         : AutoPots
 * @brief          : GPIO Main Source File
 * @Date           : May 5, 2023
 * @Target     	   : STM32F446xx
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 .
 * All rights reserved.
 *
 ******************************************************************************
 */

/*==============================================================================================================================================
 * INCLUDES SECTION START
 *==============================================================================================================================================*/
#include <stdint.h>

#include "ErrTypes.h"
#include "STM32F446xx.h"


#include "GPIO_Interface.h"
#include "GPIO_Private.h"

/*==============================================================================================================================================
 * INCLUDES SECTION END
 *==============================================================================================================================================*/

/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION START
 *==============================================================================================================================================*/

static GPIO_RegDef_t *GPIO_PORT[GPIO_PERIPHERAL_NUM] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};

/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION END
 *==============================================================================================================================================*/

/*==============================================================================================================================================
 * MODULES IMPLEMENTATION
 *==============================================================================================================================================*/

/**
 * @fn			         : GPIO_u8PinInit
 * @brief		         : Function Initializes A GPIO Pin According to the Input Parameters
 * @param[in] PinConfig  : Initialization Values of the Pin @GPIO_PinConfig_t
 * @retval		         : Error Status
 *                           -> OK , NOK , NULL_POINTER
 **/

ERRORS_t GPIO_u8PinInit(const GPIO_PinConfig_t *PinConfig)
{
	/* uint8_t Variable to Carry Error Status */
	ERRORS_t Local_u8ErrorStatus = OK;

	/* Check if Pointer Don't Point to Allocated Data */
	if (NULL != PinConfig)
	{
		/* Check if Right Port and PinNum is Passed Before Executing */
		if (GPIO_NOT_VALID != GPIO_u8CheckPinConfig(PinConfig))
		{
			/* Select Mode : INPUT , OUTPUT , ANALOG , ALERNATE_FUNCTION */
			(GPIO_PORT[PinConfig->Port]->MODER) &= (~(MODER_MASK << ((PinConfig->PinNum) * MODER_PIN_ACCESS)));
			(GPIO_PORT[PinConfig->Port]->MODER) |= ((PinConfig->Mode) << ((PinConfig->PinNum) * MODER_PIN_ACCESS));

			/* Select PullType : PULL_UP , PULL_DOWN */
			(GPIO_PORT[PinConfig->Port]->PUPDR) &= (~(PUPDR_MASK << ((PinConfig->PinNum) * PUPDR_PIN_ACCESS)));
			(GPIO_PORT[PinConfig->Port]->PUPDR) |= ((PinConfig->PullType) << ((PinConfig->PinNum) * PUPDR_PIN_ACCESS));

			if ((PinConfig->Mode == OUTPUT) || (PinConfig->Mode) == ALTERNATE_FUNCTION)
			{
				/* Select Output Speed : LOW_SPEED , MEDIUM_SPEED , FAST_SPEED , HIGH_SPEED */
				(GPIO_PORT[PinConfig->Port]->OSPEEDR) &= (~(OSPEEDR_MASK << ((PinConfig->PinNum) * OSPEEDR_PIN_ACCESS)));
				(GPIO_PORT[PinConfig->Port]->OSPEEDR) |= ((PinConfig->Speed) << ((PinConfig->PinNum) * OSPEEDR_PIN_ACCESS));

				/* Select Output Type : PUSH_PULL , OPEN_DRAIN */
				if ((PinConfig->OutputType) == OPEN_DRAIN)
				{
					/* OPEN_DRAIN Bit = 1 */
					(GPIO_PORT[PinConfig->Port]->OTYPER) |= (1 << (PinConfig->PinNum));
				}
				else
				{
					/* IF PUSH_PULL is Passed OR Any Other Value  */
					/* PUSH_PULL Bit = 0 */
					(GPIO_PORT[PinConfig->Port]->OTYPER) &= (~(1 << (PinConfig->PinNum)));
				}

				if ((PinConfig->Mode) == ALTERNATE_FUNCTION)
				{
					/* REGNum To Indicate For AFR_L OR AFR_H */
					/* BITNum To Indicate For IN AFR_L OR AFR_H */
					uint8_t Local_u8REGNum = ((PinConfig->PinNum) >= REG_WIDTH);
					uint8_t Local_u8BITNum = ((PinConfig->PinNum) % REG_WIDTH);

					/* Select Required AF From AF0 -> AF15 */
					(GPIO_PORT[PinConfig->Port]->AFR[Local_u8REGNum]) &= (~(AFR_MASK << (Local_u8BITNum * AFR_PIN_ACCESS)));
					(GPIO_PORT[PinConfig->Port]->AFR[Local_u8REGNum]) |= ((PinConfig->AltFunc) << (Local_u8BITNum * AFR_PIN_ACCESS));
				}
			}
		}
		else
		{
			/* Wrong Configuration Option */
			Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		/* Pointer Not Pointing To Data */
		Local_u8ErrorStatus = NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}

/**
 * @fn			         : GPIO_u8SetPinValue
 * @brief		         : Function To Set A GPIO Pin to A Certain Value
 * @param[in] Port       : The Port Number ,get options @Port_t enum
 * @param[in] PinNum     : The Pin Number , get options  @Pin_t enum
 * @param[in] PinValue   : The Output Value , get options  @PinValue_t enum
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

ERRORS_t GPIO_u8SetPinValue(Port_t Port, Pin_t PinNum, PinValue_t PinValue)
{
	/* uint8_t Variable to Carry Error Status */
	ERRORS_t Local_u8ErrorStatus = OK;

	/* Check if Right Port and PinNum is Passed Before Executing */
	if ((Port <= PORTH) && (PinNum <= PIN15))
	{
		/* Check if Pin Desired Value is HIGH */
		if (PinValue == PIN_HIGH)
		{
			/* Set Bit Using ODR */
			GPIO_PORT[Port]->ODR |= (1 << PinNum);

			/* Set Bit Using BSRR */
			/* GPIO_PORT[ Port ]->BSRR = ( 1 << PinNum ) ; */
		}
		else if (PinValue == PIN_LOW)
		{
			/* Clear Bit Using ODR */
			GPIO_PORT[Port]->ODR &= (~(1 << PinNum));

			/* Clear Bit Using BSRR */
			/* GPIO_PORT[ Port ]->BSRR = ( 1 << ( 16+PinNum ) ) ; */
		}
		else
		{
			/* Wrong PinValue Configuration Option is Passed */
			Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		/* Wrong Port or PinNum Configuration Options is Passed */
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}

/**
 * @fn			         : GPIO_u8TogglePinValue
 * @brief		         : Function To Toggle A GPIO Pin Value ( From High to Low or Vice Versa )
 * @param[in] Port       : The Port Number , get options @Port_t
 * @param[in] PinNum     : The Pin Number , get options @Pin_t
 * @retval		         : Error Status
 *                           -> OK , NOK
 **/

ERRORS_t GPIO_u8TogglePinValue(Port_t Port, Pin_t PinNum)
{
	/* uint8_t Variable to Carry Error Status */
	ERRORS_t Local_u8ErrorStatus = OK;

	/* Check if Right Port and PinNum is Passed Before Executing */
	if ((Port <= PORTH) && (PinNum <= PIN15))
	{
		/* Toggle Passed Bit */
		(GPIO_PORT[Port]->ODR) ^= (1 << PinNum);
	}
	else
	{
		Local_u8ErrorStatus = NOK;
	}
	return Local_u8ErrorStatus;
}

/**
 * @fn			         : GPIO_u8ReadPinValue
 * @brief		         : Function To Read GPIO Pin and Return in Pointer the Value on the Pin
 * @param[in] Port       : The Port Number ,  get options  @Port_t
 * @param[in] PinNum     : the Pin Number , get options  @Pin_t
 * @param[in] PinValue   : Pointer To Put the Result init , Values -> @PinValue_t
 * @retval		         : Error Status
 *                           -> OK , NOK , NULL_POINTER
 **/

ERRORS_t GPIO_u8ReadPinValue(Port_t Port, Pin_t PinNum, PinValue_t *PinValue)
{
	/* uint8_t Variable to Carry Error Status */
	ERRORS_t Local_u8ErrorStatus = OK;

	if (PinValue != NULL)
	{
		/* Check if Right Port and PinNum is Passed Before Executing */
		if ((Port <= PORTH) && (PinNum <= PIN15))
		{
			*PinValue = (((GPIO_PORT[Port]->IDR) >> PinNum) & 0x01U);
		}
		else
		{
			Local_u8ErrorStatus = NOK;
		}
	}
	else
	{
		Local_u8ErrorStatus = NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}

/**
 * @fn			         : GPIO_u8PinsInit
 * @brief		         : Function To Initialize a Group Of Pins
 * @param[in] Config     : Pointer To Sturct @GPIO_PinConfig_t
 * @param[in] PinsNumber : Number Of Pins Used
 * @retval		         : Error Status
 *                           -> OK , GPIO_NOK , NULL_POINTER
 * @note			     : To Use Fuction Make in Application  Array of  Structs
 *                         and Fill it With Pins Configurations , Size of Array is the  "PinsNumber" Parameter
 **/

ERRORS_t GPIO_u8PinsInit(const GPIO_PinConfig_t *Config, uint8_t PinsNumber)
{
	/* Itterator */
	uint8_t Counter = 0;

	/* uint8_t Variable to Carry Error Status */
	ERRORS_t ErrorStatus = OK;

	if (NULL != Config)
	{
		/* Itterate Through Array Of Struct Elements */
		for (Counter = 0; Counter < PinsNumber; Counter++)
		{
			/* Intialize Every Struct in the Array */
			ErrorStatus = GPIO_u8PinInit(&(Config[Counter]));
			if ( ErrorStatus == NOK  || ErrorStatus == NULL_POINTER )
			{
				return GPIO_NOK;
			}
		}
	}
	else
	{
		ErrorStatus = NULL_POINTER;
	}

	return ErrorStatus;
}

/**
 * @fn			         : GPIO_u8CheckPinConfig
 * @brief		         : Function To Check on Configuration Structure Passed to Program Functions
 * @param[in] Config     : Pointer to Struct @GPIO_PinConfig_t
 * @retval		         : Error Status
 *                           -> GPIO_VALID , GPIO_NOT_VALID
 * @note			         : This Function is a Private Function that Services on GPIO Functions
 **/

static ERRORS_t GPIO_u8CheckPinConfig(const GPIO_PinConfig_t *PinConfig)
{
	/* uint8_t Variable to Carry Error Status */

	ERRORS_t ErrorStatus = OK;

	/* Check on ALL Passed Configurations */
	if ((PinConfig->AltFunc) > AF15 || (PinConfig->AltFunc) < AF0 ||
		(PinConfig->Mode > ANALOG) || (PinConfig->Mode) < INPUT ||
		(PinConfig->OutputType) > OPEN_DRAIN || (PinConfig->OutputType) < PUSH_PULL ||
		(PinConfig->PinNum) > PIN15 || (PinConfig->PinNum) < PIN0 ||
		(PinConfig->Port) > PORTH || (PinConfig->Port) < PORTA ||
		(PinConfig->PullType) > PULL_DOWN || (PinConfig->PullType) < NO_PULL ||
		(PinConfig->Speed) > HIGH_SPEED || (PinConfig->Speed) < LOW_SPEED)
	{
		/* Wrong Configuration */
		ErrorStatus = GPIO_NOT_VALID ;
	}
	else
	{
		ErrorStatus = GPIO_VALID ;
	}
	return ErrorStatus;
}
