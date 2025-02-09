#include "Arduino.h"
#include "spiders.h"
#include <MCPStepper.h>


Spider::Spider(){}

void Spider::setSpiderValues(byte spiderStepper, byte fanPin, byte ledPin)
{
	if(spiderStepper == 0)
	{
		this->spiderStepper = &stepperA;
	}
	else if(spiderStepper == 1)
	{
		this->spiderStepper = &stepperB;
	}

	this->mcp = &mcp2;
	this->fanPin = fanPin;
	this->ledPin = ledPin;

	this->tFan = 0;
	this->tLED = 0;
	this->fanState = LOW;
	this->ledState = LOW;
	this->stepperState = 0;
}


void Spider::raiseSpider(int distance, int speed)
{
	spiderStepper->setSpeed(speed);
	spiderStepper->step(distance);
	this->stepperState = this->stepperState + distance;
}


void Spider::lowerSpider(int distance, int speed)
{
	spiderStepper->setSpeed(speed);
	spiderStepper->step(-distance);
	this->stepperState = this->stepperState - distance;
}


void Spider::turnSpiderOff(long interval)
{
	unsigned long T1 = millis();

	if(T1 - tOn >= interval)
	{
		mcp->digitalWrite(ledPin, LOW);
		mcp->digitalWrite(fanPin, LOW);
	}

}


void Spider::blinkLED(long onInterval, long offInterval)
{
	unsigned long T1 = millis();

	if((ledState == LOW) && (T1 - tLED >= onInterval)) 
	{
		ledState = HIGH;
		tLED = T1; 
		mcp->digitalWrite(ledPin, ledState);
	}
	if((ledState == HIGH) && (T1 - tLED >= offInterval)) 
	{
		ledState = LOW;
		tLED = T1; 
		mcp->digitalWrite(ledPin, ledState);
	}
}


void Spider::spinFans(long onInterval, long offInterval)
{
	unsigned long T1 = millis();

	if((ledState == LOW) && (T1 - tFan >= onInterval)) 
	{
		ledState = HIGH;
		tFan = T1; 
		mcp->digitalWrite(fanPin, fanState);
	}
	if((ledState == HIGH) && (T1 - tFan >= offInterval)) 
	{
		ledState = LOW;
		tFan = T1; 
		mcp->digitalWrite(fanPin, fanState);
	}
}



// OLD -----------


// void Spider::animateSpider(int duration, int interval)
// {
// 	int N = duration / interval;

// 	analogWrite(this->fanPin, 100);

// 	for(int i = 0; i < N; i++)
// 	{
// 		digitalWrite(this->ledPin, HIGH);
// 		delay(interval);
// 		digitalWrite(this->ledPin, LOW);
// 		delay(interval);
// 	}

// 	analogWrite(this->fanPin, LOW);
// }



// void Spider::spinFans(int duration)
// {
// 	digitalWrite(this->fanPin, HIGH);
// 	delay(duration);
// 	digitalWrite(this->fanPin, HIGH);
// }

// void Spider::blinkLED(int duration, int interval)
// {
//   unsigned long currentMillis = millis();
 
//   if(currentMillis - previousMillis >= interval) 
//   {
//     // save the last time you blinked the LED 
//     previousMillis = currentMillis;   

//     // if the LED is off turn it on and vice-versa:
//     if (ledState == LOW)
//       ledState = HIGH;
//     else
//       ledState = LOW;

//     // set the LED with the ledState of the variable:
//     digitalWrite(ledPin, ledState);
//   }
// }



// void Spider::blinkLED(int duration, int interval)
// {
// 	int N = duration / interval;

// 	for(int i = 0; i < N; i++)
// 	{
// 		digitalWrite(this->ledPin, HIGH);
// 		delay(interval);
// 		digitalWrite(this->ledPin	, LOW);
// 		delay(interval);
// 	}
// }
