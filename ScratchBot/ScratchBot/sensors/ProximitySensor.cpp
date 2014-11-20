/* 
* ProximitySensor.cpp
*
* Created: 11/10/2014 8:47:35 PM
* Author: N
*/


#include "ProximitySensor.h"
#include "Pinouts.h"
#include "Arduino.h"
#include <SharpIR.h>

// default constructor
ProximitySensor::ProximitySensor()
{
	pinMode(PROX_OUT, INPUT);
	SharpIR sharp(PROX_OUT,25,93,20150);
} //ProximitySensor
float ProximitySensor::distanceToObject() {
	//Detects closest object, returns distance in cm
	return sharp.distance();
}
bool ProximitySensor::detectObject() {
	return this->distanceToObject() < 100; //Detected an object less than 3 meters away
}

