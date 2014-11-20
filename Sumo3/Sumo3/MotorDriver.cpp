/* 
* MotorDriver.cpp
*
* Created: 11/10/2014 8:33:30 PM
* Author: N
*/


#include "MotorDriver.h"
#include "Pinouts.h"
#include <Arduino.h>
#define ACCELERATION_CONST 0.1
using namespace std;

// default constructor
MotorDriver::MotorDriver()
{
	leftSpeedTarget = 0;
	rightSpeedTarget = 0;	
	leftSpeed = 0;
	rightSpeed = 0;
	pinMode(M1IN1, OUTPUT);
	pinMode(M1IN2, OUTPUT);
	pinMode(M2IN1, OUTPUT);
	pinMode(M2IN2, OUTPUT);
	pinMode(M1PWM, OUTPUT);
	pinMode(M2PWM, OUTPUT);
}
void MotorDriver::setLeft(int left) {
	leftSpeedTarget = left;
}
void MotorDriver::setRight(int right) {
	rightSpeedTarget = right;
}
void MotorDriver::goForward(int v) {
	setLeft(v);
	setRight(v);
}
void MotorDriver::goBackward(int v) {
	goForward(-v);
}
//Make a 0-point turn
void MotorDriver::turnCW(int v) {
	setLeft(v);
	setRight(-v);
}
void MotorDriver::turnCCW(int v) {
	turnCW(-v);
}
int MotorDriver::getLeft() {
	return leftSpeed;
}
int MotorDriver::getRight() {
	return rightSpeed;
}
void MotorDriver::execDrive() {
	//Left motor direction control
	if (leftSpeed > 0) {
		digitalWrite(M1IN1, HIGH);
		digitalWrite(M1IN2, LOW);
		} else if (leftSpeed = 0) {
		digitalWrite(M1IN1, LOW);
		digitalWrite(M1IN2, LOW);
		} else {
		digitalWrite(M1IN1, LOW);
		digitalWrite(M1IN2, HIGH);
	}

	//Right motor direction control
	if (rightSpeed > 0) {
		digitalWrite(M2IN1, HIGH);
		digitalWrite(M2IN2, LOW);
		} else if (leftSpeed = 0) {
		digitalWrite(M2IN1, LOW);
		digitalWrite(M2IN2, LOW);
		} else {
		digitalWrite(M2IN1, LOW);
		digitalWrite(M2IN2, HIGH);
	}
	
	//Speed control
	analogWrite(M1PWM, abs(leftSpeed)*2.55);
	analogWrite(M2PWM, abs(leftSpeed)*2.55);
}
void MotorDriver::genActualSpeed() {
	leftSpeed = leftSpeed + int((leftSpeedTarget - leftSpeed) * ACCELERATION_CONST);
	rightSpeed = rightSpeed + int((rightSpeedTarget - rightSpeed) * ACCELERATION_CONST);
}

void MotorDriver::exec() {
	genActualSpeed();
	execDrive();
}
int MotorDriver::getLeftTarget() {
	return leftSpeedTarget;
}
int MotorDriver::getRightTarget() {
	return rightSpeedTarget;
}