/* 
* IR.h
*
* Created: 11/10/2014 8:50:49 PM
* Author: N
*/


#ifndef __IR_H__
#define __IR_H__


class IR
{
//functions
public:
	IR();
	bool detectLeft();
	bool detectRight();
protected:
private:
	IR( const IR &c );
	IR& operator=( const IR &c );
	int getLeftIR();
	int getRightIR();
	int THRESHOLD;

}; //IR

#endif //__IR_H__
