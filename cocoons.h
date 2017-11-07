/*
 * cocoons.h
 *
 *  Created on: Aug 12, 2017
 *      Author: lauriaclarke
 */

#ifndef SRC_COCOONS_H_
#define SRC_COCOONS_H_

#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Tlc5940.h"
// #include "patternTimes.h"

#define FAST_THRESHOLD	50
#define SCALE 			50

class Cocoon
{
public:
	byte inPin;
	byte outPin;
	byte ledPin;

	int ledMax;
	int ledMin;

	int inhaleTime;
	int exhaleTime;
	long waitTime;
	int waitTimeF;
	int subtractor;

	unsigned long T2;

	byte state;

	Adafruit_MCP23017* mcp;

	Cocoon();
	
	void setCocoonValues(byte mcp, byte inPin, byte outPin, byte ledPin);
	void printValues();
	void resetCocoonValues();
	void setCocoonTestValues();
	void turnOff();
	void breathe();
	void breatheD(bool P);
	void breatheFaster(int P);
	//---------------------------
	void LEDOff();
	void LEDOn();
	void breathIn(); 
	void breathOut(); 
	void blinkLED();

};



#endif /* SRC_TREES_H_ */