/*
 * ShareBlock.h
 *
 *  Created on: 30 Jul 2013
 *      Author: lester
 */

#ifndef SHAREBLOCK_H_
#define SHAREBLOCK_H_

#include "stdio.h"

/*!

 Main idea about share data across application.

 data must be serialize or converted to a block
 block most be simple

 Information to include on data block

 Total size of data.
 Size of dynamic allocated data. to bring possibility of preallocated data and use some allocator

 Important information

 Name | Size | description
 INDEX	 2   next available index to store a data struct, index*sizeof(data struct) is the total size of block
 ASIZE   2   total Allocated size to store pointer ,but array data will not include, because it will store on a fixed max size array
 ID      2     Data identification, data type can be explicit assumed
 TYPE    2     Data type
 char,   c8
 uchar,  uc8
 short,  s16
 ushort, us16
 int,    i32
 uint,   ui32
 byte*   u8p   // size will be precedent
 byte[]  u8a   // size will be next
 SIZE | 2 |  data size,  element count  for pointer and array
 DATA | x |

 alignment is required for ID

 struct {
 unsigned int32 size;	// total size and allocate size
 unsigned int32 id;		// data id
 unsigned int32 type     // type and size if necessary
 union {
 char int8;
 unsigned char uint8;
 short int16;
 unsigned short uint16;
 byte uint8a;
 }
 // next structure must be alignment

 */

/*!
 To store data in a block struct
 total size must be calculated at beginner  and check that it is available to store struct. if it is not then another block must be allocate.
 */

#define TYP_SHIFT	3
#define SHIFT_1		0
#define PRIMITIVE	(1 << SHIFT_1)
#define ARRAY		(2 << SHIFT_1)
#define POINTER		(4 << SHIFT_1)

#define TYP_FLOAT		(1 << TYP_SHIFT) | PRIMITIVE
#define TYP_DOUBLE		(2 << TYP_SHIFT) | PRIMITIVE
#define TYP_INT8		(3 << TYP_SHIFT) | PRIMITIVE
#define TYP_CHAR		(3 << TYP_SHIFT) | PRIMITIVE
#define TYP_UINT8		(4 << TYP_SHIFT) | PRIMITIVE
#define TYP_BYTE		(4 << TYP_SHIFT) | PRIMITIVE
#define TYP_INT16		(5 << TYP_SHIFT) | PRIMITIVE
#define TYP_WORD		(6 << TYP_SHIFT) | PRIMITIVE
#define TYP_UINT16		(6 << TYP_SHIFT) | PRIMITIVE
#define TYP_INT32		(7 << TYP_SHIFT) | PRIMITIVE
#define TYP_UINT32		(8 << TYP_SHIFT) | PRIMITIVE
#define TYP_DWORD		(8 << TYP_SHIFT) | PRIMITIVE
#define TYP_INT8_A		(9 << TYP_SHIFT) | ARRAY
#define TYP_INT8_P		(10 << TYP_SHIFT) | POINTER
#define TYP_UINT8_A		(11 << TYP_SHIFT) | ARRAY
#define TYP_UINT8_P		(12 << TYP_SHIFT) | POINTER
#define TYP_UINT16_A	(13 << TYP_SHIFT) | ARRAY
#define TYP_UINT16_P	(14 << TYP_SHIFT) | POINTER
#define TYP_UINT32_A	(15 << TYP_SHIFT) | ARRAY
#define TYP_UINT32_P	(16 << TYP_SHIFT) | POINTER
#define TYP_INT16_A		(17 << TYP_SHIFT) | ARRAY
#define TYP_INT16_P		(18 << TYP_SHIFT) | POINTER
#define TYP_INT32_A		(19 << TYP_SHIFT) | ARRAY
#define TYP_INT32_P		(20 << TYP_SHIFT) | POINTER
#define TYP_FLOAT_A		(21 << TYP_SHIFT) | ARRAY
#define TYP_FLOAT_P		(22 << TYP_SHIFT) | POINTER
#define TYP_DOUBLE_A	(23 << TYP_SHIFT) | ARRAY
#define TYP_DOUBLE_P	(24 << TYP_SHIFT) | POINTER

#define OFFSETOF(type, field)    ((unsigned long) &(((type *) 0)->field))

/*!
 Struct to read value from data without typecast
 */

struct _val
{
	union
	{
		float f;
		double d;
		char int8;
		unsigned char uint8;
		short int16;
		unsigned short uint16;
		int int32;
		unsigned uint32;
		char int8a[1];
		unsigned char uint8a[1];
		short int16a[1];
		unsigned short uint16a[1];
		int int32a[1];
		unsigned int uint32a[1];
	};
};

/*!
 Description structure
 it is necessary to convert from structure to a block of data and in reverse direction too.
 */

struct _block_desc
{
	unsigned int id;			//!< data id
	unsigned short type;
	unsigned short size;		//!< element size
	void* val;					//!< stored value	offset of value in structure
	unsigned short max_count;	//!< for array element it is the max element count
	unsigned short *pcount;		//!< when reading data of type pointer or array it will store element count, (if NULL in array element max_count will be use)
};

/*
 Data holding structure
 */
struct _data
{
	unsigned int id;			//!< unique id  data
	unsigned short type;		//!< data type
	unsigned short size;		//!< data size or count element in array or pointer mode
	unsigned int val;			// it is not really an integer, it is the best manner to use the less space possible with alignment
};

/*!
 size over 65535 must be checked
 */
struct _block
{
	unsigned short size;		//!< size of block, alignment position to use to store next data
	unsigned short asize;		//!< total allocated size , array data does not increment this size, only pointer
	struct _data data[1];		//!< first data available
};

class ShareBlock
{
public:
	ShareBlock();
	virtual ~ShareBlock();

	static void blockFromStruct(struct _block_desc *pdesc, unsigned short count, struct _block* block, unsigned int max_size);
	static void structFromBlock(struct _block_desc *pdesc, unsigned short count, struct _block* block);

	//! definition of data
	static inline void descSet(struct _block_desc *pdesc, unsigned int data_ID, unsigned int* value)
	{
		descFill(pdesc, data_ID, sizeof(*value), TYP_UINT32, value, 1);
	}
	;
	static void desc_set(struct _block_desc *pdesc, unsigned int data_ID, unsigned char* value)
	{
		descFill(pdesc, data_ID, sizeof(*value), TYP_UINT32, value, 1);
	}
	;
	static void desc_set(struct _block_desc *pdesc, unsigned int data_ID, unsigned short* value)
	{
		descFill(pdesc, data_ID, sizeof(*value), TYP_UINT32, value, 1);
	}
	;
	static void desc_set(struct _block_desc *pdesc, unsigned int data_ID, int* value)
	{
		descFill(pdesc, data_ID, sizeof(*value), TYP_UINT32, value, 1);
	}
	;
	static void desc_set(struct _block_desc *pdesc, unsigned int data_ID, short* value)
	{
		descFill(pdesc, data_ID, sizeof(*value), TYP_UINT32, value, 1);
	}
	;
	static void desc_set(struct _block_desc *pdesc, unsigned int data_ID, char* value)
	{
		descFill(pdesc, data_ID, sizeof(*value), TYP_UINT32, value, 1);
	}
	;
	static void desc_set(struct _block_desc *pdesc, unsigned int data_ID, float* value)
	{
		descFill(pdesc, data_ID, sizeof(*value), TYP_UINT32, value, 1);
	}
	;
	static void desc_set(struct _block_desc *pdesc, unsigned int data_ID, double* value)
	{
		descFill(pdesc, data_ID, sizeof(*value), TYP_UINT32, value, 1);
	}
	;

	// For pointer elements counter must be use
	// for array this can be optional
	static inline void desc_set_array(struct _block_desc *pdesc, unsigned int data_ID, unsigned short max, float* array, unsigned short* count = NULL)
	{
		descFill(pdesc, data_ID, sizeof(*array), TYP_FLOAT_A, array, max, count);
	}
	;
	static inline void desc_set_array(struct _block_desc *pdesc, unsigned int data_ID, unsigned short max, char* array, unsigned short* count = NULL)
	{
		descFill(pdesc, data_ID, sizeof(*array), TYP_INT8_A, array, max, count);
	}
	;
	static inline void desc_set_array(struct _block_desc *pdesc, unsigned int data_ID, unsigned short max, unsigned char* array, unsigned short* count = NULL)
	{
		descFill(pdesc, data_ID, sizeof(*array), TYP_UINT8_A, array, max, count);
	}
	;
	static inline void desc_set_array(struct _block_desc *pdesc, unsigned int data_ID, unsigned short max, short* array, unsigned short* count = NULL)
	{
		descFill(pdesc, data_ID, sizeof(*array), TYP_INT16_A, array, max, count);
	}
	;
	static inline void desc_set_array(struct _block_desc *pdesc, unsigned int data_ID, unsigned short max, unsigned short* array, unsigned short* count = NULL)
	{
		descFill(pdesc, data_ID, sizeof(*array), TYP_UINT16_A, array, max, count);
	}
	;
	static inline void desc_set_array(struct _block_desc *pdesc, unsigned int data_ID, unsigned short max, int* array, unsigned short* count = NULL)
	{
		descFill(pdesc, data_ID, sizeof(*array), TYP_INT32_A, array, max, count);
	}
	;
	static inline void desc_set_array(struct _block_desc *pdesc, unsigned int data_ID, unsigned short max, unsigned int* array, unsigned short* count = NULL)
	{
		descFill(pdesc, data_ID, sizeof(*array), TYP_UINT8_A, array, max, count);
	}
	;
	static inline void desc_set_array(struct _block_desc *pdesc, unsigned int data_ID, unsigned short max, double* array, unsigned short* count = NULL)
	{
		descFill(pdesc, data_ID, sizeof(*array), TYP_DOUBLE_A, array, max, count);
	}
	;

private:
	// Fill description structure
	static void descFill(struct _block_desc *pdesc, unsigned int data_ID, unsigned short size, unsigned short type, void* val, unsigned short max, unsigned short* count = NULL);
};

#endif /* SHAREBLOCK_H_ */
