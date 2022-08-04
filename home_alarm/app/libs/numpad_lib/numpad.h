/*
 * numpad.h
 *
 *  Created on: Aug 3, 2022
 *      Author: papai
 */

#ifndef NUMPAD_H_
#define NUMPAD_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct Numpad_dev
{
	bool (*row0_read)();
	bool (*row1_read)();
	bool (*row2_read)();
	bool (*row3_read)();
	void (*col0_write)(bool state);
	void (*col1_write)(bool state);
	void (*col2_write)(bool state);
	void (*delay)(uint32_t ms);
	void (*buzzer)(bool state);
}Numpad_dev;


bool Numpad_init(Numpad_dev * dev);
char Numpad_scan();

#endif /* NUMPAD_H_ */
