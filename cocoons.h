/*
 * cocoons.h
 *
 *  Created on: Aug 12, 2017
 *      Author: lauriaclarke
 */

#ifndef SRC_COCOONS_H_
#define SRC_COCOONS_H_
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Tlc5940.h"

class Cocoon
{
public:
	int inPin;
	int outPin;
	int ledPin;
	int ledHigh;
	int ledLow;

	long inhaleTime;
	long exhaleTime;
	long waitTime;
	unsigned long T2;

	int state;

	Adafruit_MCP23017* mcp;


	Cocoon();
	
	void setCocoonValues(Adafruit_MCP23017* mcp, int inPin, int outPin, int ledPin, long inhaleTime, long exhaleTime, long waitTime);
	void breathe();
	void breathIn(); 
	void breathOut(); 
	void blinkLED();

};



#endif /* SRC_TREES_H_ */