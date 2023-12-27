
#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

typedef enum {
	/* Choose general purpose timer number (from 2 to 5) from here */
	TIMER_2_,
	TIMER_3_,
	TIMER_4_,
	TIMER_5_

}Timer_No_e;

typedef enum{
	/* Choose timer channel from here*/
	CH1,
	CH2,
	CH3,
	CH4

}Timer_Channl_e;

typedef enum{
	/* Choose Alignment Mode [Edge-aligned (Up/Down) / Center-aligned (mode 1/2/3)] */


	UP_COUNTER,
	/* 1) the counter counts from 0 to the auto-reload value */

	DOWN_COUNTER,
	/* 2) the counter counts from the auto-reload value down to 0 */

	CENTER_ALIGNED_MODE_1,
	/* 3) The counter counts up and down alternatively.Output compare interrupt
	 * flags of channels configured in output set only when the counter is counting down.*/

	CENTER_ALIGNED_MODE_2,
	/* 4) The counter counts up and down alternatively.Output compare interrupt
	 * flags of channels configured in output set only when the counter is counting up.*/

	CENTER_ALIGNED_MODE_3
	/* 5) The counter counts up and down alternatively.Output compare interrupt
	 * flags of channels configured in output set both when the counter is counting up or down.*/

}Timer_AlignmentMode_e;

typedef enum {
    /* Choose general purpose timer number (from 2 to 5) from here */
    Rising,
    Falling

}Timer_Edge;

#define TIMER_RISING 	0
#define TIMER_FALLING	1


#define 	TIM1		    0
#define 	TIM2		    1
#define 	TIM3		    2
#define 	TIM4		    3

#define 	TIM_CHANNEL1		                1
#define 	TIM_CHANNEL2		                2
#define 	TIM_CHANNEL3		                3
#define 	TIM_CHANNEL4		                4

#define 	TIM_DISABLE		                0
#define 	TIM_ENABLE		                1

#define 	UP_COUNT		                0
#define 	DOWN_COUNT  	                1

#define 	DIV_1			                0
#define 	DIV_2			                1
#define 	DIV_4			                2

#define     ONE_PULSE_MODE                  0
#define     PERIODIC_MODE                   1

#define 	CENTER_ALIGNED_MODE_1_			0
#define 	CENTER_ALIGNED_MODE_2_			1
#define 	CENTER_ALIGNED_MODE_3_			2
#define 	EDGE_ALIGNED_MODE				3

#define 	mSEC			                1000
#define 	uSEC			                1


#define PORTA_PIN0		TIM2_CH1
#define PORTA_PIN1		TIM2_CH2
#define PORTA_PIN2		TIM2_CH3
#define PORTA_PIN3		TIM2_CH4
#define PORTA_PIN6		TIM3_CH1
#define PORTA_PIN7		TIM3_CH2
#define PORTA_PIN8		TIM1_CH1
#define PORTA_PIN9		TIM1_CH2
#define PORTA_PIN10		TIM1_CH3
#define PORTA_PIN11		TIM1_CH4
#define PORTB_PIN0		TIM3_CH3
#define PORTB_PIN1		TIM3_CH4


typedef struct
{
    u16 Prescaler;
    u16 Period;
    u8 Period_Mode;					/* PERIODIC_MODE or ONE_PULSE_MODE */
    u8 Direction;					/* UP_COUNT or DOWN_COUNT */
    u8 Clock_Div;					/* DIV_1, DIV_2 or DIV_3 */
    u8 Center_Aligned_Mode;			/* EDGE_ALIGNED_MODE, CENTER_ALIGNED_MODE_(1,2 OR 3)*/
    u8 Update_State;	            /* ENABLE or DISABLE */
    u8 AutoReloadBuffer;            /* ENABLE or DISABLE */
    u8 Counter_State;               /* ENABLE or DISABLE */
    u8 UDI_State;                   /* ENABLE or DISABLE */
}GPT_Config;

/*Function Prototypes*/







void TimerX_Count(Timer_No_e Copy_e_Timer,Timer_AlignmentMode_e Copy_e_Mode, u32 Copy_u32_MilliSeconds );
/* @function: counts for a time of Milli-Seconds using a timer from 2 to 5.
 * @parameters:
 * 		1- Timer Number (from 2 to 5): choose from  ( Timer_No_e ) enum.
 * 		2- Alignment Mode [Edge-aligned (Up/Down) / Center-aligned (mode 1/2/3)]: choose from  ( Timer_AlignmentMode_e ) enum.
 * 		3- Time of update event in milli-seconds.
 * @return: None.
 * */

void TimerX_ExternalCounterOnETR(Timer_No_e Copy_e_Timer, u16 Copy_u16_Counts);
/* @function: use ETR pin as external input to the counter and generate an interrupt after certain
 * number of counts.
 * @parameters:
 * 		1- Timer Number (from 2 to 5): choose from  ( Timer_No_e ) enum.
 * 		2- Number of counts needed to generate an interrupt.
 * 	@return: None.
 * 	NOTE: extra configurations for the function are in <Timer_config.h> file.
 */

void TimerX_PWM(Timer_No_e Copy_e_Timer, Timer_Channl_e Copy_e_Channel,u8 Copy_u8_DutyCycle);
/*@function:Choose a channel in a selected timer to work in PWM mode given its duty cycle, under a time period
 * determined by the chosen frequency in <Timer_config.h> file.
 *@parameters:
 *		1- Timer Number (from 2 to 5): choose from  ( Timer_No_e ) enum.
 *		2- Channel for the timer: choose from  ( Timer_Channl_e ) enum.
 *		3- Duty cycle in Percentage %.
 *@return: None
 */

void Timer5_ICU_voidInit(Timer_No_e Copy_e_Timer); // Initialize Input Capture Unit


ERRORS_t TIMER5_u8CompSetCallBack(void (*Copy_TIM2_CallBack_ICU)(void));


ERRORS_t ICU_voidSetTriggerEdge(Timer_Edge Copy_u8Edge);

u32 TIMER_u32GetIcuValue(void);

void TimerX_EncoderMode(Timer_No_e Copy_e_Timer);
/*@function: Enable the timer in encoder hardware mode.
 *@parameters: Timer Number (from 2 to 5): choose from  ( Timer_No_e ) enum.
 *@return: None
 */

//void TimerX_ExternalCounterOnTIxPin(Timer_No_e Copy_e_Timer, u16 Copy_u16_Counts);

#endif /* TIMER_INTERFACE_H_ */
