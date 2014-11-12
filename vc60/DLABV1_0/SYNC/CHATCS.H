// ChatCS.h: interface for the CChatCS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATCS_H__5A4AA681_6F68_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_CHATCS_H__5A4AA681_6F68_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SyncSocket.h"

class AFX_EXT_CLASS CChatCS : public CSyncSocket  
{
public:
	virtual int WriteChatMessage(CString cause,CString msg);
	int ReadChatMessage(CString &cause, CString &msg);
	CChatCS();
	virtual ~CChatCS();

};

#endif // !defined(AFX_CHATCS_H__5A4AA681_6F68_11D3_A036_0000E8DE4B3B__INCLUDED_)
