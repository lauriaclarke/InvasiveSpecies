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
#include "Tlc5940.h"
// #include <MCPStepper.h>

#define N_COCOONCS	1

class Tree
{
public:
	Cocoon cocoons[12];
	Spider spiders[2];
	int nCocoons;
	int nSpiders;

	int trigger;

	Tree();

	void setupTree(int cocoonValues[12][7], int spiderValues[1][4][4]); 
	int setupCocoons(int cocoonValues[12][7]); 
	int setupSpiders(int spiderValues[1][4][4]);
	int setupTriggers();

	int checkTrigger();
	int runSpider(int sound);
	int runCocoons();
};



#endif /* SRC_TREES_H_ */
