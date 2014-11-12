// SDriver.h: interface for the CSDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDRIVER_H__F043CB60_6BAF_11D3_A8D7_0000E83D722B__INCLUDED_)
#define AFX_SDRIVER_H__F043CB60_6BAF_11D3_A8D7_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Comm32.h"

class AFX_EXT_CLASS CSDriver : public CComm32  
{
public:
	DWORD Negativo();
	DWORD Positivo();
	void RefreshPos(int pRelPos[4]);
	void GetPos(int pPos[6]);
	DWORD ResetPos();
	DWORD MoveRel(BYTE pMotor, int pPos);
	DWORD MoveTo(BYTE pMotor,int pPos);
	DWORD Init();
	CSDriver();
	virtual ~CSDriver();

private:
	char m_temp1[20];
	char m_temp2[20];
	CString m_String;
	// Posicion actual de los motores
	int m_Motor_Pos[6];
	// usada para indicar los motores en movimiento el comando W limpia esta variable
	BYTE m_Motor_Mov[6];
};

#endif // !defined(AFX_SDRIVER_H__F043CB60_6BAF_11D3_A8D7_0000E83D722B__INCLUDED_)
