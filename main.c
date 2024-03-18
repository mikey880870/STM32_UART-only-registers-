#include "usart.h"
#include "delay.h"
#define pc_mcu_uart USART2
#include <stdio.h>


int fputc(int ch, FILE* stream){
	USART_sendByte(USART2,ch);
	return ch;
}

int main(void){
	
	init_uart(pc_mcu_uart);	
	printf("Hello UART");
	return 0;
}

