#include <ZumoMotors.h>

ZumoMotors motors;

#define ALPHA 0.82

int oldLeft = 0;
int oldRight = 0;

// Power is from -100 to 100
void leftSide(int power){
  oldLeft = int(ALPHA*oldLeft+(1-ALPHA)*power);
  motors.setLeftSpeed(oldLeft*4);
}

// Power is from -100 to 100
void rightSide(int power){
  oldRight = int(ALPHA*oldRight+(1-ALPHA)*power);
  motors.setRightSpeed(oldRight*4);
}
