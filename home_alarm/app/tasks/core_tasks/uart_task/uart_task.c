/*
 * uart_task.c
 *
 *  Created on: 4 Aug 2022
 *      Author: papai
 */


#include "uart_task.h"

//TaskHandle_t uart_task_h;

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
	while(1)
	{
		/*Wait for data on the uart*/
		vTaskDelay(pdMS_TO_TICKS(portMAX_DELAY));
	}
}
