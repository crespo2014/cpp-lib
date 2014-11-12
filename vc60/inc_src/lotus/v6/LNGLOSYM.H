//===========================================================================
//
// Module:	LNGLOSYM.H
//
// Description:
//
//		C++ API global typedefs and constant symbols (included by LNGLOBAL.H).
//
//===========================================================================
//
// Copyright (c) 1996-2003 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNGLOSYM_H
#define LNGLOSYM_H

//-----	Check for a valid platform symbol, and define any missing symbols
//		required by the C API headers.
//
//		The C++ API platform symbols are:
//
//		W32:		Windows NT or Windows 95 (Intel)
//		ALPHA:		Windows NT (DEC Alpha)
//		OS2:		OS/2 Warp
//		AIX:		IBM AIX
//		SOLSPARC:	Solaris Sparc
//		SOLX86:		Solaris X86
//		HPUX:		HP-UX
//		MAC:		Macintosh PPC
//		OS390:		IBM OS/390
//		OS400:		IBM OS/400 on AS/400
//		LINUX:		Red Hat Linux 6.0 (Intel)

// We don't need to do it if global.h has been already included
#ifndef GLOBAL_DEFS

#if (defined (W32) && !defined (UNIX)) || defined ALPHA
	#if !defined _X86_ && !defined _ALPHA_ && !defined ALPHA
		#define _X86_		// assume Intel if no processor type specified
	#elif defined ALPHA && !defined _ALPHA_
		#define _ALPHA_
	#endif
	#ifndef W32
		#define W32
	#endif
	#ifndef NT
		#define NT
	#endif
#elif defined OS2
	#ifndef OS2_2x
		#define OS2_2x
	#endif
#elif defined AIX || defined SOLSPARC || defined SOLX86 || defined HPUX || \
	defined OS390 || defined OS400 || defined LINUX
	#ifndef UNIX
		#define UNIX
	#endif
	#if (defined SOLSPARC || defined SOLX86) && !defined SOLARIS
		#define SOLARIS	
	#endif
#endif

#if !defined NT && !defined OS2_2x && !defined UNIX && !defined MAC
	#error ERROR: No platform specified.
#endif

#endif //GLOBAL_DEFS

//-----	Define IOSTREAM_INIT_NOT_NEEDED for HPUX. This must be defined before
//		<iostream.h> is included.

#if defined HPUX && !defined _IOSTREAM_INIT_NOT_NEEDED
	#define _IOSTREAM_INIT_NOT_NEEDED
#endif

//===========================================================================
//                       EXTERNAL HEADER FILES
//===========================================================================

//-----	Include system header files.

#include <stddef.h>			// needed to define size_t for operator new
#include <string.h>			// needed for strlen etc.
#ifdef AIX
	#include <strings.h>	// AIX needs both STRING.H and STRINGS.H
#endif


//-----	C API header files.

#ifndef GLOBAL_DEFS
	#include <global.h>		// required for all C API programs
#endif

#ifndef NAME_DEFS
	#include <names.h>		// defines MAXPATH, needed below
#endif


//===========================================================================
//                       PLATFORM-DEPENDENT SYMBOLS
//===========================================================================

//-----	Generate an error if not compiling on a supported platform. Currently,
//		the supported platforms are:
//
//		Microsoft Visual C++ on Windows NT and Windows 95
//		IBM VisualAge C++ on Windows NT and Windows 95
//		IBM VisualAge C++ on OS/2 Warp
//		Solaris Sparc and X86
//		AIX
//		HP-UX
//		Metrowerks on Mac PPC
//		IBM OS/390
//		IBM AS/400

#if !(defined NT && (defined MSC || defined IBM_C || defined __BORLANDC__)) && \
	!(defined OS2_2x && defined IBM_C) && \
	!defined SOLARIS && !defined AIX && !defined HPUX && \
	!(defined MAC && defined MWERKS_C) && !defined OS390 && !defined OS400 && \
	!(defined LINUX && defined GCC)

	#error ERROR: Unsupported platform.
#endif

//-----	Define LNGLOBALS_SUPPORTED if the platform allows each instance of
//		a shared library to have its own copy of global data, and define the
//		global data access macro accordingly. All globals are maintained in
//		a single structure to make it possible to support globals on all
//		platforms.

#if defined NT || defined OS2_2x || defined SOLARIS || defined MAC || \
	defined AIX || defined HPUX || defined OS390 || defined OS400 || defined LINUX
	#define LNGLOBALS_SUPPORTED
#else
	#error ERROR: Unsupported platform for global data.
#endif

//-----	Define the DLL import/export macros for each platform that
//		supports dynamically linked libraries.

#if defined NODLL || !defined NOTSDK
	#define LNIMPEXPCL
	#define LNIMPEXPFN(rt) rt
#else
	#if defined W32 && !defined UNIX	// UNIX also defines W32
		#ifdef __BORLANDC__
			#define LNIMPEXPCL _export
			#define LNIMPEXPFN(rt) rt _export
		#else
			#define LNIMPEXPCL __declspec(dllexport)
			#define LNIMPEXPFN(rt) __declspec(dllexport) rt
		#endif
	#elif defined OS2
		#define LNIMPEXPCL _Export
		#define LNIMPEXPFN(rt) rt _Export
	#else
		#define LNIMPEXPCL
		#define LNIMPEXPFN(rt) rt
	#endif
#endif

//-----	Define LNOLE_SUPPORTED if the platform includes support for OLE.

#if defined NT
	#define LNOLE_SUPPORTED
#endif

//-----	On OS/390, make sure we're compiling with the IEEE floating point option.

#if defined OS390 && (!defined __BFP__ ||  __BFP__ != 1)
	#error ERROR: C++ API applications must use the -Wc,'float(ieee)' compiler option.
#endif

//-----	On OS/390 and OS/400, define the symbol LNNO_TEXT_TRANSLATION if the code
//		is being compiled in ASCII, to suppress translation between EBCDIC and
//		LMBCS. Assume EBCDIC if the symbol LNCPPAPI_EBCDIC is defined, or if
//		neither __STRING_CODE_SET__ nor LNCPPAPI_ASCII is defined.

#if defined OS390 || defined OS400
	#define EBCDIC_PLATFORM
	#ifdef LNCPPAPI_EBCDIC	
		#ifdef LNCPPAPI_ASCII
			#error ERROR: Cannot define both LNCPPAPI_EBCDIC and LNCPPAPI_ASCII.
		#endif
	#else
		#if defined __STRING_CODE_SET__ || defined LNCPPAPI_ASCII
			#define LNNO_TEXT_TRANSLATION
			#ifndef LNCPPAPI_ASCII
				#define LNCPPAPI_ASCII
			#endif
		#else
			#define EBCDIC_TRANSLATION_REQUIRED
		#endif
	#endif	// LNCPPAPI_EBCDIC
#endif

//===========================================================================
//                       CONSTANTS AND TYPEDEFS
//===========================================================================

//-----	Fundamental numeric types.

typedef DWORD LNINT;			// unsigned 32-bit integer
typedef LONG LNSINT;			// signed 32-bit integer
typedef int LNBOOL;				// boolean, platform-dependent size
typedef NUMBER LNNUMBER;		// IEEE floating point number

//-----	C++ API error/status code, similar to the C API STATUS code. LNSTATUS
//		is a 32-bit value. where the low word contains the status code and the
//		high word contains flags; if the status code is zero, the high word is
//		zero also. If the status code is non-zero, the most significant 4 bits
//		of the high word are one following:
//
//			MSBs	                     Meaning
//			----	---------------------------------------------------------
//			0000	low word of LNSTATUS contains a Notes C API STATUS code
//			1100	low word of LNSTATUS contains a C++ API error code
//			1101	low word of LNSTATUS contains a C++ API warning code
//
//		Note that the other bits in the high word are reserved.

typedef DWORD LNSTATUS;

const LNSTATUS LNNOERROR = 0;
const WORD LNSTATUS_CSTATUS = 0;
const WORD LNSTATUS_ERROR = 0xC000;
const WORD LNSTATUS_WARNING = 0xD000;
const WORD LNSTATUS_FLAGS = 0xF000;

//-----	API version number and string. The build number (LNAPIBUILD) is defined
//		as a string constant in LNBUILD.H.

typedef LNINT LNVERSION;

const LNVERSION LNAPIVERSION = 300;

#define LNAPIVERSIONSTRING "Lotus C++ API Release 3.0 for Domino and Notes 6.0"

#include "lnbuild.h"


//-----	LNCHAR is used to identify character data that has already been
//		translated into LMBCS, and is meant to be used as a pointer type (i.e.,
//		LNCHAR *). LNCHAR is defined as int to distinguish LNCHAR * from char *
//		and LNString *; int is used rather than void to make sure the
//		compiler will never implicitly convert LNCHAR * to char *.

typedef int LNCHAR;

//-----	LNERROR_MESSAGE_LENGTH is a reasonable default (not maximum) length
//		for Notes error messages, and can be used to declare an error message
//		text buffer for the LNGetErrorMessage function.

const int LNERROR_MESSAGE_LENGTH = 512;

//-----	LNMAXPATH is the same as the Notes MAXPATH value, which is 100 on 16-bit
//		Windows and 256 everywhere else. Unfotunately, a Borland C++ header file
//		redefines MAXPATH to 80, so we use LNMAXPATH instead.

#ifdef BCC
	const int LNMAXPATH = 100;
#else
	#if MAXPATH != 256
		#error Error: Notes MAXPATH has been redefined.
	#endif
	const int LNMAXPATH = MAXPATH;
#endif

#endif	// LNGLOSYM_H

