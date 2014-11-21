#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
/*
 * Sumo3.ino
 *
 * Created: 11/19/2014 6:04:51 PM
 * Author: N
 */
#include <Arduino.h>
#include <avr32/io.h>
#include "MotorDriver.h"
#include "SensorsArray.h"
#include "Sniper.h"

#define TICK 100

using namespace std;
SensorsArray sensors;
MotorDriver motors;
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
void setup()
{
	  /* add setup code here, setup code runs once when the processor starts */
	  sensors = SensorsArray();
	  motors = MotorDriver();
          pinMode(led, OUTPUT); 
          Serial.begin(9600);
          Serial.println("Good morning world.");
}
void loop() {
	sensors.exec();
	int mills = millis();
	//Every tick
        digitalWrite(led, HIGH); 
	while((mills - sensors.getTick()) < TICK) {
          Serial.print(mills);
          Serial.print("  ");
          Serial.print(sensors.getTick());
          Serial.print("  ");
          Serial.println(mills-sensors.getTick());
		sensors.setTick(millis());
	}
        digitalWrite(led, LOW); 
	motors.turnCW(100);
        Serial.println(sensors.getButton().isPressed());
        Serial.println(sensors.getProximitySensor().distanceToObject());
        Serial.println(sensors.getTick());
	motors.exec();
}

void loop2()
{

	  /* add main program code here, this code starts again each time it ends */
	//Refresh sensor data
	sensors.exec();
    int mills = millis();
	//Every tick
	while((mills - sensors.getTick()) < TICK) {
		sensors.setTick(millis());	
	}
	Sniper sniper = Sniper(sensors, motors);
	//Go through strategies in most->least priority order
	if(sniper.shouldRun())
		sniper.activate();
	motors.exec();
}
