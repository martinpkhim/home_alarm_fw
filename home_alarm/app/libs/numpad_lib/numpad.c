/*
 * numpad.c
 *
 *  Created on: Aug 3, 2022
 *      Author: papai
 */


#include "numpad.h"

#define COLUMN_NUM	(3)
#define	ROW_NUM		(4)


Numpad_dev * numpad_local_dev = NULL;


typedef struct scan_pin
{
	void (*write_func)(bool state);
	bool (*read_func)();
	char character;
}scan_pin;

scan_pin	scan_array[COLUMN_NUM][ROW_NUM] 	= {0};

bool Numpad_init(Numpad_dev * dev)
{
	if(dev == NULL)
		return false;

	numpad_local_dev = dev;

	/*Initialize an array with the functions*/

	/*column 1*/
	scan_array[0][0].write_func = numpad_local_dev->col0_write;
	scan_array[0][1].write_func = numpad_local_dev->col0_write;
	scan_array[0][2].write_func = numpad_local_dev->col0_write;
	scan_array[0][3].write_func = numpad_local_dev->col0_write;

	scan_array[0][0].read_func = numpad_local_dev->row0_read;
	scan_array[0][1].read_func = numpad_local_dev->row1_read;
	scan_array[0][2].read_func = numpad_local_dev->row2_read;
	scan_array[0][3].read_func = numpad_local_dev->row3_read;

	scan_array[0][0].character = '1';
	scan_array[0][1].character = '4';
	scan_array[0][2].character = '7';
	scan_array[0][3].character = '*';


	/*column 2*/
	scan_array[1][0].write_func = numpad_local_dev->col1_write;
	scan_array[1][1].write_func = numpad_local_dev->col1_write;
	scan_array[1][2].write_func = numpad_local_dev->col1_write;
	scan_array[1][3].write_func = numpad_local_dev->col1_write;

	scan_array[1][0].read_func = numpad_local_dev->row0_read;
	scan_array[1][1].read_func = numpad_local_dev->row1_read;
	scan_array[1][2].read_func = numpad_local_dev->row2_read;
	scan_array[1][3].read_func = numpad_local_dev->row3_read;

	scan_array[1][0].character = '2';
	scan_array[1][1].character = '5';
	scan_array[1][2].character = '8';
	scan_array[1][3].character = '0';

	/*column 3*/
	scan_array[2][0].write_func = numpad_local_dev->col2_write;
	scan_array[2][1].write_func = numpad_local_dev->col2_write;
	scan_array[2][2].write_func = numpad_local_dev->col2_write;
	scan_array[2][3].write_func = numpad_local_dev->col2_write;

	scan_array[2][0].read_func = numpad_local_dev->row0_read;
	scan_array[2][1].read_func = numpad_local_dev->row1_read;
	scan_array[2][2].read_func = numpad_local_dev->row2_read;
	scan_array[2][3].read_func = numpad_local_dev->row3_read;

	scan_array[2][0].character = '3';
	scan_array[2][1].character = '6';
	scan_array[2][2].character = '9';
	scan_array[2][3].character = '#';

	return true;
}


char Numpad_scan()
{
	for(uint8_t i = 0;i < COLUMN_NUM;i++)
	{
		for(uint8_t j = 0;j < ROW_NUM;j++)
		{
			scan_array[i][j].write_func(false);
			numpad_local_dev->delay(10);
			if(!scan_array[i][j].read_func())
			{
				numpad_local_dev->buzzer(true);
				numpad_local_dev->delay(100);
				numpad_local_dev->buzzer(false);
				scan_array[i][0].write_func(true);
				return scan_array[i][j].character;
			}
		}

		scan_array[i][0].write_func(true);
	}

	return 'X';
}
