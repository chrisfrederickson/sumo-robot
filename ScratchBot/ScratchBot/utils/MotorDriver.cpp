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
MotorDriver::setLeft(int left) {
	leftSpeed = left;
}
MotorDriver::setRight(int right) {
	rightSpeed = right;
}
MotorDriver::getLeft() {
	return leftSpeed;
}
MotorDriver::getRight() {
	return rightSpeed;
}