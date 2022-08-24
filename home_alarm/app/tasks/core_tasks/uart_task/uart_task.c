/*
 * uart_task.c
 *
 *  Created on: 4 Aug 2022
 *      Author: papai
 */


#include "uart_task.h"
#include "usart.h"
#include "circbuffer.h"

//TaskHandle_t uart_task_h;
uint8_t data_byte = 0;


void uart_task(void * params);

void uart_task_create()
{
	BaseType_t result = pdPASS;
	result = xTaskCreate(uart_task,
				"uart_t",
				200,
				NULL,
				2,
				NULL);

	configASSERT(result == pdPASS);
}

void uart_task(void * params)
{
	taskENTER_CRITICAL();
	HAL_StatusTypeDef status = HAL_ERROR;
	status = HAL_UART_Receive_DMA(&huart2, &data_byte, 1);
	taskEXIT_CRITICAL();

	while(1)
	{
		/*Wait for data on the uart*/
		vTaskDelay(pdMS_TO_TICKS(portMAX_DELAY));

		/*Run URC scanning*/
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UBaseType_t uxSavedInterruptStatus;
	uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();
	circbuffer_insert(&data_byte, 1);
	taskEXIT_CRITICAL_FROM_ISR(uxSavedInterruptStatus);
}
