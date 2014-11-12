/*
 * ZmqMsg.cpp
 *
 *  Created on: 31 Oct 2013
 *      Author: lester
 */


#ifdef ZMQ

#include "ZmqMsg.h"

#include "errno.h"

ZmqMsg::ZmqMsg(const void* dt, unsigned short size)
{
	CHECK_TRACE_API(zmq_msg_init(&msg) == 0);
	set(dt, size);
}

unsigned short ZmqMsg::set(const void* dt, unsigned short size)
{
	// dont release this buffer of data
	CHECK_API_RET(zmq_msg_init_data(&msg,(void*)dt,size, NULL, NULL) == 0);
	return NO_ERR;
}


#endif
