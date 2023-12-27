/*
 ****************************************************************************************************
									 INCLUDES
 ****************************************************************************************************
    --------------Include section start --------------*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MCAL_GPIO_Interface.h"
#include "Timer_interface.h"
#include "ULTRASONIC_interface.h"
#include 	"ACC.h"



/* --------------Include section end   --------------*/


 /*
 ****************************************************************************************************
									 Global Variables
 ****************************************************************************************************
*/
u8 DutyCycle;
f32 distaceMeasured;
extern u8 data;
extern Timer_No_e Global_uddtTimerNumber;
extern u8  Global_u8DutyCycle;
extern Timer_Channl_e Global_uddtChNo;
extern u8 Global_u8CruiseControlMode;
extern u8 Global_SafeDistance;


 /*
 ****************************************************************************************************
									 ACC Function Definitions
 ****************************************************************************************************
*/

// (_TIM2, 64, 10000-1, 6, 1, DutyCycle)
/**
 * @brief Function that takes timer setting and initializes them
 * @param Copy_uddtTMR
 * @param Copy_uddtChNo
 * @param Copy_u8DutyCycle
 * @return void
 */
void ACC_Init(Timer_No_e Copy_uddtTMR, Timer_Channl_e Copy_uddtChNo,u8 Copy_u8_DutyCycle)
{
	DutyCycle = Copy_u8_DutyCycle; // 1 -->100
    TimerX_PWM(Copy_uddtTMR,Copy_uddtChNo,DutyCycle);
}

/**
 * @brief Changed speed of motors through changing duty cycle
 * @param Copy_uddtTMR
 * @param Copy_u8DutyCycle
 * @return void
 */
void ACC_voidChangeSpeed(Timer_No_e Copy_uddtTMR, u8 Copy_u8DutyCycle)
{
    TimerX_PWM(Copy_uddtTMR,CH3,Copy_u8DutyCycle);

}


/**
 * @brief Depending on UART input, set duty cycle speed
 * @details CCR1 = (Duty Cycle * (ARR + 1)) / 100
 * @param Copy_uddtTMR The timer to set speed in
 * @param Copy_u8Signal Choose one of 4 speeds to set: 0, 30, 60 or 90
 */
void ACC_voidSetSpeed(Timer_No_e Copy_uddtTMR, u8 Copy_u8Signal)
{
	/*Check if in Normal Cruise Control*/
	if(20 == Global_u8CruiseControlMode)
	{
		if(0 == Copy_u8Signal)
		{
			Global_u8DutyCycle = 1;
            TimerX_PWM(Copy_uddtTMR,CH3,Global_u8DutyCycle);
		}
		else if (3 == Copy_u8Signal)
		{
			Global_u8DutyCycle = 30;
            TimerX_PWM(Copy_uddtTMR,CH3,Global_u8DutyCycle);
		}
		else if (6 == Copy_u8Signal)
		{
			Global_u8DutyCycle = 60;
            TimerX_PWM(Copy_uddtTMR,CH3,Global_u8DutyCycle);
		}
		else if (9 == Copy_u8Signal)
		{
			Global_u8DutyCycle = 90;
            TimerX_PWM(Copy_uddtTMR,CH3,Global_u8DutyCycle);
		}
	}

}

/**Call in while if in adaptive mode because will keep adapting speed*/
/**
 * @brief Handles the adaptive cruise control. Once we are in the adaptive mode the ultrasonic measures the distace between the car and the object ahead.
 * @details If the distance meausred is more than the safe distance, we speed up the car. If the distance is less than the safe disatnce, the duty cycle is decreased therefore slowing the car
 * @param None
 * @return  void
 */
void ACC_AdaptiveSpeedControl(void)
{
	if(30 == Global_u8CruiseControlMode)
	{
		distaceMeasured = HULTRASONIC_f32GetDistance();
		/*Measure Distace using Ultrasonic*/

		/* If distace less than safe ditance adjust and decrease speed*/
		if((f32)Global_SafeDistance > distaceMeasured)
		{
			/*Check duty cycle, and make sure it is less by 20 */
			if(Global_u8DutyCycle > 20)
			{
				Global_u8DutyCycle -= 10;
                TimerX_PWM(TIMER_2_,CH3,Global_u8DutyCycle);
			}

		}
		/* If distace more than safe ditance adjust and increase speed*/
		else if((f32)Global_SafeDistance < distaceMeasured)
		{
			/*Check duty cycle, and make sure it is less than 90 */
			if(Global_u8DutyCycle < 90)
			{
				Global_u8DutyCycle += 10;
                TimerX_PWM(TIMER_2_,CH3,Global_u8DutyCycle);
			}
		}
		else if ((f32)8 > distaceMeasured){

			//Global_u8DutyCycle = 0;
			//MTIM_voidSetCCR1(Global_uddtTimerNumber, (1)-1);
			ACC_voidStopCar();


			/*keep else empty for MISRA C */
		}
	}

}



/**
 * @brief Function that stops the car
 * @param None
 * @return void
 *
 */
void ACC_voidStopCar(void)
{
    TimerX_PWM(TIMER_2_,CH3,0);

}



