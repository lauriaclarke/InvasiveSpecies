#include "trees.h"
#include "cocoons.h"
#include "spiders.h"
#include "Stepper.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"


/*********************************************************/
/******************  CONSTANTS  **************************/

#define BAUD_RATE          9600 

/*********************************************************/
/****************  GLOBAL VARIABLES  *********************/

Tree* tree;
extern Adafruit_MCP23017 mcp;
// Spiders** spiders;
// Cocoons** cocoons;

// {inPin, outPin, inDuration, outDuration}
int cocoonValues[2][5] = 
{
	{0, 1, 11, 500, 1000},			
	{12, 14, 15, 5000, 2000}
};

// {{spiderN}}
int spiderValues [1][4][4]
{
	// stepperPins, fanPins, ledPin, totalSteps
	{{1, 2, 3, 4},  {5},     {13},  {200}}
};

int triggerPins[2] = {19, 20};


/*********************************************************/
/**************  MAIN  ***********************************/


void setup() 
{
	if(!systemSetup())
	{
		Serial.println("ERROR: Setup Failed");
	}
}


void loop() 
{
	Serial.println("Hey!");	
	tree->cocoons[0]->breathIn(3); //, &mcp);
  	delay(1000);
	tree->cocoons[0]->breathOut(3); //, &mcp);
	// tree->spiders[0]->blinkLED(10000, 1000);
	delay(8000);
}


/*********************************************************/
/******************  SETUP HELPERS  **********************/

int systemSetup()
{
	Serial.begin(9600);
    mcp.begin();    

	tree = new Tree(triggerPins);
	tree->setupTree(cocoonValues, spiderValues); //, &mcp);

	return 1;
}


