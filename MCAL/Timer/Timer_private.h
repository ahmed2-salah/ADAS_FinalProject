
#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

typedef struct{
	/* Timer registers for general purpose timers from 2 to 5 */
	volatile u32 TIMx_CR1;
	volatile u32 TIMx_CR2;
	volatile u32 TIMx_SMCR;
	volatile u32 TIMx_DIER;
	volatile u32 TIMx_SR;
	volatile u32 TIMx_EGR;
	volatile u32 TIMx_CCMR1;
	volatile u32 TIMx_CCMR2;
	volatile u32 TIMx_CCER;
	volatile u32 TIMx_CNT;
	volatile u32 TIMx_PSC;
	volatile u32 TIMx_ARR;
	volatile u32 Reserved_Register_1_NOT_USED;
	volatile u32 TIMx_CCR1;
	volatile u32 TIMx_CCR2;
	volatile u32 TIMx_CCR3;
	volatile u32 TIMx_CCR4;
	volatile u32 Reserved_Register_2_NOT_USED;
	volatile u32 TIMx_DCR;
	volatile u32 TIMx_DMAR;
	volatile u32 TIM_2_5_OR;

}Timer_2_to_5_Registers;

typedef struct {
    /*Timers from 2 to 5 Memory Access*/
    Timer_2_to_5_Registers Timer_Number[1];

}Timer_No2_t;
typedef struct {
    /*Timers from 2 to 5 Memory Access*/
    Timer_2_to_5_Registers Timer_Number[1];

}Timer_No3_t;
typedef struct {
    /*Timers from 2 to 5 Memory Access*/
    Timer_2_to_5_Registers Timer_Number[1];

}Timer_No5_t;
//imer_2_to_5_Registers Timer_Number[4];
/* Base address for timers 2 to 5 */
#define  TIMER_2		( (volatile Timer_No2_t *) 0x40000000 )
#define  TIMER_3		( (volatile Timer_No3_t *) 0x40000400 )
#define  TIMER_5		( (volatile Timer_No5_t *) 0x40000C00 )
enum {

	/*TIMx control register 1 (TIMx_CR1)*/
	TIMx_CR1_CEN,
	TIMx_CR1_UDIS,
	TIMx_CR1_URS,
	TIMx_CR1_OPM,
	TIMx_CR1_DIR,
	TIMx_CR1_CMS_0,
	TIMx_CR1_CMS_1,
	TIMx_CR1_ARPE,
	TIMx_CR1_CKD_0,
	TIMx_CR1_CKD_1,

	/*TIMx slave mode control register (TIMx_SMCR)*/
	TIMx_SMCR_SMS_0 =0,
	TIMx_SMCR_SMS_1,
	TIMx_SMCR_SMS_2,
	TIMx_SMCR_TS_0 =4,
	TIMx_SMCR_TS_1,
	TIMx_SMCR_TS_2,
	TIMx_SMCR_MSM,
	TIMx_SMCR_ETF_0,
	TIMx_SMCR_ETF_1,
	TIMx_SMCR_ETF_2,
	TIMx_SMCR_ETF_3,
	TIMx_SMCR_ETPS_0,
	TIMx_SMCR_ETPS_1,
	TIMx_SMCR_ECE,
	TIMx_SMCR_ETP,

	/*TIMx DMA/Interrupt enable register (TIMx_DIER)*/
	TIMx_DIER_UIE =0,
	TIMx_DIER_CC1IE,
	TIMx_DIER_CC2IE,
	TIMx_DIER_CC3IE,
	TIMx_DIER_CC4IE,
	TIMx_DIER_TIE =6,
	TIMx_DIER_UDE =8,
	TIMx_DIER_CC1DE,
	TIMx_DIER_CC2DE,
	TIMx_DIER_CC3DE,
	TIMx_DIER_CC4DE,
	TIMx_DIER_TDE =14,

	/*TIMx event generation register (TIMx_EGR)*/
	TIMx_EGR_UG =0,
	TIMx_EGR_CC1G,
	TIMx_EGR_CC2G,
	TIMx_EGR_CC3G,
	TIMx_EGR_CC4G,
	TIMx_EGR_TG =6,

	/*TIMx capture/compare mode register 1 (TIMx_CCMR1)*/
	/*Bits for output mode*/
	 TIMx_CCMR1_CC1S_0 =0,
	 TIMx_CCMR1_CC1S_1,
	 TIMx_CCMR1_OC1FE,
	 TIMx_CCMR1_OC1PE,
	 TIMx_CCMR1_OC1M_0,
	 TIMx_CCMR1_OC1M_1,
     TIMx_CCMR1_OC1M_2,
     TIMx_CCMR1_OC1CE,
	 TIMx_CCMR1_CC2S_0,
	 TIMx_CCMR1_CC2S_1,
	 TIMx_CCMR1_OC2FE,
	 TIMx_CCMR1_OC2PE,
	 TIMx_CCMR1_OC2M_0,
	 TIMx_CCMR1_OC2M_1,
	 TIMx_CCMR1_OC2M_2,
	 TIMx_CCMR1_OC2CE,
	 /*Other bits for input mode*/
	 TIMx_CCMR1_IC1PSC_0 =2,
	 TIMx_CCMR1_IC1PSC_1,
	 TIMx_CCMR1_IC1F_0,
	 TIMx_CCMR1_IC1F_1,
	 TIMx_CCMR1_IC1F_2,
	 TIMx_CCMR1_IC1F_3,
	 TIMx_CCMR1_IC2PSC_0 =10,
	 TIMx_CCMR1_IC2PSC_1,
	 TIMx_CCMR1_IC2F_0,
	 TIMx_CCMR1_IC2F_1,
	 TIMx_CCMR1_IC2F_2,
	 TIMx_CCMR1_IC2F_3,

	 /*TIMx capture/compare mode register 2 (TIMx_CCMR2)*/
	 /*Bits for output mode*/
     TIMx_CCMR2_CC3S_0 =0,
	 TIMx_CCMR2_CC3S_1,
	 TIMx_CCMR2_OC3FE,
	 TIMx_CCMR2_OC3PE,
	 TIMx_CCMR2_OC3M_0,
	 TIMx_CCMR2_OC3M_1,
	 TIMx_CCMR2_OC3M_2,
	 TIMx_CCMR2_OC3CE,
	 TIMx_CCMR2_CC4S_0,
	 TIMx_CCMR2_CC4S_1,
	 TIMx_CCMR2_OC4FE,
	 TIMx_CCMR2_OC4PE,
	 TIMx_CCMR2_OC4M_0,
	 TIMx_CCMR2_OC4M_1,
	 TIMx_CCMR2_OC4M_2,
	 TIMx_CCMR2_OC4CE,
	 /*Other bits for input mode*/
	 TIMx_CCMR2_IC3PSC_0 =2,
	 TIMx_CCMR2_IC3PSC_1,
	 TIMx_CCMR2_IC3F_0,
	 TIMx_CCMR2_IC3F_1,
	 TIMx_CCMR2_IC3F_2,
	 TIMx_CCMR2_IC3F_3,
	 TIMx_CCMR2_IC4PSC_0 =10,
	 TIMx_CCMR2_IC4PSC_1,
	 TIMx_CCMR2_IC4F_0,
	 TIMx_CCMR2_IC4F_1,
	 TIMx_CCMR2_IC4F_2,
	 TIMx_CCMR2_IC4F_3,

	 /*TIMx capture/compare enable register (TIMx_CCER)*/
	 TIMx_CCER_CC1E =0,
	 TIMx_CCER_CC1P,
	 TIMx_CCER_CC1NP =3,
	 TIMx_CCER_CC2E,
	 TIMx_CCER_CC2P,
	 TIMx_CCER_CC2NP =7,
	 TIMx_CCER_CC3E,
	 TIMx_CCER_CC3P,
	 TIMx_CCER_CC3NP =11,
	 TIMx_CCER_CC4E,
	 TIMx_CCER_CC4P,
	 TIMx_CCER_CC4NP =15,



	}Timer_Register_Bits_e;

typedef struct
{
    u8 timer;
    u8 channel;
}TIM_CH_t;



#define 	TIM2_CH1    0
#define 	TIM2_CH2    1
#define 	TIM2_CH3    2
#define 	TIM2_CH4    3
#define 	TIM3_CH1    4
#define 	TIM3_CH2    5
#define 	TIM3_CH3    6
#define 	TIM3_CH4    7
#define 	TIM1_CH1    8
#define 	TIM1_CH2    9
#define 	TIM1_CH3    10
#define 	TIM1_CH4    11


#define TIM_CHANNEL_OUTPUT			0
#define TIM_CHANNEL_IC_TL1			1
#define TIM_CHANNEL_IC_TL2			2
#define TIM_CHANNEL_IC_TRC			3


#define TIM_RISING_EDGE				0
#define TIM_FALLING_EDGE			1

#define TIMER_MASK					0xFF88
#define TIMER_RESET					0x0064

static TIMER_t * Get_timer( u8 timer);
static TIM_CH_t* GET_TIM_CH(u8 Port_Pin);



#define  External_Mode_One 			0
#define  External_Mode_Two  		1

#endif /* TIMER_PRIVATE_H_ */
