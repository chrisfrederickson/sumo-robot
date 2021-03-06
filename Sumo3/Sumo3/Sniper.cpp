/* 
* Sniper.cpp
*
* Created: 11/15/2014 8:04:02 PM
* Author: N
*/


#include "Sniper.h"

// default constructor
Sniper::Sniper(SensorsArray s, MotorDriver m): Strategy(s, m)
{
	this->s = s;
	this->m = m;
} //Sniper
bool Sniper::shouldRun() {
	return this->s.getProximitySensor().detectObject();
}
void Sniper::activate() {
	//Override this to send commands to the system.
	//Turn CCW until you see something
	if(this->s.getProximitySensor().detectObject()) {
		//Gun it
		this->m.goForward(100);
	} else if(this->s.getTick() < 5000) {
		this->m.turnCCW(100);
	}
}
void Sniper::tapIn() {
	//Check if this should run, if so, run the thing. This just simplifies the code
	if(this->shouldRun())
		this->activate();
}
