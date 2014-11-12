// Joystick.h: interface for the CJoystick class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JOYSTICK_H__3D105E00_A453_11D3_B87A_0000B490D4F4__INCLUDED_)
#define AFX_JOYSTICK_H__3D105E00_A453_11D3_B87A_0000B490D4F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmsystem.h"

class CJoystick  
{
public:
	HWND m_hWnd;
	int SetWnd(HWND phWnd);
	int m_SmaxY;        // Dimensiones de la pantalla
	int m_SmaxX;
	int m_JmaxX;
	int m_JmaxY;
	int m_Scale;
	UINT m_ID;
	BOOL m_IsDriver;
	BOOL m_isJoystick;
	MMRESULT m_Result;
	JOYINFO m_JI;
	UINT m_Cant;            // Cantidad de Joystick disponibles
	int Init();
	CJoystick();
	virtual ~CJoystick();

};

#endif // !defined(AFX_JOYSTICK_H__3D105E00_A453_11D3_B87A_0000B490D4F4__INCLUDED_)
