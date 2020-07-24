#include "stm32f0xx.h"

// konfiguracja timera opóźnienia
void wait_init(void){
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;	// enable TIM17 clock
	TIM17->CR1 = 0;
	TIM17->PSC = 48-1;			// F = 1kHz
	TIM17->CR1 = TIM_CR1_CEN;		// counter enabled
	TIM17->EGR = 1;				// trigger update event to reload timer registers
}

// opóźnienie w us
void waitus(uint32_t time){
	time = time+TIM17->CNT;
	while((uint16_t)(time - TIM17->CNT) < 0x8000){}
}

// opóźnienie w ms
void waitms(uint32_t time){
	while(time--) waitus(1000);
}

