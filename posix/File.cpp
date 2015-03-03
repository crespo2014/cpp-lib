/*
 * File.cpp
 *
 *  Created on: 24 Jan 2015
 *      Author: lester
 */
#include <system_error>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "File.h"
#include <poll.h>

namespace POSIX {

File::File(const char* name,int flag)
{
    fd_ = ::open(name,flag);
    if (fd_ == -1) throw std::system_error(errno,std::system_category());
    status_ |= status_e::ok;
}

File::File(const char* name, int flag,const std::nothrow_t& t)
{
  fd_ = ::open(name,flag);
  if (fd_ == -1)
    status_ |= status_e::fail;
}

File::File(File&& f) : fd_(f.fd_),status_(f.status_)
{
    f.fd_ = -1;
}

File& File::operator =(const File&& f)
{

}

File::~File()
{
    if (fd_ != -1)
        ::close(fd_);
        //close(std::nothrow);
}

bool File::good()
{
  return status_ == status_e::ok;
}

bool File::eof()
{
  return (status_ & status_e::eof_);
}

//bool File::close(const std::nothrow_t& t)
//{
//    fclose(fd_) != 0)
//}

void File::close()
{
    if (::close(fd_) != 0)
        throw std::system_error(errno,std::system_category());
    fd_ = -1;
}

int File::ioctl(unsigned long request, void* arg)
{
    return ::ioctl(fd_,request,arg);
}

void* File::mmap(void *addr, size_t length, int prot, int flags,off_t offset)
{
    void* p = ::mmap(addr,length,prot,flags,fd_,offset);
    if (p == MAP_FAILED)
        throw std::system_error(errno, std::system_category());
    return p;
}

bool File::poll(short events, short& revents, int timeout, const std::nothrow_t&)
{
    struct pollfd fds;
    fds.events = events;
    fds.revents = 0;
    fds.fd = fd_;
    int r = ::poll(&fds, 1, timeout);
    revents = fds.revents;
    return (r > 0);
}

} /* namespace POSIX */
