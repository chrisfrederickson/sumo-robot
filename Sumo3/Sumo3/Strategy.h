/* 
* Strategy.h
*
* Created: 11/10/2014 9:11:37 PM
* Author: N
*/


#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "MotorDriver.h"
#include "SensorsArray.h"

class Strategy
{
public:
	Strategy(SensorsArray s, MotorDriver m);
	bool shouldRun();
	void activate();
	void tapIn();
        void updateSensors(SensorsArray s);
	Strategy( const Strategy &c );
protected:
private:	
	SensorsArray sensors;
	MotorDriver motors;

}; //Strategy

#endif //__STRATEGY_H__
