/*
 * manager_task.c
 *
 *  Created on: 4 Aug 2022
 *      Author: papai
 */


#include "manager_task.h"
#include "interface.h"
#include <stdlib.h>
#include <string.h>

//TaskHandle_t manager_task_h;

typedef enum sys_states
{
	STATE_STARTUP = 0,
	STATE_INIT,
	STATE_DISARMED,
	STATE_ARMED,
	STATE_ALERT,
}sys_states;

sys_states system_state = STATE_STARTUP;

void manager_task(void * params);

void manager_task_create()
{
	BaseType_t result = pdPASS;
	result = xTaskCreate(manager_task,
				"manager_t",
				100,
				NULL,
				2,
				NULL);

	configASSERT(result == pdPASS);
}

void manager_task(void * params)
{
	lcd_data 		lcd_data 	= {0};
	io_state_data 	io_data 	= {0};

	while(1)
	{
		/*Collect data from the system and control the state*/
		switch(system_state)
		{
			case STATE_STARTUP:
			{
				/*Display splash screen, version info etc*/
				memcpy(lcd_data.text, "HOME ALARM V1.0", 15);
				xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));


				vTaskDelay(pdMS_TO_TICKS(5000));

				system_state = STATE_INIT;

				break;
			}
			case STATE_INIT:
			{
				/*Do a system check, display results*/
				memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
				memcpy(lcd_data.text, "INITIALISING...", 15);
				xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

				vTaskDelay(pdMS_TO_TICKS(2000));

				/*Wait for status report from IO task (battery voltage, sensors etc.)*/
				xQueueReceive(io_queue, (void*)&io_data, pdMS_TO_TICKS(portMAX_DELAY));


				memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
				if(io_data.vbat >= 3.2)
				{
					memcpy(lcd_data.text, "VBAT OK", 7);
				}
				else
				{
					memcpy(lcd_data.text, "VBAT ERROR", 10);
				}

				xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

				vTaskDelay(pdMS_TO_TICKS(2000));

				if(io_data.io_state == 0)
				{
					memcpy(lcd_data.text, "I/O OK", 7);
				}
				else
				{
					memcpy(lcd_data.text, "I/O ERROR", 9);
				}

				xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

				vTaskDelay(pdMS_TO_TICKS(2000));

				system_state = STATE_DISARMED;

				break;
			}
			case STATE_DISARMED:
			{
				/*Notify user of disarmed state, wait for arming*/
				memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
				memcpy(lcd_data.text, "DISARMED", 9);
				xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

				system_state = STATE_ARMED;

				break;
			}
			case STATE_ARMED:
			{
				/*Wait for IO event to signal alert or go back to disarmed state*/

				//system_state = STATE_ALERT;

				break;
			}
			case STATE_ALERT:
			{
				/*Wait for user action to return to disarmed state*/

				system_state = STATE_DISARMED;

				break;
			}
		}

	}
}
