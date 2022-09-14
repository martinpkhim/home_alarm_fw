/*
 * init_task.c
 *
 *  Created on: 4 Aug 2022
 *      Author: papai
 */

#include "init_task.h"
#include "manager_task.h"
#include "uart_task.h"
#include "gsm_task.h"
#include "io_task.h"
#include "lcd_task.h"
#include "numpad_task.h"
#include "interface.h"
#include "flash.h"
#include "config.h"

//TaskHandle_t init_task_h;

void init_task(void * params);

void init_task_create()
{
	BaseType_t result = pdPASS;
	result = xTaskCreate(init_task,
				"init_t",
				100,
				NULL,
				1,
				NULL);

	configASSERT(result == pdPASS);
}

void init_task(void * params)
{
	while(1)
	{
		taskENTER_CRITICAL();
		if(!config_load())
		{
			config_init();
		}
		taskEXIT_CRITICAL();

		interface_init();

		/*Call the initialising function of each task*/
		manager_task_create();
		//uart_task_create();
		gsm_task_create();
		io_task_create();
		lcd_task_create();
		numpad_task_create();

		/*Delete the init_task after initialisation*/
		vTaskDelete(NULL);
	}
}
