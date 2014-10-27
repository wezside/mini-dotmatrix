/**
 * @author wezside
 * Based on the code from Bildr (http://bildr.org/2011/02/74hc595/)
 */

#include "Arduino.h"

//How many of the shift registers - change this
#define number_of_74hc595s 1 

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

// Lower will be faster must be larger than 0
#define SPEED 80

int SER_Pin = 8;   //pin 14 on the 75HC595
int RCLK_Pin = 9;  //pin 12 on the 75HC595
int SRCLK_Pin = 10; //pin 11 on the 75HC595

int anime = 0;	
int counter = 0;
int shift_right_counter = 8;

char in[] = {0, 0, 0, 0};
char out[] = {0, 0, 0, 0,
			  0, 0, 0, 0,
			  0, 0, 0, 0};

// A: 0110 1001 1111 1001 
// b: 0100 0111 0101 0111 
char chars[] = {6, 9, 15, 9, 
				4, 7, 5, 7};
int char_index = 0;

// Registers or Shift register pins
boolean registers[numOfRegisterPins];

// Forward declarations
void clearRegisters();
void writeRegisters();
void row(int i);
void col(int i);

void setup()
{
	Serial.begin(115200);

	pinMode(SER_Pin, OUTPUT);
	pinMode(RCLK_Pin, OUTPUT);
	pinMode(SRCLK_Pin, OUTPUT);

	// Reset all register pins
	clearRegisters();
	writeRegisters();	
}               

//set all register pins to LOW
void clearRegisters()
{
	for(int i = numOfRegisterPins - 1; i >=  0; i--)
	{
		registers[i] = LOW;
	}
} 

//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters()
{
	digitalWrite(RCLK_Pin, LOW);
	for(int i = numOfRegisterPins - 1; i >=  0; i--)
	{
		digitalWrite(SRCLK_Pin, LOW);
		int val = registers[i];
		digitalWrite(SER_Pin, val);
		digitalWrite(SRCLK_Pin, HIGH);

	}
	digitalWrite(RCLK_Pin, HIGH);
}

void setRegisterPin(int index, int value)
{
	registers[index] = value;
}

void row(int i)
{
	setRegisterPin(i, HIGH);  
}

void col(int i)
{
	setRegisterPin(i + 4, HIGH);
}	

void loop()
{
	clearRegisters();
	writeRegisters();

	if (shift_right_counter == -1)
	{
		for (int i = 0; i < 4; ++i)
		{
			in[i] = out[i] | (chars[char_index * 4 + i] << 3);
		}	
		// shift_right_counter = 12;
	}

	// Wrap around for row counter
	if (counter == 4) counter = 0;

	// Light up the row with index
	row(counter);

	// Animate in (right to left)
	if (anime % SPEED == 0 && shift_right_counter != -1)
	{
		// For each of the rows
		for (int i = 0; i < 4; ++i)
		{
			out[i] = in[i] >> shift_right_counter;
		}		
		shift_right_counter--;
		Serial.println(shift_right_counter, DEC);
	}
	else if (shift_right_counter == -1) shift_right_counter = 8;

	// Animation frame counter
	anime++;

	for (int i = 0; i < 4; ++i)
	{
		if (!(out[counter] & 1 << i)) col(i);
	}
	writeRegisters();
	delay(5);  

	if (counter < 4) counter ++;
	else counter = 0;
}
