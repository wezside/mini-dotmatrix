/**
 * @author wezside
 * Based on the code from Bildr (http://bildr.org/2011/02/74hc595/)
 */

#include "Arduino.h"

int SER_Pin = 8;   //pin 14 on the 75HC595
int RCLK_Pin = 9;  //pin 12 on the 75HC595
int SRCLK_Pin = 10; //pin 11 on the 75HC595
int counter = 0;

// 1001 0110 0000 0110
char a[] = {9, 6, 0, 6};

//How many of the shift registers - change this
#define number_of_74hc595s 1 

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];

void clearRegisters();
void writeRegisters();
void row(int i);
void col(int i);

void setup()
{
	a[0] = a[0] >> 4;
	pinMode(SER_Pin, OUTPUT);
	pinMode(RCLK_Pin, OUTPUT);
	pinMode(SRCLK_Pin, OUTPUT);

	//reset all register pins
	clearRegisters();
	writeRegisters();
	Serial.begin(115200);
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

void loop()
{
	clearRegisters();
	writeRegisters();

	if (counter == 4) counter = 0;
	row(counter);

	for (int i = 0; i < 4; ++i)
	{
		if (a[counter] & 1 << i) col(i);
	}

	writeRegisters();
	delay(5);  

	if (counter < 4) counter ++;
	else counter = 0;
}

void row(int i)
{
	setRegisterPin(i, HIGH);  
}

void col(int i)
{
	setRegisterPin(i + 4, HIGH);
}	