/*
 * ZmqContext.h
 *
 *  Created on: 30 Oct 2013
 *      Author: lester
 */

#ifndef ZMQCONTEXT_H_
#define ZMQCONTEXT_H_

#include "zmq-4.0.3/zmq.h"


class ZmqSocket;

class ZmqContext
{
private:
	ZmqContext(ZmqContext&);
public:
	ZmqContext();
	virtual ~ZmqContext(); //
	inline bool isInitialize()
	{
		return (context != 0);
	}
	unsigned short init()
	{
		CHECK_RET_CODE(context == 0, ERR_CONNECTED);
		context = zmq_ctx_new();
		CHECK_API_RET_CODE(context != 0, ERR_API);
		return NO_ERR;
	}
	/*
	 Setup items
	 */
	void setup_poll(ZmqSocket **sock,zmq_pollitem_t* items,unsigned char count);
	/*
	 poll all zmq sockets
	 */
	unsigned short poll();
	operator void*()
	{
		return context;
	}
private:
	void* context;
	ZmqSocket **poll_sock;
	zmq_pollitem_t* poll_items;
	unsigned char poll_count;
};


#endif /* ZMQCONTEXT_H_ */
