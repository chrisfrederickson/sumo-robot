/* 
* ProximitySensor.h
*
* Created: 11/10/2014 8:47:35 PM
* Author: N
*/


#ifndef __PROXIMITYSENSOR_H__
#define __PROXIMITYSENSOR_H__

class ProximitySensor
{
//variables
public:
protected:
private:

//functions
public:
	ProximitySensor();
	float distanceToObject();
	bool detectObject();
	void exec();
	int distance();
//	ProximitySensor( const ProximitySensor &c );
protected:
private:
	float cm();
	int dist; 

	int _irPin;
	int _model;
	int _avg;
	int _p;
	int _sum;
	int _previousDistance;
	int _tol;

}; //ProximitySensor

#endif //__PROXIMITYSENSOR_H__
