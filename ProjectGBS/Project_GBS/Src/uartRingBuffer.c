/**
  ******************************************************************************

  File:		UartRingbuffer.c
  Author: Nguyen Khac Duong
  Created on: 8-2023

  ******************************************************************************
*/

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include <string.h>
#include <stdio.h>
#include "stm32f10x_usart.h"
#include "UartRingbuffer.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/**
 *@brief  Define timeout
*/
#define TIMEOUT_DEF 500  // 500ms timeout for the functions
uint16_t timeout;


/**
 *@brief  Define the ring buffer for USART1 and USART3
 *@param  rx_buffer, tx_buffer: Use for USART1
 *		  rx_buffer3, tx_buffer3: Use for USART1
 *		  *_rx_buffer, *_tx_buffer: Use handler for USART1
 *		  *_rx_buffer3, *_tx_buffer3: Use handler for USART3
 * */
ring_buffer rx_buffer = { { 0 }, 0, 0};
ring_buffer tx_buffer = { { 0 }, 0, 0};

ring_buffer rx_buffer3 = { { 0 }, 0, 0};
ring_buffer tx_buffer3 = { { 0 }, 0, 0};

ring_buffer *_rx_buffer;
ring_buffer *_tx_buffer;

ring_buffer *_rx_buffer3;
ring_buffer *_tx_buffer3;

/******************************************************************************/
/*                     			 PROTOTYPE                        		      */
/******************************************************************************/


/**
 * @func   Initializes Ring buffer
 * @brief  Ringbuf_init
 * @param  None
 * @retval None
 */
void Ringbuf_init(void)
{
	_rx_buffer = &rx_buffer;
	_tx_buffer = &tx_buffer;

	_rx_buffer3 = &rx_buffer3;
	_tx_buffer3 = &tx_buffer3;

	/******************************************************************************/
	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	/******************************************************************************/

	USART_ITConfig(USART1, USART_IT_ERR, ENABLE);
	USART_ITConfig(USART3, USART_IT_ERR, ENABLE);

	/******************************************************************************/
	/* 				Enable the UART Data Register not empty Interrupt		      */
	/******************************************************************************/

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
}


/**
 * @func   Storing the received character into the location
 * @brief  store_char
 * @param  c, *buffer
 * @retval None
 */
void store_char(unsigned char c, ring_buffer *buffer)
{
	int i = (unsigned int)(buffer->head + 1) % UART_BUFFER_SIZE;

	/******************************************************************************/
	/*   if we should be storing the received character into the location         */
	/*   just before the tail (meaning that the head would advance to the         */
	/*   current location of the tail), we're about to overflow the buffer        */
	/*   and so we don't write the character or advance the head.		          */
	/******************************************************************************/

	if(i != buffer->tail) {
	buffer->buffer[buffer->head] = c;
	buffer->head = i;
  }
}


/**
 * @func   Look for a particular string in the given buffer
 * @brief  Look_for
 * @param  *string, *buffertolookinto
 * @retval 1, if the string is found and -1 if not found
 */
int Look_for (char *str, char *buffertolookinto)
{
	int stringlength = strlen (str);
	int bufferlength = strlen (buffertolookinto);
	int so_far = 0;
	int indx = 0;
repeat:
	while (str[so_far] != buffertolookinto[indx])
		{
			indx++;
			if (indx>stringlength) return 0;
		}
	if (str[so_far] == buffertolookinto[indx])
	{
		while (str[so_far] == buffertolookinto[indx])
		{
			so_far++;
			indx++;
		}
	}

	if (so_far == stringlength);
	else
	{
		so_far =0;
		if (indx >= bufferlength) return -1;
		goto repeat;
	}

	if (so_far == stringlength) return 1;
	else return -1;
}


/**
 * @func   Reads the data in the rx_buffer and increment the tail count in rx_buffer
 * @brief  Uart_read
 * @param  *usart
 */
int Uart_read(USART_TypeDef *usart)
{
	if (usart == USART1)
	{
		/******************************************************************************/
		/*     if the head isn't ahead of the tail, we don't have any characters      */
		/******************************************************************************/

		if(_rx_buffer->head == _rx_buffer->tail)
		{
			return -1;
		}
		else
		{
			unsigned char c = _rx_buffer->buffer[_rx_buffer->tail];
			_rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % UART_BUFFER_SIZE;
			return c;
		}
	}

	else if(usart == USART3)
	{
		/******************************************************************************/
		/*     if the head isn't ahead of the tail, we don't have any characters      */
		/******************************************************************************/

		if(_rx_buffer3->head == _rx_buffer3->tail)
		{
			return -1;
		}
		else
		{
			unsigned char c = _rx_buffer3->buffer[_rx_buffer3->tail];
			_rx_buffer3->tail = (unsigned int)(_rx_buffer3->tail + 1) % UART_BUFFER_SIZE;
			return c;
		}
	}

	else return -1;
}


/**
 * @func   Writes the data to the tx_buffer and increment the head count in tx_buffer
 * @brief  store_char
 * @param  c, *buffer
 * @retval None
 */
void Uart_write(int c, USART_TypeDef  *usart)
{
	if (c>=0)
	{
		if (usart == USART1)
		{
			int i = (_tx_buffer->head + 1) % UART_BUFFER_SIZE;
			while (i == _tx_buffer->tail);

			_tx_buffer->buffer[_tx_buffer->head] = (uint8_t)c;
			_tx_buffer->head = i;

			USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		}

		else if (usart == USART3)
		{
			int i = (_tx_buffer3->head + 1) % UART_BUFFER_SIZE;
			while (i == _tx_buffer3->tail);

			_tx_buffer3->buffer[_tx_buffer3->head] = (uint8_t)c;
			_tx_buffer3->head = i;

			USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
		}
	}
}


/**
 * @func   Checks if the data is available to read in the rx_buffe
 * @brief  IsDataAvailable
 * @param  usart
 */
int IsDataAvailable(USART_TypeDef  *usart)
{
	if (usart == USART1)  return (uint16_t)(UART_BUFFER_SIZE + _rx_buffer->head - _rx_buffer->tail) % UART_BUFFER_SIZE;
	else if (usart == USART3)  return (uint16_t)(UART_BUFFER_SIZE + _rx_buffer3->head - _rx_buffer3->tail) % UART_BUFFER_SIZE;
	return -1;
}


/**
 * @func   Function to send the string to the uart
 * @brief  Uart_sendstring
 * @param  *s, *usart
 * @retval None
 */
void Uart_sendstring (const char *s, USART_TypeDef  *usart)
{
	uint32_t len = strlen(s);
	for(uint32_t i = 0; i < len; i++)
	{
		USART_SendData(USART3, *(s + i));
		while(USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
	}
}


/**
 * @func   Copies the required data from a buffer
 * @brief  store_char
 * @param  startString: the string after which the data need to be copied
 * 		   endString: the string before which the data need to be copied
 * @retval None
 */
void GetDataFromBuffer (char *startString, char *endString, char *buffertocopyfrom, char *buffertocopyinto)
{
	int startStringLength = strlen (startString);
	int endStringLength   = strlen (endString);
	int so_far = 0;
	int indx = 0;
	int startposition = 0;
	int endposition = 0;

repeat1:
	while (startString[so_far] != buffertocopyfrom[indx]) indx++;
	if (startString[so_far] == buffertocopyfrom[indx])
	{
		while (startString[so_far] == buffertocopyfrom[indx])
		{
			so_far++;
			indx++;
		}
	}

	if (so_far == startStringLength) startposition = indx;
	else
	{
		so_far =0;
		goto repeat1;
	}

	so_far = 0;

repeat2:
	while (endString[so_far] != buffertocopyfrom[indx]) indx++;
	if (endString[so_far] == buffertocopyfrom[indx])
	{
		while (endString[so_far] == buffertocopyfrom[indx])
		{
			so_far++;
			indx++;
		}
	}

	if (so_far == endStringLength) endposition = indx-endStringLength;
	else
	{
		so_far =0;
		goto repeat2;
	}

	so_far = 0;
	indx=0;

	for (int i=startposition; i<endposition; i++)
	{
		buffertocopyinto[indx] = buffertocopyfrom[i];
		indx++;
	}
}


/**
 * @func   Resets the entire ring buffer, the new data will start from position 0
 * @brief  Uart_flush
 * @param  *usart
 * @retval None
 */
void Uart_flush (USART_TypeDef *usart)
{
	if (usart == USART1)
	{
		memset(_rx_buffer->buffer,'\0', UART_BUFFER_SIZE);
		_rx_buffer->head = 0;
		_rx_buffer->tail = 0;
	}
	if (usart == USART3)
	{
		memset(_rx_buffer3->buffer,'\0', UART_BUFFER_SIZE);
		_rx_buffer3->head = 0;
		_rx_buffer3->tail = 0;
	}

}


/**
 * @func   Peek for the data in the Rx Bffer without incrementing the tail count
 * @brief  Uart_peek
 * @param  *usart
 * @retval The position of rx buffer
 */
int Uart_peek(USART_TypeDef *usart)
{
	if (usart == USART1)
	{
		if(_rx_buffer->head == _rx_buffer->tail)
		{
			return -1;
		}
		else
		{
			return _rx_buffer->buffer[_rx_buffer->tail];
		}
	}
	else if (usart == USART3)
	{
		if(_rx_buffer3->head == _rx_buffer3->tail)
		{
			return -1;
		}
		else
		{
			return _rx_buffer3->buffer[_rx_buffer3->tail];
		}
	}

	return -1;
}


/**
 * @func   copies the data from the incoming buffer into our buffer
 	 	 * Must be used if you are sure that the data is being received
 	 	 * it will copy irrespective of, if the end string is there or not
 	 	 * if the end string gets copied, it returns 1 or else 0
 	 	 * Use it either after (IsDataAvailable) or after (Wait_for) functions
 * @brief  Copy_upto
 * @param  *usart
 * @retval  1 on success and -1 otherwise
 */
int Copy_upto (char *string, char *buffertocopyinto, USART_TypeDef *usart)
{
	int so_far =0;
	int len = strlen (string);
	int indx = 0;

again:
	while ( !IsDataAvailable(usart) );
	while (Uart_peek(usart) != string[so_far])
	{
		if (usart == USART1)
		{
			buffertocopyinto[indx] = _rx_buffer->buffer[_rx_buffer->tail];
			_rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % UART_BUFFER_SIZE;
			indx++;
			while (!IsDataAvailable(USART1));
		}

		else if (usart == USART3)
		{
			buffertocopyinto[indx] = _rx_buffer3->buffer[_rx_buffer3->tail];
			_rx_buffer3->tail = (unsigned int)(_rx_buffer3->tail + 1) % UART_BUFFER_SIZE;
			indx++;
			while (!IsDataAvailable(USART3));
		}
	}
	while (Uart_peek(usart) == string [so_far])
	{
		so_far++;
		buffertocopyinto[indx++] = Uart_read(usart);
		if (so_far == len) return 1;
		timeout = TIMEOUT_DEF;
		while ( (!IsDataAvailable(usart) ) &&timeout );
		if (timeout == 0) return 0;
	}

	if (so_far != len)
	{
		so_far = 0;
		goto again;
	}

	if (so_far == len) return 1;
	else return -1;
}


/**
 * @func  Copies the entered number of characters (blocking mode) from the Rx buffer into the buffer, after some particular string is detected
 * @brief  Get_after
 * @param  *string, numberofchars, *buffertosave, *usart
 * @retval  1 on success and -1 otherwise
 */
int Get_after (char *string, uint8_t numberofchars, char *buffertosave, USART_TypeDef *usart)
{
	for (int indx=0; indx<numberofchars; indx++)
	{
		timeout = TIMEOUT_DEF;
		while ((!IsDataAvailable(usart))&&timeout);  // wait until some data is available
		if (timeout == 0) return 0;  				 // if data isn't available within time, then return 0
		buffertosave[indx] = Uart_read(usart);  	 // save the data into the buffer... increments the tail
	}
	return 1;
}


/**
 * @func    Waits for a particular string to arrive in the incoming buffer... It also increments the tail
		   * get the entered number of characters after the entered string
		   * returns 1, if the string is detected
		   * added timeout feature so the function won't block the processing of the other functions
 * @brief  Copy_upto
 * @param  *string, *usart
 * @retval 1 on success and -1 otherwise
 */
int Wait_for (char *string, USART_TypeDef *usart)
{
	int so_far =0;
	int len = strlen (string);

again:
	timeout = TIMEOUT_DEF;
	while ((!IsDataAvailable(usart))&&timeout);  // let's wait for the data to show up
	if (timeout == 0) return 0;
	while (Uart_peek(usart) != string[so_far])   // peek in the rx_buffer to see if we get the string
	{
		if (usart == USART1)
		{
			if (_rx_buffer->tail != _rx_buffer->head)
			{
				_rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % UART_BUFFER_SIZE;  // increment the tail
			}

			else
			{
				return 0;
			}
		}
		else if (usart == USART3)
		{
			if (_rx_buffer3->tail != _rx_buffer3->head)
			{
				_rx_buffer3->tail = (unsigned int)(_rx_buffer3->tail + 1) % UART_BUFFER_SIZE;  // increment the tail
			}

			else
			{
				return 0;
			}
		}
	}
	while (Uart_peek(usart) == string [so_far]) 	// if we got the first letter of the string
	{
		// now we will peek for the other letters too
		if (usart == USART1)
		{
			so_far++;
			_rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % UART_BUFFER_SIZE;  // increment the tail
			if (so_far == len)
			{
				return 1;
			}
			timeout = TIMEOUT_DEF;
			while ((!IsDataAvailable(usart))&&timeout);
			if (timeout == 0) return 0;
		}
		else if (usart == USART3)
		{
			so_far++;
			_rx_buffer3->tail = (unsigned int)(_rx_buffer3->tail + 1) % UART_BUFFER_SIZE;  // increment the tail
			if (so_far == len)
			{
				return 1;
			}
			timeout = TIMEOUT_DEF;
			while ((!IsDataAvailable(usart))&&timeout);
			if (timeout == 0) return 0;
		}
	}

	if (so_far != len)
	{
		so_far = 0;
		goto again;
	}

	if (so_far == len)
	{
		printf("Wait for complete!\n");
		return 1;
	}
	else
	{
		printf("Wait for complete!\n");
		return 0;
	}

}

/**
 * @func   Interrupt function: The function will be processed in the isr handler function to control the peripheral device
 * @brief  Uart_isr
 * @param  *usart
 */
void Uart_isr (USART_TypeDef *husart)
{
	uint32_t isrflags = READ_REG(husart->SR);
	uint32_t cr1its = READ_REG(husart->CR1);

	/******************************************************************************/
	/*            if DR is not empty and the Rx Int is enabled                    */
	/******************************************************************************/

    if (((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
    {

		/*************************************************************************************/
		/*  @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (Overrun    */
    	/*  		error) and IDLE (Idle line detected) flags are cleared by software       */
    	/*  		sequence: a read operation to USART_SR register followed by a read       */
    	/*  		operation to USART_DR register.   										 */
    	/*  @note   RXNE flag can be also cleared by a read to the USART_DR register    	 */
    	/*  @note   TC flag can be also cleared by software sequence: a read operation to    */
    	/* 			USART_SR register followed by a write operation to USART_DR register.    */
    	/*  @note   TXE flag is cleared only by a write to the USART_DR register.		     */
		/*************************************************************************************/

    	husart->SR;									 /* Read status register */
    	unsigned char c = husart->DR;

    	if (husart == USART1)
    	{
            store_char (c, _rx_buffer);  // store data in buffer
    	}
    	else if (husart == USART3)
    	{
            store_char (c, _rx_buffer3);  // store data in buffer
    	}

        return;
    }

	/******************************************************************************/
	/*        If interrupt is caused due to Transmit Data Register Empty          */
	/******************************************************************************/

    if (((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
    {
    	if (husart == USART1)
    	{
    		if(tx_buffer.head == tx_buffer.tail)
			{
			  // Buffer empty, so disable interrupts
				USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
			}

    		else
			{
				// There is more data in the output buffer. Send the next byte
				unsigned char c = tx_buffer.buffer[tx_buffer.tail];
				tx_buffer.tail = (tx_buffer.tail + 1) % UART_BUFFER_SIZE;


				/*************************************************************************************/
				/*  @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (Overrun    */
		    	/*  		error) and IDLE (Idle line detected) flags are cleared by software       */
		    	/*  		sequence: a read operation to USART_SR register followed by a read       */
		    	/*  		operation to USART_DR register.   										 */
		    	/*  @note   RXNE flag can be also cleared by a read to the USART_DR register    	 */
		    	/*  @note   TC flag can be also cleared by software sequence: a read operation to    */
		    	/* 			USART_SR register followed by a write operation to USART_DR register.    */
		    	/*  @note   TXE flag is cleared only by a write to the USART_DR register.		     */
				/*************************************************************************************/

				husart->SR;
				husart->DR = c;
			}
		}

    	if (husart == USART3)
		{
			if(tx_buffer3.head == tx_buffer3.tail)
			{
			  // Buffer empty, so disable interrupts
				USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
			}

			else
			{
				// There is more data in the output buffer. Send the next byte
				unsigned char c = tx_buffer3.buffer[tx_buffer3.tail];
				tx_buffer3.tail = (tx_buffer3.tail + 1) % UART_BUFFER_SIZE;

				/*************************************************************************************/
				/*  @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (Overrun    */
		    	/*  		error) and IDLE (Idle line detected) flags are cleared by software       */
		    	/*  		sequence: a read operation to USART_SR register followed by a read       */
		    	/*  		operation to USART_DR register.   										 */
		    	/*  @note   RXNE flag can be also cleared by a read to the USART_DR register    	 */
		    	/*  @note   TC flag can be also cleared by software sequence: a read operation to    */
		    	/* 			USART_SR register followed by a write operation to USART_DR register.    */
		    	/*  @note   TXE flag is cleared only by a write to the USART_DR register.		     */
				/*************************************************************************************/

				husart->SR;
				husart->DR = c;
			}
		}

    	return;
    }
}

/* UARTRINGBUFFER_C_ */
/* END FILE */
