/*
 * RdWrBlock.h
 *
 *  Created on: 5 Sep 2013
 *      Author: lester
 */

#ifndef RDWRBLOCK_H_
#define RDWRBLOCK_H_

#include "log.h"

class RdWrBlock
{
public:
	RdWrBlock();
	virtual ~RdWrBlock();
	void Init(void* mem, unsigned short size);
	inline void updateWritePosition(unsigned short count)
	{
		if (wr_pos + count > size)
			wr_pos = size;
		else
			wr_pos += count;
		//log("read %d write %d",rd_pos,wr_pos)
	}
	inline void updateReadPosition(unsigned short count)
	{
		rd_pos += count;
		//log("read %d write %d",rd_pos,wr_pos)
	}
	inline bool isEmpty()
	{
		return (rd_pos == wr_pos);
	}
	inline void clear()
	{
		if (rd_pos != wr_pos)
		{
			log_d("Discarding %d bytes",wr_pos-rd_pos);
			//log_buff("Discarded: ",&block[rd_pos],wr_pos - rd_pos);
			rd_pos = wr_pos;
			// event most be clear
		}

	}
	void getWriteBuffer(unsigned char* &buffer, unsigned short &size);
	void getReadBuffer(unsigned char* &buffer, unsigned short &size);
private:
	unsigned short size;
	unsigned char *block;
	unsigned short wr_pos;
	unsigned short rd_pos;
};

#endif /* RDWRBLOCK_H_ */
