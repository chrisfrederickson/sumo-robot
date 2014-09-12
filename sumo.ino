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
#include <ZumoBuzzer.h>
#define TICK_LENGTH 10 //In milliseconds
unsigned long time;

void setup(){
  Serial.begin(115200);
  startSensors();
  Serial.println("HERE!!");
}

ZumoBuzzer buzz;

void loop(){
  //Serial.println("HERE!");
  time = millis();
  strategy_func cur_strategy = (strategy_func)0;
  sensors_t sens;
  //Serial.println("BEFORE loopSensors!");
  loopSensors(&sens);
  //Serial.println(sens.ir[0]);
  Serial.print("ACC: ");
  Serial.print(sens.acc[0]);
  Serial.print(" ");
  Serial.println(sens.acc[1]);
  // Filled
  notastrategy(sens,&cur_strategy);
  //sideimpactstrategy(sens,&cur_strategy);
  wallavoidance(sens,&cur_strategy);
  //centersit(sens,&cur_strategy);
  //pushing(sens,&cur_strategy);
  //Serial.println((int)&notastrategy_action);
  cur_strategy(sens);
  int waits = 0;
  while((millis() - time) < TICK_LENGTH){waits++;}
  if (waits == 0){
    buzz.playFrequency(1000,20,15);
  }
}
