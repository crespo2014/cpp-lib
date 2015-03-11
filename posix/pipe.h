/*
 * pipe.h
 *
 *  Created on: 10 Mar 2015
 *      Author: lester
 */

#ifndef PIPE_H_
#define PIPE_H_

#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>
#include <sys/uio.h>

#include "File.h"

class Pipe
{
public:
	/*
	 * Create a pipe
	 */
	Pipe(const std::nothrow_t&)
	{
		int fd[2];
		if (::pipe(fd) == 0)
		{
			rd_fd_ = std::move(POSIX::File(fd[0]));
			wr_fd_ = std::move(POSIX::File(fd[1]));
		}
		else
			good = false;
	}
	ssize_t spliceTo(int fd_out,size_t len)
	{
		auto r = ::splice(rd_fd_.getfd(),nullptr,fd_out,nullptr,len,0);
		if (r < 0)
			throw std::system_error(errno, std::system_category(), "splice");
		return r;
	}

	ssize_t sendfile(int out_fd,off_t* offset,size_t count, const std::nothrow_t&)
	{
		return 0;
	}
	ssize_t sendfile(int out_fd,size_t count)
	{
		auto r = ::sendfile(out_fd,rd_fd_.getfd(),nullptr,count);
		if (r < 0)
			throw std::system_error(errno, std::system_category(), "sendfile");
		return r;
	}
	ssize_t sendfile(int out_fd,size_t count,const std::nothrow_t&)
	{
		auto r = ::sendfile(out_fd,rd_fd_.getfd(),nullptr,count);
		return r;
	}
	ssize_t writev(const struct iovec *iov, int iovcnt, const std::nothrow_t&)
	{
		return ::writev(wr_fd_.getfd(), iov, iovcnt);
	}
	ssize_t readv(const struct iovec *iov, int iovcnt, const std::nothrow_t&)
	{
		return ::readv(rd_fd_.getfd(), iov, iovcnt);
	}
	ssize_t read(void* dt, size_t count, const std::nothrow_t&)
	{
		return ::read(rd_fd_.getfd(), dt, count);
	}
	ssize_t write(const void* dt, size_t count, const std::nothrow_t&)
	{
		return ::write(wr_fd_.getfd(), dt, count);
	}
	operator bool() const
	{
		return (good && rd_fd_ && wr_fd_);
	}
	bool shutdownRead(const std::nothrow_t&)
	{
		rd_fd_.close();
		return true;
	}
	bool shutdownWrite(const std::nothrow_t&)
	{
		wr_fd_.close();
		return true;
	}
private:
	// Disabling all default
	Pipe(const Pipe&) = delete;
	Pipe(Pipe&&) = delete;
	Pipe& operator=(const Pipe&) = delete;
	Pipe& operator=(Pipe&&) = delete;
	bool good = true;
	POSIX::File rd_fd_;
	POSIX::File wr_fd_;
};

#endif /* PIPE_H_ */
