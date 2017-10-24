#include "cocoons.h"
#include "trees.h"
#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
// #include "Tlc5940.h"

// extern Adafruit_MCP23017 mcp;

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

// Speed is value of 0, 1, 2, 3
// Duration will have to be calibrated based on speed

void Cocoon::breathIn() //Adafruit_MCP23017* mcp)
{
	this->mcp->digitalWrite(this->inPin, HIGH);
	delay(this->outDuration);
	this->mcp->digitalWrite(this->inPin, LOW);
}


void Cocoon::breathOut() //Adafruit_MCP23017* mcp)
{
	this->mcp->digitalWrite(this->outPin, HIGH);
	delay(this->outDuration);
	this->mcp->digitalWrite(this->outPin, LOW);
}



