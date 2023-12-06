/**
 * @file IR_Sensor_IR_Config.h
 * @brief Configuration file for the IR sensor.
 *
 * This file contains the configuration settings for the IR sensor.

 */

#ifndef IR_CONFIG_H_
#define IR_CONFIG_H_
#include"STM32F446xx.h"
#include"MCAL_GPIO_Interface.h"
/**
 * @def IR_PORT
 * @brief GPIO port to which the IR sensors are connected.
 *
 * Connect the IR sensors to this GPIO port.
 */
#define IR_PORT         PORTB

/**
 * @def IR_RIGHT
 * @brief Pin number to which the right IR sensor is connected.
 *
 * Connect the right IR sensor to this pin.
 */
#define IR_RIGHT        PIN0

/**
 * @def IR_LEFT
 * @brief Pin number to which the left IR sensor is connected.
 *
 * Connect the left IR sensor to this pin.
 */
#define IR_LEFT        PIN1


#endif /* IR_CONFIG_H_ */
