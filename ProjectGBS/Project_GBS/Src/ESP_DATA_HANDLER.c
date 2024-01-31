///**
//  ******************************************************************************
//
//  File:	  ESP_DATA_HANDLER.c
//  Author: Nguyen Khac Duong
//  Modify: Tran Xuan Dung
//  Created on: 8-2023
//
//  ******************************************************************************
//*/
//
///******************************************************************************/
///*                              INCLUDE FILES                                 */
///******************************************************************************/
//
//#include "ESP_DATA_HANDLER.h"
//#include "UartRingbuffer.h"
//#include "stdio.h"
//#include "string.h"
//#include "i2c_lcd.h"
//
//
////char *form = "POST /postdata HTTP/1.1\r\nHost: 192.168.2.13:3000\r\nContent-Type: application/json\r\nContent-Length: 334\r\n\r\n";
//
////char *json = "{\"iddevice\": \"7\",\"date\" :{\"ngaythangnam\" : \"2011/9/24\",\"giophutgiay\" : \"10:11:59\"},\"coordinatesDevice\" : {\"latitude\" : \"21.014927925937805\",\"longtitude\" : \"105.84262852543921\"},\"coordinatesGateway\" : {\"latitude\" : \"21.01492792593785\",\"longtitude\" : \"105.8426285254321\"},\"distance\" :123,\"diachi\":\"diachi3\",\"bando\" : \"2144\",\"state\" : 0}";
//
//
///******************************************************************************/
///*                     			 PROTOTYPE                        		      */
///******************************************************************************/
//
///**
// * @func   Send IP
// * @brief  SendCIPSEND
// * @param  *s
// * @retval None
// */
//void SendCIPSEND(char* s)
//{
//	char tmp[30];
//    sprintf(tmp, "AT+CIPSEND=%d\r\n", strlen(s));
//    Uart_flush(USART3);
//
//    Uart_sendstring(tmp, USART3); delay_ms(1500);
//
//    delay_ms(3000);
//}
//
//
///**
// * @func   Send one command
// * @brief  Send1
// * @param  *s
// * @retval None
// */
// void Send1(char* s)
// {
//    Uart_flush(USART3);
//    Uart_sendstring(s, USART3); delay_ms(1500);
//    delay_ms(1500);
//}
//
//
///**
//* @func   Send commands until the respond command send
//* @brief  Send
//* @param  *s
//* @retval None
//*/
//void Send(char *s)
//{
//	Uart_flush(USART3);
//	while(!(Wait_for("OK\r\n", USART3) )){ // nếu không hiện ok thì cứ gửi lệnh ra đến khi ok thì thôi
//		Uart_sendstring(s, USART3);delay_ms(1500);
//	}
//	delay_ms(1000);
//}
//
//
///**
//* @func   Initialization all parameter of ESP-01
//* @brief  ESP_Init
//* @param  *s
//* @retval None
//*/
//void ESP_Init (char *SSID, char *PASSWD, char *ipServer,int port, char *json)
//{
//
//	char data[500];
//	char form[200];
//	delay_ms(1500);
//
////	Uart_flush(USART3);
////	Uart_sendstring("\rAT+RST\r\n", USART3);
////	delay_ms(3000);
//	resetlai:
//		Send1("\rAT+RST\r\n");
//
//		Send1("\rAT+CWMODE=1\r\n");// AT+CWMODE=1<CR><LF>
////
////		sprintf(data,"\r\nAT+CIPSTA=\"%s\"\r\n",ipESP);
////		Send(data);
//
//		Send1("AT+CIFSR");
//
//		sprintf (data,"\rAT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWD);
//		Send1(data);
//
//
//	sprintf(data,"\rAT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ipServer,port) ;
//
//	Send1(data);
//
//	while(!(Wait_for("OK\r\n", USART3) )){ // nếu không hiện ok thì cứ gửi lệnh ra đến khi ok thì thôi
//		delay_ms(1000);
//		goto resetlai ;delay_ms(1500);
//	}
//	delay_ms(1000);
//
//
//	sprintf(form,"POST /postdata HTTP/1.1\r\nHost: %s:%d\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n",ipServer, port,strlen(json));
//
//	sprintf(data,"%s%s",form,json);
//
//	SendCIPSEND(data);
//
//	Send1(data);
//
//	delay_ms(2000);
//}
//
//
///**
//* @func   Start transform the data
//* @brief  ESP_Start
//* @param  None
//* @retval None
//*/
//void ESP_Start()
//{
//
//
//}
//



//#include "ESP_DATA_HANDLER.h"
//#include "UartRingbuffer.h"
//#include "stdio.h"
//#include "string.h"
//#include "i2c_lcd.h"
//
////char *form = "POST /postdata HTTP/1.1\r\nHost: 192.168.2.13:3000\r\nContent-Type: application/json\r\nContent-Length: 334\r\n\r\n";
//
////char *json = "{\"iddevice\": \"7\",\"date\" :{\"ngaythangnam\" : \"2011/9/24\",\"giophutgiay\" : \"10:11:59\"},\"coordinatesDevice\" : {\"latitude\" : \"21.014927925937805\",\"longtitude\" : \"105.84262852543921\"},\"coordinatesGateway\" : {\"latitude\" : \"21.01492792593785\",\"longtitude\" : \"105.8426285254321\"},\"distance\" :123,\"diachi\":\"diachi3\",\"bando\" : \"2144\",\"state\" : 0}";
//
//void SendCIPSEND(char* s)
//{
//	char tmp[30];
//    sprintf(tmp, "AT+CIPSEND=%d\r\n", strlen(s));
//    Uart_flush(USART3);
//
//    Uart_sendstring(tmp, USART3); delay_ms(1500);
//
//    //delay_ms(3000);
//}
//
// void Send1(char* s)
// {
//    Uart_flush(USART3);
//    Uart_sendstring(s, USART3); delay_ms(1000);
//    //delay_ms(3000);
//}
//
////void Send(char *s)
////{
////	Uart_flush(USART3);
////	while(!(Wait_for("OK\r\n", USART3) )){ // náº¿u khÃ´ng hiá»‡n ok thÃ¬ cá»© gá»­i lá»‡nh ra Ä‘áº¿n khi ok thÃ¬ thÃ´i
////		Uart_sendstring(s, USART3);delay_ms(1500);
////	}
////	delay_ms(1500);
////}
//
//
//
//void ESP_Init (char *SSID, char *PASSWD, char *ipServer,int port, char *json)
//{
//
//	char data[500];
//	char form[200];
//	delay_ms(1000);
//
////	Uart_flush(USART3);
////	Uart_sendstring("\rAT+RST\r\n", USART3);
////	delay_ms(3000);
//	resetlai:
//		Send1("\rAT+RST\r\n");
//
//		Send1("\rAT+CWMODE=1\r\n");// AT+CWMODE=1<CR><LF>
////
////		sprintf(data,"\r\nAT+CIPSTA=\"%s\"\r\n",ipESP);
////		Send(data);
//
//		Send1("AT+CIFSR");
//
//		sprintf (data,"\rAT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWD);
//		Send1(data);
//
//
//	sprintf(data,"\rAT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ipServer,port) ;
//
//	Send1(data);
//
//	while(!(Wait_for("OK\r\n", USART3) )){ // náº¿u khÃ´ng hiá»‡n ok thÃ¬ cá»© gá»­i lá»‡nh ra Ä‘áº¿n khi ok thÃ¬ thÃ´i
//		delay_ms(1000);
//		goto resetlai ;delay_ms(1000);
//	}
//	delay_ms(1000);
//
//
//	sprintf(form,"POST /postdata HTTP/1.1\r\nHost: %s:%d\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n",ipServer, port,strlen(json));
//
//	sprintf(data,"%s%s",form,json);
//
//	SendCIPSEND(data);
//
//	Send1(data);
//
//	//delay_ms(10000);
//}
//
//
//
//void ESP_Start()
//{
//
//
//}


//#include "ESP_DATA_HANDLER.h"
//#include "UartRingbuffer.h"
//#include "stdio.h"
//#include "string.h"
//#include "i2c_lcd.h"
//
////char *form = "POST /postdata HTTP/1.1\r\nHost: 192.168.2.13:3000\r\nContent-Type: application/json\r\nContent-Length: 334\r\n\r\n";
//
////char *json = "{\"iddevice\": \"7\",\"date\" :{\"ngaythangnam\" : \"2011/9/24\",\"giophutgiay\" : \"10:11:59\"},\"coordinatesDevice\" : {\"latitude\" : \"21.014927925937805\",\"longtitude\" : \"105.84262852543921\"},\"coordinatesGateway\" : {\"latitude\" : \"21.01492792593785\",\"longtitude\" : \"105.8426285254321\"},\"distance\" :123,\"diachi\":\"diachi3\",\"bando\" : \"2144\",\"state\" : 0}";
//
//
//
// void Send1(char* s)
// {
//    Uart_flush(USART3);
//    Uart_sendstring(s, USART3);
//    delay_ms(1500);
//}
//
//void Send(char *s)
//{
//	Uart_flush(USART3);
//	Uart_sendstring(s, USART3);
//	while(!(Wait_for("OK\r\n", USART3) ));
//}
//
//void SendCIPSEND(char* s)
//{
//	char tmp[30];
//    sprintf(tmp, "AT+CIPSEND=%d\r\n", strlen(s));
//    Uart_flush(USART3);
//
//    Uart_sendstring(tmp, USART3); delay_ms(1500);
//}
//
//void ESP_Init (char *SSID, char *PASSWD, char *ipServer,int port, char *json)
//{
//	char data[500];
//	char form[200];
//	delay_ms(500);
//
//
//	resetlai:
//		Send1("\rAT+RST\r\n");
//
//		Send1("\rAT+CWMODE=0\r\n");
//
//
////		sprintf(data,"\r\nAT+CIPSTA=\"%s\"\r\n",ipESP);
////		Send(data);
//
//		//Send1("AT+CIFSR");
//
//		sprintf (data,"\rAT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWD);
//		Send(data);
//
//
//	sprintf(data,"\rAT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ipServer,port) ;
//
//	Send1(data);
//
//	while(!(Wait_for("OK\r\n", USART3) )){
//		//delay_ms(1000);
//		goto resetlai ;
//	}
//
//
//	sprintf(form,"POST /postdata HTTP/1.1\r\nHost: %s:%d\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n",ipServer, port,strlen(json));
//
//	sprintf(data,"%s%s",form,json);
//
//	SendCIPSEND(data);
//
//	Send1(data);
//
//	Send1("\rAT+CIPCLOSE\r\n");
//
//}
//
//
//void ESP_Start (char *SSID, char *PASSWD, char *ipServer,int port, char *json)
//{
//	char data[500];
//	char form[200];
//	delay_ms(500);
//
//	sprintf(form,"POST /postdata HTTP/1.1\r\nHost: %s:%d\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n",ipServer, port,strlen(json));
//
//	sprintf(data,"%s%s",form,json);
//
//	SendCIPSEND(data);
//
//	Send1(data);
//
//	Send1("\rAT+CIPCLOSE\r\n");
//
//}
//
//


#include "ESP_DATA_HANDLER.h"
#include "UartRingbuffer.h"
#include "stdio.h"
#include "string.h"
#include "i2c_lcd.h"

//char *form = "POST /postdata HTTP/1.1\r\nHost: 192.168.2.13:3000\r\nContent-Type: application/json\r\nContent-Length: 334\r\n\r\n";

//char *json = "{\"iddevice\": \"7\",\"date\" :{\"ngaythangnam\" : \"2011/9/24\",\"giophutgiay\" : \"10:11:59\"},\"coordinatesDevice\" : {\"latitude\" : \"21.014927925937805\",\"longtitude\" : \"105.84262852543921\"},\"coordinatesGateway\" : {\"latitude\" : \"21.01492792593785\",\"longtitude\" : \"105.8426285254321\"},\"distance\" :123,\"diachi\":\"diachi3\",\"bando\" : \"2144\",\"state\" : 0}";



 void Send1(char* s)
 {
    Uart_flush(USART3);
    Uart_sendstring(s, USART3);
    delay_ms(1500);
}

void Send(char *s)
{
	Uart_flush(USART3);
	Uart_sendstring(s, USART3);
	while(!(Wait_for("OK\r\n", USART3) ));

}

void SendCIPSEND(char* s)
{
	char tmp[30];
    sprintf(tmp, "AT+CIPSEND=%d\r\n", strlen(s));
    Uart_flush(USART3);

    Uart_sendstring(tmp, USART3); delay_ms(1500);

}

void ESP_Init (char *SSID, char *PASSWD, char *ipServer, int port, char *json, uint32_t flagESP)
{

	char data[500];
	char form[200];
	delay_ms(500);

	if(flagESP == 0 ) goto resetlai;
	else goto guilan2;
	resetlai:
		Send1("\rAT+RST\r\n");

		Send1("\rAT+CWMODE=0\r\n");


//		sprintf(data,"\r\nAT+CIPSTA=\"%s\"\r\n",ipESP);
//		Send(data);

		//Send1("AT+CIFSR");

		sprintf (data,"\rAT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWD);
		Send(data);

	guilan2:

	sprintf(data,"\rAT+CIPSTART=\"TCP\",\"%s\",%d\r\n", ipServer,port) ;

	Send1(data);

	while(!(Wait_for("OK\r\n", USART3) )){
		//delay_ms(1000);
		goto resetlai ;
	}


	sprintf(form,"POST /postdata HTTP/1.1\r\nHost: %s:%d\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n",ipServer, port,strlen(json));

	sprintf(data,"%s%s",form,json);

	SendCIPSEND(data);

	Send1(data);

	Send1("\rAT+CIPCLOSE\r\n");

}




