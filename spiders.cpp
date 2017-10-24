#include "Arduino.h"
#include "spiders.h"
#include <Stepper.h>


Spider::Spider(){}

void Spider::setSpiderValues(int stepperPins[4], int fanPin[1], int ledPin[1], int totalSteps[1])
{
	this->stepperPins = stepperPins;
	this->fanPin = fanPin;
	this->ledPin = ledPin;
	this->totalSteps = totalSteps;
}


void Spider::animateSpider(int duration, int interval)
{
	int N = duration / interval;

	analogWrite(this->fanPin[0], 100);

	for(int i = 0; i < N; i++)
	{
		digitalWrite(this->ledPin[0], HIGH);
		delay(interval);
		digitalWrite(this->ledPin[0], LOW);
		delay(interval);
	}

	analogWrite(this->fanPin[0], LOW);
}



void Spider::spinFans(int duration)
{
	digitalWrite(this->fanPin[0], HIGH);
	delay(duration);
	digitalWrite(this->fanPin[0], HIGH);
}


void Spider::blinkLED(int duration, int interval)
{
	int N = duration / interval;

	for(int i = 0; i < N; i++)
	{
		digitalWrite(this->ledPin[0], HIGH);
		delay(interval);
		digitalWrite(this->ledPin[0], LOW);
		delay(interval);
	}
}
