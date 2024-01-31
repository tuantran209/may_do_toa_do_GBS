/**
  ******************************************************************************

  File:	  main.c
  Author: Nguyen Khac Duong
  Modify: Tran Xuan Dung
  Created on: 8-2023

  ******************************************************************************
*/

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include <stdint.h>
#include "stdio.h"
#include "string.h"
#include <string.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "misc.h"

#include "keypad4x4.h"
#include "i2c_lcd.h"
#include "uartRingBuffer.h"
#include "NMEA.h"
#include "ESP_DATA_HANDLER.h"


/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

#define USART1_Tx					GPIO_Pin_9
#define USART1_Rx					GPIO_Pin_10
#define USART1_GPIO_Clock			RCC_APB2Periph_GPIOA
#define USART1_GPIO_Port			GPIOA
#define USART1_Clock				RCC_APB2Periph_USART1


#define USART2_Tx					GPIO_Pin_2
#define USART2_Rx					GPIO_Pin_3
#define USART2_GPIO_Clock			RCC_APB2Periph_GPIOA
#define USART2_GPIO_Port			GPIOA
#define USART2_Clock				RCC_APB1Periph_USART2

#define USART3_Tx					GPIO_Pin_10
#define USART3_Rx					GPIO_Pin_11
#define USART3_GPIO_Clock			RCC_APB2Periph_GPIOB
#define USART3_GPIO_Port			GPIOB
#define USART3_Clock				RCC_APB1Periph_USART3


char GGA[100];
char RMC[100];


GPSSTRUCT gpsData;


int flagGGA = 0, flagRMC = 0;



char lcdBuffer [50];



int flagKeypad = 0;



int flagGPS = 0;


double latitudeGateway = 21.006692;
double longitudeGateway = 105.828713;


char *ipServer = "117.0.35.45";
//char *SSID = "Luftmensch";
//char *SSPASS = "12345678";
char *SSID = "GBS";
char *SSPASS = "0101915236";
//char *SSID = "VanLoc-NgoaiSan";
//char *SSPASS = "88888888";
int port = 8282;


int flagESP = 0;

uint32_t countESP = 0;

int VCCTimeout = 5000; // GGA or RMC will not be received if the VCC is not sufficient



/******************************************************************************/
/*                     			 PROTOTYPE                        		      */
/******************************************************************************/



void Delay1Ms(void);
void Delay_Ms(uint32_t u32DelayInMs);
void delay_us(uint32_t delay);
void timer_Init(void);


static void USART1_Init(void);
static void USART2_Init(void);
static void USART3_Init(void);



int _write(int file, char *ptr, int len)
{
	for(uint32_t i = 0; i < len; i++){
		USART_SendData(USART2, *(ptr + i));
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {}
	}
	return len;
}


void UART3_SendByte(char c)
{
	USART_SendData(USART3, c);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
}



void UART2_SendByte(char c)
{
	USART_SendData(USART2, c);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {}
}


void Uart2_sendstring (const char *s, USART_TypeDef  *usart)
{
	uint32_t len = strlen(s);
	for(uint32_t i = 0; i < len; i++){
		USART_SendData(USART2, *(s + i));
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {}
	}
}


void UART1_SendByte(char c)
{
	USART_SendData(USART1, c);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}
}


void CommonInit();
void testledc13();




int main(void)
{
	/******************************************************************************/
	/*                     Initialization  and setup peripheral                  */
	/******************************************************************************/
	CommonInit();// Khai bao
	testledc13();// Test led vdk PC13

	printf("\rInit  LCD 11111111!\n");
	lcd_init ();                                 // ham khoi dong LCD16x
	Delete_LCD();
	lcd_send_string ("Final project!!\0");
	Newline_LCD();
	lcd_send_string ("Init done!!!");

	/******************************************************************************/
	/*                     Setup the string enter from Keypad                     */
	/******************************************************************************/
	char namePosition[16] = {'\0'};				// Chuoi in ra LCD
	uint8_t posNamePos = 0;						// Vi tri ki tu trong chuoi
	char key = 0;								// Ki tu duoc nhap tu keypad


	while (1)
	{
//		gpsData.rmcstruct.date.Day = 10;    gpsData.rmcstruct.date.Mon =12 ;   gpsData.rmcstruct.date.Yr = 23;
//		gpsData.ggastruct.tim.hour = 7;     gpsData.ggastruct.tim.min =50;   gpsData.ggastruct.tim.sec = 39;
//		gpsData.ggastruct.lcation.latitude =21.014927925937805;      gpsData.ggastruct.lcation.longitude = 105.84262852543921;
//
//		char json[500];
//
//		sprintf(json,"{\"iddevice\": \"%s\",\"date\" :{\"ngaythangnam\" : \"%d/%d/%d\",\"giophutgiay\" : \"%d:%d:%d\"},\"coordinatesDevice\" : {\"latitude\" : \"%.18f\",\"longtitude\" : \"%.18f\"},\"coordinatesGateway\" : {\"latitude\" : \"%.18f\",\"longtitude\" : \"%.18f\"},\"distance\" :0,\"diachi\":\"\",\"bando\" : \"\",\"state\" : 0}"
//				,namePosition,gpsData.rmcstruct.date.Yr,gpsData.rmcstruct.date.Mon,gpsData.rmcstruct.date.Day
//				,gpsData.ggastruct.tim.hour ,gpsData.ggastruct.tim.min ,gpsData.ggastruct.tim.sec
//				,gpsData.ggastruct.lcation.latitude,gpsData.ggastruct.lcation.longitude
//				,gpsData.ggastruct.lcation.latitude,gpsData.ggastruct.lcation.longitude);
//
//
//
//		ESP_Init(SSID, SSPASS, ipServer, port,json);
//		delay_ms(10000); break;

		/******************************************************************************/
		/*                    	 Enter the ID Device fromKeypad                       */
		/******************************************************************************/

		key = KEY4x4_GetKey();
		delay_ms(150);
		if( key != 0)
		{
			/******************************************************************************/
			/*                    	 		Press * to begin                       		  */
			/******************************************************************************/
			if( key == '*' && flagKeypad == 0)//The first '*' keypad is pressed
			{
				flagKeypad = 1;
				posNamePos = 0;	//Clear lcd
				flagGPS = 0;

				Delete_LCD();
				lcd_send_string("Wait for keypad!");
				printf("Wait for keypad...");
			}

			/******************************************************************************/
			/*                    	 		Press * to begin                       		  */
			/******************************************************************************/
			else if( key != '*' && flagKeypad == 0)//The first '*' keypad is pressed
			{
				flagKeypad = 0;
				posNamePos = 0;	//Clear lcd
				flagGPS = 0;
				posNamePos = 0;

				Delete_LCD();
				lcd_send_string("Press * to begin!");
				printf("Press * to begin...");
			}

			else
			{
				if( key == '*')
				{
					if( posNamePos >= sizeof(namePosition))
					{
						printf("Save and exit!\n");
						printf("excute %s", namePosition);
						namePosition[posNamePos] = '\0';
						flagGPS = 1;
						flagKeypad = 0;
					}
					else
					{
						printf("Error and clear!\n");
					}
				}
				else if( key == '#')
				{
					printf("Delele key!\n");
					if( posNamePos != 0 ) posNamePos --;
				}
				else
				{
					namePosition[posNamePos] = key;
					if( posNamePos < sizeof(namePosition) ) posNamePos ++;
				}
				namePosition[posNamePos] = '\0';	//Set last string
				Delete_LCD();
				lcd_send_string(namePosition);
				printf("%s\n",namePosition);
			}
		}

		/******************************************************************************/
		/*                    			Handle the GPS module                         */
		/******************************************************************************/

		if( flagGPS == 1 )
		{
			/******************************************************************************/
			/*                    			Wait for GGA and RMC                          */
			/******************************************************************************/
			if (Wait_for("GGA\0", USART1) == 1)
			{
				printf("GGA found\n");
				VCCTimeout = 5000;  // Reset the VCC Timeout indicating the GGA is being received

				Copy_upto("*", GGA, USART1);
				if (decodeGGA(GGA, &gpsData.ggastruct) == 0) flagGGA = 2;  // 2 indicates the data is valid
				else flagGGA = 1;  // 1 indicates the data is invalid
			}

			if (Wait_for("RMC\0", USART1) == 1)
			{
				printf("RMC found\n");
				VCCTimeout = 5000;  // Reset the VCC Timeout indicating the RMC is being received

				Copy_upto("*", RMC, USART1);
				if (decodeRMC(RMC, &gpsData.rmcstruct) == 0) flagRMC = 2;  // 2 indicates the data is valid
				else flagRMC = 1;  // 1 indicates the data is invalid
			}

			/******************************************************************************/
			/*                    	    GGA and RMC ready to decode                       */
			/******************************************************************************/

			if ((flagGGA == 2) | (flagRMC == 2))
			{
				Delete_LCD();
				sprintf (lcdBuffer, "%02d:%02d:%02d, %02d%02d%02d", gpsData.ggastruct.tim.hour, \
					  gpsData.ggastruct.tim.min, gpsData.ggastruct.tim.sec, gpsData.rmcstruct.date.Day, \
					  gpsData.rmcstruct.date.Mon, gpsData.rmcstruct.date.Yr);
				lcd_send_string(lcdBuffer);
				memset(lcdBuffer, '\0', 50);
				Newline_LCD();
				sprintf (lcdBuffer, "%.2f%c, %.2f%c  ", gpsData.ggastruct.lcation.latitude, gpsData.ggastruct.lcation.NS,\
					  gpsData.ggastruct.lcation.longitude, gpsData.ggastruct.lcation.EW);
				lcd_send_string(lcdBuffer);


				char json[500];
//				sprintf(json,"{\"iddevice\": \"%s\",\"date\" :{\"ngaythangnam\" : \"%d/%d/%d\",\"giophutgiay\" : \"%d:%d:%d\"},\"coordinatesDevice\" : {\"latitude\" : \"%.18f\",\"longtitude\" : \"%.18f\"},\"coordinatesGateway\" : {\"latitude\" : \"%.18f\",\"longtitude\" : \"%.18f\"},\"distance\" :123,\"diachi\":\"\",\"bando\" : \"\",\"state\" : 0}"
//				,"iddevice2",gpsData.rmcstruct.date.Yr,gpsData.rmcstruct.date.Mon,gpsData.rmcstruct.date.Day
//				,gpsData.ggastruct.tim.hour ,gpsData.ggastruct.tim.min ,gpsData.ggastruct.tim.sec
//				,gpsData.ggastruct.lcation.latitude,gpsData.ggastruct.lcation.longitude
//				,gpsData.ggastruct.lcation.latitude,gpsData.ggastruct.lcation.longitude);

				sprintf(json,"{\"iddevice\": \"%s\",\"date\" :{\"ngaythangnam\" : \"%d/%d/%d\",\"giophutgiay\" : \"%d:%d:%d\"},\"coordinatesDevice\" : {\"latitude\" : \"%.18f\",\"longtitude\" : \"%.18f\"},\"coordinatesGateway\" : {\"latitude\" : \"%.18f\",\"longtitude\" : \"%.18f\"},\"distance\" :123,\"diachi\":\"\",\"bando\" : \"\",\"state\" : 1}"
								,namePosition,gpsData.rmcstruct.date.Yr,gpsData.rmcstruct.date.Mon,gpsData.rmcstruct.date.Day
								,gpsData.ggastruct.tim.hour ,gpsData.ggastruct.tim.min ,gpsData.ggastruct.tim.sec
								,gpsData.ggastruct.lcation.latitude,gpsData.ggastruct.lcation.longitude
								,latitudeGateway ,longitudeGateway);

//				uint32_t countESP = 0;
				while (countESP <= 5)
				{
					ESP_Init(SSID, SSPASS, ipServer, port,json, flagESP);
					delay_ms(1000);
					countESP++;
					flagESP = 1;
				}
				break;
//				ESP_Init(SSID, SSPASS, ipServer, port,json, flagESP);
//				delay_ms(1000);
//				flagESP = 1;
			}

			/******************************************************************************/
			/*                    	    GGA and RMC not fix yet                           */
			/******************************************************************************/

			else if ((flagGGA == 1) | (flagRMC == 1))
			{
				// Instead of clearing the display, it's better if we print spaces.
				// This will avoid the "refreshing" part

//				printf("in ra %s", iddevice);
				Delete_LCD();
				lcd_send_string("   NO FIX YET   ");
				Newline_LCD();
				lcd_send_string("   Please wait  ");
				delay_ms(2000);
//				gpsData.rmcstruct.date.Day = 10;    gpsData.rmcstruct.date.Mon =12 ;   gpsData.rmcstruct.date.Yr = 23;
//				gpsData.ggastruct.tim.hour = 7;     gpsData.ggastruct.tim.min =50;   gpsData.ggastruct.tim.sec = 39;
//				gpsData.ggastruct.lcation.latitude =21.014927925937805;      gpsData.ggastruct.lcation.longitude = 105.84262852543921;
//
//				char json[500];
//
//				sprintf(json,"{\"iddevice\": \"%s\",\"date\" :{\"ngaythangnam\" : \"%d/%d/%d\",\"giophutgiay\" : \"%d:%d:%d\"},\"coordinatesDevice\" : {\"latitude\" : \"%.18f\",\"longtitude\" : \"%.18f\"},\"coordinatesGateway\" : {\"latitude\" : \"%.18f\",\"longtitude\" : \"%.18f\"},\"distance\" :0,\"diachi\":\"\",\"bando\" : \"\",\"state\" : 1}"
//						,namePosition,gpsData.rmcstruct.date.Yr,gpsData.rmcstruct.date.Mon,gpsData.rmcstruct.date.Day
//						,gpsData.ggastruct.tim.hour ,gpsData.ggastruct.tim.min ,gpsData.ggastruct.tim.sec
//						,gpsData.ggastruct.lcation.latitude,gpsData.ggastruct.lcation.longitude
//						,latitudeGateway ,longitudeGateway);
//
//
//
//				ESP_Init(SSID, SSPASS, ipServer, port, json, flagESP);
//				delay_ms(1000);
//				flagESP = 1;
			}

			/******************************************************************************/
			/*                    	    VCC for GPS module isn't supply                   */
			/******************************************************************************/

			if (VCCTimeout <= 0)
			{
				VCCTimeout = 5000;  // Reset the timeout

				//reset flags
				flagGGA =flagRMC =0;

				// You are here means the VCC is less, or maybe there is some connection issue
				// Check the VCC, also you can try connecting to the external 5V
				Delete_LCD();
				lcd_send_string("    VCC Issue   ");
				Newline_LCD();
				lcd_send_string("Check Connection");
				printf("    VCC Issue   \n");
			}
		}
	}
}


void CommonInit()
{
	/* Initialization USART1 */
	USART1_Init();

	/* Initialization USART2 */
	USART2_Init();

	/* Initialization USART3 */
	USART3_Init();

	/* Initialization RingBuffer for USART2 and USART3 */
	Ringbuf_init();

	/* Initialization Keypad */
	ConfigKeypad();

	/* Initialization  SystemCoreClock */
	SysTick_Config(SystemCoreClock/1000);
}


void testledc13()
{
	GPIO_InitTypeDef gpioInit;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_13;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &gpioInit);
}


void Delay1Ms(void)
{
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < 1000) {
	}
}


void delay_us(uint32_t delay)
{
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < delay) {
	}
}


void Delay_Ms(uint32_t u32DelayInMs)
{
	while (u32DelayInMs) {
		Delay1Ms();
		--u32DelayInMs;
	}
}


void timer_Init(void)
{
	TIM_TimeBaseInitTypeDef timerInit;

	/******************************************************************************/
	/* 							 Cap clock cho Timer2                             */
	/******************************************************************************/

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/******************************************************************************/
	/* 					       Cau hinh tham so Timer2                            */
	/******************************************************************************/

	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	timerInit.TIM_Period = 0xFFFF;
	timerInit.TIM_Prescaler = 72 - 1;

	TIM_TimeBaseInit(TIM2, &timerInit);

	/******************************************************************************/
	/* 					              Kich hoat Timer2                            */
	/******************************************************************************/

	TIM_Cmd(TIM2, ENABLE);
}


static void USART1_Init(void)
{
	GPIO_InitTypeDef		GPIO_InitStructure;
	USART_InitTypeDef		USART_InitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;

	/******************************************************************************/
	/* 							 Cap clock cho USART1                             */
	/******************************************************************************/

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/******************************************************************************/
	/* 					           Cau hinh chan Tx              	              */
	/******************************************************************************/

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	/******************************************************************************/
	/* 					           Cau hinh chan Rx              	              */
	/******************************************************************************/

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/******************************************************************************/
	/* 			     Initializes GPIO As Alternate function mode             	  */
	/******************************************************************************/

	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

	/******************************************************************************/
	/* 			    		 Initializes USART1 Clock	                          */
	/******************************************************************************/

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/******************************************************************************/
	/* 			    		 Initializes USART1 parameter	                      */
	/******************************************************************************/

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);

	/******************************************************************************/
	/* 			    		 		NVIC configuration	                          */
	/******************************************************************************/

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* xoa co ngat nhan cho lan dau su dung*/
	USART_ClearFlag(USART1, USART_IT_RXNE);

	/* Cau hinh cho phep ngat nhan*/
//		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	/******************************************************************************/
	/* 					              Kich hoat USART1                            */
	/******************************************************************************/

	USART_Cmd(USART1, ENABLE);
}



void USART1_IRQHandler (void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		Uart_isr(USART1);
	}
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}


static void USART2_Init(void)
{
	GPIO_InitTypeDef		GPIO_InitStructure;
	USART_InitTypeDef		USART_InitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;

	/******************************************************************************/
	/* 							 Cap clock cho USART1                             */
	/******************************************************************************/

	RCC_APB2PeriphClockCmd(USART2_GPIO_Clock, ENABLE);

	/******************************************************************************/
	/* 					           Cau hinh chan Tx              	              */
	/******************************************************************************/

	GPIO_InitStructure.GPIO_Pin = USART2_Tx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART2_GPIO_Port, &GPIO_InitStructure);

	/******************************************************************************/
	/* 					           Cau hinh chan Rx              	              */
	/******************************************************************************/

	GPIO_InitStructure.GPIO_Pin = USART2_Rx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART2_GPIO_Port, &GPIO_InitStructure);
	//Initializes GPIO As Alternate function mode
	GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);


	/******************************************************************************/
	/* 			    		 Initializes USART2 Clock	                          */
	/******************************************************************************/

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/******************************************************************************/
	/* 			    		 Initializes USART2 parameter	                      */
	/******************************************************************************/

	USART_InitStructure.USART_BaudRate = 56000;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2, &USART_InitStructure);

	/******************************************************************************/
	/* 			    		 		NVIC configuration	                          */
	/******************************************************************************/

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* xoa co ngat nhan cho lan dau su dung*/
	USART_ClearFlag(USART2, USART_IT_RXNE);

	/* Cau hinh cho phep ngat nhan*/
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	/******************************************************************************/
	/* 					              Kich hoat USART2                            */
	/******************************************************************************/

	USART_Cmd(USART2, ENABLE);
}



void USART2_IRQHandler (void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		uint8_t byReceiverData = USART_ReceiveData(USART2);
		UART2_SendByte(byReceiverData);
	}
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}



static void USART3_Init(void)
{
	GPIO_InitTypeDef		GPIO_InitStructure;
	USART_InitTypeDef		USART_InitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;

	/******************************************************************************/
	/* 							 Cap clock cho USART1                             */
	/******************************************************************************/

	RCC_APB2PeriphClockCmd(USART3_GPIO_Clock, ENABLE);

	/******************************************************************************/
	/* 					           Cau hinh chan Tx              	              */
	/******************************************************************************/

	GPIO_InitStructure.GPIO_Pin = USART3_Tx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART3_GPIO_Port, &GPIO_InitStructure);

	/******************************************************************************/
	/* 					           Cau hinh chan Rx              	              */
	/******************************************************************************/

	GPIO_InitStructure.GPIO_Pin = USART3_Rx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART3_GPIO_Port, &GPIO_InitStructure);

	 //Initializes GPIO As Alternate function mode
	GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);

	/******************************************************************************/
	/* 			    		 Initializes USART3 Clock	                          */
	/******************************************************************************/

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART3, &USART_InitStructure);

	/******************************************************************************/
	/* 			    		 		NVIC configuration	                          */
	/******************************************************************************/

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* xoa co ngat nhan cho lan dau su dung*/
	USART_ClearFlag(USART3, USART_IT_RXNE);

	/* Cau hinh cho phep ngat nhan*/
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	/******************************************************************************/
	/* 					              Kich hoat USART3                            */
	/******************************************************************************/

	USART_Cmd(USART3, ENABLE);
}



void USART3_IRQHandler (void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		Uart_isr(USART3);
	}
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}
