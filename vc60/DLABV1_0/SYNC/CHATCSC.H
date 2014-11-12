// ChatCSC.h: interface for the CChatCSC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATCSC_H__2AB53262_557C_11D3_8023_0000E8DE4B3B__INCLUDED_)
#define AFX_CHATCSC_H__2AB53262_557C_11D3_8023_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define LIST_BOX 0 //tipo de lista donde se mostraran los datos
#include "ChatCS.h"
#include "WndChat.h"

class AFX_EXT_CLASS CChatCSC : public CChatCS  
{
public:
	int ReadChatMessage(CString& cause,CString& msg);
	virtual int WriteChatMessage(CWndChat *p);
	int ReadChatUsersList(LPVOID pLB, int list_type=LIST_BOX);
	int WriteChatUsersList(CPtrList& list);
	CChatCSC();
	virtual ~CChatCSC();

};

#endif // !defined(AFX_CHATCSC_H__2AB53262_557C_11D3_8023_0000E8DE4B3B__INCLUDED_)
