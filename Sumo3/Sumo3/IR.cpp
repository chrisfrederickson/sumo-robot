/* 
* IR.cpp
*
* Created: 11/10/2014 8:50:49 PM
* Author: N
*/


#include "IR.h"
#include "Pinouts.h"
#include <Arduino.h>

// default constructor
IR::IR()
{
	THRESHOLD = 1000;
	ZumoReflectanceSensorArray sensors(IR_LEFT);
	//PINS USED ARE IR_LEFT and IR_RIGHT
	sensors.init();
} 
bool IR::detectLeft() {
	//Detects white on the left
	return getLeftIR()>THRESHOLD;
}
bool IR::detectRight() {
	//Detects white on the right
	return getRightIR()>THRESHOLD;
}
int IR::getLeftIR() {
	unsigned int sensorValues[6];
	sensors.read(sensorValues);
	return 100-sensorValues[0]/20;
	//I know what you're thinking -- what's up with this calibration?
	//Well that's the stuff that we used in the original code, and
	//that seemed to turn out pretty well. Think of this like our
	//good luck charm. <|:-D
}
int IR::getRightIR() {
	unsigned int sensorValues[6];
	sensors.read(sensorValues);
	return 100-sensorValues[5]/20;
}
