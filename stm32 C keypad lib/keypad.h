/*
 * keypad.h
 *
 *  Created on: 15 Dec 2019
 *      Author: pc
 */
#include "stm32f1xx_hal.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "token_capture.h"
/*
 * definiton of keypad pins
 * here you define how rows and cols are connected to the gpio
 */
#define R1_PORT 	GPIOB
#define R1_PIN 		GPIO_PIN_3

#define R2_PORT 	GPIOB
#define R2_PIN 		GPIO_PIN_4

#define R3_PORT		GPIOB
#define R3_PIN 		GPIO_PIN_5

#define R4_PORT 	GPIOB
#define R4_PIN 		GPIO_PIN_6

#define C1_PORT 	GPIOB
#define C1_PIN 		GPIO_PIN_7

#define C2_PORT 	GPIOB
#define C2_PIN 		GPIO_PIN_8

#define C3_PORT 	GPIOB
#define C3_PIN 		GPIO_PIN_9

#define ENABLED 			1
#define DISABLED 			0

#define _DEBOUNCE_TIME		25	//20ms
#define WAIT_FOR_DEBOUNCE()	HAL_Delay(_DEBOUNCE_TIME)

/*
 * define gpio read/write functions here
 * define how you read and write gpio in your mcu/tool chain
 * ex if you are reading/writing directly through gpio register, you define the code here
 */
#define readkeypad_pin		HAL_GPIO_ReadPin
#define writekeypad_pin		HAL_GPIO_WritePin

#define HIGH 				GPIO_PIN_SET
#define LOW					GPIO_PIN_RESET


//variable definition
_Bool key_event;
uint_fast8_t KEYPRESS;

/*
 * function prototype
 */
char read_keypad (void);

void test_keypad(char c);//to test all keypress action

char get_keypad_char(uint8_t pin);	//saves keyedin char in an input buffer array

char scan_and_identify_key(uint16_t GPIO_Pin); //function for scanning row-col identifying pressed key

void backspace(char c);

void clear_inputchar();//clears every input char in the buffer

void process_key(uint16_t GPIO_Pin); //identify key pressed

void scan_keypad();

void stop_column_scanning();//stops column pins

void generate_event();


__weak void press_event(char c);
__weak void release_event();
__weak void hold_event();

#endif /* KEYPAD_H_ */
