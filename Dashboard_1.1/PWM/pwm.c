/*
 * pwm.c
 *
 *  Created on: 17.01.2019
 *      Author: user
 */

#include "../PWM/pwm.h"
#include "stm32f1xx_hal.h"

void set_backlight(int bl)
{
	  TIM3->CCR1 = bl;
	  TIM3->CCR2 = bl;
	  TIM3->CCR3 = bl;
}

void pwm_init()
{
	  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // Uruchamia generowanie PWM przez timer 4 na kanale 1
	  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // Uruchamia generowanie PWM przez timer 4 na kanale 2
	  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3); // Uruchamia generowanie PWM przez timer 4 na kanale 3
}
