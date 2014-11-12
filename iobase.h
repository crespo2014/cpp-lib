/*
 * iobase.h
 *
 *  Created on: 15 Jun 2014
 *      Author: lester
 */

#ifndef IOBASE_H_
#define IOBASE_H_

#include  <utility>
#include <bitset>
#include "Buffer.h"
#include "MonotonicTime.h"

template<typename I>
class bits
{
public:
	unsigned flags = 0;

	bool operator[](I b) const
	{
		return ((flags & (1 << b)) != 0);
	}
	void set(I b)
	{
		flags |= (1 << b);
	}
	void clear(I b)
	{
		flags &= (~(1 << b));
	}
	void reset()
	{
		flags = 0;
	}
};

namespace io
{

/*
 * abstract that must be implement by input output devices
 */

class io_base
{
private:
	// io device status
	enum flag
	{
		connected = 0,    //
		can_read,
		can_write,
		timeout,
		error,
		need_read,
		need_write
	};
public:
	io_base()
	{

	}
	io_base(const io_base & b) :
			flags(b.flags), monoticTimeoutMS(b.monoticTimeoutMS), last_monoticTimeoutMS(
					b.last_monoticTimeoutMS)
	{

	}
	io_base(io_base && b) :
			flags(b.flags), monoticTimeoutMS(b.monoticTimeoutMS), last_monoticTimeoutMS(
					b.last_monoticTimeoutMS)
	{

	}

	io_base& operator =(io_base && b)
	{
		if (this != &b)
		{
			flags = b.flags;
			monoticTimeoutMS = b.monoticTimeoutMS;
			last_monoticTimeoutMS = b.last_monoticTimeoutMS;
		}
		return *this;
	}

	io_base& operator =(const io_base & b)
	{
		if (this != &b)
		{
			flags = b.flags;
			monoticTimeoutMS = b.monoticTimeoutMS;
			last_monoticTimeoutMS = b.last_monoticTimeoutMS;
		}
		return *this;
	}

	bool isConnected() const
	{
		return flags[flag::connected];
	}
	inline bool isEvent() const
	{
		return (flags[flag::can_read] || flags[flag::can_write]
				|| flags[flag::error]);
	}
	inline bool isError() const
	{
		return flags[flag::error];
	}
	inline bool canRead() const
	{
		return flags[flag::can_read];
	}
	inline bool canWrite() const
	{
		return flags[flag::can_write];
	}
	// check for recorded time out event and clear timeout flag
	inline bool isTimeOut()
	{
		bool b = flags[flag::timeout];
		flags.clear(flag::timeout);
		return b;
	}
	/*
	 * Read write from device controlling flow with error code
	 */
	void read(io::Buffer& buffer, api_error& e)
	{
		uint32_t size = buffer.getWSize();
		if (size)
		{
			read(buffer.getW(), size, &e);
		}
		buffer.updateW(size);
	}
	void write(io::Buffer& buffer, api_error& e)
	{
		uint32_t size = buffer.getRSize();
		if (size)
		{
			write(buffer.getR(), size,&e);
		}
		buffer.updateR(size);
	}

	// Read write operator with exceptions
	io_base& operator >>(io::Buffer& buffer)
	{
		uint32_t size = buffer.getWSize();
		if (size)
		{
			read(buffer.getW(), size);
		}
		buffer.updateW(size);
		return *this;
	}
	io_base& operator <<(io::Buffer& buffer)
	{
		uint32_t size = buffer.getRSize();
		if (size)
		{
			write(buffer.getR(), size);
		}
		buffer.updateR(size);
		return *this;
	}
	// write operation without modification
	void operator <<(const io::Buffer& buffer)
	{
		uint32_t size = buffer.getRSize();
		if (size)
		{
			write(buffer.getR(), size);
		}
	}
	bool needRead() const
	{
		return flags[flag::need_read];
	}
	bool needWrite() const
	{
		return flags[flag::need_write];
	}

	/*
	 * Get current timeout for this object.
	 * call this function before poll devices
	 *
	 * msTimeout is the current timeout
	 * time is the current time
	 *
	 */
	void getTimeOut(int &msTimeout, unsigned long time)
	{
		if (isTimeOut())
		{
			// this is a bad situation, because somebody forgot handle ontimeout events
			// return_exception(uncached timeut);
		}
		// Check if this object has set timeout
		if (monoticTimeoutMS != 0)
		{
			// check if the timeout has happened
			if (time >= monoticTimeoutMS)
			{
				msTimeout = 0;
				flags.set(flag::timeout);
			}
			else
			{
				// no previous time defined or time mark is above this object
				if ((msTimeout < 0) || (time + msTimeout > monoticTimeoutMS))
					msTimeout = monoticTimeoutMS - time;
			}

		}
	}
	/*
	 * After poll check device timeout
	 */
	void checktTimeOut(unsigned long time)
	{
		if ((monoticTimeoutMS != 0) && (time >= monoticTimeoutMS))
		{
			// object most process timeout, otherwise the flag will remain active for next time
			last_monoticTimeoutMS = monoticTimeoutMS;
			monoticTimeoutMS = 0;
			onTimeOut();
		}
	}

	/*!
	 * Set timeout mark, a timeout event will be generate for this object when system time reach the value
	 */
	inline void setTimeOut(unsigned long time_ms = 0)
	{
		if (!time_ms)
		{
			flags.clear(flag::timeout);
		}
		monoticTimeoutMS =
				(time_ms == 0) ? 0 : MonotonicTime().toMS() + time_ms;
	}
	/*!
	 * Set Timeout relative to last timeout mark
	 */
	void setNextTimeout(unsigned long time_ms = 0)
	{
		if (!time_ms)
		{
			monoticTimeoutMS = 0;		// disable timeout
		}
		else
		{
			if (last_monoticTimeoutMS == 0)
				last_monoticTimeoutMS = MonotonicTime().toMS();
			monoticTimeoutMS = last_monoticTimeoutMS + time_ms;
		}
	}
	/*
	 virtual io::Buffer& read(io::Buffer &buffer) = 0;
	 virtual io::Buffer& write(io::Buffer &buffer) = 0;
	 */

	// read from device return number of read bytes in maxSize
	virtual void read(void* buffer, uint32_t& maxSize,
			api_error * e = nullptr) = 0;
	// return number of write bytes in size
	virtual void write(void* buffer, uint32_t& len,
			api_error* e = nullptr) = 0;

	virtual void onRead()
	{
		setCanRead();
		unsetNeedRead();
	}
	virtual void onWrite()
	{
		setCanWrite();
		unsetNeedWrite();
	}
	virtual void onTimeOut()
	{
		flags.set(flag::timeout);
	}
	virtual void onError()
	{
		setOnError();
		unsetCanRead();
		unsetCanWrite();
		unsetNeedRead();
		unsetNeedWrite();
	}

	//! clear timeout status on device
	void unsetTimeout()
	{
		flags.clear(flag::timeout);
	}
	//!clear error flag on device
	void unsetError()
	{
		flags.clear(flag::error);
	}

	virtual ~io_base()
	{
	}
	/*!
	 * called from poll handler
	 */

	/*
	 * Set unset bit functions
	 */
	inline void setCanRead()
	{
		flags.set(flag::can_read);
	}
	inline void setNeedRead()
	{
		flags.set(flag::need_read);
	}
	void setOnError()
	{
		flags.set(flag::error);
	}
	inline void setCanWrite()
	{
		flags.set(flag::can_write);
	}
	inline void setNeedWrite()
	{
		flags.set(flag::need_write);
	}
	inline void unsetCanWrite()
	{
		flags.clear(flag::can_write);
	}
	inline void unsetNeedWrite()
	{
		flags.clear(flag::need_write);
	}
	inline void unsetCanRead()
	{
		flags.clear(flag::can_read);
	}
	inline void unsetNeedRead()
	{
		flags.clear(flag::need_read);
	}
	/*
	 * Get status functions
	 */

	/*!
	 * Update device status to connected, called from derived class
	 */
	inline void onConnected(int fd)
	{
		flags.set(flag::connected);
		setNeedRead();
		setNeedWrite();
		unsetCanRead();
		unsetCanWrite();
	}
	inline void setconnected()
	{
		onConnected(-1);
	}
	/*!
	 * update device status to disconnect
	 */
	inline void onDisconnect()
	{
		unsetNeedRead();
		unsetNeedWrite();
		unsetCanRead();
		unsetCanWrite();
		flags.clear(flag::connected);
	}
	void clear()
	{
		flags.reset();
		monoticTimeoutMS = 0;
	}
	void setTrace()
	{
		trace = true;
	}
	void unsetTrace()
	{
		trace = false;
	}
protected:
	bool trace = false;		// trace to log all traffic
private:
	bits<flag> flags;
	//! set this to a non zero value to get a timeout event when this socket is poll and system time reach the settled value
	unsigned long monoticTimeoutMS = 0;
	// timeout mark of last event to get more precise timeout
	unsigned long last_monoticTimeoutMS = 0;// MonotonicTime().toMS();
};

/*
 * A derive class that notify all events on a specific io object
 * events are Read, Write, Error, TimeOut
 *
 * B base class, N notify class
 */
template<class B, class N>
class ioNotifier: public B
{
public:
	ioNotifier(N& p) :
			parent(p)
	{

	}
	// move constructor
	ioNotifier(ioNotifier&& n) :
			B(n), parent(n.parent)
	{

	}
	virtual ~ioNotifier()
	{

	}
protected:
	// override callback functions
	virtual void onRead() override
	{
		parent.onRead(this);
	}
	virtual void onWrite() override
	{
		parent.onWrite(this);
	}
	virtual void onTimeOut() override
	{
		parent.onTimeOut(this);
	}
	virtual void onError() override
	{
		parent.onError(this);
	}

private:
	N& parent;
};

//berkeley sockets

} /* namespace io */

#endif /* IOBASE_H_ */
