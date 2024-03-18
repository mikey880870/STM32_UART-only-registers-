#include "usart.h"

void init_uart(USART_TypeDef* uart){  
	/* GPIO init */
	//PA9 usart tx/ PA10 usart rx
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	// AF mode
	GPIOA->MODER &= (~GPIO_MODER_MODE2 | ~GPIO_MODER_MODE3);
	GPIOA->MODER |= (0b10 << GPIO_MODER_MODE2_Pos | 0b10 << GPIO_MODER_MODE3_Pos);

	/* choose function of PA9, it is AF7 (usart2_tx) here. */
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2_Msk;
	GPIOA->AFR[0] |= (0x7 << GPIO_AFRL_AFSEL2_Pos);
	/* choose function of PA10, it is AF7 (usart2_rx) here. */
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3_Msk;
	GPIOA->AFR[0] |= (0x7 << GPIO_AFRL_AFSEL3_Pos);
	//tx push pull,rx output
	GPIOA->OTYPER &= ~(0x1 << 2) | ~(0x1 << 3);
	GPIOA->OTYPER |= (0x0 << 2) | (0x1 << 3);
	//rx no pull up or pull up 
	GPIOA->PUPDR &= ~(0b11 << GPIO_PUPDR_PUPD3_Pos);
	GPIOA->PUPDR |= (0b01 << GPIO_PUPDR_PUPD3_Pos);
	// tx very high speed
	GPIOA->OSPEEDR &= ~(0b11 << GPIO_OSPEEDR_OSPEED2_Pos);
	GPIOA->OSPEEDR |= (0b11 << GPIO_OSPEEDR_OSPEED2_Pos);
	
	/* uart init */
	uart->CR1 = 0x00;     /* clear CR register*/
	uart->BRR = (104 << 4) | 3;
	// close flow control
	uart->CR3 &= ~(USART_CR3_RTSE | USART_CR3_CTSE);
	uart->CR1 |= USART_CR1_RE;  /* Rx enable */ 
	uart->CR1 |= USART_CR1_TE;  /* Tx enable */
	uart->CR1 |= (0x0 << 12) | (0x0 << 10);     /* 8 data bits ,parity disable*/
	uart->CR2 &= 0x0 << USART_CR2_STOP_Pos;  /* 1 stop bit */
	uart->CR1 |= USART_CR1_RXNEIE; /* RXNE interrupt enable */
	uart->CR1 |= USART_CR1_UE;  /* Enable usart */

	NVIC_EnableIRQ(USART2_IRQn); /* usart interrupt enable */
}

void USART_sendChar(USART_TypeDef* uart,char c){
	uart->DR = c;
	// wait txe flag
	while(!(uart->SR & (1 << 6)));
}

void USART_sendByte(USART_TypeDef* uart,uint8_t byte){
	uart->DR = byte;
	while(!(uart->SR & (1 << 6)));
}

void USART_sendArray(USART_TypeDef* uart,uint8_t *array,uint16_t length){
	for(uint16_t i = 0;i < length;i++){
		USART_sendByte(uart,array[i]);
	}
}

void USART_sendString(USART_TypeDef* uart,uint8_t *string){
	for(uint8_t i = 0;string[i] != '\0';i++){
		USART_sendByte(uart,string[i]);
	}
}

uint8_t USART_getChar(USART_TypeDef* uart){
	uint8_t temp;
	// wait rxne flag
	while(!(uart->SR & (1 << 5)));
	temp = uart->DR;
	return temp;
}


