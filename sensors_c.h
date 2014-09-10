#ifndef STRATEGIES_H
#define STRATEGIES_H
void startSensors();
void loopSensors();
typedef struct sensors_t_ {
  //commented with suggested types instead
  unsigned int ir[6];
  //float acc[3];
  float acc[2]
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
#endif
