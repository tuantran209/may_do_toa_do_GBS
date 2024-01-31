/*
 * i2c_lcd.h
 *
 *  Created on: Jul 16, 2023
 *      Author: admin
 */

#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#include "stm32f10x.h"
#include <stdint.h>

/*
 ******************************************************************************
 */
#define SDA		GPIO_Pin_11//GPIO_Pin_9
#define SCL		GPIO_Pin_10//GPIO_Pin_8

#define I2C_Port GPIOB
#define I2C_Clock RCC_APB2Periph_GPIOB

#define I2C_LCD_ADDR 0x4E

extern void Delay_Ms(uint32_t u32DelayInMs);

#define I2C_LCD_Delay_Ms(u16DelayMs) Delay_Ms(u16DelayMs)

/*
 ******************************************************************************
 */

#define LCD_EN 2
#define LCD_RW 1
#define LCD_RS 0
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_BL 3

/*
 ******************************************************************************
 */

#define PCF8574A_Address      	0x4E
//#define I2C_Chanel      		I2C2
#define I2C_Chanel      		I2C1

/*
 ******************************************************************************
 */

void delay_ms(uint32_t ms);
void lcd_Write_byte(char data);
void lcd_init (void);
void lcd_Data_Write(char data);
void lcd_Control_Write(char data);
void lcd_send_string (char *str);
void Delete_LCD(void);
void Newline_LCD(void);

#endif /* I2C_LCD_H_ */
