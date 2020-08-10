/*
 * gui.h
 *
 *  Created on: 17.02.2019
 *      Author: user
 */

#ifndef GUI_H_
#define GUI_H_


uint8_t gui_speed = 0;
double gui_power = 0;
double gui_battery = 100;
uint8_t gui_brightness =100;
uint8_t gui_charging = 0;
uint8_t gui_gear = 1;
int gui_trip = 0;
uint8_t gui_cruise_speed_set = 0;
uint8_t gui_cruise_speed_limit = 0;
uint8_t gui_cruise_mode = 0;
uint8_t gui_leds_byte1 = 0;
uint8_t gui_leds_byte2 = 0;

uint8_t gui_picture_iteration = 0;
uint8_t gui_statement = 0;

uint8_t gui_h = 12;
uint8_t gui_m = 10;


void gui_init();
void gui_set_brightness(uint8_t x);
void gui_get_data_from_can();
void gui_display_statement(uint8_t number);

void gui_screen_main();
void gui_screen_intro();
void gui_test();

uint8_t dbg_blink = 0;


uint16_t TEST_counter = 0;
uint16_t TEST_counter2 = 0;
uint16_t TEST_counter3 = 0;
uint16_t TEST_counter4 = 0;
uint8_t TEST_flag = 0;
uint8_t TEST_poprz_stan = 0;




#endif /* GUI_H_ */
