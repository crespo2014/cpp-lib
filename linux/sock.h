/*
 * sock.h
 *
 *  Created on: 19 Jun 2014
 *      Author: lester
 */

#ifndef SOCK_H_
#define SOCK_H_

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include "exception_base.h"
#include "os.h"
#include "iobase.h"

/*
 * Socket class
 * constructors
 *  none
 *  family,type, protocol, blocking mode
 *
 *  connect	  - ecode allowed
 */

namespace net {
class socket: public io::io_base
{
	enum
	{
		write_channel = 1,    //
		read_channel = 2,
	};

public:
	socket() :
			fd(-1)
	{

	}
	socket(int family, int type, int protocol = 0)
	{
		fd = ::socket(family, type, protocol);
		if (fd == -1) throw error_sock_api(ERROR_INFO());
	}
	socket(int fd, struct sockaddr_in& sock_addr) :
			fd(fd), sock_addr(sock_addr)

	{
		setconnected();
	}
	socket(const socket& o) : io_base(o),
			fd(o.fd), sock_addr(o.sock_addr)
	{
		o.fd = -1;
	}
	socket(socket&& o) : io_base(o),
			fd(o.fd), sock_addr(o.sock_addr)
	{
		o.fd = -1;
	}
	//! Assignment operator
	socket& operator=(const socket& o)
	{
		if (fd != -1)
		{
			close();
		}
		io_base::operator =(o);
		fd = o.fd;
		sock_addr = o.sock_addr;
		o.fd = -1;
		return *this;
	}
	//! Move assignment operator
	socket& operator=(socket&& o)
	{
		if (fd != -1)
		{
			close();
		}
		io_base::operator =(o);
		fd = o.fd;
		sock_addr = o.sock_addr;
		o.fd = -1;
		return *this;
	}
	int getfd() const
	{
		return fd;
	}
	void close()
	{
		if (fd != -1)
		{
			::close(fd);
			fd = -1;
			onDisconnect();
		}
	}
	~socket()
	{
		if (fd != -1) ::close(fd);
	}
	void create(int family = AF_INET, int type = SOCK_STREAM, int protocol = 0)
	{
		if (fd != -1) throw error_api(ERROR_INFO(),api_error::get_close());
		fd = ::socket(family, type, protocol);
		if (fd == -1) throw error_sock_api(ERROR_INFO());
	}
	void setnonBlocking(bool b = true)
	{
		if (fd < 0) throw error_api(ERROR_INFO(),api_error::get_close());
		int opt = b ? 0 : 1;
		int ir = ::ioctl(fd, FIONBIO, &opt);
		if (ir < 0) throw error_sock_api(ERROR_INFO());
	}
	void connect(const char* server, unsigned short port)
	{
		if (fd < 0) throw error_api(ERROR_INFO(),api_error::get_close());
		sock_addr.sin_family = AF_INET;
		sock_addr.sin_port = htons(port);
		int ir = inet_aton(server, &sock_addr.sin_addr);
		if (ir == 0) throw error_sock_api(ERROR_INFO());

		ir = ::connect(fd, (const sockaddr*) &sock_addr, sizeof(sock_addr));
		if (ir == -1)
		{
			if (errno != EINPROGRESS) throw error_sock_api(ERROR_INFO());
		}
		setconnected();
	}
	socket accept()
	{
		if (fd < 0) throw error_api(ERROR_INFO(),api_error::get_close());

		struct sockaddr_in sock_addr;
		int size = sizeof(sock_addr);

		int n_sock = ::accept(fd, (struct sockaddr*) &sock_addr, (socklen_t*) &size);
		if (n_sock == -1) throw error_sock_api(ERROR_INFO());
		unsetCanRead();
		setNeedRead();
		return socket(n_sock, sock_addr);
	}

	/*!
	 * Start listenning on a port
	 */
	void bind(uint16_t port, uint32_t address = INADDR_ANY)
	{
		if (fd < 0) throw error_api(ERROR_INFO(),api_error::get_close());
		sock_addr.sin_family = AF_INET;
		sock_addr.sin_addr.s_addr = address;
		sock_addr.sin_port = htons(port);
		int ir = ::bind(fd, (struct sockaddr*) &sock_addr, sizeof(sock_addr));
		if (ir == -1) throw error_sock_api(ERROR_INFO());
	}
	void listen(int count = 5)
	{
		if (fd < 0) throw error_api(ERROR_INFO(),api_error::get_close());
		int ir = ::listen(fd, count);
		if (ir == -1) throw error_sock_api(ERROR_INFO());
		setconnected();
	}
	/*
	 * for non-blocking socket get error code
	 */
	int getLastError()
	{
		if (fd < 0) throw error_api(ERROR_INFO(),api_error::get_close());
		int ec;
		unsigned int size = sizeof(ec);
		getsockopt(fd, SOL_SOCKET, SO_ERROR, &ec, &size);
		return ec;
	}
	void setTrace(bool b = true)
	{
		trace = b;
	}
protected:
	void read(void* buffer, uint32_t& maxSize, api_error * e = nullptr) override
	{
		int ir;
		if (fd < 0) throw error_api(ERROR_INFO(),api_error::get_close());
		ir = ::recv(fd, buffer, maxSize, 0);		// leave space to put a zero at the end of string
		if (ir == 0)
		{
			if (e != nullptr)
			{
				e->seteof();
			} else
			{
				throw error_api(ERROR_INFO(),api_error::get_eof());
			}
			// eof condition
			ir = 0;
			unsetCanRead();
			unsetNeedRead();
		} else if (ir < 0)
		{
			ir = 0;
			os::api_error_type code = os::getLastSocketError();
			if (code == EAGAIN)
			{
				setNeedRead();
				unsetCanRead();
			} else
			{
				if (e != nullptr)
				{
					e->setApi(code);
				} else
					throw error_sock_api(ERROR_INFO(), code);
			}
		} else
		{
			if ((unsigned) ir < maxSize)
			{
				setNeedRead();
				unsetCanRead();
			}
			// all data on tcp buffer has been read
			/*
			 if (trace)
			 {
			 log_d("%d bytes", ir);
			 //logHexBuff(buffer.getW(), ir, "tcp recv ");
			 }
			 */
		}
		maxSize = ir;
	}
	void write(void* buffer, uint32_t& len, api_error* e = nullptr) override
	{
		int ir;
		if (fd < 0) throw error_api(ERROR_INFO(),api_error::get_close());
		ir = ::send(fd, buffer, len, 0);
		if (ir == 0)
		{
			setNeedWrite();
			unsetCanWrite();
		} else if (ir < 0)
		{
			os::api_error_type code = os::getLastSocketError();
			if (code == EAGAIN)
			{
				setNeedRead();
				unsetCanRead();
				ir = 0;
			} else
			{
				if (e != nullptr)
				{
					return e->setApi(code);
				} else
					throw error_sock_api(ERROR_INFO(), code);
			}
		} else
		{
			if ((unsigned) ir < len)
			{
				unsetCanWrite();
				setNeedWrite();
			}

			if (trace)
			{
				// log_d("%d bytes", ir);
				//logHexBuff(buffer.getR(), buffer.getRSize(), "tcp sent ");
			}
		}
		len = ir;
	}
private:
	mutable int fd;
	struct sockaddr_in sock_addr;    // connection information
	bool trace = false;    // trace all traffic in this socket

	/*
	 * 	unsigned short waitData(unsigned int msTimeout)
	 {
	 ASSERT(fd != -1, ERR_CLOSE);
	 int ir;
	 struct pollfd poll_fd;
	 poll_fd.fd = fd;
	 poll_fd.events = POLLIN;
	 CHECK_API_RET((ir = poll(&poll_fd, 1, msTimeout)) > 0);
	 if (ir == 0) return ERR_TIMEOUT;
	 return NO_ERR;
	 }
	 unsigned short setReadWriteTimeout_ms(int rd_ms, int wr_ms)
	 {
	 ASSERT(fd != -1, ERR_CLOSE);
	 struct timeval rd = { rd_ms / 1000, rd_ms * 1000 };
	 struct timeval wr = { wr_ms / 1000, wr_ms * 1000 };
	 CHECK_TAPI_RET(setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO,&rd, sizeof(rd)) == 0);
	 CHECK_TAPI_RET(setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO,&wr, sizeof(wr)) == 0);
	 return NO_ERR;
	 }
	 unsigned short setReadWriteBuffers(int rd, int wr)
	 {
	 ASSERT(fd != -1, ERR_CLOSE);
	 CHECK_TAPI_RET(setsockopt(fd, SOL_SOCKET, SO_RCVBUF,&rd, sizeof(rd)) == 0);
	 CHECK_TAPI_RET(setsockopt(fd, SOL_SOCKET, SO_SNDBUF,&wr, sizeof(wr)) == 0);
	 return NO_ERR;
	 }*/


};
}


#endif /* SOCK_H_ */
