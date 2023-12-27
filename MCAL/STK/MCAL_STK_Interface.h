/**
 * @file MCAL_STK_Interface.h
 * @brief This file contains the interface of the MCAL_STK driver.
 *
 * @author Ahmed Abu Raya
 * @date 2023-06-20
 */

#ifndef MCAL_STK_INTERFACE_H_
#define MCAL_STK_INTERFACE_H_

/**
 * @headerfile "STD_TYPES.h"
 * @brief This header file contains the standard data types.
 */
#include "STD_TYPES.h"

/**
 * @enum STK_ClkSrc_t
 * @brief Enumeration for the SysTick clock source
 */
typedef enum {
	/**
	 * @brief AHB clock divided by 8
	 */
	AHB_8_DIVIDE,
	/**
	 * @brief CPU clock
	 */
	CPU_CLOCK_AHB
} STK_ClkSrc_t;

/**
 * @enum STK_ExceptionMode_t
 * @brief Enumeration for the SysTick exception mode
 */
typedef enum {
	/**
	 * @brief Disable SysTick exception
	 */
	DISABLE_EXCEPTION = 0,
	/**
	 * @brief Enable SysTick single exception
	 */
	ENABLE_SINGLE_EXCEPTION = 1,
	/**
	 * @brief Enable SysTick periodic exception
	 */
	ENABLE_PERIODIC_EXCEPTION = 2
} STK_ExceptionMode_t;

/**
 * @struct STK_CfgType
 * @brief Structure that contains the SysTick configuration
 */
typedef struct {
	/**
	 * @brief SysTick clock source
	 */
	STK_ClkSrc_t SysTick_ClkSrc;
	/**
	 * @brief SysTick exception mode
	 */
	STK_ExceptionMode_t SysTick_Exception;

	/* Pointer to the user function to be called on SysTick exception */
	void (*Systick_CallBackPtr)(void);
} STK_CfgType;

/**
 * @extern STK_CfgType STK_G_Config
 * @brief Global variable that holds the current SysTick configuration
 */
extern STK_CfgType STK_G_Config;

/**
 * @brief Initializes the SysTick peripheral
 *
 * @param Cp_STK_Cfg Pointer to the SysTick configuration structure
 */
void MCL_STK_vInit(STK_CfgType *Cp_STK_Cfg);

/**
 * @brief Resets the SysTick counter
 */
void MCL_STK_vResetTimer(void);

/**
 * @brief Delays the specified number of microseconds
 *
 * @param Cp_u32Ticks Number of microseconds to delay
 */
void MCL_STK_vDelay_us(u32 Cp_u32Ticks);

/**
 * @brief Delays the specified number of milliseconds
 *
 * @param Cp_u32Ticks Number of milliseconds to delay
 */
void MCL_STK_vDelay_ms(u32 Cp_u32Ticks);

/**
 * @brief Sets a single shot timer
 *
 * @param Cp_u32Ticks Number of ticks for the timer
 * @param Copy_Ptr Pointer to the function to be called when the timer expires
 */
void MCL_STK_vSetIntervalSingle(u32 Cp_u32Ticks, void (*Copy_Ptr)(void));

/**
 * @brief Sets a periodic timer
 *
 * @param Cp_u32Ticks Number of ticks for the timer
 * @param Copy_Ptr Pointer to the function to be called when the timer expires
 */
void MCL_STK_vSetIntervalPeriodic(u32 Cp_u32Ticks, void (*Copy_Ptr)(void));

/**
 * @brief Stops the periodic timer
 */
void MCL_STK_vStopInterval(void);

/**
 * @brief Gets the number of milliseconds elapsed since the SysTick counter was reset
 *
 * @return Number of milliseconds elapsed
 */
u32 MCL_STK_u32GetElapsed(void);

/**
 * @brief Gets the number of milliseconds remaining until the next SysTick timer interrupt
 *
 * @return Number of milliseconds remaining
 */
u32 MCL_STK_u32GetRemaining(void);

#endif /* MCAL_STK_INTERFACE_H_ */