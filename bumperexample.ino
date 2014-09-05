#include <ZumoBuzzer.h>
#include <ZumoMotors.h> 
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include "types.h"
//#include "drivetrain.cpp"
#include "strategies.h"

void setup(){
  
}

void loop(){
  strategy_func cur_strategy = 0;
  sensors_t sens;
  // Filled
  notastrategy(sens,cur_strategy);
  cur_strategy(sens);
}
