/**
  ******************************************************************************

  File:		UartRingbuffer.h
  Author: Nguyen Khac Duong
  Created on: 8-2023

  ******************************************************************************
*/


#ifndef UARTRINGBUFFER_H_
#define UARTRINGBUFFER_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include "stdint.h"
#include "stm32f10x_usart.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/**
 *@brief  Change the size of the buffer
*/
#define UART_BUFFER_SIZE 64

/**
 *@brief  Buffer Structure
*/
typedef struct
{
  unsigned char buffer[UART_BUFFER_SIZE];
  volatile unsigned int head;
  volatile unsigned int tail;
} ring_buffer;


/******************************************************************************/
/*                     			 PROTOTYPE                        		      */
/******************************************************************************/

/**
 * @func   Initializes Ring buffer
 * @brief  Ringbuf_init
 * @param  None
 * @retval None
 */
void Ringbuf_init(void);


/**
 * @func   Storing the received character into the location
 * @brief  store_char
 * @param  c, *buffer
 * @retval None
 */
void store_char(unsigned char c, ring_buffer *buffer);


/**
 * @func   Reads the data in the rx_buffer and increment the tail count in rx_buffer
 * @brief  Uart_read
 * @param  *usart
 */
int Uart_read(USART_TypeDef *usart);


/**
 * @func   Writes the data to the tx_buffer and increment the head count in tx_buffer
 * @brief  store_char
 * @param  c, *buffer
 * @retval None
 */
void Uart_write(int c, USART_TypeDef *usart);


/**
 * @func   Function to send the string to the uart
 * @brief  Uart_sendstring
 * @param  *s, *usart
 * @retval None
 */
void Uart_sendstring(const char *s, USART_TypeDef *usart);


/**
 * @func   Checks if the data is available to read in the rx_buffe
 * @brief  IsDataAvailable
 * @param  usart
 */
int IsDataAvailable(USART_TypeDef *usart);


/**
 * @func   Look for a particular string in the given buffer
 * @brief  Look_for
 * @param  *string, *buffertolookinto
 * @retval 1, if the string is found and -1 if not found
 */
int Look_for (char *str, char *buffertolookinto);


/**
 * @func   Copies the required data from a buffer
 * @brief  store_char
 * @param  startString: the string after which the data need to be copied
 * 		   endString: the string before which the data need to be copied
 * @retval None
 */
void GetDataFromBuffer (char *startString, char *endString, char *buffertocopyfrom, char *buffertocopyinto);


/**
 * @func   Resets the entire ring buffer, the new data will start from position 0
 * @brief  Uart_flush
 * @param  *usart
 * @retval None
 */
void Uart_flush (USART_TypeDef *usart);


/**
 * @func   Peek for the data in the Rx Bffer without incrementing the tail count
 * @brief  Uart_peek
 * @param  *usart
 * @retval The position of rx buffer
 */
int Uart_peek(USART_TypeDef *usart);


/**
 * @func   copies the data from the incoming buffer into our buffer
 	 	 * Must be used if you are sure that the data is being received
 	 	 * it will copy irrespective of, if the end string is there or not
 	 	 * if the end string gets copied, it returns 1 or else 0
 	 	 * Use it either after (IsDataAvailable) or after (Wait_for) functions
 * @brief  Copy_upto
 * @param  *usart
 * retval  1 on success and -1 otherwise
 */
int Copy_upto (char *string, char *buffertocopyinto, USART_TypeDef *usart);


/**
 * @func  Copies the entered number of characters (blocking mode) from the Rx buffer into the buffer, after some particular string is detected
 * @brief  Get_after
 * @param  *string, numberofchars, *buffertosave, *usart
 * retval  1 on success and -1 otherwise
 */
int Get_after (char *string, uint8_t numberofchars, char *buffertosave, USART_TypeDef *usart);


/* Wait until a paricular string is detected in the Rx Buffer
* Return 1 on success and -1 otherwise
* USAGE: while (!(Wait_for("some string")));
*/
int Wait_for (char *string, USART_TypeDef *usart);


/**
 * @func   Interrupt function: The function will be processed in the isr handler function to control the peripheral device
 * @brief  Uart_isr
 * @param  *usart
 */
void Uart_isr (USART_TypeDef *husart);


#endif
/* UARTRINGBUFFER_H_ */
/* END FILE */
