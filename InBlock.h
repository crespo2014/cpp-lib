/*
 * InBlock.h
 *
 *  Created on: 16 Apr 2014
 *      Author: lester
 */

#ifndef INBLOCK_H_
#define INBLOCK_H_

/*
 * input block
 * Use to cache data read from device.
 * For parsing proporse the parser will use mark to this buffer to avoid copy data to temporal location
 *
 * setOrigin(iterator)  function will be use to
 */
class InBlock {

	char* data = nullptr;			// ioblock
	char* origin;
	char* last;
	unsigned int size;

public:
	InBlock() :
			origin(data), last(data), size(0) {
	}
	~InBlock() {

	}
	class iterator {
		friend class InBlock;
		iterator(char* pos) :
				pos(pos) {
		}
		//InBlock* block = nullptr;
		char* pos;
	public:
		iterator & operator ++() {
			++pos;
			return *this;
		}
		char &operator *() {
			return *pos;
		}
		// convert iterator to char *
		operator const char*() const {
			return pos;
		}
		bool operator ==(const iterator& it) const {
			return (pos == it.pos);
		}
		bool operator !=(const iterator& it) const {
			return (pos != it.pos);
		}
		bool operator >(const iterator& it) const {
			return (pos > it.pos);
		}
		iterator operator+(int i) {
			return {pos + i};
		}
		int operator-(const iterator& it) {
			return pos - it.pos;
		}

	};
	/*
	 * set origin will do nothing until more data is needed
	 * iterator will be updated on read operation on block
	 *
	 * read file to block
	 * start iterator until reach end, set origin, read more data, continue processing
	 */
	void setOrigin(const iterator& it) {
		origin = it.pos;
	}
	const iterator end() const {
		return last;
	}
	iterator begin() {
		return {origin};
	}
	void updateRead(const iterator& it) {
		origin = it.pos;
	}
	/*
	 * Compact data, moving origin to offset zero
	 * update iterator.
	 * request for new data.
	 */
	void read(iterator & it) {
		// compact and read new data
	}
};

#endif /* INBLOCK_H_ */
