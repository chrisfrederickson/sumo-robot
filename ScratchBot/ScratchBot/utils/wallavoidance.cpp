#include "types.h"
#include "drivetrain.h"
#include "randomNumber.h"
#include <Arduino.h>

#define REVERSE_SPEED -100
#define TURN_SPEED 100
#define REVERSE_TICKS 35
#define TURN_TICS_MIN 20
#define TURN_TICS_MAX 30

int wallavoidance_stage = 0; //0 idle, 1 reverse, 2 turn
int wallavoidancelineLeft;
int wallavoidance_ticks = 0;

// How to take this strategy
void wallavoidance_actionReverse(sensors_t sens){
  Serial.println("Wall reverse!");
  leftSide(REVERSE_SPEED);
  rightSide(REVERSE_SPEED);
}

void wallavoidance_actionTurnRight(sensors_t sens){
  Serial.println("Wall right!");
  leftSide(TURN_SPEED);
  rightSide(-TURN_SPEED);
}

void wallavoidance_actionTurnLeft(sensors_t sens){
  Serial.println("Wall left!");
  leftSide(-TURN_SPEED);
  rightSide(TURN_SPEED);
}

// When to take this strategy
void wallavoidance(sensors_t sens,strategy_func* taken_strat){
  wallavoidance_ticks--;
  //Serial.print("TICKS: ");
  //Serial.println(wallavoidance_ticks);
  switch(wallavoidance_stage){
    case 0:
      if(sens.lineLeft == 1 || sens.lineRight == 1){
        wallavoidance_stage = 1;
        wallavoidance_ticks = REVERSE_TICKS;
        wallavoidancelineLeft = sens.lineLeft;
      }else{
        break;
      }
    case 1:
      *taken_strat = &wallavoidance_actionReverse;
      if(wallavoidance_ticks == 0){
        wallavoidance_stage = 2;
        wallavoidance_ticks = getRandom(TURN_TICS_MIN, TURN_TICS_MAX);
      }else{
        break;
      }
    case 2:
      if(wallavoidancelineLeft){
        *taken_strat = &wallavoidance_actionTurnRight;
      }else{
        *taken_strat = &wallavoidance_actionTurnLeft;
      }
      if(wallavoidance_ticks == 0) wallavoidance_stage = 0;
      break;
    default:
      wallavoidance_stage = 0;
      break;
  }
}
