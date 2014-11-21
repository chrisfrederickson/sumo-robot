/* 
* MotionSensor.h
*
* Created: 11/10/2014 8:52:48 PM
* Author: N
*/


#ifndef __MOTIONSENSOR_H__
#define __MOTIONSENSOR_H__


class MotionSensor
{
//variables
public:
protected:
private:

//functions
public:
	MotionSensor();
	int getAccX();
	int getAccY();
	int getAccZ();
	int getGyroX();
	int getGyroY();
	int getGyroZ();
	MotionSensor( const MotionSensor &c );
protected:
private:
	

}; //MotionSensor

#endif //__MOTIONSENSOR_H__
