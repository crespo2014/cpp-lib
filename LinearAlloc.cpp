/*
 * LinearAlloc.cpp
 *
 *  Created on: 1 Nov 2013
 *      Author: lester
 */

#include "LinearAlloc.h"
#include "os.h"
#include "string.h"
#include "log.h"

/*
void* LinearAlloc::get(unsigned short size)
{
	//CHECK_RET_CODE(getFree() >= size,0);
	unsigned short idx = pos;
	pos += ((size + sizeof(*dt) -1)/sizeof(*dt));
	return &dt[idx];
}
*/

void LinearAlloc::AddString(const char *str, unsigned int len, char * &mem)
{
	if ((len < 1) || (str == nullptr))
		throw error_api(ERROR_INFO(),api_error::get_wrong_param());
	mem = (char*)get(len + 1);
	memcpy(mem, str, len);
	mem[len] = 0;
}
