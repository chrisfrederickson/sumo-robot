#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

#define MAX_TICKS 18
#define DEG_PER_TICK 5
#define NINETY_DEG 16
int tick = -1;

int getRandom(int mi, int ma) {
    tick = tick + 1;
    if(tick == 0) 
        return NINETY_DEG; //First time, return ticks for ninety degrees
    else
        return mi + (random() % (ma - mi));
        //return random(1,MAX_TICKS) * DEG_PER_TICK; //Then, run as a plain RNG in tick units
}
int oneTick() { //Move one tick for debug purposes
    return DEG_PER_TICK;  
}
void moveOneTick(sensors_t sens) {
  leftSide(100);
  rightSide(-100); 
}
void tickDemo(sensors_t sens,strategy_func* taken_strat) {
  *taken_strat = &moveOneTick; 
}
