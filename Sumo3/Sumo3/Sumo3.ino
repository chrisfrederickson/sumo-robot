/*
 * Sumo3.ino
 *
 * Created: 11/19/2014 6:04:51 PM
 * Author: N
 */
#include <Arduino.h>
#include <avr32/io.h>
#include <ZumoReflectanceSensorArray.h>
#include <QTRSensors.h>
#include "MotorDriver.h"
#include "SensorsArray.h"
#include "Sniper.h"
#include "WallAvoidance.h"
#include "IR.h"
#include "Button.h"
#include "MotionSensor.h"
#include "ProximitySensor.h"

#define TICK 100

using namespace std;
SensorsArray sensors;
MotorDriver motors;
boolean q;
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

//STRATEGIES
//WallAvoidance wallAvoidance = WallAvoidance(sensors, motors);
//Sniper sniper = Sniper(sensors, motors);
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
  if(sensors.getProximitySensor().cm() > 700) 
    motors.goForward(100);
  else
    motors.turnCW(100);
    
  motors.exec();
}

void loop5() {
	//int mills = millis();
	//Every tick
	//while((sensors.getTick() - mills) < TICK) {
          /*Serial.print(sensors.getTick());
          Serial.print("  ");
          Serial.print(mills);          
          Serial.print("  ");
          Serial.println(sensors.getTick()-mills);*/
          //sensors.setTick(millis());
	//}
        //sensors.exec();
        
        /*if(q == true) {
        digitalWrite(led, LOW); 
        q=false;
        } else if(q==false){
        digitalWrite(led,HIGH);
        q=true;
        }*/
        /*
        if(sensors.getIR().detectLeft())
        digitalWrite(led, HIGH);
        else
        digitalWrite(led, LOW);
	
        //Serial.print("Button Data: ");
        //Serial.println(sensors.getButton().isPressed());
        Serial.print("Proximity Data: ");
        Serial.println(sensors.getProximitySensor().distanceToObject());
        Serial.print("IR Data: ");
        Serial.print(sensors.getIR().getLeftIR());
        Serial.print(" ");
        Serial.println(sensors.getIR().getRightIR());
        Serial.print("Tick: ");
        Serial.println(sensors.getTick());
        
        wallAvoidance.updateSensors(sensors);
      	sniper.updateSensors(sensors);
	//Go through strategies in most->least priority order
        /*if(wallAvoidance.shouldRun())
          wallAvoidance.activate();
	else if(sniper.shouldRun())
          sniper.activate();
        */
        /**/
        motors.goForward(millis()%1000 > 500?100:-100);
	motors.exec();
}
/*
void loop2()
{
	  /* add main program code here, this code starts again each time it ends 
	//Refresh sensor data
	
    int mills = millis();
	//Every tick
	while((sensors.getTick()-mills) < TICK) {
		sensors.setTick(millis());	
	}

	motors.exec();
}
*/
