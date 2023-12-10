/*
 * CAN_Interface.h
 *
 *  Created on: Nov 23, 2023
 *  Author: MERNA MAGDY
 */

#ifndef INC_CAN_INTERFACE_H_
#define INC_CAN_INTERFACE_H_
#include "stm32f4xx.h"
#include "CAN_Types.h"
#include "CAN_Private.h"

#define TS1_Q		1
#define TS2_Q		2
#define HIGH		1
#define LOW			0
#define STDID_Pos   21UL
#define RTR_Pos		2UL
#define EXTID_Pos	3UL
/*
 * brief: Enter the normal mode to have access on the CAN bus
 * called after the initialization or debug mode or to leave sleep mode to normal mode
 * param: void
 * retval: void
 */
void HAL_CAN_start(void);
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
 * retval: STATIC void
 */
void HAL_CAN_vsetbiTime(S_CAN_BITIME_CONFIG* bitime);
/*
 * brief: SET THE INITIALIZATION CONFIGURATION
 * param: a pointer to  S_CAN_INIT_CONFIG structure that contains
 * 		  CAN initialization configuration
 * param: a pointer to  S_CAN_BITIME_CONFIG structure that contains
 * 		  bit time CAN clk configuration
 * retval: void
 */
void HAL_CAN_vInit(S_CAN_INIT_CONFIG* initConfig,S_CAN_BITIME_CONFIG* bitime);
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
void HAL_CAN_pu8TXFRAME(S_CAN_INIT_CONFIG* initConfig,S_CAN_TXFRAME* TX_FRAME, uint8_t DATA[], uint8_t* MAILBOX_CODE);
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
/*
 * brief: locks the latest FIFO mailbox and the recent massage will be discarded in case of OVERRUN
 * parameter: void
 * retval: void
 */
void HAL_CAN_RX_FIFO_LOCKING();
/*
 * brief: delocks the latest FIFO mailbox and the recent massage will be replace it in case of OVERRUN
 * parameter: void
 * retval: void
 */
void HAL_CAN_RX_FIFO_DELOCKING();
/*
 * @brief  Configures the CAN reception filter according to the specified
 *         parameters in the s_framexConfig structure.
 * @param  FRAMEX_CONFIG pointer to a s_framexConfig structure that
 *         contains the filter configuration information.
 * @retval None
 */
void HAL_CAN_FILTER_CONFIG(s_filterxConfig* FRAMEX_CONFIG);
/*
 * @brief       Receive frame from RX_FIFO Queue
 * @param  		RX_FIFO to specify which FIFO Queue to receive from
 * @in/out arg  RX_FRAME to store the received frame
 * @in/out arg	DATA[] array to store the data received
 * @retval None
 */
void HAL_CAN_psRXFRAME(S_CAN_RXFRAME* RX_FRAME, uint8_t DATA[],E_FILTER_ASSIGN RX_FIFO);
/*
 * brief: check the number of frames in RX_FIFO Queue
 * param: RX_FIFO the used FIFO Queue in the Receiver
 * in/out:FRAMES_NUM the returned value of stored frames in the RX_FIFO
 * retval: void
 */
void HAL_CAN_RX_FRAMES_NUM(E_FILTER_ASSIGN RX_FIFO,uint8_t* FRAMES_NUM);
/*
 * brief: TX transmission completion check
 * param: MAILBOX_CODE the mailbox number used to transmit the message
 * in/out:status is the returned status 1 for the completion/0 for the failure
 * retval: void
 */
void HAL_CAN_p8CHECK_TXCOMPLETION(uint8_t* status,uint8_t MAILBOX_CODE);
/*
 * brief: entering a debug mode(SILENT, LOOPBACK, LOOPBACK AND SILENT)
 * it enters the init mode and it needs to enter the normal mode to have access on the CAN bus
 * param: initConfig carries the required debug mode
 * retval: void
 */
void HAL_CAN_vDebugMode(S_CAN_INIT_CONFIG* initConfig);

#endif /* INC_CAN_INTERFACE_H_ */
