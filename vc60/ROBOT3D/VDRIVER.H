// Vdriver.h: interface for the Vdriver class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_VDRIVER_H__EE675B81_3FC3_11D3_A264_0000E856599A__INCLUDED_)
#define AFX_VDRIVER_H__EE675B81_3FC3_11D3_A264_0000E856599A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SET_POS 1;
#define SET_DIR 2;
#define SET_DPOS 3;
#define SET_MOVING 4;

class AFX_EXT_CLASS Vdriver  
{
public:
	int SetDir(BYTE Motor, BYTE Valor);
	int SetMoving(BYTE Motor, BYTE Valor);
	int SetDPos(BYTE Motor, int Valor);
	int SetPos(BYTE Motor, int Valor);
	void Close();

	// Puntero a Dpos
	DWORD* m_Motor_DPos;
	// Puntero a la posicion de los motores
	int* m_Motor_Pos;
	// Si es driver no es cargado entonces la anterior apunta aqui
	int m_Motor_Pos1[6];
	// Estructura para ejecucion de operaciones
	DWORD* m_Message;
	int Init();
	Vdriver();
	virtual ~Vdriver();

	
private:
	int m_Timer_ID;
	HANDLE m_hCVxD;
	DWORD m_Error;
	BOOL OnOpen;
	int a;
};



#endif // !defined(AFX_VDRIVER_H__EE675B81_3FC3_11D3_A264_0000E856599A__INCLUDED_)
