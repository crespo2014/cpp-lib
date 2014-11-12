// CamBuff.cpp: implementation of the CCamBuff class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CamBuff.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamBuff::CCamBuff()
{
  shape = new CVisShape(0,0,192,142);
  
}

CCamBuff::~CCamBuff()
{

}

void CCamBuff::GetBuffer(char *buf)
{
  image = new CVisByteImage(*shape,evisimoptDefault,(byte*)buf); 
  nuevo = true;
}

void CCamBuff::Display(CPoint org)
{
   CRect Rect;
	if (nuevo == true)
 {
  Rect.SetRect(org.x,org.y,org.x+image->Width(),org.y+image->Height()+55);
  m_pane = new CVisPane(Rect,"Captura",evispaneDefault,m_handle,true);
  nuevo=false;
 }
 m_pane->Display(*image,evispanedispDefault,true,false);
}



void CCamBuff::GetHandle(CWnd *handle)
{
  m_handle = handle;
}
