/*
 * ShareBlock.cpp
 *
 *  Created on: 30 Jul 2013
 *      Author: lester
 */

#include "ShareBlock.h"
#include "string.h"

ShareBlock::ShareBlock()
{


}

ShareBlock::~ShareBlock()
{

}

void ShareBlock::descFill(struct _block_desc *pdesc, unsigned int data_ID, unsigned short size, unsigned short type, void* val, unsigned short max, unsigned short* count)
{
	memset(pdesc, 0, sizeof(*pdesc));
	pdesc->id = data_ID;
	pdesc->size = size;
	pdesc->type = type;
	pdesc->val = val;
	pdesc->max_count = max;
	pdesc->pcount = count;
}

/*!
 Create a block of data using descriptors,
 check how long block will be
 loop into descriptor and put data into block buffer.
 */
void ShareBlock::blockFromStruct(struct _block_desc *pdesc, unsigned short count, struct _block* block, unsigned int max_size)
{

	unsigned short i;
	unsigned short val_size;		// real size in bytes value store in data
	unsigned int tot_size;

	struct _data* data;
	struct _block_desc *desc = pdesc;

	/*!
	 Get all necessary size to store data from structure
	 Use size * element count for pointer
	 size * ( count OR max if count is not supplied )
	 */
	tot_size = sizeof(*block) - sizeof(block->data);
	for (i = 0, pdesc = desc; i < count; i++, pdesc++)
	{
		tot_size += (sizeof(block->data) - sizeof(data->val));

		// Array type
		if (pdesc->type & ARRAY)
		{
			if (!pdesc->pcount)
				tot_size += pdesc->size * pdesc->max_count;
			else
				tot_size += pdesc->size * *pdesc->pcount;
		} else if (pdesc->type & POINTER)
		// Pointer type
		{
			if (!pdesc->pcount)
				return;			//!< Error, NULL is no valid for
			tot_size += pdesc->size * *pdesc->pcount;
		} else if (pdesc->type & PRIMITIVE)
		{
			tot_size += (pdesc->size);
		} else
		{
			// unknown type
		}

		if (tot_size & (sizeof(int) - 1))
			tot_size = (tot_size + sizeof(int)) & (~(sizeof(int) - 1));
	}
	if (max_size < tot_size)
		return;

	memset(block, 0, sizeof(*block));
	block->size = OFFSETOF(struct _block,data);

	for (i = 0, pdesc = desc; i < count; i++, pdesc++)
	{
		data = (struct _data*) (((unsigned char*) block) + block->size);
		data->type = pdesc->type;
		data->size = pdesc->size;
		val_size = data->size;

		// pointer or array
		if (pdesc->type & ARRAY)
		{
			if (!pdesc->pcount)
				val_size = data->size * pdesc->max_count;
			else
				val_size = data->size * *pdesc->pcount;
		} else if (pdesc->type & POINTER)
		{
			if (!pdesc->pcount)
				return;			//!< Error, NULL is no valid for
			val_size = data->size * *pdesc->pcount;
			block->asize += val_size;
		}

		// smaller data size most be same that an integer, because memory alignment is necessary
		if (data->size <= sizeof(int))
		{
			data->val = *((int *) (pdesc->val));
		} else
		{
			//Unknown data type
			memcpy(&data->val, pdesc->val, val_size);
		}
		// another data with size > integer
		block->size += sizeof(struct _data) - sizeof(data->val) + val_size;
		if (block->size & (sizeof(int) - 1))
			block->size = (block->size + sizeof(int)) & (~(sizeof(int) - 1));
	}

}

/*
 Starting with first data position until reach the size of the block
 Read data from block, look for data id on description structure (more than one data with same description is allowed)
 */
void ShareBlock::structFromBlock(struct _block_desc *pdesc, unsigned short count, struct _block* block)
{
	void *max = (char*) block + block->size;
/*
	unsigned short i;
	unsigned short val_size;		// real size in bytes value store in data
	unsigned int tot_size;
	*/

	struct _data* data;

	data = block->data;
	while (data < max)
	{
		// look at descriptor using id

	}
}
