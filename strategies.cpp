#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

// How to take this strategy
void notastrategy_action(sensors_t sens){
//  Serial.println("IMPL!");
  leftSide(100);
  rightSide(100);
  return;
}

// When to take this strategy
void notastrategy(sensors_t sens,strategy_func* taken_strat){
  if (true){
    *taken_strat = &notastrategy_action;
  }else{
  }
}
