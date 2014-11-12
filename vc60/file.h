/*
 * file_api.h
 *
 *  Created on: 29/06/2012
 *      Author: lester
 */

#ifndef FILE_API_H_
#define FILE_API_H_

#include "platform.h"
#include "bobject.h"

#ifdef WIN32

#include "w32\sysfile.h"

#else

#include "linux\sysfile.h"

#endif

// flags de fichero 
#define FF_ADD	1		// open for add
#define FF_WR	2		// write 
#define FF_RO	4
#define FF_BIN	8		// binary mode
#define FF_SH_RD	16	// share read

class cfile : public csysfile , public CbObject
{
public:
	cfile();
	virtual ~cfile();
	DWORD	open(const char* file_name, const DWORD mode);
	DWORD	close();
	DWORD	write(const void* buffer, const DWORD size);
	DWORD	read(void* buffer,const DWORD size,DWORD* readed);
	BOOL	isOpen();
private:
	DWORD	mfilemode;

};

#endif /* FILE_API_H_ */
