/*
 * EventFile.h
 *
 *  Created on: 5 Sep 2013
 *      Author: lester
 */

#ifndef EVENTFILE_H_
#define EVENTFILE_H_
/*
 Event file it is a file descriptor that store a 8byte value
 write and read operation must be use with 8 byte buffer
 file descriptor support poll operation.

 read operation will block if value reach 0
 after read value will be zero or minus one, it depend on file mode.

 a semaphore file will be create, to avoid multiple read operation.
 */
class EventFile
{
public:
	EventFile();
	virtual ~EventFile();
	void init();	// create file descriptor
	void set();		// write to file, a read event will trigger
	void reset();	// clear file event
	bool waitRead(int mstimeout = -1);	// use -1 to infinite
	void release();
	inline int getfd() { return fd; };
private:
	int fd;
};

#endif /* EVENTFILE_H_ */
