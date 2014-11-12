/*
 * ZmqMsg.h
 *
 *  Created on: 31 Oct 2013
 *      Author: lester
 */

#ifndef ZMQMSG_H_
#define ZMQMSG_H_

#include "zmq/zmq.h"

#include "errno.h"

class ZmqMsg
{
	bool initialized;
public:
	ZmqMsg() :
			initialized(false)
	{

		init();

	}
	ZmqMsg(const void* dt, unsigned short size);
	~ZmqMsg()
	{
		close();
	}
	unsigned short set(const void* dt, unsigned short size);
	void get(void* &dt, unsigned short &size)
	{
		dt = zmq_msg_data(&msg);
		size = zmq_msg_size(&msg);
	}
	operator zmq_msg_t *()
	{
		return &msg;
	}
	inline unsigned short getSize()
	{
		return zmq_msg_size(&msg);
	}
	inline void* getData()
	{
		return zmq_msg_data(&msg);
	}
	void close()
	{
		if (initialized)
		{
			CHECK_TRACE_API(zmq_msg_close(&msg) == 0);
		}
	}
	unsigned short init()
	{
		CHECK_TRACE_API(zmq_msg_init(&msg) == 0);
		initialized = true;
		return NO_ERR;
	}
private:
	zmq_msg_t msg;
};

#endif /* ZMQMSG_H_ */
