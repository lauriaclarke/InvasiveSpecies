#include "Arduino.h"
#include "spiders.h"
#include <MCPStepper.h>


Spider::Spider(){}

void Spider::setSpiderValues(Stepper* spiderStepper, Adafruit_MCP23017* mcp, int fanPin, int ledPin)
{
	this->spiderStepper = spiderStepper;
	this->mcp = mcp;
	this->fanPin = fanPin;
	this->ledPin = ledPin;

	this->T2 = 0;
	this->fanState = LOW;
	this->ledState = LOW;
}


void Spider::raiseSpider(int distance, int speed)
{
	spiderStepper->setSpeed(speed);
	spiderStepper->step(distance);
}


void Spider::lowerSpider(int distance, int speed)
{
	spiderStepper->setSpeed(speed);
	spiderStepper->step(-distance);
}



void Spider::blinkLED(int onInterval, int offInterval)
{
  unsigned long T1 = millis();
 
  if((ledState == LOW) && (T1 - T2 >= onInterval)) 
  {
  	ledState = HIGH;
    T2 = T1; 
    digitalWrite(ledPin, ledState);
  }
  if((ledState == HIGH) && (T1 - T2 >= offInterval)) 
  {
  	ledState = LOW;
    T2 = T1; 
    digitalWrite(ledPin, ledState);
  }
}


void Spider::spinFans(int onInterval, int offInterval)
{
  unsigned long T1 = millis();
 
  if((ledState == LOW) && (T1 - T2 >= onInterval)) 
  {
  	ledState = HIGH;
    T2 = T1; 
    mcp->digitalWrite(fanPin, fanState);
  }
  if((ledState == HIGH) && (T1 - T2 >= offInterval)) 
  {
  	ledState = LOW;
    T2 = T1; 
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
