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
QueueHandle_t		config_queue;
QueueHandle_t		msg_queue;
QueueHandle_t		rsp_msg_queue;
QueueHandle_t		sms_queue;
SemaphoreHandle_t	numpad_mutex;

void interface_init()
{
	lcd_queue 		= xQueueCreate(3, sizeof(lcd_data));
	io_queue 		= xQueueCreate(3, sizeof(io_state_data));
	key_queue 		= xQueueCreate(3, sizeof(uint8_t));
	config_queue 	= xQueueCreate(2, sizeof(bool));
	msg_queue 		= xQueueCreate(2, sizeof(msg_data));
	rsp_msg_queue 	= xQueueCreate(2, sizeof(msg_data));
	sms_queue 		= xQueueCreate(2, sizeof(msg_data));
	numpad_mutex 	= xSemaphoreCreateMutex();
	xSemaphoreGive(numpad_mutex);
}
