/*
 * spiders.h
 *
 *  Created on: Aug 12, 2017
 *      Author: lauriaclarke
 */

#ifndef SRC_SPIDERS_H_
#define SRC_SPIDERS_H_


class Spider
{
public:
	int* stepperPins;
	int* fanPin;
	int* ledPin;
	int* totalSteps;
	// Stepper spiderStepper; 

	Spider();

	void setSpiderValues(int stepperPins[4], int fanPin[1], int ledPin[1], int totalSteps[1]);
	void raiseSpider(int distance, int speed);
	void lowerSpider(int distance, int speed);
	void animateSpider(int duration, int interval);
	void spinFans(int duration);
	void blinkLED(int duration, int interval);
};


#endif /* SRC_SPIDERS_H_ */