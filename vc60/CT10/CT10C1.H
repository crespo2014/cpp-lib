// ct10c1.h: interface for the CPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CT10C1_H__2E83796F_F4E6_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_CT10C1_H__2E83796F_F4E6_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\LFC10\lfc10c01.h"

#define RECEIVED_DATA WM_APP+1

class CPort : public CAsyncCommPort  
{
public:
	CDialog* Dlg;
	virtual int OnReceiveData(BYTE* pBuffer, DWORD pCant);
	CPort();
	virtual ~CPort();

};

#endif // !defined(AFX_CT10C1_H__2E83796F_F4E6_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
