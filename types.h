#ifndef TYPES1_H
#define TYPES1_H

typedef struct sensors_t {
  unsigned int ir[6];
  float acc[3];
  float comp[3];
  int pushbutton;
  float vbat;
  int contact;
  int contactLeft;
  int lineLeft;
  int lineRight;
  int slip;
  int angleOfIncidence;
} sensors_t;

typedef void (*strategy_func)(sensors_t);
#endif