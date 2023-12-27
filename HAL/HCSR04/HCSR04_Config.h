/**
 * @file HCSR04_Config.h
 * @brief Configuration file for the HC-SR04 ultrasonic sensor.
 *
 * @author Ahmed Abu Raya
 * @date 2023-06-20
 */

#ifndef HCSR04_CFG_H_
#define HCSR04_CFG_H_

/**
 * @headerfile "HCSR04_Interface.h"
 * @brief This header file contains the interface for the HC-SR04 ultrasonic sensor.
 */
#include "HCSR04_Interface.h"

/**
 * @def HCSR04_INSTANCE_COUNT
 * @brief Number of HC-SR04 ultrasonic sensors to be used in the project.
 *
 * This macro defines the number of HC-SR04 sensors to be used in the project.
 */
#define HCSR04_INSTANCE_COUNT  	1

/**
 * @def HCSR04_SENSOR1
 * @brief Sensor instance for HC-SR04 sensor 1.
 *
 * This macro defines the sensor instance for HC-SR04 sensor 1.
 */
#define HCSR04_SENSOR1  		0

/**
 * @brief Sets the configuration for the HC-SR04 sensor.
 *
 * This function sets the configuration for the HC-SR04 sensor.
 * It is called to initialize the sensor configuration before using it.
 */
void HAL_HCSR04_vSetCfg();

#endif /* HCSR04_CFG_H_ */
