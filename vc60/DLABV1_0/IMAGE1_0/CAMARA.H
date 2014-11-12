// Camara.h: interface for the CCamara class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMARA_H__D2DF03A6_2282_11D3_9A2B_000021B01127__INCLUDED_)
#define AFX_CAMARA_H__D2DF03A6_2282_11D3_9A2B_000021B01127__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <VisImSrc.h>
#include <VisCore.h>
#include <VisDisplay.h>
#include <stdlib.h>
#include <afxmt.h>

typedef CVisRGBABytePixel Cpixel;
//typedef CVisBytePixel Cpixel;
typedef CVisImage<Cpixel>		CImage;

class AFX_EXT_CLASS CCamara  
{
  
  

 public:
	 void Grab(DWORD cms);
	 void CopyBuffer(char *buffer,char i);
	 void LoadDriver();
	 void Settings();
	 int tam;
     bool flag;
	 DWORD cmsTimeout;
     CVisSequence<Cpixel> m_sequence;
     CImage m_image;
     CVisPane *m_pane;
     bool m_refresca;
     BYTE* temp;
     bool m_existpane;
	 CWnd* m_handle;
	 
	 void GetHandle(CWnd *handle);
	 void Display(CPoint org);
	 void Play();
	 void Desconecta();
	 void Conecta();
     byte* GetBuffAdd();	
	 BYTE* GetBuffer();
	 CCamara();
	 virtual ~CCamara();
	 char* GrabNext(DWORD cms);

};

#endif // !defined(AFX_CAMARA_H__D2DF03A6_2282_11D3_9A2B_000021B01127__INCLUDED_)
