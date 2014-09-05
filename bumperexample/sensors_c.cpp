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
***/
#define NUM_SENSORS 6
#define QTR_THRESHOLD 1000 // microseconds (This is for determining white from black)

#define CALIBRATION_SAMPLES 70 // Number of compass readings to take when calibrating
#define CRB_REG_M_2_5GAUSS 0x60 // CRB_REG_M value for magnetometer +/-2.5 gauss full scale
#define CRA_REG_M_220HZ 0x1C // CRA_REG_M value for magnetometer 220 Hz update rate

unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
LSM303 compass;

typedef struct sensors_t_ {
  unsigned int ir[6];
  float acc[3];
  float comp[3];
  bool pushbutton;
  float vbat;
  bool contact;
  bool contactLeft;
  bool lineLeft;
  bool lineRight;
  bool slip;
  int angleOfIncidence;
} sensors_t;
// Accelerometer Class -- extends the LSM303 Library to support reading and averaging the x-y acceleration
// vectors from the onboard LSM303DLHC accelerometer/magnetometer
class Accelerometer : public LSM303
{
  typedef struct acc_data_xy
  {
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
  float len_xy() const;
  float dir_xy() const;
  int x_avg(void) const;
  int y_avg(void) const;
  long ss_xy_avg(void) const;
  float dir_xy_avg(void) const;
  private:
  acc_data_xy last;
  RunningAverage<int> ra_x;
  RunningAverage<int> ra_y;
};
Accelerometer lsm303;

void setup() {
   // Initiate LSM303
  lsm303.init();
  lsm303.enable();
  LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32767, -32767, -32767};
  Serial.begin(9600);
   // Initiate LSM303
  compass.init();
  // Enables accelerometer and magnetometer
  compass.enableDefault();
  compass.writeReg(LSM303::CRB_REG_M, CRB_REG_M_2_5GAUSS); // +/- 2.5 gauss sensitivity to hopefully avoid overflow problems
  compass.writeReg(LSM303::CRA_REG_M, CRA_REG_M_220HZ); // 220 Hz compass update rate

  //How much calibration do we really need to do for a useless sensor?
  for(index = 0; index < CALIBRATION_SAMPLES; index ++)
  {
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
void loop() {
  sensors.read(sensor_values);
  loop_start_time = millis();
  lsm303.readAcceleration(loop_start_time); 
  //Raw Data
  sensors_t.ir = sensor_values;
  //TODO Z
  sensors_t.acc = lsm303.getAcceleration();
  //FIXME One int, not 3
  sensors_t.comp = averageHeading();
  sensors_t.pushbutton = button.isPressed();
  //TODO Look up data
  sensors_t.vbat = 0;
  //Parse Data
  sensors_t.contact = sensors_t.acc[0] > 1;
  sensors_t.contactLeft = sensors_t.acc[1] > 1;
  sensors_t.lineLeft = sensor_values[0] < QTR_THRESHOLD;
  sensors_t.lineRight = sensor_values[5] < QTR_THRESHOLD;
  sensors_t.slip = sensors_t.acc[0] > 2;
  //HMM - Just made something up
  sensors_t.angleOfIncidence = sin(sensors_t.acc[0]+sensors_t.acc[1]);
  /*
  typedef struct {
		unsigned int ir[6];
		float acc[3];
		float comp[3];
		bool pushbutton;
		float vbat;
		bool contact;
		bool contactLeft;
		bool lineLeft;
		bool lineRight;
		bool slip;
		int angleOfIncidence;
	} sensors_t;
  */
}

/***
*      ACCELEROMETER  *
*      ACCELERATOR    *
*      ACCELERATION   *
***/
// class Accelerometer -- member function definitions
// enable accelerometer only
// to enable both accelerometer and magnetometer, call enableDefault() instead
void Accelerometer::enable(void)
  {
  // Enable Accelerometer
  // 0x27 = 0b00100111
  // Normal power mode, all axes enabled
  writeAccReg(LSM303::CTRL_REG1_A, 0x27);
  if (getDeviceType() == LSM303::device_DLHC)
  writeAccReg(LSM303::CTRL_REG4_A, 0x08); // DLHC: enable high resolution mode
  }
  void Accelerometer::getLogHeader(void)
  {
  Serial.print("millis x y len dir | len_avg dir_avg | avg_len");
  Serial.println();
  }
  int[3] Accelerometer::getAcceleration(unsigned long timestamp) {
     int foo[] = {last.x, last.y};
     return foo;
  }
  void Accelerometer::readAcceleration(unsigned long timestamp)
  {
  readAcc();
  if (a.x == last.x && a.y == last.y) return;
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
  float Accelerometer::len_xy() const
  {
  return sqrt(last.x*a.x + last.y*a.y);
  }
  float Accelerometer::dir_xy() const
  {
  return atan2(last.x, last.y) * 180.0 / M_PI;
  }
  int Accelerometer::x_avg(void) const
  {
  return ra_x.getAverage();
  }
  int Accelerometer::y_avg(void) const
  {
  return ra_y.getAverage();
  }
  long Accelerometer::ss_xy_avg(void) const
  {
  long x_avg_long = static_cast<long>(x_avg());
  long y_avg_long = static_cast<long>(y_avg());
  return x_avg_long*x_avg_long + y_avg_long*y_avg_long;
  }
  float Accelerometer::dir_xy_avg(void) const
  {
  return atan2(static_cast<float>(x_avg()), static_cast<float>(y_avg())) * 180.0 / M_PI;
  }
  // RunningAverage class
  // based on RunningAverage library for Arduino
  // source: http://playground.arduino.cc/Main/RunningAverage
  // author: Rob.Tillart@gmail.com
  // Released to the public domain
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
  for (int i = 0; i< _size; i++) _ar[i] = zero; // needed to keep addValue simple
  }
  // adds a new value to the data-set
  template <typename T>
  void RunningAverage<T>::addValue(T f)
  {
  _sum -= _ar[_idx];
  _ar[_idx] = f;
  _sum += _ar[_idx];
  _idx++;
  if (_idx == _size) _idx = 0; // faster than %
  if (_cnt < _size) _cnt++;
  }
  // returns the average of the data-set added so far
  template <typename T>
  T RunningAverage<T>::getAverage() const
  {
  if (_cnt == 0) return zero; // NaN ? math.h
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

/***
*                 *
*      COMPASS    *
*                 *
***/
// Converts x and y components of a vector to a heading in degrees.
// This function is used instead of LSM303::heading() because we don't
// want the acceleration of the Zumo to factor spuriously into the
// tilt compensation that LSM303::heading() performs. This calculation
// assumes that the Zumo is always level.
template <typename T> float heading(LSM303::vector<T> v)
{
  float x_scaled = 2.0*(float)(v.x - compass.m_min.x) / ( compass.m_max.x - compass.m_min.x) - 1.0;
  float y_scaled = 2.0*(float)(v.y - compass.m_min.y) / (compass.m_max.y - compass.m_min.y) - 1.0;
  float angle = atan2(y_scaled, x_scaled)*180 / M_PI;
  if (angle < 0)
  angle += 360;
  return angle;
}
// Yields the angle difference in degrees between two headings
float relativeHeading(float heading_from, float heading_to)
{
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
float averageHeading()
{
  LSM303::vector<int32_t> avg = {0, 0, 0};
  for(int i = 0; i < 10; i ++)
  {
  compass.read();
  avg.x += compass.m.x;
  avg.y += compass.m.y;
  }
  avg.x /= 10.0;
  avg.y /= 10.0;
  // avg is the average measure of the magnetic vector.
  return heading(avg);
}


