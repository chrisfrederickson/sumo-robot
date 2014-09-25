#ifndef LINEFOLLOW_H
#define LINEFOLLOW_H
void linefollow_actionTurnRight(sensors_t sens);
void linefollow_actionTurnLeft(sensors_t sens);
void linefollow(sensors_t sens,strategy_func* taken_strat);
#endif
