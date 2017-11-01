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

	// for(int i = 0; i < nCocoons; i++)
	// {
	// 	this->cocoons[i] = new Cocoon();
	// }	


	// for(int i = 0; i < nCocoons; i++)
	// {
	// 	this->spiders[i] = new Spider();
	// }	

	this->trigger = 1;
}



void Tree::setupTree(int cocoonValues[12][7], int spiderValues[1][4])
{

	if(!this->setupCocoons(cocoonValues))
	{
		Serial.println("ERROR: Cocoon setup");
	}

	// if(!this->setupSpiders(spiderValues))
	// {
	// 	Serial.println("ERROR: Spider setup");
	// }

	// if(!this->setupTriggers())
	// {
	// 	Serial.println("ERROR: Trigger setup");
	// }

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
	}

	return 1;
}


//-------------------------------------------------------------------








int runSpider(int sound, int spider)
{
	// Start sounds from speakers and move spiders. 
	// Argument specifies which sound and spider
	//
	// -> Should each speaker play a different sound?
	// 		If so, shoulds designate by spider.
	// 		This may be a good idea anyway so motion
	//	 	of spider can be easily included in method later. 
	// ...already agreed with
}


