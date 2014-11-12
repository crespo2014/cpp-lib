/*
 * Page.h
 *
 *  Created on: 19 Jun 2014
 *      Author: lester.crespo
 */

#ifndef PAGE_H_
#define PAGE_H_

class Page
{
public:
	Page();
	virtual ~Page();
	static Page* Page::create(unsigned int size)
	{
		return nullptr;
	}
	void release();

	Page* next;
	unsigned int size;

};

#endif /* PAGE_H_ */
