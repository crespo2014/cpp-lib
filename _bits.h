/*
 * _bits.h
 *
 *  Created on: 10 Jun 2014
 *      Author: lester
 */

#ifndef BITS_H_
#define BITS_H_

/*
 * This file contains class use to optimize vector or arrays of bits
 *
 * bit iterator is made of
 * 	bits* start
 * 	uint* mask.	     current bit position.
 *   --- no --- uint* max_mask.  use for the last chunk of sequence, next chunk never pass this mask.
 *  --- use parent matrix to go next chunk
 *
 *
 *  check a chunk for one bit
 *  Chunk is a object containing a constant number of sub-elements
 */

template<class B>
class _bit_it
{
	B* start;
	uint8_t mask;	// max chunk of 255 bits
public:
	_bit_it(B* s, uint8_t m = 1) :
			start(s), mask(m)
	{

	}
	_bit_it<B>& operator ++()
	{
		if ((mask <<= 1) == (1 << size() ))
		{
			mask = 1;
			start++;
		}
		return *this;
	}
	/*
	 * Get count of elements per chunk
	 */
	static constexpr uint8_t size()
	{
		return sizeof(B)*8;
	}
	/*
	 * Check if element is not zero
	 */
	bool any()
	{
		return (*start != 0);
	}
};

#endif /* BITS_H_ */
