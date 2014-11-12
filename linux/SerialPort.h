/*
 * SerialPort.h
 *
 *  Created on: Sep 16, 2013
 *      Author: lcrespo
 */

#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include "fcntl.h"
#include "termios.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"
#include <poll.h>
#include "Buffer.h"
#include "iobase.h"

using namespace io;

class SerialPort: io_base
{
public:
	SerialPort();
	virtual ~SerialPort();
	// last parameter is interval delay between bytes
	void open(unsigned char id, unsigned int baud, unsigned char data_bit, unsigned char stop_bit, const char parity,
			unsigned char tenthsSecondDelay);
	//
	unsigned short read(void* buffer, unsigned short max_size, unsigned short &size);
	// wait for data incoming in serial port
	unsigned short waitData(int mstimeout);
	//
	void  setInterByteDelay(unsigned char tenthsSecond);
	void close();
private:
	void write(void* data, unsigned short size);
	//
	void read(void* &data, unsigned short &size);
	void updateRead(unsigned short count);

	int fd;    //file  descriptor
	unsigned char rd_buff[255];
	unsigned short rd_pos;			// client is reading from this point
	unsigned short rd_wr_pos;		// class is written from this point

public:

};

#endif /* SERIALPORT_H_ */
