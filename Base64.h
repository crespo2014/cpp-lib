/*
 * Base64.h
 *
 *  Created on: 3 Sep 2013
 *      Author: lester
 */

#ifndef BASE64_H_
#define BASE64_H_

class Base64
{
public:
	Base64(void* out, unsigned short max_size);
	~Base64();
	void encode(const unsigned char* data,unsigned short size);
	void decode(const unsigned char* data,unsigned short size);
	inline unsigned short getSize() { return wr_pos;}
private:
	unsigned char*	wr;
	unsigned short wr_size,wr_pos;
};


#endif /* BASE64_H_ */
