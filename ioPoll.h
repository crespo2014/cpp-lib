/*
 * ioPoll.h
 *
 *  Created on: 16 Jun 2014
 *      Author: lester
 *
 *  Definition of compatible socket pool using select function
 */

#ifndef IOPOLL_H_
#define IOPOLL_H_

#include <list>
#include <algorithm>
#include <vector>
#include <time.h>

#include "iobase.h"
#include "log.h"
#include "sock.h"

namespace io {

/*
 * Class holding a device list
 */

template<class IO>
class _dev_list
{
public:
	//! Add a new device to poll if device already the handle is reset, it means update file descriptor next time
	// received a reference and store as pointer
	void add(IO* obj)
	{
		// do nothing if device exits
		auto it = std::find(devList.begin(), devList.end(), obj);
		// return if was found
		if (it == devList.end())
		{
			devList.push_back(obj);
			count++;
		} else
		{
			(*it) = 0;
			devList.push_back(obj);
		}
		onChange = true;
	}
	//! remove a device from poll list, nothing happen if element is not found
	void remove(IO* obj)
	{
		// do nothing if device exits
		auto it = std::find(devList.begin(), devList.end(), obj);
		if (it != devList.end())
		{
			(*it) = 0;
			onChange = true;
			count--;
		}
	}
	uint32_t getDeviceCount() const
	{
		return count;
	}
	bool hasChange() const
	{
		return onChange;
	}

protected:
	_dev_list() :
			count(0), onChange(false)
	{

	}
	//! device list to poll
	std::list<IO*> devList;
protected:
	//! count of devices  in list
	int count;
	//! true if a device list has been change, it means devices handles need to be update before poll
	bool onChange;
};

/*
 * sPoll is a class use to poll sockets using system function select
 */
class sPoll: public _dev_list<net::socket>
{
public:
	sPoll()
	{

	}
	~sPoll()
	{

	}
	//! Poll all object in device list
	void pollDevices()
	{
		// timeout can be 0 if there is a timeout elapse or -1
		int timeout = -1;
		os::sock_fd_type fd_max = 0;
		// calculate timeout, get the less one
		unsigned long long time = MonotonicTime().toMS();

		// check for timeouts
		for (auto &p : devList)
		{
			if (p) p->getTimeOut(timeout, time);
		}
		// setup fd_set structure
		// fd must be a valid handler
		FD_ZERO(&rd_fd);
		FD_ZERO(&wr_fd);
		FD_ZERO(&er_fd);
		for (auto &p : devList)
		{
			os::sock_fd_type fd = p->getfd();
			if (fd > fd_max) fd_max = fd;
			if (p->needRead())
			FD_SET(fd, &rd_fd);
			if (p->needWrite())
			FD_SET(fd, &wr_fd);
			FD_SET(fd, &er_fd);
		}
		struct timeval tm;
		if ((timeout >= 0 ) && (timeout > time))
		{
			tm.tv_sec = (timeout - time) / 1000;
			tm.tv_usec = ((timeout - time) % 1000) * 1000 * 1000;
		}
		else
		{
			tm.tv_sec = 0;
			tm.tv_usec = 0;
		}
		int ir = select(count, &rd_fd, &wr_fd, &er_fd, (timeout >= 0)?&tm:nullptr);
		if (ir < 0) throw error_sock_api(ERROR_INFO(), os::getLastSocketError());
		time = MonotonicTime().toMS();

		for (auto it = devList.begin(); it != devList.end(); ++it)
		{
			auto fd = (*it)->getfd();
			net::socket* volatile *p = &(*it);
			if (!(*p)) continue;
			(*p)->checktTimeOut(time);
			if (!(*p)) continue;
			if (FD_ISSET(fd, &rd_fd)) (*p)->onRead();
			if (!(*p)) continue;
			if (FD_ISSET(fd, &wr_fd)) (*p)->onWrite();
			if (!(*p)) continue;
			if (FD_ISSET(fd, &er_fd)) (*p)->onError();
		}
	}
private:
//! update file descriptor list from io device list
	void populate()
	{

	}
	fd_set rd_fd;
	fd_set wr_fd;
	fd_set er_fd;
}
;

/*!
 * two side io device.
 * client side can write and read using block
 * as same for server side with reverse operation.
 */
class BoardData;

class ioBuffer: public io_base
{
public:
	ioBuffer() :
			io_base()
	{
		onConnected(-1);
	}
	virtual io::Buffer& getReadBlock() = 0;
	virtual io::Buffer& getWriteBlock() = 0;

	virtual void onRead()
	{
		io_base::onRead();
	}
	virtual void onWrite()
	{
		io_base::onWrite();
	}
	virtual void onTimeOut()
	{
		io_base::onTimeOut();
	}
	virtual void onError()
	{
		io_base::onError();
	}

};

}
#endif /* IOPOLL_H_ */
