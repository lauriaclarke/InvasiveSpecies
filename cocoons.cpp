#include "cocoons.h"
#include "trees.h"
#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Tlc5940.h"


Cocoon::Cocoon(){}

void Cocoon::setCocoonValues(Adafruit_MCP23017* mcp, int inPin, int outPin, int ledPin, long inhaleTime, long exhaleTime, long waitTime)
{
	this->inPin = inPin;
	this->outPin = outPin;
	this->ledPin = ledPin;
	this->inhaleTime = inhaleTime;
	this->exhaleTime = exhaleTime;
	this->waitTime = waitTime;
	this->mcp = mcp;
	this->T2 = 0;
	this->state = 0;
	this->ledHigh = 4095;
	this->ledLow = 0;
}


void Cocoon::breathe() 
{
	unsigned long T1 = millis();

	if((this->state == 0) && (T1 - T2 >= waitTime)) 
	{
		state = 1; 
		T2 = T1; 
		this->mcp->digitalWrite(this->inPin, HIGH);

		Tlc.set(this->ledPin, );
		Tlc.update();
	}
	else if ((this->state == 1) && (T1 - T2 >= inhaleTime)) 
	{
		state = 2; 
		T2 = T1; 
		this->mcp->digitalWrite(this->inPin, LOW);
		this->mcp->digitalWrite(this->outPin, HIGH);
	} 
	else if ((this->state == 2) && (T1 - T2 >= exhaleTime)) 
	{
		state = 0; 
		T2 = T1; 
		this->mcp->digitalWrite(this->outPin, LOW);
	} 
}


void Cocoon::breathIn()
{
	this->mcp->digitalWrite(this->inPin, HIGH);
	delay(this->inhaleTime);
	this->mcp->digitalWrite(this->inPin, LOW);
}


void Cocoon::breathOut()
{
	this->mcp->digitalWrite(this->outPin, HIGH);
	delay(this->exhaleTime);
	this->mcp->digitalWrite(this->outPin, LOW);
}

void Cocoon::blinkLED()
{
	Serial.println("YO!");
	Serial.println(this->ledPin);
    Tlc.set(0, 1000);   
    Tlc.update();
    delay(2000);
    Tlc.clear();
    Tlc.update();
    delay(1000);
}


