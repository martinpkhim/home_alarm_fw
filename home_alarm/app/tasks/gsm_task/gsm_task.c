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
#include "circbuffer.h"
#include "interface.h"
#include "config.h"

//TaskHandle_t gsm_task_h;

typedef enum GSM_STATE
{
	BT_CONFIGURE = 0,
	BT_CONNECT,
	BT_CONNECTED,
	GSM_MODULE_START,
	GSM_CHECK_CREDENTIALS,
	GSM_CONNECT,
	GSM_CONNECTED,

}GSM_STATE;


static GSM_STATE gsm_sm = GSM_MODULE_START;
static m66_ctrl m66_ctrl_struct = {0};
static bool config_state = false;
static uint8_t data_byte = 0;

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

	taskENTER_CRITICAL();
	HAL_StatusTypeDef status = HAL_ERROR;
	status = HAL_UART_Receive_DMA(&huart2, &data_byte, 1);
	taskEXIT_CRITICAL();

	while(1)
	{

		if(xQueueReceive(config_queue, (void*)&config_state, pdMS_TO_TICKS(100)) == pdTRUE)
		{
			gsm_sm = GSM_MODULE_START;
		}

		switch(gsm_sm)
		{
			case GSM_MODULE_START:
			{
				if(M66_at() != CMD_OK)
				{
					M66_hw_reset();
				}
				/*Go to the next state based on the device mode*/
				if(config_state)
				{
					gsm_sm = BT_CONFIGURE;
				}
				else
				{
					gsm_sm = GSM_CHECK_CREDENTIALS;
				}
				break;
			}
			case BT_CONFIGURE:
			{
				/*Enable bluetooth*/
				M66_set_bt_state(1);
				/*Set bluetooth local name*/
				M66_set_bt_name("ALARM");
				/*Set the visibility of the bluetooth device*/
				M66_set_bt_visibility(1);

				gsm_sm = BT_CONNECT;

				break;
			}
			case BT_CONNECT:
			{

				gsm_sm = BT_CONNECTED;
				break;
			}
			case BT_CONNECTED:
			{
				msg_data rsp_msg = {0};
				if(xQueueReceive(rsp_msg_queue, (void*)&rsp_msg, pdMS_TO_TICKS(100)) == pdTRUE)
				{
					/*If data arrives send it through BT*/
					M66_send_bt_data(rsp_msg.text);
				}

				if(!config_state)
				{
					M66_set_bt_state(0);
					gsm_sm = GSM_MODULE_START;
				}

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
					//M66_enter_pin(config.pincode);
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

				uint8_t netstat = 0;
				M66_query_network_status(&netstat);

				if((netstat == 1) || (netstat == 5))
				{
					gsm_sm = GSM_CONNECTED;
				}

				break;
			}
			case GSM_CONNECTED:
			{

				msg_data sms_msg = {0};
				if(xQueueReceive(sms_queue, (void*)&sms_msg, pdMS_TO_TICKS(100)) == pdTRUE)
				{
					M66_send_sms(config.tel_num, sms_msg.text);
				}

				uint8_t netstat = 0;
				M66_query_network_status(&netstat);

				if((netstat != 1) || (netstat != 5))
				{
					gsm_sm = GSM_MODULE_START;
				}

				break;
			}
			default:
			{
				gsm_sm = GSM_MODULE_START;
				break;
			}
		}


		if(!circbuffer_is_emtpy())
		{
			M66_check_URC();
		}

		/*Collect data from the system and control the state*/
		vTaskDelay(pdMS_TO_TICKS(500));
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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	UBaseType_t uxSavedInterruptStatus;
	uxSavedInterruptStatus = taskENTER_CRITICAL_FROM_ISR();
	circbuffer_insert(&data_byte, 1);
	taskEXIT_CRITICAL_FROM_ISR(uxSavedInterruptStatus);
}

