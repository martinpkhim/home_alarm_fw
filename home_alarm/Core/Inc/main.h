/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32l1xx_hal.h"

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
#define ADC_VBAT_Pin GPIO_PIN_0
#define ADC_VBAT_GPIO_Port GPIOA
#define SENS0_Pin GPIO_PIN_1
#define SENS0_GPIO_Port GPIOA
#define SENS1_Pin GPIO_PIN_4
#define SENS1_GPIO_Port GPIOA
#define SENS1_EXTI_IRQn EXTI4_IRQn
#define SENS2_Pin GPIO_PIN_5
#define SENS2_GPIO_Port GPIOA
#define SENS2_EXTI_IRQn EXTI9_5_IRQn
#define SENS3_Pin GPIO_PIN_6
#define SENS3_GPIO_Port GPIOA
#define SENS3_EXTI_IRQn EXTI9_5_IRQn
#define SENS4_Pin GPIO_PIN_7
#define SENS4_GPIO_Port GPIOA
#define SENS4_EXTI_IRQn EXTI9_5_IRQn
#define SENS5_Pin GPIO_PIN_0
#define SENS5_GPIO_Port GPIOB
#define SENS5_EXTI_IRQn EXTI0_IRQn
#define SENS6_Pin GPIO_PIN_1
#define SENS6_GPIO_Port GPIOB
#define SENS6_EXTI_IRQn EXTI1_IRQn
#define SENS7_Pin GPIO_PIN_2
#define SENS7_GPIO_Port GPIOB
#define SENS7_EXTI_IRQn EXTI2_IRQn
#define SENS8_Pin GPIO_PIN_10
#define SENS8_GPIO_Port GPIOB
#define SENS8_EXTI_IRQn EXTI15_10_IRQn
#define SENS9_Pin GPIO_PIN_11
#define SENS9_GPIO_Port GPIOB
#define SENS9_EXTI_IRQn EXTI15_10_IRQn
#define COL0_Pin GPIO_PIN_12
#define COL0_GPIO_Port GPIOB
#define COL1_Pin GPIO_PIN_13
#define COL1_GPIO_Port GPIOB
#define COL2_Pin GPIO_PIN_14
#define COL2_GPIO_Port GPIOB
#define ROW0_Pin GPIO_PIN_15
#define ROW0_GPIO_Port GPIOB
#define ROW1_Pin GPIO_PIN_8
#define ROW1_GPIO_Port GPIOA
#define ROW2_Pin GPIO_PIN_9
#define ROW2_GPIO_Port GPIOA
#define ROW3_Pin GPIO_PIN_10
#define ROW3_GPIO_Port GPIOA
#define PWRKEY_Pin GPIO_PIN_15
#define PWRKEY_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_6
#define SPI1_CS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
