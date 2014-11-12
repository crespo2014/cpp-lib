/*
 * Matrix.h
 *
 *  Created on: 4 Jun 2014
 *      Author: lester
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <stdint.h>
/*
 * One dimension matrix
 */
template<typename T>
class Matrix1D
{
public:
	Matrix1D()
	{

	}
	~Matrix1D()
	{

	}
	void setSize(uint16_t count)
	{
		data.setSize(count);
	}
	void Expand(uint8_t count)
	{
		data.SetSize(data.size);
	}
private:
	std::vector<T> data;
};

template<typename T>
class Matrix2D
{

};

/*
 * 2 Dimensions matrix with bool is done using std::bitset<16>
 *
 * each row will return the first bitset
 *
 * Matrix ( rows , columns set), ::columnset_size
 * [] -> column set
 *  [] -> bool ref value
 *
 *  for each row
 *   while not last column
 *     get column set,
 *     jump to next
 *
 */
template<>
class Matrix2D<bool>
{
public:
	Matrix2D(uint16_t m) :
			m(m), row_size((m + 7) / 8)
	{
		reserve = row_size * m * 2;
		d = new uint8_t[reserve];
	}
	~Matrix2D()
	{
		delete d;
	}
	void add(uint16_t count = 1)

	{

	}

	class value
	{
		friend Matrix2D<bool> ;
		operator bool() const
		{
			return ((*d & mask) != 0);
		}
		bool operator =(bool b)
		{
			if (b)
				*d |= mask;
			else
				*d &= ~mask;
			return b;
		}
		bool operator *() const
		{
			return ((*d & mask) != 0);
		}
	private:
		value(uint8_t *d, uint8_t mask) :
				d(d), mask(mask)
		{

		}
		uint8_t * const d;
		uint8_t const mask;
	};
	class row
	{
		friend Matrix2D<bool> ;
	public:
		value operator [](uint16_t column)
		{
			if (column >= count)
				return
				{	0,0 };
			return
			{ d + column / 8,uint8_t (column %8)};
		}
	private:
		row(uint8_t * d, uint16_t count) :
				d(d), count(count)
		{

		}
		uint8_t * const d;
		uint16_t const count;
	};
	row operator [](uint16_t row)
	{
		if (row >= m)
		{
			return
			{	0,0};
		}
		return
		{	d + (row * row_size),m};
	}
private:
	uint16_t m;	//matrix dimension
	uint16_t reserve;
	uint16_t row_size;
	uint8_t *d;
};

#endif /* MATRIX_H_ */
