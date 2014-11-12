/*
 * sock.h
 *
 *  Created on: 19 Jun 2014
 *      Author: lester
 */

#ifndef SOCK_H_
#define SOCK_H_

#pragma comment(lib,"Ws2_32.lib")

#include <stdio.h>
#include <stdlib.h>   // Needed for _wtoi

#include "os.h"
#include "iobase.h"

DEFINE_DERIVED_EXCEPTION(error_address, error_socket, "Invalid internet address");

/*
 * Socket class
 * constructors
 *  none
 *  family,type, protocol, blocking mode
 *
 *  connect	  - ecode allowed
 */

namespace net
{
class socket: public io::io_base
{
	static WORD ws_version;
	static WSADATA ws_data;

	using fd_type = SOCKET;
	enum
	{
		write_channel = 1,    //
		read_channel = 2,
	};

	mutable os::sock_fd_type fd;
	struct sockaddr_in sock_addr;    // connection information
	bool trace = false;    // trace all traffic in this socket

public:
	static int ws_startup;
	static int startUp()
	{
		ws_version = MAKEWORD(2, 2);
		return WSAStartup(ws_version, &ws_data);
	}
	socket() :
			fd(-1)
	{

	}
	socket(int family, int type, int protocol = 0)
	{
		fd = ::socket(family, type, protocol);
		if (fd == -1)
			throw error_sock_api(ERROR_INFO());
	}
	socket(int fd, struct sockaddr_in& sock_addr) :
			fd(fd), sock_addr(sock_addr)

	{
		setconnected();
	}
	socket(const socket& o) :
			io_base(o), fd(o.fd), sock_addr(o.sock_addr)
	{
		o.fd = -1;
	}
	socket(socket&& o) :
			io_base(o), fd(o.fd), sock_addr(o.sock_addr)
	{
		o.fd = -1;
	}
	//! Assignment operator
	net::socket& operator=(const net::socket& o)
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
	net::socket& operator=(socket&& o)
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
	os::sock_fd_type getfd() const
	{
		return fd;
	}
	void close()
	{
		if (fd != -1)
		{
			::closesocket(fd);
			fd = -1;
			onDisconnect();
		}
	}
	~socket()
	{
		if (fd != -1)
			::closesocket(fd);
	}
	void create(int family = AF_INET, int type = SOCK_STREAM, int protocol = 0)
	{
		if (fd != -1)
			throw error_api(ERROR_INFO(), api_error::get_open());
		fd = ::socket(family, type, protocol);
		if (fd == -1)
		{
			throw error_sock_api(ERROR_INFO());
		}

	}
	void setnonBlocking(bool b = true)
	{
		if (fd < 0)
			throw error_api(ERROR_INFO(), api_error::get_close());
		u_long opt = b ? 0 : 1;
		int ir = ::ioctlsocket(fd, FIONBIO, &opt);
		if (ir < 0)
			throw error_sock_api(ERROR_INFO());
	}
	void connect(const char* server, unsigned short port)
	{
		if (fd < 0)
			throw error_api(ERROR_INFO(), api_error::get_open());
		sock_addr.sin_family = AF_INET;
		sock_addr.sin_port = htons(port);

		sock_addr.sin_addr.S_un.S_addr = inet_addr(server);
		if ((sock_addr.sin_addr.S_un.S_addr == INADDR_NONE) || (sock_addr.sin_addr.S_un.S_addr == INADDR_ANY ))
		{
			throw error_address(ERROR_INFO());
		}
		int ir = ::connect(fd, (const sockaddr*) &sock_addr, sizeof(sock_addr));
		if (ir == SOCKET_ERROR)
		{
			api_error ae(os::getLastSocketError());
			if (!ae.would_block())
				throw error_sock_api(ERROR_INFO(), ae);
		}
		setconnected();
	}
	net::socket accept()
	{
		if (fd < 0)
			throw error_api(ERROR_INFO(), api_error::get_close());

		struct sockaddr_in sock_addr;
		int size = sizeof(sock_addr);

		int n_sock = ::accept(fd, (struct sockaddr*) &sock_addr, (socklen_t*) &size);
		if (n_sock == SOCKET_ERROR)
		{
			throw error_sock_api(ERROR_INFO(), os::getLastSocketError());
		}
		unsetCanRead();
		setNeedRead();
		return socket(n_sock, sock_addr);
	}

	/*!
	 * Start listenning on a port
	 */
	void bind(uint16_t port, uint32_t address = INADDR_ANY)
	{
		if (fd < 0)
			throw error_api(ERROR_INFO(), api_error::get_close());
		sock_addr.sin_family = AF_INET;
		sock_addr.sin_addr.s_addr = address;
		sock_addr.sin_port = htons(port);
		int ir = ::bind(fd, (struct sockaddr*) &sock_addr, sizeof(sock_addr));
		if (ir == -1)
			throw error_sock_api(ERROR_INFO(), os::getLastSocketError());
	}
	void listen(int count = 5)
	{
		if (fd < 0)
			throw error_api(ERROR_INFO(), api_error::get_close());
		int ir = ::listen(fd, count);
		if (ir == -1)
			throw error_sock_api(ERROR_INFO(), os::getLastSocketError());
		onConnected(fd);
	}
	/*
	 * for non-blocking socket get error code
	 */
	void getLastError(api_error& e)
	{
		if (fd < 0)
			throw error_api(ERROR_INFO(), api_error::get_close());
		int ec;
		int size = sizeof(ec);
		getsockopt(fd, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&ec), &size);
		e.setApi(ec);
	}
	void setTrace(bool b = true)
	{
		trace = b;
	}
protected:
	void read(void* buffer, uint32_t& maxSize, api_error * e = nullptr) override
	{
		int ir;
		if (fd < 0)
			throw error_api(ERROR_INFO(), api_error::get_close());
		ir = ::recv(fd, reinterpret_cast<char*>(buffer), maxSize, 0);		// leave space to put a zero at the end of string
		if (ir == 0)
		{
			if (e != nullptr)
			{
				e->seteof();
			}
			else
			{
				throw error_api(ERROR_INFO(), api_error::get_eof());
			}
			// eof condition
			ir = 0;
			unsetCanRead();
			unsetNeedRead();
		}
		else if (ir < 0)
		{
			ir = 0;
			api_error ae(os::getLastSocketError());
			if (ae.would_block())
			{
				setNeedRead();
				unsetCanRead();
			}
			else
			{
				if (e != nullptr)
				{
					*e = ae;
				}
				else
					throw error_sock_api(ERROR_INFO(), ae);
			}
		}
		else
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
		if (fd < 0)
			throw error_api(ERROR_INFO(), api_error::get_close());
		ir = ::send(fd, reinterpret_cast<char*>(buffer), len, 0);
		if (ir == 0)
		{
			setNeedWrite();
			unsetCanWrite();
		}
		else if (ir < 0)
		{
			os::api_error_type code = os::getLastSocketError();
			if (code == EAGAIN)
			{
				setNeedWrite();
				unsetCanWrite();
				ir = 0;
			}
			else
			{
				if (e != nullptr)
				{
					return e->setApi(code);
				}
				else
					throw error_sock_api(ERROR_INFO(), code);
			}
		}
		else
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
}
;
}

#endif /* SOCK_H_ */
