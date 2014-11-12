/* 
* SensorsArray.cpp
*
* Created: 11/10/2014 9:01:11 PM
* Author: N
*/

#include "Button.h"
#include "MotionSensor.h"
#include "ProximitySensor.h"
#include "SensorsArray.h"


// default constructor
SensorsArray::SensorsArray()
{
	b = Button();
	m = MotionSensor();
	p = ProximitySensor();
	tick = 0;
}
Button SensorsArray::getButton() {
	return b;
}
int SensorsArray::getTick() {
	return tick;
}
void SensorsArray::setTick(int t) {
	tick = t;
}
int SensorsArray::incTick() {
	return tick++;
};