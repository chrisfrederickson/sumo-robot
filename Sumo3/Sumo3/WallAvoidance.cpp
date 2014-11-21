/* 
* Sniper.cpp
*
* Created: 11/15/2014 8:04:02 PM
* Author: N
*/


#include "WallAvoidance.h"

// default constructor
WallAvoidance::WallAvoidance(SensorsArray s, MotorDriver m): Strategy(s, m)
{
	this->s = s;
	this->m = m;
} //Sniper
bool WallAvoidance::shouldRun() {
	return this->s.getIR().detectLeft() || this->s.getIR().detectRight();
}
void WallAvoidance::activate() {
        m.goBackward(100);
	if(this->s.getIR().detectLeft()) {
            m.turnCW(100);
	} else {
	    m.turnCW(100);
	}
}
void WallAvoidance::tapIn() {
	//Check if this should run, if so, run the thing. This just simplifies the code
	if(shouldRun())
		activate();
}
