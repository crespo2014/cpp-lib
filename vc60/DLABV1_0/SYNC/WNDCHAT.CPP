// WndChat.cpp: implementation of the CWndChat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WndChat.h"
#include <afxwin.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWndChat::CWndChat(CString title,CString nick,CWnd* parent,CWndChat* p,int type)
{
	wnd_type=type;
	gate=p;
	wnd_access=false;// semaforos para regular
	msg_access=false;// el multiacceso
	BufferChatSend="";
	hostuser=title;
	localuser=nick;
	Create(NULL,
		title,
		WS_OVERLAPPEDWINDOW|WS_CHILD|WS_VISIBLE,
		CRect(0,0,370,320),parent
		);
	cs=new CStatic();
	cs->Create("aqui",
		WS_CHILD|WS_VISIBLE|WS_BORDER,
		CRect(10,250,40,270),
		this);
	ce=new CEdit();
	ce->Create(WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|WS_BORDER,
		CRect(50,250,300,270),
		this,
		100); 
	/*cem=new CEdit();
	cem->Create(WS_CHILD|WS_VISIBLE|ES_AUTOVSCROLL|WS_BORDER|ES_MULTILINE|ES_READONLY,
		CRect(10,10,350,240),
		this,
		101);*/
	cl=new CListBox();
	cl->Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_BORDER|LBS_EXTENDEDSEL,
		CRect(10,10,350,240),
		this,
		101);
	cb=new CButton();
	cb->Create("Send",
		WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		CRect(310,250,350,270),
		this,
		IDB_BUTTON);
}
CWndChat::CWndChat(CString title,CString nick,CWndChat* p,int type)
{
	wnd_type=type;
	gate=p;
	wnd_access=false;// semaforos para regular
	msg_access=false;// el multiacceso
	BufferChatSend="";
	hostuser=title;
	localuser=nick;
	Create(NULL,
		title,
		WS_OVERLAPPEDWINDOW,
		CRect(0,0,370,320)
		);
	cs=new CStatic();
	cs->Create("aqui",
		WS_CHILD|WS_VISIBLE|WS_BORDER,
		CRect(10,250,40,270),
		this);
	ce=new CEdit();
	ce->Create(WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|WS_BORDER,
		CRect(50,250,300,270),
		this,
		100); 
	/*cem=new CEdit();
	cem->Create(WS_CHILD|WS_VISIBLE|ES_AUTOVSCROLL|WS_BORDER|ES_MULTILINE|ES_READONLY,
		CRect(10,10,350,240),
		this,
		101);*/
	cl=new CListBox();
	cl->Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_BORDER|LBS_EXTENDEDSEL,
		CRect(10,10,350,240),
		this,
		101);
	cb=new CButton();
	cb->Create("Send",
		WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		CRect(310,250,350,270),
		this,
		IDB_BUTTON);
}

CWndChat::~CWndChat()
{

}
///////////MESSAGE HANDLERS///////////////////////////////////////

void CWndChat::OnSend()
{
	msg_access=true;
	ce->GetWindowText(BufferChatSend);
	ce->SetWindowText("");
	cl->AddString(localuser+": "+BufferChatSend);
	if(gate)
	{
		while(gate->msg_access)
		{}
		gate->hostuser=hostuser;
		gate->BufferChatSend=BufferChatSend;
		gate->msg_access=true;
	}
}

//////////MESSAGE MAP//////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CWndChat,CFrameWnd)
ON_BN_CLICKED(IDB_BUTTON,OnSend)
END_MESSAGE_MAP()
