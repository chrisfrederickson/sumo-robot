#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

// How to take this strategy
void pushing_action(sensors_t sens){
//  Serial.println("IMPL!");
  leftSide(100);
  rightSide(100);
  return;
}

// When to take this strategy
void pushing(sensors_t sens,strategy_func* taken_strat){
  if (sens.contact){
    *taken_strat = &pushing_action;
  }else{
  }
}
