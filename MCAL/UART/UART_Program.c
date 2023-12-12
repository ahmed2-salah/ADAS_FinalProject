/*******************************************************************************
 * Filename              :   UART_Program.c
 * Author                :   Hassan_Elgabas
 * Origin Date           :   Aug 16, 2023
 * Version               :   1.0.0
 * Compiler              :   GCC ARM Embedded Toolchain
 * Target                :
 * Notes                 :   None
 **
 *******************************************************************************/
/************************ SOURCE REVISION LOG *********************************
 *
 *    Date    Version   Author             Description
 *  14/10/20   1.0.0   Mohamemd Waleed   Initial Release.
 *
 *******************************************************************************/

/*==============================================================================================================================================
 * Includes
 *==============================================================================================================================================*/
#include <stdint.h>
#include "STM32F446xx.h"
#include "ErrTypes.h"
#include "UART_Interface.h"
#include "UART_Private.h"

/*==============================================================================================================================================
 * GLOBAL VARIABLES SECTION
 *==============================================================================================================================================*/
/* Array Of Pointers To UART Registers */
static USART_Reg_t *UART[UARTNUMBER] = {USART1, USART2, USART3, UART4, UART5, USART6};

static void (*UART_PTR_TO_FUNC[UARTNUMBER][FlagsNumber])(void) = {NULL};

static uint8_t UART_RecieveBufferFlag[UARTNUMBER] = {0};

static uint8_t UART_RecieveBufferSize[UARTNUMBER] = {0};

static uint16_t *UART_RecievedBufferIT[UARTNUMBER] = {0};

static uint16_t *UART_RecievedBuffer[UARTNUMBER] = {0};
uint8_t * FLAGGG=NULL;
/*==============================================================================================================================================
 * FUNCTION DEFINITION SECTION
 *==============================================================================================================================================*/
/*==============================================================================================================================================
 *@fn      : USART_voidReadFlag
 *@brief  : This function is used to read the status of a specific flag
 *@paramter[in]  : UART_ID_t UART_ID : ID of the UART peripheral
 *paramter[in]   : USART_Flag_t Flag : Flag to be read
 *@retval uint8_t : Status of the flag
 *==============================================================================================================================================*/
uint8_t UART_ReadFlag(UART_ID_t UART_ID, USART_Flag_t Flag)
{
	/* Read Flag & return it */
	return ((UART[UART_ID]->SR >> Flag) & 1);
}
/*==============================================================================================================================================
 *@fn      : UART_voidInit
 *@brief  : This function is used to initialize the UART peripheral
 *@paramter[in]  : UART_Config_t *UART_Config
 *@retval void
 *==============================================================================================================================================*/
void UART_voidInit(UART_Config_t *UART_Config)
{
	/* Enabling UART */
	UART[UART_Config->UART_ID]->CR1 |= (UART_Enable << USART_UE);

	/* Setting Baud Rate */
	UART_SettingBaudRate(UART_Config);

	/* Setting Word Lenght */
	UART[UART_Config->UART_ID]->CR1 &= ~(OneBitMasking << USART_M);
	UART[UART_Config->UART_ID]->CR1 |= ((UART_Config->WordLength) << USART_M);

	/* Setting Parity State */
	UART[UART_Config->UART_ID]->CR1 &= ~(OneBitMasking << USART_PCE);
	UART[UART_Config->UART_ID]->CR1 |= ((UART_Config->ParityState) << USART_PCE);

	/* Parity Selection */
	UART[UART_Config->UART_ID]->CR1 &= ~(OneBitMasking << USART_PS);
	UART[UART_Config->UART_ID]->CR1 |= ((UART_Config->Parity) << USART_PS);

	/* Setting Stop Bits*/
	UART[UART_Config->UART_ID]->CR2 &= ~(TwoBitMasking << USART_STOP);
	UART[UART_Config->UART_ID]->CR2 |= ((UART_Config->StopBits) << USART_STOP);

	/* Setting Over Sampling */
	UART[UART_Config->UART_ID]->CR2 &= ~(OneBitMasking << USART_OVER8);
	UART[UART_Config->UART_ID]->CR2 |= ((UART_Config->OverSampling) << USART_OVER8);

	/* Setting UART Interrupts */
	UART_voidInterruptConfig(UART_Config);
	/* Setting Direction */
	UART[UART_Config->UART_ID]->CR1 &= ~(TwoBitMasking << USART_RE);
	UART[UART_Config->UART_ID]->CR1 |= ((UART_Config->Direction) << USART_RE);
}

/*==============================================================================================================================================
 *@fn    : UART_SettingBaudRate
 *@brief  : This function is used to set the baud rate of the UART peripheral
 *@paramter[in]  : UART_Config_t *UART_Config
 *@retval void
 *==============================================================================================================================================*/
void UART_SettingBaudRate(UART_Config_t *UART_Config)
{
	float USART_DIV = 0;

	uint32_t DIV_Fraction = 0;

	UART[UART_Config->UART_ID]->BRR = 0;

	/* BaudRate Equation */
	USART_DIV = Clock_Freq / (float)(8U * (2U - UART_Config->OverSampling) * UART_Config->BaudRate);
	USART_DIV *= 1000UL;

	/* Set the Mantissa Part */
	UART[UART_Config->UART_ID]->BRR |= ((uint32_t)USART_DIV / 1000UL) << USART_DIV_MANTISSA;

	/* Calculte the Fraction */
	DIV_Fraction = (uint32_t)USART_DIV % 1000UL;

	DIV_Fraction = DIV_Fraction * (16 / (UART_Config->OverSampling + 1));

	/* get Round */
	DIV_Fraction += 500UL;

	UART[UART_Config->UART_ID]->BRR |= (uint32_t)(DIV_Fraction / 1000UL) << USART_DIV_FRACTION;
}
/*==============================================================================================================================================
 *@fn      : UART_voidInterruptConfig
 *@brief  : This function is used to configure the interrupts of the UART peripheral
 *@paramter[in]  :  UART_Config_t *UART_Config
 *@retval void
 *==============================================================================================================================================*/
void UART_voidInterruptConfig(UART_Config_t *UART_Config)
{
	/* Clearing Interrupt Bits */
	UART[UART_Config->UART_ID]->CR1 &= ~(FiveBitMasking << USART_IDLEIE);
	/* Setting Interrupt Bits */
	/* Setting IDLE Interrupt */
	UART[UART_Config->UART_ID]->CR1 |= ((UART_Config->Interrupts->IDLE) << USART_IDLEIE);
	/* Setting RXNE Interrupt */
	UART[UART_Config->UART_ID]->CR1 |= ((UART_Config->Interrupts->RXN) << USART_RXNEIE);
	/* Setting TC Interrupt */
	UART[UART_Config->UART_ID]->CR1 |= ((UART_Config->Interrupts->TC) << USART_TCIE);
	/* Setting TXE Interrupt */
	UART[UART_Config->UART_ID]->CR1 |= ((UART_Config->Interrupts->TX) << USART_TXEIE);
	/* Setting PE Interrupt */
	UART[UART_Config->UART_ID]->CR1 |= ((UART_Config->Interrupts->PE) << USART_PEIE);
}

/*==============================================================================================================================================
 *@fn      : UART_voidTransmit
 *@brief  : This is a asynchronus function used to transmit data  through UART peripheral
 *@paramter[in]  : u16 Copy_u16Data
 *@retval void
 *==============================================================================================================================================*/
void UART_voidTransmitData(UART_Config_t *UART_Config, uint16_t Copy_u16Data)
{
	/* Making sure that data regste is empty */
	while (((UART[UART_Config->UART_ID]->SR >> TXE_Flage) & 1) == 0)
		;
	/*Setting Data to be Transfered */
	UART[UART_Config->UART_ID]->DR = Copy_u16Data;
	/*Waiting for Data to be transfered */
	while (((UART[UART_Config->UART_ID]->SR >> TC_Flage) & 1) == 0)
		;
}
/*==============================================================================================================================================
 *@fn      : UART_u16Receive
 *@brief  :  This is a asynchronus function used to receive data  through UART peripheral
 *@paramter[in]  : void
 *@retval u16
 *==============================================================================================================================================*/
uint16_t UART_u16Receive(UART_Config_t *UART_Config)
{

	/* Wait for data to be transfered from other device*/
	while (((UART[UART_Config->UART_ID]->SR >> RXNE_Flage) & 1) == 0)
		;
	/* Returning Data from Data register */
	return UART[UART_Config->UART_ID]->DR;
}
/*==============================================================================================================================================
 *@fn      : UART_voidTransmitIT
 *@brief  :  This is a function used to receive data through UART peripheral using interrupts
 * *@paramter[in]  : UART_Config_t *UART_Config
 *@retval u16
 *==============================================================================================================================================*/
void UART_u16ReceiveIT(UART_Config_t *UART_Config, uint8_t * copy_flag)
{


	/*klabii*/
	FLAGGG=copy_flag;
	/* Enabling Read Data Register Not Empty Interrupt */
	UART[UART_Config->UART_ID]->CR1 |= (1 << USART_RXNEIE);
}
/*==============================================================================================================================================
 *@fn    USART_voidRecieveBuffer
 *@brief  This function is used to receive a string through UART peripheral using polling
 *@paramter[in]  Copy_p8Buffer : Pointer to the Buffer which the received string will be written to
 *@paramter[in]  Copy_u8BufferSize : The Size of the Buffer
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidRecieveBuffer(UART_Config_t *UART_Config, uint8_t *Copy_p8Buffer, uint16_t Copy_u8BufferSize)
{

	/* Local Variable to hold the counter */
	uint16_t Local_u8Counter = 0;

	/* Looping on the buffer */
	for (Local_u8Counter = 0; Local_u8Counter < Copy_u8BufferSize; Local_u8Counter++)
	{

		/* Receiving Data */
		Copy_p8Buffer[Local_u8Counter] = UART_u16Receive(UART_Config);
	}
}
/*==============================================================================================================================================
 *@fn    USART_voidTransmitBuffer
 *@brief  This function is used to transmit a string through UART peripheral using polling
 *@paramter[in]  Copy_p8Buffer : Pointer to the Buffer which the string will be transmitted from
 *@paramter[in]  Copy_u8BufferSize : The Size of the Buffer
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidTransmitBuffer(UART_Config_t *UART_Config, uint16_t *Copy_p8Buffer, uint16_t Copy_u8BufferSize)
{

	/* Local Variable to hold the counter */
	uint16_t Local_u8Counter = 0;

	/* Looping on the buffer */
	for (Local_u8Counter = 0; Local_u8Counter < Copy_u8BufferSize; Local_u8Counter++)
	{

		/* Transmitting Data */
		UART_voidTransmitData(UART_Config, Copy_p8Buffer[Local_u8Counter]);
	}
}
/*==============================================================================================================================================
 *@fn    UART_VoidEnableDMATransmit
 *@brief   This function is used to enable the DMA for the UART peripheral
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_VoidEnableDMATransmit(UART_Config_t *UART_Config)
{
	/* Enabling DMA for Transmit */
	UART[UART_Config->UART_ID]->CR3 |= (1 << USART_DMAT);
}
/*==============================================================================================================================================
 *@fn    UART_VoidEnableDMAReciver
 *@brief   This function is used to enable the DMA for the UART peripheral
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_VoidEnableDMAReciver(UART_Config_t *UART_Config)
{
	/* Enabling DMA for Recieving */
	UART[UART_Config->UART_ID]->CR3 |= (1 << USART_DMAR);
}
/*==============================================================================================================================================
 *@fn    USART_voidRecieveBufferIR
 *@brief  This function is used to receive a string through UART peripheral using interrupts
 *@paramter[in]  Copy_p8Buffer : Pointer to the Buffer which the received string will be written to
 *@paramter[in]  Copy_u8BufferSize : The Size of the Buffer
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidRecieveBufferIT(UART_Config_t *UART_Config, uint16_t *Copy_p8Buffer, uint16_t Copy_u8BufferSize, void (*pv_CallBackFunc)(void))
{
	UART_RecieveBufferFlag[UART_Config->UART_ID] = 1;

	UART_RecieveBufferSize[UART_Config->UART_ID] = Copy_u8BufferSize;

	/* Setting CallBack Function */
	UART_PTR_TO_FUNC[UART_Config->UART_ID][RXN] = pv_CallBackFunc;

	/* Setting the Buffer */
	UART_RecievedBuffer[UART_Config->UART_ID] = Copy_p8Buffer;

	/* Enabling Read Data Register Not Empty Interrupt */
	UART[UART_Config->UART_ID]->CR1 |= (1 << USART_RXNEIE);
}

/*==============================================================================================================================================
 *@fn    USART_voidTransmitBuffer
 *@brief  This function is used to transmit a string through UART peripheral using interrupts
 *@paramter[in]  Copy_p8Buffer : Pointer to the Buffer which the string will be transmitted from
 *@paramter[in]  Copy_u8BufferSize : The Size of the Buffer
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidTransmitBufferIT(UART_Config_t *UART_Config, uint16_t *Copy_p8Buffer, uint16_t Copy_u8BufferSize);


/*==============================================================================================================================================
 *@fn    UART_HANDLE_IT
 *@brief  This function is used to Handle Interrupts
 *@paramter[in] UARTNumber : UART Number Needed To Be Handled
 *@retval void
 *@note  This Function is Private
 *==============================================================================================================================================*/
static void UART_HANDLE_IT( UART_ID_t UARTNumber )
{
	/* Comming from UART_ReciveBufferIT*/
		if ((UART_ReadFlag(UARTNumber, RXNE_Flage) == 1) && UART_RecieveBufferFlag[UARTNumber] == 1)
		{
			static uint8_t FlagCounter = 0;

			/* Reading Data */
			UART_RecievedBufferIT[UARTNumber][FlagCounter++] = UART[UARTNumber]->DR;

			if (FlagCounter == UART_RecieveBufferSize[UARTNumber])
			{
				/* Disabling Read Data Register Not Empty Interrupt */
				UART_RecieveBufferFlag[UARTNumber] = 0;

				UART[UARTNumber]->CR1 &= ~(1 << USART_RXNEIE);

				/* Calling the CallBack Function */
				UART_PTR_TO_FUNC[UARTNumber][RXNE_Flage]();
			}
		}

		/* Comming From UART_RecieBuffer*/
		if ((UART_ReadFlag(UARTNumber, RXNE_Flage) == 1))
		{
			*UART_RecievedBuffer[UARTNumber] = UART[UARTNumber]->DR;

			UART[UARTNumber]->CR1 &= ~(1 << USART_RXNEIE);

			/* Calling the CallBack Function */
			UART_PTR_TO_FUNC[UARTNumber][RXN]();
		}
		/* Transmission Complete */
		if (UART_ReadFlag(UARTNumber, TC_Flage) == 1)
		{
			/* Clearing the TC Flag */
			UART[UARTNumber]->SR &= ~(1 << TC_Flage);

			/* Calling the CallBack Function */
			UART_PTR_TO_FUNC[UARTNumber][TC_Flage]();
		}
		/* Transmit Data Register Empty */
		if (UART_ReadFlag(UARTNumber, TXE_Flage) == 1)
		{
			/* Clearing the TXE Flag */
			UART[UARTNumber]->SR &= ~(1 << TXE_Flage);

			/* Calling the CallBack Function */
			UART_PTR_TO_FUNC[UARTNumber][TXE_Flage]();
		}

		/* Overrun Error */
		if (UART_ReadFlag(UARTNumber, ORE_Flage) == 1)
		{
			/* Clearing the ORE Flag */
			UART[UARTNumber]->SR &= ~(1 << ORE_Flage);

			/* Calling the CallBack Function */
			UART_PTR_TO_FUNC[UARTNumber][ORE_Flage]();
		}

		/* Framing Error */
		if (UART_ReadFlag(UARTNumber, FE_Flage) == 1)
		{
			/* Clearing the FE Flag */
			UART[UARTNumber]->SR &= ~(1 << FE_Flage);

			/* Calling the CallBack Function */
			UART_PTR_TO_FUNC[UARTNumber][FE_Flage]();
		}
		/* Noise Error */
		if (UART_ReadFlag(UARTNumber, NF_Flage) == 1)
		{
			/* Clearing the NE Flag */
			UART[UARTNumber]->SR &= ~(1 << NF_Flage);

			/* Calling the CallBack Function */
			UART_PTR_TO_FUNC[UARTNumber][NF_Flage]();
		}

		/* Parity Error */
		if (UART_ReadFlag(UARTNumber, PE_Flage) == 1)
		{
			/* Clearing the PE Flag */
			UART[UARTNumber]->SR &= ~(1 << PE_Flage);

			/* Calling the CallBack Function */
			UART_PTR_TO_FUNC[UARTNumber][PE_Flage]();
		}
}

/*
 * @function 		:	USART_SendStringPolling
 * @brief			:	Send String using USART
 * @param			:	String
 * @retval			:	Error State
 */
Error_State_t USART_SendStringPolling(uint8_t USART_Num , const char* String)
{
	Error_State_t Error_State = OK;
	uint16_t Counter=0;
	if (NULL != String)
	{
		while (String[Counter] != '\0')
		{
			if ((USART_Num >= 0) && (USART_Num <= 5))
			{
				/*wait till DR is Empty*/
				while (!(GET_BIT(UART[USART_Num]->SR,TXE_Flage)));
				/*Store data in the DR Register*/
				UART[USART_Num]->DR = String[Counter];
				/*wait till Transmission is complete*/
				while (!(GET_BIT(UART[USART_Num]->SR,TC_Flage)));
			}
			else {
				Error_State = USART_WRONG_NUMBER;
				break;
			}
			Counter++;
		}
	}
	else {
		Error_State = Null_Pointer;
	}
	return Error_State ;
}

/*==============================================================================================================================================
 * ISR
 *==============================================================================================================================================*/
/* UART1 ISR */
void USART1_IRQHandler(void)
{
	*FLAGGG=UART[0]->DR;
}
/* UART2 ISR */
void USART2_IRQHandler(void)
{

	  UART_HANDLE_IT(UART_2) ;

}
/* UART3 ISR */
void USART3_IRQHandler(void)
{
	UART_HANDLE_IT(UART_3);
}
/* UART4 ISR */
void UART4_IRQHandler(void)
{
	UART_HANDLE_IT(UART_4);
}
/* UART5 ISR */
void UART5_IRQHandler(void)
{
	UART_HANDLE_IT(UART_5);
}
/* UART6 ISR */
void USART6_IRQHandler(void)
{
	UART_HANDLE_IT(UART_6);
}
