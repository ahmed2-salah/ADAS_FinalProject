/**
 * @file HCSR04_Config.c
 * @brief Source file for the HC-SR04 ultrasonic sensor configurations.
 *
 * @author Ahmed Abu Raya
 * @date 2023-06-20
 */

/**
 * @headerfile "HCSR04_Interface.h"
 * @brief This header file contains the interface for the HC-SR04 ultrasonic sensor.
 */
#include "HCSR04_Interface.h"

/**
 * @headerfile "MCAL_GPIO_Interface.h"
 * @brief This header file contains the interface for GPIO operations.
 */
#include "../../inc/MCAL_GPIO_Interface.h"

/**
 * @headerfile "MCAL_TIM_Interface.h"
 * @brief This header file contains the interface for timer operations.
 */
#include "../../inc/MCAL_TIM_Interface.h"

/**
 * @brief Configuration parameters for the HC-SR04 sensor instances.
 *
 * This array defines the configuration parameters for each HC-SR04 sensor instance.
 * Each element in the array represents a separate instance of the sensor.
 */
HCSR04_CfgType HCSR04_CfgParam[HCSR04_INSTANCE_COUNT] =
		{
				// HC-SR04 Sensor Unit 1 Configurations
				{
						.ECHO_Port = GPIOA,
						.ECHO_Pin = GPIO_PIN0,
						.TRIG_Port = GPIOB,
						.TRIG_Pin = GPIO_PIN14,
						.Instance = 0,
						.TIM_Instance = TIM2,
						.IC_TIM_CH = TIM_CHANNEL_1,
						.TIM_CLK_MHz = 16
				}
		};

/**
 * @brief TIM_HandleTypeDef structure for HC-SR04 sensor timing.
 *
 * This structure defines the configuration parameters for the timer used by the HC-SR04 sensor.
 */
TIM_HandleTypeDef US_htim2 =
		{
				.Channel = TIM_CHANNEL_1,
				.Instance = TIM2
		};
