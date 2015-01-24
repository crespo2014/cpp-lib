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

namespace POSIX {

File::File(const char* name,int flag)
{
    file_ = ::open(name,flag);
    if (file_ == -1) throw std::system_error(errno,std::system_category());
    status_ |= status_e::ok;
}

File::File(const char* name, int flag,const std::nothrow_t& t)
{
  file_ = ::open(name,flag);
  if (file_ == -1)
    status_ |= status_e::fail;
}

File::File(File&& f) : file_(f.file_),status_(f.status_)
{
    f.file_ = -1;
}

File& File::operator =(const File&& f)
{

}

File::~File()
{
    if (file_ != -1)
        ::close(file_);
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
//    fclose(file_) != 0)
//}

void File::close()
{
    if (::close(file_) != 0)
        throw std::system_error(errno,std::system_category());
    file_ = -1;
}

int File::ioctl(unsigned long request, void* arg)
{
    return ::ioctl(file_,request,arg);
}

} /* namespace POSIX */
