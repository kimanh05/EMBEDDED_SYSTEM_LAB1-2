/*
 * LED_7seg.h
 *
 *  Created on: Oct 1, 2026
 *      Author: kiman
 */

#ifndef INC_LED_7SEG_H_
#define INC_LED_7SEG_H_

#include "main.h"

void LED7_init(void);
void LED7_Scan(void);

void LED7_SetDigit(int num, int position, uint8_t show_dot);
void LED7_SetColon(uint8_t status);

void LED_On(uint8_t index);
void LED_Off(uint8_t index);

#endif /* INC_LED_7SEG_H_ */
