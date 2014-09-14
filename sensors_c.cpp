#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <Pushbutton.h>
#include <LSM303.h>
#include <Wire.h>
#include "types.h"
#include "sensors_c.h"

#include <ZumoBuzzer.h>
#include <Arduino.h>
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
        [ ] Solve all the syntax issues here
        
        https://github.com/pololu/lsm303-arduino 
        
***/
#define NUM_SENSORS 6
#define QTR_THRESHOLD 1000 // microseconds (This is for determining white from black)
#define ACC_THRESHOLD 1 //In odd units -- this is just something that needs plenty of calibration
#define CONTACT_FRONT_THRESHOLD 2800
#define CONTACT_BACK_THRESHOLD 2800
#define CONTACT_SIDE_THRESHOLD 4000
#define SLIP_THRESHOLD 2 //In odd units -- this is the acceleration detection for slippage

#define CALIBRATION_SAMPLES 120 // Number of compass readings to take when calibrating
#define CRB_REG_M_2_5GAUSS 0x60 // CRB_REG_M value for magnetometer +/-2.5 gauss full scale
#define CRA_REG_M_220HZ 0x1C // CRA_REG_M value for magnetometer 220 Hz update rate

#define RA_SIZE 3  // number of readings to include in running average of accelerometer readings
#define M_PI 3.14159

unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
LSM303 compass;
int loop_start_time;
ZumoBuzzer buzzr;

long acc_bias_x,acc_bias_y;

//typedef struct sensors_t {
//  //commented with suggested types instead
//  unsigned int ir[6];
//  //float acc[3];
//  int acc[2];
//  //float comp[3];
//  float comp;
//  int pushbutton; //bool
//  float vbat;
//  int contact; //bool
//  int contactLeft; //bool
//  int lineLeft; //bool
//  int lineRight; //bool
//  int slip; //bool
//  int angleOfIncidence;
//} sensors_t;



// Accelerometer Class -- extends the LSM303 Library to support reading and averaging the x-y acceleration
// vectors from the onboard LSM303DLHC accelerometer/magnetometer
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
    int getXAcceleration();
    int getYAcceleration();
    float len_xy() const;
    float dir_xy() const;
  private:
    acc_data_xy last;
    RunningAverage<int> ra_x;
    RunningAverage<int> ra_y;

};
Accelerometer accelerometer;
void startSensors() {
  Wire.begin();
   // Initiate Accelerometer
  accelerometer.init();
  accelerometer.enable();
//  accelerometer.setTimeout(3);
//  LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32767, -32767, -32767};
   // Initiate LSM303
//  compass.init();
//  // Enables accelerometer and magnetometer
//  compass.enableDefault();
//  compass.writeReg(LSM303::CRB_REG_M, CRB_REG_M_2_5GAUSS); // +/- 2.5 gauss sensitivity to hopefully avoid overflow problems
//  compass.writeReg(LSM303::CRA_REG_M, CRA_REG_M_220HZ); // 220 Hz compass update rate
//  //TODO How much calibration do we really need to do for a useless sensor? Adjust num;
  long accum_x,accum_y;
  accum_x = 0;
  accum_y = 0;
  for(int index = 0; index < CALIBRATION_SAMPLES; index ++) {
    // Take a reading of the magnetic vector and store it in compass.m
    accelerometer.readAcceleration(millis());
    accum_x += accelerometer.getXAcceleration();
    accum_y += accelerometer.getYAcceleration();
    Serial.println(index);
    delay(15);
  }
//  accum_x /= CALIBRATION_SAMPLES;
//  accum_y /= CALIBRATION_SAMPLES;
  acc_bias_x = accum_x / CALIBRATION_SAMPLES;
  acc_bias_y = accum_y / CALIBRATION_SAMPLES;
  Serial.print("Accelerometer data taken from ");
  Serial.print(CALIBRATION_SAMPLES);
  Serial.print(" samples.");
  Serial.println("");
  
  Serial.print("ACCUM-X: ");
  Serial.print(accum_x);
  Serial.print(" ACCUM-Y: ");
  Serial.print(accum_y);
  Serial.println("");
  
  Serial.print("Here are the offsets: AVG-X: ");
  Serial.print(acc_bias_x);
  Serial.print("  AVG-Y: ");
  Serial.print(acc_bias_y);
//  // Set calibrated values to compass.m_max and compass.m_min
//  compass.m_max.x = running_max.x;
//  compass.m_max.y = running_max.y;
//  compass.m_min.x = running_min.x;
//  compass.m_min.y = running_min.y;

} 
void loopSensors(sensors_t* s) {
  loop_start_time = millis();
  sensors.read(sensor_values);
  //Serial.println("hERE!!!");
  accelerometer.readAcceleration(loop_start_time); 
  //Raw Data
  for(int i = 0; i < NUM_SENSORS; i++) {
    s->ir[i] = 100-sensor_values[i]/20;
  }
  //Serial.println("hERE!");
  s->acc[0] = accelerometer.getXAcceleration()-acc_bias_x;
  s->acc[1] = accelerometer.getYAcceleration()-acc_bias_y;
  s->comp = 0;
  //Serial.println("hERE!!");
  s->pushbutton = button.isPressed();
  s->vbat = 0;
  //Parse Data
  s->contact = 0;
  s->contactLeft = 0;
  if(abs(s->acc[0]) > CONTACT_FRONT_THRESHOLD || abs(s->acc[0]) > CONTACT_BACK_THRESHOLD || abs(s->acc[1]) > CONTACT_SIDE_THRESHOLD) {
     //Now we figure out which one is the most significant
    if(abs(s->acc[0]) > abs(s->acc[1])) {
//       s->contact = 1;
       s->contactLeft = 0;
    } else {
       s->contact = 0;
       s->contactLeft = 1; 
    }
  }
  if(s->contact) {
    buzzr.playFrequency(3000,600,15);
  } if(s->contactLeft) {
    buzzr.playFrequency(5000,600,15);
    Serial.print(" ACC-Y: ");
    Serial.print(s->acc[1]);
    Serial.println("");
  }
//    Serial.print("ACC-X: ");
  //  Serial.print(accelerometer.getXAcceleration());
  //  Serial.print(" | ");
//    Serial.print(s->acc[0]);
//    Serial.print(" ACC-Y: ");
  //  Serial.print(accelerometer.getYAcceleration());
  //  Serial.print(" | ");
//    Serial.print(s->acc[1]);
//    Serial.print("  DIR: ");
//    Serial.print(accelerometer.dir_xy());
//    Serial.print(" Front/Back Hit? ");
//    Serial.print(s->contact);
//    Serial.print(" Side Hit? ");
//    Serial.print(s->contactLeft);
//    Serial.println("");

  s->lineLeft = sensor_values[0] < QTR_THRESHOLD;
  s->lineRight = sensor_values[5] < QTR_THRESHOLD;
  s->slip = s->acc[0] > SLIP_THRESHOLD;
  //HMM - Just made something up. In theory some sort of trigonometric expression should correctly find the bot.
  s->angleOfIncidence = accelerometer.dir_xy(); //In radians
}

/***
*      ACCELEROMETER  *
*      ACCELERATOR    *
*      ACCELERATION   *
***/
// class Accelerometer -- member function definitions
// enable accelerometer only
// to enable both accelerometer and magnetometer, call enableDefault() instead
  void Accelerometer::enable(void) {
      // Enable Accelerometer
      // 0x27 = 0b00100111
      // Normal power mode, all axes enabled
      writeAccReg(LSM303::CTRL_REG1_A, 0x27);
      if (getDeviceType() == LSM303::device_DLHC)
          writeAccReg(LSM303::CTRL_REG4_A, 0x08); // DLHC: enable high resolution mode
  }
  void Accelerometer::getLogHeader(void) {
      Serial.print("millis x y len dir | len_avg dir_avg | avg_len");
      Serial.println();
  }
  //Gets the current acceleration of the device, no printing
  int Accelerometer::getXAcceleration() {
    return last.x;
  }
  int Accelerometer::getYAcceleration() {
    return last.y;
  }
  void Accelerometer::readAcceleration(unsigned long timestamp) {
      //Serial.println("HERE!!!");
      readAcc();
      //Serial.println("HERE!!!!");
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
    float Accelerometer::len_xy() const {
        return sqrt(last.x*a.x + last.y*a.y);
    }
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

float heading(LSM303::vector<long int> v) {
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
float averageHeading() {
    LSM303::vector<int32_t> avg = {0, 0, 0};
    for(int i=0; i<10; i++) {
        compass.read();
        avg.x += compass.m.x;
        avg.y += compass.m.y;
    }
    avg.x /= 10.0;
    avg.y /= 10.0;
    // avg is the average measure of the magnetic vector.
    return heading(avg);
}
/***
    RUNNING AVERAGE
***/
template <typename T>
T RunningAverage<T>::zero = static_cast<T>(0);

template <typename T>
RunningAverage<T>::RunningAverage(int n)
{
  _size = n;
  _ar = (T*) malloc(_size * sizeof(T));
  clear();
}

template <typename T>
RunningAverage<T>::~RunningAverage()
{
  free(_ar);
}

// resets all counters
template <typename T>
void RunningAverage<T>::clear() 
{ 
  _cnt = 0;
  _idx = 0;
  _sum = zero;
  for (int i = 0; i< _size; i++) _ar[i] = zero;  // needed to keep addValue simple
}

// adds a new value to the data-set
template <typename T>
void RunningAverage<T>::addValue(T f)
{
  _sum -= _ar[_idx];
  _ar[_idx] = f;
  _sum += _ar[_idx];
  _idx++;
  if (_idx == _size) _idx = 0;  // faster than %
  if (_cnt < _size) _cnt++;
}

// returns the average of the data-set added so far
template <typename T>
T RunningAverage<T>::getAverage() const
{
  if (_cnt == 0) return zero; // NaN ?  math.h
  return _sum / _cnt;
}

// fill the average with a value
// the param number determines how often value is added (weight)
// number should preferably be between 1 and size
template <typename T>
void RunningAverage<T>::fillValue(T value, int number)
{
  clear();
  for (int i = 0; i < number; i++) 
  {
    addValue(value);
  }
}
