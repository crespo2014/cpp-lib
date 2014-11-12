/*******************************************************************************
 * entgstr.h - generic string class
 *
 * Copyright (c) 1994-2000 Entrust Technologies  All rights reserved.          
 ******************************************************************************/
                    
#ifndef ENTGSTR_H
#define ENTGSTR_H

#if !defined( ENTAPI )
#include <entbdefs.h>
#else
#include <toolkit/entapi/tkbdefs.h>
//#include <toolkit/entapi/entbdefs.h>
#endif

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

class GString
{
public:

// Constructors
	EXPT32 EXPT GString();
	EXPT32 EXPT GString(const GString& stringSrc);
	EXPT32 EXPT GString(char ch, int nRepeat);
	EXPT32 EXPT GString(const char* psz);
	EXPT32 EXPT GString(const char* pch, int nLength);
	   
	EXPT32 EXPT ~GString();
	   
// Attributes & Operations

   // as an array of characters
	EXPT32 int EXPT GetLength() const;
	EXPT32 BOOL EXPT IsEmpty() const;
	EXPT32 void EXPT Empty();                       // free up the data
	
	EXPT32 char EXPT GetAt(int nIndex) const;       // 0 based
	EXPT32 char EXPT operator[](int nIndex) const;  // same as GetAt
	EXPT32 void EXPT SetAt(int nIndex, char ch);
	EXPT32 EXPT operator const char*() const;       // as a C string
	EXPT32 int EXPT GetCharCount() const;  // Return number of chars as opposed to number of bytes
	EXPT32 int EXPT GetCharAt(int n) const; // Return the nth character
	
	// overloaded assignment
	EXPT32 const GString& EXPT operator=(const GString& stringSrc);
	EXPT32 const GString& EXPT operator=(char ch);
	EXPT32 const GString& EXPT operator=(const char* psz);
	
	// string concatenation
	EXPT32 const GString& EXPT operator+=(const GString& string);
	EXPT32 const GString& EXPT operator+=(char ch);
	EXPT32 const GString& EXPT operator+=(const char* psz);
	
	EXPT32 friend GString EXPT operator+(const GString& string1, const GString& string2);
	EXPT32 friend GString EXPT operator+(const GString& string, char ch);
	EXPT32 friend GString EXPT operator+(char ch, const GString& string);
	EXPT32 friend GString EXPT operator+(const GString& string, const char* psz);
	EXPT32 friend GString EXPT operator+(const char* psz, const GString& string);
	
	// string comparison
	EXPT32 int EXPT Compare(const char* psz) const;         // straight character
	EXPT32 int EXPT CompareNoCase(const char* psz) const;   // ignore case
	
	// simple sub-string extraction
	EXPT32 GString EXPT Mid(int nFirst, int nCount) const;
	EXPT32 GString EXPT Mid(int nFirst) const;
	EXPT32 GString EXPT Left(int nCount) const;
	EXPT32 GString EXPT Right(int nCount) const;
	EXPT32 GString EXPT SpanIncluding(const char* pszCharSet) const;
	EXPT32 GString EXPT SpanExcluding(const char* pszCharSet) const;

	EXPT32 void EXPT ShiftLeft(int nCount);	// shift a GString to the left, dropping leading characters
	EXPT32 void EXPT ShiftRight(int nCount);	// shift right, spaces are inserted
	
	// upper/lower/reverse conversion
	EXPT32 void EXPT MakeUpper();
	EXPT32 void EXPT MakeLower();
	EXPT32 void EXPT MakeReverse();
	   
	// whitespace removal
	EXPT32 void EXPT Trim();		// trim whitespace at each end of string
	EXPT32 void EXPT RTrim();		// trim whitespace at end of string
	EXPT32 void EXPT LTrim();		// trim whitespace at start of string
	   
	// searching (return starting index, or -1 if not found)
	// look for a single character match
	EXPT32 int EXPT Find(char ch) const;                    // like "C" strchr
	EXPT32 int EXPT FindNoCase(char ch) const;              // like "C" strchr
	EXPT32 int EXPT ReverseFind(char ch) const;
	EXPT32 int EXPT FindOneOf(const char* pszCharSet) const;
	
	// look for a specific sub-string
	EXPT32 int EXPT Find(const char* pszSub) const;         // like "C" strstr
	EXPT32 int EXPT FindNoCase(const char* pszSub) const;
	
	// input and output
	
//	EXPT32 friend ostream& EXPT operator<<(ostream& ar, const GString& string);
	EXPT32 GString& EXPT printf(char* fmt,...); // this replaces existing GString with formatted output
	EXPT32 GString& EXPT printf(const char* fmt,...); // variation with const parameter.

	// Access to string implementation buffer as "C" character array
	EXPT32 char* EXPT GetBuffer(int nMinBufLength);
	EXPT32 void EXPT ReleaseBuffer(int nNewLength = -1); // truncates GString to new length
	EXPT32 char* EXPT GetBufferSetLength(int nNewLength);
	EXPT32 void EXPT Clear();
	EXPT32 int EXPT match(void *obj, int type = 0);
	EXPT32 int EXPT compare(void *obj, int type = 0);

	// Implementation
protected:
	// lengths/sizes in characters
	//  (note: an extra character is always allocated)
	char* m_pchData;            // actual string (zero terminated)
	int m_reserved0;          // does not include terminating 0
	int m_reserved1;         // does not include terminating 0
	
	// implementation helpers
	void Init();
	void AllocCopy(GString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
	void AllocBuffer(int nLen);
	void AssignCopy(int nSrcLen, const char* pszSrcData);
	void ConcatCopy(int nSrc1Len, const char* pszSrc1Data, int nSrc2Len, const char* pszSrc2D);
	void ConcatInPlace(int nSrcLen, const char* pszSrcData);
	
};

EXPT32 BOOL EXPT  operator==(const GString& s1, const GString& s2);
EXPT32 BOOL EXPT  operator==(const GString& s1, const char* s2);
EXPT32 BOOL EXPT  operator==(const char* s1, const GString& s2);
EXPT32 BOOL EXPT  operator!=(const GString& s1, const GString& s2);
EXPT32 BOOL EXPT  operator!=(const GString& s1, const char* s2);
EXPT32 BOOL EXPT  operator!=(const char* s1, const GString& s2);
EXPT32 BOOL EXPT  operator<(const GString& s1, const GString& s2);
EXPT32 BOOL EXPT  operator<(const GString& s1, const char* s2);
EXPT32 BOOL EXPT  operator<(const char* s1, const GString& s2);
EXPT32 BOOL EXPT  operator>(const GString& s1, const GString& s2);
EXPT32 BOOL EXPT  operator>(const GString& s1, const char* s2);
EXPT32 BOOL EXPT  operator>(const char* s1, const GString& s2);
EXPT32 BOOL EXPT  operator<=(const GString& s1, const GString& s2);
EXPT32 BOOL EXPT  operator<=(const GString& s1, const char* s2);
EXPT32 BOOL EXPT  operator<=(const char* s1, const GString& s2);
EXPT32 BOOL EXPT  operator>=(const GString& s1, const GString& s2);
EXPT32 BOOL EXPT  operator>=(const GString& s1, const char* s2);
EXPT32 BOOL EXPT  operator>=(const char* s1, const GString& s2);
		 
#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#endif

