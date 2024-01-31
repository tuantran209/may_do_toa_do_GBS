/*
 * keypad4x4.c
 *
 *  Created on: Jul 17, 2023
 *      Author: admin
 */


#include "keypad4x4.h"
#include "stdint.h"
#include "stm32f10x.h"
#include "i2c_lcd.h"
#include "string.h"

uint8_t key ;
char input[20] ;
char password[20]  = "123654";
int LenPassWord ;
uint8_t IndexInput = 0;

//uint8_t KEY4x4[4][4] = {
//  {'1','2','3','A'},
//  {'4','5','6','B'},
//  {'7','8','9','C'},
//  {'*','0','#','D'}
//};

uint8_t KEY4x4[4][4] = {
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
};

uint8_t KEY4x4_Push(void){
	if((GPIO_ReadInputDataBit(GPIO_COLUMN,col1)==0)||(GPIO_ReadInputDataBit(GPIO_COLUMN,col2)==0)||(GPIO_ReadInputDataBit(GPIO_COLUMN,col3)==0)||(GPIO_ReadInputDataBit(GPIO_COLUMN,col4)==0))
	{
		return 1;
	}
	else return 0;
}

void ConfigKeypad(void)
{
	GPIO_InitTypeDef gp;
	RCC_APB2PeriphClockCmd(ROW_Clock,ENABLE);
	RCC_APB2PeriphClockCmd(COLUMN_Clock,ENABLE);

	// output
	gp.GPIO_Mode = GPIO_Mode_Out_PP;
	gp.GPIO_Pin = row1|row2|row3|row4;
	gp.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_ROW,&gp);

	// input
	gp.GPIO_Pin = col1|col2|col3|col4;
	gp.GPIO_Mode = GPIO_Mode_IPU;
	gp.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_COLUMN,&gp);

//	GPIO_Init(GPIOB,&gp);
}

void KEY4x4_CheckCol(uint8_t col)
{
	GPIO_SetBits(GPIO_ROW,row1);
	GPIO_SetBits(GPIO_ROW,row2);
	GPIO_SetBits(GPIO_ROW,row3);
	GPIO_SetBits(GPIO_ROW,row4);
	if(col==0){
		GPIO_ResetBits(GPIO_ROW,row1);
	}
	else if(col==1){
		GPIO_ResetBits(GPIO_ROW,row2);
	}
	else if(col==2){
		GPIO_ResetBits(GPIO_ROW,row3);
	}
	else if(col == 3){
		GPIO_ResetBits(GPIO_ROW,row4);
	}
}

uint8_t KEY4x4_GetKey(void)
{
	uint8_t i;
	GPIO_ResetBits(GPIO_ROW,row1);
	GPIO_ResetBits(GPIO_ROW,row2);
	GPIO_ResetBits(GPIO_ROW,row3);
	GPIO_ResetBits(GPIO_ROW,row4);

	if(KEY4x4_Push()==1)
	{
		delay_ms(10);
		if(KEY4x4_Push()==1)
		{
			for(i = 0 ;i<4;i++)
			{
				KEY4x4_CheckCol(i);
				if(GPIO_ReadInputDataBit(GPIO_COLUMN,col1)==0)
				{
					return KEY4x4[0][i];
				}
				else if(GPIO_ReadInputDataBit(GPIO_COLUMN,col2)==0)
				{
					return KEY4x4[1][i];
				}
				else if(GPIO_ReadInputDataBit(GPIO_COLUMN,col3)==0)
				{
					return KEY4x4[2][i];
				}
				else if(GPIO_ReadInputDataBit(GPIO_COLUMN,col4)==0)
				{
					return KEY4x4[3][i];
				}
			}
		}
	}
	return 0;
}

//void ConfigLed()
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//}
