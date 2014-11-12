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
	m_SmaxY=768;        // Dimensiones de la pantalla
	m_SmaxX=1024;
	m_JmaxX=65535;
	m_JmaxY=65535;
	m_Scale=5;
}

CJoystick::~CJoystick()
{

}

int CJoystick::Init()
{
	m_Cant=joyGetNumDevs();
	joySetCapture(m_hWnd,JOYSTICKID1,0,FALSE);
	if (m_Cant==0)
		return false;

	for (m_ID=JOYSTICKID1; m_ID<m_Cant; m_ID++)
	{
		if (joyGetPos(m_ID, &m_JI)==JOYERR_NOERROR)
		{ 
			break;
		}
		if (m_ID == m_Cant-1)
			return false;
	}
	return true;
}



int CJoystick::SetWnd(HWND phWnd)
{
	m_hWnd=phWnd;
	return true;
}
