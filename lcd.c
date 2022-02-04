/*
 * lcd.c
 *
 *  Created on: 3 Şub 2022
 *      Author: atay
 */

#include "lcd.h"
I2C_HandleTypeDef hi2c1;


void lcd_init(char data)
{
	char u, m;
	u = data&(0xF0);
	m = (data<<4)&(0xF0);
	uint8_t giden_data[4];
	giden_data[0] = u | 0x0C; // e=1 rs=0
	giden_data[1] = u | 0x08; // e=0 rs=0
	giden_data[2] = m | 0x0C; // e=1 rs=0
	giden_data[3] = m | 0x08; // e=0 rs=0
	while(HAL_I2C_Master_Transmit(&hi2c1, 0x27<<1, (uint8_t *) giden_data, 4, 1000) != HAL_OK );
}

void write(char data)
{
	char u, m;
	u = data&(0xF0);
	m = (data<<4)&(0xF0);
	uint8_t giden_data[4];
	giden_data[0] = u | 0x0D; // e=1 rs=1
	giden_data[1] = u | 0x09; // e=0 rs=1
	giden_data[2] = m | 0x0D; // e=1 rs=1
	giden_data[3] = m | 0x09; // e=0 rs=1
	while(HAL_I2C_Master_Transmit(&hi2c1, 0x27<<1, (uint8_t *) giden_data, 4, 1000) != HAL_OK );
}

void set_cursor(uint8_t a, uint8_t b)
{
	uint8_t giden_data[4];
	char u, m;
	char data;
	data = 0b10000000  + b;
	if(a == 1)
		data = 0b10000000 + 0b01000000 + b;


	u = data&(0xF0);
	m = (data<<4)&(0xF0);

	giden_data[0] = u | 0x0C; // e=1 rs=0 rw = 0
	giden_data[1] = u | 0x08; // e=0 rs=0 rw = 0
	giden_data[2] = m | 0x0C; // e=1 rs=0 rw = 0
	giden_data[3] = m | 0x08; // e=0 rs=0 rw = 0


	while(HAL_I2C_Master_Transmit(&hi2c1, 0x27<<1, (uint8_t *) giden_data, 4, 1000) != HAL_OK );


//	RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
//	0   0   1  AC6 AC5 AC4 AC3 AC2 AC1 AC0

//	1   2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
//	00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
//	40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F


}

void clear()
{
	lcd_init(0x80);
	for(int i = 0; i<70; i++)
	string_gonder(" ");
}


void lcd_init_ilk(void)
{
	HAL_Delay(50);
	lcd_init(0x30);
	HAL_Delay(5);
	lcd_init(0x30);
	HAL_Delay(1);
	lcd_init(0x30);
	HAL_Delay(10);
	lcd_init(0x20);
	HAL_Delay(10);

    lcd_init(0x28); // 4 bitle çalış
    HAL_Delay(1);
    lcd_init(0x08); // display on-off
    HAL_Delay(1);
    lcd_init(0x01); // display clear
    HAL_Delay(1);
    lcd_init (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
    HAL_Delay(1);
    lcd_init (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)

}


void string_gonder( char * data)
{

	while(* data) write( * data++);

}

