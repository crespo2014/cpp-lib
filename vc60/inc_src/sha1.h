// sha1.h: interface for the Csha1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHA1_H__127E1B95_4A21_4196_A7EC_40085E481190__INCLUDED_)
#define AFX_SHA1_H__127E1B95_4A21_4196_A7EC_40085E481190__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

class Csha1 : public CbObject  
{
public:
	DWORD GetHash(BYTE* buffer,WORD* size);
	void Init();
	void Proccess_String(const char* str) { Proccess_Buffer((BYTE*)str,strlen(str)); };
	void Proccess_Buffer(const unsigned char* pbuffer,DWORD length);
	Csha1();
	virtual ~Csha1();


private:
	inline unsigned CircularShift(int bits, unsigned word);
	void ProcessMessageBlock();
	
	void PadMessage();

	union
	{
		unsigned H[5];						// Message digest buffers
		BYTE hash[20];
	};

	unsigned Length_Low;				// Message length in bits
	unsigned Length_High;				// Message length in bits

	unsigned char Message_Block[64];	// 512-bit message blocks
	int Message_Block_Index;			// Index into message block array

	bool Computed;						// Is the digest computed?
	bool Corrupted;						// Is the message digest corruped?

};

#endif // !defined(AFX_SHA1_H__127E1B95_4A21_4196_A7EC_40085E481190__INCLUDED_)
