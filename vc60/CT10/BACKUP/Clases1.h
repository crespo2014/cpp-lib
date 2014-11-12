// Clases1.h: interface for the CMessageClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASES1_H__4397C914_CC05_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_CLASES1_H__4397C914_CC05_11D3_A036_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMessageClass : public CObject  
{
public:
	int WaitMessage();
	int GetMesage(UINT* Msg, WPARAM* wParam, LPARAM* lParam);
	int IsMessage();
	CEvent* GetMessageEvent();
	int ReplyMessage();
	int SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	CMessageClass();
	virtual ~CMessageClass();

private:

protected:
	CCriticalSection    m_CriticalSection;
	CEvent				m_SendEvent;
	CEvent				m_ReceiveEvent;
	LPARAM				m_lParam;
	WPARAM				m_wParam;
	UINT				m_Msg;
	BOOL				m_OnMessage;

};

#endif // !defined(AFX_CLASES1_H__4397C914_CC05_11D3_A036_0000E83D722B__INCLUDED_)
