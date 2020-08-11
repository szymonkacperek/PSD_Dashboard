/*
 * gui.c
 *
 *  Created on: 17.02.2019
 *      Author: user
 */

#include "../GUI/gui.h"

#include "../GUI/gui_data.h"

 #include "../Drivers/u8glib/inc/u8g.h"
 #include "../Drivers/u8glib/inc/u8g_arm.h"
 #include "../Drivers/u8glib/pictures.h"
 #include "../GUI/displays.h"
 #include "../GUI/displays.c"
#include "LCD.h"


#include "../GUI/ws_leds.h"
#include "../GUI/ws_leds.c"
#include "../PWM/pwm.h"
#include "../PWM/pwm.c"
#include "string.h"


// Wedlug danych wysylanych po UART w funkcjach ws_* wszystkie ledy od predkosci
// i backlightu powinny byc wylaczone.
void gui_init() {
//	displays_init();
//	Lcd_init();
	pwm_init();
	ws_set_brightness(gui_brightness);
	ws_senddata();
	set_backlight(0);

}

void gui_set_brightness(uint8_t x)
{
	gui_brightness = x;


}



//EKRANY
void gui_screen_main() {

	////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////debug/////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	//Kod ponizej w petli zmienia wartosci zmiennych na wyswietlaczu ( w celu pokazowym)
	//ostatecznie nalezy wykomendowac wszystko az do nastepnego znacznika debug

	TEST_counter++;

	TEST_counter2++;
	if (TEST_counter2 > 3) {
		TEST_counter2 = 0;
		gui_battery = gui_battery - 0.5;
	}
	if (gui_battery < 1) {
		gui_battery = 100;
		TEST_flag = 0;
	}

	TEST_counter3++;
	if (TEST_counter3 > 2) {
		TEST_counter3 = 0;

		if (TEST_flag == 0) {
			gui_speed++;
		} else {
			gui_speed--;
		}

	}

	if (gui_speed > 140) {
		TEST_flag = 1;
		//gui_speed = 0;
	}

	if (gui_speed < 1) {
		TEST_flag = 0;
	}

	gui_charging = 0;

	if (TEST_flag == 0 && gui_power != 12) {
		TEST_counter2++;
		if (TEST_counter2 > 3) {
			TEST_counter2 = 0;
			gui_power = gui_power + 0.2;
		}

		if (gui_power > 12) {
			gui_power = 12;
		}

	}

	if (TEST_flag == 1) {
		TEST_counter2++;
		if (TEST_counter2 > 3) {
			TEST_counter2 = 0;
			gui_power = gui_power - 0.3;
			if (gui_power < 0) {
				gui_power = 0;
			}
		}
	}

	TEST_counter4++;
	if (TEST_counter4 > 20) {
		TEST_counter4 = 0;

		if (TEST_poprz_stan == 0) {
			gui_leds_byte1 = 0b11000101;
			gui_leds_byte2 = 0b00100001;
			TEST_poprz_stan = 1;
		} else {
			gui_leds_byte1 = 0b01000101;
			gui_leds_byte2 = 0b01100000;
			TEST_poprz_stan = 0;
		}

	}

////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////koniec debug/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

	gui_picture_iteration++;

	if (gui_picture_iteration > 7) {
		gui_picture_iteration = 0;
	}

	//co kazda klatke
	display_speed(gui_speed, gui_cruise_speed_set);

	ws_set_leds(gui_leds_byte1, gui_leds_byte2);
	ws_set_speed(gui_speed);
	ws_set_power(gui_power, gui_charging);
	ws_set_battery(gui_battery);
	ws_senddata();

	//  co 2 klatke
	if ((gui_picture_iteration == 0) || (gui_picture_iteration == 2)
			|| (gui_picture_iteration == 4) || (gui_picture_iteration == 6)) {
		display_power(gui_power, gui_charging);
		display_battery(gui_battery);
	}

	// co 8 klatke
	if (gui_picture_iteration == 7) {
		display_gear(gui_gear);
		displays_set_brightness(255);

		ws_set_leds(0xFF, 0xFF);

		if (gui_statement != 0) {
			gui_display_statement(gui_statement);
		} else {
			Lcd_clr();
			asm("nop");

			Lcd_string("     ");
			Lcd_int(gui_h);
			Lcd_string(":");
			Lcd_int(gui_m);

			char output[6];
			snprintf(output, 10, "%.6d", gui_trip); //Convert to string and format

			Lcd_cursor(1, 0);

			Lcd_string("    ");
			Lcd_string(output);
			Lcd_string(" km");
		}
	}

}

void gui_screen_intro() {
//	display_logo();
//	display_power_disable();
//	display_battery_disable();
//	display_gear_disable();

	ws_set_leds(0xFF, 0xFF);
	ws_senddata();

//	Lcd_clr();
//	asm("nop");
//	Lcd_string("   PUT Solar");
//	Lcd_cursor(1, 0);
//	Lcd_string("    Dynamics");

	HAL_Delay(200);

	for (int j = 1; j <= (gui_brightness * 0.7); j++) {
		set_backlight(j);
		HAL_Delay(10);
	}

	ws_set_leds(0, 0);
	ws_senddata();

	set_backlight(gui_brightness * 0.7);

	HAL_Delay(100);
}



void gui_display_statement(uint8_t number)
{

	switch(number)
	{

			case 1:

				Lcd_clr();
				asm("nop");
				Lcd_string("  Low Battery");
				Lcd_cursor(1,0);
				Lcd_string("");

				break;


			case 2:

				Lcd_clr();
				asm("nop");
				Lcd_string(" Cruise control");
				Lcd_cursor(1,0);
				Lcd_string("       ENABLED");

				break;

			case 3:

				Lcd_clr();
				asm("nop");
				Lcd_string(" Cruise control");
				Lcd_cursor(1,0);
				Lcd_string("    DISABLED");

				break;


			case 4:

				Lcd_clr();
				asm("nop");
				Lcd_string("     Charging");
				Lcd_cursor(1,0);
				Lcd_string("");

				break;

			case 5:

				Lcd_clr();
				asm("nop");
				Lcd_string("     Motor");
				Lcd_cursor(1,0);
				Lcd_string("    Failure");

				break;

			case 6:

				Lcd_clr();
				asm("nop");
				Lcd_string("    Battery");
				Lcd_cursor(1,0);
				Lcd_string("    Failure");

				break;

			case 7:

				Lcd_clr();
				asm("nop");
				Lcd_string("  Unidentified");
				Lcd_cursor(1,0);
				Lcd_string("    Failure");

				break;



				//WINCYJ KOMUNIKAT�W
				//WINCYJ KOMUNIKAT�W
				//WINCYJ KOMUNIKAT�W
				//WINCYJ KOMUNIKAT�W
				//WINCYJ KOMUNIKAT�W
				//WINCYJ KOMUNIKAT�W


	default:
	    //jaki� kod
	    break;
	}



}

void gui_test() {
//	pwm_init();
//	set_backlight(2);
//	ws_set_brightness(gui_brightness);
//	ws_senddata();
//
//	ws_set_leds(0xFF, 0xFF);
//	ws_set_speed(70);
//	ws_set_power(6, 0);
//	ws_set_battery(50);
//
//	ws_senddata();
//	HAL_Delay(200);

	////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////debug/////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	//Kod ponizej w petli zmienia wartosci zmiennych na wyswietlaczu ( w celu pokazowym)
	//ostatecznie nalezy wykomendowac wszystko az do nastepnego znacznika debug

	TEST_counter++;

	TEST_counter2++;
	if (TEST_counter2 > 3) {
		TEST_counter2 = 0;
		gui_battery = gui_battery - 0.5;
	}
	if (gui_battery < 1) {
		gui_battery = 100;
		TEST_flag = 0;
	}

	TEST_counter3++;
	if (TEST_counter3 > 2) {
		TEST_counter3 = 0;

		if (TEST_flag == 0) {
			gui_speed++;
		} else {
			gui_speed--;
		}

	}

	if (gui_speed > 140) {
		TEST_flag = 1;
		//gui_speed = 0;
	}

	if (gui_speed < 1) {
		TEST_flag = 0;
	}

	gui_charging = 0;

	if (TEST_flag == 0 && gui_power != 12) {
		TEST_counter2++;
		if (TEST_counter2 > 3) {
			TEST_counter2 = 0;
			gui_power = gui_power + 0.2;
		}

		if (gui_power > 12) {
			gui_power = 12;
		}

	}

	if (TEST_flag == 1) {
		TEST_counter2++;
		if (TEST_counter2 > 3) {
			TEST_counter2 = 0;
			gui_power = gui_power - 0.3;
			if (gui_power < 0) {
				gui_power = 0;
			}
		}
	}

	TEST_counter4++;
	if (TEST_counter4 > 20) {
		TEST_counter4 = 0;

		if (TEST_poprz_stan == 0) {
			gui_leds_byte1 = 0b11000101;
			gui_leds_byte2 = 0b00100001;
			TEST_poprz_stan = 1;
		} else {
			gui_leds_byte1 = 0b01000101;
			gui_leds_byte2 = 0b01100000;
			TEST_poprz_stan = 0;
		}

	}

	////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////koniec debug/////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////


	ws_set_leds(gui_leds_byte1, gui_leds_byte2);
	ws_set_speed(gui_speed);
	ws_set_power(gui_power, gui_charging);
	ws_set_battery(gui_battery);
	ws_senddata();
}
