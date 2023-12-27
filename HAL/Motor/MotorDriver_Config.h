/**
 * @file MotorDriver_Config.h
 * @brief Configuration file for the motor driver.
 *
 * This file contains the configuration settings for the motor driver.

 */

#ifndef HAL_MOTORDRIVER_MOTORDRIVER_CONFIG_H_
#define HAL_MOTORDRIVER_MOTORDRIVER_CONFIG_H_

/**
 * @headerfile "MCAL_GPIO_Interface.h"
 * @brief This header file contains the interface for GPIO operations.
 */
#include "MCAL_GPIO_Interface.h"

/**
 * @def MOTORDRIVER_PORT
 * @brief GPIO port for the motor driver.
 *
 * This macro defines the GPIO port to which the motor driver is connected.
 */
#define MOTORDRIVER_PORT  PORTA
/**
 * @def MOTORDRIVER_PORT
 * @brief GPIO port for the motor driver.
 *
 * This macro defines the GPIO port to which the motor driver is connected.
 */
#define MOTORDRIVER_STERING_PORT  PORTC
/**
 * @def MOTORDRIVER_IN1
 * @brief GPIO pin for IN1 of the motor driver.
 *
 * This macro defines the GPIO pin for IN1 of the motor driver.
 */
#define MOTORDRIVER_IN1   PIN4

/**
 * @def MOTORDRIVER_IN2
 * @brief GPIO pin for IN2 of the motor driver.
 *
 * This macro defines the GPIO pin for IN2 of the motor driver.
 */
#define MOTORDRIVER_IN2   PIN1

/**
 * @def MOTORDRIVER_IN3
 * @brief GPIO pin for IN3 of the motor driver.
 * Steering
 * This macro defines the GPIO pin for IN3 of the motor driver.
 */
#define MOTORDRIVER_IN3   PIN0

/**
 * @def MOTORDRIVER_IN4
 * @brief GPIO pin for IN4 of the motor driver.
 *  Steering
 * This macro defines the GPIO pin for IN4 of the motor driver.
 */
#define MOTORDRIVER_IN4   PIN1





#endif /* HAL_MOTORDRIVER_MOTORDRIVER_CONFIG_H_ */
