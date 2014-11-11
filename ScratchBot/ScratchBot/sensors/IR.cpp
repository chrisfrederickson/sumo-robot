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
IR::detectLeft() {
	//Detects white on the left
	return getLeftIR()>THRESHOLD;
}
IR::detectRight() {
	//Detects white on the right
	return getRightIR()>THRESHOLD;
}
IR::getLeftIR() {
	return 0;	
}
IR::getRightIR() {
	return 0;
}