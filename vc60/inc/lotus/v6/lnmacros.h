//===========================================================================
//
// Module:	LNMACROS.H
//
// Description:
//
//		C++ API macros and inline functions.
//
//===========================================================================
//
// Copyright (c) 1996-2001 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNMACROS_H
#define LNMACROS_H

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif

//===========================================================================
//                        LNSTATUS MANIPULATION
//===========================================================================

//---------------------------------------------------------------------------
//	LNGetLNSTATUSFlags(code): returns the flags from the specified LNSTATUS
//	code.
//---------------------------------------------------------------------------

inline WORD LNGetLNSTATUSFlags( LNSTATUS code )
{
	return HIWORD(code) & LNSTATUS_FLAGS;
}	

//---------------------------------------------------------------------------
//	LNIsSTATUS(code): returns TRUE if the specified LNSTATUS code represents
//	a non-zero C API status code.
//---------------------------------------------------------------------------

inline LNBOOL LNIsSTATUS( LNSTATUS code )
{
	return (HIWORD(code) == 0) && LOWORD(code);
}

//---------------------------------------------------------------------------
//	LNIsError(code): returns TRUE if the specified LNSTATUS code is a C or
//	C++ API error code, FALSE if the LNSTATUS is zero or a C++ API warning
//	code. Note that all non-zero C API STATUS values are considered errors.
//---------------------------------------------------------------------------

inline LNBOOL LNIsError( LNSTATUS code )
{
	return
		(LNGetLNSTATUSFlags(code) == LNSTATUS_ERROR) || LNIsSTATUS(code);
}

//---------------------------------------------------------------------------
//	LNIsWarning(code): returns TRUE if the specified LNSTATUS is a C++ API
//	warning code, FALSE otherwise.
//---------------------------------------------------------------------------

inline LNBOOL LNIsWarning( LNSTATUS code )
{
	return LNGetLNSTATUSFlags(code) == LNSTATUS_WARNING;
}

//---------------------------------------------------------------------------
//	LNMakeLNSTATUS(code): converts the specified STATUS code to an LNSTATUS.
//---------------------------------------------------------------------------

inline LNSTATUS LNMakeLNSTATUS( STATUS code )
{
	return (LNSTATUS) code;
}

//===========================================================================
//                            MISCELLANEOUS
//===========================================================================

//---------------------------------------------------------------------------
//	LNGetAPILibraryVersionString: returns the name associated with the version
//	ID returned by LNGetAPILibraryVersion.
//---------------------------------------------------------------------------

inline const char * LNGetAPILibraryVersionString()
{
#ifdef EBCDIC_TRANSLATION_REQUIRED
	return LNGetAPILibraryVersionText(TRUE);
#else
	return LNGetAPILibraryVersionText(FALSE);
#endif
}

//---------------------------------------------------------------------------
//	LNGetAPIProgramVersion: returns the version ID for the API program
//	compiled with this set of header files.
//---------------------------------------------------------------------------

inline LNVERSION LNGetAPIProgramVersion()
{
	return LNAPIVERSION;
}

//---------------------------------------------------------------------------
//	LNGetAPIProgramVersionString: returns the name associated with the version
//	ID returned by LNGetAPIProgramVersion.
//---------------------------------------------------------------------------

inline const char * LNGetAPIProgramVersionString()
{
	return LNAPIVERSIONSTRING;
}

//---------------------------------------------------------------------------
//	LNGetErrorMessage(error, buffer, buflen): retrieves the null-terminated
//	error message string, in the platform character set, for the specified
//	error or warning code, and returns the string length (excluding null
//	terminator).
//---------------------------------------------------------------------------

inline LNINT LNGetErrorMessage
	( LNSTATUS error, char *buffer, LNINT buflen = LNERROR_MESSAGE_LENGTH)
{
#ifdef EBCDIC_TRANSLATION_REQUIRED
	return LNGetErrorMessageText(error, buffer, buflen, TRUE);
#else
	return LNGetErrorMessageText(error, buffer, buflen, FALSE);
#endif
}

//---------------------------------------------------------------------------
//	LNGetPlatform: returns the name  of the platform for which this API program
//	was built.
//---------------------------------------------------------------------------

inline const char * LNGetPlatform()
{
	return PLATFORM_NAME;
}

//---------------------------------------------------------------------------
//	LNGetThrowAllErrors/LNSetThrowAllErrors(flag): returns/modifies the global
//	ThrowAllErrors flag, which determines how errors are handled by C++ API
//	functions. If TRUE, all errors are thrown as exceptions; otherwise, errors
//	are returned by functions that return an LNSTATUS code.
//---------------------------------------------------------------------------

inline LNBOOL LNGetThrowAllErrors()
	{ return LNGetThrowAllErrorsGlobal(); }

inline void LNSetThrowAllErrors( LNBOOL flag )
	{ LNSetThrowAllErrorsGlobal(flag); }

//---------------------------------------------------------------------------
//	LNGLOBAL(x): used to access global data items. On platforms that support
//	per-process global data (currently all of them), LNGLOBAL just references
//	the global item in the LNGlobalData structure.
//---------------------------------------------------------------------------

#ifdef LNGLOBALS_SUPPORTED
	#define LNGLOBAL(x) (LNGlobalData.x)
#else
	#error ERROR: Unsupported platform for global data.
#endif

//---------------------------------------------------------------------------
//	LNIsClassID: returns TRUE if the specified value is a valid class ID,
//	FALSE otherwise.
//---------------------------------------------------------------------------

inline LNBOOL LNIsClassID( LNCLASSID id )
{
	return id > LNCLASS_BEGIN && id < LNCLASS_END;
}


//---------------------------------------------------------------------------
//	MAKELONG(a, b): combines two WORD values into a LONG.
//---------------------------------------------------------------------------

#if !defined(WINDOWS_INCLUDED)
// added to handle extended note type
	#if defined MAKELONG
		#undef MAKELONG
	#endif		
	#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#endif


#endif	// LNMACROS_H

