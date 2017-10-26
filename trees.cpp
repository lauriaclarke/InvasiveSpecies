#include "Arduino.h"
#include "trees.h"
#include "cocoons.h"
#include "spiders.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
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



void Tree::setupTree(int cocoonValues[12][7], int spiderValues[1][4][4])
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

// Set trigger pins
int Tree::setupTriggers()
{
	// pinMode(this->trigger, INPUT);

	// return 1;
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
	}

	Serial.println("Cocoons Initialized!");
	return 1;
}

// Setup values and pinmodes for spiders
int Tree::setupSpiders(int spiderValues[1][4][4])
{
	// // Set values and for spiders
	// for(int i = 0; i < nSpiders; i++)
	// {
	// 	this->spiders[i]->setSpiderValues(spiderValues[i][0], spiderValues[i][1], spiderValues[i][2], spiderValues[i][3]);	
	// }	


	// // Set pinmode for spiders
	// for(int i = 0; i < nSpiders; i++)
	// {
	// 	// Setup LED pin
	// 	pinMode(this->spiders[i]->ledPin[0], OUTPUT);
	// 	pinMode(this->spiders[i]->fanPin[0], OUTPUT);	

	// 	// Setup four stepper pins
	// 	for(int j = 0; j < 4; j++)
	// 	{
	// 		pinMode(this->spiders[i]->stepperPins[j], OUTPUT);
	// 	}
	// }

	return 1;
}


//-------------------------------------------------------------------


int Tree::checkTrigger()
{
	if(digitalRead(trigger))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


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


int runCocoons()
{
	// Move the cocoons around.
	// -> Should have arguments for how many and how fast?
	// -> Perhaps groupings would work well?
}