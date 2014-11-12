/*
 * ZmqContext.cpp
 *
 *  Created on: 30 Oct 2013
 *      Author: lester
 */


#ifdef ZMQ


#include "ZmqContext.h"
#include "ZmqSocket.h"

ZmqContext::ZmqContext()
{
	context = 0;
	poll_count = 0;
	poll_sock = 0;
	poll_items = 0;

}

ZmqContext::~ZmqContext()
{
	if (context)
	{
		//CHECK_TRACE_API(zmq_term(context) ==0);	//TODO deprecated
		CHECK_TRACE_API(zmq_ctx_term(context) == 0);
		context = 0;
	}
}

void ZmqContext::setup_poll(ZmqSocket **sock, zmq_pollitem_t* items, unsigned char count)
{
	poll_sock = sock;
	poll_items = items;
	poll_count = count;
	for (int i = 0; i < count; i++)
	{
		poll_items[i].events = ZMQ_POLLIN | ZMQ_POLLOUT | ZMQ_POLLERR;
		poll_items[i].socket = *poll_sock[i];
		poll_items[i].fd = -1;
	}
}

unsigned short ZmqContext::poll()
{
	// timeout can be 0 if there is a timeout elapse or -1

	int timeout = -1;
	// calculate timeout, get the less one
	unsigned long time = getMonotonicClockMS();
	for (int i = 0; i < poll_count; i++)
	{
		poll_sock[i]->getTimeOut(timeout, time);
		// setup events to poll
		poll_items[i].events = 0;
		if (!poll_sock[i]->canRead()) poll_items[i].events |= ZMQ_POLLIN;
		if (!poll_sock[i]->canWrite()) poll_items[i].events |= ZMQ_POLLOUT;
		if (!poll_sock[i]->isError()) poll_items[i].events |= ZMQ_POLLERR;
	}

	int ir = zmq_poll(poll_items, poll_count, timeout);

	CHECK_API_RET(ir >= 0);
	if (ir == 0)
	{
		time = getMonotonicClockMS();
		for (int i = 0; i < poll_count; i++)
			poll_sock[i]->checktTimeOut(time);
		return ERR_TIMEOUT;
	}

	for (int i = 0; i < poll_count; i++)
	{
		if (poll_items[i].revents != 0)
		{
			if (poll_items[i].revents & ZMQ_POLLIN)
			{
				poll_sock[i]->onZmqRead();
			}
			if (poll_items[i].revents & ZMQ_POLLOUT)
			{
				poll_sock[i]->onZmqWrite();
			}
			if (poll_items[i].revents & ZMQ_POLLERR) poll_sock[i]->setOnError();
		}
	}
	return NO_ERR;

}

#endif
