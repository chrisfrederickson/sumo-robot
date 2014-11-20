/* 
* SensorsArray.h
*
* Created: 11/10/2014 9:01:11 PM
* Author: N
*/


#ifndef __SENSORSARRAY_H__
#define __SENSORSARRAY_H__

#include "Button.h"
#include "MotionSensor.h"
#include "ProximitySensor.h"
#include "SensorsArray.h"

class SensorsArray
{
//variables
public:
protected:
private:

//functions
public:
	SensorsArray();
	Button getButton();
	ProximitySensor getProximitySensor();
	int getTick();
	void setTick(int t);
	int incTick();
	void exec();
//	SensorsArray( const SensorsArray &c );
//	SensorsArray& operator=( const SensorsArray &c );
protected:
private:
	Button b;
	MotionSensor m;
	ProximitySensor p;
	int tick;

}; //SensorsArray

#endif //__SENSORSARRAY_H__
