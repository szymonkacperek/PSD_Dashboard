/*
 * pwm.h
 *
 *  Created on: 17.01.2019
 *      Author: user
 */

#ifndef PWM_H_
#define PWM_H_

#include "stm32f1xx_hal.h"

TIM_HandleTypeDef htim3;

void set_backlight(int bl);
void pwm_init(void);
#endif /* PWM_H_ */
