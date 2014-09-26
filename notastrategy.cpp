#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

#define MOTORS_SPEED 100

long lastNASCount = 0;
long startNAS = 0;

// How to take this strategy
extern int oldLeft;
void notastrategy_action(sensors_t sens){
  //Serial.println("IMPL!");
  
  // This means this action didn't run last loop 
  if (sens.count-1 > lastNASCount){
    startNAS = sens.count;
    leftSide(MOTORS_SPEED);
    rightSide(MOTORS_SPEED);
  }
  // This means it did
  else if (sens.count-1 == lastNASCount){
    if (sens.count - startNAS > 75){
      leftSide(MOTORS_SPEED);
      rightSide(MOTORS_SPEED);
    }else{
      leftSide(MOTORS_SPEED);
      rightSide(MOTORS_SPEED);
    } 
  }
  lastNASCount = sens.count;
  return;
}

// When to take this strategy
void notastrategy(sensors_t sens,strategy_func* taken_strat){
  if (true){
    *taken_strat = &notastrategy_action;
  }else{
  }
}
