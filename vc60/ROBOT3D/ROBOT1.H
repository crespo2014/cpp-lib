// Robot1.h: interface for the CRobot1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROBOT1_H__6AD19C62_4764_11D3_A264_0000E856599A__INCLUDED_)
#define AFX_ROBOT1_H__6AD19C62_4764_11D3_A264_0000E856599A__INCLUDED_

#include "SDriver.h"	    // Added by ClassView
#include "Trayectoria.h"	// Added by ClassView
#include "GLWindow.h"
#include "VDriver.h"
#include "Pos.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CRobot1 : public CGLWindow,
				private CTrayectoria
{
public:
	BOOL m_OnExecute;
	CString GetCmdChar();
	void ResetPos();
	void Close();
	DWORD Stop(BYTE pMotor);
	DWORD Run(BYTE pMotor, BYTE pDireccion);
	DWORD Move(BYTE Motor, int Valor);
	virtual void Timer();
	void CheckPos();
	BOOL Negativo();
	BOOL Positivo();
	void Executor();
	void ExecuteList(PVOID *param,DWORD pCant);
	BOOL GoToPoint(double points[3]);
	virtual void MouseClick();
	virtual void MouseMoving();
	int Init();
	virtual void PaintNow();
	CRobot1();
	virtual ~CRobot1();

private:
	//CString m_Cmdchar;
	// Clase usada para comunicacion con el quick
	CSDriver m_Comm32;

	void StopExecutor();
	void GetChar();

	GLuint m_List_Base;

	// Almacenar posicion de los motores en el calculo de trayectoria temporales
	int m_Pos[3];
	double m_Point[3];

	// Usada en la interpretacion de comandos
	BYTE  m_Motor;
	int   m_Num;
	BOOL m_OnWaiting;
	
	LPCSTR m_Buffer;
	PVOID *m_List;
	DWORD m_ListCant;
	DWORD m_ListPos;
	char m_Char;
	UINT m_Timer_ID;
	int m_TempI;

	// Posicion actual de los motores
	int m_Robot_Data[6];
	// Posicion de los motores cuando ocurrio MouseDowm
	int m_Prev_Data[6];

	// driver para el manejo del robot
	Vdriver m_Driver;

	// variable temporal
	CString m_CmdChar;
	int m_Temp_Pos[4];
	char a[20],b[20],c[20];


};

#endif // !defined(AFX_ROBOT1_H__6AD19C62_4764_11D3_A264_0000E856599A__INCLUDED_)
