#include <stdint.h>
#include "math.h"
#include "ErrTypes.h"
#include "STM32F446xx.h"
#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "SCB_Interface.h"
#include "NVIC_Interface.h"
#include "UART_Interface.h"
#include "Bluetooth_interface.h"


#define NUM_OF_USART_PINS  2

UART_Config_t * UART_CONFIG ;
uint8_t Reading=0;


/*this is a static function that will use in this file only*/
/*don't touch it i exactly call it _-_*/
static void USART1_Init(void)
{
	/* USART1 Interrupts Configuration */
	static UART_Interrupts_t USART2Interrupts =
	{
			.IDLE = UART_Disable, .PE = UART_Disable, .RXN = UART_Enable, .TC = UART_Disable, .TX = UART_Disable

	};

	/* USART1 Configuration */
	static UART_Config_t USART1Config =
	{
			.UART_ID = UART_1, .BaudRate = BaudRate_9600, .Direction = RXN, .OverSampling = OverSamplingBy16, .ParityState = UART_Disable, .StopBits = OneStopBit, .WordLength = _8Data, .Interrupts = &USART2Interrupts};

	/* USART1 Initialization */
	UART_voidInit(&USART1Config);

	/* Initialize UART Struct Globally */
	UART_CONFIG = &USART1Config;
}

/*this is the init function which will initiate the Bluetooth module*/
/*also we will call it in main */
void Bluetooth_init (void)
{

	//uint8_t receivingdata ;
	RCC_AHB1EnableCLK(GPIOAEN);

	RCC_APB2EnableCLK(USART1EN);

	NVIC_EnableIRQ(USART1_IRQ);

	SCB_VoidSetPriorityGroup(GP_2_SP_8);
	/* Set UART1 to Group Priority Zero*/
	NVIC_SetPriority(USART1_IRQ, 0);

	GPIO_PinConfig_t LEDPIN = {.AltFunc=AF0,.Mode=OUTPUT,.OutputType=PUSH_PULL,.PinNum=PIN5,.Port=PORTA,.Speed=LOW_SPEED};
	GPIO_u8PinInit(&LEDPIN);
	/* USART1 GPIO Pins Configuration Working in Full Duplex */
	GPIO_PinConfig_t USART1_Pins[NUM_OF_USART_PINS] =
	{
			/* USART1 Tx Pin */
			{.AltFunc = AF7, .Mode = ALTERNATE_FUNCTION, .OutputType = PUSH_PULL, .PinNum = PIN9, .Port = PORTA, .PullType = NO_PULL, .Speed = LOW_SPEED},
			/* USART1 Rx Pin */
			{.AltFunc = AF7, .Mode = ALTERNATE_FUNCTION, .OutputType = PUSH_PULL, .PinNum = PIN10, .Port = PORTA, .PullType = NO_PULL, .Speed = LOW_SPEED}};

	/* Initializing USART1 Pins */
	GPIO_u8PinsInit(USART1_Pins, NUM_OF_USART_PINS);
	USART1_Init();

	UART_u16ReceiveIT(UART_CONFIG, &Reading);

}


/*this function where we will write our application in */
/*we will call it in main*/
void Bluetooth_void_GetReading(void)
{
	if(Reading=='F')
	{
		GPIO_u8SetPinValue(PORTA, PIN5, PIN_HIGH);
	}
	else if (Reading== 'G')
	{
		GPIO_u8SetPinValue(PORTA, PIN5, PIN_LOW);

	}
}
