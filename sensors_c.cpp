#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Pushbutton.h>
#include <LSM303.h>
#include <Wire.h>

/***
    Dev Notes:
        -Acceleration seems to read only in X,Y directions. I guess Z 
            could work, I'd have to look further into the header, but
            I don't think that is important
        -From what I've seen, compass does not give three points of data, 
            just a single heading. There are a few other functions that were
            provided by examples and put into an array. But it will not be 
            traditional X, Y, Z points. Currently it's one int- the average heading over ten reads.
        -Can I find those libraries? I don't think I have them.
        -Stuff like `contact` needs calibration. What is "X" and "Y" relative to the front of the bot? 
        
        Tasks to complete
        [ ] Where can I find the specs for the voltage tester?
        [X] For the accel, which direction is "X"? ANS: FRONT
        [X] Is the external LSM library included with the examples? 
        No, it must be downloaded separately
        [X] If not, is this library needed? What's up with LSM303.h and Wire.h
        They must be included
        Wire.h is actually an included Arduino Library
        [ ] Calibrate values
        [X] Angle of Incidence math
        [X] Discover exactly what versino of the accel/magne that is available: LSM303DLHC (http://www.pololu.com/catalog/product/2124)
        [ ] There's probably other stuff to be done
        
        https://github.com/pololu/lsm303-arduino 
        
***/
#define NUM_SENSORS 6
#define QTR_THRESHOLD 1000 // microseconds (This is for determining white from black)
#define ACC_THRESHOLD 1 //In odd units -- this is just something that needs plenty of calibration
#define SLIP_THRESHOLD 2 //In odd units -- this is the acceleration detection for slippage

#define CALIBRATION_SAMPLES 70 // Number of compass readings to take when calibrating
#define CRB_REG_M_2_5GAUSS 0x60 // CRB_REG_M value for magnetometer +/-2.5 gauss full scale
#define CRA_REG_M_220HZ 0x1C // CRA_REG_M value for magnetometer 220 Hz update rate

#define RA_SIZE 3  // number of readings to include in running average of accelerometer readings

//sensors_c.cpp:46: error: 'ZumoReflectanceSensorArray' does not name a type
//sensors_c.cpp:48: error: 'Pushbutton' does not name a type
//sensors_c.cpp:50: error: 'LSM303' does not name a type
//sensors_c.cpp:70: error: expected class-name before '{' token
unsigned int sensor_values[NUM_SENSORS];
//FIXME error: 'ZumoReflectanceSensorArray' does not name a type
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
//FIXME error: 'Pushbutton' does not name a type
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
//FIXME error: 'LSM303' does not name a type
LSM303 compass;
int loop_start_time;

typedef struct sensors_t {
  //commented with suggested types instead
  unsigned int ir[6];
  //float acc[3];
  float acc[2];
  //float comp[3];
  //float comp
  int pushbutton; //bool
  float vbat;
  int contact; //bool
  int contactLeft; //bool
  int lineLeft; //bool
  int lineRight; //bool
  int slip; //bool
  int angleOfIncidence;
} sensors_t;

sensors_t s;

// Accelerometer Class -- extends the LSM303 Library to support reading and averaging the x-y acceleration
// vectors from the onboard LSM303DLHC accelerometer/magnetometer
//sensors_c.cpp: In constructor 'Accelerometer::Accelerometer()':
//sensors_c.cpp:79: error: class 'Accelerometer' does not have any field named 'ra_x'
//sensors_c.cpp:79: error: 'RA_SIZE' was not declared in this scope
//sensors_c.cpp:79: error: class 'Accelerometer' does not have any field named 'ra_y'
template <typename T> 
class RunningAverage
{
  public:
    RunningAverage(void);
    RunningAverage(int);
    ~RunningAverage();
    void clear();
    void addValue(T);
    T getAverage() const;
    void fillValue(T, int);
  protected:
    int _size;
    int _cnt;
    int _idx;
    T _sum;
    T * _ar;
    static T zero;
};

class Accelerometer : public LSM303 {
  typedef struct acc_data_xy {
    unsigned long timestamp;
    int x;
    int y;
    float dir;
  } acc_data_xy;
  
  public:
    Accelerometer() : ra_x(RA_SIZE), ra_y(RA_SIZE) {};
    ~Accelerometer() {};
    void enable(void);
    void getLogHeader(void);
    void readAcceleration(unsigned long timestamp);
    int* getAcceleration();
    float len_xy() const;
    float dir_xy() const;
  private:
    acc_data_xy last;
    RunningAverage<int> ra_x;
    RunningAverage<int> ra_y;  
};
Accelerometer accelerometer;
//sensors_c.cpp: In function 'void startSensors()':
//sensors_c.cpp:93: error: 'Wire' was not declared in this scope
//sensors_c.cpp:95: error: 'class Accelerometer' has no member named 'init'
//sensors_c.cpp:97: error: 'LSM303' has not been declared
//sensors_c.cpp:97: error: 'int16_t' was not declared in this scope
//sensors_c.cpp:97: error: 'running_min' was not declared in this scope
//sensors_c.cpp:97: error: expected primary-expression before '{' token
//sensors_c.cpp:97: error: expected `;' before '{' token
//sensors_c.cpp:97: error: expected primary-expression before ',' token
//sensors_c.cpp:97: error: 'running_max' was not declared in this scope
//sensors_c.cpp:97: error: expected primary-expression before '{' token
//sensors_c.cpp:97: error: expected `;' before '{' token
//sensors_c.cpp:98: error: 'Serial' was not declared in this scope
//sensors_c.cpp:100: error: 'compass' was not declared in this scope
//sensors_c.cpp:103: error: 'LSM303' has not been declared
//sensors_c.cpp:104: error: 'LSM303' has not been declared
//sensors_c.cpp:107: error: 'index' was not declared in this scope
//sensors_c.cpp:110: error: 'min' was not declared in this scope
//sensors_c.cpp:112: error: 'max' was not declared in this scope
//sensors_c.cpp:115: error: 'delay' was not declared in this scope
void startSensors() {
  Wire.begin();
   // Initiate Accelerometer
  accelerometer.init();
  accelerometer.enable();
  LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32767, -32767, -32767};
  Serial.begin(9600);
   // Initiate LSM303
  compass.init();
  // Enables accelerometer and magnetometer
  compass.enableDefault();
  compass.writeReg(LSM303::CRB_REG_M, CRB_REG_M_2_5GAUSS); // +/- 2.5 gauss sensitivity to hopefully avoid overflow problems
  compass.writeReg(LSM303::CRA_REG_M, CRA_REG_M_220HZ); // 220 Hz compass update rate

  //TODO How much calibration do we really need to do for a useless sensor? Adjust num;
  for(int index = 0; index < CALIBRATION_SAMPLES; index ++) {
    // Take a reading of the magnetic vector and store it in compass.m
    compass.read();
    running_min.x = min(running_min.x, compass.m.x);
    running_min.y = min(running_min.y, compass.m.y);
    running_max.x = max(running_max.x, compass.m.x);
    running_max.y = max(running_max.y, compass.m.y);
    Serial.println(index);
    delay(50);
  }
  // Set calibrated values to compass.m_max and compass.m_min
  compass.m_max.x = running_max.x;
  compass.m_max.y = running_max.y;
  compass.m_min.x = running_min.x;
  compass.m_min.y = running_min.y;

} 
//sensors_c.cpp: In function 'void loopSensors()':
//sensors_c.cpp:125: error: 'sensors' was not declared in this scope
//sensors_c.cpp:126: error: 'loop_start_time' was not declared in this scope
//sensors_c.cpp:126: error: 'millis' was not declared in this scope
//sensors_c.cpp:129: error: expected unqualified-id before '.' token
//sensors_c.cpp:131: error: expected unqualified-id before '.' token
//sensors_c.cpp:133: error: expected unqualified-id before '.' token
//sensors_c.cpp:134: error: expected unqualified-id before '.' token
//sensors_c.cpp:136: error: expected unqualified-id before '.' token
//sensors_c.cpp:138: error: expected unqualified-id before '.' token
//sensors_c.cpp:139: error: expected unqualified-id before '.' token
//sensors_c.cpp:140: error: expected unqualified-id before '.' token
//sensors_c.cpp:141: error: expected unqualified-id before '.' token
//sensors_c.cpp:142: error: expected unqualified-id before '.' token
//sensors_c.cpp:144: error: expected unqualified-id before '.' token
void loopSensors() {
  sensors.read(sensor_values);
  loop_start_time = millis();
  accelerometer.readAcceleration(loop_start_time); 
  //Raw Data
  for(int i = 0; i < NUM_SENSORS; i++) {
    s.ir[i] = sensor_values[i];
  }
  //TODO Z or change struct
  s.acc = accelerometer.getAcceleration();
  //FIXME One int, not 3
  s.comp = averageHeading();
  s.pushbutton = button.isPressed();
  //TODO Look up how to do that
  s.vbat = 0;
  //Parse Data
  s.contact = sensors_t.acc[0] > ACC_THRESHOLD;
  s.contactLeft = sensors_t.acc[1] > ACC_THRESHOLD;
  s.lineLeft = sensor_values[0] < QTR_THRESHOLD;
  s.lineRight = sensor_values[5] < QTR_THRESHOLD;
  s.slip = sensors_t.acc[0] > SLIP_THRESHOLD;
  //HMM - Just made something up. In theory some sort of trigonometric expression should correctly find the bot.
  s.angleOfIncidence = accelerometer.dir_xy(); //In radians
}

/***
*      ACCELEROMETER  *
*      ACCELERATOR    *
*      ACCELERATION   *
***/
// class Accelerometer -- member function definitions
// enable accelerometer only
// to enable both accelerometer and magnetometer, call enableDefault() instead
//sensors_c.cpp: In member function 'void Accelerometer::enable()':
//sensors_c.cpp:159: error: 'LSM303' has not been declared
//sensors_c.cpp:159: error: 'writeAccReg' was not declared in this scope
//sensors_c.cpp:160: error: 'getDeviceType' was not declared in this scope
//sensors_c.cpp:160: error: 'LSM303' has not been declared
//sensors_c.cpp:161: error: 'LSM303' has not been declared
  void Accelerometer::enable(void) {
      // Enable Accelerometer
      // 0x27 = 0b00100111
      // Normal power mode, all axes enabled
      writeAccReg(LSM303::CTRL_REG1_A, 0x27);
      if (getDeviceType() == LSM303::device_DLHC)
          writeAccReg(LSM303::CTRL_REG4_A, 0x08); // DLHC: enable high resolution mode
  }
//  sensors_c.cpp: In member function 'void Accelerometer::getLogHeader()':
//sensors_c.cpp:164: error: 'Serial' was not declared in this scope
  void Accelerometer::getLogHeader(void) {
      Serial.print("millis x y len dir | len_avg dir_avg | avg_len");
      Serial.println();
  }
  //Gets the current acceleration of the device, no printing
//  sensors_c.cpp: At global scope:
//sensors_c.cpp:168: error: prototype for 'int* Accelerometer::getAcceleration(long unsigned int)' does not match any in class 'Accelerometer'
//sensors_c.cpp:84: error: candidate is: int* Accelerometer::getAcceleration()
  int* Accelerometer::getAcceleration(unsigned long timestamp) {
       int foo[2] = {last.x, last.y};
       return foo;
  }
//  sensors_c.cpp: In member function 'void Accelerometer::readAcceleration(long unsigned int)':
//sensors_c.cpp:173: error: 'readAcc' was not declared in this scope
//sensors_c.cpp:174: error: 'a' was not declared in this scope
//sensors_c.cpp:176: error: 'a' was not declared in this scope
//sensors_c.cpp:178: error: 'ra_x' was not declared in this scope
//sensors_c.cpp:179: error: 'ra_y' was not declared in this scope
  void Accelerometer::readAcceleration(unsigned long timestamp) {
      readAcc();
      if(a.x == last.x && a.y == last.y) return;
          last.timestamp = timestamp;
          last.x = a.x;
          last.y = a.y;
          ra_x.addValue(last.x);
          ra_y.addValue(last.y);
          #ifdef LOG_SERIAL
            Serial.print(last.timestamp);
            Serial.print(" ");
            Serial.print(last.x);
            Serial.print(" ");
            Serial.print(last.y);
            Serial.print(" ");
            Serial.print(len_xy());
            Serial.print(" ");
            Serial.print(dir_xy());
            Serial.print(" | ");
            Serial.print(sqrt(static_cast<float>(ss_xy_avg())));
            Serial.print(" ");
            Serial.print(dir_xy_avg());
            Serial.println();
          #endif
    }
//    sensors_c.cpp: In member function 'float Accelerometer::len_xy() const':
//sensors_c.cpp:198: error: 'a' was not declared in this scope
//sensors_c.cpp:198: error: 'sqrt' was not declared in this scope
    float Accelerometer::len_xy() const {
        return sqrt(last.x*a.x + last.y*a.y);
    }
    //sensors_c.cpp: In member function 'float Accelerometer::dir_xy() const':
//sensors_c.cpp:201: error: 'atan2' was not declared in this scope
//sensors_c.cpp:201: error: 'M_PI' was not declared in this scope
    float Accelerometer::dir_xy() const {
        return atan2(last.x, last.y) * 180.0 / M_PI;
    }

/***
*                   *
*      COMPASS      *
*                   *
***/
// Converts x and y components of a vector to a heading in degrees.
// This function is used instead of LSM303::heading() because we don't
// want the acceleration of the Zumo to factor spuriously into the
// tilt compensation that LSM303::heading() performs. This calculation
// assumes that the Zumo is always level.

float heading(LSM303::vector<T> v) {
    float x_scaled = 2.0*(float)(v.x - compass.m_min.x) / ( compass.m_max.x - compass.m_min.x) - 1.0;
    float y_scaled = 2.0*(float)(v.y - compass.m_min.y) / (compass.m_max.y - compass.m_min.y) - 1.0;
    float angle = atan2(y_scaled, x_scaled)*180 / M_PI;
    if (angle < 0)
        angle += 360;
    return angle;
}
// Yields the angle difference in degrees between two headings
//sensors_c.cpp: At global scope:
//sensors_c.cpp:214: error: 'LSM303' has not been declared
//sensors_c.cpp:214: error: 'T' was not declared in this scope
//sensors_c.cpp:214: error: 'v' was not declared in this scope
//sensors_c.cpp:214: error: expected ',' or ';' before '{' token
float relativeHeading(float heading_from, float heading_to) {
    float relative_heading = heading_to - heading_from;
    // constrain to -180 to 180 degree range
    if (relative_heading > 180)
        relative_heading -= 360;
    if (relative_heading < -180)
        relative_heading += 360;
    return relative_heading;
}
// Average 10 vectors to get a better measurement and help smooth out
// the motors' magnetic interference.
//sensors_c.cpp: In function 'float averageHeading()':
//sensors_c.cpp:235: error: 'LSM303' has not been declared
//sensors_c.cpp:235: error: 'int32_t' was not declared in this scope
//sensors_c.cpp:235: error: 'avg' was not declared in this scope
//sensors_c.cpp:235: error: expected primary-expression before '{' token
//sensors_c.cpp:235: error: expected `;' before '{' token
float averageHeading() {
    LSM303::vector<int32_t> avg = {0, 0, 0};
    for(int i=0; i<10; i++) {
        //FIXME error: 'compass' was not declared in this scope
        compass.read();
        avg.x += compass.m.x;
        avg.y += compass.m.y;
    }
    avg.x /= 10.0;
    avg.y /= 10.0;
    // avg is the average measure of the magnetic vector.
    //FIXME error: 'heading' cannot be used as a function
    return heading(avg);
}
