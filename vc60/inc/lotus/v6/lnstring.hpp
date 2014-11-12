//===========================================================================
//
// Module:		LNSTRING.HPP
//
// Description:
//
//		Class library definition for LNString and related classes.
//
//===========================================================================
//
// Copyright (c) 1996-1998 Lotus Development Corporation. All rights reserved.
// This software is subject to the Lotus Software Agreement, Restricted
// Rights for U.S. government users, and applicable export regulations.
//
//===========================================================================

#ifndef LNSTRING_HPP
#define LNSTRING_HPP

#ifndef LNGLOBAL_H
#include "lnglobal.h"
#endif

extern const char * LNEMPTYSTRING;

//
// Flags for LNString::Parse.
//

typedef WORD LNSTRINGPARSEFLAGS;

#define LNSTRINGPARSEFLAGS_TRIM_SPACE			0x0001
						// trim leading/trailing spaces and tabs
#define	LNSTRINGPARSEFLAGS_STOP_AT_FIRST_DELIM	0x0002
						// stop parsing at first delimiter
#define LNSTRINGPARSEFLAGS_DEFAULT				0
						// default flags (don't trim, don't stop at 1st delim)

//
//	Class definition for LNChar.
//

class LNIMPEXPCL LNChar : public LNNotesClass
{
friend LNSINT LNStringCompare
	( const LNChar &c1, char c2, LNSTRINGCOMPAREFLAGS flags );
friend LNIMPEXPFN(LNSINT) LNStringCompare
	( const LNChar &c1, const LNChar &c2, LNSTRINGCOMPAREFLAGS flags );

public:
#ifdef LNNO_TEXT_TRANSLATION
	LNChar( char c ) { Setup(c, TRUE); }
#else
	LNChar( char c ) { Setup(c, FALSE); }
#endif	
	LNChar( const LNChar &other );
	LNChar( LNStringBody *string, LNINT pos );

	~LNChar();
	
	LNChar& operator=( const LNChar &other );

#ifdef LNNO_TEXT_TRANSLATION
	LNChar& operator=( char c ) { return Assign(c, TRUE); }
	operator char() const  { return GetChar(TRUE); }
#else
	LNChar& operator=( char c ) { return Assign(c, FALSE); }
	operator char() const  { return GetChar(FALSE); }
#endif

	LNINT GetByteCount() const;
	
	const LNCHAR * GetCharPtr() const;

	LNCLASSID GetClassID() const {return LNCLASSID_LNCHAR;}
	
	LNBOOL IsAlpha();

	LNBOOL IsAlnum();

	LNBOOL IsArith();

	LNBOOL IsCntrl();

	LNBOOL IsDigit();

	LNBOOL IsLower();

	LNBOOL IsNull();

	LNBOOL IsPunct();

	LNBOOL IsSpace();

	LNBOOL IsUpper();

	LNChar& RemoveAccent();

	LNChar& ToLower();

	LNChar& ToUpper();
	
private:
	LNChar();	// Disabled.

	LNChar & Assign( char c, LNBOOL notranslate = FALSE );

	char GetChar( LNBOOL notranslate = FALSE ) const;

	char * GetTextPtr() const;

	void Setup( char c, LNBOOL notranslate = FALSE );

	LNStringBody *Body;
	LNINT Pos;
};

//
//	Class definition for LNString.
//
class LNIMPEXPCL LNString : public LNSmartPtr
{
friend class LNChar;

public:
	LNString();
	LNString( const LNString &other );
#ifdef LNNO_TEXT_TRANSLATION
	LNString( const char *string ) { Setup((LNCHAR *) string); }
	LNString( const char *string, LNINT len ) { Setup((LNCHAR *) string, len); }
#else
	LNString( const char *string ) { Setup(string); }
	LNString( const char *string, LNINT len ) { Setup(string, len); }
#endif	
	LNString( const LNCHAR *string );
	LNString( const LNCHAR *string, LNINT len );
	LNString( const LNChar &c );
	LNString( LNStringBody *stringb );
	LNString( LNINT number );

	~LNString();

	LNString& operator=( const LNString &other );
	LNString& operator=( const LNCHAR *string );
	LNString& operator=( const LNChar &c );
	LNString& operator=( const LNStringBody *stringb );
	LNString& operator=( LNINT number );
#ifdef LNNO_TEXT_TRANSLATION
	LNString& operator=( const char *string )
		{ return operator=((const LNCHAR *) string); }
	operator const char *() const { return (const char *) GetTextPtr(); }
#else
	LNString& operator=( const char *string ) { return Assign(string); }
	operator const char *() const { return GetPlatformTextPtr(); }
#endif	

	LNChar operator[]( int n ) const;
	LNChar operator[]( LNINT n ) const;

	LNString& operator+=( const LNString &string );
	LNString& operator<<( const LNString &string );

	LNSTATUS Append( const LNString &string );

	LNSTATUS Delete( LNINT pos, LNINT count=1 );
  
	LNSTATUS Find( const LNString &substr, LNINT pos, LNINT *loc ) const;

	LNSTATUS FindChar( char c, LNINT pos, LNINT *loc ) const
		{ return FindChar(LNString(&c, 1), pos, loc); }

	LNSTATUS FindChar( const LNString &set, LNINT pos, LNINT *loc ) const;

	LNSTATUS FindNextWordStart( LNINT pos, LNINT *loc ) const;

	LNSTATUS FindNextWordEnd( LNINT pos, LNINT *loc ) const;

	LNSTATUS FindPreviousWordStart( LNINT pos, LNINT *loc ) const;

	LNSTATUS FindPreviousWordEnd( LNINT pos, LNINT *loc ) const;

	char * GetBuf() const;

	LNINT GetBufLength() const;

	LNINT GetByteLength() const;

	LNINT GetByteCount() const {return GetBufLength();}

	LNINT GetCharacterCount() const {return GetLength();}

	LNCLASSID GetClassID() const {return LNCLASSID_LNSTRING;}

	LNINT GetLength() const;

	LNINT GetPlatformByteCount() const {return GetByteLength();}

	const char * GetPlatformTextPtr() const;

	LNSTATUS GetSubString( LNINT pos, LNINT count, LNString *dest ) const;

	char * GetTextPtr() const {return GetBuf();}

	LNSTATUS Insert( LNINT pos, const LNString &string );

	LNBOOL IsNull() const;

	LNSTATUS Parse
		( const LNString &delims, LNText *tokens,
		  LNSTRINGPARSEFLAGS flags = LNSTRINGPARSEFLAGS_DEFAULT ) const;

	void RemoveAccent();

	LNSTATUS Replace( LNINT pos, const LNString &string );
	LNSTATUS Replace( LNINT pos, LNINT count, const LNString &string );

	void ToLower();

	void ToUpper();

private:
	LNString & Assign( const char *string );

	void Setup( const char *string );
	void Setup( const char *string, LNINT len );
	void Setup( const LNCHAR *string );
	void Setup( const LNCHAR *string, LNINT len );

	void PrepareToModify();
};


//---------------------------------------------------------------------------
//	Inline versions of LNStringCompare.
//---------------------------------------------------------------------------
inline LNSINT LNStringCompare
	( char c1, char c2,
	  LNSTRINGCOMPAREFLAGS flags = LNSTRINGCOMPAREFLAGS_DEFAULT )
	{ return LNStringCompare(LNChar(c1), LNChar(c2), flags); }

inline LNSINT LNStringCompare
	( const LNChar &c1, char c2,
	  LNSTRINGCOMPAREFLAGS flags = LNSTRINGCOMPAREFLAGS_DEFAULT )
	{ return LNStringCompare(c1, LNChar(c2), flags); }

inline LNSINT LNStringCompare
	( char c1, const LNChar &c2,
	  LNSTRINGCOMPAREFLAGS flags = LNSTRINGCOMPAREFLAGS_DEFAULT )
	{ return LNStringCompare(LNChar(c1), c2, flags); }
//---------------------------------------------------------------------------
//	Relational operators to compare two strings or two characters. The
//	comparison is case and accent insensitive. Note that to avoid ambiguous
//	conversions between the overloaded operators and the built-in versions,
//	each combination of LNString/LNChar and char */char needs to be explicitly
//	defined.
//---------------------------------------------------------------------------

inline LNBOOL operator==( const LNString &string1, const char *string2 )
{
	return LNStringCompare(string1, LNString(string2)) == 0;
}

inline LNBOOL operator==( const char *string1, const LNString &string2 )
{
	return LNStringCompare(LNString(string1), string2) == 0;
}

inline LNBOOL operator==( const LNString &string1, const LNString &string2 )
{
	return LNStringCompare(string1, string2) == 0;
}

inline LNBOOL operator==( const LNChar &c1, char c2 )
{
	return LNStringCompare(c1, c2) == 0;
}

inline LNBOOL operator==( char c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) == 0;
}

inline LNBOOL operator==( const LNChar &c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) == 0;
}

//---------------------------------------------------------------------------

inline LNBOOL operator!=( const LNString &string1, const char *string2 )
{
	return LNStringCompare(string1, LNString(string2)) != 0;
}

inline LNBOOL operator!=( const char *string1, const LNString &string2 )
{
	return LNStringCompare(LNString(string1), string2) != 0;
}

inline LNBOOL operator!=( const LNString &string1, const LNString &string2 )
{
	return LNStringCompare(string1, string2) != 0;
}

inline LNBOOL operator!=( const LNChar &c1, char c2 )
{
	return LNStringCompare(c1, c2) != 0;
}

inline LNBOOL operator!=( char c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) != 0;
}

inline LNBOOL operator!=( const LNChar &c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) != 0;
}
//---------------------------------------------------------------------------

inline LNBOOL operator<( const LNString &string1, const char *string2 )
{
	return LNStringCompare(string1, LNString(string2)) == -1;
}

inline LNBOOL operator<( const char *string1, const LNString &string2 )
{
	return LNStringCompare(LNString(string1), string2) == -1;
}

inline LNBOOL operator<( const LNString &string1, const LNString &string2 )
{
	return LNStringCompare(string1, string2) == -1;
}

inline LNBOOL operator<( const LNChar &c1, char c2 )
{
	return LNStringCompare(c1, c2) == -1;
}

inline LNBOOL operator<( char c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) == -1;
}

inline LNBOOL operator<( const LNChar &c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) == -1;
}

//---------------------------------------------------------------------------

inline LNBOOL operator<=( const LNString &string1, const char *string2 )
{
	return LNStringCompare(string1, LNString(string2)) <= 0;
}

inline LNBOOL operator<=( const char *string1, const LNString &string2 )
{
	return LNStringCompare(LNString(string1), string2) <= 0;
}

inline LNBOOL operator<=( const LNString &string1, const LNString &string2 )
{
	return LNStringCompare(string1, string2) <= 0;
}

inline LNBOOL operator<=( const LNChar &c1, char c2 )
{
	return LNStringCompare(c1, c2) <= 0;
}

inline LNBOOL operator<=( char c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) <= 0;
}

inline LNBOOL operator<=( const LNChar &c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) <= 0;
}

//---------------------------------------------------------------------------

inline LNBOOL operator>( const LNString &string1, const char *string2 )
{
	return LNStringCompare(string1, LNString(string2)) == 1;
}

inline LNBOOL operator>( const char *string1, const LNString &string2 )
{
	return LNStringCompare(LNString(string1), string2) == 1;
}

inline LNBOOL operator>( const LNString &string1, const LNString &string2 )
{
	return LNStringCompare(string1, string2) == 1;
}

inline LNBOOL operator>( const LNChar &c1, char c2 )
{
	return LNStringCompare(c1, c2) == 1;
}

inline LNBOOL operator>( char c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) == 1;
}

inline LNBOOL operator>( const LNChar &c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) == 1;
}

//---------------------------------------------------------------------------

inline LNBOOL operator>=( const LNString &string1, const char *string2 )
{
	return LNStringCompare(string1, LNString(string2)) >= 0;
}

inline LNBOOL operator>=( const char *string1, const LNString &string2 )
{
	return LNStringCompare(LNString(string1), string2) >= 0;
}

inline LNBOOL operator>=( const LNString &string1, const LNString &string2 )
{
	return LNStringCompare(string1, string2) >= 0;
}

inline LNBOOL operator>=( const LNChar &c1, char c2 )
{
	return LNStringCompare(c1, c2) >= 0;
}

inline LNBOOL operator>=( char c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) >= 0;
}

inline LNBOOL operator>=( const LNChar &c1, const LNChar &c2 )
{
	return LNStringCompare(c1, c2) >= 0;
}

#endif

