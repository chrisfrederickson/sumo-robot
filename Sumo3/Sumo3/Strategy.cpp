/* 
* Strategy.cpp
*
* Created: 11/10/2014 9:11:36 PM
* Author: N
*/


#include "Strategy.h"

// default constructor
Strategy::Strategy(SensorsArray s, MotorDriver m) {
	sensors = s;
	motors = m;
}
bool Strategy::shouldRun() {
	//Use sensor data to determine if this strategy should run;
	//If so, return true
	return true;
}
void Strategy::activate() {
	//Override this to send commands to the system.
}
void Strategy::tapIn() {
	//Check if this should run, if so, run the thing. This just simplifies the code
	if(this->shouldRun())
		this->activate();
}
