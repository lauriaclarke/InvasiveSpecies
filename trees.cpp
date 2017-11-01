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



void Tree::setupTree(int cocoonValues[12][7], int spiderValues[1][4])
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
int Tree::setupCocoons(int cocoonValues[12][7])
{
	// Set values and for cocoons
	for(int i = 0; i < nCocoons; i++)
	{
		this->cocoons[i].setCocoonValues((Adafruit_MCP23017*)cocoonValues[i][0], cocoonValues[i][1], cocoonValues[i][2], cocoonValues[i][3], cocoonValues[i][4], cocoonValues[i][5], cocoonValues[i][6]);	
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
int Tree::setupSpiders(int spiderValues[1][4])
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


void Tree::testCocoons()
{
	for(int i = 0; i < nCocoons)
	{
		// Test Fans
		this->cocoons[i].breathIn();
		delay(3000);
		this->cocoons[i].breathOut();

		// Test LED
		this->cocoons[i].LEDOn();
		delay(2000);
		this->cocoons[i].LEDOff();
	}
}

void Tree::testSpiders()
{
	for(int i = 0; i < nSpiders)
	{
		if(this->spiders[i].stepperState == LOW)
		// Test Fans
		this->cocoons[i].breathIn();
		delay(3000);
		this->cocoons[i].breathOut();

		// Test LED
		this->cocoons[i].LEDOn();
		delay(2000);
		this->cocoons[i].LEDOff();
	}
}


