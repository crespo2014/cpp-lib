// Joystick.cpp: implementation of the CJoystick class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Joystick.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CJoystick::CJoystick()
{
	m_fChange=true;
	m_Period=20;
	m_hWnd=NULL;
	m_NumDevs=0;
	m_Threshold=10;
	m_OnInit=false;
}

CJoystick::~CJoystick()
{

}

int CJoystick::Init()
{
	m_NumDevs=joyGetNumDevs();
	if (m_NumDevs==0)
		return false;

	for (m_ID=JOYSTICKID1; m_ID<m_NumDevs; m_ID++)
	{
		if (joyGetPos(m_ID, &m_JI)==JOYERR_NOERROR)
		{ 
			if (m_fChange)
					joySetThreshold(m_ID,m_Threshold);
			if (joySetCapture(m_hWnd,m_ID,m_Period,m_fChange)==0)
			{
				joyGetDevCaps(m_ID,&m_JC,sizeof(m_JC));
				m_OnInit=true;
				return true;
			}
		}
		if (m_ID == m_NumDevs-1)
			return false;
	}
	return false;
}



int CJoystick::SetWnd(HWND phWnd)
{
	m_hWnd=phWnd;
	return true;
}

int CJoystick::Normalize(int px,int py,int pz,double *pfx,double *pfy,double *pfz)
{
	if (m_OnInit)
	{
		*pfx=(double)((double)(px/1000-m_JC.wXmin))/((double)(m_JC.wXmax/1000-m_JC.wXmin));
		*pfy=(double)((double)(py/1000-m_JC.wYmin))/((double)(m_JC.wYmax/1000-m_JC.wYmin));
		return true;
	}
	*pfx=0;*pfy=0;*pfz=0;
	return false;
}
