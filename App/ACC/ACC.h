

/*Preprocessor file guard*/
#ifndef ACC_ACC_H_
#define ACC_ACC_H_

 /*
 ****************************************************************************************************
									 ACC Prototypes
 ****************************************************************************************************
*/

/**
 * @brief Function that takes timer setting and initializes them
 * @param Copy_e_Timer
 * @param Copy_e_Channel
 * @param Copy_u8_DutyCycle
 * @return void
 */
void ACC_Init(Timer_No_e Copy_uddtTMR, Timer_Channl_e Copy_uddtChNo,u8 Copy_u8_DutyCycle);

/**
 * @brief Changed speed of motors through changing duty cycle
 * @param Copy_uddtTMR
 * @param Copy_u8DutyCycle
 * @return void
 */
void ACC_voidChangeSpeed(Timer_No_e Copy_uddtTMR, u8 Copy_u8DutyCycle);

/**
 * @brief
 * @param Copy_uddtTMR
 * @param Copy_u8Signal
 */
void ACC_voidSetSpeed(Timer_No_e Copy_uddtTMR, u8 Copy_u8Signal);

void ACC_AdaptiveSpeedControl(void);

/**
 * @brief
 */
void ACC_voidStopCar(void);

#endif /* ACC_ACC_H_ */
