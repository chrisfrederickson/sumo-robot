/* 
* RandomMovement.h
*
* Created: 11/10/2014 9:14:26 PM
* Author: N
*/


#ifndef __RANDOMMOVEMENT_H__
#define __RANDOMMOVEMENT_H__
#include "Strategy.h"

class RandomMovement: public Strategy
{
//functions
public:
	RandomMovement(SensorsArray s, MotorDriver m);
	~RandomMovement();
	RandomMovement( const RandomMovement &c );
	RandomMovement& operator=( const RandomMovement &c );
protected:
private:
	

}; //RandomMovement

#endif //__RANDOMMOVEMENT_H__
