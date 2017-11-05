#include "cocoons.h"
#include "trees.h"
#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Tlc5940.h"
#include "tlc_fades.h"

int count;

Cocoon::Cocoon(){}

void Cocoon::setCocoonValues(Adafruit_MCP23017* mcp, int inPin, int outPin, int ledPin) //, long inhaleTime, long exhaleTime, long waitTime, long waitTimeF)
{
	this->inPin = inPin;
	this->outPin = outPin;
	this->ledPin = ledPin;
	this->inhaleTime = (int)random(500, 1000); 		//inhaleTime;
	this->exhaleTime = (int)random(500, 1000); 		//exhaleTime;
	this->waitTime   = 10000L + random(1000, 30000); 	// waitTime;
	this->waitTimeF  = (int)random(5, 200);			// waitTimeF;


	Serial.print(this->inhaleTime);
	Serial.print(", ");
	Serial.print(this->exhaleTime);
	Serial.print(", ");
	Serial.print(this->waitTime);
	Serial.print(", ");
	Serial.println(this->waitTimeF);


	this->count = 0;
	this->mcp = mcp;
	this->T2 = 0;
	this->state = 0;
	this->ledMax = 4095;
	this->ledMin = 100;
}


void Cocoon::breathe() 
{
	unsigned long T1 = millis();

	if((state == 0) && (T1 - T2 >= (unsigned long)waitTime)) 
	{		
		// Serial.println("S0->S1");
		// Serial.println(T1);
		state = 1; 
		T2 = T1; 
		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + (unsigned long)inhaleTime);
	}
	else if ((this->state == 1) && (T1 - T2 >= (unsigned long)inhaleTime)) 
	{
		// Serial.println("S1->S2");
		// Serial.println(T1);
		state = 2; 
		T2 = T1; 
		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
		tlc_addFade(ledPin, ledMax, ledMin, millis(), millis() + (unsigned long)exhaleTime);
	} 
	else if ((this->state == 2) && (T1 - T2 >= (unsigned long)exhaleTime)) 
	{
		// Serial.println("S2->S0");
		// Serial.println(T1);
		state = 0; 
		T2 = T1; 
		mcp->digitalWrite(outPin, LOW);
	} 

	tlc_updateFades();
}



/*
int Cocoon::breatheR(unsigned long wT, unsigned long iT, unsigned long eT) 
{
	// static int count; // = 0;
	unsigned long T1 = millis();

	if((state == 0) && (T1 - T2 >= wT)) 
	{
		Serial.println("S0->S1");
		state = 1; 
		T2 = T1; 
		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + iT);
	}
	else if ((state == 1) && (T1 - T2 >= iT)) 
	{
		Serial.println("S1->S2");
		state = 2; 
		T2 = T1; 
		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
		tlc_addFade(ledPin, ledMax, ledMin, millis(), millis() + eT);
	} 
	else if ((state == 2) && (T1 - T2 >= eT)) 
	{
		Serial.println("S2->S0");
		state = 0; 
		T2 = T1; 
		mcp->digitalWrite(outPin, LOW);

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
*/



void Cocoon::breatheFaster(int P) //long wT, long wTF, long iT, long eT) 
{	
	// static int count = 0;
	unsigned long T1 = millis();
	unsigned long tt1 = waitTime;
	unsigned long tt2 = (unsigned long)inhaleTime;
	unsigned long tt3 = (unsigned long)exhaleTime;
	unsigned long period = tt1 + tt2 + tt3;
	unsigned long steps = (unsigned long)AWAKETIME / period;
 	unsigned long scale = (waitTime - (long)waitTimeF) / steps;

//---------------------------------------------------

	// if(count < steps)
	// {
	// 	tt1 = waitTime - scale * count;

	// 	if(tt2 < 2000L)
	// 	{
	// 		tt2 = inhaleTime + 100L * count;
	// 		tt3 = exhaleTime + 100L * count;
	// 	}
	// 	else
	// 	{
	// 		tt2 = 2000L;
	// 		tt3 = 1000L;
	// 	}
	// }
	// else
	// {
	// 	tt1 = waitTimeF;
	// 	tt2 = 2000L;
	// 	tt3 = 1000L;
	// }

//---------------------------------------------------
 	// If state == waiting and time exceeds wait, then inhale
	if((state == 0) && (T1 - T2 >= tt1)) 
	{
		// Serial.println("S0->S1");
		state = 1; 
		T2 = T1; 

		if(tt1 > waitTimeF)
		{
			tt1 = waitTime - scale * count;
		}
		else
		{
			tt1 = waitTimeF;
		}

		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + tt2);
	}
	// If state == inhale and time exceeds inhale, then exhale
	else if ((state == 1) && (T1 - T2 >= tt2)) 
	{
		// Serial.println("S1->S2");
		state = 2; 
		T2 = T1; 

		if(tt2 < 2000)
		{
			tt2 = inhaleTime + 100L * count;
		}
		else
		{
			tt2 = 2000;
		}

		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
		tlc_addFade(ledPin, ledMax, ledMin, millis(), millis() + tt3);
	} 
	// If state == exhale and time exceeds exhale, then wait
	else if ((state == 2) && (T1 - T2 >= tt3)) 
	{
		// Serial.println("S2->S0");
		state = 0; 
		T2 = T1; 

		if(tt3 < 1000)
		{
			tt3 = exhaleTime + 100L * count;
		}
		else
		{
			tt3 = 1000L;
		}

		mcp->digitalWrite(outPin, LOW);

		if(this->count < steps)
		{
			this->count = count + 1;
			// Serial.println(count);
		}
	} 

	tlc_updateFades();
}

	// if(P)
 	// 	{
	 // 		Serial.println(AWAKETIME);
	 // 		Serial.print("period - ");
	 // 		Serial.print(period);
	 // 		Serial.print("  steps - ");
	 // 		Serial.print(steps);
	 // 		Serial.print("  scale - ");
	 // 		Serial.println(scale);
		//     Serial.print("wait - ");
		// 	Serial.print(tt1);
		//     Serial.print("  inhale - ");
		// 	Serial.print(tt2);
		// 	Serial.print("  exhale - ");
		// 	Serial.println(tt3);
		// 	Serial.println(count);
 	// 	}

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


