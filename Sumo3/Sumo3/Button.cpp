/* 
* Button.cpp
*
* Created: 11/10/2014 8:44:21 PM
* Author: N
*/


#include "Button.h"
#include "Pinouts.h"
#include <Arduino.h>
using namespace std;

// default constructor
Button::Button()
{
	pressed = false;
  pinMode(BUTTON, INPUT);
}
bool Button::isPressed() {
	return pressed;
}
void Button::waitForPress() {
	while(!pressed){
		exec();
	}
}
void Button::exec() {
	//Get pressed state
  if(digitalRead(BUTTON) == HIGH)
    pressed = true;
  else
    pressed = false;
}
/*Button::Button& operator=( const Button &c ) {
	return c;
}*/
