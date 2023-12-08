/*
 ******************************************************************************
 * @file           : GPIO_Private.h
 * @Author         : Hassan_Elgabas
 * @brief          : Main program body
 * @Date           : May 5, 2023
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Ayman.
 * All rights reserved.
 *
 ******************************************************************************
 */
#ifndef GPIO_INC_GPIO_PRIVATE_H_
#define GPIO_INC_GPIO_PRIVATE_H_

/*==============================================================================================================================================
 * PRIVATE FUNCTIONS PROTOTYPES
 *==============================================================================================================================================*/

/**
 * @fn			         : GPIO_u8CheckPinConfig
 * @brief		         : Function To Check on Configuration Structure Passed to Program Functions
 * @param[in] Config     : Pointer to Struct @GPIO_PinConfig_t
 * @retval		         : Error Status
 *                           -> GPIO_VALID , GPIO_NOT_VALID
 * @note			         : This Function is a Private Function that Services on GPIO Functions
 **/

static ERRORS_t GPIO_u8CheckPinConfig(const GPIO_PinConfig_t *PinConfig);

/*==============================================================================================================================================
 * MASKS SECTION
 *==============================================================================================================================================*/
#define MODER_MASK 0x3U
#define MODER_PIN_ACCESS 2U

#define PUPDR_MASK 0x3U
#define PUPDR_PIN_ACCESS 2U

#define AFR_MASK 0xFU
#define AFR_PIN_ACCESS 4U

#define OTYPER_MASK 0x1U

#define OSPEEDR_MASK 0x3U
#define OSPEEDR_PIN_ACCESS 4U
/*==============================================================================================================================================
 * MACROS
 *==============================================================================================================================================*/
#define GPIO_PERIPHERAL_NUM 8U
#define REG_WIDTH 8U

#endif /* GPIO_INC_GPIO_PRIVATE_H_ */
