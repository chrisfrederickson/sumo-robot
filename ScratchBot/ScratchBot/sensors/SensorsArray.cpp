/* 
* SensorsArray.cpp
*
* Created: 11/10/2014 9:01:11 PM
* Author: N
*/


#include "SensorsArray.h"

// default constructor
SensorsArray::SensorsArray()
{
	b = Button();
	m = MotionSensor();
	p = ProximitySensor();
	tick = 0;
}
SensorsArray::getButton() {
	return b;
}
SensorsArray::getTick() {
	return tick;
}
SensorsArray::setTick(int t) {
	tick = t;
}
SensorsArray::incTick() {
	return tick++;
};