/*******************************************************************************
 * Filename              :   UART_Interface.h
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
#ifndef UART_INCLUDE_UART_INTERFACE_H_
#define UART_INCLUDE_UART_INTERFACE_H_

/*==============================================================================================================================================
 * Enums Declaration
 *==============================================================================================================================================*/

typedef enum
{
	UART_1 = 0, // UART 1
	UART_2,		// UART 2
	UART_3,		// UART 3
	UART_4,		// UART 4
	UART_5,		// UART 5
	UART_6,		// UART 6
} UART_ID_t;
typedef enum
{
	OverSamplingBy16 = 0, // Over Sampling By 16
	OverSamplingBy8 = 1,  // Over Sampling By 8
} OverSampling_t;

typedef enum
{
	R_X = 1,   // Receive Mode
	T_X = 2,   // Transmit Mode
	RX_TX = 3, // Receive and Transmit Mode
} Direction_t;

typedef enum
{
	_8Data = 0, // 8 Data Bits
	_9Data = 1, // 9 Data Bits
} WordLength_t;

typedef enum
{
	EvenParity = 0, // Even Parity
	OddParity = 1,	// Odd Parity
} ParitySelection_t;
typedef enum
{
	UART_Disable = 0, // Disable
	UART_Enable,	  // Enable
} UART_InitialeState_t;

typedef enum
{
	OneStopBit = 0,	   // One Stop Bit
	HalfStopBit,	   // Half Stop Bit
	TwoStopBit,		   // Two Stop Bit
	OneAndHalfStopBit, // One And Half Stop Bit
} StopBits_t;

typedef enum
{
	BaudRate_2400 = 2400UL,		// Baud Rate 2400
	BaudRate_4800 = 4800UL,		// Baud Rate 4800
	BaudRate_9600 = 9600UL,		// Baud Rate 9600
	BaudRate_14400 = 14400UL,	// Baud Rate 14400
	BaudRate_19200 = 19200UL,	// Baud Rate 19200
	BaudRate_28800 = 28800UL,	// Baud Rate 28800
	BaudRate_38400 = 38400UL,	// Baud Rate 38400
	BaudRate_57600 = 57600UL,	// Baud Rate 57600
	BaudRate_76800 = 76800UL,	// Baud Rate 76800
	BaudRate_115200 = 115200UL, // Baud Rate 115200
	BaudRate_230400 = 230400UL, // Baud Rate 230400
	BaudRate_250000 = 250000UL, // Baud Rate 250000
} BaudRate_t;
typedef enum
{
	PE,
	TX,
	TC,
	RXN,
	IDLE,
} Interrupts_t;
typedef enum
{
	PE_Flage = 0, /* Parity Error Flag*/
	FE_Flage,	  /* Framing Error Flag*/
	NF_Flage,	  /* Noise Error Flag*/
	ORE_Flage,	  /* OverRun Error Flag*/
	IDLE_Flage,	  /* IDLE Line Detected Flag*/
	RXNE_Flage,	  /* Read Data Register Not Empty Flag*/
	TC_Flage,	  /* Transmission Complete Flag*/
	TXE_Flage,	  /* Transmit Data Register Empty Flag*/
	LBD_Flage,	  /* LIN Break Detection Flag*/
	CTS_Flage,	  /* CTS Flag*/
} USART_Flag_t;
/*==============================================================================================================================================
 * Structs Declaration
 *==============================================================================================================================================*/
typedef struct
{
	UART_InitialeState_t PE;   // Parity Error
	UART_InitialeState_t TX;   // Transmit Data Register Empty
	UART_InitialeState_t TC;   // Transmission Complete
	UART_InitialeState_t RXN;  // Read Data Register Not Empty
	UART_InitialeState_t IDLE; // IDLE Line Detected
} UART_Interrupts_t;

typedef struct
{
	UART_ID_t UART_ID;				  // UART ID
	BaudRate_t BaudRate;			  // Baud Rate
	WordLength_t WordLength;		  // Word Length
	UART_InitialeState_t ParityState; // Parity State
	StopBits_t StopBits;			  // Stop Bits
	ParitySelection_t Parity;		  // Parity
	Direction_t Direction;			  // Direction
	OverSampling_t OverSampling;	  // Over Sampling
	UART_Interrupts_t *Interrupts;	  // Interrupts
} UART_Config_t;

/*==============================================================================================================================================
 * Function Prototypes
 *==============================================================================================================================================*/
/*==============================================================================================================================================
 *@fn      : USART_voidReadFlag
 *@brief  : This function is used to read the status of a specific flag
 *@paramter[in]  : UART_ID_t UART_ID : ID of the UART peripheral
 *paramter[in]   : USART_Flag_t Flag : Flag to be read
 *@retval uint8_t : Status of the flag
 *==============================================================================================================================================*/
uint8_t UART_ReadFlag(UART_ID_t UART_ID, USART_Flag_t Flag);
/*==============================================================================================================================================
 *@fn      : UART_voidInit
 *@brief  : This function is used to initialize the UART peripheral
 *@paramter[in]  : UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidInit(UART_Config_t *UART_Config);

/*==============================================================================================================================================
 *@fn    : UART_SettingBaudRate
 *@brief  : This function is used to set the baud rate of the UART peripheral
 *@paramter[in]  : UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_SettingBaudRate(UART_Config_t *UART_Config);
/*==============================================================================================================================================
 *@fn      : UART_voidTransmit
 *@brief  : This is a function used to transmit data through UART peripheral
 *@paramter[in]  : u16 Copy_u16Data : Data to be transmitted
 *@paramter[in]  : UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidTransmitData(UART_Config_t *UART_Config, uint16_t Copy_u16Data);

/*==============================================================================================================================================
 *@fn      : UART_u16Receive
 *@brief  :  This is a function used to receive data through UART peripheral
 * *@paramter[in]  : UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval u16
 *==============================================================================================================================================*/
uint16_t UART_u16Receive(UART_Config_t *UART_Config);

/*==============================================================================================================================================
 *@fn      : UART_voidInterruptConfig
 *@brief  : This function is used to configure the interrupts of the UART peripheral
 *@paramter[in]  : UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidInterruptConfig(UART_Config_t *UART_Config);
/*==============================================================================================================================================
 *@fn      : UART_voidTransmitIT
 *@brief  :  This is a function used to receive data through UART peripheral using interrupts
 * *@paramter[in]  : UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval u16
 *==============================================================================================================================================*/
void UART_u16ReceiveIT(UART_Config_t *UART_Config, uint8_t * copy_flag);
/*==============================================================================================================================================
 *@fn    USART_voidRecieveBuffer
 *@brief  This function is used to receive a string through UART peripheral using polling
 *@paramter[in]  Copy_p8Buffer : Pointer to the Buffer which the received string will be written to
 *@paramter[in]  Copy_u8BufferSize : The Size of the Buffer
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidRecieveBuffer(UART_Config_t *UART_Config, uint8_t *Copy_p8Buffer, uint16_t Copy_u8BufferSize);
/*==============================================================================================================================================
 *@fn    USART_voidTransmitBuffer
 *@brief  This function is used to transmit a string through UART peripheral using polling
 *@paramter[in]  Copy_p8Buffer : Pointer to the Buffer which the string will be transmitted from
 *@paramter[in]  Copy_u8BufferSize : The Size of the Buffer
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidTransmitBuffer(UART_Config_t *UART_Config, uint16_t *Copy_p8Buffer, uint16_t Copy_u8BufferSize);
/*==============================================================================================================================================
 *@fn    USART_voidRecieveBufferIR
 *@brief  This function is used to receive a string through UART peripheral using interrupts
 *@paramter[in]  Copy_p8Buffer : Pointer to the Buffer which the received string will be written to
 *@paramter[in]  Copy_u8BufferSize : The Size of the Buffer
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidRecieveBufferIT(UART_Config_t *UART_Config, uint16_t *Copy_p8Buffer, uint16_t Copy_u8BufferSize, void (*pv_CallBackFunc)(void));

/*==============================================================================================================================================
 *@fn    USART_voidTransmitBuffer
 *@brief  This function is used to transmit a string through UART peripheral using interrupts
 *@paramter[in]  Copy_p8Buffer : Pointer to the Buffer which the string will be transmitted from
 *@paramter[in]  Copy_u8BufferSize : The Size of the Buffer
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_voidTransmitBufferIT(UART_Config_t *UART_Config, uint16_t *Copy_p8Buffer, uint16_t Copy_u8BufferSize);

/*

@function         :    USART_SendStringPolling
@brief            :    Send String using USART
@param            :    String
@retval            :    Error State
*/
Error_State_t USART_SendStringPolling(uint8_t USART_Num , const char* String);
/*==============================================================================================================================================
 *@fn    UART_VoidEnableDMATransmit
 *@brief   This function is used to enable the DMA for the UART peripheral
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_VoidEnableDMATransmit(UART_Config_t *UART_Config);
/*==============================================================================================================================================
 *@fn    UART_VoidEnableDMAReciver
 *@brief   This function is used to enable the DMA for the UART peripheral
 *@paramter[in] UART_Config_t *UART_Config : Pointer to the UART peripheral configuration structure
 *@retval void
 *==============================================================================================================================================*/
void UART_VoidEnableDMAReciver(UART_Config_t *UART_Config);
/*
 * @function 		:	USART_SendStringPolling
 * @brief			:	Send String using USART
 * @param			:	String
 * @retval			:	Error State
 */
Error_State_t USART_SendStringPolling(uint8_t USART_Num , const char* String);

#endif /* UART_INCLUDE_UART_INTERFACE_H_ */
