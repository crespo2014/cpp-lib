/*
 * File.h
 *
 *  Created on: 24 Jan 2015
 *      Author: lester
 */

#ifndef FILE_H_
#define FILE_H_

#include <new>
#include "stdio.h"

namespace POSIX {

class File
{
  File& operator=(const File&)=delete;
  File(const File&)= delete;
  //bool close(const std::nothrow_t& t);
public:
  File(const char* name,int flag);
  File(const char* name,int flag,const std::nothrow_t& t);
  File(File&&);
  File& operator=(const File&&);
  virtual ~File();
  bool good();
  bool eof();
  void close();
  int ioctl(unsigned long request, void* arg);
protected:
private:
  int file_ = -1;
  unsigned status_ = status_e::closed;
  enum status_e { ok,fail,eof_,closed };
};

} /* namespace POSIX */

#endif /* FILE_H_ */
