/*
 * lcd.h
 *
 *  Created on: 3 Şub 2022
 *      Author: atay
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_
#include "stm32f4xx_hal.h"


void lcd_init(char data);

void write(char data);

void set_cursor( uint8_t x, uint8_t y );

void lcd_init_ilk(void);

void clear();

void string_gonder( char * data);

#endif /* INC_LCD_H_ */
