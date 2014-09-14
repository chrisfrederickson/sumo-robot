#include <Wire.h>
#include "types.h"
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <LSM303.h>
#include "sensors_c.h"
#include "notastrategy.h"
#include "wallavoidance.h"
#include "centersit.h"
#include "sideImpactStrategy.h"
#include "pushing.h"
#include "test_acc.h"
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>

#define TICK_LENGTH 10 //In milliseconds
#define PLAY_MUSIC 1 //bool T (1)/F(0)
#define DONT_MOVE 1 //bool 
#define MELODY_LENGTH 7
unsigned char note[MELODY_LENGTH] = {NOTE_C(3),NOTE_C(3),NOTE_G(3),NOTE_G(3),
NOTE_A(3),NOTE_A(3),NOTE_G(3)};

// Measured in MS
unsigned int duration[MELODY_LENGTH] ={750,750,750,750,
750,750,1500
};

unsigned int currentNote;
unsigned int currentDelay;

unsigned long time;

ZumoBuzzer buzz;
Pushbutton mainbutton(ZUMO_BUTTON); // pushbutton on pin 12

void setup(){
  buzz.playNote(NOTE_F(4), 250, 15); 
  mainbutton.waitForButton(); 
  buzz.playNote(NOTE_F(4), 50, 9); 
//  buzz.playNote(NOTE_F(4), 250, 15);
//  for (int i = 0; i < ENC_MELODY_LENGTH; i++) {
//    buzz.playNote(enc_note[currentNote], enc_duration[currentNote], 15);
//  } 
  time = millis();
  Serial.begin(115200);
  startSensors();
  Serial.println("HERE!!");
  
  //MUSIC
  currentNote = 0;
  currentDelay = 0;
  while(millis() - time < 5000) {
    float diff = (millis() - time);
    Serial.println(diff);
    if(diff == 1126 || diff == 2250 || diff == 3375) {
       buzz.playNote(NOTE_C(3), 250, 15); 
    } else if(diff == 4500) {
       buzz.playNote(NOTE_C(5), 250, 15);  
    }
  }
}
void loop(){
  //Serial.println("HERE!");
  time = millis();
  strategy_func cur_strategy = (strategy_func)0;
  sensors_t sens;
  //Serial.println("BEFORE loopSensors!");
  loopSensors(&sens);
  // Filled
  notastrategy(sens,&cur_strategy);
  //test_acc(sens,&cur_strategy);
  //sideimpactstrategy(sens,&cur_strategy);
  wallavoidance(sens,&cur_strategy);
  
  //centersit(sens,&cur_strategy);
  //pushing(sens,&cur_strategy);
  //Serial.println((int)&notastrategy_action);
  if(DONT_MOVE == 0)
      cur_strategy(sens);
  int waits = 0;
  while((millis() - time) < TICK_LENGTH){waits++;}
  if (waits == 0){
    buzz.playFrequency(1000,20,15);
  }
  
  //MUSIC
  if (currentNote < MELODY_LENGTH && !buzz.isPlaying() && PLAY_MUSIC == 1) {
      // play note at max volume
      // VOLUME ON A SCALE OF 0-15
      buzz.playNote(note[currentNote], duration[currentNote], 15);
      currentNote++;
  } else if(currentNote >= MELODY_LENGTH) {
      currentNote = 0;
  } 
}
