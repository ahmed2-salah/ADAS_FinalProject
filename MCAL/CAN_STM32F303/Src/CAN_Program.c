/*
 * CAN_PROGRAM.C
 * Created on: Nov 23, 2023
 * Author: MERNA MAGDY
 */

#include "CAN_Interface.h"


CAN_TypeDef*  CAN_INSTANCE= CAN;	//ASSIGN CAN BASE ADDRESS


void HAL_CAN_ENTER_SLEEP_MODE(void)
{
	SET_BIT(CAN_INSTANCE->MCR,CAN_MCR_SLEEP);
	while((READ_BIT(CAN_INSTANCE->MSR,CAN_MSR_SLAK)>>CAN_MSR_SLAK_Pos)==LOW);
}



void HAL_CAN_LEAVE_SLEEP_MODE(void)
{
	CLEAR_BIT(CAN_INSTANCE->MCR,CAN_MCR_SLEEP);
	while((READ_BIT(CAN_INSTANCE->MSR,CAN_MSR_SLAK)>>CAN_MSR_SLAK_Pos)==HIGH);
}



void HAL_CAN_ENTER_INIT_MODE(void)
{

	//for software initialization
	SET_BIT(CAN_INSTANCE->MCR,CAN_MCR_INRQ);//SET INREQ BIT
	//WAIT FOR THE FLAG RAISING
	while((READ_BIT(CAN_INSTANCE->MSR, CAN_MSR_INAK)>>CAN_MSR_INAK)==LOW);
	//LEAVE SLEEP MODE
	HAL_CAN_LEAVE_SLEEP_MODE();

	//ALL MASSAGES TO AND FROM THE CAN BUS ARE STOPPED
	//OUTPUT OF CANTX=1	RECESSIVE
}



void HAL_CAN_LEAVE_INIT_MODE(void)
{
	CLEAR_BIT(CAN_INSTANCE->MCR,CAN_MCR_INRQ);//CLEAR INREQ BIT
	//WAIT FOR THE FLAG TO FALL
	while((READ_BIT(CAN_INSTANCE->MSR, CAN_MSR_INAK)>>CAN_MSR_INAK_Pos)==HIGH);
}



void HAL_CAN_vsetbiTime(S_CAN_BITIME_CONFIG* bitime)
{
	//HAL_CAN_ENTER_INIT_MODE();
	WRITE_REG(CAN_INSTANCE->BTR,((CAN_INSTANCE->BTR&0XFF000000)|(uint32_t)(bitime->prescaler<<CAN_BTR_BRP_Pos)|(uint32_t)(bitime->TS1_Qunata<<CAN_BTR_TS1_Pos)|(uint32_t)(bitime->TS2_Qunata<<CAN_BTR_TS2_Pos)));
};



void HAL_CAN_vInit(S_CAN_INIT_CONFIG* initConfig)
{
	switch((initConfig->debugMode))
	{
	case SILENT_MODE:SET_BIT(CAN_INSTANCE->BTR,CAN_BTR_SILM);
		   CLEAR_BIT(CAN_INSTANCE->BTR,CAN_BTR_LBKM);
		   break;
	case LOOPBACK_MODE:CLEAR_BIT(CAN_INSTANCE->BTR,CAN_BTR_SILM);
		   SET_BIT(CAN_INSTANCE->BTR,CAN_BTR_LBKM);
		   break;
	case LOOPBACK_SILENT_MODE:SET_BIT(CAN_INSTANCE->BTR,CAN_BTR_SILM);
		   SET_BIT(CAN_INSTANCE->BTR,CAN_BTR_LBKM);
		   break;
	default:
			break;
	}
/**************************************************************/
	if(!initConfig->IDENTIFIER_PRIORITY)//FIFO Priority
	{
		SET_BIT(CAN_INSTANCE->MCR, CAN_MCR_TXFP);
	}
	else
	{
		CLEAR_BIT(CAN_INSTANCE->MCR, CAN_MCR_TXFP);
	}
/**************************************************************/

	if(!initConfig->AUTO_RETRANSMISSION)
	{
		SET_BIT(CAN_INSTANCE->MCR, CAN_MCR_NART);
	}
	else
	{
		CLEAR_BIT(CAN_INSTANCE->MCR, CAN_MCR_NART);
	}
/*************************************************************/
	if(initConfig->AUTO_BUSOFF_RECOVERY)
	{
		SET_BIT(CAN_INSTANCE->MCR,CAN_MCR_ABOM);
	}
	else
	{
		CLEAR_BIT(CAN_INSTANCE->MCR,CAN_MCR_ABOM);
	}
/************************************************************/
	if(initConfig->AUTO_WAKEUP_MODE)
	{
		SET_BIT(CAN_INSTANCE->MCR,CAN_MCR_AWUM);
	}
	else
	{
		CLEAR_BIT(CAN_INSTANCE->MCR,CAN_MCR_AWUM);
	}
/*************************************************************/
	if(initConfig->TIME_TRIG_COM==ENABLE)
	{
		SET_BIT(CAN_INSTANCE->MCR,CAN_MCR_TTCM);
	}
}




void HAL_CAN_pu8TXFRAME(S_CAN_INIT_CONFIG* initConfig,S_CAN_TXFRAME* TX_FRAME, uint32_t DATA[], uint8_t* MAILBOX_CODE)
{
	//CHECK IF ANY MAILBOX IS EMPTY
	if((READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TME0)>>CAN_TSR_TME0_Pos)||(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TME1)>>CAN_TSR_TME1_Pos)||(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TME2)>>CAN_TSR_TME2_Pos))
	{
		//READ 2 MAILBOX CODE BITS
		*MAILBOX_CODE=(CAN_INSTANCE->TSR & CAN_TSR_CODE)>>CAN_TSR_CODE_Pos;

		/******************************************************************************************************************/
		//CHECK ID TYPE
		if(TX_FRAME->ID_TYPE==STD_ID)
		{
			//fill all mailbox registers
			CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TIR=(TX_FRAME->ID_TYPE)|(TX_FRAME->StdId)|(TX_FRAME->RTR);
		}
		else
		{
			SET_BIT(CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TIR,CAN_TI0R_IDE);
			CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TIR=(TX_FRAME->ExtId)|(TX_FRAME->RTR);//fill all mailbox reigsters
		}
		/*****************************************************************************************************************/

		//SET DATA LENGTH
		CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TDTR=(TX_FRAME->DLC & CAN_TDT0R_DLC);

		/*****************************************************************************************************************/

		/* Set up the Transmit Global Time mode ONLY IN TIME TRIGGERED COMMUNICATION MODE WITH DLC=8 BYTES*/
		if((TX_FRAME->GLOBAL_TRANSMISSION==ENABLE)||(initConfig->TIME_TRIG_COM==ENABLE)||TX_FRAME->DLC==8UL)
		{
			SET_BIT(CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TDTR,CAN_TDT1R_TGT);
		}
		else
		{
			CLEAR_BIT(CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TDTR,CAN_TDT1R_TGT);
		}

		/******************************************************************************************************************/
		 /* INCLUDE the PRELOAD DATA */
		//HIGHER BYTES
		      WRITE_REG(CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TDHR,
		                ((uint32_t)DATA[7] << CAN_TDH0R_DATA7_Pos) |
		                ((uint32_t)DATA[6] << CAN_TDH0R_DATA6_Pos) |
		                ((uint32_t)DATA[5] << CAN_TDH0R_DATA5_Pos) |
		                ((uint32_t)DATA[4] << CAN_TDH0R_DATA4_Pos));
	    //LOWER BYTES
		      WRITE_REG(CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TDLR,
		                ((uint32_t)DATA[3] << CAN_TDL0R_DATA3_Pos) |
		                ((uint32_t)DATA[2] << CAN_TDL0R_DATA2_Pos) |
		                ((uint32_t)DATA[1] << CAN_TDL0R_DATA1_Pos) |
		                ((uint32_t)DATA[0] << CAN_TDL0R_DATA0_Pos));
		/******************************************************************************************************************/
	}

}



void HAL_CAN_vAbortTXRQ(uint8_t MAILBOX_CODE)
{
	if(MAILBOX_CODE==0)
	{
		/* Add cancellation request for Tx Mailbox 0 */
	    SET_BIT(CAN_INSTANCE->TSR, CAN_TSR_ABRQ0);
	}
	else if(MAILBOX_CODE==1)
	{
		/* Add cancellation request for Tx Mailbox 1 */
		SET_BIT(CAN_INSTANCE->TSR, CAN_TSR_ABRQ1);
	}
	else if(MAILBOX_CODE==2)
	{
		/* Add cancellation request for Tx Mailbox 2 */
		SET_BIT(CAN_INSTANCE->TSR, CAN_TSR_ABRQ2);
	}
	else
	{

	}
}



void HAL_CAN_u8GetFreeMailbox(uint8_t* FREE_MAILBOX_COUNT)
{
	*FREE_MAILBOX_COUNT=0;	/*FREE_MAILBOX_COUNT is an in/out argument*/
	if((READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TME0)>>CAN_TSR_TME0_Pos)!=0)
	{
		*FREE_MAILBOX_COUNT++;
	}
	if((READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TME1)>>CAN_TSR_TME1_Pos)!=0)
	{
		*FREE_MAILBOX_COUNT++;
	}
	if((READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TME2)>>CAN_TSR_TME2_Pos)!=0)
	{
		*FREE_MAILBOX_COUNT++;
	}
}



void HAL_CAN_u8IS_TXFRAME_PENDING(uint8_t* pendingStatus,uint8_t MAILBOX_CODE)
{
	*pendingStatus=0;

	uint32_t MASK= CAN_TSR_TME0<<MAILBOX_CODE;

	if((READ_BIT(CAN_INSTANCE->TSR,MASK)>>(MAILBOX_CODE+CAN_TSR_TME0_Pos))!=0)
	{
		*pendingStatus=1;
	}
}


