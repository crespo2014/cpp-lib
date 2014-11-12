/*
 * ZmqSocket.h
 *
 *  Created on: 30 Oct 2013
 *      Author: lester
 */

#ifndef ZMQSOCKET_H_
#define ZMQSOCKET_H_

#include <string>

#include "ZmqContext.h"
#include "ZmqMsg.h"
#include "string.h"
#include "ioBase.h"

class ZmqSocket: public ioDevBase
{
	void *sock;
	// socket type
	int type;

	// Status support for this socket
	// upon checkStatus function call this socket will received data automatically
	// and send it when it is possible

	/*!
	 copy constructor.
	 */
	ZmqSocket(const ZmqSocket& obj);
	void operator=(const ZmqSocket& obj);

	/*
	 Assignment and copy constructor will swap object data because a socket object can not be copied
	 */

	/*!
	 move constructor.
	 */
	ZmqSocket(ZmqSocket& obj)		//<<! no copy constructor, object can not be use on vector container
	{
		ioDevBase::operator=(obj);
		sock = obj.sock;
		type = obj.type;
		// invalidate previous object
		obj.sock = 0;
	}

	/*!
	 Assignment operator
	 */
	void operator=(ZmqSocket& obj)	//<<! no assignment constructor, object can not be use on vector container
	{
		if (sock)
			close();
		sock = obj.sock;
		type = obj.type;
		// invalidate previous object
		obj.sock = 0;
	}

	friend class ZmqContext;
	int getFileDescriptor()
	{
		int fd;
		size_t fd_size = sizeof(fd);
		CHECK_API_RET_CODE(zmq_getsockopt(sock,ZMQ_FD,&fd,&fd_size) != -1, -1);
		return fd;
	}

	/*!
	 * Check if there is a multi-part message waiting to be read
	 */
	bool isRcvMore()
	{
		return false;
	}

	virtual void onWrite()
	{
		// it will never happened
		CHECK_RET_VOID(false);
	}
protected:
	/*!
	 * Polled events for zmq socket
	 */
	virtual void onZmqRead()
	{
		setCanRead();
	}
	virtual void onZmqWrite()
	{
		setCanWrite();
	}

	/*!
	 * Overriden IO base events
	 */
	virtual void onRead()
	{
		// check real events on sock
		fdCheckEvents();
	}

	/*!
	 * Using this socket in a system poll require checking of internal zmq socket status
	 */
	void fdCheckEvents()
	{
		//HERE();
		int evt;
		size_t size = sizeof(evt);
		CHECK_API_RET_VOID(zmq_getsockopt(sock,ZMQ_EVENTS,&evt,&size) != -1);
		if (evt & ZMQ_POLLIN)
		{
			setCanRead();
			//HERE();
			//log_d("zmq on read %X",this);
			onZmqRead();
		}
		if (evt & ZMQ_POLLOUT)
		{
			setCanWrite();
			//HERE();
			//log_d("zmq on write %X",this);
			onZmqWrite();
		}
		if (evt & ZMQ_POLLERR)
		{
			ioDevBase::onError();
			log_d("zmq on error %X", this);
		}
	}
	/*
	 * Update read write events, do not call event function
	 */
	void updateEvents()
	{
		int evt;
		size_t size = sizeof(evt);
		CHECK_API_RET_VOID(zmq_getsockopt(sock,ZMQ_EVENTS,&evt,&size) != -1);
		if (evt & ZMQ_POLLIN)
		{
			setCanRead();
		}
		else
		{
			unsetCanRead();
		}
		if (evt & ZMQ_POLLOUT)
		{
			setCanWrite();
		}
		else
		{
			unsetCanWrite();
		}
		if (evt & ZMQ_POLLERR)
		{
			setOnError();
			unsetNeedRead();
		}
	}
	unsigned short close();

public:

	ZmqSocket();
	virtual ~ZmqSocket();
	/*
	 * wait for event on socket
	 */
	unsigned short waitForWrite(long msTimeout);
	unsigned short waitForRead(long msTimeout);
	/*
	 * restart a connection
	 */
	unsigned short create(ZmqContext &context, int type);
	unsigned short bind(const char* endpoint);
	unsigned short unbind(const char* endpoint);
	unsigned short disconnect(const char* endpoint);
	unsigned short connect(const char* endpoint);

	unsigned short setRecvTimeout(int timeout_ms);
	unsigned short setSendTimeout(int timeout_ms);
	/*
	 * blocking call to received
	 */
	unsigned short waitrecv(ZmqMsg &msg);
	unsigned short isRecvMoreMessage(bool &b);
	operator void*()
	{
		return sock;
	}
	/*
	 * Use by subscription sock to subscribe to
	 */
	unsigned short Subscribe(const char* filter);
	unsigned short unSubscribe(const char* filter);
	unsigned short setLinger(int v);

	unsigned short sendPart(const void* dt, unsigned short size, int flags = ZMQ_DONTWAIT)
	{
		return write(dt, size, flags | ZMQ_SNDMORE);
	}
	unsigned short sendPart(const std::string &dt)
	{
		return sendPart(dt.c_str(), dt.length());
	}

	unsigned short send(std::string msg)
	{
		return write(msg.c_str(), msg.length());
	}

	//! read data from socket and fill string object
	unsigned short read(std::string &s, int flags = ZMQ_DONTWAIT)
	{
		ZmqMsg msg;
		CHECK_ERR_RET(readMsg(msg, flags));
		s.assign(static_cast<char*>(msg.getData()), msg.getSize());
		return NO_ERR;
	}

	unsigned short readMsg(ZmqMsg &msg, int flags = ZMQ_DONTWAIT)
	{
		int i = zmq_recvmsg(sock, msg, flags);
		unsetCanRead();
		CHECK_RET_CODE(i != 0 ,ERR_BUSY);		// return if there is not more messages
		CHECK_API_RET(i != -1);					// return if there was a error
		updateEvents();
		return NO_ERR;
	}

	//! write data to socket
	unsigned short write(const void* data, unsigned short len, int flags = ZMQ_DONTWAIT)
	{
		CHECK_RET_CODE(sock != 0, ERR_CLOSE);
		CHECK_API_RET(zmq_send(sock, data, len, flags) != -1);
		unsetCanWrite();
		updateEvents();			// to get a new read possibility
		return NO_ERR;
	}
	//! write data to socket
	unsigned short writeMsg(void* data, unsigned short len, int flags = ZMQ_DONTWAIT)
	{
		ZmqMsg msg(data, len);
		CHECK_API_RET(zmq_sendmsg(sock, msg, flags) != -1);
		unsetCanWrite();
		updateEvents();			// to get a new read possibility
		return NO_ERR;
	}

	void release(const char* endpoint)
	{
		if (sock != 0)
		{
			disconnect(endpoint);
			close();
		}
	}
};

/*!
 * use this class with req-rep or rep-req socket
 * a status is maintained
 */
class ZmqStatusSock: public ZmqSocket
{
	enum
	{
		ST_NONE,			// it is not sending it is not receiving, first command use will decide the direction
		ST_ERROR,			//
		ST_SENDING,			// data is waiting to be send
		ST_READING,			// waiting to read data a timeout can be useful
		ST_DATA_RECEIVED,	// data has been received
		ST_WAIT_SEND,		// after get data waiting for send more data
		ST_TIMEOUT,
	} status;
	std::string data;
	//! every read operation this timeout will be set and clear
	unsigned long readTimeout;

	/*!
	 * Send data on buffer when canWrite is possible
	 */
	unsigned short Send()
	{
		unsigned short e;
		CHECK_ERR_TRACE((e = write(data.c_str(), data.length())));
		//log_d("zmq sent %s",data.c_str());
		if (readTimeout)
			setTimeOut(readTimeout);
		if (e != NO_ERR)
			status = ST_ERROR;
		else
			status = ST_READING;
		return e;
	}
protected:
	void setReadTimeout(unsigned long timeout_ms)
	{
		readTimeout = timeout_ms;
	}
public:
	//! default constructor
	ZmqStatusSock() :
			status(ST_NONE), readTimeout(0)
	{

	}
	/*!
	 * Overridden ZMQ IO events
	 */
	virtual void onZmqRead()
	{
		unsigned short e;
		CHECK_ERR_TRACE((e = read(data)));
		if (readTimeout)
			setTimeOut(0);
		if (e != NO_ERR)
			status = ST_ERROR;
		else
		{
			//log_d("zmq received %s",data.c_str());
			status = ST_DATA_RECEIVED;
		}
	}
	virtual void onZmqWrite()
	{
		if (status == ST_SENDING)
			Send();
		else
			setCanWrite();
	}

	/*!
	 * Check for received data
	 */
	bool isData()
	{
		return (status == ST_DATA_RECEIVED);
	}
	/*
	 * true if this object is able to queue data to send
	 */
	bool isSendDirection()
	{
		return ((status == ST_DATA_RECEIVED) || (status == ST_NONE) || (status == ST_WAIT_SEND));
	}
	unsigned short sendData(std::string s)
	{
		CHECK_RET_CODE((status == ST_DATA_RECEIVED) || (status == ST_NONE) || (status == ST_WAIT_SEND), ERR_STATUS);
		data = s;
		status = ST_SENDING;

		if (canWrite())
			return Send();
		return NO_ERR;
	}
	unsigned short getData(std::string& d)
	{
		CHECK_RET_CODE(status == ST_DATA_RECEIVED, ERR_STATUS);
		d = data;
		status = ST_WAIT_SEND;
		return NO_ERR;
	}
protected:
	/*!
	 * Use this function after a timeout or re-connection
	 */
	void clearStatus()
	{
		status = ST_NONE;
	}
	/*!
	 * send last command again
	 */
	void resend()
	{
		status = ST_SENDING;
		if (canWrite())
			Send();
	}
};

#endif /* ZMQSOCKET_H_ */
