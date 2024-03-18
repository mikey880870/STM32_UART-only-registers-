#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f407xx.h"
#define delay_timer TIM3

void delay_timer_enable(TIM_TypeDef* timer);
void delay_timer_disable(TIM_TypeDef* timer);
void timer_reload(TIM_TypeDef* timer);
void delay_timer_init(TIM_TypeDef* timer,int psc,int arr);
void delay_timer_start(TIM_TypeDef* timer);
void delay_timer_stop(TIM_TypeDef* timer);

void delay_us(uint16_t us);
void delay_ms(uint16_t ms);
void delay_s(uint16_t s);

#endif

