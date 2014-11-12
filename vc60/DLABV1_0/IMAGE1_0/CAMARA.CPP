// Camara.cpp: implementation of the CCamara class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Camara.h"
#include <afxmt.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamara::CCamara():m_sequence(), m_image()
{
  
  
  flag = true;
  cmsTimeout = 10000;
  m_refresca = true;
  m_existpane=false;
  
}

CCamara::~CCamara()
{

}

void CCamara::Conecta()
{
  m_sequence.DisconnectFromSource();
  VisFindImageSource(m_sequence, 0, true);
 
}

char* CCamara::GrabNext(DWORD cms)
	{
         CImage imageT;

		if (m_sequence.PopFront(imageT, cms))
		{
			m_image = imageT;
			if (imageT.MemBlock().PbData())
			return (char*)imageT.MemBlock().PbData();
		}
		return NULL;
	}


void CCamara::Desconecta()
{

	m_sequence.DisconnectFromSource();
	m_sequence.Clear();
	m_image.Deallocate();
	m_pane->DestroyWnd();
}



void CCamara::Play()
{
 
  
	if (flag)
  {
  flag = false;
  assert (m_sequence.HasImageSource());
  bool fCur = m_sequence.ImageSource().UseContinuousGrab();
  m_sequence.ImageSource().SetUseContinuousGrab(!fCur);
 }
  else
  {
	  m_refresca = true;
  }
}


void CCamara::Display(CPoint org)
{
   CRect Rect;
	if (m_existpane == false)
   {
   m_existpane = true;
   Rect.SetRect(org.x,org.y,org.x+m_image.Width()+22,org.y+m_image.Height()+55);
   m_pane = new CVisPane(Rect,"Captura",evispaneDefault,m_handle,true);
   }
   m_pane->Display(m_image,evispanedispDefault,true,false);
  
 }    
 
void CCamara::GetHandle(CWnd *handle)
{
 m_handle = handle;
}

BYTE* CCamara::GetBuffer()
{
	BYTE* Mem;
	Mem = m_image.MemBlock().PbData();
	return Mem;
}

byte* CCamara::GetBuffAdd()
{
return temp;
}

void CCamara::Settings()
{
    m_sequence.ImageSource().DoDialog(evisviddlgVFWFormat,(HWND)m_handle);
    m_sequence.ImageSource().DoDialog(evisviddlgVFWCompression,(HWND)m_handle);

}

void CCamara::LoadDriver()
{
    VisAddProviderRegEntryForVFW();
    VisFindImageSource(m_sequence);
    if ((m_sequence.HasImageSource()) && (m_sequence.ImageSource().IsValid()))
   
       Grab(cmsTimeout);
       
}



void CCamara::CopyBuffer(char *buffer, char i)
{
 if (buffer)
 memcpy(&buffer[i*tam],&m_image.MemBlock().PbData()[i*tam],tam);
}

void CCamara::Grab(DWORD cms)
{
 CImage imageT;

		if (m_sequence.PopFront(imageT, cms))
		{
			m_image = imageT;
			
		}
}
