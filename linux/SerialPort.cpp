/*
 * SerialPort.cpp
 *
 *  Created on: Sep 16, 2013
 *      Author: lcrespo
 */

#include "SerialPort.h"
#include "fcntl.h"
#include "termios.h"
#include "string.h"
#include "unistd.h"
#include "errno.h"
#include <poll.h>
#include "log.h"

SerialPort::SerialPort()
{
	rd_pos = 0;
	rd_wr_pos = 0;
}

SerialPort::~SerialPort()
{
	close();
}

void SerialPort::close()
{
	if (fd != -1)
	{
		::close(fd);
		onDisconnect();
	}
}

void SerialPort::open(unsigned char id, unsigned int baud, unsigned char data_bit, unsigned char stop_bit, const char parity,
		unsigned char tenthsSecondDelay)
{
	char fname[20];
	sprintf(fname, "/dev/ttyS%d", id);
	fd = ::open(fname, O_RDWR | O_NOCTTY | /*O_SYNC*/O_NONBLOCK);

	if (fd == -1) throw uexception::error_api(ERROR_INFO());

	/* make fd asynchronous */
	::fcntl(fd, F_SETFL, FASYNC);

	onConnected(fd);
	struct termios old_tios, tios;
	speed_t speed;

	/* Save */
	tcgetattr(fd, &(old_tios));

	memset(&tios, 0, sizeof(struct termios));

	/* C_ISPEED     Input baud (new interface)
	 C_OSPEED     Output baud (new interface)
	 */
	switch (baud)
	{
	case 110:
		speed = B110;
		break;
	case 300:
		speed = B300;
		break;
	case 600:
		speed = B600;
		break;
	case 1200:
		speed = B1200;
		break;
	case 2400:
		speed = B2400;
		break;
	case 4800:
		speed = B4800;
		break;
	case 9600:
		speed = B9600;
		break;
	case 19200:
		speed = B19200;
		break;
	case 38400:
		speed = B38400;
		break;
	case 57600:
		speed = B57600;
		break;
	case 115200:
		speed = B115200;
		break;
	default:
		speed = B9600;
		log_e("WARNING Unknown baud rate %d for %s (B9600 used)", baud, fname);

	}
	if ((cfsetispeed(&tios, speed) < 0) || (cfsetospeed(&tios, speed) < 0))
	{
		close();
		throw uexception::error_api(ERROR_INFO());
	}

	/* C_CFLAG      Control options
	 CLOCAL       Local line - do not change "owner" of port
	 CREAD        Enable receiver
	 */
	tios.c_cflag |= (CREAD | CLOCAL);
	/* CSIZE, HUPCL, CRTSCTS (hardware flow control) */

	/* Set data bits (5, 6, 7, 8 bits)
	 CSIZE        Bit mask for data bits
	 */
	tios.c_cflag &= ~CSIZE;
	switch (data_bit)
	{
	case 5:
		tios.c_cflag |= CS5;
		break;
	case 6:
		tios.c_cflag |= CS6;
		break;
	case 7:
		tios.c_cflag |= CS7;
		break;
	case 8:
	default:
		tios.c_cflag |= CS8;
		break;
	}

	/* Stop bit (1 or 2) */
	if (stop_bit == 1)
		tios.c_cflag &= ~ CSTOPB;
	else
		/* 2 */
		tios.c_cflag |= CSTOPB;

	/* PARENB       Enable parity bit
	 PARODD       Use odd parity instead of even */
	if (parity == 'N')
	{
		/* None */
		tios.c_cflag &= ~ PARENB;
	} else if (parity == 'E')
	{
		/* Even */
		tios.c_cflag |= PARENB;
		tios.c_cflag &= ~ PARODD;
	} else
	{
		/* Odd */
		tios.c_cflag |= PARENB;
		tios.c_cflag |= PARODD;
	}

	/* Raw input */
	tios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	if (parity == 'N')
	{
		/* None */
		tios.c_iflag &= ~INPCK;
	} else
	{
		tios.c_iflag |= INPCK;
	}

	/* Software flow control is disabled */
	tios.c_iflag &= ~(IXON | IXOFF | IXANY);

	/* C_OFLAG      Output options
	 OPOST        Postprocess output (not set = raw output)
	 ONLCR        Map NL to CR-NL

	 ONCLR ant others needs OPOST to be enabled
	 */

	/* Raw ouput */
	tios.c_oflag &= ~ OPOST;

	// read max data with a 10ms inter byte timeout
	tios.c_cc[VMIN] = 255;		// block until received n chars or time expired
	tios.c_cc[VTIME] = tenthsSecondDelay;		// tenths of a second elapses between bytes

	if (tcsetattr(fd, TCSANOW, &tios) < 0)
	{
		close();
		throw uexception::error_api(ERROR_INFO());
	}
}

void SerialPort::write(void* buffer, unsigned short size)
{
	if (fd == -1) throw uexception::error_api(ERROR_INFO(), api_error::get_close());

	int ir = ::write(fd, buffer, size);
	if (ir < 0)
	{
		log_e("error written data code : %d", errno);

	}
	//logHexBuff(buffer, size,"serial send ");

}
unsigned short SerialPort::read(void* buffer, unsigned short max_size, unsigned short &size)
{
	if (fd == -1) throw uexception::error_api(ERROR_INFO(), api_error::get_close());
	int ir = ::read(fd, buffer, max_size);
	if (ir < 0)
	{
		log_e("error readding data code : %d", errno);

	}
	log_buff("serial rec ", buffer, ir);
	size = ir & 0xFFFF;

}

unsigned short SerialPort::waitData(int msTimeout)
{
	struct pollfd poll_fd;
	poll_fd.fd = fd;
	poll_fd.events = POLLIN | POLLERR;    // if 0 fd won't be check for events
	int ir = poll(&poll_fd, 1, msTimeout);
	if (ir < 0)
	{
		log_e("poll failed with code %d", errno);

	}

	return 0;
}

void SerialPort::read(void* &data, unsigned short &size)
{
	//if (read(rd_buff, sizeof(rd_buff), size) != NO_ERR) return ERR_UNKNOWN;
	data = rd_buff;
	//return NO_ERR;
}

void SerialPort::updateRead(unsigned short count)
{
	rd_pos += count;
}

void SerialPort::setInterByteDelay(unsigned char tenthsSecond)
{
	//return ERR_NO_IMPLEMENT;
}


