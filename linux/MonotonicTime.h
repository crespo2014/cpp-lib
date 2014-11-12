/*
 * MonotonicTime.h
 *
 *  Created on: 6 May 2014
 *      Author: lester
 */

#ifndef MONOTONICTIME_H_
#define MONOTONICTIME_H_

#include <time.h>

class MonotonicTime
{
	struct timespec ts;
public:
	MonotonicTime(const struct timespec& ts) :
			ts(ts)
	{

	}
	MonotonicTime()
	{
		clock_gettime(CLOCK_MONOTONIC, &ts);
	}
	const struct timespec& get() const
	{
		return ts;
	}
	void addMilliseconds(uint32_t ms)
	{

	}
	MonotonicTime operator -(const MonotonicTime& m)
	{
		struct timespec t;
		t.tv_sec = ts.tv_sec - m.ts.tv_sec;
		if (ts.tv_nsec < m.ts.tv_nsec)
		{
			t.tv_nsec = 1000000000 - m.ts.tv_nsec + ts.tv_nsec;
			t.tv_sec--;
		}
		else
			t.tv_nsec = ts.tv_nsec - m.ts.tv_nsec;

		return t;
	}
	unsigned getH() const
	{
		return ts.tv_sec / 3600;
	}
	unsigned getM() const
	{
		return (ts.tv_sec / 60) % 60;
	}
	unsigned getS() const
	{
		return (ts.tv_sec % 60);
	}
	unsigned getMs() const
	{
		return ts.tv_nsec / 1000000;
	}
	unsigned long toMS() const
	{
		return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
	}

	unsigned long toNanoSeconds() const
	{
		return (ts.tv_sec * 1000*1000*1000 + ts.tv_nsec );
	}
};

#endif /* MONOTONICTIME_H_ */
