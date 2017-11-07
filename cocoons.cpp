#include "cocoons.h"
#include "trees.h"
#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Tlc5940.h"
#include "tlc_fades.h"

extern volatile bool ISRFlag;
extern volatile bool TIMERFlag;
// extern volatile unsigned long ISRTime;

Cocoon::Cocoon(){}

void Cocoon::setCocoonValues(byte mcp, byte inPin, byte outPin, byte ledPin) //, long inhaleTime, long exhaleTime, long waitTime, long waitTimeF)
{
	this->inPin = inPin;
	this->outPin = outPin;
	this->ledPin = ledPin;
	this->inhaleTime = (int)random(500, 1000); 		//inhaleTime;
	this->exhaleTime = (int)random(500, 1000); 		//exhaleTime;
	this->waitTime   = random(1000, 50000); 	// waitTime;
	this->waitTimeF  = (int)random(5, 200);			// waitTimeF;
	// this->subtractor = (this->waitTime - this->waitTimeF) / (AWAKETIME / 3000L);

	printValues();

	if(mcp == 0)
	{
		this->mcp = &mcp0;
	}
	else if(mcp == 0)
	{
		this->mcp = &mcp1;
	}

	this->T2 = 0;
	this->state = 0;
	this->ledMax = 4095;
	this->ledMin = 100;
}

void Cocoon::printValues()
{
	Serial.print(this->inhaleTime);
	Serial.print(", ");
	Serial.print(this->exhaleTime);
	Serial.print(", ");
	Serial.print(this->waitTime);
	Serial.print(", ");
	Serial.println(this->waitTimeF);
}

void Cocoon::setCocoonTestValues()
{
	this->inhaleTime = 2000;
	this->exhaleTime = 2000;
	this->waitTime = 4000;
}

void Cocoon::resetCocoonValues()
{
	this->inhaleTime = (int)random(500, 1000); 		//inhaleTime;
	this->exhaleTime = (int)random(500, 1000); 		//exhaleTime;
	this->waitTime   = random(1000, 50000); 	// waitTime;
	this->waitTimeF  = (int)random(5, 200);			// waitTimeF;

	// printValues();
}

void Cocoon::breathe() 
{
	unsigned long T1 = millis();
	long TR = (waitTime / 2) * random(0, 2);

	if((state == 0) && (T1 - T2 >= TR)) 
	{		
		// Serial.println("S0->S1");
		// Serial.println(T1);
		state = 2; 
		T2 = T1; 		
		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + (unsigned long)inhaleTime);
	}	
	if((state == 1) && (T1 - T2 >= (unsigned long)waitTime)) 
	{		
		// Serial.println("S0->S1");
		// Serial.println(T1);
		state = 2; 
		T2 = T1; 
		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + (unsigned long)inhaleTime);
	}
	else if ((this->state == 2) && (T1 - T2 >= (unsigned long)inhaleTime)) 
	{
		// Serial.println("S1->S2");
		// Serial.println(T1);
		state = 3; 
		T2 = T1; 
		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
		tlc_addFade(ledPin, ledMax, ledMin, millis(), millis() + (unsigned long)exhaleTime);
	} 
	else if ((this->state == 3) && (T1 - T2 >= (unsigned long)exhaleTime)) 
	{
		// Serial.println("S2->S0");
		// Serial.println(T1);
		state = 1; 
		T2 = T1; 
		mcp->digitalWrite(outPin, LOW);
	} 

	tlc_updateFades();
}

void Cocoon::breatheFaster(int P) //long wT, long wTF, long iT, long eT) 
{	
	unsigned long T1 = millis();

 	// If state == waiting and time exceeds wait, then inhale
	if((state == 0) && (T1 - T2 >= waitTime)) 
	{
		// Serial.println("S0->S1");
		state = 1; 
		T2 = T1; 

		if(waitTime - 1000 > waitTimeF)
		{
			waitTime = waitTime - 2000;
		}
		else
		{
			waitTime = waitTimeF;
		}

		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + inhaleTime);
	}
	// If state == inhale and time exceeds inhale, then exhale
	else if ((state == 1) && (T1 - T2 >= inhaleTime)) 
	{
		// Serial.println("S1->S2");
		state = 2; 
		T2 = T1; 

		if(inhaleTime < 2000)
		{
			inhaleTime = inhaleTime + 100L;
		}
		else
		{
			inhaleTime = 2000;
		}

		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
		tlc_addFade(ledPin, ledMax, ledMin, millis(), millis() + exhaleTime);
	} 
	// If state == exhale and time exceeds exhale, then wait
	else if ((state == 2) && (T1 - T2 >= exhaleTime)) 
	{
		// Serial.println("S2->S0");
		state = 0; 
		T2 = T1; 

		if(exhaleTime < 1000)
		{
			exhaleTime = exhaleTime + 100L;
		}
		else
		{
			exhaleTime = 1000L;
		}

		mcp->digitalWrite(outPin, LOW);


		if(P)
 		{
	 		Serial.println(AWAKETIME);
		    Serial.print("wait - ");
			Serial.print(waitTime);
		    Serial.print("  inhale - ");
			Serial.print(inhaleTime);
			Serial.print("  exhale - ");
			Serial.println(exhaleTime);
 		}
	} 

	tlc_updateFades();
}


void Cocoon::breatheD(int P) //long wT, long wTF, long iT, long eT) 
{	
	unsigned long T1 = millis();
	long subtractor;
	int lockout = 0;
	// static bool flag;

	// If state == waiting and time exceeds wait, then inhale
	if(state == 0)
	{
		long K = AWAKETIME / waitTime;
		subtractor = (long)((waitTime - waitTimeF) / K);
		if(P)
		{
			Serial.println(ISRFlag);
			Serial.print(waitTime);	
			Serial.print(", ");
			Serial.print(subtractor);		
			Serial.print(", ");
			Serial.println(K);	
		}
		Serial.println("m");
		state = 1;
	}
	if((state == 1) && (T1 - T2 >= waitTime)) 
	{
		state = 2; 
		T2 = T1; 
		mcp->digitalWrite(inPin, HIGH);
		tlc_addFade(ledPin, ledMin, ledMax, millis(), millis() + inhaleTime);

		if(ISRFlag)
		{
			if((waitTime - (long)subtractor) > 0)
			{
				waitTime = waitTime - subtractor;
			}
			else
			{
				waitTime = waitTimeF;
				inhaleTime = 2000L;
				exhaleTime = 1000L;
			}	
		}
		tlc_updateFades();
	}
	// If state == inhale and time exceeds inhale, then exhale
	else if ((state == 2) && (T1 - T2 >= inhaleTime)) 
	{
		// Serial.println("S1->S2");
		state = 3; 
		T2 = T1; 
		mcp->digitalWrite(inPin, LOW);
		mcp->digitalWrite(outPin, HIGH);
		tlc_addFade(ledPin, ledMax, ledMin, millis(), millis() + exhaleTime);

		if(ISRFlag)
		{
			if(inhaleTime < 2000L)
			{
				inhaleTime = inhaleTime + 50L;
			}
			else
			{
				inhaleTime = 2000L;
			}
		}
		tlc_updateFades();
	} 
	// If state == exhale and time exceeds exhale, then wait
	else if ((state == 3) && (T1 - T2 >= exhaleTime)) 
	{
		// Serial.println("S2->S0");
		state = 4; 
		T2 = T1; 
		mcp->digitalWrite(outPin, LOW);

		if(ISRFlag)
		{
			if(exhaleTime < 1500L)
			{
				exhaleTime = exhaleTime + 35L;
			}
			else
			{
				exhaleTime = 1500L;
			}		
		}
		if(P)
		{
			Serial.println(TIMERFlag);
			Serial.println(ISRFlag);
			Serial.print(waitTime);	
			Serial.print(", ");
			Serial.println(subtractor);
		}
		tlc_updateFades();
	} 
	else if(state == 4)
	{
		// if(T1 - ISRTime > AWAKETIME)
		// {
			if((!ISRFlag) && (TIMERFlag))
			{
				this->turnOff();
				this->resetCocoonValues();
				state = 0;
			}
			else
			{
				state = 0;
			}
		// }
		// else
		// {
		// 	state = 1;
		// }

		if(P)
		{
			Serial.println(ISRFlag);
			Serial.println(TIMERFlag);
		}
		tlc_updateFades();
	}	
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

void Cocoon::turnOff()
{
	this->mcp->digitalWrite(this->outPin, LOW);
	this->mcp->digitalWrite(this->inPin, LOW);
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


