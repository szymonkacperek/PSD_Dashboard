/*
 * displays.c
 *
 *  Created on: 04.12.2018
 *      Author: Marcin Szykowny
 */
#include <stdlib.h>
#include "displays.h"
#include "stm32f1xx_hal.h"
#include "main.h"

#include "LCD.h"

#include "../Drivers/u8glib/inc/u8g.h"
#include "../Drivers/u8glib/inc/u8g_arm.h"
#include "../Drivers/u8glib/pictures.h"

void display_battery(double value) //USE OLED #1 (LEFT) to display battery level
{
	char output[10] = "";
	snprintf(output, 10, "%4.1f", value); //Convert to string and format

	HAL_I2C_Mem_Write(&hi2c1, 0xE0, 4, 1, 0, 0, 10); //USTAW ADRES
	//u8g_small.font = u8g_font_fub30r;

	u8g_FirstPage(&u8g_small);
	do
	{
		if(value <=9)
		{
			u8g_DrawStr(&u8g_small, 31, 32, output);
		}
		else
		{
			u8g_DrawStr(&u8g_small, 20, 32, output);
		}

	} while ( u8g_NextPage(&u8g_small) );

}

void display_gear(int state) //USE OLED #2 (CENTER) to display gear setting (R N D)
{
	HAL_I2C_Mem_Write(&hi2c1, 0xE0, 10, 10, 0, 0, 10); //USTAW ADRES
	switch (state)
	{
	    case 0: // code to be executed if state = 0 (neutral);


	    	u8g_FirstPage(&u8g_small);
	    	do
	    	{
	    		u8g_DrawBitmap(&u8g_small, 0, 0, 16, 64, neutral);
	    	} while ( u8g_NextPage(&u8g_small) );


	        break;

	    case 1: // code to be executed if state = 1(drive);


	    	u8g_FirstPage(&u8g_small);
	    	do
	    	{
	    		u8g_DrawBitmap(&u8g_small, 0, 0, 16, 64, drive);
	    	} while ( u8g_NextPage(&u8g_small) );



	        break;

	    case 2: // code to be executed if state = 2(reverse);

	    	u8g_FirstPage(&u8g_small);
	    	do
	    	{
	    		u8g_DrawBitmap(&u8g_small, 0, 0, 16, 64, reverse);
	    	} while ( u8g_NextPage(&u8g_small) );

	        break;
	}
}


void display_power_disable(void)
{
	HAL_I2C_Mem_Write(&hi2c1, 0xE0, 1, 1, 0, 0, 10); //USTAW ADRES
	u8g_FirstPage(&u8g_small);
		do
		{
			u8g_DrawBitmap(&u8g_small, 0, 0, 16, 64, blank_small);
		} while ( u8g_NextPage(&u8g_small) );
}

void display_battery_disable(void)
{
	HAL_I2C_Mem_Write(&hi2c1, 0xE0, 4, 1, 0, 0, 10); //USTAW ADRES
	u8g_FirstPage(&u8g_small);
		do
		{
			u8g_DrawBitmap(&u8g_small, 0, 0, 16, 64, blank_small);
		} while ( u8g_NextPage(&u8g_small) );

}
void display_gear_disable(void)
{
	HAL_I2C_Mem_Write(&hi2c1, 0xE0, 10, 10, 0, 0, 10); //USTAW ADRES
	u8g_FirstPage(&u8g_small);
		do
		{
			u8g_DrawBitmap(&u8g_small, 0, 0, 16, 64, blank_small);
		} while ( u8g_NextPage(&u8g_small) );

}



void display_power(double value,uint8_t charging) //USE OLED #3 (RIGHT) to display current power consumption
{

	char output[10] = "";
	snprintf(output, 10, "%4.1f", value); //Convert to string and format

	HAL_I2C_Mem_Write(&hi2c1, 0xE0, 1, 1, 0, 0, 10); //USTAW ADRES
	//u8g_DrawBitmap(&u8g_small, 0, 0, 16, 64, blank_small);



	u8g_FirstPage(&u8g_small);
	do
	{
		if(charging == 1)
		{
			u8g_DrawBitmap(&u8g_small, 0, 0, 16, 64, charge);
		}

		if(value <=9)
		{
			u8g_DrawStr(&u8g_small, 31, 32, output);
		}
		else
		{
			u8g_DrawStr(&u8g_small, 20, 32, output);
		}
	} while ( u8g_NextPage(&u8g_small) );



}

void display_speed(double value, uint8_t cruise)
{
		char output[10];
		char output_cruise[10];

		snprintf(output, 10, "%3.0f", value); //Convert to string and format
		snprintf(output_cruise, 10, "%d", cruise); //Convert to string and format
		u8g_FirstPage(&u8g_big);
		do
		{

			if(value <= 9)
			{
				u8g_big.font = u8g_font_fur49n;
				u8g_DrawStr(&u8g_big, 72, 50, output);
			}

			if((value > 9) && (value <= 99))
			{
				u8g_big.font = u8g_font_fur49n;
				u8g_DrawStr(&u8g_big, 34, 50, output);
			}

			if(value > 99)
			{
				u8g_big.font = u8g_font_fur49n;
				u8g_DrawStr(&u8g_big, 1, 50, output);
			}



			//u8g_DrawHLine(&u8g_big, 0, 54, 128);

			u8g_big.font = u8g_font_6x10;
			u8g_DrawStr(&u8g_big, 104,63, "km/h");


			if(cruise > 0)
			{

				u8g_DrawStr(&u8g_big, 1,63, "set ");
				u8g_DrawStr(&u8g_big, 22,63, output_cruise);

			}





		} while ( u8g_NextPage(&u8g_big) );



}

void displays_init(void)
{




	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);// MUSI BYC

	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_SET); // (reset i2c)


	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET); // MUSI BYC mux+
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET); // MUSI BYC mux

	  	u8g_InitComFn(&u8g_big, &u8g_dev_ssd1309_128x64_hw_spi, u8g_com_hw_spi_fn);


		HAL_I2C_Mem_Write(&hi2c1, 0xE0, 1, 1, 0, 0, HAL_MAX_DELAY); //USTAW ADRES
		HAL_Delay(5);
		u8g_InitComFn(&u8g_small, &u8g_dev_ssd1306_128x32_2x_i2c, u8g_com_hw_i2c_fn); //here we init our u8glib driver
		u8g_small.font = u8g_font_fub30r;
		HAL_Delay(5);
		HAL_I2C_Mem_Write(&hi2c1, 0xE0, 2, 1, 0, 0, HAL_MAX_DELAY); //USTAW ADRES
		HAL_Delay(5);
		u8g_InitComFn(&u8g_small, &u8g_dev_ssd1306_128x32_2x_i2c, u8g_com_hw_i2c_fn); //here we init our u8glib driver
		u8g_small.font = u8g_font_fub30r;
		HAL_Delay(5);
	  	HAL_I2C_Mem_Write(&hi2c1, 0xE0, 4, 1, 0, 0, HAL_MAX_DELAY); //USTAW ADRES
		HAL_Delay(5);
	  	u8g_InitComFn(&u8g_small, &u8g_dev_ssd1306_128x32_2x_i2c, u8g_com_hw_i2c_fn); //here we init our u8glib driver
		u8g_small.font = u8g_font_fub30r;

	  HAL_Delay(100);
}

void display_logo(void)
{
	u8g_FirstPage(&u8g_big);
	do
	{
	u8g_DrawBitmap(&u8g_big, 0, 0, 16, 64, psd_logo_big);
	} while ( u8g_NextPage(&u8g_big) );

}

void displays_set_brightness(uint8_t val)
{

	u8g_SetContrast(&u8g_big, val);

	HAL_I2C_Mem_Write(&hi2c1, 0xE0, 1, 1, 0, 0, HAL_MAX_DELAY); //USTAW ADRES
	u8g_SetContrast(&u8g_small, val);
	HAL_I2C_Mem_Write(&hi2c1, 0xE0, 2, 1, 0, 0, HAL_MAX_DELAY); //USTAW ADRES
	u8g_SetContrast(&u8g_small, val);
	HAL_I2C_Mem_Write(&hi2c1, 0xE0, 4, 1, 0, 0, HAL_MAX_DELAY); //USTAW ADRES
	u8g_SetContrast(&u8g_small, val);

}
