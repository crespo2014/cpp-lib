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
	int Normalize(int px,int py,int pz,double* pfx,double* pfy,double *pfz);
	HWND m_hWnd;
	int SetWnd(HWND phWnd);
	int m_Scale;
	UINT m_ID;
	JOYINFO m_JI;
	JOYCAPS m_JC;
	UINT m_NumDevs;            // Cantidad de Joystick disponibles
	UINT m_Period;
	UINT m_Threshold;
	BOOL m_fChange;
	BOOL m_OnInit;
	int Init();
	CJoystick();
	virtual ~CJoystick();

};

#endif // !defined(AFX_JOYSTICK_H__3D105E00_A453_11D3_B87A_0000B490D4F4__INCLUDED_)
