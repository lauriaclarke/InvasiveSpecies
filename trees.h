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
#include <MCPStepper.h>

#define N_COCOONCS		1
#define SPIDER_STEPS    800
#define STEPS_PER_REV   200
#define AWAKETIME      	120000UL

class Tree
{
public:
	Cocoon cocoons[12];
	Spider spiders[2];
	int nCocoons;
	int nSpiders;

	int chirp;
	int drone;

	Tree();

	void breatheAll();
	void breatheFasterAll();
	void setupTree(const unsigned int cocoonValues[12][8], const unsigned int spiderValues[1][4]); 
	int setupCocoons(const unsigned int  cocoonValues[12][8]); 
	int setupSpiders(const unsigned int spiderValues[1][4]);

	int runSpider(int sound);
	int runCocoons();

	void testCocoons();
	void testSpiders();
};



#endif /* SRC_TREES_H_ */
