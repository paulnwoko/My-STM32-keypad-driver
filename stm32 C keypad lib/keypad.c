/*
 * keypad.c
 *
 *  Created on: 16 Feb 2020
 *      Author: ngp
 */
#include "keypad.h"

//defines

#define PRESS	 		1
#define RELEASE 		2
#define HOLD	 		3

#define ENABLED	 		1
#define DISABLED	 	0

#define KEYRELEASE		readkeypad_pin(R1_PORT, R1_PIN)&readkeypad_pin(R2_PORT, R2_PIN)&readkeypad_pin(R3_PORT, R3_PIN)&readkeypad_pin(R4_PORT, R4_PIN)

//var declaration
char keychar = ' ',  keychar_ = ' ';


//scan key
void scan_keypad ()
{
	/* Make COL 1 LOW and all other COLs HIGH */
	writekeypad_pin (C1_PORT, C1_PIN, LOW);  //Pull the R1 low
	writekeypad_pin (C2_PORT, C2_PIN, HIGH);  // Pull the R2 High
	writekeypad_pin (C3_PORT, C3_PIN, HIGH);  // Pull the R3 High

	/* Make COL 2 LOW and all other COLs HIGH */
	writekeypad_pin (C1_PORT, C1_PIN, HIGH);  //Pull the R1 low
	writekeypad_pin (C2_PORT, C2_PIN, LOW);  // Pull the R2 High
	writekeypad_pin (C3_PORT, C3_PIN, HIGH);  // Pull the R3 High

	/* Make COL 3 LOW and all other COLs HIGH */
	writekeypad_pin (C1_PORT, C1_PIN, HIGH);  //Pull the R1 low
	writekeypad_pin (C2_PORT, C2_PIN, HIGH);  // Pull the R2 High
	writekeypad_pin (C3_PORT, C3_PIN, LOW);  // Pull the R3 High
}


//
//process key char
//
void process_key(uint16_t GPIO_Pin)
{

	WAIT_FOR_DEBOUNCE();	//delay debounce

	if(GPIO_Pin == R1_PIN){
		if (readkeypad_pin(R1_PORT, R1_PIN) == LOW){

			if (!(readkeypad_pin (C1_PORT, C1_PIN))){
				keychar = '1';
			}
			else if(!(readkeypad_pin (C2_PORT, C2_PIN))){
				keychar = '2';
			}
			else if(!(readkeypad_pin (C3_PORT, C3_PIN))){
				keychar = '3';
			}
		}
	}

	else if(GPIO_Pin == R2_PIN){
		if (readkeypad_pin(R2_PORT, R2_PIN) == LOW){
			if (!(readkeypad_pin (C1_PORT, C1_PIN))){
				keychar = '4';
			}
			else if(!(readkeypad_pin (C2_PORT, C2_PIN))){
				keychar = '5';
			}
			else if(!(readkeypad_pin (C3_PORT, C3_PIN))){
				keychar = '6';
			}
		}
	}

	else if(GPIO_Pin == R3_PIN){
		if (readkeypad_pin(R3_PORT, R3_PIN) == LOW){
			if (!(readkeypad_pin (C1_PORT, C1_PIN))){
				keychar = '7';
			}
			else if(!(readkeypad_pin (C2_PORT, C2_PIN))){
				keychar = '8';
			}
			else if(!(readkeypad_pin (C3_PORT, C3_PIN))){
				keychar = '9';
			}
		}
	}

	else if(GPIO_Pin == R4_PIN){
		if (readkeypad_pin(R4_PORT, R4_PIN) == LOW){
			if (!(readkeypad_pin (C1_PORT, C1_PIN))){
				keychar = '*';
			}
			else if(!(readkeypad_pin (C2_PORT, C2_PIN))){
				keychar = '0';
			}
			else if(!(readkeypad_pin (C3_PORT, C3_PIN))){
				keychar = '#';
			}
		}
	}
}


/*
 * stops/initialize col scanning process
 */
void stop_column_scanning()
{
	writekeypad_pin (C1_PORT, C1_PIN, LOW);
	writekeypad_pin (C2_PORT, C2_PIN, LOW);
	writekeypad_pin (C3_PORT, C3_PIN, LOW);
}


//read keypad character
__weak char get_keypad_char(uint8_t pin)
{
	if(KEYPRESS == ENABLE)
	{
		scan_and_identify_key(pin);
		/*put user keypress code starts here*/
		  initiate_token_capture(keychar);
		/*put user keypress code ends here*/
		keychar_ =  keychar;
		KEYPRESS = DISABLE;
	}

	char ch = keychar;
	keychar = ' ';
	return ch;			// char_to_int_converter(keychar) ;
}


/*//function for scanning row-col identifying pressed key
 * integrated row-col scanning and key-pressed identifier in one functon
 * NOTE STM32F103C8 PINS ARE ACTIVE LOW SO VERIFY THE PIN LOGIC WHILE USING THIS LIB ON OTHER MCU
 */
char scan_and_identify_key(uint16_t GPIO_Pin)
{
	//delay debounce
	WAIT_FOR_DEBOUNCE();
	key_event = ENABLED;//key event is true

	// scan row 1
	if(GPIO_Pin == R1_PIN){
		if (readkeypad_pin(R1_PORT, R1_PIN) == LOW){//detects pressed row

			//scan col1
			writekeypad_pin (C1_PORT, C1_PIN, HIGH);//ACTIVE LOW
			writekeypad_pin (C2_PORT, C2_PIN, LOW);
			writekeypad_pin (C3_PORT, C3_PIN, LOW);
			if (readkeypad_pin (R1_PORT, R1_PIN)){
				keychar = '1';
				writekeypad_pin (C1_PORT, C1_PIN, LOW);
			}
			else{
				//scan col2
				writekeypad_pin (C1_PORT, C1_PIN, LOW);//ACTIVE LOW
				writekeypad_pin (C2_PORT, C2_PIN, HIGH);
				writekeypad_pin (C3_PORT, C3_PIN, LOW);//ACTIVE LOW
				if(readkeypad_pin (R1_PORT, R1_PIN)){
					keychar = '2';
					writekeypad_pin (C2_PORT, C2_PIN, LOW);
					//stop_column_scanning();
				}
				else{
					//scan col3
					writekeypad_pin (C1_PORT, C1_PIN, LOW);//ACTIVE LOW
					writekeypad_pin (C2_PORT, C2_PIN, LOW);
					writekeypad_pin (C3_PORT, C3_PIN, HIGH);//ACTIVE LOW
					if(readkeypad_pin (R1_PORT, R1_PIN)){
						keychar = '3';
						writekeypad_pin (C3_PORT, C3_PIN, LOW);
						//stop_column_scanning();
					}
				}
			}
		}
	}


	//scan row 2
	if(GPIO_Pin == R2_PIN){
		if (readkeypad_pin(R2_PORT, R2_PIN) == LOW){

			//scan col1
			writekeypad_pin (C1_PORT, C1_PIN, HIGH);//ACTIVE LOW
			writekeypad_pin (C2_PORT, C2_PIN, LOW);//ACTIVE LOW
			writekeypad_pin (C3_PORT, C3_PIN, LOW);//ACTIVE LOW
			if (readkeypad_pin (R2_PORT, R2_PIN)){
				keychar = '4';
				writekeypad_pin (C1_PORT, C1_PIN, LOW);
			}
			else{
				//scan col2
				writekeypad_pin (C1_PORT, C1_PIN, LOW);//ACTIVE LOW
				writekeypad_pin (C2_PORT, C2_PIN, HIGH);//ACTIVE LOW
				writekeypad_pin (C3_PORT, C3_PIN, LOW);//ACTIVE LOW
				if(readkeypad_pin (R2_PORT, R2_PIN)){
					keychar = '5';
					writekeypad_pin (C2_PORT, C2_PIN, LOW);
				}
				else{
					//scan col3
					writekeypad_pin (C1_PORT, C1_PIN, LOW);//ACTIVE LOW
					writekeypad_pin (C2_PORT, C2_PIN, LOW);//ACTIVE LOW
					writekeypad_pin (C3_PORT, C3_PIN, HIGH);//ACTIVE LOW
					if(readkeypad_pin (R2_PORT, R2_PIN)){
						keychar = '6';
						writekeypad_pin (C3_PORT, C3_PIN, LOW);
					}
				}
			}
		}
	}


	//scan row3
	if(GPIO_Pin == R3_PIN){
		if (readkeypad_pin(R3_PORT, R3_PIN) == LOW){

			//scan col1
			writekeypad_pin (C1_PORT, C1_PIN, HIGH);//ACTIVE LOW
			writekeypad_pin (C2_PORT, C2_PIN, LOW);//ACTIVE LOW
			writekeypad_pin (C3_PORT, C3_PIN, LOW);//ACTIVE LOW
			if (readkeypad_pin (R3_PORT, R3_PIN)){
				keychar = '7';
				writekeypad_pin (C1_PORT, C1_PIN, LOW);
			}
			else{
				//scan col2
				writekeypad_pin (C1_PORT, C1_PIN, LOW);//ACTIVE LOW
				writekeypad_pin (C2_PORT, C2_PIN, HIGH);//ACTIVE LOW
				writekeypad_pin (C3_PORT, C3_PIN, LOW);//ACTIVE LOW
				if(readkeypad_pin (R3_PORT, R3_PIN)){
					keychar = '8';
					writekeypad_pin (C2_PORT, C2_PIN, LOW);
				}
				else{
					//scan col3
					writekeypad_pin (C1_PORT, C1_PIN, LOW);//ACTIVE LOW
					writekeypad_pin (C2_PORT, C2_PIN, LOW);//ACTIVE LOW
					writekeypad_pin (C3_PORT, C3_PIN, HIGH);//ACTIVE LOW
					if(readkeypad_pin (R3_PORT, R3_PIN)){
						keychar = '9';
						writekeypad_pin (C3_PORT, C3_PIN, LOW);
					}
				}
			}
		}
	}


	//scan row4
	if(GPIO_Pin == R4_PIN){
		if (readkeypad_pin(R4_PORT, R4_PIN) == LOW){

			//scan col1
			writekeypad_pin (C1_PORT, C1_PIN, HIGH);//ACTIVE LOW
			writekeypad_pin (C2_PORT, C2_PIN, LOW);//ACTIVE LOW
			writekeypad_pin (C3_PORT, C3_PIN, LOW);//ACTIVE LOW
			if (readkeypad_pin (R4_PORT, R4_PIN)){
				keychar = '*';
				writekeypad_pin (C1_PORT, C1_PIN, LOW);
			}
			else{
				//scan col2
				writekeypad_pin (C1_PORT, C1_PIN, LOW);//ACTIVE LOW
				writekeypad_pin (C2_PORT, C2_PIN, HIGH);//ACTIVE LOW
				writekeypad_pin (C3_PORT, C3_PIN, LOW);//ACTIVE LOW
				if(readkeypad_pin (R4_PORT, R4_PIN)){
					keychar = '0';
					writekeypad_pin (C2_PORT, C2_PIN, LOW);
				}
				else{
					//scan col3
					writekeypad_pin (C1_PORT, C1_PIN, LOW);//ACTIVE LOW
					writekeypad_pin (C2_PORT, C2_PIN, LOW);//ACTIVE LOW
					writekeypad_pin (C3_PORT, C3_PIN, HIGH);//ACTIVE LOW
					if(readkeypad_pin (R4_PORT, R4_PIN)){
						keychar = '#';
						writekeypad_pin (C3_PORT, C3_PIN, LOW);
					}
				}
			}
		}
	}

	return keychar;
}


//to generate key press, release and hold event
void generate_event(){
	uint8_t tnow = 0;

	if (KEYPRESS == ENABLE){
		press_event(keychar); //detect press event
		tnow++;

		if(tnow > 10000){
			hold_event();//detect hold event
		}
		//note change keydetect to active low in scan routine
		else if(KEYRELEASE) {	//detect button release
			 release_event();//detect press event
			tnow = 0;//reset timer
		}
	}
}


/*******
 *event functions
 *********/

__weak void press_event(char c)
{
/*
 * implement this event in the main code to overide this weak function
 */
 	//initiate_token_capture(c);
}


__weak void release_event()
{
/*
 * implement this event in the main code to overide this weak function
 */
}


__weak void hold_event(){

	if(HOLD == 3){
		/*
		 * implement this event in the main code to overide this weak function
		 */
	}
	else{
		//reset even here
	}
}


//	 for(int i=0; i<300000; i++);;	//delay debounce
//	 if(GPIO_Pin == GPIO_PIN_3){
//		 if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET){
//			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
//		 }
//	 }
//	 else if(GPIO_Pin == GPIO_PIN_4){
//		 if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET){
//			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
//		 }
//	 }
//	 else if(GPIO_Pin == GPIO_PIN_5){
//		 if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET){
//			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
//			 HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
//		 }
//	 }
//	 else if(GPIO_Pin == GPIO_PIN_6){
//		 if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_RESET){
//			 HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
//		 }
//	 }
//	 else ;

