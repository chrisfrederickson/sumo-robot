/* 
* IR.cpp
*
* Created: 11/10/2014 8:50:49 PM
* Author: N
*/


#include "IR.h"

// default constructor
IR::IR()
{
	THRESHOLD = 1000;
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
	return 0;	
}
int IR::getRightIR() {
	return 0;
}