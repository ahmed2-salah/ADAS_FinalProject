/**
 * @file MCAL_STK_Private.h
 * @brief This file contains the private definitions of the MCAL_STK driver.
 *
 * @author Ahmed Abu Raya
 * @date 2023-06-20
 */

#ifndef MCAL_STK_PRIVATE_H_
#define MCAL_STK_PRIVATE_H_

/**
 * @headerfile "STD_TYPES.h"
 * @brief This header file contains the standard data types.
 */
#include "STD_TYPES.h"

/**
 * @headerfile "STM32F4xx_Device_Header.h"
 * @brief Include the header file for the STM32F4xx device.
 */
#include "STM32F4xx_Device_Header.h"

/**
 * @struct STK_TypeDef
 * @brief SysTick Control Register
 */
typedef struct {
	union {
		struct {
			/**
			 * @brief Enable bit
			 */
			vu32 ENABLE: 1;
			/**
			 * @brief SysTick interrupt enable bit
			 */
			vu32 TICKINT: 1;
			/**
			 * @brief SysTick clock source selection bit
			 */
			vu32 CLKSOURCE: 1;
			/**
			 * @brief Reserved bits
			 */
			u32 : 13;
			/**
			 * @brief SysTick counter flag bit
			 */
			vu32 COUNTFLAG: 1;
			/**
			 * @brief Reserved bits
			 */
			u32 : 15;
		} STK_CTRL_Bits;
		/* SysTick Control Register */
		vu32 STK_CTRL;
	};

	vu32 STK_LOAD;
	vu32 STK_VAL;
	vu32 STK_CALIB;

} STK_TypeDef;

/**
 * @def STK
 * @brief Pointer to the SysTick peripheral registers
 */
#define STK                ((volatile STK_TypeDef *)SYSTICK_BASE)

#endif /* MCAL_STK_PRIVATE_H_ */
