#ifndef COMMON_H
#define COMMON_H
#endif

#if defined(WIN32) // not for Solaris 
	#if !defined(MFCS) // not for Solaris 
		#include <windows.h>
	#else
		#include <afxwin.h>
	#endif
#else
	
	typedef const char * LPCTSTR ;
	typedef unsigned long DWORD;
	typedef unsigned char BYTE;
	typedef char * LPSECURITY_ATTRIBUTES;
	typedef void * LPVOID;
		
	#ifndef SOCKET
	#define SOCKET int
	#endif
	#ifndef INFINITE
	#define INFINITE 0xFFFFFFFF  // Infinite timeout
	#endif
	#ifndef MAXDWORD
	#define MAXDWORD 0xFFFFFFFF  // Infinite timeout
	#endif
	#ifndef BOOL
	#define BOOL bool 
	#endif
	#ifndef FALSE 
	#define FALSE false // Infinite timeout
	#endif
	#ifndef TRUE
	#define TRUE true// Infinite timeout
	#endif		
#endif// Debug.h: interface for the SDebug class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBUG_H__4C0B10B6_4DB4_11D4_84B4_0010603B1083__INCLUDED_)
#define AFX_DEBUG_H__4C0B10B6_4DB4_11D4_84B4_0010603B1083__INCLUDED_



/* 
	Class for debug messages. 
	It will output logs for programs.
	It can be expanded on requirements.
*/
class SDebug  
{
public:
	void Outsd(LPCTSTR szLog,int iLog,int level=0);
	void Outd(int iLog,int level=0);
	void Outs(LPCTSTR szLog,int level=0);
	SDebug(int level=3);
	virtual ~SDebug();
	void SetDebugLevel(int level);
	int GetDebugLevel(void);
private:
	// 0= low priority: all method reports on enter.
	// 1= process info reports
	// 2= 2nd level warnings
	// 3= normal errors
	// 4= fatal errors
	// unused
	int deblvl;
	
};


extern SDebug DMain;

// LOG(...) will be used for debug on any place.
#define LOGS DMain.Outs
#define LOGD DMain.Outd
#define LOGSD DMain.Outsd
#define LSL DMain.SetDebugLevel
#define LGL DMain.GetDebugLevel


#endif // !defined(AFX_DEBUG_H__4C0B10B6_4DB4_11D4_84B4_0010603B1083__INCLUDED_)
// Event.h: interface for the SEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENT_H__A10C5582_4CFD_11D4_84B0_0010603B1083__INCLUDED_)
#define AFX_EVENT_H__A10C5582_4CFD_11D4_84B0_0010603B1083__INCLUDED_




#if !defined(WIN32) // Solaris 
	#include <thread.h>
	#include <synch.h>
	
#endif

/*
	SEvent: Implement events.
*/
class SEvent  
{
public:
	// Reset event. 
	// this functionality is not used in SOLARIS. RESET is allwais automatic.
	BOOL Reset();
	// Wait for an event to be set
	// Return:		 TRUE if event was set
	// dwTimeout:	 Time to wait for event. INFINITE available
	BOOL Lock( DWORD dwTimeout = INFINITE );
	// Set event.
	BOOL Set();
	
	// Constructor
	// WIN32
	//   bManualReset: TRUE if requires manual reset. 
	//	           FALSE if it resets automatically after waiting threads are free
	//   bInitiallySet:TRUE to set inmediatly after creation.
	//   lpszName:	 Name for event.
	//   lpsaAttribute:Security attributes.
	// Solaris
	//   All paramethers be reserved. Use defaults to  work correctly. (SEvent())
	//   Reset is allwais automatic, thus you don't need use reset;
	SEvent(BOOL bManualReset = FALSE, BOOL bInitiallySet = FALSE, LPCTSTR lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL );
	// Destructor
	virtual ~SEvent();
	
private:
	// Windows event handle.
	#if defined(WIN32)	// Win32
		HANDLE hEvent;
	#else				// SOLARIS
		cond_t cvp;
		mutex_t mp;
	#endif

};

#endif // !defined(AFX_EVENT_H__A10C5582_4CFD_11D4_84B0_0010603B1083__INCLUDED_)
#ifndef SMutex_H
#define SMutex_H




#if !defined(WIN32) 
	#include <thread.h>
#endif



/*
	SMutex:	 Implement mutex.
*/
class SMutex 
{
public:
	// Unlock mutex
	// In the same thread a mutex must be unlock as many times
	// as it was locked before free.
	BOOL Unlock( );
	// Lock: Lock mutex.
	// Return:	 TRUE if mutex was locked
	// dwTimeout:Time to wait for mutex. INFINITE is available.
	BOOL Lock( DWORD dwTimeout = INFINITE );
	// Constructor
	// bInitiallyOwn:TRUE if mutex is locked inmediatly after creation
	// lpszName:	 Name for mutex.
	// lpsaAttribute:pointer to security attributes.(Not used in Solaris, must be set to null)
	SMutex(BOOL bInitiallyOwn, LPCTSTR lpszName = NULL, LPSECURITY_ATTRIBUTES lpsaAttribute = NULL );

	SMutex();
	// Destructor.
	~SMutex();

private:
	// Windows mutex handle.
	#if defined(WIN32) 
		HANDLE	hmutex;				 // Windows Mutex 
	#else
		mutex_t mtx; // Solaris Mutex 
	#endif
};

#endif // #define SMutex_H

// Thread.h: interface for the SThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__A10C5580_4CFD_11D4_84B0_0010603B1083__INCLUDED_)
#define AFX_THREAD_H__A10C5580_4CFD_11D4_84B0_0010603B1083__INCLUDED_




#if !defined(WIN32)		// Solaris
	#include <thread.h>
#endif

class SThread  
{
public:
/*
	Construction: 
		Free indicates if Thread should be automatically 
		destroyed when ThreadFunc returns.
*/
	SThread(BOOL _Free=FALSE);

/*
	A new thread is created.
	// Win32
  lpThreadAttributes:
	Pointer to a SECURITY_ATTRIBUTES structure that determines whether
	the returned handle can be inherited by child processes. 
	If lpThreadAttributes is NULL, the handle cannot be inherited. 
	Windows NT: The lpSecurityDescriptor member of the structure
		specifies a security descriptor for the new thread. 
		If lpThreadAttributes is NULL, the thread gets a default 
		security descriptor. 
	Windows 95: The lpSecurityDescriptor member of the structure is 
		ignored. 
  dwStackSize :
	Specifies the size, in bytes, of the stack for the new thread. 
	If 0 is specified, the stack size defaults to the same size as
	that of the primary thread of the process. The stack is allocated
	automatically in the memory space of the process and it is freed
	when the thread terminates. Note that the stack size grows,
	if necessary. 
	CreateThread tries to commit the number of bytes specified by 
	dwStackSize, and fails if the size exceeds available memory. 
  dwCreationFlags:
	Specifies additional flags that control the creation of the thread.
	If the CREATE_SUSPENDED flag is specified, the thread is created
	in a suspended state, and will not run until the ResumeThread
	function is called. If this value is zero, the thread runs
	immediately after creation. At this time, no other values are
	supported.
	
	// Solaris
	The lifetime of a thread begins with the  successful return
     from  thr_create(),  which  calls start_func() and ends with
     either:
        o  the normal completion of start_func()
        o  the return from an explicit call to thr_exit()
        o  the conclusion of the calling process exit()

	All paramethers for this functions are reserved;
	
	
*/
	BOOL Start(LPSECURITY_ATTRIBUTES lpThreadAttributes=NULL,DWORD dwStackSize=0,DWORD dwCreationFlags=0);
/* 
	Wait until the thread is terminated
*/
	void End();
/*
	Destruction: On Destroy time, the thread is resume.
	If there is a loop on ThreadFunc, it should check if hevEndThread is set.
	The event will be set if it is required to terminate.
*/
	virtual ~SThread();

protected:

/* 
	This event is signaled only if the thread is requiered to 
	terminate. In ThreadFunc must be check if event is set to
	force exit.
*/
	SEvent EvEndThread;

/*	
	ThreadFunc: It is the function to override to implement our behaviour
	for the thread when it is created.
	If there is a loop on ThreadFunc, it should check if hevEndThread is set.
	The event will be set if it is required to terminate.
*/
virtual DWORD ThreadFunc()=0; 

// DWORD ThreadFunc(); to test

private:
	void Delete();
	BOOL Free;
	// sThreadFunc: Required for implement not Object Oriented on API.
	#if defined(WIN32)	// Win32
  	  static DWORD WINAPI sThreadFunc( LPVOID Este);
	  DWORD dwThreadId; // Thread Identifier
	    // A handle to the new thread. 
	    // NULL if thread could not be created.
	  HANDLE hThread;
	#else			// SOLARIS
		static void * sThreadFunc( void *);
		thread_t tid;			// Solaris ID
	#endif
};

#endif // !defined(AFX_THREAD_H__A10C5580_4CFD_11D4_84B0_0010603B1083__INCLUDED_)
#ifndef READINI_H
#define READINI_H




/* 
	Class for read inifiles. 
*/

class SIniFile
{
public:
	int ReadIniItem(char *devuelve,const char *item);
	void SetIniFile(const char * file);
	void SetIniSect(const char * _sect);
private:
	char namefile[1024];
	char section[128];
};

extern SIniFile Ini;

#endif


#if !defined BUFFER_H
#define BUFFER_H

//Buffer.h 
/* 
	It manages dynamic memory requirements
*/

//#include "Common.h"

// Revisada 29-06-01

// SBuffer should not have trace because trace is using buffer.

class SBuffer
{
public:
// RemoveFirst removes first NumBytesToRemove from the buffer.
	void RemoveFirst(DWORD NumBytesToRemove);
//Constructor
   SBuffer();
/* Copy constructor.
	It can be used for direct assignment on construction
*/
   SBuffer(const SBuffer& Original);

   SBuffer(const char* Text);

   SBuffer(const BYTE* data, DWORD size);

//Destructor
   virtual ~SBuffer();
/*	
	void Size(DWORD NewSize)
	It will assign the buffer size, increasing 
	or decreasing if necesary.
	Parameters:
		NewSize: New required size.
*/	
	void Size(DWORD NewSize);
/*
	DWORD Size()
	Returns current buffer size.
*/
	DWORD Size(void) const;
/*
	operator BYTE*()
	It allows to use the buffer as a BYTE*
*/
	operator BYTE*(void);

/*
	operator char*()
	It allows to use the buffer as a BYTE*
*/
	operator char*(void);

/*
	operator const BYTE*()
	It allows to use the buffer as a const BYTE*
*/
	operator const BYTE*(void) const;
/*
	operator const char*()
	It allows to use the buffer as a const char*
*/
	operator const char *(void) const;
/*
	operator =
	it allows direct assignment
*/
	SBuffer& operator=(const SBuffer& Original);
/* 
	This can assign a text directly to the buffer
*/
	SBuffer& SBuffer::operator =(const char *Text);
/*
	It can append one buffer from another.
*/
	SBuffer& SBuffer::operator +=(const SBuffer &ToAdd);

private:
//length of buffer
	DWORD length;
//Pointer to reserved memory
	BYTE *pData;
};

#endif


#if !defined(AFX_STRACE_H__83023741_2737_11D5_9997_000102AD72A8__INCLUDED_)
#define AFX_STRACE_H__83023741_2737_11D5_9997_000102AD72A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
//#include "Mutex.h"
//#include "SBuffer.h"
#include "stdarg.h"

// Revisada 29-6-00

// Explanation for STrace.
// Each STrace object will show a trace.
// Normally, each class will create it's own STrace object
// as: 
//		static STrace trace("Class name");
// then, in each function for the .cpp the functions can
// be called, as trace.Debug("Debug message");
// There are 5 types of traces from lowest to highest priority:
// Debug->Log->Warning->Error->Fatal.
// Each priority can be set to show messages or not.
// For each object, you can set to show messages or not.
// Local levels for classes are waited to have the "layer",
// so, lower layer can be hiden.
// For Base.h, the local levels are set from 16 to 32.
// You can select if you want "Base" trace by setting the 
// global levels.
// For example, if you set:
//		setGlobalTraceLevels(32,0,0,0,0)
// you will hide all debug messages for "base" but will maintain
// logs, warnings, errors and fatals.
// Local levels can be set in construction time, or modified with
//		setLocalTraceLevels(...).
// In this way, the default debug level for class Event is
// 16 so any global trace level set higher than 16 will hide
// this messages, but you can set the level higher in some
// part in your code to investigate some special behaviour.

// If fileName is set to "" (Default), the result is printed
// to string. It will print to the filename if other.
		
class STrace  
{
public:
	//Class constructor. 
	//Parameters:
	// The name of the class that will be printed in the Debug and Fatal messages
	// The local levels for each file or class where we need to print a message.
	STrace(const char *clase="Trace", int LocalDebugLevel=256, int LocalLogLevel=256, int LocalWarningLevel=256, int LocalErrorLevel=256, int LocalFatalLevel=256);
	virtual ~STrace();
	
	//All this methods print a message, the first parameter is a
	//formatted string and the second is a variable number of 
	//parameters like in the printf function of C.
	void Debug (const char *str, ...);		
	void Log (const char *str, ...);		
	void Warning (const char *str, ...);	
	void Error (const char *str, ...);		
	void Fatal (const char *str, ...);		

	//Sets the trace levels with the value passed.
	//0 show all messages. Any local level higher or equal to global
	// trace level shown its message.
	static void SetGlobalTraceLevels (int DebugLev=0, int LogLev=0, int WarningLev=0, int ErrorLev = 0, int FatalLev = 0);
	
	// Set Local trace levels 
	void SetLocalTraceLevels (int DebugLev=256, int LogLev=256, int WarningLev=256, int ErrorLev = 256, int FatalLev = 256);
	
	//Sets the full name of the file where the output is going to write.
	//The date and a ".log" extension will be added to the file's name.
	static void SetFileName (const char *pfileName);
	
	void GetActualFileName (char **pfileName);

private:

	SBuffer clase;
	static SBuffer fileName;

	static int GlobalLevels[5];
	int LocalLevels[5];

	SMutex block;

	void imprimir(const char *str, va_list marker);

	void getHeader(SBuffer *header);

};



#endif // !defined(AFX_STRACE_H__83023741_2737_11D5_9997_000102AD72A8__INCLUDED_)



#if !defined(AFX_STIME_H__E8141F10_737C_11D5_861E_0010603B1083__INCLUDED_)
#define AFX_STIME_H__E8141F10_737C_11D5_861E_0010603B1083__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "SBuffer.h"

class STime  
{
public:
	void GetGMTTime(SBuffer* pTimeText);
	void GetLocalDate(SBuffer* pDateText);
	void GetLocalDateInv(SBuffer *pDate);
	void GetLocalTime(SBuffer* TimeText);
	
	STime();
	virtual ~STime();

};

#endif // !defined(AFX_STIME_H__E8141F10_737C_11D5_861E_0010603B1083__INCLUDED_)

