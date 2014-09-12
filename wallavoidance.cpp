#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

#define REVERSE_SPEED -100
#define TURN_SPEED 20
#define REVERSE_TICKS 100
#define TURN_TICS_MIN 50
#define TURN_TICS_MAX 100

int wallavoidance_stage = 0; //0 idle, 1 reverse, 2 turn
int wallavoidance_contactLeft;
int wallavoidance_ticks = 0;

// How to take this strategy
void wallavoidance_actionReverse(sensors_t sens){
  leftSide(REVERSE_SPEED);
  rightSide(REVERSE_SPEED);
}

void wallavoidance_actionTurnRight(sensors_t sens){
  leftSide(100);
  rightSide(TURN_SPEED);
}

void wallavoidance_actionTurnLeft(sensors_t sens){
  leftSide(TURN_SPEED);
  rightSide(100);
}

// When to take this strategy
void wallavoidance(sensors_t sens,strategy_func* taken_strat){
  wallavoidance_ticks--;
  
  switch(wallavoidance_stage){
    case 0:
      if(sens.contact == 1){
        wallavoidance_stage = 1;
        wallavoidance_ticks = REVERSE_TICKS;
        wallavoidance_contactLeft = sens.contactLeft;
      }else{
        break;
      }
    case 1:
      *taken_strat = &wallavoidance_actionReverse;
      if(wallavoidance_ticks == 0){
        wallavoidance_stage == 2;
        wallavoidance_ticks = random(TURN_TICS_MIN, TURN_TICS_MAX);
      }else{
        break;
      }
    case 2:
      if(wallavoidance_contactLeft){
        *taken_strat = &wallavoidance_actionTurnRight;
      }else{
        *taken_strat = &wallavoidance_actionTurnLeft;
      }
      if(wallavoidance_ticks == 0) wallavoidance_stage == 0;
      break;
    default:
      wallavoidance_stage == 0;
      break;
  }
}
