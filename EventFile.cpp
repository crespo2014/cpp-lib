/*
 * EventFile.cpp
 *
 *  Created on: 5 Sep 2013
 *      Author: lester
 */

#ifndef _WIN32

#include "EventFile.h"
#include <sys/eventfd.h>
#include <unistd.h>
#include "poll.h"
#include "errno.h"
#include "log.h"

EventFile::EventFile()
{
	fd = -1;

}

EventFile::~EventFile()
{
	release();
}

void EventFile::release()
{
	if (fd != -1)
	{
		close(fd);
		fd = -1;
	}

}

void EventFile::init()
{
	if (fd == -1)
	{
		// create a simple event file, read will put value to zero
		fd = eventfd(0, EFD_NONBLOCK);
		if (fd == -1)
		{
			throw uexception::error_api(ERROR_INFO());
		}
	}
}

void EventFile::set()
{
	uint64_t u = 1;


	if (write(fd, &u, sizeof(u)) == -1)
	{
		// blocking operation will be considerate as already reset event
		if (errno != EAGAIN)
		{
			throw uexception::error_api(ERROR_INFO());
		}
	}
}

/*
 Read data from event to reset status.
 if operation would block
 */
void EventFile::reset()
{

	unsigned char ui64[8];
	if (read(fd, &ui64, sizeof(ui64)) == -1)
	{
		// blocking operation will be considerate as already reset event
		if (errno != EAGAIN)
		{
			throw uexception::error_api(ERROR_INFO());
		}
	}
}

/*
 wait for data available for read on file
 or a numbers of milliseconds pass
 */
bool EventFile::waitRead(int mstimeout)
{
	struct pollfd pfd[1];
	pfd[0].fd = fd;
	pfd[0].events = POLLIN | POLLPRI;
	if (poll(pfd, 1, mstimeout) < 0)
	{
		throw uexception::error_api(ERROR_INFO());
	}
	if (!pfd[0].revents) return false;
	return true;

}

#endif
