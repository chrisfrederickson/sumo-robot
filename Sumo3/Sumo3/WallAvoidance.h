/* 
* WallAvoidance.h
*
* Created: 11/20/2014 8:04:02 PM
* Author: N
*/


#ifndef __WALLAVOIDANCE_H__
#define __WALLAVOIDANCE_H__
#include "Strategy.h"

class WallAvoidance: public Strategy
{
//variables
public:
protected:
private:

//functions
public:
	WallAvoidance(SensorsArray s, MotorDriver m);
	WallAvoidance( const WallAvoidance &c );
	bool shouldRun();
	void activate();
	void tapIn();
protected:
private:
	SensorsArray s;
	MotorDriver m;

};

#endif //__WALLAVOIDANCE_H__
