/*
 * MonotinicTime.h
 *
 *  Created on: 19 Jun 2014
 *      Author: lester.crespo
 */

#ifndef MONOTINICTIME_H_
#define MONOTINICTIME_H_

#include <windows.h>
#include <time.h>
#include <stdio.h>
#include "timeCounter.h"

using MonotonicTime = TimeCounter;

class MonotonicTime1
{
public:
	MonotonicTime1() :
			tickCount(GetTickCount())
	{

	}
	~MonotonicTime1()
	{

	}
	// convert time to ms
	unsigned long toMS() const
	{
		return tickCount;
	}
	// convert time to ns
	unsigned long toNanoSeconds() const
	{
		return tickCount * 1000 * 1000;
	}
	unsigned getH() const
	{
		return (tickCount/ (1000 * 60*60)) % 24;
	}
	unsigned getM() const
	{
		return (tickCount/ (1000 * 60 )) % 60;
	}
	unsigned getS() const
	{
		return (tickCount/ (1000)) % 60;
	}
	unsigned getMs() const
	{
		return tickCount % 1000;
	}
private:
	DWORD tickCount;
};

#endif /* MONOTINICTIME_H_ */
