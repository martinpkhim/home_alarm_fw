/*
 * lcd.h
 *
 *  Created on: Aug 3, 2022
 *      Author: papai
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>


typedef struct LCD_dev
{
	bool (*i2c_write)(uint8_t addr, uint8_t * data, uint8_t len);
	bool (*i2c_read)(uint8_t addr, uint8_t * data, uint8_t len);
	void (*delay)(uint32_t ms);
}LCD_dev;

bool LCD_I2C_init(LCD_dev * fp_struct);
bool LCD_init();
bool LCD_write(char * text, uint8_t len);
bool LCD_clear();
bool LCD_next_line();
bool LCD_light_switch(bool state);

#endif /* LCD_H_ */
