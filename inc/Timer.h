#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>

class Timer {
public:
	Timer();
	~Timer();
	void Reset();
	double GetElapsed();
private:
	struct timeval t0_;
};

#endif  // TIMER_H_
