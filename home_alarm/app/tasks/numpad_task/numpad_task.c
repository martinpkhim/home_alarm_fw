/*
 * numpad_task.c
 *
 *  Created on: 4 Aug 2022
 *      Author: papai
 */


#include "numpad_task.h"
#include "numpad.h"
#include "gpio.h"
#include "tim.h"
#include "interface.h"

//TaskHandle_t numpad_task_h;
Numpad_dev	 numpad_ctrl = {0};

void numpad_task(void * params);

void col0_write(bool status);
void col1_write(bool status);
void col2_write(bool status);

bool row0_read();
bool row1_read();
bool row2_read();
bool row3_read();

void buzzer_write(bool state);
void numpad_delay(uint32_t ms);

void numpad_task_create()
{
	BaseType_t result = pdPASS;
	result = xTaskCreate(numpad_task,
				"numpad_t",
				500,
				NULL,
				4,
				NULL);

	configASSERT(result == pdPASS);

}

void numpad_task(void * params)
{
	char key = 'X';

	numpad_ctrl.col0_write = col0_write;
	numpad_ctrl.col1_write = col1_write;
	numpad_ctrl.col2_write = col2_write;

	numpad_ctrl.row0_read = row0_read;
	numpad_ctrl.row1_read = row1_read;
	numpad_ctrl.row2_read = row2_read;
	numpad_ctrl.row3_read = row3_read;

	numpad_ctrl.delay 	= numpad_delay;
	numpad_ctrl.buzzer 	= buzzer_write;

	Numpad_init(&numpad_ctrl);

	while(1)
	{
		xSemaphoreTake(numpad_mutex, pdMS_TO_TICKS(portMAX_DELAY));

		/*Keep scanning the numpad for keypresses*/
		key = Numpad_scan();
		if(key != 'X')
		{
			lcd_data data 	= {0};
			data.text[0] 	= key;
			data.led		= true;
			/*Send the key to the LCD task*/
			xQueueSend(lcd_queue, (void*)&data, pdMS_TO_TICKS(100));
			/*Send the key to the manager task as well*/
			xQueueSend(key_queue, (void*)&key, pdMS_TO_TICKS(100));
		}
		xSemaphoreGive(numpad_mutex);
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

void col0_write(bool status)
{
	HAL_GPIO_WritePin(COL0_GPIO_Port, COL0_Pin, (GPIO_PinState)status);
}

void col1_write(bool status)
{
	HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, (GPIO_PinState)status);
}

void col2_write(bool status)
{
	HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, (GPIO_PinState)status);
}

bool row0_read()
{
	return (HAL_GPIO_ReadPin(ROW0_GPIO_Port, ROW0_Pin) == GPIO_PIN_SET) ? true : false;
}

bool row1_read()
{
	return (HAL_GPIO_ReadPin(ROW1_GPIO_Port, ROW1_Pin) == GPIO_PIN_SET) ? true : false;
}

bool row2_read()
{
	return (HAL_GPIO_ReadPin(ROW2_GPIO_Port, ROW2_Pin) == GPIO_PIN_SET) ? true : false;
}

bool row3_read()
{
	return (HAL_GPIO_ReadPin(ROW3_GPIO_Port, ROW3_Pin) == GPIO_PIN_SET) ? true : false;
}

void buzzer_write(bool state)
{
	TIM4->ARR = 137;
	TIM4->CCR2 = 68;
	(state == true) ? HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2) : HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
}

void numpad_delay(uint32_t ms)
{
	vTaskDelay(ms);
}
