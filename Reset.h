#ifndef Reset_h
#define Reset_h

#include "Arduino.h"

// Number of anemometer pulses before resetting system.
// Divide by 20 for total loops around sculpture. 
#define WDT_RESET          10000

void softwareReset();
	
#endif