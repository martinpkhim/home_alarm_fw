/*
 * gsm_task.c
 *
 *  Created on: 4 Aug 2022
 *      Author: papai
 */

#include "gsm_task.h"
#include "M66.h"
#include "main.h"
#include "usart.h"

//TaskHandle_t gsm_task_h;

typedef enum GSM_STATE
{
	GSM_MODULE_START = 0,
	GSM_CHECK_CREDENTIALS,
	GSM_CONNECT,
	GSM_CONNECTED,
	GSM_SEND,

}GSM_STATE;

GSM_STATE gsm_sm = GSM_MODULE_START;
m66_ctrl m66_ctrl_struct = {0};

void powerkey_switch(bool state);
bool send_data(uint8_t * data, uint16_t len);
void delay_gsm(uint32_t);

void gsm_task(void * params);

void gsm_task_create()
{
	BaseType_t result = pdPASS;
	result = xTaskCreate(gsm_task,
				"gsm_t",
				400,
				NULL,
				4,
				NULL);

	configASSERT(result == pdPASS);
}

void gsm_task(void * params)
{

	m66_ctrl_struct.data_send = send_data;
	m66_ctrl_struct.pwrkey_switch = powerkey_switch;
	m66_ctrl_struct.delay = delay_gsm;
	M66_ctrl_init(&m66_ctrl_struct);

	while(1)
	{
		switch(gsm_sm)
		{
			case GSM_MODULE_START:
			{
				M66_hw_reset();
				gsm_sm = GSM_CHECK_CREDENTIALS;
				break;
			}
			case GSM_CHECK_CREDENTIALS:
			{
				bool status = true;
				/*Disable the command echoing*/
				M66_disable_echo();
				/*Check the pin code status*/
				M66_check_pin(&status);
				if(!status)
				{
					//M66_enter_pin(1234);
				}

				/*Set text mode for SMS*/
				 M66_set_mode(1);

				 /*Save the currently set config*/
				M66_save_config();

				gsm_sm = GSM_CONNECT;

				break;
			}
			case GSM_CONNECT:
			{
				/*Enable the radio*/
				M66_switch_radio(1);
				/*Select the operator based on the mccmnc*/
				M66_select_operator(21670);

				/*Enable bluetooth*/
				M66_set_bt_state(1);
				/*Set bluetooth local name*/
				M66_set_bt_name("ALARM");
				/*Set the visibility of the bluetooth device*/
				M66_set_bt_visibility(1);

				uint8_t netstat = 0;
				do
				{
					/*Query the network status*/
					M66_query_network_status(&netstat);
					vTaskDelay(pdMS_TO_TICKS(500));
				}while((netstat != 1) || (netstat != 5));

				gsm_sm = GSM_CONNECTED;

				break;
			}
			case GSM_CONNECTED:
			{
				uint8_t netstat = 0;
				M66_query_network_status(&netstat);

				if((netstat != 1) || (netstat != 5))
				{
					gsm_sm = GSM_MODULE_START;
				}

				break;
			}
			case GSM_SEND:
			{
				M66_send_sms("+36702047619", "HELLO BABE");

				gsm_sm = GSM_CONNECTED;
				break;
			}
			default:
			{
				gsm_sm = GSM_MODULE_START;
				break;
			}
		}

		/*Collect data from the system and control the state*/
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}


void powerkey_switch(bool state)
{
	taskENTER_CRITICAL();
	GPIO_PinState pin_state = (state) ? GPIO_PIN_SET : GPIO_PIN_RESET;
	HAL_GPIO_WritePin(PWRKEY_GPIO_Port, PWRKEY_Pin, pin_state);
	taskEXIT_CRITICAL();
}

bool send_data(uint8_t * data, uint16_t len)
{
	return (HAL_UART_Transmit(&huart2, data, len, 2000) == HAL_OK) ? true : false;
}

void delay_gsm(uint32_t delay_ms)
{
	vTaskDelay(pdMS_TO_TICKS(delay_ms));
	//HAL_Delay(delay);
}

