#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include "types.h"
#include "sensors_c.h"
#include "notastrategy.h"
#include "wallavoidance.h"

#define TICK_LENGTH 10 //In milliseconds
#include "strategies.h"
#include "sideImpactStrategy.h"

void setup(){
  Serial.begin(115200);
  unsigned long time;
}



void loop(){
  time = millis()
  strategy_func cur_strategy = (strategy_func)0;
  sensors_t sens;
  // Filled
  notastrategy(sens,&cur_strategy);
  sideimpactstrategy(sens,&cur_strategy);
  wallavoidance(sens,&cur_strategy);

  //Serial.println((int)&notastrategy_action);
  cur_strategy(sens);
  while((millis() - time) < TICK_LENGTH){}
}
