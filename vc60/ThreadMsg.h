// ThreadMsg.h: interface for the CThreadMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADMSG_H__CAC8DCA8_C7F3_4922_89E0_7D3746566F9B__INCLUDED_)
#define AFX_THREADMSG_H__CAC8DCA8_C7F3_4922_89E0_7D3746566F9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Envio de mensajes al hilo, hay que derivar de esta clase

typedef struct 
{
	DWORD		lParam;
	DWORD		wParam;
	DWORD		Msg;
	LPVOID		pData;
	DWORD		Result;
	int			ErrorCode;
} S_THREADMSG,*LP_THREADMSG;

#define MSG_TIMEOUT 1000

class CThreadMsg  
{
public:
	DWORD Release();
	DWORD Initialize();
	DWORD ThreadReplyMsg();
	DWORD SendMessage(S_THREADMSG* lpMessage,DWORD timeout = MSG_TIMEOUT);
	DWORD ThreadGetMsg(S_THREADMSG** lpMessage);
	DWORD GetSndEvent(LPHANDLE lpHandle);
	DWORD WaitMessage(DWORD TimeOut = INFINITE);
	CThreadMsg();
	virtual ~CThreadMsg();
private:
	HANDLE			m_hSendEvent;	
	HANDLE			m_hReplyEvent;
	BOOL				OnMessage;
	//int					TimeOut;
	S_THREADMSG*	m_Msg;

};

#endif // !defined(AFX_THREADMSG_H__CAC8DCA8_C7F3_4922_89E0_7D3746566F9B__INCLUDED_)
