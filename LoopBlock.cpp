/*
 * LoopBlock.cpp
 *
 *  Created on: 1 Aug 2013
 *      Author: lester
 */

#include "LoopBlock.h"
#include "string.h"
#include "time.h"
#include "stdio.h"

/*!
 Head of block
 This structure will be at beginning of all blocks
 ts  		time stamp or block id, use for detect overwritten
 write_pos 	Next position to write in, counting from address of block, this value most be alignment
 val			data will start here,
 */
struct _loopBlock
{
	volatile unsigned int uid;
	volatile unsigned short write_pos;	// next position to write starting in offset of val = (sizeof block - sizeof val)
	int val;							// data will start here alignment of integer
};

#define LOOP_BLOCK_VAL_OFFSET OFFSETOF(struct _loopBlock,val)

LoopBlock::LoopBlock()
{
	block_count = 0;
	pmem = 0;
	esize = 0;
	block_size = 0;
	element_asize = 0;
}
/*!
 Alignment must be checked previous to split
 all block must be initialize
 */
void LoopBlock::Init(void* mem, unsigned short size, unsigned short block_count, unsigned short element_size)
{
	unsigned short i;

	this->block_count = block_count;
	this->pmem = (unsigned char*) mem;
	this->esize = element_size;

	// memory must be divide with alignment
	// align to the less value to avoid overflow
	block_size = size / block_count;
	block_size &= ~(sizeof(int) - 1);

	element_asize = esize;
	if (element_asize % sizeof(int))
	{
		element_asize += sizeof(int);
		element_asize &= ~(sizeof(int) - 1);
	}

	// Clear all blocks
	for (i = 0; i < block_count; i++)
	{
		((struct _loopBlock *) &pmem[block_size * i])->write_pos = 0;		// there is not data on block
		((struct _loopBlock *) &pmem[block_size * i])->uid = 0;
	}

	// initialize write iterator
	wr_it.block_idx = 0;
	wr_it.pos = LOOP_BLOCK_VAL_OFFSET;
	wr_it.uid = 1;

	((struct _loopBlock *) &pmem[0])->uid = 1;
}

/*!
 Write data inside block structure store size will be use
 */
void LoopBlock::write(void* val)
{
	void* pwr = getWritePtr();
	memcpy(pwr, val, esize);
	writeDone();
}

/*
 Server call this function to request a write position to put data
 check available space left
 go to next block if necessary
 */
void* LoopBlock::getWritePtr()
{
	// check for end of block
	if (wr_it.pos + esize > block_size)
	{
		unsigned short c = wr_it.block_idx;
		next(wr_it);

		//printf("\nServer jump to %d ", wr_it.uid);
		/*!
		 prepare new block for written
		 update uid - not body can use this block because there is another older block, the older block is not release yet
		 */
		struct _loopBlock *pblock = (struct _loopBlock *) &pmem[block_size * wr_it.block_idx];
		pblock->uid = wr_it.uid;
		pblock->write_pos = 0;

		// update previous block, to indicate that there is another new block
		((struct _loopBlock *) &pmem[block_size * c])->write_pos += element_asize;
	}
	return &pmem[block_size * wr_it.block_idx + wr_it.pos];
}

/*
 Server will call this function to consolidate previous write position
 block will be update with position of write iterator
 */
void LoopBlock::writeDone()
{
	wr_it.pos += element_asize;
	((struct _loopBlock *) &pmem[block_size * wr_it.block_idx])->write_pos = wr_it.pos;
}

/*!
 Clients will call this function to get data from loop

 Check block for overwritten
 Check available data
 Read data
 Check again block for overwritten  ( ts is the first value to modify by server when overwritten happen).

 move to next read position.
 jump to next block if end of this one is reached

 */
void LoopBlock::read(struct _block_it& it, void* val, unsigned short size)
{
	//todo switch to error info
	/*
	// Validate input parameters
	if ((it.block_idx >= block_count) || (size != esize))
		return ERR_INVALID_PARAM;

	struct _loopBlock *pblock = (struct _loopBlock *) &pmem[block_size * it.block_idx];

	// check overwritten
	if (it.uid != pblock->uid)
		return ERR_DATA_OVERRIDE;

	// check available data
	if (it.pos >= ((struct _loopBlock *) &pmem[block_size * it.block_idx])->write_pos)
		return ERR_NO_MORE;

	// check end of block and go to next
	if (it.pos + esize > block_size)
	{
		next(it);
		pblock = (struct _loopBlock *) &pmem[block_size * it.block_idx];

		// check overwritten
		if (it.uid != pblock->uid)
			return ERR_DATA_OVERRIDE;

		// check available data
		if (it.pos >= pblock->write_pos)
			return ERR_NO_MORE;
	}

	//read data
	memcpy(val, (unsigned char*) pblock + it.pos, size);

	// check overwritten
	if (it.uid != pblock->uid)
		return ERR_DATA_OVERRIDE;

	// move to next read position
	it.pos += element_asize;
	return NO_ERR;
	*/
}

LoopBlock::~LoopBlock()
{

}

/*!
 Get the older block with data available to read
 the block with less uid is the older
 but if max integer is reached then some block will be lost
 */
unsigned int LoopBlock::getReadBlock(struct _block_it& block)
{
	block.pos = OFFSETOF(struct _loopBlock,val);
	block.uid = ~0;

	unsigned int ts;
	unsigned int i;

	for (i = 0; i < block_count; i++)
	{
		ts = ((struct _loopBlock *) &pmem[block_size * i])->uid;
		if (ts && (ts < block.uid))
		{
			block.uid = ts;
			block.block_idx = i;
		}
	}
	return 0;
}

/*!
 Move iterator to next position
 jump to a need block if there is not space left on the current one

 this function will be use only to jump to next block, movement in the same block will be done with plus
 */
bool LoopBlock::next(struct _block_it &it)
{
	// go to next position
	it.pos += element_asize;

	// check end of block.
	if (it.pos + esize > block_size)
	{
		it.block_idx++;
		it.uid++;
		if (it.block_idx == block_count)
			it.block_idx = 0;
		it.pos = LOOP_BLOCK_VAL_OFFSET;
		return true;
	}
	return false;
}
