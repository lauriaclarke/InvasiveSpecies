/*
 * spiders.h
 *
 *  Created on: Aug 12, 2017
 *      Author: lauriaclarke
 */

#ifndef SRC_SPIDERS_H_
#define SRC_SPIDERS_H_

#include <MCPStepper.h>	
#include "Adafruit_MCP23017.h"

class Spider
{
public:
	byte fanPin;
	byte ledPin;

	byte fanState;
	byte ledState;
	int stepperState;

	unsigned long tFan;
	unsigned long tLED;
	unsigned long tOn;
	
	Adafruit_MCP23017* mcp;
	Stepper* spiderStepper; 

	Spider();

	void setSpiderValues(byte spiderStepper, byte fanPin, byte ledPin);
	void raiseSpider(int distance, int speed);
	void lowerSpider(int distance, int speed);
	// void animateSpider(int duration, int interval);
	void spinFans(long onInterval, long offInterval);
	void blinkLED(long onInterval, long offInterval);
	void turnSpiderOff(long interval);

};

extern Stepper stepperA;
extern Stepper stepperA;

#endif /* SRC_SPIDERS_H_ */