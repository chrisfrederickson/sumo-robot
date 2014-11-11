/* 
* Button.cpp
*
* Created: 11/10/2014 8:44:21 PM
* Author: N
*/


#include "Button.h"
using namespace std;

// default constructor
Button::Button()
{
	pressed = false;
}
bool Button::isPressed() {
	return pressed;
}
void Button::waitForPress() {
	while(!pressed){
		
	}
}