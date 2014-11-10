#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

unsigned long int lastSI = 0;

// How to take this strategy
void sideimpactstrategy_action(sensors_t sens){
  Serial.println("SIDE IMPACT!");
  leftSide(100);
  rightSide(100);
  return;
}

// When to take this strategy
void sideimpactstrategy(sensors_t sens,strategy_func* taken_strat){
  if (sens.contactLeft){
    lastSI = millis();
    *taken_strat = &sideimpactstrategy_action;
  }else if (millis()-500 < lastSI){
    *taken_strat = &sideimpactstrategy_action;
  }
}
