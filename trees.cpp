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

	this->chirpPin = 5;
	this->dronePin = 6;
	this->chirpState = HIGH;
	this->droneState = HIGH;
	this->T2 = 0;
}


void Tree::setupTree(const byte cocoonValues[12][4], const byte spiderValues[1][4])
{

	if(!this->setupCocoons(cocoonValues))
	{
		Serial.println("ERROR: Cocoon setup");
	}

	if(!this->setupSpiders(spiderValues))
	{
		Serial.println("ERROR: Spider setup");
	}

	pinMode(chirpPin, OUTPUT);
	pinMode(dronePin, OUTPUT);
	digitalWrite(chirpPin, chirpState);
	digitalWrite(dronePin, droneState);
}


// Setup values and pinmode for cocoons
int Tree::setupCocoons(const byte cocoonValues[12][4]) //, const unsigned long cocoonTimes[12][4])
{
	// Set values and for cocoons
	for(int i = 0; i < nCocoons; i++)
	{
		this->cocoons[i].setCocoonValues(cocoonValues[i][0], cocoonValues[i][1], cocoonValues[i][2], cocoonValues[i][3]);	
		// this->cocoons[i].printValues();
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
int Tree::setupSpiders(const byte spiderValues[2][4])
{
	// Set values and for spiders
	for(int i = 0; i < nSpiders; i++)
	{
		this->spiders[i].setSpiderValues(spiderValues[i][0], spiderValues[i][2], spiderValues[i][3]);
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
		}
	}

	Serial.println("Spiders Initialized!");
	return 1;
}

//-------------------------------------------------------------------

void Tree::chirp(long interval)
{
	long onInterval = interval;
	long offInterval = 200L;

	unsigned long T1 = millis();

	if((chirpState == LOW) && (T1 - T2 >= offInterval)) 
	{
		Serial.println("HEY!");
		chirpState = HIGH;
		T2 = T1; 
		digitalWrite(chirpPin, chirpState);
	}
	if((chirpState == HIGH) && (T1 - T2 >= onInterval)) 
	{
		Serial.println("Hi!");
		chirpState = LOW;
		T2 = T1; 
		digitalWrite(chirpPin, chirpState);
	}
}

void Tree::drone(long interval)
{
	long onInterval = interval;
	long offInterval = 200L;

	unsigned long T1 = millis();

	if((droneState == LOW) && (T1 - T2 >= offInterval)) 
	{
		onInterval = onInterval - 100;
		Serial.println("HEY!");
		droneState = HIGH;
		T2 = T1; 
		digitalWrite(dronePin, droneState);
	}
	if((chirpState == HIGH) && (T1 - T2 >= onInterval)) 
	{
		Serial.println("Hi!");
		droneState = LOW;
		T2 = T1; 
		digitalWrite(dronePin, droneState);
	}
}


void Tree::resetAllCocoons()
{
    this->cocoons[0].resetCocoonValues();
    this->cocoons[1].resetCocoonValues();
    this->cocoons[2].resetCocoonValues();
    this->cocoons[3].resetCocoonValues();
    this->cocoons[4].resetCocoonValues();
    this->cocoons[5].resetCocoonValues();
    this->cocoons[6].resetCocoonValues();
    this->cocoons[7].resetCocoonValues();
    this->cocoons[8].resetCocoonValues();
    this->cocoons[9].resetCocoonValues();
    this->cocoons[10].resetCocoonValues();
    this->cocoons[11].resetCocoonValues();
}

void Tree::cocoonsOff()
{
    this->cocoons[0].turnOff();
    this->cocoons[1].turnOff();
    this->cocoons[2].turnOff();
    this->cocoons[3].turnOff();
    this->cocoons[4].turnOff();
    this->cocoons[5].turnOff();
    this->cocoons[6].turnOff();
    this->cocoons[7].turnOff();
    this->cocoons[8].turnOff();
    this->cocoons[9].turnOff();
    this->cocoons[10].turnOff();
    this->cocoons[11].turnOff();
}

void Tree::breatheAll()
{
    this->cocoons[0].breatheD(0);
    this->cocoons[1].breatheD(0);
    this->cocoons[2].breatheD(0);
    this->cocoons[3].breatheD(0);
    this->cocoons[4].breatheD(0);
    this->cocoons[5].breatheD(0);
    this->cocoons[6].breatheD(0);
    this->cocoons[7].breatheD(0);
    this->cocoons[8].breatheD(0);
    this->cocoons[9].breatheD(0);
    this->cocoons[10].breatheD(0);
    this->cocoons[11].breatheD(1);
}

void Tree::breatheFasterAll()
{
    this->cocoons[0].breatheFaster(0);
    this->cocoons[1].breatheFaster(0);
    this->cocoons[2].breatheFaster(0);
    this->cocoons[3].breatheFaster(0);
    this->cocoons[4].breatheFaster(0);
    this->cocoons[5].breatheFaster(0);
    this->cocoons[6].breatheFaster(0);
    this->cocoons[7].breatheFaster(0);
    this->cocoons[8].breatheFaster(0);
    this->cocoons[9].breatheFaster(0);
    this->cocoons[10].breatheFaster(0);
    this->cocoons[11].breatheFaster(1);
}

void Tree::testCocoonsAll()
{
	for(int i = 0; i < nCocoons; i++)
	{
		this->cocoons[i].setCocoonTestValues();
	}

	breatheAll();
}

void Tree::testCocoons()
{
	for(int i = 0; i < nCocoons; i++)
	{
		this->cocoons[i].setCocoonTestValues();
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


