/* 
* Strategy.h
*
* Created: 11/10/2014 9:11:37 PM
* Author: N
*/


#ifndef __STRATEGY_H__
#define __STRATEGY_H__


class Strategy
{
//variables
public:
protected:
private:

//functions
public:
	Strategy(SensorsArray s, MotorDriver m);
	bool shouldRun();
	void activate();
	void tapIn();
protected:
private:
	Strategy( const Strategy &c );
	Strategy& operator=( const Strategy &c );
	SensorsArray sensors;
	MotorDriver motors;

}; //Strategy

#endif //__STRATEGY_H__