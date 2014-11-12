/*
 * File.cpp
 *
 *  Created on: 18 Apr 2014
 *      Author: lester
 */

#include "File.h"
#include "log.h"

void File::LoadToMemory(const char* fname,void* &dt,unsigned int &size, OneRelease &alloc)
{
	struct stat fstatus;
	f = fopen(fname, "r");
	//CHECK_API_RET(lstat(fname, &fstatus) == 0);
	dt = alloc.alloc(fstatus.st_size);
	size = fread(dt,1,fstatus.st_size,f);
	close();
}
