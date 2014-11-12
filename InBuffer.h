/*
 * InBuffer.h
 *
 *  Created on: 18 Apr 2014
 *      Author: lester
 */

#ifndef INBUFFER_H_
#define INBUFFER_H_

#include "iobase.h"
#include "Buffer.h"
#include "os.h"

/*
 * Input buffer
 * Expanding a buffer, to read data from source when end of read iterator is reached
 * also allow to adjust read pointer after data has been compacted
 */
class InBuffer: protected io::Buffer
{
	//Data source
	io::io_base& source;
public:
	template<int N>
	explicit InBuffer(io::io_base& dev, io::Block<N> &b) :
			Buffer(b), source(dev)
	{

	}
	// get more data from device
	void readData()
	{
		compact();
		if (!getWSize())
		{
			throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
		}
		source >> *this;
	}
	/*
	 * Get iterator for this buffer
	 */
	Buffer::iterator begin()
	{
		return Buffer::read_begin();
	}
	Buffer::iterator end()
	{
		return Buffer::read_end();
	}
	/*
	 * All iterator must be adjust before execute a read data operation
	 */
	void adjust(Buffer::iterator& it)
	{
		it -= rd_idx;    //(Buffer::read_begin() - Buffer::begin());
	}
	// Set which data must be remain on the buffer after a read operation.
	void setOrigin(const Buffer::iterator& it)
	{
		updateR(it);
	}
};

#endif /* INBUFFER_H_ */
