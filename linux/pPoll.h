/*
 * pPoll.h
 *
 *  Created on: 20 Jun 2014
 *      Author: lester.crespo
 */

#ifndef PPOLL_H_
#define PPOLL_H_

#include <list>
#include <algorithm>
#include <vector>
#include <time.h>

#include "iobase.h"
#include "log.h"

namespace io
{

/*!
 * This is a pool class using a base I/O object
 */
class pPoll
{
	int count;
	//! device list to poll
	std::list<io::io_sock*> devList;
	//! list of handles
	std::vector<struct pollfd> devHandle;
	//! true if a device list has been change, it means devices handles need to be update before poll
	bool onChange;

public:
	Poll() :
			count(0)
	{
		onChange = true;
	}
	~Poll()
	{

	}
	void setChanged()
	{
		onChange = true;
	}
	void add(io_sock& obj)
	{
		return add(&obj);
	}

	//! Add a new device to poll
	void add(io_sock* obj)
	{
		log_d("added %X", obj);
		// do nothing if device exits
		auto it = std::find(devList.begin(), devList.end(), obj);
		// return if was found
		if (it == devList.end())
		{
			devList.push_back(obj);
		}
		else
			CHECK_TRACE(false);
		onChange = true;
		count++;
	}
	//! remove a device from poll list
	unsigned short remove(io_sock* obj)
	{
		// do nothing if device exits
		auto it = std::find(devList.begin(), devList.end(), obj);
		// return if element it was not found
		CHECK_RET(it != devList.end());
		(*it) = 0;
		onChange = true;
		count--;
		return NO_ERR;
	}
	// file descriptor has been change for this io device create a new one at the end of list
	void reset(io_sock* obj)
	{
		auto it = std::find(devList.begin(), devList.end(), obj);
		CHECK_RET_VOID(it != devList.end());
		(*it) = 0;
		devList.push_back(obj);
		onChange = true;
	}
	//! Poll all object in device list
	unsigned short pollDevices()
	{
		if (onChange)
		{
			devHandle.resize(count);
			onChange = false;
			// remove not pointers elements
			for (auto it = devList.begin(); it != devList.end();)
			{
				// check exboard that need to be remove, check pending operations before
				if ((*it) == 0)
				{
					it = devList.erase(it);
				}
				else
					++it;
			}
		}
		// timeout can be 0 if there is a timeout elapse or -1
		int timeout = -1;
		// calculate timeout, get the less one
		unsigned long time = MonotonicTime().toMS();

		// get objects timeout,
		// on timeout mus not be called here
		auto io_it = devList.begin();
		for (std::vector<struct pollfd>::iterator fd_it = devHandle.begin(); fd_it != devHandle.end(); ++fd_it, ++io_it)
		{
			io_sock* volatile *p = &(*io_it);
			struct pollfd& fd = (*fd_it);

			(*p)->getTimeOut(timeout, time);
			// setup events to poll
			fd.fd = (**p).getfd();
			fd.events = 0;
			if ((*p)->needRead())
				fd.events |= POLLIN;
			if ((*p)->needWrite())
				fd.events |= POLLOUT;
			fd.events |= POLLERR;
		}
		//TODO execute timeout function. after that if change then recalculate
		// Poll all devices
		int ir;
		//TODO int ir = poll(devHandle.data(), count, timeout);
		//CHECK_API_RET(ir >= 0);
		time = MonotonicTime().toMS();
		// check events
		io_it = devList.begin();
		for (std::vector<struct pollfd>::iterator fd_it = devHandle.begin(); fd_it != devHandle.end(); ++fd_it, ++io_it)
		{
			io_sock* volatile *p = &(*io_it);
			struct pollfd& fd = (*fd_it);
			if (*p)
				(*p)->checktTimeOut(time);
			if ((ir > 0) && (fd.revents != 0))
			{
				if ((fd.revents & POLLERR) && (*p))
				{
					(*p)->onError();
				}
				if ((fd.revents & POLLIN) && (*p))
				{
					(*p)->onRead();
				}
				if ((fd.revents & POLLOUT) && (*p))
				{
					(*p)->onWrite();
				}
			}
		}
		return NO_ERR;
	}
}
;

/*
 * A io null device can be use to get a timeout event
 */
class ioNull: public io_base
{
public:
	ioNull() :
			io_base()
	{
		onConnected(-1);
	}
};

} /* namespace io */

#endif /* PPOLL_H_ */
