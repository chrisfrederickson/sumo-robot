#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

#define REVERSE_SPEED_X -100
#define TURN_SPEED_X 35                  
#define TURN_TICS_X 1

//Not really necessary but I am basing it off the wall avoidance code.
int linefollow_stage = 0; //0 idle, 1 turn
int linefollowlineLeft =0;
int linefollow_ticks = 0;

// How to take this strategy
void linefollow_actionTurnRight(sensors_t sens){
  Serial.println("LF right!");
  leftSide(TURN_SPEED_X);
  rightSide(-TURN_SPEED_X);
}

void linefollow_actionTurnLeft(sensors_t sens){
  Serial.println("LF left!");
  leftSide(-TURN_SPEED_X);
  rightSide(TURN_SPEED_X);
}

// When to take this strategy
void linefollow(sensors_t sens,strategy_func* taken_strat){
  linefollow_ticks--;
  //Serial.print("TICKS: ");
  //Serial.println(wallavoidance_ticks);
  switch(linefollow_stage){
    case 0:
      linefollow_ticks = 0;
      if(sens.lineLeft == 1 || sens.lineRight == 1){
        linefollow_stage = 1;
        linefollow_ticks = TURN_TICS_X;
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
