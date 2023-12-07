/*
 * SERVO_Interface.h
 *
 *  Created on: Dec 7, 2023
 *  Author: MERNA MAGDY
 */

#ifndef SERVO_INTERFACE_H_
#define SERVO_INTERFACE_H_
#include "GPIO_Interface.h"
//#include "ErrTypes.h"

#define MILLISECOND_PER_DEGREE 		(float)(0.5/90)
#define SERVO_PERIOD_MILLISECOND	20
/*
 * @brief: 		it initializes the OCx PIN for the servo.
 * @parameter:	PORT is the OCx port number.
 * @parameter:	PIN is the OCx pin number.
 * @retval:		std_error.
 * */

ERRORS_t servoVinit(Port_t PORT,Pin_t PIN);

/*
 * @brief: 		it converts the desired angle into duty cycle and feeds it to the PWM signal generator.
 * @parameter:	angle is the desired servo angle.
 * @retval:		void.
 * */
ERRORS_t servoVwrite(uint16_t angle);

#endif /* SERVO_INTERFACE_H_ */
