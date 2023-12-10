/*
 * CAN_Types.h
 *
 *  Created on: Nov 23, 2023
 *  Author: Merna Magdy
 */

#ifndef STM32F3XX_HAL_DRIVER_INC_CAN_TYPES_H_
#define STM32F3XX_HAL_DRIVER_INC_CAN_TYPES_H_

#include"stm32f446xx.h"

typedef enum
{
	PRESCALER_1 =0,
	PRESCALER_2=1,
	PRESCALER_4=3,
	PRESCALER_8=7,
	PRESCALER_16=15,
	PRESCALER_32=31,
	PRESCALER_64=63,
	PRESCALER_128=127,
	PRESCALER_256=255,
	PRESCALER_512=511,
	PRESCALER_1024=1023
}E_CAN_PRESCALER;/*@ CAN_PRESCALER*/

typedef enum
{
	SLEEP_MODE,
	INITIALIZATION_MODE,
	NORMAL_MODE,
	SILENT_MODE,
	LOOPBACK_MODE,
	LOOPBACK_SILENT_MODE
}E_CAN_MODE;


typedef struct
{
	E_CAN_PRESCALER prescaler;/* @ E_CAN_PRESCALER*/
	uint8_t TS1_Qunata; /*number of time quantum in time segment 1 to set the desired baud rate with less error risk*/
	uint8_t TS2_Qunata; /*number of time quantum in time segment 2 to set the desired baud rate with less error risk*/

}S_CAN_BITIME_CONFIG;

typedef struct
{
	E_CAN_MODE debugMode;
	FunctionalState AUTO_RETRANSMISSION;
	FunctionalState IDENTIFIER_PRIORITY;
	FunctionalState	AUTO_BUSOFF_RECOVERY;
	FunctionalState AUTO_WAKEUP_MODE;

	FunctionalState	TIME_TRIG_COM;
	/*ADD MORE MODES FUNCTIONALITIES*/
}S_CAN_INIT_CONFIG;

typedef enum
{
	STD_ID,//standard identifier
	EXT_ID=0x00000004U//extended identifier
}E_CAN_ID_TYPE;
typedef enum
{
	MSK_MODE,
	ID_MODE
}E_FILTER_MATCHING_MODE;
typedef enum
{
	DUAL_16,
	SINGLE_32
}E_FILTER_SCALE;
typedef enum
{
	FIFO0,
	FIFO1
}E_FILTER_ASSIGN;

typedef struct
{
	E_FILTER_MATCHING_MODE filterxMode;
	E_FILTER_SCALE filterxScale;
	E_FILTER_ASSIGN filterxAssign;
	FunctionalState	filterxActivation;
	uint16_t MSG_ID_MASK_LOW;
	uint16_t MSG_ID_MASK_HIGH;
	uint16_t MSG_ID_LOW;
	uint16_t MSG_ID_HIGH;
	uint32_t filterBank;//you have 14 (0~13)bank each composed of 2 32_bit registers
}s_filterxConfig;

typedef struct
{
	E_CAN_ID_TYPE ID_TYPE;      /* Specifies the type of identifier for the message that will be transmitted.
	                      	  	  This parameter can be a value of @ref CAN_identifier_type */
	uint32_t StdId;    			/* Specifies the standard identifier.
	                      	  	  This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF. */
	uint32_t ExtId;   		    /* Specifies the extended identifier.
									  This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF. */

	uint32_t RTR;      /* Specifies the type of frame for the message that will be transmitted.
	                      This parameter can be a value of @ref CAN_remote_transmission_request */
	uint32_t DLC;      /* Specifies the length of the frame that will be transmitted.
	                      This parameter must be a number between Min_Data = 0 and Max_Data = 8 */
	FunctionalState GLOBAL_TRANSMISSION;
}S_CAN_TXFRAME;

typedef struct
{
	E_CAN_ID_TYPE ID_TYPE;      /* Specifies the type of identifier for the message that will be transmitted.
	                      	  	  This parameter can be a value of @ref CAN_identifier_type */
	uint32_t StdId;    			/* Specifies the standard identifier.
	                      	  	  This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF. */
	uint32_t ExtId;   		    /* Specifies the extended identifier.
									  This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF. */

	uint32_t RTR;      /* Specifies the type of frame for the message that will be transmitted.
	                      This parameter can be a value of @ref CAN_remote_transmission_request */
	uint32_t DLC;      /* Specifies the length of the frame that will be transmitted.
	                      This parameter must be a number between Min_Data = 0 and Max_Data = 8 */
	uint32_t FILTER_BANK_INDEX;
}S_CAN_RXFRAME;


#endif /* STM32F3XX_HAL_DRIVER_INC_CAN_TYPES_H_ */
