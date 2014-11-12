/*
 * timeCounter.h
 *
 *  Created on: 25 Jun 2014
 *      Author: lester.crespo
 */

#ifndef TIMECOUNTER_H_
#define TIMECOUNTER_H_

#include "os.h"
#include "exception_base.h"

class TimeCounter
{
	LARGE_INTEGER PerformanceCount;
public:
	static LARGE_INTEGER Frequency;
	static LARGE_INTEGER getFrequence()
	{
		LARGE_INTEGER f;
		if (!QueryPerformanceFrequency(&f))
			throw error_api(ERROR_INFO(), os::getLastApiError());
		return f;
	}
	TimeCounter()
	{
		if (!QueryPerformanceCounter(&PerformanceCount))
			throw error_api(ERROR_INFO(), os::getLastApiError());
	}
	TimeCounter(LONGLONG PerformanceCount)
	{
		this->PerformanceCount.QuadPart = PerformanceCount;
	}
	TimeCounter operator+(const TimeCounter& t) const
	{
		return TimeCounter(t.PerformanceCount.QuadPart + PerformanceCount.QuadPart);
	}
	TimeCounter operator-(const TimeCounter& t) const
	{
		return TimeCounter(PerformanceCount.QuadPart - t.PerformanceCount.QuadPart);
	}
	// convert current time to milliseconds
	unsigned long long toMS() const
	{
		return PerformanceCount.QuadPart * 1000 / Frequency.QuadPart;
	}
	// convert time to ns
	unsigned long long toNanoSeconds() const
	{
		return PerformanceCount.QuadPart * 1000 * 1000 * 1000 / Frequency.QuadPart;
	}
	unsigned getH() const
	{
		return ((PerformanceCount.QuadPart / Frequency.QuadPart) / (60 * 60) % 24);
	}
	unsigned getM() const
	{
		return ((PerformanceCount.QuadPart / Frequency.QuadPart) / (60) % 60);
	}
	unsigned getS() const
	{
		return ((PerformanceCount.QuadPart / Frequency.QuadPart) % 60);
	}
	// extract milliseconds from time
	unsigned long long getMs() const
	{
		return ((PerformanceCount.QuadPart * 1000 / Frequency.QuadPart) % 1000);
	}

};

#endif /* TIMECOUNTER_H_ */
