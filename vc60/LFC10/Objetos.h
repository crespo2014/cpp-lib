// Objetos.h: interface for the CCommPortObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJETOS_H__4397C911_CC05_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_OBJETOS_H__4397C911_CC05_11D3_A036_0000E83D722B__INCLUDED_

#include "Clases1.h"	// Added by ClassView
#include "CDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct S_PortParams
{
	DCB   m_DCB;
	int   m_PortNumber;
} PortParams;

class CCommPortObject : public CObject  
{
	DECLARE_DYNAMIC( CCommPortObject )
public:
	CCommPortObject();
	virtual ~CCommPortObject();

public:
	CString m_FileConfig;
	CConfigDlg m_ConfigDlg;
	DWORD m_NumberOfBytesRead;
	char m_Buffer[255];
	OVERLAPPED m_EventOverlapped;
	CEvent m_WriteEvent;
	CEvent m_ReadEvent;
	CEvent m_CommEvent;
	DWORD  m_ModemStat;
	DWORD  m_EventMask;
	DWORD  m_EventsMask;
	char   m_PortName[20];
	int    m_PortNumber;
	HANDLE m_PortHandle;
	BOOL   m_OnConnect;
	CMessageClass   m_Message;
	CWinThread*		m_ReadThread;
	DCB             m_DCB;
	COMMPROP		m_COMMPROP;
	OVERLAPPED		m_ReadOverlapped;
	OVERLAPPED		m_WriteOverlapped;
	COMMTIMEOUTS	m_CommTimeOuts;
	COMSTAT			m_CommStat;
	COMMCONFIG		m_CommConfig;
private:
};



#endif // !defined(AFX_OBJETOS_H__4397C911_CC05_11D3_A036_0000E83D722B__INCLUDED_)
