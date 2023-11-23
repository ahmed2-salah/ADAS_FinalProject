/**
 * @file MotorDriver_Interface.h
 * @brief Interface file for the motor driver.
 *
 * This file contains the function prototypes for controlling the motor driver.

 */

#ifndef HAL_MOTORDRIVER_MOTORDRIVER_INTERFACE_H_
#define HAL_MOTORDRIVER_MOTORDRIVER_INTERFACE_H_

/**
 * @brief Initializes the motor driver.
 *
 * This function initializes the motor driver.
 */
void MotorDriver_voidInit(void);


/**
 * @brief Moves the motors forward.
 *
 * This function moves the motors forward.
 */
void MotorDriver_voidMoveForward(void);

/**
 * @brief Moves the motors backward.
 *
 * This function moves the motors backward.
 */
void MotorDriver_voidMoveBackward(void);

/**
 * @brief Turns the motors right.
 *
 * This function turns the motors right.
 */
void MotorDriver_voidMoveRight(void);

/**
 * @brief Turns the motors left.
 *
 * This function turns the motors left.
 */
void MotorDriver_voidMoveLeft(void);

/**
 * @brief Stops the motors.
 *
 * This function stops the motors.
 */
void MotorDriver_voidStop(void);

#endif /* HAL_MOTORDRIVER_MOTORDRIVER_INTERFACE_H_ */
