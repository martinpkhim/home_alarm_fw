/*
 * app.c
 *
 *  Created on: 4 Aug 2022
 *      Author: papai
 */

#include "app.h"
#include "FreeRTOS.h"
#include "task.h"
#include "init_task.h"
#include "stm32l1xx.h"


void app_main()
{

	init_task_create();

	vTaskStartScheduler();

	/*Should not reach here*/
	while(1)
	{
		__NOP();
	}
}
