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
	int leftSpeedTarget;
	int rightSpeedTarget;
	int leftSpeed;
	int rightSpeed;

//functions
public:
	MotorDriver();
	void execDrive();
	void genActualSpeed();
	void exec();
	void setLeft(int l);
	void setRight(int r);
	void goForward(int v);
	void goBackward(int v);
	void turnCW(int v);
	void turnCCW(int v);
	int getLeft();
	int getRight();	
	MotorDriver( const MotorDriver &c );
	MotorDriver& operator=( const MotorDriver &c );
protected:
private:

}; //MotorDriver

#endif //__MOTORDRIVER_H__
