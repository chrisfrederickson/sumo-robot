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
	ProximitySensor( const ProximitySensor &c );
	ProximitySensor& operator=( const ProximitySensor &c );
protected:
private:
	

}; //ProximitySensor

#endif //__PROXIMITYSENSOR_H__
