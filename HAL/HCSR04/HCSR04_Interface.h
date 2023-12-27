/**
 * @file HCSR04_Interface.h
 * @brief Interface file for the HC-SR04 ultrasonic sensor.
 *
 * This file provides the interface for the HC-SR04 ultrasonic sensor.
 *
 * @author Ahmed Abu Raya
 * @date 2023-06-20
 */

#ifndef HCSR04_INTERFACE_H_
#define HCSR04_INTERFACE_H_

/**
 * @headerfile "STD_TYPES.h"
 * @brief This header file contains the standard data types.
 */
#include "../../inc/STD_TYPES.h"

/**
 * @headerfile "HCSR04_Config.h"
 * @brief This header file contains the configuration settings for the HC-SR04 ultrasonic sensor.
 */
#include "HCSR04_Config.h"

/**
 * @headerfile "MCAL_TIM_Interface.h"
 * @brief This header file contains the interface for timer operations.
 */
#include "../../inc/MCAL_TIM_Interface.h"

/**
 * @headerfile "MCAL_GPIO_Interface.h"
 * @brief This header file contains the interface for GPIO operations.
 */
#include "../../inc/MCAL_GPIO_Interface.h"

/**
 * @struct HCSR04_CfgType
 * @brief Configuration structure for the HC-SR04 ultrasonic sensor.
 *
 * This structure defines the configuration settings for the HC-SR04 ultrasonic sensor.
 * It contains various parameters required for sensor operation.
 */
typedef struct {
	u8 Instance;            /*!< Sensor instance number. Meant for private use only. */
	GPIO_TypeDef* ECHO_Port;    /*!< Pointer to GPIOx PORT for ECHO pin. Meant for private use only. */
	GPIO_Pin_t ECHO_Pin;      /*!< GPIO Pin for ECHO pin. Meant for private use only. */
	GPIO_TypeDef* TRIG_Port; /*!< Pointer to GPIOx PORT for TRIGGER pin. Meant for private use only. */
	GPIO_Pin_t TRIG_Pin;   /*!< GPIO Pin for TRIGGER pin. Meant for private use only. */
	TIM_TypeDef* TIM_Instance; /*!< Timer instance for sensor timing. Meant for private use only. */
	TIM_Channel_t IC_TIM_CH;   /*!< Timer input capture channel for sensor timing. Meant for private use only. */
	TIM_IC_CfgType IC_Init;    /*!< Timer input capture configuration for sensor timing. Meant for private use only. */
	u32 TIM_CLK_MHz;           /*!< Timer clock frequency in MHz. Meant for private use only. */
} HCSR04_CfgType;

extern HCSR04_CfgType HCSR04_CfgParam[]; /*!< Array of HC-SR04 sensor configurations. */

extern TIM_HandleTypeDef US_htim2; /*!< Timer handle for the HC-SR04 sensor. */

/**
 * @brief Initializes the HC-SR04 ultrasonic sensor.
 *
 * This function initializes the HC-SR04 ultrasonic sensor with the provided configuration.
 *
 * @param HCSR04 Pointer to the HC-SR04 configuration structure.
 * @param TMR_Handle Pointer to the timer handle used for sensor timing.
 */
void HAL_HCSR04_vInit(HCSR04_CfgType* HCSR04, TIM_HandleTypeDef* TMR_Handle);

/**
 * @brief Triggers the HC-SR04 ultrasonic sensor.
 *
 * This function triggers the HC-SR04 ultrasonic sensor to start the distance measurement process.
 *
 * @param HCSR04_u8Instance Sensor instance number.
 */
void HAL_HCSR04_vTrigger(u8 HCSR04_u8Instance);

/**
 * @brief Timer overflow interrupt handler for the HC-SR04 sensor.
 *
 * This function is the interrupt handler for the timer overflow event used by the HC-SR04 sensor.
 *
 * @param TMR_Handle Pointer to the timer handle.
 */
void HAL_HCSR04_TMR_OVF_ISR(TIM_HandleTypeDef* TMR_Handle);

/**
 * @brief Timer input capture interrupt handler for the HC-SR04 sensor.
 *
 * This function is the interrupt handler for the timer input capture event used by the HC-SR04 sensor.
 *
 * @param TMR_Handle Pointer to the timer handle.
 */
void HAL_HCSR04_TMR_IC_ISR(TIM_HandleTypeDef* TMR_Handle);

/**
 * @brief Reads the distance measured by the HC-SR04 ultrasonic sensor.
 *
 * This function reads the distance measured by the HC-SR04 ultrasonic sensor in centimeters.
 *
 * @param HCSR04_u8Instance Sensor instance number.
 * @return Distance measured by the sensor in centimeters.
 */
u32 HAL_HCSR04_f32Read(u8 HCSR04_u8Instance);

#endif /* HCSR04_INTERFACE_H_ */