
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
      void exec();
      int getLeftIR();
	int getRightIR();
protected:
private:
	int THRESHOLD;
        int leftIR;
        int rightIR;
}; //IR

#endif //__IR_H__
