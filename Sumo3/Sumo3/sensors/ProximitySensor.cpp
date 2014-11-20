/* 
* ProximitySensor.cpp
*
* Created: 11/10/2014 8:47:35 PM
* Author: N
*/


#include "ProximitySensor.h"

// default constructor
ProximitySensor::ProximitySensor()
{
} //ProximitySensor
float ProximitySensor::distanceToObject() {
	//Detects closest object, returns distance in meters
	return 0;
}
bool ProximitySensor::detectObject() {
	return this->distanceToObject() < 3; //Detected an object less than 3 meters away
}

