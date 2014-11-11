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
	int distanceToObject();
	bool detectObject();
protected:
private:
	ProximitySensor( const ProximitySensor &c );
	ProximitySensor& operator=( const ProximitySensor &c );

}; //ProximitySensor

#endif //__PROXIMITYSENSOR_H__
