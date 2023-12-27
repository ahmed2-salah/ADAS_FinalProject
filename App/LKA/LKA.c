/*
 * LKA.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Ahmed
 */
#include"STM32F446xx.h"
#include"stdint.h"
#include"IR_Interface.h"
#include"MotorDriver_Interface.h"
#include"ErrTypes.h"
volatile uint8_t left_IR = 0, right_IR = 0;

/*
 * @ brief LKS Init.
 * */
void LKS_Init(void)
{
	IR_Init();
}
/**
 * @brief LKS mode task.
 */
//void APP_LKS_vTask(void) {
//	// Read left and right IR sensor values
//	left_IR = IR_u8Read_LeftIR();
//
//	right_IR =IR_u8Read_RightIR();
//
//	while (1) {
//		/* If the car is inside the lane / No lane markings are detected on both sides */
//		if (left_IR == BLACK && right_IR == BLACK) {
//			// Move the car forward
//			MotorDriver_voidMoveForward(5);
//		}
//			/* If the car drifts to the right / Lane markings are detected on the right side */
//		else if (left_IR == BLACK && right_IR == WHITE) {
//			// Steer the car to the left
//			MotorDriver_voidMoveLeft(5,2);
//		}
//			/* If the car drifts to the left / Lane markings are detected on the left side */
//		else if (left_IR == WHITE && right_IR == BLACK) {
//			// Steer the car to the right
//			MotorDriver_voidMoveRight(5, 2);
//		} else{
//			// Stop the car
//			MotorDriver_voidStop();
//		}
//	}
//}

