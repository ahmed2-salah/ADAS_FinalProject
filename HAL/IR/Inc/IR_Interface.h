/**
 * @file IR_Sensor_IR_Interface.h
 * @brief Interface file for the IR sensor.
 *
 * This file contains the function declarations and constants for the IR sensor interface.
 */

#ifndef IR_INTERFACE_H_
#define IR_INTERFACE_H_
/**
 * @def WHITE
 * @brief Constant representing the white color.
 */
#define WHITE   0

/**
 * @def BLACK
 * @brief Constant representing the black color.
 */
#define BLACK   1

/**
 * @brief Initializes the IR sensors.
 *
 * This function initializes the IR sensors.
 */
void IR_Init(void);

/**
 * @brief Reads the value of the right IR sensor.
 *
 * @return The value of the right IR sensor (either WHITE or BLACK).
 */
void IR_u8Read_RightIR(void);

/**
 * @brief Reads the value of the left IR sensor.
 *
 * @return The value of the left IR sensor (either WHITE or BLACK).
 */
void IR_u8Read_LeftIR(void);


#endif /* IR_INTERFACE_H_ */
