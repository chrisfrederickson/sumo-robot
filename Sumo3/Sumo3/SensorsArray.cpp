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
	//m = MotionSensor();
        i = IR();
	p = ProximitySensor();
	tick = 0;
}
Button SensorsArray::getButton() {
	return b;
}
ProximitySensor SensorsArray::getProximitySensor() {
	return p;
}
IR SensorsArray::getIR() {
  return i;
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
void SensorsArray::exec() {
	//Refresh sensor data for each thing
	b.exec();
	p.exec();
        i.exec();
}
