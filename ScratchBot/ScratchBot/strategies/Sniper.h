/* 
* Sniper.h
*
* Created: 11/15/2014 8:04:02 PM
* Author: N
*/


#ifndef __SNIPER_H__
#define __SNIPER_H__
#include "Strategy.h"

class Sniper
{
//variables
public:
protected:
private:

//functions
public:
	Sniper(SensorsArray s, MotorDriver m);
	~Sniper();
	Sniper( const Sniper &c );
	Sniper& operator=( const Sniper &c );
	bool shouldRun();
	void activate();
	void tapIn();
protected:
private:
	

}; //Sniper

#endif //__SNIPER_H__
