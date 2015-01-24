/*
 * File.cpp
 *
 *  Created on: 24 Jan 2015
 *      Author: lester
 */

#include "File.h"

namespace POSIX {

File::File()
{
  // TODO Auto-generated constructor stub

}

File::File(const char* name, const char* mode)
{
}

File::File(const char* name, const char* mode,const std::nothrow_t& t)
{
  file_ = fopen(name,mode);
  if (file_ == nullptr)
    status_ |= status_e::fail;
}

File::File(File&& f)
{
}

File& File::operator =(const File&& f)
{

}

File::~File()
{

}

bool File::good()
{
  return status_ == status_e::ok;
}

bool File::eof()
{
  return (status_ & status_e::eof_);
}

} /* namespace POSIX */

bool POSIX::File::close(const std::nothrow_t& t)
{
}

void POSIX::File::close()
{
}
