/*
 * BridgeSock.h
 *
 *  Created on: 16 Jun 2014
 *      Author: lester
 */

#ifndef BRIDGESOCK_H_
#define BRIDGESOCK_H_

#include <iostream>

#include "iobase.h"
#include "os.h"
#include "sock.h"

/*
 * Bridge socket that redirect all incoming data to another one
 * How
 * onRead data is read to buffer until it is full
 * onWrite data is write from other side buffer until is empty then try to read
 *
 */

template<class P>	// events will be reporter to this class
class BridgeSock: public net::socket
{
public:
	BridgeSock(P& parent, BridgeSock* sock) :
			parent(parent), sock(sock), buff(b), tm_count(0)
	{

	}
	BridgeSock& operator =(const BridgeSock& o)
	{
		 net::socket::operator =(o);
		return *this;
	}
	~BridgeSock()
	{

	}
protected:

private:
	P& parent;
	BridgeSock* sock;
	io::Block<1280> b;
	io::Buffer buff;
	// hold read times
	unsigned long tm[10];
	uint8_t tm_count;

	virtual void onRead() override
	{
		setCanRead();
		unsetNeedRead();
		do
		{
			*this >> buff;
			if (buff.getRSize())
			{
				unsigned long *l = (unsigned long *) buff.getR();
				tm[tm_count] = MonotonicTime().toNanoSeconds() - *l;
				if (++tm_count == sizeof(tm) / sizeof(*tm))
				{
					std::cout << getpid() << "-->";
					for (unsigned i = 0; i != sizeof(tm) / sizeof(*tm); ++i)
					{
						std::cout << " " << tm[i];
					}
					std::cout << std::endl;
					tm_count = 0;
				}
				// touch all data
				for (char* c = (char*) buff.getR();
						c != (char*) buff.getR() + buff.getRSize(); ++c)
				{
					(*c) += 1;
				}
				*l = MonotonicTime().toNanoSeconds();
			}
			if (sock->canWrite())
			{
				(*sock) << buff;
				buff.compact();
			}
		} while (canRead() && buff.getWSize());
	}
	virtual void onWrite() override
	{
		setCanWrite();
		unsetNeedWrite();
		do
		{
			if (sock->buff.getRSize())
			{
				(*sock) << buff;
				buff.compact();
			}
			if (sock->canRead())
			{
				*sock >> sock->buff;
			}
		} while (canWrite() && sock->buff.getRSize());
	}
	virtual void onError() override
	{
		onDisconnect();
		parent.onSockError(this);
	}
};

#endif /* BRIDGESOCK_H_ */
