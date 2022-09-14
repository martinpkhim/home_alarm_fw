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
#include "semphr.h"
#include <stdbool.h>
#include "tim.h"
#include "config.h"
#include <stdio.h>

#define		MAX_KEY_CNT		(7)

//TaskHandle_t manager_task_h;

typedef enum sys_states
{
	STATE_STARTUP = 0,
	STATE_INIT,
	STATE_DISARMED,
	STATE_ARMED,
	STATE_ALERT,
	STATE_CONFIG,
}sys_states;

sys_states system_state = STATE_STARTUP;

void buzzer_sound();
void manager_task(void * params);
static void send_text(lcd_data * data);

void manager_task_create()
{
	BaseType_t result = pdPASS;
	result = xTaskCreate(manager_task,
				"manager_t",
				400,
				NULL,
				2,
				NULL);

	configASSERT(result == pdPASS);
}

void manager_task(void * params)
{
	lcd_data 		lcd_data 				= {0};
	io_state_data 	io_data 				= {0};
	char			key_buffer[MAX_KEY_CNT]	= {0};
	uint8_t			key_cnt					= 0;
	char			armed_str[]				= "ARMED";
	char			disarmed_str[]			= "DISARMED";
	char			alarm_str[]				= "ALARM";
	char			config_str[]			= "CONFIG";

	while(1)
	{
		/*Collect data from the system and control the state*/
		switch(system_state)
		{
			case STATE_STARTUP:
			{
				/*Take the numpad control*/
				xSemaphoreTake(numpad_mutex, pdMS_TO_TICKS(500));

				/*Display splash screen, version info etc*/
				memcpy(lcd_data.text, "HOME ALARM V1.0", 15);
				lcd_data.clr = true;
				lcd_data.led = true;
				xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

				vTaskDelay(pdMS_TO_TICKS(5000));

				system_state = STATE_INIT;

				break;
			}
			case STATE_INIT:
			{
				/*Notify user of disarmed state, wait for arming*/
				memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
				memcpy(lcd_data.text, disarmed_str, strlen(disarmed_str));
				lcd_data.crlf = true;
				lcd_data.led  = false;
				xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

				xSemaphoreGive(numpad_mutex);

				system_state = STATE_DISARMED;

				break;
			}
			case STATE_DISARMED:
			{
				/*Menu system here for configuration*/
				/* *0# puts the device in config mode*/
				/* *password# arms the device*/
				char key;
				char code[5] = {0};
				sscanf(key_buffer, "*%[^#]#", code);
				if(xQueueReceive(key_queue, (void*)&key, pdMS_TO_TICKS(100)) == pdTRUE)
				{
					key_buffer[key_cnt] = key;
					key_cnt++;

					if(key_cnt >= MAX_KEY_CNT)
					{
						key_cnt = 0;
						memset(key_buffer, '\0', sizeof(key_buffer));

						/*Notify user of disarmed state, wait for arming*/
						memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
						memcpy(lcd_data.text, disarmed_str, strlen(disarmed_str));
						lcd_data.crlf = true;
						xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

					}
					else if((atoi(code) == config.password) && (config.password != 0))
					{
						key_cnt = 0;
						memset(key_buffer, '\0', sizeof(key_buffer));

						/*Notify user of disarmed state, wait for arming*/
						memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
						memcpy(lcd_data.text, armed_str, strlen(armed_str));
						lcd_data.crlf = true;
						lcd_data.led  = true;
						xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

						buzzer_sound();

						/*Before arming, wait a few seconds*/
						vTaskDelay(pdMS_TO_TICKS(config.arming_delay));

						system_state = STATE_ARMED;
					}
					else if(strcmp(key_buffer, "*0#") == 0)
					{
						/*Config mode*/
						/*Notify user of disarmed state, wait for arming*/
						memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
						memcpy(lcd_data.text, config_str, strlen(config_str));
						lcd_data.crlf = false;
						lcd_data.led  = true;
						xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

						bool config_state = true;
						xQueueSend(config_queue, (void*)&config_state, pdMS_TO_TICKS(100));

						system_state = STATE_CONFIG;
					}
				}

				break;
			}
			case STATE_ARMED:
			{

				/* *password# disarms the device*/
				char key;
				char code[5] = {0};
				sscanf(key_buffer, "*%[^#]#", code);
				if(xQueueReceive(key_queue, (void*)&key, pdMS_TO_TICKS(100)) == pdTRUE)
				{
					key_buffer[key_cnt] = key;
					key_cnt++;

					if(key_cnt >= MAX_KEY_CNT)
					{
						key_cnt = 0;
						memset(key_buffer, '\0', sizeof(key_buffer));

						/*Notify user of disarmed state, wait for arming*/
						memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
						memcpy(lcd_data.text, armed_str, strlen(armed_str));
						lcd_data.crlf = true;
						xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

					}
					else if((atoi(code) == config.password) && (config.password != 0))
					{
						key_cnt = 0;
						memset(key_buffer, '\0', sizeof(key_buffer));

						/*Notify user of disarmed state, wait for arming*/
						memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
						memcpy(lcd_data.text, disarmed_str, strlen(disarmed_str));
						lcd_data.crlf = true;
						lcd_data.led  = false;
						xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

						buzzer_sound();

						system_state = STATE_DISARMED;
					}
				}

				/*Wait for IO event to signal alert or go back to disarmed state*/
				if(xQueueReceive(io_queue, (void*)&io_data, pdMS_TO_TICKS(100)) == pdTRUE)
				{
					/*If any of the intputs are high*/
					if((io_data.io_state & config.sensor_mask) != 0)
					{
						/*Notify user of disarmed state, wait for arming*/
						memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
						memcpy(lcd_data.text, alarm_str, strlen(alarm_str));
						lcd_data.crlf = true;
						xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

						/*Create a message containing the alert info and send it to the gsm task*/
						msg_data sms_data = {0};
						uint8_t ptr = 0;
						ptr += sprintf(sms_data.text, "ALARM!\r\n");
						for(uint8_t i = 0;i < 9;i++)
						{
							ptr += sprintf(&sms_data.text[i], "S%d: %d\r\n",i, ((io_data.io_state) & (1 << i)) ? 1 : 0);
						}

						xQueueSend(sms_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

						system_state = STATE_ALERT;
						break;
					}
				}

				vTaskDelay(pdMS_TO_TICKS(500));

				break;
			}
			case STATE_ALERT:
			{
				/*Wait for user action to return to disarmed state*/

				/* *password# disarms the device*/
				char key;
				char code[5] = {0};
				sscanf(key_buffer, "*%[^#]#", code);
				if(xQueueReceive(key_queue, (void*)&key, pdMS_TO_TICKS(100)) == pdTRUE)
				{
					key_buffer[key_cnt] = key;
					key_cnt++;

					if(key_cnt >= MAX_KEY_CNT)
					{
						key_cnt = 0;
						memset(key_buffer, '\0', sizeof(key_buffer));

						/*Notify user of disarmed state, wait for arming*/
						memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
						memcpy(lcd_data.text, alarm_str, strlen(alarm_str));
						lcd_data.crlf = true;
						xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

					}
					else if((atoi(code) == config.password) && (config.password != 0))
					{
						key_cnt = 0;
						memset(key_buffer, '\0', sizeof(key_buffer));

						/*Notify user of disarmed state*/
						memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
						memcpy(lcd_data.text, disarmed_str, 9);
						lcd_data.crlf = true;
						xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

						buzzer_sound();

						system_state = STATE_DISARMED;
					}
				}

				break;
			}
			case STATE_CONFIG:
			{
				msg_data msg_data_buf = {0};
				if(xQueueReceive(msg_queue, (void*)&msg_data_buf, pdMS_TO_TICKS(100)) == pdTRUE)
				{
					char tel_num_new[13]  = {0};
					char passw_str_new[5] = {0};
					char passw_str_old[5] = {0};
					char mask_str[5] 	  = {0};
					char delay_str[5] 	  = {0};
					msg_data rsp_msg_data = {0};
					if(sscanf(msg_data_buf.text, "$%[^;];%[^;];%[^;];%[^;];%[^;];", tel_num_new, passw_str_old, passw_str_new, mask_str, delay_str) == 5)
					{

						uint16_t old_pw = atoi(passw_str_old);

						if(config.password == old_pw)
						{

							memcpy(config.tel_num, tel_num_new, sizeof(tel_num_new));
							config.password 		= atoi(passw_str_new);
							config.sensor_mask 		= atoi(mask_str);
							config.arming_delay 	= atoi(delay_str);

							config_save();

							sprintf(rsp_msg_data.text, "CONFIG OK");
							xQueueSend(rsp_msg_queue, (void*)&rsp_msg_data, pdMS_TO_TICKS(100));

							vTaskDelay(pdMS_TO_TICKS(5000));

							key_cnt = 0;
							memset(key_buffer, '\0', sizeof(key_buffer));

							/*Notify user of disarmed state, wait for arming*/
							memset(lcd_data.text, '\0', LCD_BUFF_MAX_SIZE);
							memcpy(lcd_data.text, disarmed_str, strlen(disarmed_str));
							lcd_data.crlf = true;
							xQueueSend(lcd_queue, (void*)&lcd_data, pdMS_TO_TICKS(100));

							bool config_state = false;
							xQueueSend(config_queue, (void*)&config_state, pdMS_TO_TICKS(100));

							buzzer_sound();

							system_state = STATE_DISARMED;
						}

					}
					else
					{
						sprintf(rsp_msg_data.text, "CONFIG NOK");
						xQueueSend(rsp_msg_queue, (void*)&rsp_msg_data, pdMS_TO_TICKS(100));
					}

				}
				break;
			}
		}

	}
}


void buzzer_sound()
{
	TIM4->ARR = 137;
	TIM4->CCR2 = 68;
	for(uint8_t i = 0;i < 10;i++)
	{
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
		vTaskDelay(pdMS_TO_TICKS(80));
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
		vTaskDelay(pdMS_TO_TICKS(80));
	}
}

static void send_text(lcd_data * data)
{
	xQueueSend(lcd_queue, (void*)data, pdMS_TO_TICKS(100));
}
