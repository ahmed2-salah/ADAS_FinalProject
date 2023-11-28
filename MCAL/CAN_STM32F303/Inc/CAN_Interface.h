/*
 * CAN_Interface.h
 *
 *  Created on: Nov 23, 2023
 *  Author: MERNA MAGDY
 */

#ifndef INC_CAN_INTERFACE_H_
#define INC_CAN_INTERFACE_H_
#include "stm32f3xx.h"
#include "CAN_Types.h"
#include "CAN_Private.h"

#define TS1_Q	8
#define TS2_Q	1
#define HIGH	1
#define LOW		0
/*
 * brief:set the SLEEP mode configuration
 * param: void
 * retval: void
 */
void HAL_CAN_ENTER_SLEEP_MODE(void);
/*
 * brief: clear the SLEEP mode configuration
 * param: void
 * retval: void
 */
void HAL_CAN_LEAVE_SLEEP_MODE(void);
/*
 * brief: set the Initialization mode configuration
 * param: void
 * retval: void
 */
void HAL_CAN_ENTER_INIT_MODE(void);
/*
 * brief: clear the Initialization mode configuration
 * param: void
 * retval: void
 */
void HAL_CAN_LEAVE_INIT_MODE(void);
/*
 * brief: set bit Time
 * param: a pointer to  S_CAN_BITIME_CONFIG structure that contains
 * 		  bit time CAN clk configuration
 * retval: void
 */
void HAL_CAN_vsetbiTime(S_CAN_BITIME_CONFIG* bitime);
/*
 * brief: SET THE INITIALIZATION CONFIGURATION
 * param: a pointer to  S_CAN_INIT_CONFIG structure that contains
 * 		  CAN initialization configuration
 * retval: void
 */
void HAL_CAN_vInit(S_CAN_INIT_CONFIG* initConfig);
/*
 * brief: PREPARE THE TX FRAME
 * parameter: a pointer to  S_CAN_INIT_CONFIG structure that contains
 * 		 	  CAN initialization configuration
 * parameter: a pointer to  S_CAN_TXFRAME structure that contains
 * 		  	  FRAME CONFIGURATION
 * parameter: DATA array that contains CAN payload
 * in/out arg: pointer to a byte location that should be updated by the function
 * retval: void
 */
void HAL_CAN_pu8TXFRAME(S_CAN_INIT_CONFIG* initConfig,S_CAN_TXFRAME* TX_FRAME, uint32_t DATA[], uint8_t* MAILBOX_CODE);
/*
 * brief: Abort a requested Frame to be transmitted
 * param: the code of the mailbox carrying the massage to be aborted
 * retval: void
 */
void HAL_CAN_vAbortTXRQ(uint8_t MAILBOX_CODE);
/*
 * brief: GET NUMBER OF TX EMPTY MAILBOXES
 * in/out argument: a pointer to a byte location to store the returned number of empty TX mailboxes
 * retval: void
 */
void HAL_CAN_u8GetFreeMailbox(uint8_t* FREE_MAILBOX_COUNT);
/*
 * brief: CHECK if a massage stored in one mailbox is pending or not
 * parameter: a byte contains the code of the mailbox carrying the massage to be checked
 * in/out argument: a pointer to a byte location to store the returned pending status of the TX mailbox
 * retval: void
 */
void HAL_CAN_u8IS_TXFRAME_PENDING(uint8_t* pendingStatus,uint8_t MAILBOX_CODE);

#endif /* INC_CAN_INTERFACE_H_ */
