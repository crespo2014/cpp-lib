// ChatCSC.cpp: implementation of the CChatCSC class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChatCSC.h"
#include "WndChat.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChatCSC::CChatCSC()
{

}

CChatCSC::~CChatCSC()
{

}

int CChatCSC::WriteChatUsersList(CPtrList &list)
{
	CString buffer_list="";
	int i;
	CWndChat* p;
	for(i=0;i<list.GetCount();i++)
	{
		p=(CWndChat*)(list.GetAt(list.FindIndex(i)));
		buffer_list +=p->hostuser;
		buffer_list +="|";
	}	
	return Send(LPCTSTR(buffer_list),buffer_list.GetLength(),10);
}

int CChatCSC::ReadChatUsersList(LPVOID pLB, int list_type)
{
	CString buffer_list="";
	CString item;
	char* pBuff=new char[1025];
	int retval;

	retval=Receive(pBuff,1024,10);
	
	pBuff[retval]=NULL;
	buffer_list=pBuff;

	switch(list_type)
	{
	case LIST_BOX:
		{
			while(!buffer_list.IsEmpty())
			{
				item=buffer_list.SpanExcluding("|");
				((CListBox*)pLB)->AddString(item);
	            buffer_list.Delete(0,(int)(item.GetLength()+1));
			}
		}
	default:
	;}
	return retval;
}

int CChatCSC::WriteChatMessage(CWndChat *p)
{
	int retval;
	CString buffer="";
	CString nothing="n";
	if(p->msg_access)
	{
		if(p->wnd_type==GATE)
		{
			buffer=p->hostuser;
			buffer +="|";
			buffer +=p->BufferChatSend;
			buffer +="|";
		}
		if(p->wnd_type==HOOK)
		{
			buffer=p->localuser;
			buffer +="|";
			buffer +=p->BufferChatSend;
			buffer +="|";
		}
		retval=Send(LPCTSTR(buffer),buffer.GetLength(),10);
		p->msg_access=false;
		p->wnd_access=false;
	}
	else
	{
		retval=Send(LPCTSTR(nothing),nothing.GetLength(),10);		
	}
 return retval;

}

int CChatCSC::ReadChatMessage(CString &cause, CString &msg)
{
	CString buffer;
	char* pBuff=new char[1025];
	int retval;
	
	retval=Receive(pBuff,1024,10);
	
	pBuff[retval]=NULL;
	buffer=pBuff;
	if(buffer!="n")
	{
	cause=buffer.SpanExcluding("|");
	buffer.Delete(0,(int)(cause.GetLength()+1));
	msg=buffer.SpanExcluding("|");
	buffer.Delete(0,(int)(msg.GetLength()+1));
	}
	else
	{
		cause=buffer;
	}
	return retval;
}
