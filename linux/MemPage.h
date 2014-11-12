/*
 * MemPage.h
 *
 *  Created on: 23 Aug 2013
 *      Author: lester
 */

#ifndef MEMPAGE_H_
#define MEMPAGE_H_

#include "MemManager.h"
#include "sys/types.h"

class MemPage : public MemManager
{
public:
	MemPage();
	virtual ~MemPage();
	void Init(unsigned char count);
	// create a share memory with a key , size in bytes
	void CreateShare(key_t key, size_t size);
	// open share memory with a key
	void Open(key_t key,size_t size);
private:
	int page_key;
};

#endif /* MEMPAGE_H_ */
