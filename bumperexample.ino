#include <ZumoBuzzer.h>
#include <ZumoMotors.h> 
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#define LED 13 // this might need to be tuned for different lighting conditions, surfaces, etc. 
#define QTR_THRESHOLD 1000 // microseconds

// these might need to be tuned for different motor types
#define REVERSE_SPEED 200 // 0 is stopped, 400 is full speed
#define TURN_SPEED 200
#define FORWARD_SPEED 400
#define REVERSE_DURATION 100 // ms 
#define TURN_DURATION 300 // ms 

// POKêMON CHAMPION MUSIC 
#define MELODY_LENGTH 95 
unsigned char note[MELODY_LENGTH] = { NOTE_E(5), SILENT_NOTE, NOTE_E(5), SILENT_NOTE, NOTE_E(5), SILENT_NOTE, NOTE_C(5), NOTE_E(5), NOTE_G(5), SILENT_NOTE, NOTE_G(4), SILENT_NOTE, NOTE_C(5), NOTE_G(4), SILENT_NOTE, NOTE_E(4), NOTE_A(4), NOTE_B(4), NOTE_B_FLAT(4), NOTE_A(4), NOTE_G(4), NOTE_E(5), NOTE_G(5), NOTE_A(5), NOTE_F(5), NOTE_G(5), SILENT_NOTE, NOTE_E(5), NOTE_C(5), NOTE_D(5), NOTE_B(4), NOTE_C(5), NOTE_G(4), SILENT_NOTE, NOTE_E(4), NOTE_A(4), NOTE_B(4), NOTE_B_FLAT(4), NOTE_A(4), NOTE_G(4), NOTE_E(5), NOTE_G(5), NOTE_A(5), NOTE_F(5), NOTE_G(5), SILENT_NOTE, NOTE_E(5), NOTE_C(5), NOTE_D(5), NOTE_B(4), SILENT_NOTE, NOTE_G(5), NOTE_F_SHARP(5), NOTE_F(5), NOTE_D_SHARP(5), NOTE_E(5), SILENT_NOTE, NOTE_G_SHARP(4), NOTE_A(4), NOTE_C(5), SILENT_NOTE, NOTE_A(4), NOTE_C(5), NOTE_D(5), SILENT_NOTE, NOTE_G(5), NOTE_F_SHARP(5), NOTE_F(5), NOTE_D_SHARP(5), NOTE_E(5), SILENT_NOTE, NOTE_C(6), SILENT_NOTE, NOTE_C(6), SILENT_NOTE, NOTE_C(6), SILENT_NOTE, NOTE_G(5), NOTE_F_SHARP(5), NOTE_F(5), NOTE_D_SHARP(5), NOTE_E(5), SILENT_NOTE, NOTE_G_SHARP(4), NOTE_A(4), NOTE_C(5), SILENT_NOTE, NOTE_A(4), NOTE_C(5), NOTE_D(5), SILENT_NOTE, NOTE_E_FLAT(5), SILENT_NOTE, NOTE_D(5), NOTE_C(5) }; // Measured in MS
/* This is the Mario Theme song. Using official sheet music, we can convert bpm and ms to note lengths, then reverse the process */

unsigned int duration[MELODY_LENGTH] = { 100, 25, 125, 125, 125, 125, 125, 250, 250, 250, 250, 250, 375, 125, 250, 375, 250, 250, 125, 250, 167, 167, 167, 250, 125, 125, 125, 250, 125, 125, 375, 375, 125, 250, 375, 250, 250, 125, 250, 167, 167, 167, 250, 125, 125, 125, 250, 125, 125, 375, 250, 125, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 125, 125, 250, 125, 125, 125, 250, 125, 125, 200, 50, 100, 25, 500, 250, 125, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 125, 125, 250, 250, 125, 375, 500 };
ZumoBuzzer buzzer; 
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
unsigned int currentNote;
unsigned int currentDelay;
char currentDir; 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
void waitForButtonAndCountDown() { 
  digitalWrite(LED, HIGH); 
  button.waitForButton(); 
  digitalWrite(LED, LOW); // play audible countdown
  for (int i = 0; i < 3; i++) {
    buzzer.playNote(NOTE_G(3), 200, 10+i);
    delay(1000);
  } 
    delay(1000); 
    buzzer.playNote(NOTE_G(4), 500, 15);
    delay(1000);
}

void setup() {
  // uncomment if necessary to correct motor directions
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true); 
  pinMode(LED, HIGH);
  currentNote = 0;
  currentDelay = 0;
  currentDir = 'F';
  waitForButtonAndCountDown();
} 

void loop() { 
  if (button.isPressed()) {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown(); 
  } 
  sensors.read(sensor_values);
  if (currentNote < MELODY_LENGTH && !buzzer.isPlaying()) { 
    // play note at max volume
    // VOLUME ON A SCALE OF 0-15
    buzzer.playNote(note[currentNote], duration[currentNote], 15);
    currentNote++; 
  } else if(currentNote >= MELODY_LENGTH) { 
    currentNote = 0;
  } 
  
  if (sensor_values[0] < QTR_THRESHOLD) { 
    // if leftmost sensor detects line, reverse and turn to the right 
    currentDir = 'R';
    currentDelay = 0; 
  } else if (sensor_values[5] < QTR_THRESHOLD) {
    // if rightmost sensor detects line, reverse and turn to the left
    currentDir = 'L';
    currentDelay = 0; 
  } else {
    // otherwise, go straight 
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    currentDir = 'F';
 } 

  if(currentDir == 'R') {
    if(currentDelay < REVERSE_DURATION) { 
      motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    } else if(currentDelay < REVERSE_DURATION + TURN_DURATION) { 
      motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    } else { 
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      currentDir = 'F'; 
      currentDelay = 0;
    }
    currentDelay++;
    } else if(currentDir == 'L') {
      if(currentDelay < REVERSE_DURATION) { 
        motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
      } else if(currentDelay < REVERSE_DURATION + TURN_DURATION) {
        motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
      } else { 
        motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED); 
        currentDir = 'F'; 
        currentDelay = 0; 
      } currentDelay++; 
    }
}

