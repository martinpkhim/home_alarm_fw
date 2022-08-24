/*
 * lcd.c
 *
 *  Created on: Aug 3, 2022
 *      Author: papai
 */

#include "lcd.h"

#define	I2C_ADDR					(0x3F)

#define	LCD_CMD_OFF					(0x08)
#define	LCD_CMD_ON					(0x0E)
#define	LCD_CMD_CLR					(0x01)
#define	LCD_CMD_RETURN				(0x02)
#define	LCD_CMD_SET_ENTRY			(0x28)
#define	LCD_CMD_CURSOR_BLINK		(0x0F)
#define	LCD_CMD_R_SHIFT				(0x14)
#define	LCD_CMD_NEXT_LINE			(0xC0)

typedef union LCD_data
{
	struct data_bits
	{
		uint8_t RS 	: 1;
		uint8_t RW 	: 1;
		uint8_t E 	: 1;
		uint8_t LED : 1;
		uint8_t D0 	: 1;
		uint8_t D1 	: 1;
		uint8_t D2 	: 1;
		uint8_t D3 	: 1;
	}data_bits;
	uint8_t data_byte;
}LCD_data;

typedef enum LCD_data_mode
{
	LCD_CMD,
	LCD_DATA,
}LCD_data_mode;

LCD_dev * LCD_local_dev = NULL;


static bool LCD_send(uint8_t cmd, LCD_data_mode mode);

bool LCD_I2C_init(LCD_dev * fp_struct)
{
	if(fp_struct == NULL)
		return false;

	LCD_local_dev = fp_struct;
	return true;
}

bool LCD_init()
{
	bool res = true;

	res &= LCD_send(LCD_CMD_OFF, LCD_CMD);
	LCD_local_dev->delay(10);
	res &= LCD_send(0x0E, LCD_CMD);
	LCD_local_dev->delay(10);
	res &= LCD_send(LCD_CMD_ON, LCD_CMD);
	LCD_local_dev->delay(10);
	res &= LCD_send(LCD_CMD_RETURN, LCD_CMD);
	LCD_local_dev->delay(10);
	res &= LCD_send(LCD_CMD_CLR, LCD_CMD);
	LCD_local_dev->delay(10);
	res &= LCD_send(LCD_CMD_SET_ENTRY, LCD_CMD);
	LCD_local_dev->delay(10);
	res &= LCD_send(LCD_CMD_CURSOR_BLINK, LCD_CMD);

	return res;

}

bool LCD_write(char * text, uint8_t len)
{
	bool res = true;

	for(uint8_t i = 0;i < len;i++)
	{
		uint8_t data_byte = text[i];
		res = LCD_send(data_byte,LCD_DATA);
		LCD_local_dev->delay(10);

		if(i == 15)
		{
			res &= LCD_send(LCD_CMD_RETURN, LCD_CMD);
			LCD_local_dev->delay(10);
			res &= LCD_send(0xC0, LCD_CMD);
		}
	}

	return res;
}

bool LCD_clear()
{
	bool res = true;


	res &= LCD_send(LCD_CMD_CLR, LCD_CMD);
	LCD_local_dev->delay(10);
	res &= LCD_send(LCD_CMD_RETURN, LCD_CMD);
	LCD_local_dev->delay(10);

	return res;
}

bool LCD_next_line()
{
	bool res = true;
	res &= LCD_send(LCD_CMD_NEXT_LINE, LCD_CMD);
	return res;
}

static bool LCD_send(uint8_t cmd, LCD_data_mode mode)
{
	bool res = true;
	LCD_data send_cmd = {0};
	send_cmd.data_bits.LED 	= 1;


	if(mode == LCD_CMD)
	{
		send_cmd.data_bits.RS = 0;
	}
	else
	{
		send_cmd.data_bits.RS = 1;
	}


	/*Set the first nibble*/
	send_cmd.data_byte |= (cmd & 0xF0);
	res &= LCD_local_dev->i2c_write(I2C_ADDR, &send_cmd.data_byte, 1);

	LCD_local_dev->delay(20);

	/*Pulse the enable pin*/
	send_cmd.data_bits.E = 1;
	res &= LCD_local_dev->i2c_write(I2C_ADDR, &send_cmd.data_byte, 1);
	LCD_local_dev->delay(20);
	send_cmd.data_bits.E = 0;
	res &= LCD_local_dev->i2c_write(I2C_ADDR, &send_cmd.data_byte, 1);

	LCD_local_dev->delay(20);

	/*Send the second half of the data*/
	send_cmd.data_byte &= ~(send_cmd.data_byte & 0xF0);
	send_cmd.data_byte |= (cmd & 0x0F) << 4;
	res &= LCD_local_dev->i2c_write(I2C_ADDR, &send_cmd.data_byte, 1);

	LCD_local_dev->delay(20);

	/*Pulse the enable pin*/
	send_cmd.data_bits.E = 1;
	res &= LCD_local_dev->i2c_write(I2C_ADDR, &send_cmd.data_byte, 1);
	LCD_local_dev->delay(20);
	send_cmd.data_bits.E = 0;
	res &= LCD_local_dev->i2c_write(I2C_ADDR, &send_cmd.data_byte, 1);

	return res;
}


