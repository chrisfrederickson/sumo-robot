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

#define TICK = 10;

using namespace std;
SensorsArray sensors;
MotorDriver motors;

void setup()
{

	  /* add setup code here, setup code runs once when the processor starts */
	  sensors = SensorsArray();
	  motors = MotorDriver();

}

void loop()
{

	  /* add main program code here, this code starts again each time it ends */
	//Refresh sensor data
	sensors.exec();
    int mills = millis();
	//Every tick
	while(mills - sensors.getTick() >= TICK) {
		sensors.setTick(millis());	
	}
	Sniper sniper = Sniper(sensors, motors);
	//Go through strategies in most->least priority order
	if(sniper.shouldRun())
		sniper.activate();
}