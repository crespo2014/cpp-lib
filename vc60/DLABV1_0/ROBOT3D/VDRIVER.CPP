// Vdriver.cpp: implementation of the Vdriver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vdriver.h"
#include "Winbase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Vdriver::Vdriver()
{
	OnOpen=false;
}

Vdriver::~Vdriver()
{
	Close();

}

int Vdriver::Init()
{
	// Cargar driver y chequear su funcionamiento

	// Nombre del driver
	char name[]="\\\\.\\Robot.vxd";  
	// Carga del vxd
 	m_hCVxD=CreateFile(name,0,0,NULL,CREATE_NEW,FILE_FLAG_DELETE_ON_CLOSE, 0);
	if (m_hCVxD == INVALID_HANDLE_VALUE)
	{
		m_Error=GetLastError();
		CString message;
		message.Format(" Error %d Cargando Driver",m_Error);
		AfxMessageBox(message);
		m_Motor_Pos=m_Motor_Pos1;
		return false;
	}
	OnOpen=true;
	// Transferencia de datos 

	PDWORD Temp[3]; 
	DWORD Frec=8;  
	if (DeviceIoControl(m_hCVxD,0x8000,Temp,Frec,NULL,0,NULL,NULL)==0)
	{
		AfxMessageBox("Error en DeviceIoControl");
	}
	// Recogida de punteros
	m_Motor_DPos=Temp[0];
	m_Motor_Pos=(int*)Temp[1];
	m_Message=Temp[2];

	if (!m_Message[1])
		AfxMessageBox("Error Inizializando Driver ");
	return true;
}

void Vdriver::Close()
{
	if (OnOpen)
		if (m_Message[1])
		{
			CloseHandle(m_hCVxD);
			OnOpen=false;
		}
}

int Vdriver::SetPos(BYTE Motor, int Valor)
{
	if (OnOpen)
		if (m_Message[1])
		{
			do
			{
				a=0;
			}
			while (!m_Message[0]);
			m_Message[2]=SET_POS;
			m_Message[3]=Motor;
			m_Message[4]=Valor;
			m_Message[0]=TRUE;
			return 0;
		}
	return -1;
}

int Vdriver::SetDir(BYTE Motor, BYTE Valor)
{
	if (OnOpen)		
		if (m_Message[1])
		{
			do
			{
				a=0;
			}
			while (m_Message[0]);
			m_Message[2]=SET_DIR;
			m_Message[3]=Motor;
			m_Message[4]=Valor;
			m_Message[0]=TRUE;
			return 0;
		}
		return -1;
}

int Vdriver::SetDPos(BYTE Motor, int Valor)
{
	if (OnOpen)
		if (m_Message[1])
		{
			if (Valor>0) SetDir(Motor,true);
			else SetDir(Motor,false);
			do
			{
				a=0;
			}
			while (m_Message[0]);
			m_Message[2]=SET_DPOS;
			m_Message[3]=Motor;
			m_Message[4]=abs(Valor);
			m_Message[0]=TRUE;
			return 0;
		}
	return -1;

}

// Valor determina la accion a realizar
// 0 Deteine el motor
// 1 Direccion negativa
// 2 Direccion positiva

int Vdriver::SetMoving(BYTE Motor, BYTE Valor)
{
	if (OnOpen)
		if (m_Message[1])
		{
			do
			{
				a=0;
			}
			while (m_Message[0]);
			m_Message[2]=SET_MOVING;
			m_Message[3]=Motor;
			m_Message[4]=Valor;
			m_Message[0]=TRUE;
			return 0;
		}
	return -1;
}
