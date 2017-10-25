#include "trees.h"
#include "cocoons.h"
#include "spiders.h"
#include "Stepper.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Tlc5940.h"


/*********************************************************/
/******************  CONSTANTS  **************************/

#define BAUD_RATE          9600 

/*********************************************************/
/****************  GLOBAL VARIABLES  *********************/

Tree tree;
Adafruit_MCP23017 mcp0;
Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;


// {inPin, outPin, inDuration, outDuration}
int cocoonValues[12][6] = 
{
  {(int)&mcp0, 0, 1, 0, 500, 1000},     
  {(int)&mcp0, 0, 1, 0, 500, 1000},
  {(int)&mcp0, 0, 1, 0, 500, 1000},
  {(int)&mcp0, 0, 1, 0, 500, 1000},
  {(int)&mcp0, 0, 1, 0, 500, 1000},
  {(int)&mcp0, 0, 1, 0, 500, 1000},
  {(int)&mcp0, 0, 1, 0, 500, 1000},
  {(int)&mcp0, 0, 1, 0, 500, 1000},
  {(int)&mcp0, 0, 1, 0, 500, 1000},
  {(int)&mcp0, 0, 1, 0, 500, 1000},
  {(int)&mcp0, 0, 1, 0, 500, 1000},
  {(int)&mcp0, 0, 1, 0, 500, 1000}
};

// {{spiderN}}
int spiderValues [1][4][4]
{
  // stepperPins, fanPins, ledPin, totalSteps
  {{1, 2, 3, 4},  {5},     {13},  {200}}
};

int triggerPin = 1;


/*********************************************************/
/**************  MAIN  ***********************************/


void setup() 
{
//  Tlc.init();
  if(!systemSetup())
  {
    Serial.println("ERROR: Setup Failed");
  }
}


void loop() 
{
//  Serial.println("Hey!"); 
//  tree->cocoons[0]->breathIn(); 
//  delay(1000);
//  tree->cocoons[0]->breathOut();
//  delay(8000);
//   tree.cocoons[0]->blinkLED();
}


/*********************************************************/
/******************  SETUP HELPERS  **********************/

int systemSetup()
{
  Serial.begin(9600);
  // Initialize MCPs
  mcp0.begin();    
  mcp1.begin(1);  
  mcp2.begin(2);  
  
  // Initialize TLC5940

  Tlc.init();
//  Tlc.clear();
//  Tlc.update();
//  pinMode(13, OUTPUT);
//  pinMode(11, OUTPUT);
//  pinMode(9, OUTPUT);
  // Setup Tree container
  tree = Tree();
  tree.setupTree(cocoonValues, spiderValues); 

  return 1;
}



