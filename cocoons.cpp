#include "cocoons.h"
#include "trees.h"
#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Tlc5940.h"


Cocoon::Cocoon(){}

void Cocoon::setCocoonValues(Adafruit_MCP23017* mcp, int inPin, int outPin, int ledPin, int inDuration, int outDuration)
{
	this->inPin = inPin;
	this->outPin = outPin;
	this->ledPin = ledPin;
	this->inDuration = inDuration;
	this->outDuration = outDuration;
	this->mcp = mcp;
}


void Cocoon::breathIn()
{
	this->mcp->digitalWrite(this->inPin, HIGH);
	delay(this->outDuration);
	this->mcp->digitalWrite(this->inPin, LOW);
}


void Cocoon::breathOut()
{
	this->mcp->digitalWrite(this->outPin, HIGH);
	delay(this->outDuration);
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


