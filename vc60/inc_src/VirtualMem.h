// VirtualMem.h: interface for the CVirtualMem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIRTUALMEM_H__7A1A29EA_8C70_4F17_A0AC_1A2604260A6D__INCLUDED_)
#define AFX_VIRTUALMEM_H__7A1A29EA_8C70_4F17_A0AC_1A2604260A6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVirtualMem  
{
protected:
	
public:
	CVirtualMem();
	virtual ~CVirtualMem();
	DWORD Release();
	DWORD SetMaxSize(DWORD dwMaxSize);
	DWORD SetSize(DWORD dwSize);
	DWORD IncSize(DWORD dwOffset);
	DWORD AddBuffer(BYTE* lpBuffer,DWORD dwSize);
	DWORD GetSize() const {return m_Size;}
	BYTE* Data() {return m_MemBuffer;}
private:
	DWORD Free();

	BYTE*	m_MemBuffer;
	DWORD	m_MaxSize;
	DWORD	m_Size;
	DWORD	m_Commit;
	DWORD	m_LastError;

};

#endif // !defined(AFX_VIRTUALMEM_H__7A1A29EA_8C70_4F17_A0AC_1A2604260A6D__INCLUDED_)
