#include "delay.h"

void delay_timer_enable(TIM_TypeDef* timer){
	if(timer == TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
		while (!(RCC->APB1ENR & RCC_APB1ENR_TIM3EN));
	} 
}

void delay_timer_disable(TIM_TypeDef* timer){
	if(timer == TIM3){
		RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;
	}
}

void delay_timer_init(TIM_TypeDef* timer,int psc,int arr){
	timer->PSC = (uint16_t)(psc-1);
	timer->ARR = (uint16_t)(arr-1);
}

void delay_timer_start(TIM_TypeDef* timer){
	timer->CR1 |= TIM_CR1_CEN;
}

void delay_timer_stop(TIM_TypeDef* timer){
	timer->CR1 &= ~TIM_CR1_CEN;
}

void delay_us(uint16_t us){
	delay_timer_enable(delay_timer);
	delay_timer_init(delay_timer,16,us);
	delay_timer_start(delay_timer);
	while(delay_timer->CNT != 0);
	delay_timer_disable(delay_timer);
}

void delay_ms(uint16_t ms){
	while(ms-- != 0){
		delay_us(1000);
	}
}

void delay_s(uint16_t s){
	while(s-- != 0){
		delay_ms(1000);
	}
}