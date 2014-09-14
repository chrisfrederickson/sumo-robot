#include "types.h"
#include "drivetrain.h"
#include <Arduino.h>

// How to take this strategy
void test_acc_action(sensors_t sens){
  Serial.println("Stuff");
  return;
}

// When to take this strategy
void test_acc(sensors_t sens,strategy_func* taken_strat){
  if (sens.contact == 1 || sens.contactLeft == 1){
    *taken_strat = &test_acc_action;
  }else{
  }
}
