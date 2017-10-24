#include "cocoons.h"
#include "trees.h"
#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
// #include "Tlc5940.h"

// extern Adafruit_MCP23017 mcp;

Cocoon::Cocoon(){}

void Cocoon::setCocoonValues(int inPin, int outPin, int ledPin, int inDuration, int outDuration)
{
	this->inPin = inPin;
	this->outPin = outPin;
	this->ledPin = ledPin;
	this->inDuration = inDuration;
	this->outDuration = outDuration;
}

// Speed is value of 0, 1, 2, 3
// Duration will have to be calibrated based on speed

void Cocoon::breathIn(int speed, Adafruit_MCP23017* mcp)
{
	// int value;
	// value = 150 + speed * 33;

	// if(speed < 4)
	// {
	// 	analogWrite(this->inPin, value);
	// }
	// else if(speed == 4)
	// {
	// 	mcp->digitalWrite(this->inPin, HIGH);
	// 	mcp->digitalWrite(this->ledPin, HIGH);
	// }

	// int d = 200;

	// for(int i = 0; i < this->inDuration; i = i + d)
	// {
	// 	mcp->digitalWrite(this->inPin, HIGH);
	// 	mcp->digitalWrite(this->ledPin, HIGH);
	// 	delay(d/2);
	// 	mcp->digitalWrite(this->inPin, LOW);
	// 	mcp->digitalWrite(this->ledPin, LOW);
	// 	delay(d/2);
	// }

	// Serial.println("IN PIN: ");
	// Serial.print(this->inPin);

	// mcp.digitalWrite(this->inPin, HIGH);
	// // mcp.digitalWrite(this->ledPin, HIGH);
	// delay(10000);
	// // delay(this->outDuration);
	// mcp.digitalWrite(this->inPin, LOW);
	// // mcp.digitalWrite(this->ledPin, LOW);

	Serial.println("IN PIN: ");
	Serial.print(this->inPin);

	mcp->digitalWrite(this->inPin, HIGH);
	// mcp.digitalWrite(this->ledPin, HIGH);
	delay(1000);
	// delay(this->outDuration);
	mcp->digitalWrite(this->inPin, LOW);
	// mcp.digitalWrite(this->ledPin, LOW);	
	Serial.println("Done!");
}


void Cocoon::breathOut(int speed, Adafruit_MCP23017* mcp)
{
	int value;
	// value = 150 + speed * 33;
	// if(speed < 4)
	// {
	// 	analogWrite(this->outPin, value);
	// }
	// else if(speed == 4)
	// {
		mcp->digitalWrite(this->outPin, HIGH);
		// mcp.digitalWrite(this->ledPin, HIGH);
	// }

	delay(this->outDuration);
	mcp->digitalWrite(this->outPin, LOW);
	// mcp.digitalWrite(this->ledPin, LOW);
}



