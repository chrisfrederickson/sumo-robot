#include "types.h"
#include "drivetrain.h"

void notastrategy_action(sensors_t sens){
  leftSide(0);
  rightSide(0);
  return;
}

void notastrategy(sensors_t sens,strategy_func taken_strat){
  taken_strat = &notastrategy_action;
}
