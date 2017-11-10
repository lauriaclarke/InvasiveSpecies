#include "Arduino.h"
#include "Reset.h"
#include <avr/wdt.h>

void softwareReset()
{
  wdt_enable(WDTO_15MS);
  while (1)
  {
  }
}