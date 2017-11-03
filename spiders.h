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
	int fanPin;
	int ledPin;

	int fanState;
	int ledState;
	int stepperState;

	unsigned long tFan;
	unsigned long tLED;
	unsigned long tOn;
	
	Adafruit_MCP23017* mcp;
	Stepper* spiderStepper; 

	Spider();

	void setSpiderValues(Stepper* spiderStepper, Adafruit_MCP23017* mcp, int fanPin, int ledPin);
	void raiseSpider(int distance, int speed);
	void lowerSpider(int distance, int speed);
	// void animateSpider(int duration, int interval);
	void spinFans(int onInterval, int offInterval);
	void blinkLED(int onInterval, int offInterval);
	void turnSpiderOff(int interval);

};


#endif /* SRC_SPIDERS_H_ */