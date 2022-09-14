/*
 * lcd_task.c
 *
 *  Created on: 4 Aug 2022
 *      Author: papai
 */


#include "lcd_task.h"
#include "lcd.h"
#include "i2c.h"
#include "interface.h"

//TaskHandle_t lcd_task_h;
LCD_dev 	lcd_i2c 	= {0};

void lcd_task(void * params);

bool i2c_write(uint8_t dev_addr, uint8_t * data, uint8_t len);
bool i2c_read(uint8_t dev_addr, uint8_t * data, uint8_t len);
void i2c_delay(uint32_t ms);


void lcd_task_create()
{
	BaseType_t result = pdPASS;
	result = xTaskCreate(lcd_task,
				"lcd_t",
				100,
				NULL,
				3,
				NULL);

	configASSERT(result == pdPASS);
}

void lcd_task(void * params)
{
	lcd_i2c.i2c_write 	= i2c_write;
	lcd_i2c.i2c_read 	= i2c_read;
	lcd_i2c.delay 		= i2c_delay;

	LCD_I2C_init(&lcd_i2c);
	LCD_init();


	while(1)
	{
		/*Wait until data is received then print it on the LCD screen*/
		lcd_data data = {0};
		xQueueReceive(lcd_queue, (void*)&data, pdMS_TO_TICKS(portMAX_DELAY));
		taskENTER_CRITICAL();
		if(data.clr)
		{
			LCD_clear();
		}
		LCD_write(data.text, strlen(data.text));
		if(data.crlf)
		{
			LCD_next_line();
		}

		LCD_light_switch(data.led);

		taskEXIT_CRITICAL();
	}
}


bool i2c_write(uint8_t dev_addr, uint8_t * data, uint8_t len)
{
	HAL_StatusTypeDef status = HAL_ERROR;
	status = HAL_I2C_Master_Transmit(&hi2c1, (dev_addr << 1), data, len, 200);
	return (status == HAL_OK) ? true : false;
}

bool i2c_read(uint8_t dev_addr, uint8_t * data, uint8_t len)
{
	HAL_StatusTypeDef status = HAL_ERROR;
	status = HAL_I2C_Master_Transmit(&hi2c1, (dev_addr << 1), data, len, 200);
	status = HAL_I2C_Master_Receive(&hi2c1, ((dev_addr << 1) | 0x01), data, len, 200);
	return (status == HAL_OK) ? true : false;
}

void i2c_delay(uint32_t ms)
{
	vTaskDelay(ms);
	//HAL_Delay(ms);
}


