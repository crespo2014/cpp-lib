/*
 * MemPage.h
 *
 *  Created on: 19 Jun 2014
 *      Author: lester.crespo
 */

#ifndef MEMPAGE_H_
#define MEMPAGE_H_

#include "MemManager.h"

class MemPage  : public MemManager
{
public:
	MemPage();
	virtual ~MemPage();
};

#endif /* MEMPAGE_H_ */
