#ifndef TYPES1_H
#define TYPES1_H

typedef struct sensors_t {
  unsigned int ir[6];
  int acc[2];
  float comp;
  int pushbutton;
  float vbat;
  int contact;
  int contactLeft;
  int ignoreContactX;
  int ignoreContactY;
  int lineLeft;
  int lineRight;
  int slip;
  int angleOfIncidence;
  int count;
} sensors_t;

typedef void (*strategy_func)(sensors_t);

#define STRATEGY_NORMAL 0xF00D
#define STRATEGY_PLAN_B 0xBBBB

#endif
