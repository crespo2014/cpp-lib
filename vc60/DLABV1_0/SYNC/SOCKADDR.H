// SockAddr.h: interface for the CSockAddr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKADDR_H__516D81C8_49D1_11D3_8023_0000E8DE4B3B__INCLUDED_)
#define AFX_SOCKADDR_H__516D81C8_49D1_11D3_8023_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CSockAddr : public  sockaddr_in  
{
public:
	CSockAddr(const ULONG ulAddr,const USHORT ushPort=0);
	CSockAddr();
	operator LPSOCKADDR()
	{
		return (LPSOCKADDR)&sin_family;
	}
	virtual ~CSockAddr();

};

#endif // !defined(AFX_SOCKADDR_H__516D81C8_49D1_11D3_8023_0000E8DE4B3B__INCLUDED_)
