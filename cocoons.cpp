#include "cocoons.h"
#include "trees.h"
#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Tlc5940.h"
#include "tlc_fades.h"


Cocoon::Cocoon(){}

void Cocoon::setCocoonValues(Adafruit_MCP23017* mcp, int inPin, int outPin, int ledPin, long inhaleTime, long exhaleTime, long waitTime, long waitTimeF)
{
	this->inPin = inPin;
	this->outPin = outPin;
	this->ledPin = ledPin;
	this->inhaleTime = inhaleTime;
	this->exhaleTime = exhaleTime;
	this->waitTime = waitTime;
	this->waitTimeF = waitTimeF;

	this->mcp = mcp;
	this->T2 = 0;
	this->state = 0;
	this->ledMax = 4095;
	this->ledMin = 100;
}



int Cocoon::breatheR(long wT, long iT, long eT) 
{
	static int count = 0;
	unsigned long T1 = millis();

	if((state == 0) && (T1 - T2 >= wT)) 
	{
		state = 1; 
		T2 = T1; 
		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + iT);
	}
	else if ((state == 1) && (T1 - T2 >= iT)) 
	{
		state = 2; 
		T2 = T1; 
		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
		tlc_addFade(ledPin, ledMax, ledMin, millis(), millis() + eT);
	} 
	else if ((state == 2) && (T1 - T2 >= eT)) 
	{
		state = 0; 
		T2 = T1; 
		mcp->digitalWrite(outPin, LOW);

		if(count < FAST_THRESHOLD)
		{
			count++;
		}
		else
		{
			count = 0;
		}
	} 

	tlc_updateFades();

	return count;
}

void Cocoon::breathe() 
{
	unsigned long T1 = millis();

	if((state == 0) && (T1 - T2 >= waitTime)) 
	{
		state = 1; 
		T2 = T1; 
		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + inhaleTime);
	}
	else if ((this->state == 1) && (T1 - T2 >= inhaleTime)) 
	{
		state = 2; 
		T2 = T1; 
		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
		tlc_addFade(ledPin, ledMax, ledMin, millis(), millis() + exhaleTime);
	} 
	else if ((this->state == 2) && (T1 - T2 >= exhaleTime)) 
	{
		state = 0; 
		T2 = T1; 
		mcp->digitalWrite(outPin, LOW);
	} 

	tlc_updateFades();
}

void Cocoon::breatheFaster() //long wT, long wTF, long iT, long eT) 
{	
	int count;
	unsigned long tt1 = waitTime;
	unsigned long tt2 = inhaleTime;
	unsigned long tt3 = exhaleTime;
	unsigned long period = tt1 + tt2 + tt3;
	unsigned long steps = AWAKETIME / period;
 	unsigned long scale = (waitTime - waitTimeF) / steps;

 	Serial.print(steps);
 	Serial.print(", ");
 	Serial.println(scale);

	count = breatheR(tt1, tt2, tt3);

	if((count < steps) && (tt1 > waitTimeF))
	{
		// Serial.println(tt1);
		tt1 = waitTime - scale * count;

		if(tt2 < 2000)
		{
			tt2 = inhaleTime + scale * count;
			tt3 = exhaleTime + scale * count;
		}
		else
		{
			tt2 = 2000;
			tt3 = 1000;
		}
	}
	else
	{
		tt1 = waitTimeF;
	}

	Serial.print(tt1);
    Serial.print(", ");
	Serial.print(tt2);
	Serial.print(", ");
	Serial.println(tt3);

	Serial.println(count);
}



// ------------------------------------------------------


void Cocoon::breatheNoFade() 
{
	unsigned long T1 = millis();

	if((state == 0) && (T1 - T2 >= waitTime)) 
	{
		state = 1; 
		T2 = T1; 
		mcp->digitalWrite(inPin, HIGH);
		Tlc.set(ledPin, HIGH);
	}
	else if ((this->state == 1) && (T1 - T2 >= inhaleTime)) 
	{
		state = 2; 
		T2 = T1; 
		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
	} 
	else if ((this->state == 2) && (T1 - T2 >= exhaleTime)) 
	{
		state = 0; 
		T2 = T1; 
		mcp->digitalWrite(outPin, LOW);
		Tlc.set(ledPin, LOW);
	} 

	Tlc.update();
}



void Cocoon::breathIn()
{
	this->mcp->digitalWrite(this->inPin, HIGH);
	delay(this->inhaleTime);
	this->mcp->digitalWrite(this->inPin, LOW);
}


void Cocoon::breathOut()
{
	this->mcp->digitalWrite(this->outPin, HIGH);
	delay(this->exhaleTime);
	this->mcp->digitalWrite(this->outPin, LOW);
}



void Cocoon::LEDOn()
{
    Tlc.set(this->ledPin, 1000);   
    Tlc.update();
}


void Cocoon::LEDOff()
{
    Tlc.set(this->ledPin, 0);   
    Tlc.update();
}


void Cocoon::blinkLED()
{
    Tlc.set(0, 1000);   
    Tlc.update();
    delay(2000);
    Tlc.clear();
    Tlc.update();
    delay(1000);
}


