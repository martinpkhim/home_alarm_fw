/*
 * interface.h
 *
 *  Created on: Aug 4, 2022
 *      Author: papai
 */

#ifndef INTERFACE_INTERFACE_H_
#define INTERFACE_INTERFACE_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define	LCD_BUFF_MAX_SIZE	(32)

typedef struct lcd_data
{
	char text[LCD_BUFF_MAX_SIZE];
}lcd_data;

typedef struct io_state_data
{
	float 		vbat;
	uint16_t	io_state;
}io_state_data;


extern QueueHandle_t	lcd_queue;
extern QueueHandle_t	io_queue;

void interface_init();

#endif /* INTERFACE_INTERFACE_H_ */
