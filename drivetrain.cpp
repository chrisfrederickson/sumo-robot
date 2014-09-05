#include <ZumoMotors.h>

ZumoMotors motors;

// Power is from -100 to 100
void leftSide(int power){
  motors.setLeftSpeed(power*4);
}

// Power is from -100 to 100
void rightSide(int power){
  motors.setRightSpeed(power*4);
}
