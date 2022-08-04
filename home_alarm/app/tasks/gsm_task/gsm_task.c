/*
 * gsm_task.c
 *
 *  Created on: 4 Aug 2022
 *      Author: papai
 */

#include "gsm_task.h"

//TaskHandle_t gsm_task_h;

void gsm_task(void * params);

void gsm_task_create()
{
	BaseType_t result = pdPASS;
	result = xTaskCreate(gsm_task,
				"gsm_t",
				200,
				NULL,
				3,
				NULL);

	configASSERT(result == pdPASS);
}

void gsm_task(void * params)
{
	while(1)
	{
		/*Collect data from the system and control the state*/
		vTaskDelay(pdMS_TO_TICKS(portMAX_DELAY));
	}
}
