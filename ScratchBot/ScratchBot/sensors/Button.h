/* 
* Button.h
*
* Created: 11/10/2014 8:44:22 PM
* Author: N
*/


#ifndef __BUTTON_H__
#define __BUTTON_H__

using namespace std;
class Button
{
//variables
public:
protected:
private:

//functions
public:
	Button();
	bool isPressed();
	void waitForPress();
	Button( const Button &c );
protected:
private:
	bool pressed;
}; //Button

#endif //__BUTTON_H__
