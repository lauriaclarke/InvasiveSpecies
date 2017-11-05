#include "Arduino.h"
#include "trees.h"
#include "cocoons.h"
#include "spiders.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include <MCPStepper.h>
#include "Tlc5940.h"


Tree::Tree()
{
	this->nCocoons = 12;
	this->nSpiders = 2;

	this->chirp = 5;
	this->drone = 4;
}



void Tree::setupTree(const int cocoonValues[12][4], const int spiderValues[1][4])
{

	if(!this->setupCocoons(cocoonValues))
	{
		Serial.println("ERROR: Cocoon setup");
	}

	if(!this->setupSpiders(spiderValues))
	{
		Serial.println("ERROR: Spider setup");
	}
}


// Setup values and pinmode for cocoons
int Tree::setupCocoons(const int cocoonValues[12][4]) //, const unsigned long cocoonTimes[12][4])
{
	// Set values and for cocoons
	for(int i = 0; i < nCocoons; i++)
	{
		this->cocoons[i].setCocoonValues((Adafruit_MCP23017*)cocoonValues[i][0], cocoonValues[i][1], cocoonValues[i][2], cocoonValues[i][3], 
			cocoonTimes[i][0], cocoonTimes[i][1], cocoonTimes[i][2], cocoonTimes[i][3]);	
	}	

	// Set pinmode for cocoons
	for(int i = 0; i < nCocoons; i++)
	{
		this->cocoons[i].mcp->pinMode(this->cocoons[i].inPin, OUTPUT);
		this->cocoons[i].mcp->pinMode(this->cocoons[i].outPin, OUTPUT);	
		this->cocoons[i].mcp->pullUp(this->cocoons[i].inPin, HIGH);
		this->cocoons[i].mcp->pullUp(this->cocoons[i].outPin, HIGH);	
		this->cocoons[i].mcp->digitalWrite(this->cocoons[i].inPin, LOW);
		this->cocoons[i].mcp->digitalWrite(this->cocoons[i].outPin, LOW);
	}

	Serial.println("Cocoons Initialized!");
	return 1;
}

// Setup values and pinmodes for spiders
int Tree::setupSpiders(const int spiderValues[1][4])
{
	// Set values and for spiders
	for(int i = 0; i < nSpiders; i++)
	{
		this->spiders[i].setSpiderValues((Stepper*)spiderValues[i][0], (Adafruit_MCP23017*)spiderValues[i][1], spiderValues[i][2], spiderValues[i][3]);
	}	

	// Set pinmode for spiders
	for(int i = 0; i < nSpiders; i++)
	{
		// Setup LED pin
		this->spiders[i].mcp->pinMode(this->spiders[i].ledPin, OUTPUT);
		this->spiders[i].mcp->pinMode(this->spiders[i].fanPin, OUTPUT);	


		this->spiders[i].mcp->digitalWrite(this->spiders[i].ledPin, LOW);
		this->spiders[i].mcp->digitalWrite(this->spiders[i].fanPin, LOW);	

		// Setup Stepper
		this->spiders[i].spiderStepper->init();

		// Raise spider
		if(this->spiders[i].stepperState == LOW)
		{
			this->spiders[i].raiseSpider(SPIDER_STEPS, 40);
			this->spiders[i].stepperState = HIGH;
		}
	}

	return 1;
}


//-------------------------------------------------------------------


// void Tree::makeNoise(int noise, int interval)
// {
//   unsigned long T1 = millis();
 
//   if(T1 - T2 >= onInterval)
//   {
//   	ledState = HIGH;
//     T2 = T1; 
//     digitalWrite(ledPin, ledState);
//   }
//   if((ledState == HIGH) && (T1 - T2 >= offInterval)) 
//   {
//   	ledState = LOW;
//     T2 = T1; 
//     digitalWrite(ledPin, ledState);
//   }
// }



void Tree::breatheAll()
{
    this->cocoons[0].breathe();
    this->cocoons[1].breathe();
    this->cocoons[2].breathe();
    this->cocoons[3].breathe();
    this->cocoons[4].breathe();
    this->cocoons[5].breathe();
    this->cocoons[6].breathe();
    this->cocoons[7].breathe();
    this->cocoons[8].breathe();
    this->cocoons[9].breathe();
    this->cocoons[10].breathe();
    this->cocoons[11].breathe();
}

void Tree::breatheFasterAll()
{
    this->cocoons[0].breatheFaster();
    this->cocoons[1].breatheFaster();
    this->cocoons[2].breatheFaster();
    this->cocoons[3].breatheFaster();
    this->cocoons[4].breatheFaster();
    this->cocoons[5].breatheFaster();
    this->cocoons[6].breatheFaster();
    this->cocoons[7].breatheFaster();
    this->cocoons[8].breatheFaster();
    this->cocoons[9].breatheFaster();
    this->cocoons[10].breatheFasterP();
    this->cocoons[11].breatheFaster();
}



void Tree::testCocoons()
{
	for(int i = 0; i < nCocoons; i++)
	{
		// Test Fans
		this->cocoons[i].breathIn();
		delay(100);
		this->cocoons[i].breathOut();

		// Test LED
		this->cocoons[i].LEDOn();
		delay(2000);
		this->cocoons[i].LEDOff();
	}
}

void Tree::testSpiders()
{
	for(int i = 0; i < nSpiders; i++)
	{
		// Set initial time spider turns on
		this->spiders[i].tOn = millis();

		this->spiders[i].spinFans(1000, 1000);
		this->spiders[i].blinkLED(2000, 2000);
		
		if(this->spiders[i].stepperState == 0)
		{
			this->spiders[i].raiseSpider(SPIDER_STEPS, 40);
		}
		else if(this->spiders[i].stepperState == SPIDER_STEPS)
		{
			this->spiders[i].lowerSpider(SPIDER_STEPS, 40);
		}
		else
		{
			this->spiders[i].lowerSpider(STEPS_PER_REV, 40);
		}
	}
}


