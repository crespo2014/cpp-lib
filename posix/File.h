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
  bool close(const std::nothrow_t& t);
public:
  File(const char* name,const char* mode);
  File(const char* name,const char* mode,const std::nothrow_t& t);
  File(File&&);
  File& operator=(const File&&);
  File();
  virtual ~File();
  bool good();
  bool eof();
  void close();
protected:
private:
  FILE * file_ = nullptr;
  unsigned status_ = status_e::closed;
  enum status_e { ok,fail,eof_,closed };
};

} /* namespace POSIX */

#endif /* FILE_H_ */
