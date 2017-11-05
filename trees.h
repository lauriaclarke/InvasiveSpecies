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

#include "Arduino.h"
#include "cocoons.h";
#include "spiders.h"
#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "Tlc5940.h"
#include <MCPStepper.h>
// #include "patternTimes.h"

#define N_COCOONCS		1
#define SPIDER_STEPS    800
#define STEPS_PER_REV   200
#define AWAKETIME       120000UL


class Tree
{
public:
	Cocoon cocoons[12];
	Spider spiders[2];
	int nCocoons;
	int nSpiders;

	int chirpPin;
	int dronePin;
	int chirpState;
	int droneState;
	unsigned long T2;
	Tree();

	void chirp(long interval);
	void drone(long interval);
	void breatheAll();
	void breatheFasterAll();
	void resetAllCocoons();
	void cocoonsOff();
	void setupTree(const int cocoonValues[12][4], const int spiderValues[2][4]); 
	int  setupCocoons(const int  cocoonValues[12][4]);
	int  setupSpiders(const int spiderValues[2][4]);

	int  runSpider(int sound);
	int  runCocoons();

	void testCocoonsAll();
	void testCocoons();
	void testSpiders();
};


#endif /* SRC_TREES_H_ */
