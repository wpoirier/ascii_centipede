//clock.cpp

#include <unistd.h>
#include <sys/time.h>
#include "clock.h"

Clock::Clock() {
}
Clock::~Clock() {
}

//initial time at the beginning of game loop
long int Clock::initialTime(void) {
	gettimeofday(&init_t, NULL); //initial time at loop start
	return init_t.tv_usec;
}

//final time at end of the loop minus inital time
long int Clock::calcDelta(void) {
	gettimeofday(&final_t, NULL); //final time at loop end 
	return final_t.tv_usec - init_t.tv_usec;
}
