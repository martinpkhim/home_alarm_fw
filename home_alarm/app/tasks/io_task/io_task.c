/*
 * io_task.c
 *
 *  Created on: 4 Aug 2022
 *      Author: papai
 */

#include "io_task.h"
#include <stdbool.h>
#include "interface.h"
#include "adc.h"
#include "gpio.h"

typedef struct io_read
{
	uint16_t 		GPIO_Pin;
	GPIO_TypeDef * 	GPIO_Port;
}io_read;

//TaskHandle_t 	io_task_h;
bool			it_flag = false;
io_read			io_struct[9] =
{
		{.GPIO_Port = SENS1_GPIO_Port, .GPIO_Pin = SENS1_Pin },
		{.GPIO_Port = SENS2_GPIO_Port, .GPIO_Pin = SENS2_Pin },
		{.GPIO_Port = SENS3_GPIO_Port, .GPIO_Pin = SENS3_Pin },
		{.GPIO_Port = SENS4_GPIO_Port, .GPIO_Pin = SENS4_Pin },
		{.GPIO_Port = SENS5_GPIO_Port, .GPIO_Pin = SENS5_Pin },
		{.GPIO_Port = SENS6_GPIO_Port, .GPIO_Pin = SENS6_Pin },
		{.GPIO_Port = SENS7_GPIO_Port, .GPIO_Pin = SENS7_Pin },
		{.GPIO_Port = SENS8_GPIO_Port, .GPIO_Pin = SENS8_Pin },
		{.GPIO_Port = SENS9_GPIO_Port, .GPIO_Pin = SENS9_Pin },
};

void io_task(void * params);

void io_task_create()
{
	BaseType_t result = pdPASS;
	result = xTaskCreate(io_task,
				"io_t",
				200,
				NULL,
				3,
				NULL);

	configASSERT(result == pdPASS);
}

void io_task(void * params)
{
	while(1)
	{
		/*Collect data from the system and control the state*/

		io_state_data 	io_data 	= {0};
		uint32_t adc_val = 0;
		float adc_val_f = 0.0f;
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 5000);
		adc_val = HAL_ADC_GetValue(&hadc);
		adc_val_f = adc_val * (3300.0 / 4095.0);
		io_data.vbat = ((adc_val_f * (10000.0f + 1000.f)) / (1000.0f)) / 1000.0;

		for(uint8_t i = 0;i < 9;i++)
		{
			io_data.io_state = HAL_GPIO_ReadPin(io_struct[i].GPIO_Port, io_struct[i].GPIO_Pin) << i;
		}

		xQueueSend(io_queue, (void*)&io_data, pdMS_TO_TICKS(100));

		vTaskDelay(pdMS_TO_TICKS(500));
	}
}






//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	it_flag = true;
//
//	switch(GPIO_Pin)
//	{
//		case SENS1_Pin:
//		{
//
//			break;
//		}
//		case SENS2_Pin:
//		{
//
//			break;
//		}
//		case SENS3_Pin:
//		{
//
//			break;
//		}
//		case SENS4_Pin:
//		{
//
//			break;
//		}
//		case SENS5_Pin:
//		{
//
//			break;
//		}
//		case SENS6_Pin:
//		{
//
//			break;
//		}
//		case SENS7_Pin:
//		{
//
//			break;
//		}
//		case SENS8_Pin:
//		{
//
//			break;
//		}
//		case SENS9_Pin:
//		{
//
//			break;
//		}
//		default:
//		{
//			/*should not happen*/
//			break;
//		}
//	}
//}
