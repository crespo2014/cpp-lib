/*
 * log.h
 *
 *  Created on: 21 Apr 2014
 *      Author: lester
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdarg.h>
#include "os.h"

#include "File.h"
#include "MonotonicTime.h"
#include "Buffer.h"
#include "Console.h"

/*
 * Change log
 * v 2.0
 * a buffer need to be use because it will be use with operator <<
 * also to reduce syscall.
 */

/*
 * Available log levels
 */
enum log_level
{
	level_error,	//
	level_warning,
	level_info,
	level_debug
};

class Log;
extern Log &glog;
extern Log* pglog;

class Log
{
	_console console;
	File file;

	bool traceConsole = false;

	// termination version
	void print(io::Buffer& b)
	{
	}

	template<typename T, class ... A>
	void print(io::Buffer& b, const T& t, const A& ... args)
	{
		b << t;
		print(b, args...);
	}

	/*
	void writeTime(io::Buffer& b)
	{
		MonotonicTime t;
		b.updateW(
				snprintf(reinterpret_cast<char*>(b.getW()), b.getWSize(),
						"%u:%02u:%02u.%03u ", t.getH(), t.getM(), t.getS(),
						t.getMs()));
	}
	*/

	Log()
	{

	}
	/*
	 * Write buffer to file and/or console
	 */
	void write(io::Buffer& b)
	{
		if (console)
		{
			console << b.copy();
			console.flush();
		}
		if (file)
		{
			file << b.copy();
			file.flush();
		}
	}
public:
	static Log& get()
	{
		static Log slog;
		return slog;
	}

	/*
	 * Trace a high level message
	 */
	void message(const char* fmt, ...)
	{
		if (!console && !file)
			return;
		io::Block<255> blck;
		io::Buffer b(blck);
		b.dont_throw();

		b << MonotonicTime() << ' ';

		va_list arg_ptr;
		va_start(arg_ptr, fmt);
		b.updateW(
				vsnprintf(reinterpret_cast<char*>(b.getW()), b.getWSize(), fmt,
						arg_ptr));
		va_end(arg_ptr);

		b << '\n';

		write(b);
	}

	void log(log_level lvl, const char* fmt, ...)
	{
		if (!console && !file)
			return;
		io::Block<255> blck;
		io::Buffer b(blck);
		b.dont_throw();
		b << MonotonicTime() << ' ';

		va_list arg_ptr;
		va_start(arg_ptr, fmt);
		b.updateW(
				vsnprintf(reinterpret_cast<char*>(b.getW()), b.getWSize(), fmt,
						arg_ptr));
		va_end(arg_ptr);

		b << '\n';
		write(b);

	}
	/*
	 * Print elapsed time for a specific task
	 */
	void time(const char* msg, const MonotonicTime& t)
	{
		message("%s done in  H:M S.ms %u:%02u %02u.%03u ", msg, t.getH(),
				t.getM(), t.getS(), t.getMs());
	}

	~Log()
	{

	}

	/*
	 * Constructor open a file_name
	 */
	Log(const char *file_name) :
			file(file_name)
	{
		pglog = this;
	}

	void createFile(const char* file_path)
	{
		file.open(file_path, "w+");
		pglog = this;
	}
	void close();

	bool isASCII(const unsigned char* data, unsigned short len)
	{
		uint32_t i;
		for (i = 0; i < len; i++)
		{
			if ((data[i] > 0x19) && (data[i] < 0x81))
				continue;
			switch (data[i])
			{
			case '\r':
			case '\t':
			case '\n':
			case 0:
			case 0xF1:		//'ñ':
			case 0xD1:		//'Ñ':
				continue;
			}
			return false;
		}
		return true;
	}

	void writeBuffer(log_level lvl, const char* lbl,
			const void* data, unsigned short len)
	{
		if (!console && !file)
			return;
		io::Block<255> blck;
		io::Buffer b(blck);
		b.dont_throw();

		b << MonotonicTime() << ' ' << lbl << io::cBlock(data, len) << '\n';

		write(b);
	}

	void writeHex(const void* data, unsigned short len, const char* lbl)
	{
		if (!console && !file)
			return;

		const uint8_t * dt = reinterpret_cast<const uint8_t*>(data);

		unsigned short i;
		// try to print like ascii if possible
		for (i = 0; i < len; i++)
		{
			if ((dt[i] > 0x19) && (dt[i] < 0x81))
				continue;
			switch (dt[i])
			{
			case '\r':
			case '\t':
			case '\n':
			case 0:
			case 0xF1:		//'ñ':
			case 0xD1:		//'Ñ':
				continue;
			}
			break;
		}
		/*
		 if (i == len)
		 return writeASCII(dt, len, lbl);*/

		io::Block<255> blck;
		io::Buffer b(blck);

		b << lbl;
		/*
		 for (unsigned short i = 0; i < len; i++)
		 {
		 char
		 fprintf(console.streamf, "%02X ", dt[i]);
		 }
		 */
		b << '\n';
		write(b);
	}
	/*
	 Open std out console to write log on it
	 */
	void openConsole()
	{
		console.open();
		pglog = this;
	}

	template<class ... A>
	void log_push(log_level lvl, const A& ... args)
	{
		if (!console && !file)
			return;
		io::Block<255> blck;
		io::Buffer b(blck);
		b.dont_throw();
		b << MonotonicTime() << ' ';
		print(b, args...);
		b << '\n';
		write(b);
	}
};

/*
 error messages are trace always
 support to trace high level message
 */

#define log_e(msg, ... )		do { glog.log(level_error,msg, ##__VA_ARGS__ ); } while(0)
#define log_e_push(...)			do { glog.log_push(level_error,  ##__VA_ARGS__ ); } while(0)
#define log_message(...)		do { glog.message( __VA_ARGS__ ); } while(0)
#define log_elapse_time(msg,t) 	do { glog.time(msg,t); } while(0)
#define log_e_api(x,...) 		do { glog.write_linux_api_msg(x,  ##__VA_ARGS__ ); } while(0)
#define log_buff(lbl,data,len)  do { glog.writeBuffer(level_error,lbl,data,len); } while(0)

#ifdef _DEBUG
#define trace_line()	do { glog.message("at %s:%s -> %d",__FILE__,__LINE__,__func__); } while(0)
#define log_w(msg,...)	do { glog.log(level_warning, msg,  ##__VA_ARGS__ ); } while(0)
#define log_i(msg,...)	do { glog.log(level_info,msg,  ##__VA_ARGS__ ); } while(0)
#define log_d(msg,...)	do { glog.log(level_debug,msg,  ##__VA_ARGS__ );} while(0)

#else
#define trace_line()	do {} while(0)
#define log_w(msg,...)	do {} while(0)
#define log_i(msg,...)	do {} while(0)
#define log_d(msg,...)	do {} while(0)

#endif

//#define log(x,...) { struct timespec ts; clock_gettime(CLOCK_MONOTONIC,&ts); printf("%li.%li ",ts.tv_sec,ts.tv_nsec / 1000000); printf(x,  ##__VA_ARGS__ ); printf("\n");}
#define COMMENT SLASH(/)
#define SLASH(s) /##s

//Macro expansion to convert number into string on preprocessor stage
// 1 stage get number value, second get string from number
#define STR_(x) #x
#define STR(x) STR_(x)

/*
 * Helper function to debug json node
 */

#ifdef _DEBUG
#define TRACE_NODE(x)	do \
	{ \
		HERE(); \
		std::string j=(x).write(); \
		logHexBuff(j.c_str(),j.length(),"JSON:") \
	} while(0)

#else

#define TRACE_NODE(x)
#endif

#define THREAD_NONE		0		// no started or finished
#define THREAD_STARTING	1		// waiting to be online
#define THREAD_RUNNING	2		// running
#define THREAD_CLOSING	3		// close sent
//#define THREAD_FINISHED	4

#endif /* LOG_H_ */
