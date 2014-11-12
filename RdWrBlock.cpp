/*
 * RdWrBlock.cpp
 *
 *  Created on: 5 Sep 2013
 *      Author: lester
 */

#include "RdWrBlock.h"
#include "log.h"

RdWrBlock::RdWrBlock()
{
	wr_pos = 0;
	block = 0;
	size = 0;
	rd_pos = 0;
}

void RdWrBlock::Init(void* mem, unsigned short size)
{
	block = (unsigned char*) mem;
	this->size = size;
	rd_pos = 0;
	wr_pos = 0;
}

RdWrBlock::~RdWrBlock()
{

}

void RdWrBlock::getWriteBuffer(unsigned char* &buffer, unsigned short &size)
{
	if (!block) throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
	if (rd_pos >= wr_pos)
	{
		wr_pos = 0;
		rd_pos = 0;
	}
	buffer = &block[wr_pos];
	size = this->size - wr_pos;
}

void RdWrBlock::getReadBuffer(unsigned char* &buffer, unsigned short &size)
{
	if (wr_pos <= rd_pos)
		if (!block) throw error_api(ERROR_INFO(),api_error::get_eof());
	buffer = &block[rd_pos];
	size = wr_pos - rd_pos;
}
