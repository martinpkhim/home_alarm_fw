/*
 * interface.c
 *
 *  Created on: Aug 4, 2022
 *      Author: papai
 */


#include "interface.h"


QueueHandle_t		lcd_queue;
QueueHandle_t		io_queue;
QueueHandle_t		key_queue;
SemaphoreHandle_t	numpad_mutex;

void interface_init()
{
	lcd_queue 		= xQueueCreate(3, sizeof(lcd_data));
	io_queue 		= xQueueCreate(3, sizeof(io_state_data));
	key_queue 		= xQueueCreate(3, sizeof(uint8_t));
	numpad_mutex 	= xSemaphoreCreateMutex();
	xSemaphoreGive(numpad_mutex);
}
