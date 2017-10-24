/*
 * trees.h
 *
 *  Created on: Aug 12, 2017
 *      Author: lauriaclarke
 *	
 *  MAX
 *	Breath in - 2000, Breath out - 2000
 *  MIN
 *  See code...
 */

#ifndef SRC_TREES_H_
#define SRC_TREES_H_

#include "cocoons.h";
#include "spiders.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"

#define N_COCOONCS	1

class Tree
{
public:
	Cocoon** cocoons;
	Spider** spiders;
	int nCocoons;
	int nSpiders;

	int trigger;

	Tree(int triggerPin);

	void setupTree(int cocoonValues[1][6], int spiderValues[1][4][4]); //, Adafruit_MCP23017* mcp);
	int setupCocoons(int cocoonValues[1][6]); // , Adafruit_MCP23017* mcp);
	int setupSpiders(int spiderValues[1][4][4]);
	int setupTriggers();

	int checkTrigger();
	int runSpider(int sound);
	int runCocoons();
};



#endif /* SRC_TREES_H_ */
