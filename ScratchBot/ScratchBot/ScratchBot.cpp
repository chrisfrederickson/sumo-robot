/*
 * ScratchBot.cpp
 *
 * Created: 10/27/2014 4:36:24 PM
 *  Author: N
 */ 


#include <avr32/io.h>

class MotorDriver {
	public:
	MotorDriver() {
		leftSpeed = 0;
		rightSpeed = 0;	
	}
	void setLeft(int left) {
		leftSpeed = left;
	}
	void setRight(int right) {
		rightSpeed = right;
	}
	int getLeft() {
		return leftSpeed;
	}
	int getRight() {
		return rightSpeed;
	}
	private:
	int leftSpeed;
	int rightSpeed;
};
class Button {
	public: 
	Button() {
		pressed = false;
	}
	bool isPressed() {
		return pressed;
	}	
	void waitForPress() {
		while(!pressed){
			
		}
	}
	private:
	bool pressed;
};
class Proximity {
	public:
	int distanceToObject() {
		//Detects closest object, returns distance in meters
		return 0;
	}	
};
class IR {
	public:
	IR() {
		THRESHOLD = 1000;
	}
	bool detectLeft() {
		//Detects white on the left
		return getLeftIR()>THRESHOLD;
	}	
	bool detectRight() {
		//Detects white on the right
		return getRightIR()>THRESHOLD;
	}
	private:
	int THRESHOLD;
	int getLeftIR() {
		return 0;
	}
	int getRightIR() {
		return 0;
	}
};
class MotionSensor {
	public:
	int getAccX() {
		return 0;
	}
	int getAccY() {
		return 0;
	}
	int getAccZ() {
		return 0;
	}
	int getGyroX() {
		return 0;
	}
	int getGyroY() {
		return 0;
	}
	int getGyroZ() {
		return 0;
	}
};
class SensorsArray {
	public:
	SensorsArray() {
		b = Button();
		m = MotionSensor();
		p = Proximity();
		tick = 0;
	}
	Button getButton() {
		return b;
	}
	int getTick() {
		return tick;
	}
	void setTick(int t) {
		tick = t;
	}
	int incTick() {
		return tick++;
	}

	private:
	Button b;	
	MotionSensor m;
	Proximity p;
	int tick;
};
class Strategy() {
	
}
int main(void)
{
    while(1) {
        SensorsArray sensors = SensorsArray();
		MotorDriver motors = MotorDriver();
		return 0;
    }
}