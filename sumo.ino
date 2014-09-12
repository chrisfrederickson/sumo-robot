#include <Wire.h>
#include "types.h"
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <LSM303.h>
#include "sensors_c.h"
#include "notastrategy.h"
#include "wallavoidance.h"
#include "centersit.h"
#include "sideImpactStrategy.h"
#include "pushing.h"
#include <ZumoMotors.h>

#define TICK_LENGTH 10 //In milliseconds
unsigned long time;

void setup(){
  Serial.begin(115200);
}



void loop(){
  time = millis();
  strategy_func cur_strategy = (strategy_func)0;
  sensors_t sens;
  // Filled
  notastrategy(sens,&cur_strategy);
  sideimpactstrategy(sens,&cur_strategy);
  wallavoidance(sens,&cur_strategy);
  centersit(sens,&cur_strategy);
  pushing(sens,&cur_strategy);

  //Serial.println((int)&notastrategy_action);
  cur_strategy(sens);
  while((millis() - time) < TICK_LENGTH){}
}
