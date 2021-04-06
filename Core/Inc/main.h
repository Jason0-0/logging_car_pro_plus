/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define J2_STEP_L_DIR_Pin GPIO_PIN_4
#define J2_STEP_L_DIR_GPIO_Port GPIOE
#define J1_STEP_R_DIR_Pin GPIO_PIN_5
#define J1_STEP_R_DIR_GPIO_Port GPIOE
#define K1_STEP_R_EN_Pin GPIO_PIN_6
#define K1_STEP_R_EN_GPIO_Port GPIOE
#define B_STEP_L_PUL_Pin GPIO_PIN_12
#define B_STEP_L_PUL_GPIO_Port GPIOH
#define C_STEP_R_PUL_Pin GPIO_PIN_11
#define C_STEP_R_PUL_GPIO_Port GPIOH
#define E_SERVO_RAISE_L_Pin GPIO_PIN_15
#define E_SERVO_RAISE_L_GPIO_Port GPIOD
#define F_SERVO_RAISE_R_Pin GPIO_PIN_14
#define F_SERVO_RAISE_R_GPIO_Port GPIOD
#define G_SERVO_PLATFORM_Pin GPIO_PIN_13
#define G_SERVO_PLATFORM_GPIO_Port GPIOD
#define H_SERVO_GRABER_Pin GPIO_PIN_12
#define H_SERVO_GRABER_GPIO_Port GPIOD
#define K2_STEP_L_EN_Pin GPIO_PIN_12
#define K2_STEP_L_EN_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
