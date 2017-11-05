#include "cocoons.h"
#include "trees.h"
#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Tlc5940.h"
#include "tlc_fades.h"


Cocoon::Cocoon(){}

void Cocoon::setCocoonValues(Adafruit_MCP23017* mcp, int inPin, int outPin, int ledPin, long inhaleTime, long exhaleTime, long waitTime)
{
	this->inPin = inPin;
	this->outPin = outPin;
	this->ledPin = ledPin;
	this->inhaleTime = inhaleTime;
	this->exhaleTime = exhaleTime;
	this->waitTime = waitTime;

	this->mcp = mcp;
	this->T2 = 0;
	this->state = 0;
	this->ledMax = 4095;
	this->ledMin = 100;
}


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

void Cocoon::breatheFasterP() 
{	
	static int count;
	unsigned long T1 = millis();

	long tt1 = waitTime;
	long tt2 = inhaleTime;
	long tt3 = exhaleTime;

	if(tt1 > 1000)
	{
		// Serial.println(tt1);
		tt1 = waitTime - SCALE * count;

		if(tt2 < 2000)
		{
			tt2 = inhaleTime + SCALE * count;
			tt3 = exhaleTime + SCALE * count;
		}
		else
		{
			tt2 = 2000;
			tt3 = 1000;
		}
	}
	else
	{
		tt1 = 1000;
	}

	if((state == 0) && (T1 - T2 >= tt1)) 
	{
		state = 1; 
		T2 = T1; 
		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + tt2);
	}
	else if ((this->state == 1) && (T1 - T2 >= tt2)) 
	{
		state = 2; 
		T2 = T1; 
		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
		tlc_addFade(ledPin, ledMax, ledMin, millis(), millis() + tt3);
	} 
	else if ((this->state == 2) && (T1 - T2 >= tt3)) 
	{
		state = 0; 
		T2 = T1; 
		mcp->digitalWrite(outPin, LOW);
		
		if(count < FAST_THRESHOLD)
		{
			count++;
			Serial.print(tt1);
			Serial.print(", ");
			Serial.print(tt2);
			Serial.print(", ");
			Serial.println(tt3);

			Serial.println(count);
		}
		else
		{
			count = 0;
		}
	} 

	tlc_updateFades();
}

void Cocoon::breatheFaster() 
{	
	static int count;
	unsigned long T1 = millis();

	long tt1 = waitTime;
	long tt2 = inhaleTime;
	long tt3 = exhaleTime;

	if(tt1 > 1000)
	{
		tt1 = waitTime - SCALE * count;

		if(tt2 < 2000)
		{
			tt2 = inhaleTime + SCALE * count;
			tt3 = exhaleTime + SCALE * count;
		}
		else
		{
			tt2 = 2000;
			tt3 = 1000;
		}
	}
	else
	{
		tt1 = 1000;
	}


	// Serial.println(tt1);

	if((state == 0) && (T1 - T2 >= tt1)) 
	{
		state = 1; 
		T2 = T1; 
		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + tt2);
	}
	else if ((this->state == 1) && (T1 - T2 >= tt2)) 
	{
		state = 2; 
		T2 = T1; 
		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
		tlc_addFade(ledPin, ledMax, ledMin, millis(), millis() + tt3);
	} 
	else if ((this->state == 2) && (T1 - T2 >= tt3)) 
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
}

// ------------------------------------------------------

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


