#ifndef _USART_H_
#define _USART_H_

#include "stm32f407xx.h"

void init_uart(USART_TypeDef* uart);
void USART_sendChar(USART_TypeDef* uart,char c);
void USART_sendByte(USART_TypeDef* uart,uint8_t byte);
void USART_sendArray(USART_TypeDef* uart,uint8_t *array,uint16_t length);
void USART_sendString(USART_TypeDef* uart,uint8_t *string);

uint8_t USART_getChar(USART_TypeDef* uart);


#endif
