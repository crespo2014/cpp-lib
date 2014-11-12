//===========================================================================
//
// Module:	LNGLOFUN.H
//
// Description:
//
//		C++ API global function declarations (included by LNGLOBAL.H).
//
//===========================================================================
//
// Copyright (c) 1996-2004 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNGLOFUN_H
#define LNGLOFUN_H

class LNNotesSession;						// forward declaration needed


extern LNIMPEXPFN(void) LNDelete( void *object );

extern LNIMPEXPFN(LNVERSION) LNGetAPILibraryVersion();

extern LNIMPEXPFN(const char *) LNGetAPILibraryVersionText( LNBOOL ebcdic );

extern LNIMPEXPFN(const char *) LNGetClassName( LNCLASSID id, LNBOOL ebcdic );

extern LNIMPEXPFN(LNINT) LNGetErrorMessageText
	( LNSTATUS error, char *buffer, LNINT buflen, LNBOOL ebcdic );

extern LNIMPEXPFN(LNNotesSession *) LNGetSession();

extern LNIMPEXPFN(LNBOOL) LNGetThrowAllErrorsGlobal();

extern LNIMPEXPFN(LNBOOL) LNIsNotesInitialized();

extern LNIMPEXPFN(void *) LNNew( size_t size );

extern LNIMPEXPFN(void) LNSetThrowAllErrorsGlobal( LNBOOL flag );

extern LNIMPEXPFN(LNSINT) LNStringCompare
	( const LNChar &c1, const LNChar &c2,
	  LNSTRINGCOMPAREFLAGS flags = LNSTRINGCOMPAREFLAGS_DEFAULT );

extern LNIMPEXPFN(LNSINT) LNStringCompare
	( const LNCHAR *string1, const LNCHAR *string2,
	  LNSTRINGCOMPAREFLAGS flags = LNSTRINGCOMPAREFLAGS_DEFAULT );

extern LNIMPEXPFN(LNSINT) LNStringCompare
	( const LNString &string1, const LNString &string2, 
	  LNSTRINGCOMPAREFLAGS flags = LNSTRINGCOMPAREFLAGS_DEFAULT );

extern LNIMPEXPFN(LNSTATUS) LNStringTranslate
	(const void * input, LNCHARSET charset, LNString *output, LNINT *retLength=0);

extern LNIMPEXPFN(LNSTATUS) LNStringTranslate
	(const LNString &input, LNCHARSET charset, LNINT bufLength, void *outputBuf,
	 LNINT *retLength=0);

#endif	// LNGLOFUN_H

