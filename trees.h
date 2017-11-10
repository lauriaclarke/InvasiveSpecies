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
#include "seedvalues.h"
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
	byte nCocoons;
	byte nSpiders;

	byte chirpPin;
	byte dronePin;
	byte chirpState;
	byte droneState;
	unsigned long T2;
	unsigned long sleepTime;
	unsigned long awakeTime;
	long chirpInterval;
	long droneInterval;


	Tree();

	void chirp();
	void drone();
	void stopSounds();
	void breatheAll();
	void breatheFasterAll();
	void resetAllCocoons();
	void cocoonsOff();
	void setupTree(const byte cocoonValues[12][4], const byte spiderValues[2][4]); 
	int  setupCocoons(const byte  cocoonValues[12][4]);
	int  setupSpiders(const byte spiderValues[2][4]);

	int  runSpider(int sound);
	int  runCocoons();

	void testCocoonsAll();
	void testCocoons();
	void testSpiders();
};


#endif /* SRC_TREES_H_ */
