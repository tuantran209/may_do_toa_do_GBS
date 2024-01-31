/*
 * keypad4x4.h
 *
 *  Created on: Jul 17, 2023
 *      Author: admin
 */

#include "stdint.h"
#ifndef __KEYPAD4X4_H
#define __KEYPAD4x4_H

#ifdef __cplusplus
 extern "C" {
#endif

#define ROW_Clock	RCC_APB2Periph_GPIOB
#define COLUMN_Clock  RCC_APB2Periph_GPIOA
#define GPIO_ROW GPIOB
//#define GPIO_ROW GPIOA

//#define row1   GPIO_Pin_4
//#define row2   GPIO_Pin_5
//#define row3   GPIO_Pin_6
//#define row4   GPIO_Pin_7

#define row1   GPIO_Pin_12
#define row2   GPIO_Pin_13
#define row3   GPIO_Pin_14
#define row4   GPIO_Pin_15

//#define GPIO_COLUMN  GPIOB
#define GPIO_COLUMN  GPIOA

//#define col1   GPIO_Pin_12
//#define col2   GPIO_Pin_13
//#define col3   GPIO_Pin_14
//#define col4   GPIO_Pin_15

#define col1   GPIO_Pin_4
#define col2   GPIO_Pin_5
#define col3   GPIO_Pin_6
#define col4   GPIO_Pin_7


void ConfigKeypad(void);
//void ConfigLed(void);
uint8_t KEY4x4_Push(void);
void KEY4x4_CheckCol(uint8_t col);
uint8_t KEY4x4_GetKey(void);


#ifdef __cplusplus

}
#endif


#endif
