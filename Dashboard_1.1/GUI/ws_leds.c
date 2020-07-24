/*
 * ws_leds.c
 *
 *  Created on: 16.02.2019
 *      Author: user
 */

#include "../GUI/ws_leds.h"
#include "stm32f1xx_hal.h"
#include <math.h>

void ws_senddata(void)
{
	char uart_buffer[9] = {ws_spd,ws_spd_lim,ws_bat,ws_powr,ws_powr_mod,ws_leds1,ws_leds2,ws_led_bright,ws_mod};
	HAL_UART_Transmit(&huart1, (uint8_t*)uart_buffer,9, 100);
}

void ws_set_leds(uint8_t byte1,uint8_t byte2)
{
	ws_leds1 = byte1;
	ws_leds2 = byte2;
}

void ws_set_speed(uint8_t x)
{
	uint8_t buf = floor(x/2.5);
	if(buf > 56)
	{
		buf = 56;
	}
	ws_spd = buf;

}
void ws_set_power(double x, uint8_t charging)
{

	if(charging == 0)
	{
		uint8_t buf = floor(x/0.75);
		if(buf > 16)
		{
			buf = 16;
		}
		ws_powr = buf;

		ws_powr_mod = 0;
	}
	if(charging == 1)
	{
		uint8_t buf = floor(x);
		if(buf > 3)
		{
			buf = 3;
		}
		ws_powr = buf;

		ws_powr_mod = 1;
	}

}
void ws_set_battery(double x)
{

	uint8_t buf = 0;

	if(x == 0)
	{
		buf = 0;
	}

	if((x <= 6.66)&&(x > 0))
	{
		buf = 1;
	}

	if((x > 6.66)&&(x <= 13.33))
	{
		buf = 2;
	}

	if((x > 13.33)&&(x <= 20))
	{
		buf = 3;
	}

	if(x > 20)
	{
		buf = floor(x/5.25);
	}


	if(buf > 19)
	{
		buf = 19;
	}
	ws_bat = buf;
}

void ws_set_brightness(uint8_t y)
{
	ws_led_bright = y;

}
