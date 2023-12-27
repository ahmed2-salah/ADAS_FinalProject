/*
 * CAN_PROGRAM.C
 * Created on: Nov 23, 2023
 * Author: MERNA MAGDY
 */

#include "CAN_Interface.h"


CAN_TypeDef*  CAN_INSTANCE= CAN1;	//ASSIGN CAN BASE ADDRESS


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
	while((READ_BIT(CAN_INSTANCE->MSR, CAN_MSR_INAK)>>CAN_MSR_INAK_Pos)==LOW);
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

void HAL_CAN_vDebugMode(S_CAN_INIT_CONFIG* initConfig)
{
	HAL_CAN_ENTER_INIT_MODE();
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
}

void HAL_CAN_vInit(S_CAN_INIT_CONFIG* initConfig,S_CAN_BITIME_CONFIG* bitime)
{
	HAL_CAN_ENTER_INIT_MODE();
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
	else
	{
		CLEAR_BIT(CAN_INSTANCE->MCR,CAN_MCR_TTCM);
	}
	HAL_CAN_vsetbiTime(bitime);
}

void HAL_CAN_start(void)
{
	//ENTER THE NORMAL MODE
	HAL_CAN_LEAVE_INIT_MODE();
	HAL_CAN_LEAVE_SLEEP_MODE();
}
void HAL_CAN_pu8TXFRAME(S_CAN_INIT_CONFIG* initConfig,S_CAN_TXFRAME* TX_FRAME, uint8_t DATA[], uint8_t* MAILBOX_CODE)
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
			CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TIR=(TX_FRAME->ID_TYPE)|((TX_FRAME->StdId)<<STDID_Pos)|((TX_FRAME->RTR)>>RTR_Pos);
		}
		else
		{
			SET_BIT(CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TIR,CAN_TI0R_IDE);
			CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TIR=((TX_FRAME->ExtId)>>EXTID_Pos)|((TX_FRAME->RTR)>>RTR_Pos);//fill all mailbox reigsters
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
		/* Request transmission */
        SET_BIT(CAN_INSTANCE->sTxMailBox[*MAILBOX_CODE].TIR, CAN_TI0R_TXRQ);

	}

}

void HAL_CAN_p8CHECK_TXCOMPLETION(uint8_t* status,uint8_t MAILBOX_CODE)
{	*status=1;
	if(MAILBOX_CODE==0)
	{
		while(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_RQCP0)==1UL);
		if(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TXOK0)!=1UL)
		{
			//TRANSMISSION FAILED
			*status=0;
			if(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_ALST0))
			{
				//ARBITRATION LOSS
			}
			if(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TERR0))
			{
				//Transmission error detection
			}
		}
	}
	else if(MAILBOX_CODE==1)
	{

		while(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_RQCP1)==1UL);
		if(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TXOK0)!=1UL)
		{	status=0;
			//TRANSMISSION FAILED
			if(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_ALST1))
			{
				//ARBITRATION LOSS
			}
			if(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TERR1))
			{
				//Transmission error detection
			}
		}
	}
	else if(MAILBOX_CODE==2)
	{
		while(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_RQCP0)==1UL);
		if(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TXOK0)!=1UL)
		{	status=0;
			//TRANSMISSION FAILED
			if(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_ALST0))
			{
				//ARBITRATION LOSS
			}
			if(READ_BIT(CAN_INSTANCE->TSR,CAN_TSR_TERR0))
			{
				//Transmission error detection
			}
		}

	}
	else
	{
		//parameter ERROR
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
	*pendingStatus=1;

	uint32_t MASK= CAN_TSR_TME0<<MAILBOX_CODE;

	if((READ_BIT(CAN_INSTANCE->TSR,MASK)>>(MAILBOX_CODE+CAN_TSR_TME0_Pos))!=0)
	{
		*pendingStatus=0;
	}
}

void HAL_CAN_RX_FIFO_LOCKING()
{
	SET_BIT(CAN_INSTANCE->MCR,CAN_MCR_RFLM);
}

void HAL_CAN_RX_FIFO_DELOCKING()
{
	CLEAR_BIT(CAN_INSTANCE->MCR,CAN_MCR_RFLM);
}
void HAL_CAN_FILTER_CONFIG(s_filterxConfig* FRAMEX_CONFIG)
{
	if(FRAMEX_CONFIG->filterBank<=13UL)
	{
		//FILTER BANK INDEX MASK
		uint32_t filterIndexMsk=1UL<<(FRAMEX_CONFIG->filterBank);

		/*****************************************************************************/
		//SET FINIT :FIFO INITIALIZATION MODE
		SET_BIT(CAN_INSTANCE->FMR,CAN_FMR_FINIT);
		//DE-ACTIVATE THE FILTER BANK
		CLEAR_BIT(CAN_INSTANCE->FA1R,filterIndexMsk);
		/*****************************************************************************/
		//SET FILTER MODE
		if(FRAMEX_CONFIG->filterxMode==MSK_MODE)
		{
			CLEAR_BIT(CAN_INSTANCE->FM1R,filterIndexMsk);
		}
		else if(FRAMEX_CONFIG->filterxMode==ID_MODE)
		{
			SET_BIT(CAN_INSTANCE->FM1R,filterIndexMsk);
		}
		else
		{
			//parameter ERROR
		}
		/*****************************************************************************/
		//SET FILTER SCALE

		if(FRAMEX_CONFIG->filterxScale==DUAL_16)
		{	//shift by HIGH<<5 in case of STD_ID
			//shift by
			CLEAR_BIT(CAN_INSTANCE->FS1R,filterIndexMsk);
			//assign mask or identifier code based on your assigned FILTRATION MODE
			CAN_INSTANCE->sFilterRegister[FRAMEX_CONFIG->filterBank].FR1=(((uint32_t)FRAMEX_CONFIG->MSG_ID_MASK_LOW&0X0000FFFF)<<16UL)|((uint32_t)FRAMEX_CONFIG->MSG_ID_LOW&0X0000FFFF);
			CAN_INSTANCE->sFilterRegister[FRAMEX_CONFIG->filterBank].FR2=(((uint32_t)FRAMEX_CONFIG->MSG_ID_MASK_HIGH&0X0000FFFF)<<16UL)|((uint32_t)FRAMEX_CONFIG->MSG_ID_HIGH&0X0000FFFF);

		}
		else if(FRAMEX_CONFIG->filterxScale==SINGLE_32)
		{	//shift by HIGH<<5 in case of STD_ID
			//shift by LOW<<3 in case of EXT_ID
			SET_BIT(CAN_INSTANCE->FS1R,filterIndexMsk);
			//assign mask or identifier code based on your assigned FILTRATION MODE
			CAN_INSTANCE->sFilterRegister[FRAMEX_CONFIG->filterBank].FR1=(((uint32_t)FRAMEX_CONFIG->MSG_ID_HIGH&0X0000FFFF)<<16UL)|((uint32_t)FRAMEX_CONFIG->MSG_ID_LOW&0X0000FFFF);
			CAN_INSTANCE->sFilterRegister[FRAMEX_CONFIG->filterBank].FR2=(((uint32_t)FRAMEX_CONFIG->MSG_ID_MASK_HIGH&0X0000FFFF)<<16UL)|((uint32_t)FRAMEX_CONFIG->MSG_ID_MASK_LOW&0X0000FFFF);
		}
		else
		{
			//param ERROR
		}
		/******************************************************************************/
		//FILTER BANK FIFO ASSIGNATION
		if(FRAMEX_CONFIG->filterxAssign==FIFO0)
		{
			CLEAR_BIT(CAN_INSTANCE->FFA1R,filterIndexMsk);
		}
		else if(FRAMEX_CONFIG->filterxAssign==FIFO1)
		{
			SET_BIT(CAN_INSTANCE->FFA1R,filterIndexMsk);
		}
		else
		{
			//param ERROR
		}
		/*******************************************************************************/
		//FILTER ACTIVATION
		SET_BIT(CAN_INSTANCE->FA1R,filterIndexMsk);
		//CLEAR FINIT TO EXIT FILTER INIT MODE
		CLEAR_BIT(CAN_INSTANCE->FMR,CAN_FMR_FINIT);
	}
	else
	{
		//parameter ERROR
	}
}

void HAL_CAN_psRXFRAME(S_CAN_RXFRAME* RX_FRAME, uint8_t DATA[],E_FILTER_ASSIGN RX_FIFO)
{

	RX_FRAME->ID_TYPE=(CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RIR)&CAN_RI0R_IDE;
	/*****************************************************************************************/
	if(RX_FRAME->ID_TYPE==STD_ID)
	{
		RX_FRAME->StdId=((CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RIR)&CAN_RI0R_STID)>>CAN_RI0R_STID_Pos;
	}
	else if(RX_FRAME->ID_TYPE==EXT_ID)
	{
		RX_FRAME->ExtId=((CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RIR)&CAN_RI0R_EXID)>>CAN_RI0R_EXID_Pos;
	}
	else
	{
		//parameter ERROR
	}
	/****************************************************************************************/

	RX_FRAME->RTR=((CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RIR)&CAN_RI0R_RTR)>>CAN_RI0R_RTR_Pos;

	/****************************************************************************************/

	RX_FRAME->DLC=((CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RDTR)&CAN_RDT0R_DLC)>>CAN_RDT0R_DLC_Pos;

	/****************************************************************************************/

	RX_FRAME->FILTER_BANK_INDEX=(((CAN_INSTANCE->sFIFOMailBox[RX_FIFO]).RDTR)&CAN_RDT0R_FMI)>>CAN_RDT0R_FMI_Pos;

	/*****************************************************************************************/

	DATA[0] = (uint8_t)((CAN_RDL0R_DATA0 & CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RDLR) >> CAN_RDL0R_DATA0_Pos);
	DATA[1] = (uint8_t)((CAN_RDL0R_DATA1 & CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RDLR) >> CAN_RDL0R_DATA1_Pos);
    DATA[2] = (uint8_t)((CAN_RDL0R_DATA2 & CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RDLR) >> CAN_RDL0R_DATA2_Pos);
    DATA[3] = (uint8_t)((CAN_RDL0R_DATA3 & CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RDLR) >> CAN_RDL0R_DATA3_Pos);
    DATA[4] = (uint8_t)((CAN_RDH0R_DATA4 & CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RDHR) >> CAN_RDH0R_DATA4_Pos);
    DATA[5] = (uint8_t)((CAN_RDH0R_DATA5 & CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RDHR) >> CAN_RDH0R_DATA5_Pos);
    DATA[6] = (uint8_t)((CAN_RDH0R_DATA6 & CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RDHR) >> CAN_RDH0R_DATA6_Pos);
    DATA[7] = (uint8_t)((CAN_RDH0R_DATA7 & CAN_INSTANCE->sFIFOMailBox[RX_FIFO].RDHR) >> CAN_RDH0R_DATA7_Pos);

    /******************************************************************************************/

    if(RX_FIFO==FIFO0)
    {
    	SET_BIT(CAN_INSTANCE->RF0R, CAN_RF0R_RFOM0);
    }
    else if(RX_FIFO==FIFO1)
    {
    	SET_BIT(CAN_INSTANCE->RF1R, CAN_RF1R_RFOM1);
    }
    else
    {
    	//parameter ERROR
    }
}

void HAL_CAN_RX_FRAMES_NUM(E_FILTER_ASSIGN RX_FIFO,uint8_t* FRAMES_NUM)
{
	*FRAMES_NUM=0;
	if(RX_FIFO==FIFO0)
	{
		*FRAMES_NUM = CAN_INSTANCE->RF0R & CAN_RF0R_FMP0;
	}
	else if(RX_FIFO==FIFO1)
	{
		*FRAMES_NUM = CAN_INSTANCE->RF1R & CAN_RF1R_FMP1;
	}
	else
	{
		//parameter ERROR
	}
}

/*
 * YOU HAVE 3 CAN_RX INTERRUPTS
 * 1. FIFO STORAGE
 * 2. FIFO FULL
 * 3. OVERRUN
 */
