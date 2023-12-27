/**
 * @file HCSR04_Source.c
 * @brief Source file for the HC-SR04 ultrasonic sensor.
 *
 * This file provides the implementation of the HC-SR04 ultrasonic sensor functions.
 */

/**
 * @headerfile "MCAL_STK_Interface.h"
 * @brief This header file contains the interface for the system timer.
 */
#include "../../inc/MCAL_STK_Interface.h"

/**
 * @headerfile "MCAL_GPIO_Interface.h"
 * @brief This header file contains the interface for GPIO operations.
 */
#include "../../inc/MCAL_GPIO_Interface.h"

/**
 * @headerfile "Timer_Delay.h"
 * @brief This header file contains the interface for delay functions.
 */
#include "../../util/Timer_Delay.h"

/**
 * @headerfile "HCSR04_Config.h"
 * @brief This header file contains the configuration settings for the HC-SR04 ultrasonic sensor.
 */
#include "HCSR04_Config.h"

/**
 * @headerfile "HCSR04_Interface.h"
 * @brief This header file contains the interface for the HC-SR04 ultrasonic sensor.
 */
#include "HCSR04_Interface.h"

/**
 * @struct HCSR04_info
 * @brief Information structure for the HC-SR04 ultrasonic sensor.
 *
 * This structure contains information related to the HC-SR04 ultrasonic sensor, including various timing parameters.
 */
typedef struct {
	u8 EDGE_STATE;             /*!< Current edge state of the sensor. */
	u16 TMR_OVC;               /*!< Timer overflow count. */
	u32 TMR_PSC;               /*!< Timer prescaler value. */
	u32 TMR_ARR;               /*!< Timer auto-reload value. */
	u32 T1;                    /*!< Timestamp for rising edge. */
	u32 T2;                    /*!< Timestamp for falling edge. */
	u32 DIFF;                  /*!< Time difference between rising and falling edges. */
	f32 DISTANCE;              /*!< Calculated distance. */
	TIM_HandleTypeDef *HTIM;  /*!< Pointer to the timer handle used for sensor timing. */
	TIM_Channel_t ACTIV_CH;    /*!< Active timer channel. */
} HCSR04_info;

HCSR04_info Gb_HCSR04_info[HCSR04_INSTANCE_COUNT] = {0};  /*!< Array of HC-SR04 sensor information structures. */

u32 HCSR04_Distance = 0;             /*!< Variable to store the distance measured by the HC-SR04 sensor. */
u32 HCSR04_OverFlow_Count = 0;       /*!< Variable to store the timer overflow count for the HC-SR04 sensor. */

void HAL_HCSR04_vInit(HCSR04_CfgType *HCSR04, TIM_HandleTypeDef *TMR_Handle) {
	// Initialize the GPIO pins
	GPIO_CfgType GPIO_InitStruct = {0};

	GPIO_InitStruct.GPIO_Pin = HCSR04->TRIG_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_MODE_OUT_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_SPEED_HIGH;
	MCL_GPIO_vSetPinCfg(HCSR04->TRIG_Port, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = HCSR04->ECHO_Pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_SPEED_LOW;
	MCL_GPIO_vSetPinCfg(HCSR04->ECHO_Port, &GPIO_InitStruct);
	MCL_GPIO_vSetPinAltFunc(HCSR04->ECHO_Port, GPIO_InitStruct.GPIO_Pin, GPIO_AF1_TIM1_TIM2);

	/*--------[ Configure The HCSR04 IC Timer Channel ]-------*/
	TMR_Handle->Instance = HCSR04_CfgParam[HCSR04->Instance].TIM_Instance;
	TMR_Handle->Init.TIM_Mode = TIM_MODE_INPUT_CAPTURE;
	TMR_Handle->Init.TIM_Prescaler = HCSR04_CfgParam[HCSR04->Instance].TIM_CLK_MHz;
	TMR_Handle->Init.TIM_CounterMode = TIM_COUNTERMODE_UP;
	TMR_Handle->Init.TIM_Period = HCSR04->IC_Init.IC_Period;
	TMR_Handle->Init.TIM_ClockDiv = 0;
	TMR_Handle->Channel = HCSR04->IC_TIM_CH;
	TMR_Handle->Init.TIM_INT = TIM_INT_CC1;

	HCSR04_CfgParam[HCSR04->Instance].IC_Init = TIM_IC_Config;
	TIM_vInit(TMR_Handle);
	TIM_IC_vInit(TMR_Handle, &HCSR04->IC_Init);
	// Enable the timer interrupt
	TIM_vStart(TMR_Handle);
}

void HAL_HCSR04_TMR_OVF_ISR(TIM_HandleTypeDef *htim) {
	u8 i = 0;
	for (i = 0; i < HCSR04_INSTANCE_COUNT; i++) {
		if (htim->Instance == HCSR04_CfgParam[i].TIM_Instance) {
			HCSR04_OverFlow_Count++;
		}
	}
}

void HAL_HCSR04_TMR_IC_ISR(TIM_HandleTypeDef *htim) {
	// Find the HCSR04 instance corresponding to the timer and channel
	u8 instance = 0;
	for (instance = 0; instance < HCSR04_INSTANCE_COUNT; instance++) {
		if (htim->Instance == HCSR04_CfgParam[instance].TIM_Instance &&
		    htim->Channel == HCSR04_CfgParam[instance].IC_Init.IC_Channel) {

			// Check if a valid HCSR04 instance was found
			if (instance < HCSR04_INSTANCE_COUNT) {
				static u32 t1 = 0;
				static u32 t2 = 0;
				static u8 edge_state = 0;

				if (edge_state == 0) {
					// Capture T1 and reverse the ICU edge polarity
					t1 = TIM_u32ReadCapturedVal(htim, HCSR04_CfgParam[instance].IC_Init.IC_Channel);
					edge_state = 1;
					TIM_vSetClkPolarity(htim, HCSR04_CfgParam[instance].IC_Init.IC_Channel, TIM_CLOCKPOLARITY_FALLING);
					HCSR04_OverFlow_Count = 0;
				} else if (edge_state == 1) {
					// Capture T2 and calculate the distance
					u32 t2_raw = TIM_u32ReadCapturedVal(htim, HCSR04_CfgParam[instance].IC_Init.IC_Channel);
					u32 tmr_arr = HCSR04_CfgParam[instance].TIM_Instance->ARR;
					u32 tmr_psc = HCSR04_CfgParam[instance].IC_Init.IC_Prescaler;
					HCSR04_OverFlow_Count += (t2_raw < t1) ? 1 : 0;
					t2 = t2_raw + HCSR04_OverFlow_Count * (tmr_arr + 1);
					u32 diff = t2 - t1;
					HCSR04_Distance = (diff * (HCSR04_CfgParam[instance].TIM_CLK_MHz / (tmr_psc + 1))) /
					                  29; // Divide by 29 to account for the fact that ultrasonics show twice the distance
					edge_state = 0;
					TIM_vSetClkPolarity(htim, HCSR04_CfgParam[instance].IC_Init.IC_Channel, TIM_CLOCKPOLARITY_RISING);
				}
			}
		}
	}
}

u32 HAL_HCSR04_f32Read(u8 HCSR04_u8Instance) {
	return HCSR04_Distance;
}

void HAL_HCSR04_vTrigger(u8 HCSR04_u8Instance) {
	MCL_GPIO_vAtomicSetPin(HCSR04_CfgParam[HCSR04_u8Instance].TRIG_Port, HCSR04_CfgParam[HCSR04_u8Instance].TRIG_Pin,
	                       PIN_SET);
	TimerDelay_us(10);
	MCL_GPIO_vAtomicSetPin(HCSR04_CfgParam[HCSR04_u8Instance].TRIG_Port, HCSR04_CfgParam[HCSR04_u8Instance].TRIG_Pin,
	                       PIN_RESET);
}