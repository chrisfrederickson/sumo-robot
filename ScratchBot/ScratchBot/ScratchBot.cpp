/*
 * ScratchBot.cpp
 *
 * Created: 10/27/2014 4:36:24 PM
 *  Author: N
 */ 


#include <avr32/io.h>
#include "utils/MotorDriver.h"
#include "sensors/Button.h"
#include "sensors/ProximitySensor.h"
#include "sensors/IR.h"
#include "sensors/MotionSensor.h"
#include "sensors/SensorsArray.h"
#include "strategies/Strategy.h"
#include "strategies/RandomMovement.h"
#include "strategies/Sniper.h"

#include <chrono>       /* time_t, struct tm, difftime, time, mktime */
using namespace std;
using std::chrono::milliseconds;
int main(void)
{
	
    while(1) {
		int TICK = 10; //MS
        SensorsArray sensors = SensorsArray();
		MotorDriver motors = MotorDriver();
		//Refresh sensor data
		
		int mills = chrono::system_clock::now().time_since_epoch().count();
		//Every tick
		while(mills - sensors.getTick() >= TICK) {
			Sniper sniper = Sniper(sensors, motors);
			sensors.setTick(mills);
			//Go through strategies in most->least priority order
			
			sniper.tapIn();
		}
    }
	return 0;
}