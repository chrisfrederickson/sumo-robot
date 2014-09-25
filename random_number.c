#define MAX_TICKS 18
#define DEG_PER_TICK 5
int tick = -1;

int getRandom() {
    tick = tick + 1;
    if(tick == 0) 
        return 90/DEG_PER_TICK; //First time, return ticks for ninety degrees
    else
        return random(1,MAX_TICKS)*DEG_PER_TICK; //Then, run as a plain RNG in tick units   
}
int oneTick() { //Move one tick for debug purposes
    delay(250);
    return DEG_PER_TICK;  
}
