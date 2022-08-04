/*
 * interface.c
 *
 *  Created on: Aug 4, 2022
 *      Author: papai
 */


#include "interface.h"


QueueHandle_t	lcd_queue;
QueueHandle_t	io_queue;

void interface_init()
{
	lcd_queue = xQueueCreate(3, sizeof(lcd_data));
	io_queue = xQueueCreate(3, sizeof(io_state_data));
}
