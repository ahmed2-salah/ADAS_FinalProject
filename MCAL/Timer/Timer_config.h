
#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/*Note: Timers from 2 to 5 are on APB1 Bus */
#define BUS_FREQUENCY							45000000 /*Hz*/

/*for 1000 ticks freq: a tick happens every 1 ms */
#define TICKS_FREQUENCY								1000 /*Hz*/

/*********************************************************************************************************/
/*Configurations for external clock for the timer:
 *
 *Options for external mode:
 * 1) External_Mode_One
 * 2) External_Mode_Two
 *
 * For external trigger filter: Refer to the Data-sheet at TIMx slave mode control register.
 * */
#define EXTERNAL_MODE							External_Mode_Two
#define EXTERNAL_TRIGGER_FILTER							0
/*********************************************************************************************************/
/*Choose PWM  frequency in Hz*/
#define PWM_FREQUENCY									100


/**

ICU_CHANNEL1_MAPPED_TIMER is Selected by :
										1- TIM_CHANNEL_OUTPUT
										2- TIM_CHANNEL_IC_TL1
										3- TIM_CHANNEL_IC_TL2
										4- TIM_CHANNEL_IC_TRC

**/
#define  ICU_CHANNEL1_MAPPED_TIMER			TIM_CHANNEL_IC_TL1




/**

ICU_CHANNEL2_MAPPED_TIMER is Selected by :
										1- TIM_CHANNEL_OUTPUT
										2- TIM_CHANNEL_IC_TL1
										3- TIM_CHANNEL_IC_TL2
										4- TIM_CHANNEL_IC_TRC

**/
#define  ICU_CHANNEL2_MAPPED_TIMER			TIM_CHANNEL_IC_TL1


/**
 *
 *
 * ICU_CHANNEL1_MAPPED_TIMER_TRIGGER is Selected by :
 * 												1-TIM_RISING_EDGE
 * 												2-TIM_FALLING_EDGE
 *
 *
 */


#define ICU_CHANNEL1_MAPPED_TIMER_TRIGGER		TIM_RISING_EDGE


/**
 *
 *
 * ICU_CHANNEL2_MAPPED_TIMER_TRIGGER is Selected by :
 * 												1-TIM_RISING_EDGE
 * 												2-TIM_FALLING_EDGE
 */


#define ICU_CHANNEL2_MAPPED_TIMER_TRIGGER			TIM_FALLING_EDGE


/**
 *  ICU_WITH_DMA	select  :
 *  						1-TIM_ENABLE
 *  						2-TIM_DISABLE
 *
 */

#define ICU_WITH_DMA	TIM_ENABLE

#endif /* TIMER_CONFIG_H_ */
