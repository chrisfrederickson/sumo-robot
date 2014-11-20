/* 
* MotorDriver.cpp
*
* Created: 11/10/2014 8:33:30 PM
* Author: N
*/


#include "MotorDriver.h"
using namespace std;

// default constructor
MotorDriver::MotorDriver()
{
	leftSpeed = 0;
	rightSpeed = 0;	
}
void MotorDriver::setLeft(int left) {
	leftSpeed = left;
}
void MotorDriver::setRight(int right) {
	rightSpeed = right;
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