
#include "LCD.h"
#include "stm32f1xx_hal.h"

/************************************** Static declarations **************************************/

static void lcd_write_data(uint8_t data);
static void lcd_write_command(uint8_t command);
static void lcd_write(uint8_t data, uint8_t len);

/************************************** Function definitions **************************************/

/**
 * Create new Lcd_HandleTypeDef and initialize the Lcd
 */
/**
 * Initialize 16x2-lcd without cursor
 */
void Lcd_init()
{
	 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET); // Podciagniecie RST
	 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET); // Podciagniecie DC do zera



	//lcd_write_command(FUNCTION_SET | OPT_DL | OPT_N);


	//lcd_write_command(CLEAR_DISPLAY);						// Clear screen
	//lcd_write_command(DISPLAY_ON_OFF_CONTROL | OPT_D);		// Lcd-on, cursor-off, no-blink
	//lcd_write_command(ENTRY_MODE_SET | OPT_INC);			// Increment cursor

		lcd_write_command(0x80);
		lcd_write_command(0x2A);  /* **** Set "RE"=1  00101010B */
		lcd_write_command(0x71);
		lcd_write_command(0xC0);
		lcd_write_command(0x00);
		lcd_write_command(0x28);

		lcd_write_command(0x08); /* **** Set Sleep Mode On     */
		lcd_write_command(0x2A); /* **** Set "RE"=1  00101010B */
		lcd_write_command(0x79); /* **** Set "SD"=1  01111001B */

		lcd_write_command(0xD5);
		lcd_write_command(0x70);
		lcd_write_command(0x78); /* **** Set "SD"=0            */

		//lcd_write_command(0x08);
		/* **** Set 5-dot, 3 or 4 line(0x09), 1 or 2 line(0x08) */
		lcd_write_command(0x08);


		lcd_write_command(0x06); /* **** Set Com31-->Com0  Seg0-->Seg99 */
		lcd_write_command(0x72);
		lcd_write_command(0xC0);
		lcd_write_command(0x01);

		/**** Set OLED Characterization ***/
		lcd_write_command(0x2A);   /* **** Set "RE"=1  */
		lcd_write_command(0x79);   /* **** Set "SD"=1 */

		/**** CGROM/CGRAM Management ***/
	#if 0
		lcd_write_command(0x72); /* **** Set ROM */
		lcd_write_command(0x00); /*  **** Set ROM A and 8 CGRAM */
	#endif

		lcd_write_command(0xDC);    /* **** Set ROM */
		lcd_write_command(0x00);    /* **** Set ROM A and 8 CGRAM */

		lcd_write_command(0xDA);    /* **** Set Seg Pins HW Config */
		lcd_write_command(0x10);

		lcd_write_command(0x81);    /* **** Set Contrast */
		lcd_write_command(0xD9);
		lcd_write_command(0x8F);    /* **** Set Contrast */

		lcd_write_command(0xF1);

		lcd_write_command(0xDB);   /* **** Set VCOM deselect level */
		lcd_write_command(0x30);   /* **** VCC x 0.83              */

		lcd_write_command(0xDC);   /* *Set gpio -turn EN for 15V generator on. */
		lcd_write_command(0x03);

		lcd_write_command(0x78);   /* **** Exiting Set OLED Characterization */
		lcd_write_command(0x28);

		//flip display with these two lines, comment out the 0x06 write below
		//lcd_write_command(0x2A);
		//lcd_write_command(0x05);   /* **** Set Entry Mode (invert) */

		lcd_write_command(0x06);     /* **** Set Entry Mode */

		lcd_write_command(0x28);     /* **** Set "IS"=0 , "RE" =0 /28 */
		lcd_write_command(0x01);
		lcd_write_command(0x80);     /* Set DDRAM Address to 0x80 (line 1 start)*/

		//HAL_Delay(100);

		lcd_write_command(0x0C);   /* **** Turn on Display */























}

/**
 * Write a number on the current position
 */
void Lcd_clr()
{
	lcd_write_command(CLEAR_DISPLAY);
	lcd_write_command(RETURN_HOME);


}



void Lcd_int(int number)
{
	char buffer[11];
	sprintf(buffer, "%d", number);
	Lcd_string(buffer);
}

/**
 * Write a string on the current position
 */
void Lcd_string(char * string)
{
	for(uint8_t i = 0; i < strlen(string); i++)
	{
		lcd_write_data(string[i]);
	}
}

/**
 * Set the cursor position
 */
void Lcd_cursor(uint8_t row, uint8_t col)
{

	lcd_write_command(SET_DDRAM_ADDR | ((row * 0x40) + col));
}


/************************************** Static function definition **************************************/

/**
 * Write a byte to the command register
 */
void lcd_write_command(uint8_t command)
{

	uint8_t buf = 0x1F;
	HAL_SPI_Transmit(&hspi2, &buf, 1, HAL_MAX_DELAY);

	buf = command & 0x0F;
	HAL_SPI_Transmit(&hspi2 , &buf, 1, HAL_MAX_DELAY);

	buf = (command >> 4) & 0x0F;
	HAL_SPI_Transmit(&hspi2 , &buf , 1, HAL_MAX_DELAY);

}

/**
 * Write a byte to the data register
 */
void lcd_write_data(uint8_t data)
{
	uint8_t buf = 0x5F;
	HAL_SPI_Transmit(&hspi2, &buf, 1,10);

	buf = data & 0x0F;
	HAL_SPI_Transmit(&hspi2 , &buf, 1, 10);

	buf = (data >> 4) & 0x0F;
	HAL_SPI_Transmit(&hspi2 , &buf , 1, 10);
}

/**
 * Set len bits on the bus and toggle the enable line
 */
void lcd_write(uint8_t data, uint8_t len)
{
	/*
	for(uint8_t i = 0; i < len; i++)
	{
		HAL_GPIO_WritePin(lcd->data_port[i], lcd->data_pin[i], (data >> i) & 0x01);
	}

	HAL_GPIO_WritePin(lcd->en_port, lcd->en_pin, 1);
	DELAY(1);
	HAL_GPIO_WritePin(lcd->en_port, lcd->en_pin, 0); 		// Data receive on falling edge
	*/
}
