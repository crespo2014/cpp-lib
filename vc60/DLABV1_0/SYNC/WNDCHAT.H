// WndChat.h: interface for the CWndChat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDCHAT_H__C92CFDA1_4F60_11D3_8023_0000E8DE4B3B__INCLUDED_)
#define AFX_WNDCHAT_H__C92CFDA1_4F60_11D3_8023_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define IDB_BUTTON 102
#define CHAT 0
#define GATE 1
#define HOOK 2
class AFX_EXT_CLASS CWndChat : public CFrameWnd  
{
	CStatic* cs;
public:
	int wnd_type;
	CWndChat* gate;
	BOOL wnd_access;
	BOOL msg_access;
	CButton* cb;
	CListBox* cl;
	CString BufferChatSend;
	CString hostuser;
	CString localuser;
	CEdit* cem;
	CEdit* ce;
	CWndChat(CString title,CString nick,CWnd* parent,CWndChat* p=NULL,int type=CHAT);
	CWndChat(CString title,CString nick,CWndChat* p=NULL,int type=CHAT);
	virtual ~CWndChat();

	afx_msg void OnSend();
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_WNDCHAT_H__C92CFDA1_4F60_11D3_8023_0000E8DE4B3B__INCLUDED_)
