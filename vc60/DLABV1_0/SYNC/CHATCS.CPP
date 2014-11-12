// ChatCS.cpp: implementation of the CChatCS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChatCS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChatCS::CChatCS()
{

}

CChatCS::~CChatCS()
{

}

int CChatCS::ReadChatMessage(CString &cause, CString &msg)
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

int CChatCS::WriteChatMessage(CString cause,CString msg)
{
	int retval;
	CString buffer;
	buffer=cause;
			buffer +="|";
			buffer +=msg;
			buffer +="|";
				
		retval=Send(LPCTSTR(buffer),buffer.GetLength(),10);
		
 return retval;

}
