/*
 * SignalFile.h
 *
 *  Created on: 5 Sep 2013
 *      Author: lester
 */

#ifndef SIGNALFILE_H_
#define SIGNALFILE_H_

#include "SignalFile.h"
#include <sys/signalfd.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <string.h>
#include "exception_base.h"

/*
 This class create a signal file
 a file descriptor to be signaled for read write operation
 */
class SignalFile
{
public:
	SignalFile()
	{
		sigset_t mask;
		/* We will handle SIGIO a*/
		sigemptyset(&mask);
		sigaddset(&mask, SIGIO);

		/* Block the signals thet we handle using signalfd(), so they don't
		 * cause signal handlers or default signal actions to execute. */
		if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
		{
			throw error_api(ERROR_INFO());
		}
		/* Create a file descriptor from which we will read the signals. */
		fd = signalfd(-1, &mask, 0);
		if (fd < 0)
		{
			throw error_api(ERROR_INFO());
		}
	}
	void read()
	{
		struct signalfd_siginfo si;

		ssize_t res;

		res = ::read(fd, &si, sizeof(si));

		if (res < 0)
		{
			throw error_api(ERROR_INFO());
		}
		if (res != sizeof(si))
		{
			throw error_api(ERROR_INFO(), api_error::get_eof);
		}
		/*
		 if (si.ssi_signo == SIGTERM)
		 printf("Got SIGTERM\n");
		 else if (si.ssi_signo == SIGINT)
		 {

		 printf("Bye!\n");
		 }
		 else
		 {
		 fprintf(stderr, "Got some unhandled signal\n");
		 return 1;
		 }*/
	}

	~SignalFile()
	{
	}

	int getfd() const
	{
		return fd;
	}
private:
	os::fd_type fd;
};

#endif /* SIGNALFILE_H_ */
