/*
 * SERVO_Program.c
 *
 *  Created on: Dec 7, 2023
 *  Author: MERNA Magdy
 */

#include "SERVO_Interface.h"



ERRORS_t servoVinit(Port_t PORT,Pin_t PIN)
{
	/*Timerx pwm initialization*/
}

ERRORS_t servoVwrite(uint16_t angle)/*90->0.5msec    1->0.005556*/
{
	uint16_t  TIME_HIGH = angle * MILLISECOND_PER_DEGREE;
	uint8_t DUTYCYCLE = TIME_HIGH /SERVO_PERIOD_MILLISECOND;

	/*PWS_GENERATOR_IPS(uint8_t DUTYCYCLE,uint8_t SERVO_PERIOD_MILLISECOND)*/
}
