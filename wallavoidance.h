#ifndef WALLAVOIDANCE_H
#define WALLAVOIDANCE_H
void wallavoidance_actionReverse(sensors_t sens);
void wallavoidance_actionTurnRight(sensors_t sens);
void wallavoidance_actionTurnLeft(sensors_t sens);
void wallavoidance(sensors_t sens,strategy_func* taken_strat);
#endif
