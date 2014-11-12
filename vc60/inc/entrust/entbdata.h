/******************************************************************************
 * entbdata.h - generic binary data class
 *
 * Copyright (c) 1994-2000 Entrust Technologies  All rights reserved.
 *****************************************************************************/

#ifndef ENTBDATA_H
#define ENTBDATA_H

#if !defined( ENTAPI )
#include <entbdefs.h>
#include <entgstr.h>
#else
//#include <toolkit/entapi/entbdefs.h>
#include <toolkit/entapi/tkbdefs.h>
#include <toolkit/entapi/entgstr.h>
#endif

// BinData is a class for storing Binary data and referencing it in a 
// convenient manner

#ifdef	MACOS
#ifdef __CFM68K__
#pragma import on
#endif
#endif

class EXPT BinData
{
private:
	BYTE*		m_dataptr;
	UINT32		m_alloclen;	// length of memory allocation of m_dataptr
	UINT32		m_datalen;	// length of data
public:
	EXPT32 BinData(){m_dataptr=0;m_alloclen=0;m_datalen=0;}
	EXPT32 BinData(const void*, UINT32);	// construct by copying data supplied in buffer (of length specified)
	EXPT32 BinData(const BinData&);			// copy constructor
	EXPT32 BinData(const GString&);			// copy constructor
	EXPT32 BinData(const char*);
	EXPT32 ~BinData();
	EXPT32 EntLog SetBufferPtr(void*, UINT32);	// use supplied data pointer and length (data is NOT copied)
	EXPT32 void ClrBufferPtr(){m_dataptr=0;m_alloclen=0;m_datalen=0;} // clear data members without memory de-allocation.
	EXPT32 UINT32 GetLength()const{return m_datalen;} 
	EXPT32 EntLog SetLength(UINT32 NewLen); 
	EXPT32 UINT32 GetAllocatedLength()const{return m_alloclen;} 
	EXPT32 BYTE operator[](UINT16 nIndex) const{return *(m_dataptr+nIndex);}  // return a byte
	EXPT32 BYTE operator[](UINT32 nIndex) const{return *(m_dataptr+nIndex);}  // return a byte
    EXPT32 operator BYTE*() const{return m_dataptr;} // return the pointer to byte data (not null terminated)
    EXPT32 operator char*(); // null terminate and return the pointer to characters
    EXPT32 operator INT16*() const{return (INT16*)m_dataptr;}
    EXPT32 operator UINT16*() const{return (UINT16*)m_dataptr;}
    EXPT32 operator INT32*()  const{return (INT32*)m_dataptr;}
    EXPT32 operator UINT32*() const{return (UINT32*)m_dataptr;}
#ifdef __alpha
    operator INT64*()  const{return (INT64*)m_dataptr;}
    operator UINT64*() const{return (UINT64*)m_dataptr;}
#endif
    EXPT32 const BinData& operator=(const BinData&);	// copies the data.
	EXPT32 const BinData& operator=(const GString&);	// make BinData out of a GString
	EXPT32 const BinData& operator=(const char*);		// make BinData out of a string

	EXPT32 const BinData& operator+=(const BinData&);	// concatenate
	EXPT32 const BinData& operator+=(const BYTE);		// new v2 concatenate

	EXPT32 BOOL IsEmpty(){return !GetLength();}

	EXPT32 void ShiftLeft(UINT32 nCount); 
	EXPT32 void ShiftRight(UINT32 nCount);

	EXPT32 BinData Left(UINT32 nCount) const;  //  return left nCount bytes 
	EXPT32 BinData Right(UINT32 nCount) const;  // return right nCount bytes

	EXPT32 void Zeroize();	// clears alloc'd memory

	EXPT32 friend BOOL EXPT operator==(const BinData&,const BinData&);
	EXPT32 friend BOOL EXPT operator!=(const BinData&,const BinData&);

	GString ToPEM(void) const;			// returns a PEM-encoded string
	EntLog FromPEM(const GString&);		// populates from a PEM-encoded string

	GString ToHEX(void) const;			// returns a HEX-encoded string
	EntLog FromHEX(const GString&);		// populates from a HEX-encoded string
};

EXPT32 BOOL EXPT operator==(const BinData&,const BinData&);
EXPT32 BOOL EXPT operator!=(const BinData&,const BinData&);


#ifdef	MACOS
#ifdef __CFM68K__
#pragma import off
#endif
#endif

#endif

