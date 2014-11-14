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
int MotorDriver::getLeft() {
	return leftSpeed;
}
int MotorDriver::getRight() {
	return rightSpeed;
}