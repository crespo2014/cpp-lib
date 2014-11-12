// DriverChat.cpp: implementation of the CDriverChat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DriverChat.h"
#include "WndChat.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDriverChat::CDriverChat()
{

}

CDriverChat::~CDriverChat()
{

}

void CDriverChat::SetUsersMessages(CString cause, CString msg, CPtrList& list, CWndChat* exclude)
{
	int i;
	CWndChat* p;
	for(i=0;i<list.GetCount();i++)
	{
		p=(CWndChat*)(list.GetAt(list.FindIndex(i)));
		if(p!=exclude)
		{
		while(p->wnd_access)
		{}
		p->wnd_access=true;
		p->localuser=cause;
		p->BufferChatSend=msg;
		p->msg_access=true;		
		}
	}	
}





void CDriverChat::SetUserMessage(CString cause, CString msg, CPtrList& list, CString from)
{
	int i;
	CWndChat* p;
	for(i=0;i<list.GetCount();i++)
	{
		p=(CWndChat*)(list.GetAt(list.FindIndex(i)));
		while(p->wnd_access)
		{}
		p->wnd_access=true;
		if(p->hostuser==cause)
		{
		p->localuser=from;
		p->BufferChatSend=msg;
		p->msg_access=true;		
		}
		else
		{
			p->wnd_access=false;
		}
	}	

}

int CDriverChat::RefreshWndChat(CString cause, CString msg, CPtrList &list,CListBox* pLB,CListBox* pLBP)
{
	CString extra;
	int i,find;
	CWndChat* p;
		
	if(cause=="usernew")
		{
			pLB->AddString(msg);
			extra=msg + " Entra al Canal";
			pLBP->AddString(extra);
			return USER_NEW;
		}
	if(cause=="userout")
		{
		   	extra=msg + " Sale del Canal";
			pLBP->AddString(extra);
			find=pLB->FindString(-1,msg);
			if(find!=LB_ERR)
			{
				pLB->DeleteString(find);
			}
			for(i=0;i<list.GetCount();i++)
			{
			  p=(CWndChat*)(list.GetAt(list.FindIndex(i)));
	   		  if(p->hostuser==msg)
			  {
				  list.RemoveAt(list.FindIndex(i));
			  }
			}
		return USER_OUT;
		}
	if(cause=="ignore")
		{
		return IGNORE_MSG;
		}
	if(cause=="public_msg")
		{
			pLBP->AddString(msg);
			return PUBLIC_MSG;
		}
	if(cause=="")
	{
		return FINISH_CHAT;
	}
	else
		{
		  for(i=0;i<list.GetCount();i++)
		  {
			  p=(CWndChat*)(list.GetAt(list.FindIndex(i)));
	   		  if(p->hostuser==cause)
			  {
				  extra=cause + ": ";
				  extra +=msg;
				  p->cl->AddString(extra);
				  return OLD_MSG;
			  }
		  }
		}
	return NEW_CHAT;
}
