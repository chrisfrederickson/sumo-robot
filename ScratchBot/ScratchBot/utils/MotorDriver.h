/* 
* MotorDriver.h
*
* Created: 11/10/2014 8:33:47 PM
* Author: N
*/


#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__


class MotorDriver
{
//variables
public:
protected:
private:

//functions
public:
	MotorDriver();
	void setLeft(int l);
	void setRight(int r);
	int getLeft();
	int getRight();	
	MotorDriver( const MotorDriver &c );
	MotorDriver& operator=( const MotorDriver &c );
protected:
private:
	int leftSpeed;
	int rightSpeed;

}; //MotorDriver

#endif //__MOTORDRIVER_H__
