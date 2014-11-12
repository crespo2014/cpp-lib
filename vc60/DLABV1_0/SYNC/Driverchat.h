// DriverChat.h: interface for the CDriverChat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVERCHAT_H__2AB53261_557C_11D3_8023_0000E8DE4B3B__INCLUDED_)
#define AFX_DRIVERCHAT_H__2AB53261_557C_11D3_8023_0000E8DE4B3B__INCLUDED_
#include "WndChat.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define USER_NEW 0
#define USER_OUT 1
#define IGNORE_MSG 2
#define PUBLIC_MSG 3
#define NEW_CHAT 4
#define OLD_MSG 5
#define FINISH_CHAT 6

class AFX_EXT_CLASS CDriverChat  
{
public:
	int RefreshWndChat(CString cause,CString msg,CPtrList& list,CListBox* pLB,CListBox* pLBP);
	void SetUserMessage(CString cause,CString msg,CPtrList& list,CString from);
	
	void SetUsersMessages(CString cause, CString msg, CPtrList& list, CWndChat* exclude);
	CDriverChat();
	virtual ~CDriverChat();

};

#endif // !defined(AFX_DRIVERCHAT_H__2AB53261_557C_11D3_8023_0000E8DE4B3B__INCLUDED_)
