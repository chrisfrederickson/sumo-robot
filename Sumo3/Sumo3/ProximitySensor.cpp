/* 
* ProximitySensor.cpp
*
* Created: 11/10/2014 8:47:35 PM
* Author: N
*/


#include "ProximitySensor.h"
#include "Pinouts.h"
#include <Arduino.h>
// default constructor
ProximitySensor::ProximitySensor()
{
//	pinMode(PROX_OUT, INPUT);
	int a = PROX_OUT;
	int b = 25;
	int c = 93;
	int d = 20150;
	_irPin=a;
	_avg=b;
	_tol=c/100;
	_model=d;
	
	analogReference(DEFAULT);
//	SharpIR sharp(a, b, c, d);
} //ProximitySensor
float ProximitySensor::distanceToObject() {
	//Detects closest object, returns distance in centimeters
	return dist;
}
bool ProximitySensor::detectObject() {
	return this->distanceToObject() > 700; //Detected an object less than n centimeters away
}
void ProximitySensor::exec() {
  Serial.print("Detect voltage at ");
  Serial.print(cm());
  Serial.print(" or at distance ");
  Serial.println(distance());
	dist=cm();
}
float ProximitySensor::cm() {
	int raw=analogRead(_irPin);
	float voltFromRaw=map(raw, 0, 1023, 0, 5000);
return voltFromRaw;
	int puntualDistance;	
	if (_model==1080) {
		puntualDistance=27.728*pow(voltFromRaw/1000, -1.2045);
	} else if (_model==20150){
		puntualDistance=61.573*pow(voltFromRaw/1000, -1.1068);	
	}
	return puntualDistance;
}



int ProximitySensor::distance() {
	_p=0;
	_sum=0;
	for (int i=0; i<_avg; i++){
		int foo=cm();
		if (foo>=(_tol*_previousDistance)){
			_previousDistance=foo;
			_sum=_sum+foo;
			_p++;
		}
	}
	int accurateDistance=_sum/_p;
	return accurateDistance;
}
