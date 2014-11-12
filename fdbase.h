/*
 * fdbase.h
 *
 *  Created on: 22 Jun 2014
 *      Author: lester
 */

#ifndef FDBASE_H_
#define FDBASE_H_

/*
 * this a template object holding a file descriptor
 * it is use to swap ownership of descriptor for ctor and assignment
 *
 */

template<typename FD, FD no_value = -1>
class fd_base
{
public:
	FD getfd() const
	{
		return fd;
	}
protected:
	fd_base() :
			fd(no_value)
	{

	}
	fd_base(FD fd) :
			fd(fd)
	{

	}
	fd_base(const fd_base& o) :
			fd(o.fd)
	{
		o.fd = no_value;
	}
	fd_base(fd_base&& o) :
			fd(o.fd)
	{
		o.fd = no_value;
	}
	//! Assignment operator
	fd_base& operator=(const fd_base& o)
	{
		if (fd != no_value)
		{
			//close();
			//TODO close();
		}
		fd = o.fd;
		o.fd = no_value;

		return *this;
	}
	//! Move assignment operator
	fd_base& operator=(fd_base&& o)
	{
		if (fd != no_value)
		{
			//TODO close();
		}
		fd = o.fd;
		o.fd = no_value;
		return *this;
	}

	bool isfd()
	{
		return fd != no_value;
	}
	mutable FD fd;
private:
};

#endif /* FDBASE_H_ */
