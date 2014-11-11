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

int main(void)
{
    while(1) {
        SensorsArray sensors = SensorsArray();
		MotorDriver motors = MotorDriver();
		//Grab sensors
		
		//Go through strategies in most->least priority order
		
		return 0;
    }
}