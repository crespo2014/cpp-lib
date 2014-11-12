/*
 * LoopBlock.h
 *
 *  Created on: 1 Aug 2013
 *      Author: lester
 */

#ifndef LOOPBLOCK_H_
#define LOOPBLOCK_H_

#include "exception_base.h"
/*!
 Use for circular buffer

 A big area of memory will be divide in N groups for get a circular list
 each group will be name as  block
 a block will contain N element

 the server will ask for free element to write

 client will ask for next element to read.

 at beginning all block are uninitialized.
 a block is initialized with a time stamp value to check overriding

 */
/*
enum
{
	ERR_DATA_OVERRIDE = ERR_LAST + 3,	// data has been read but some has been override
	ERR_NO_SPACE_LEFT,					// there is not space for more data, it will never happened on server side,
	ERR_INVALID_PARAM,					// invalid parameters received
	ERR_INVALID_OBJECT_STATUS,			// status of object being readed is not valid
	ERR_HEADER_DATA_IS_MISSING
};
*/

#define OFFSETOF(type, field)    ((unsigned long) &(((type *) 0)->field))

/*!
 block iterator
 structure use as pointer to current read or write
 uid will be last id on write side,
 */
struct _block_it
{
	unsigned short block_idx;		// index to block
	unsigned short pos;				// read or write position
	unsigned int uid;				// block unique id
};

class LoopBlock
{
public:
	LoopBlock();
	void Init(void* mem, unsigned short size, unsigned short block_count, unsigned short element_size);
	virtual ~LoopBlock();

	//! Write data
	void write(void* val);

	//! Get current write position
	void* getWritePtr();

	//! Go to next write position, previous position will be consolidate
	void writeDone();

	//! client will be read data with this function
	void read(struct _block_it& pblock, void* val, unsigned short size);

	/*!
	 look for the older fill block ready to be read
	 if block is not found, then block 0 will be returned

	 better, get next block to current if it is initialize
	 */
	unsigned int getReadBlock(struct _block_it& block);
private:
	/*
	 Move iterator to next position
	 return
	 false if there is space in the same block
	 true  if block was full and jump to next block was done
	 */
	bool next(struct _block_it &it);

	/*!
	 Initialize current block for written.
	 ts will be update any read on this block will be discarded
	 write position will set to 0 indicating that this block has not data to read yet
	 */
	void clearWriteBlock();

	unsigned short esize;			// element size
	unsigned short block_count;		// how many block the entire memory will be divide
	unsigned short block_size;		// size of block in bytes
	unsigned short element_asize;	// element alignment size

	// write iterator
	struct _block_it wr_it;

	unsigned char* pmem;		// pointer to memory
};

#endif /* LOOPBLOCK_H_ */
