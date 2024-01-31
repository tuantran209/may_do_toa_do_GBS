/**
  ******************************************************************************

  File:	  ESP_DATA_HANDLER.h
  Author: Nguyen Khac Duong
  Modify: Tran Xuan Dung
  Created on: 8-2023

  ******************************************************************************
*/


/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#ifndef INC_ESP_DATA_HANDLER_H_
#define INC_ESP_DATA_HANDLER_H_
#include "stdint.h"

/******************************************************************************/
/*                     			 PROTOTYPE                        		      */
/******************************************************************************/

/**
 * @func   Send IP
 * @brief  SendCIPSEND
 * @param  *s
 * @retval None
 */
void SendCIPSEND(char* s);


/**
 * @func   Send one command
 * @brief  Send1
 * @param  *s
 * @retval None
 */
 void Send1(char* s);


 /**
 * @func   Send commands until the respond command send
 * @brief  Send
 * @param  *s
 * @retval None
 */
 void Send(char *s);


 /**
 * @func   Initialization all parameter of ESP-01
 * @brief  ESP_Init
 * @param  *s
 * @retval None
 */
 void ESP_Init (char *SSID, char *PASSWD, char *ipServer, int port, char *json, uint32_t flagESP);


/**
* @func   Start transform the data
* @brief  ESP_Start
* @param  None
* @retval None
*/
void ESP_Start (char *SSID, char *PASSWD, char *ipServer,int port, char *json);

#endif

/* INC_ESP_DATA_HANDLER_H_ */
/* END FILE */
