/*
 * ZmqSocket.cpp
 *
 *  Created on: 30 Oct 2013
 *      Author: lester
 */

#ifdef ZMQ

#include "ZmqSocket.h"
#include "ZmqMsg.h"
#include "string.h"

ZmqSocket::ZmqSocket()
{
	sock = 0;
	type = 0;
}

ZmqSocket::~ZmqSocket()
{
	if (sock != 0)
	{
		setLinger(0);
		close();
	}
}

unsigned short ZmqSocket::create(ZmqContext &context, int type)
{
	CHECK_RET(context.isInitialize());
	CHECK_RET_CODE(sock == 0, ERR_CONNECTED);
	sock = zmq_socket(context, type);
	CHECK_API_RET(sock != 0);
	this->type = type;
	setLinger(0);
	return NO_ERR;
}

unsigned short ZmqSocket::bind(const char* endpoint)
{
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_bind(sock, endpoint) != -1);
	// store file handle on base class
	onConnected(getFileDescriptor());
	unsetNeedWrite();		// fd only work with read events
	return NO_ERR;

}
unsigned short ZmqSocket::disconnect(const char* endpoint)
{
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_disconnect(sock, endpoint) != -1);
	onDisconnect();
	return NO_ERR;
}

unsigned short ZmqSocket::connect(const char* endpoint)
{
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_connect(sock, endpoint) != -1);
	// store file handle on base class
	onConnected(getFileDescriptor());
	unsetNeedWrite();	// fd only work with read events
	fdCheckEvents();	// getting problems with this
	return NO_ERR;
}

/*
unsigned short ZmqSocket::send(const void* dt, unsigned short size)
{
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_send(sock, dt, size, 0) != -1);
	unsetCanWrite();
	fdCheckEvents();			// to get a new read possibility
	return NO_ERR;
}
*/

unsigned short ZmqSocket::waitrecv(ZmqMsg &msg)
{
	CHECK_API_RET(zmq_recvmsg(sock, msg, 0) != -1);
	unsetCanRead();
	return NO_ERR;
}



unsigned short ZmqSocket::waitForWrite(long msTimeout)
{
	zmq_pollitem_t zmqItems[1];
	zmqItems[0].socket = sock;
	zmqItems[0].events = ZMQ_POLLOUT;
	if (zmq_poll(zmqItems, 1, msTimeout) == 0) return ERR_TIMEOUT;
	return NO_ERR;
}
unsigned short ZmqSocket::waitForRead(long msTimeout)
{
	zmq_pollitem_t zmqItems[1];
	zmqItems[0].socket = sock;
	zmqItems[0].events = ZMQ_POLLIN;
	if (zmq_poll(zmqItems, 1, msTimeout) == 0) return ERR_TIMEOUT;
	return NO_ERR;

}

unsigned short ZmqSocket::setRecvTimeout(int timeout_ms)
{
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_setsockopt(sock,ZMQ_RCVTIMEO,&timeout_ms,sizeof(timeout_ms)) != -1);
	return NO_ERR;
}
unsigned short ZmqSocket::setSendTimeout(int timeout_ms)
{
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_setsockopt(sock,ZMQ_SNDTIMEO,&timeout_ms,sizeof(timeout_ms)) != -1);
	return NO_ERR;
}

unsigned short ZmqSocket::Subscribe(const char* filter)
{
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_setsockopt(sock,ZMQ_SUBSCRIBE,filter,strlen(filter)) != -1);
	return NO_ERR;

}

unsigned short ZmqSocket::isRecvMoreMessage(bool &b)
{
	uint64_t	v;
	unsigned int size = sizeof(v);
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_getsockopt(sock, ZMQ_RCVMORE, &v, &size) == 0);
	b = v;
	return NO_ERR;
}

unsigned short ZmqSocket::unbind(const char* endpoint)
{
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_unbind(sock, endpoint) != -1);
	onDisconnect();
	return NO_ERR;

}

unsigned short ZmqSocket::unSubscribe(const char* filter)
{
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_setsockopt(sock,ZMQ_UNSUBSCRIBE,filter,strlen(filter)) != -1);
	return NO_ERR;

}

unsigned short ZmqSocket::close()
{
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_close(sock) == 0);
	onDisconnect();
	sock = 0;
	return NO_ERR;
}

unsigned short ZmqSocket::setLinger(int v)
{
	unsigned int	size=sizeof(v);
	CHECK_RET_CODE(sock != 0, ERR_CLOSE);
	CHECK_API_RET(zmq_setsockopt(sock,ZMQ_LINGER,&v,size) != -1);
	return NO_ERR;
}


#endif
