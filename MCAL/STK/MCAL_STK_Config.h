/**
 * @file MCAL_STK_Config.h
 * @brief This file contains the configuration for the STK peripheral.
 *
 * @author Ahmed Abu Raya
 * @date 2023-06-20
 */

#ifndef MCAL_STK_CONFIG_H_
#define MCAL_STK_CONFIG_H_

/**
 * @headerfile "STM32F4xx_Device_Header.h"
 * @brief Include the header file for the STM32F4xx device.
 */
#include "STM32F4xx_Device_Header.h"

/**
 * @headerfile "MCAL_STK_Interface.h"
 * @brief Include the header file for the STK interface.
 */
#include "MCAL_STK_Interface.h"

/**
 * @def STK_CLOCK_SOURCE
 * @brief The clock source for the STK peripheral.
 */
#define STK_CLOCK_SOURCE    AHB_8_DIVIDE

#endif /* MCAL_STK_CONFIG_H_ */
