

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "ErrTypes.h"
#include "STM32F446xx.h"
#include "Timer_interface.h"
#include "Timer_private.h"
#include "Timer_config.h"

void (*TIM5_CallBack_ICU)(void)=NULL;


void TimerX_Count(Timer_No_e Copy_e_Timer,Timer_AlignmentMode_e Copy_e_Mode, u32 Copy_u32_MilliSeconds )
{



    switch(Copy_e_Timer)
    {
        case TIMER_2_:
            /*Reset Timer Registers */
            TIMER_2->Timer_Number[0].TIMx_CR1 = 0x0000;

            /*Choose Edge-Aligned or Center-Aligned mode */
            switch(Copy_e_Mode)
            {
                case UP_COUNTER:
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_DIR);
                    break;
                case DOWN_COUNTER:
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_DIR);
                    break;
                case CENTER_ALIGNED_MODE_1:
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_0);
                    break;
                case CENTER_ALIGNED_MODE_2:
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_1);
                    break;
                case CENTER_ALIGNED_MODE_3:
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_0);
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_1);
                    break;
                default:
                    break;
            }

            /*Set timer prescaler*/
            TIMER_2->Timer_Number[0].TIMx_PSC = ((BUS_FREQUENCY/TICKS_FREQUENCY) -1) ;
            /*Set Auto-Reload value*/
            TIMER_2->Timer_Number[0].TIMx_ARR = ((Copy_u32_MilliSeconds /1000) * TICKS_FREQUENCY);

            /*Enable Timer */
            Set_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_CEN);
            break;
        case TIMER_3_:
            /*Reset Timer Registers */
            TIMER_3->Timer_Number[0].TIMx_CR1 = 0x0000;

            /*Choose Edge-Aligned or Center-Aligned mode */
            switch(Copy_e_Mode)
            {
                case UP_COUNTER:
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_DIR);
                    break;
                case DOWN_COUNTER:
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_DIR);
                    break;
                case CENTER_ALIGNED_MODE_1:
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_0);
                    break;
                case CENTER_ALIGNED_MODE_2:
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_1);
                    break;
                case CENTER_ALIGNED_MODE_3:
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_0);
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_1);
                    break;
                default:
                    break;
            }

            /*Set timer prescaler*/
            TIMER_3->Timer_Number[0].TIMx_PSC = ((BUS_FREQUENCY/TICKS_FREQUENCY) -1) ;
            /*Set Auto-Reload value*/
            TIMER_3->Timer_Number[0].TIMx_ARR = ((Copy_u32_MilliSeconds /1000) * TICKS_FREQUENCY);

            /*Enable Timer */
            Set_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_CEN);
            break;
            break;
    }

}


void TimerX_ExternalCounterOnETR(Timer_No_e Copy_e_Timer, u16 Copy_u16_Counts)
{
	/***This funtion uses ETR pin as external input for the timer in both external modes***/

	/*Reset timer slave mode control register to the default values
	 * NO External trigger prescaler and NO External trigger filter*/
	TIMER_2->Timer_Number[Copy_e_Timer].TIMx_SMCR = 0x0000;

	/*Set counter direction to UP counter*/
	Clr_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_DIR);

	/*Set Auto-Reload value : Number of counts needed to generate overflow*/
	TIMER_2->Timer_Number[Copy_e_Timer].TIMx_ARR = Copy_u16_Counts;

	/*Choose external trigger polarity to be rising edge*/
	Clr_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_SMCR, TIMx_SMCR_ETP);

	/*Set external trigger filter*/
	TIMER_2->Timer_Number[Copy_e_Timer].TIMx_SMCR |= EXTERNAL_TRIGGER_FILTER <<TIMx_SMCR_ETF_0 ;

	/*Enable update interrupt*/
	Set_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_DIER, TIMx_DIER_UIE);

	#if EXTERNAL_MODE == External_Mode_One
	/*Select external trigger input (ETRF) pin as trigger selection */
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR |= 0b111 << TIMx_SMCR_TS_0;
	/*Enable external clock mode 1 */
	TIMER_NO->Timer_Number[Copy_e_Timer].TIMx_SMCR |= 0b111 << TIMx_SMCR_SMS_0;

	#elif EXTERNAL_MODE == External_Mode_Two
	/*Enable external clock mode 2 */
	Set_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_SMCR, TIMx_SMCR_ECE);
    #endif

	/*Enable Timer */
	Set_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CEN);
}

void TimerX_PWM(Timer_No_e Copy_e_Timer, Timer_Channl_e Copy_e_Channel, u8 Copy_u8_DutyCycle)
{
	/* The polarity of the pwm signal is remained at the default of active high
	 * The pwm mode is working at the default UP counting (channel is active as long as TIMx_CNT<TIMx_CCR1 )
	 * PWM mode 1 */

    switch (Copy_e_Timer) {
        case TIMER_2_:
            /*Set the timer on UP counting, edge-aligned mode*/
            Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_DIR);
            Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_0);
            Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_1);

            /*Set the auto-reload preload bit for ARR*/
            Set_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_ARPE);

            /*Set the ARR value to maximum*/
            TIMER_2->Timer_Number[0].TIMx_ARR = 0xffff;

            /*Set timer prescaler: for a pwm frequency of 100 Hz */
            TIMER_2->Timer_Number[0].TIMx_PSC = ((BUS_FREQUENCY/ (0xffff * PWM_FREQUENCY)) -1) ;

            switch(Copy_e_Channel)
            {
                case CH1:
                    /*Select output mode for channel 1*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC1S_0);
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC1S_1);
                    /*Select the polarity to active high*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1P);
                    /*Choose PWM mode 1*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC1M_0);
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC1M_1);
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC1M_2);
                    /*Set the duty cycle*/
                    TIMER_2->Timer_Number[0].TIMx_CCR1 = ( (0xffff * Copy_u8_DutyCycle) /100 );
                    /*Set the preload bit*/
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC1PE);
                    /*Enable capture compare*/
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1E);
                    break;
                case CH2:
                    /*Select output mode for channel 2*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC2S_0);
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC2S_1);
                    /*Select the polarity to active high*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC2P);
                    /*Choose PWM mode 1*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC2M_0);
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC2M_1);
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC2M_2);
                    /*Set the duty cycle*/
                    TIMER_2->Timer_Number[0].TIMx_CCR2 = ( (0xffff * Copy_u8_DutyCycle) /100 );
                    /*Set the preload bit*/
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC2PE);
                    /*Enable capture compare*/
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC2E);
                    break;
                case CH3:
                    /*Select output mode for channel 3*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_CC3S_0);
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_CC3S_1);
                    /*Select the polarity to active high*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC3P);
                    /*Choose PWM mode 1*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC3M_0);
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC3M_1);
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC3M_2);
                    /*Set the duty cycle*/
                    TIMER_2->Timer_Number[0].TIMx_CCR3 = ( (0xffff * Copy_u8_DutyCycle) /100 );
                    /*Set the preload bit*/
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC3PE);
                    /*Enable capture compare*/
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC3E);
                    break;
                case CH4:
                    /*Select output mode for channel 4*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_CC4S_0);
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_CC4S_1);
                    /*Select the polarity to active high*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC4P);
                    /*Choose PWM mode 1*/
                    Clr_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC4M_0);
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC4M_1);
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC4M_2);
                    /*Set the duty cycle*/
                    TIMER_2->Timer_Number[0].TIMx_CCR4 = ( (0xffff * Copy_u8_DutyCycle) /100 );
                    /*Set the preload bit*/
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC4PE);
                    /*Enable capture compare*/
                    Set_Bit(TIMER_2->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC4E);
                    break;
                default:
                    break;
            }

            /*Initialize all counters*/
            Set_Bit(TIMER_2->Timer_Number[0].TIMx_EGR, TIMx_EGR_UG);
            /*Enable Timer */
            Set_Bit(TIMER_2->Timer_Number[0].TIMx_CR1, TIMx_CR1_CEN);
            break;



        case TIMER_3_:


            /*Set the timer on UP counting, edge-aligned mode*/
            Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_DIR);
            Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_0);
            Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_CMS_1);

            /*Set the auto-reload preload bit for ARR*/
            Set_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_ARPE);

            /*Set the ARR value to maximum*/
            TIMER_3->Timer_Number[0].TIMx_ARR = 0xffff;

            /*Set timer prescaler: for a pwm frequency of 100 Hz */
            TIMER_3->Timer_Number[0].TIMx_PSC = ((BUS_FREQUENCY/ (0xffff * PWM_FREQUENCY)) -1) ;

            switch(Copy_e_Channel)
            {
                case CH1:
                    /*Select output mode for channel 1*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC1S_0);
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC1S_1);
                    /*Select the polarity to active high*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1P);
                    /*Choose PWM mode 1*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC1M_0);
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC1M_1);
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC1M_2);
                    /*Set the duty cycle*/
                    TIMER_2->Timer_Number[0].TIMx_CCR1 = ( (0xffff * Copy_u8_DutyCycle) /100 );
                    /*Set the preload bit*/
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC1PE);
                    /*Enable capture compare*/
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1E);
                    break;
                case CH2:
                    /*Select output mode for channel 2*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC2S_0);
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC2S_1);
                    /*Select the polarity to active high*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC2P);
                    /*Choose PWM mode 1*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC2M_0);
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC2M_1);
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC2M_2);
                    /*Set the duty cycle*/
                    TIMER_3->Timer_Number[0].TIMx_CCR2 = ( (0xffff * Copy_u8_DutyCycle) /100 );
                    /*Set the preload bit*/
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_OC2PE);
                    /*Enable capture compare*/
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC2E);
                    break;
                case CH3:
                    /*Select output mode for channel 3*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_CC3S_0);
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_CC3S_1);
                    /*Select the polarity to active high*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC3P);
                    /*Choose PWM mode 1*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC3M_0);
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC3M_1);
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC3M_2);
                    /*Set the duty cycle*/
                    TIMER_3->Timer_Number[0].TIMx_CCR3 = ( (0xffff * Copy_u8_DutyCycle) /100 );
                    /*Set the preload bit*/
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC3PE);
                    /*Enable capture compare*/
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC3E);
                    break;
                case CH4:
                    /*Select output mode for channel 4*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_CC4S_0);
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_CC4S_1);
                    /*Select the polarity to active high*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC4P);
                    /*Choose PWM mode 1*/
                    Clr_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC4M_0);
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC4M_1);
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC4M_2);
                    /*Set the duty cycle*/
                    TIMER_3->Timer_Number[0].TIMx_CCR4 = ( (0xffff * Copy_u8_DutyCycle) /100 );
                    /*Set the preload bit*/
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCMR2, TIMx_CCMR2_OC4PE);
                    /*Enable capture compare*/
                    Set_Bit(TIMER_3->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC4E);
                    break;
                default:
                    break;
            }

            /*Initialize all counters*/
            Set_Bit(TIMER_3->Timer_Number[0].TIMx_EGR, TIMx_EGR_UG);
            /*Enable Timer */
            Set_Bit(TIMER_3->Timer_Number[0].TIMx_CR1, TIMx_CR1_CEN);
            break;

    }

}

void TimerX_EncoderMode(Timer_No_e Copy_e_Timer)
{
	/*Map IC1 on TI1*/
	Set_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC1S_0);
	Clr_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC1S_1);
	/*Map IC2 on TI2*/
	Set_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC2S_0);
	Clr_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CCMR1, TIMx_CCMR1_CC2S_1);
	/*Circuit is sensitive to TI1FP1 rising edge*/
	Clr_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC1P);
	Clr_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC1NP);
	/*No filter on IC1*/
	TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CCMR1 &= ~( 0b1111 << TIMx_CCMR1_IC1F_0);
	/*Circuit is sensitive to TI2FP1 rising edge*/
	Clr_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC2P);
	Clr_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CCER, TIMx_CCER_CC2NP);
	/*No filter on IC2*/
	TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CCMR1 &= ~( 0b1111 << TIMx_CCMR1_IC2F_0);
	/*Select encoder mode 3*/
	Set_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_SMCR, TIMx_SMCR_SMS_0);
	Set_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_SMCR, TIMx_SMCR_SMS_1);
	Clr_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_SMCR, TIMx_SMCR_SMS_2);
	/*Enable Timer */
	Set_Bit(TIMER_2->Timer_Number[Copy_e_Timer].TIMx_CR1, TIMx_CR1_CEN);
}



/**
 * @fn			         : Timer2_ICU_voidInit
 * @brief		         : Initializes Timer2 for Input Capture Unit (ICU)
 * @param[in] Copy_e_Timer: Timer Number (e.g., TIMER2)
 * @retval		         : None
 **/
void Timer5_ICU_voidInit(Timer_No_e Copy_e_Timer)
{

    /*1-Select the Active Input: The Capture/Compare Register (TIMx_CCR1) must be linked to the TI1 input. 
    This is done by writing the CC1S bits to 01 in the TIMx_CCMR1 register. Once CC1S is different from 00,
     the channel is configured in input and the TIMx_CCR1 register becomes read-only.*/
     
   //    Value: 10 (CC3 channel is configured as input, IC1 is mapped on TI2   PB10)  
    Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC1S_0);
    Set_Bit(TIMER_5->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC1S_1);
     
     
     /*

2-Program the Input Filter Duration: This is done in relation to the signal connected to the timer.
 If the input signal is not stable during at least 5 internal clock cycles when toggling,
  a filter duration longer than these 5 clock cycles must be programmed.
   A transition on TI1 can be validated when 8 consecutive samples with the new level have been detected.
    This is done by writing IC1F bits to 0011 in the TIMx_CCMR1 register.
*/

//    Value: 0000 (No filter, sampling is done at fDTS)
    Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_IC1F_0);
    Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_IC1F_1);
    Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_IC1F_2);
    Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_IC1F_3);




/*
Select the Edge of the Active Transition: On the TI1 channel,
 the edge of the active transition is selected by writing the CC1P and CC1NP bits to 00 in the TIMx_CCER register. 
 In this case, it’s the rising edge.
*/

  //    Value: 0 (Capture is done on a rising edge of IC1)
    Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1P);
    Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1NP);




/*
Program the Input Prescaler: In this example, 
the capture is to be performed at each valid transition, 
so the prescaler is disabled. This is done by writing IC1PS bits to 00 in the TIMx_CCMR1 register.
*/
    //This bit-field defines the ratio of the prescaler acting on CC1 input (IC1).
    //The prescaler is reset as soon as CC1E=0 (TIMx_CCER register).
    //00: no prescaler, capture is done each time an edge is detected on the capture input
    //01: capture is done once every 2 events
    //10: capture is done once every 4 events
    //11: capture is done once every 8 events//
    Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_IC1PSC_0);
    Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_IC1PSC_1);


/*
Enable Capture: 
Capture from the counter into the capture register is enabled by setting the CC1E bit in the TIMx_CCER register.
*/

    // Enable capture from the counter into the capture register
    Set_Bit(TIMER_5->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1E);


/*
Enable the Related Interrupt Request: If needed,
 the related interrupt request is enabled by setting the CC1IE bit in the TIMx_DIER register, 
 and/or the DMA request by setting the CC1DE bit in the TIMx_DIER register.*/
   
   
    // Enable the TIM5 interrupt
    Set_Bit(TIMER_5->Timer_Number[0].TIMx_DIER, TIMx_DIER_CC1IE);



   // Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC2S_0);
   // Set_Bit(TIMER_5->Timer_Number[0].TIMx_CCMR1, TIMx_CCMR1_CC2S_1);




/*7agat optional kda xD */
    /*Initialize all counters*/
    Set_Bit(TIMER_5->Timer_Number[0].TIMx_EGR, TIMx_EGR_UG);
    /*Enable Timer */
    Set_Bit(TIMER_5->Timer_Number[0].TIMx_CR1, TIMx_CR1_CEN);

}


ERRORS_t ICU_voidSetTriggerEdge(Timer_Edge Copy_u8Edge){
    ERRORS_t Local_u8ErrorState = OK;
    //    Value: 0 (Capture is done on a rising edge of IC3)
    if (Copy_u8Edge== Rising ) {
        Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1P);
        Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1NP);
    } else if (Copy_u8Edge== Falling){

        Set_Bit(TIMER_5->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1P);
        Clr_Bit(TIMER_5->Timer_Number[0].TIMx_CCER, TIMx_CCER_CC1NP);

    }else{
        return Local_u8ErrorState = NOK;

    }
    return Local_u8ErrorState = OK;
    


}
u32 TIMER_u32GetIcuValue(void){
    return TIMER_5->Timer_Number[0].TIMx_CCR1;
}

ERRORS_t TIMER5_u8CompSetCallBack(void (*Copy_TIM5_CallBack_ICU)(void))
{
    ERRORS_t Local_u8ErrorState = OK;
    if(TIM5_CallBack_ICU != NULL)
    {
        TIM5_CallBack_ICU = Copy_TIM5_CallBack_ICU;
    }
    else
    {
        Local_u8ErrorState = NOK;
    }
    return Local_u8ErrorState;
}

void TIM5_IRQHandler(void) {
    if (Get_Bit(TIMER_5->Timer_Number[0].TIMx_SR ,1) ) { //TIMx_SR_CC1IF
        // Clear the interrupt flag
        Clr_Bit(TIMER_5->Timer_Number[0].TIMx_SR ,1);
        // Handle the interrupt
        TIM5_CallBack_ICU();

        // ...
    }
}

/*
u8 flag=0;
u32 ontime=0;
u32 rising=0;
u8 ticktime=32; //micro sec

void Capture () // ISR for input capture interrupt
{
	if (flag == 0) // if rising edge detected
	{
		flag = 1; // set flag to 1
		//TIMER1_voidSetTimerValue(0);// reset timer1 counter
		//TIMER1_voidSetCompMatchTopValue(0);
		rising =TIMER_u32GetIcuValue();
		ICU_voidSetTriggerEdge(Falling); // set input capture edge select to falling edge
	}
	else // if falling edge detected
	{
		flag = 0; // set flag to 0
		ontime =(ICU_voidGetValue()-rising) * ticktime;
		ICU_voidSetTriggerEdge(Rising); // set input capture edge select to rising edge
	}
}*/