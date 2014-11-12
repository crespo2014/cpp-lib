// Hash.h: interface for the CHash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASH_H__3A8BED44_6423_487F_81FA_56BE69F5BD94__INCLUDED_)
#define AFX_HASH_H__3A8BED44_6423_487F_81FA_56BE69F5BD94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "x509cert.h"

class CHash : public CbObject  
{
public:
	DWORD GetHash(BYTE* pdata,DWORD* pSize);
	DWORD CreateHash(ALG_ID Algid);
	void Release();
	DWORD Hash_Data(const BYTE* buffer,DWORD size);
	CHash();
	virtual ~CHash();

private:
	HCRYPTPROV m_hash;
	HCRYPTPROV m_hCryptProv;
	//ALG_ID	Algid

};

#endif // !defined(AFX_HASH_H__3A8BED44_6423_487F_81FA_56BE69F5BD94__INCLUDED_)
