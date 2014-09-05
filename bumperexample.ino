#include <ZumoBuzzer.h>
#include <ZumoMotors.h> 
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include "types.h"
//#include "drivetrain.cpp"
#include "strategies.h"

void setup(){
  Serial.begin(115200);
}

void loop(){
  strategy_func cur_strategy = (strategy_func)0;
  sensors_t sens;
  // Filled
  notastrategy(sens,&cur_strategy);
  //Serial.println((int)&notastrategy_action);
  cur_strategy(sens);
}
