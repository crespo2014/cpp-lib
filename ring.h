/*
 * ring.h
 *
 *  Created on: 11 Oct 2013
 *      Author: lester
 *
 *  Template class to implement a ring or circular buffer
 *  Memory to hold buffer will be supply by external component
 *  in general a share memory segment will be use
 *  this class can be a server,that put data, or a customer , that read data.
 *  the server never stop written data, if ring is full oldest data will be overwritten
 *  customer most be quickly enough to read all server incoming data
 *
 *  customer will validate for overwritten, then read data ,and then validate again
 *
 *  a ring loop value is use to known if write and read position are in the same ring.
 *  server start written on loop 0 position 0, when last element of ring is reach then it got to loop 1, position 0
 *  a reader start reading on the same loop that writer,
 *  or can read a previous loop + n element ahead if write loop is not 0
 *
 */

#ifndef RING_H_
#define RING_H_

/*
 * Producer consumer ring.
 * TODO on lost of synchronization, then start from begging of buffer again
 */
template<typename D>

class Ring
{
	struct _ring_head
	{
		//unsigned short flag;
		unsigned short data_count;			// how many element in this memory
		unsigned short element_size;		// element size to check
		volatile unsigned short wr_loop;	// write loop index
		volatile unsigned short wr_pos;		// write pos
		D data[1];
	};
public:
	Ring()
	{
		rd_loop = 0;
		rd_pos = 0;
		writeMode = false;
		ring = 0;
	}
	bool isOnline() {
		return (ring != 0);
	}
	/*
	 Initialize a memory block to be use as ring
	 */
	unsigned short create(void* mem, unsigned short size)
	{
		ring = (struct _ring_head*) mem;
		ring->element_size = sizeof(D);
		ring->data_count = (size - sizeof(struct _ring_head)) / sizeof(D) + 1;
		// initialize write iterator
		writeMode = true;
		ring->wr_loop = 0;
		ring->wr_pos = 0;
		return NO_ERR;
	}
	/*
	 Initialize class to use to read data from ring
	 */
	void connect(void* mem)
	{
		//CHECK_RET_CODE(mem, ERR_WRONG_PARAM);
		if (sizeof(D) != ((struct _ring_head * ) mem)->element_size);
				throw error_api(ERROR_INFO(),api_error::get_wrong_param);

		// attach to ring
		ring = (struct _ring_head *) mem;
		writeMode = false;
		rd_loop = ring->wr_loop;
		rd_pos = ring->wr_pos;

	}
	/*!
	 seek read iterator to older block
	 look for the older fill block
	 if block is not found, then block 0 will be returned
	 */
	unsigned int SeekRead()
	{
		// check for close ring
		CHECK_RET_CODE(ring, ERR_CLOSE);
		CHECK_RET_CODE(!writeMode, ERR_CLOSE);
		rd_loop = ring->wr_loop;
		rd_pos = ring->wr_pos;
		return NO_ERR;
	}
	/*!
	 Customer call this function to get data from ring

	 Check block for overwritten
	 Check available data
	 Read data
	 Check again block for overwritten  ( id is the first value modified by server when overwritten happen).

	 move to next read position.
	 jump to next block if end of this one is reached
	 */
	unsigned short pop(D &val)
	{
		// check for close ring
		CHECK_RET_CODE(ring, ERR_CLOSE);
		CHECK_RET_CODE(!writeMode, ERR_CLOSE);
		// check overwritten
		CHECK_RET_CODE((rd_loop == ring->wr_loop) || ((rd_loop + 1 == ring->wr_loop) && (rd_pos > ring->wr_pos)), ERR_OVERWRITTEN);
		// check for available
		if (rd_pos == ring->wr_pos) return ERR_NO_MORE;
		// get data and go to next
		val = ring->data[rd_pos];
		// check overwritten
		CHECK_RET_CODE((rd_loop == ring->wr_loop) || ((rd_loop + 1 == ring->wr_loop) && (rd_pos > ring->wr_pos)), ERR_OVERWRITTEN);
		rd_pos++;
		if (rd_pos == ring->data_count)
		{
			rd_pos = 0;
			rd_loop++;
		}
		return NO_ERR;
	}

	//! Write data to ring
	unsigned short push(D &val)
	{
		// check for close ring
		CHECK_RET_CODE(ring, ERR_CLOSE);
		CHECK_RET_CODE(writeMode, ERR_CLOSE);
		ring->data[ring->wr_pos] = val;
		ring->wr_pos++;
		if (ring->wr_pos == ring->data_count)
		{
			ring->wr_pos = 0;
			ring->wr_loop++;
		}
		return NO_ERR;
	}
private:
	bool writeMode;
	unsigned short rd_loop;	// loop index
	unsigned short rd_pos;
	struct _ring_head* ring;

};

#endif /* RING_H_ */
