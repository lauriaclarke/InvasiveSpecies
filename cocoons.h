/*
 * cocoons.h
 *
 *  Created on: Aug 12, 2017
 *      Author: lauriaclarke
 */

#ifndef SRC_COCOONS_H_
#define SRC_COCOONS_H_
#include <Wire.h>
#include "Adafruit_MCP23017.h"
// #include "Tlc5940.h"

class Cocoon
{
public:
	int inPin;
	int inDuration;
	int outPin;
	int outDuration;
	int ledPin;
	// Adafruit_MCP23017* mcp;

	Cocoon();
	
	void setCocoonValues(int inPin, int outPin, int ledPin, int inDuration, int outDuration);
	void breathIn(Adafruit_MCP23017* mcp);
	void breathOut(Adafruit_MCP23017* mcp);

};



#endif /* SRC_TREES_H_ */