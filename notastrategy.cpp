#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

#define MOTORS_SPEED 100

// How to take this strategy
void notastrategy_action(sensors_t sens){
  //Serial.println("IMPL!");
  leftSide(MOTORS_SPEED);
  rightSide(MOTORS_SPEED);
  return;
}

// When to take this strategy
void notastrategy(sensors_t sens,strategy_func* taken_strat){
  if (true){
    *taken_strat = &notastrategy_action;
  }else{
  }
}
