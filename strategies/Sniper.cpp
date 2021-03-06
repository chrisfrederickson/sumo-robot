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
} //Sniper

// default destructor
Sniper::~Sniper()
{
} //~Sniper
bool Strategy::shouldRun() {
	//Use sensor data to determine if this strategy should run;
	//If so, return true
	return true;
}
void Strategy::activate() {
	//Override this to send commands to the system.
	//Turn CCW until you see something
	if(s.getProximitySensor().detectObject()) {
		//Gun it
		m.goForward(100);
	} else {
		m.turnCCW(100);
	}
}
void Strategy::tapIn() {
	//Check if this should run, if so, run the thing. This just simplifies the code
	if(this->shouldRun())
		this->activate();
}
