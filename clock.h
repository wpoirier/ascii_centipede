//clock.h

#define TARGET_TIME 3300 //intended game loop time (in microseconds)//default value will be 3300 in final engine

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <sys/time.h>

class Clock {

public:
	Clock();
	~Clock();

	struct timeval init_t;  //initial system time at beginning of game loop
	struct timeval final_t; //final system-clock time at end of game loop

	long int running_time; //total running time since game loop began

	int sleep_rate; //amount of time the game engine should sleep at the end of the loop

	long int initialTime(void); //initial time at start of game loop

	long int calcDelta(void); //calculate and return value of delta at end of game loop and return it

};

#endif
