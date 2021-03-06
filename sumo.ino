#include <Wire.h>
#include "types.h"
#include <ZumoBuzzer.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <LSM303.h>
#include "drivetrain.h"
#include "sensors_c.h"
#include "notastrategy.h"
#include "wallavoidance.h"
#include "randomNumber.h"
#include "linefollow.h"
#include "centersit.h"
#include "sideImpactStrategy.h"
#include "pushing.h"
#include "test_acc.h"
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>


#define TICK_LENGTH 10 //In milliseconds
#define PLAY_MUSIC 1 //bool T (1)/F(0)
#define DONT_MOVE 0 //bool 
#define VOLUME 15
#define PLAYBACK_SPEED 1
#define MELODY_LENGTH 263
unsigned char note[MELODY_LENGTH] = {NOTE_C(5),NOTE_G_SHARP(4),NOTE_B(4),NOTE_F_SHARP(4),NOTE_A(4),NOTE_E(4),NOTE_G(4),NOTE_C(4),NOTE_F(4),NOTE_C(4),NOTE_E(4),NOTE_C(4),NOTE_D_SHARP(4),NOTE_B(4),NOTE_D(4),NOTE_C_SHARP(4),
NOTE_C(4),NOTE_G_SHARP(3),NOTE_B(3),NOTE_F_SHARP(3),NOTE_A_SHARP(3),NOTE_E(3),NOTE_A_SHARP(3),NOTE_D(4),NOTE_G(4),NOTE_C(4),NOTE_G(4),NOTE_D_SHARP(4),NOTE_F_SHARP(4),NOTE_C(4),NOTE_E(4),NOTE_D(4),NOTE_C(5),NOTE_E(4),NOTE_E(4),SILENT_NOTE, SILENT_NOTE, NOTE_E(4),NOTE_E(4),SILENT_NOTE, SILENT_NOTE, 
NOTE_E(4),NOTE_E(4),SILENT_NOTE, SILENT_NOTE, NOTE_E(4),NOTE_E(4),SILENT_NOTE, NOTE_D(2),NOTE_E(4),NOTE_E(4),SILENT_NOTE, NOTE_E(5),NOTE_E(4),NOTE_E(4),NOTE_F(3),SILENT_NOTE, NOTE_E(5),NOTE_E(4),NOTE_E(4),NOTE_G(3),SILENT_NOTE, NOTE_E(5),NOTE_E(4),NOTE_E(4),NOTE_E(4),NOTE_C(3),NOTE_E_FLAT(4),NOTE_B_FLAT(3),
NOTE_E(4),NOTE_E(4),NOTE_G(4),NOTE_C(5),NOTE_E(5),NOTE_C(5),NOTE_G(4),NOTE_F(4),NOTE_E(4),NOTE_E(4),NOTE_G(4),NOTE_C(5),NOTE_E(5),NOTE_C(5),NOTE_G(4),NOTE_F(4),NOTE_E(4),NOTE_E(4),NOTE_G(4),NOTE_C(5),NOTE_E(5),NOTE_C(5),NOTE_G(4),NOTE_F(4),NOTE_E(4),NOTE_E(4),NOTE_G(4),NOTE_C(5),NOTE_E(5),NOTE_C(5),NOTE_G(4),
NOTE_F(4),NOTE_E(4),NOTE_E(4),NOTE_G(4),NOTE_C(5),NOTE_E(5),NOTE_C(5),NOTE_G(4),NOTE_F(4),NOTE_E(4),NOTE_E(4),NOTE_G(4),NOTE_C(5),NOTE_E(5),NOTE_C(5),NOTE_G(4),NOTE_F(4),NOTE_E(4),NOTE_E(4),NOTE_G(4),NOTE_C(5),NOTE_E(5),NOTE_C(5),NOTE_G(4),NOTE_F(4),NOTE_E(4),
NOTE_E(4),SILENT_NOTE, NOTE_A(3),NOTE_E(4),NOTE_D_SHARP(4),NOTE_D(4),NOTE_B(3),NOTE_A_SHARP(3),NOTE_B(3),NOTE_F(3),NOTE_F_SHARP(3),NOTE_F_SHARP(3),NOTE_A(3),NOTE_B(3),NOTE_A(3),NOTE_C(4),NOTE_B(3),NOTE_A(3),NOTE_B(3),NOTE_A(3),NOTE_E(4),NOTE_D_SHARP(4),
NOTE_D(4),NOTE_B(3),NOTE_A_SHARP(3),NOTE_B(3),NOTE_D_SHARP(4),NOTE_E(4),NOTE_B(3),NOTE_D(4),NOTE_F(4),NOTE_D(4),NOTE_E(4),NOTE_E(4),NOTE_E(3),SILENT_NOTE, NOTE_D(3),NOTE_E(4),NOTE_E(4),NOTE_E(3),SILENT_NOTE, NOTE_F(3),NOTE_E(4),NOTE_E(4),NOTE_E(3),SILENT_NOTE, 
NOTE_D(3),NOTE_E(4),NOTE_E(4),NOTE_E(3),NOTE_B(2),NOTE_B(2),NOTE_D(3),NOTE_E(4),NOTE_E(4),NOTE_D(4),NOTE_E(4),NOTE_F(4),NOTE_E(4),NOTE_D(4),NOTE_F(4),NOTE_E(4),NOTE_E(4),NOTE_F_SHARP(4),NOTE_F(4),NOTE_E(4),NOTE_D(4),
NOTE_E(4),NOTE_F(4),NOTE_E(4),NOTE_E(4),NOTE_F(4),NOTE_E(4),NOTE_D_SHARP(4),NOTE_C(4),NOTE_D(4),NOTE_D_SHARP(4),NOTE_E(4),NOTE_E(4),NOTE_B(2),NOTE_D(3),NOTE_E(4),NOTE_F(4),NOTE_F_SHARP(4),NOTE_B(3),NOTE_B(3),NOTE_B(3),NOTE_D(3),NOTE_B(3),NOTE_B(3),NOTE_C(3),NOTE_F(3),
NOTE_F(4),NOTE_F_SHARP(4),NOTE_G(4),NOTE_C(3),NOTE_C(3),NOTE_C(3),SILENT_NOTE, NOTE_C(3),NOTE_F(3),NOTE_E(3),NOTE_D(3),NOTE_F(3),NOTE_E(3),NOTE_F_SHARP(4),NOTE_G(4),NOTE_G_SHARP(4),NOTE_C_SHARP(4),NOTE_C_SHARP(4),NOTE_C_SHARP(4),NOTE_C_SHARP(4),NOTE_C_SHARP(4),SILENT_NOTE, NOTE_C_SHARP(4),
SILENT_NOTE, NOTE_C_SHARP(4),NOTE_C_SHARP(4),SILENT_NOTE, NOTE_E(4),NOTE_F(4),NOTE_F_SHARP(4),NOTE_F_SHARP(3),NOTE_C_SHARP(4),NOTE_D(4),NOTE_G(3),NOTE_B(3),NOTE_E(4),NOTE_A(3),NOTE_F(4),NOTE_C(5),NOTE_B_FLAT(4),NOTE_A(4),NOTE_E(4),
NOTE_A(3),NOTE_C(4)
};
// Measured in MS -- Each line is a measure, keep like this for debugging purposes
unsigned int duration[MELODY_LENGTH] = {83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,
83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,
83,83,83,83,333,83,167,83,333,
83,167,83,333,83,167,83,333,
83,83,167,333,83,83,83,83,333,83,83,83,83,
333,83,83,83,83,167,167,
83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,
83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,
83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,
83,83,83,83,83,83,83,83,83,167,333,
666,666,
666,666,
333,999, /* 13 */
167,167,83,83,83,83,83,167,83,167,167,
666,666,
666,666,
333,999,
333,999, /* 18 */
666,666,
666,666,83,
83,83,83,333,83,83,83,83,333,
83,83,83,83,333,83,83,83,167,83,167,
83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,
83,83,83,83,83,83,83,83,83,83,333,333,
333,167,1079,
83,167,83,83,333,83,83,167,
333,167,996,
167,167,83,83,167,83,83,167,83,83,
333,167,1079, /* 29 */
83,167,83,83,333,83,167,
83,333,333,83,83,83,1332,
1332,
333,999,
333,999,
1332,
1332,
1332,
666,666,666,666,
333,999, /* 39 */
};

unsigned int currentNote;
unsigned int currentDelay;

unsigned long time;

unsigned int currentStrategy = STRATEGY_NORMAL;
int strategyTarget = 10000;
ZumoBuzzer buzz;
Pushbutton mainbutton(ZUMO_BUTTON); // pushbutton on pin 12

void setup(){
  Serial.println("ON");
  Serial.begin(115200);
  startSensors();
  buzz.playNote(NOTE_F(4), 250, VOLUME); 
  mainbutton.waitForButton(); 
  Serial.println("Hello.");
  buzz.playNote(NOTE_F(4), 80, 9); 
  time = millis();
//  Serial.println("HERE!!");
  
  //MUSIC
  currentNote = 0;
  currentDelay = 0;
  while(millis() - time < 5000) {
    float diff = (millis() - time);
    if (diff > 50 && mainbutton.isPressed() && currentStrategy != STRATEGY_PLAN_B){
      currentStrategy = STRATEGY_PLAN_B;
      buzz.playNote(NOTE_F(5),80,9);
      Serial.println("Go to B");
    }
    //    Serial.println(diff);
    if(diff == 1126 || diff == 2250 || diff == 3375) {
       buzz.playNote(NOTE_C(3), 250, VOLUME); 
    } else if(diff == 4500) {
       buzz.playNote(NOTE_C(5), 250, VOLUME);
    }
  }
  Serial.println(currentStrategy);
}
ZumoMotors motorx;
void loop_test_motors() {
    time = millis();
    int waits = 0;
    motorx.setLeftSpeed(400);
    motorx.setRightSpeed(-400);
    while((millis() - time) < TICK_LENGTH){waits++;}
    motorx.setLeftSpeed(0);
    motorx.setRightSpeed(0);
    delay(500);
}
void loop(){
  //Serial.println("HERE!");
  time = millis();
  strategy_func cur_strategy = (strategy_func)0;
  sensors_t sens;
  //Serial.println("BEFORE loopSensors!");
  loopSensors(&sens);
  // Filled
  if(currentStrategy == STRATEGY_NORMAL){
    notastrategy(sens,&cur_strategy);
    //test_acc(sens,&cur_strategy);
    //sideimpactstrategy(sens,&cur_strategy);
    wallavoidance(sens,&cur_strategy);
  } else if(currentStrategy == STRATEGY_PLAN_B){
    // TODO: Fill in something
    Serial.print("STRATEGY PLAN B ");
    Serial.print(sens.count);
    Serial.print(" ");
    Serial.print(strategyTarget);
    Serial.print("  ");
    Serial.print(cur_strategy == &notastrategy_action);
    Serial.println("");
    notastrategy(sens,&cur_strategy);
    linefollow(sens,&cur_strategy);
    if (cur_strategy == &notastrategy_action){
      if(sens.count >= strategyTarget) {
        currentStrategy = STRATEGY_NORMAL;
        Serial.println("HERE!Q$YOEHO:AEJTHJAJHEHAOEJHEH");
      }
    }else{
      strategyTarget = sens.count + 100;
    }
  }
  //centersit(sens,&cur_strategy);
  //pushing(sens,&cur_strategy);
  //Serial.println((int)&notastrategy_action);
  if(DONT_MOVE == 0)
      cur_strategy(sens);
  int waits = 0;
  while((millis() - time) < TICK_LENGTH){waits++;}
  if (waits == 0){
    buzz.playFrequency(1000,20,VOLUME);
  }
  
  //MUSIC
  if (currentNote < MELODY_LENGTH && !buzz.isPlaying() && PLAY_MUSIC == 1) {
      // play note at max volume
      // VOLUME ON A SCALE OF 0-15
      buzz.playNote(note[currentNote], floor(duration[currentNote]*PLAYBACK_SPEED), VOLUME);
      currentNote++;
  } else if(currentNote >= MELODY_LENGTH) {
      currentNote = 0;
  } 
}
