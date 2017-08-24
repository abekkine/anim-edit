#include "Timer.h"

Timer::Timer() {
	Reset();
}

Timer::~Timer() {
}

void Timer::Reset() {
	gettimeofday(&t0_, 0);
}

double Timer::GetElapsed() {
	struct timeval t;
	gettimeofday(&t, 0);

	double dtime = (double)(t.tv_sec - t0_.tv_sec);
	dtime += ((double)(t.tv_usec - t0_.tv_usec))/1000000.0;

	return dtime;
}