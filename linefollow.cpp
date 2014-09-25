#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

#define REVERSE_SPEED -100
#define TURN_SPEED 100
#define TURN_TICS 10

//Not really necessary but I am basing it off the wall avoidance code.
int linefollow_stage = 0; //0 idle, 1 turn
int linefollowlineLeft;
int linefollow_ticks = 0;

// How to take this strategy
void linefollow_actionTurnRight(sensors_t sens){
  Serial.println("Wall right!");
  leftSide(TURN_SPEED);
  rightSide(-TURN_SPEED);
}

void linefollow_actionTurnLeft(sensors_t sens){
  Serial.println("Wall left!");
  leftSide(-TURN_SPEED);
  rightSide(TURN_SPEED);
}

// When to take this strategy
void linefollow(sensors_t sens,strategy_func* taken_strat){
  linefollow_ticks--;
  //Serial.print("TICKS: ");
  //Serial.println(wallavoidance_ticks);
  switch(linefollow_stage){
    case 0:
      if(sens.lineLeft == 1 || sens.lineRight == 1){
        linefollow_stage = 1;
        linefollow_ticks = TURN_TICS;
        linefollowlineLeft = sens.lineLeft;
      }else{
        break;
      }
    case 1:
      if(linefollowlineLeft){
        *taken_strat = &linefollow_actionTurnRight;
      }else{
        *taken_strat = &linefollow_actionTurnLeft;
      }
      if(linefollow_ticks == 0) linefollow_stage = 0;
      break;
    default:
      linefollow_stage = 0;
      break;
  }
}
