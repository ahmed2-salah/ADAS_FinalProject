/*******************************************************************************
 * Filename              :   UART_Private.h
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
#ifndef UART_INCLUDE_UART_PRIVATE_H_
#define UART_INCLUDE_UART_PRIVATE_H_

/*==============================================================================================================================================
 *@fn    UART_HANDLE_IT
 *@brief  This function is used to Handle Interrupts
 *@paramter[in] UARTNumber : UART Number Needed To Be Handled
 *@retval void
 *@note  This Function is Private
 *==============================================================================================================================================*/
static void UART_HANDLE_IT( UART_ID_t UARTNumber );


#define UARTNUMBER 6
#define Clock_Freq 16000000UL
#define FlagsNumber 10
#define OneBitMasking 0b1
#define TwoBitMasking 0b11
#define FourBitMasking 0b1111
#define FiveBitMasking 0b11111
#define ElevenBitMasking 0xFFF

#endif /* UART_INCLUDE_UART_PRIVATE_H_ */
