/* 
* IR.cpp
*
* Created: 11/10/2014 8:50:49 PM
* Author: N
*/

#include "IR.h"
#include <ZumoReflectanceSensorArray.h>
#include <QTRSensors.h>
#include "Pinouts.h"
#include <Arduino.h>

#define ZUMO_SENSOR_ARRAY_DEFAULT_EMITTER_PIN  A4
ZumoReflectanceSensorArray ir;
// default constructor
IR::IR()
{
	THRESHOLD = 1000;
//	//PINS USED ARE IR_LEFT and IR_RIGHT
      byte sensorPins[] = { IR_LEFT, IR_RIGHT };
        ir.init(sensorPins, sizeof(sensorPins), 2000, QTR_NO_EMITTER_PIN);
} 
bool IR::detectLeft() {
	//Detects white on the left
	return leftIR<THRESHOLD;
}
bool IR::detectRight() {
	//Detects white on the right
	return rightIR<THRESHOLD;
}
int IR::getLeftIR() {
	unsigned int sensorValues[2];
	ir.read(sensorValues);
        return sensorValues[0];
	return 100-sensorValues[0]/20;
	//I know what you're thinking -- what's up with this calibration?
	//Well that's the stuff that we used in the original code, and
	//that seemed to turn out pretty well. Think of this like our
	//good luck charm. <|:-D
}
int IR::getRightIR() {
	unsigned int sensorValues[2];
	ir.read(sensorValues);
        return sensorValues[1];
	return 100-sensorValues[1]/20;
}
void IR::exec() {
    leftIR = getLeftIR();
    rightIR = getRightIR();
}  
