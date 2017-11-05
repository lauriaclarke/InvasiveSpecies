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
	int inPin;
	int outPin;
	int ledPin;

	int ledMax;
	int ledMin;

	long inhaleTime;
	long exhaleTime;
	long waitTime;
	long waitTimeF;

	unsigned long T2;

	int state;

	Adafruit_MCP23017* mcp;

	Cocoon();
	
	void setCocoonValues(Adafruit_MCP23017* mcp, int inPin, int outPin, int ledPin); //, long inhaleTime, long exhaleTime, long waitTime, long waitTimeF);
	void printValues();
	int  breatheR(long wT, long iT, long eT);
	void breathe();
	void breatheNoFade();
	// void breatheFaster(); //long wT, long wTF, long iT, long eT);
	void LEDOff();
	void LEDOn();
	void breathIn(); 
	void breathOut(); 
	void blinkLED();

};



#endif /* SRC_TREES_H_ */