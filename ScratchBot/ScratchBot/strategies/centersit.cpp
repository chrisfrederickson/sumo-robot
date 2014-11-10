#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

#define IR_LOW 60
#define IR_HIGH 80

// How to take this strategy
void centersit_action(sensors_t sens){
  Serial.println("Center Sit!");
  leftSide(0);
  rightSide(0);
  return;
}

// When to take this strategy
void centersit(sensors_t sens,strategy_func* taken_strat){
  if ((sens.ir[0]<IR_HIGH && sens.ir[0]>IR_LOW)||
      (sens.ir[1]<IR_HIGH && sens.ir[1]>IR_LOW)||
      (sens.ir[2]<IR_HIGH && sens.ir[2]>IR_LOW)||
      (sens.ir[3]<IR_HIGH && sens.ir[3]>IR_LOW)||
      (sens.ir[4]<IR_HIGH && sens.ir[4]>IR_LOW)||
      (sens.ir[5]<IR_HIGH && sens.ir[5]>IR_LOW)||
      (sens.ir[6]<IR_HIGH && sens.ir[6]>IR_LOW)){
    *taken_strat = &centersit_action;
  }else{
  }
}
