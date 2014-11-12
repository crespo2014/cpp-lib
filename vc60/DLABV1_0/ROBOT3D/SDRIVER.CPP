// SDriver.cpp: implementation of the CSDriver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SDriver.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSDriver::CSDriver()
{
	BYTE i;
	for(i=0;i<6;i++)
		m_Motor_Pos[i]=0;

}

CSDriver::~CSDriver()
{
	ResetPos();
}

DWORD CSDriver::Init()
{
	SetPort(COM2);
	if (!OpenComm()) 
		if (!ConfigComm())
			return true;
	return false;
}

// Realiza un movimiento relativo al origen  
DWORD CSDriver::MoveTo(BYTE pMotor, int pPos)
{
	m_String.Empty();
	_itoa(pMotor,m_temp1,10);
	_itoa(pPos-m_Motor_Pos[pMotor],m_temp2,10);
	m_String=m_String+"M"+m_temp1+" "+m_temp2+" W /r";
	SendString(m_String,m_String.GetLength());
	return true;
}

// El movimiento realizado es relativo a la posicion actual
DWORD CSDriver::MoveRel(BYTE pMotor, int pPos)
{
	m_String.Empty();
	_itoa(pMotor,m_temp1,10);
	_itoa(pPos,m_temp2,10);
	m_String=m_String+"M"+m_temp1+" "+m_temp2+" W /r";
	if (SendString(m_String,m_String.GetLength()))
		m_Motor_Pos[pMotor]+=pPos;
	return true;
}

// llevar el robot a las coordenadas iniciales
DWORD CSDriver::ResetPos()
{
	m_String.Empty();
	_itoa(-m_Motor_Pos[0],m_temp1,10);
	m_String=m_String+"M0 "+m_temp1+" M1 ";
	_itoa(-m_Motor_Pos[1],m_temp1,10);
	m_String=m_String+m_temp1+" M2 ";
	_itoa(-m_Motor_Pos[2],m_temp1,10);
	m_String=m_String+m_temp1+" M3 ";
	_itoa(-m_Motor_Pos[3],m_temp1,10);
	m_String=m_String+m_temp1+" W \r";
	if (!SendString(m_String,m_String.GetLength()))
		for(int i=0;i<4;i++)
			m_Motor_Pos[i]=0;
	return true;
}

// Devuelve la posicion actual de los motores
void CSDriver::GetPos(int pPos[])
{
	memcpy(pPos,m_Motor_Pos,6*sizeof(int));
}

// Usada para introducir cambios de coordenadas
void CSDriver::RefreshPos(int pRelPos[])
{
	for (int i=0;i<4;i++)
		m_Motor_Pos[i]+=pRelPos[i];
}

// reinterpretacion de comandos para conocer la posicion real de los motores
//DEL DWORD CSDriver::SendString(LPCSTR lpBuffer,DWORD nNumberOfBytesToWrite)
//DEL {
//DEL 	char* tempC=(char*)lpBuffer;
//DEL 	int tempI,tempII;
//DEL 	/*
//DEL 	switch(*tempC)
//DEL 	{
//DEL 		tempC++;
//DEL 	case 'M':
//DEL 		{
//DEL 			if (Positivo()) m_Motor=(BYTE)m_Num;
//DEL 			if (Negativo())
//DEL 				m_Driver.SetDPos(m_Motor,m_Num);
//DEL 			break;
//DEL 		}
//DEL 	case 'W':
//DEL 		{
//DEL 			m_OnWaiting=true;
//DEL 			break;
//DEL 		}
//DEL 	case 'C':
//DEL 		{
//DEL 			if (Positivo()) m_Driver.SetMoving((BYTE)m_Num,true);
//DEL 			break;
//DEL 		}
//DEL 	case 'S':
//DEL 		{
//DEL 			if (Positivo()) m_Driver.SetMoving((BYTE)m_Num,false);
//DEL 			break;
//DEL 		}
//DEL 	case 0:
//DEL 		{
//DEL 			// Se acabo esta lista
//DEL 			m_ListPos++;
//DEL 			if (m_ListPos==m_ListCant)
//DEL 				StopExecutor();
//DEL 			else
//DEL 			{
//DEL 				m_Buffer=((CPos*)m_List[m_ListPos])->GetMov();
//DEL 			}
//DEL 			break;
//DEL 		}
//DEL 	case 32:
//DEL 		{
//DEL 			break;
//DEL 		}
//DEL 	default:
//DEL 		{
//DEL 			StopExecutor();
//DEL 			AfxMessageBox("Invalid Comand",0,0);
//DEL 			break;
//DEL 		}
//DEL 		}
//DEL 	
//DEL */
//DEL 
//DEL 
//DEL 	CComm32::SendString(lpBuffer,nNumberOfBytesToWrite);
//DEL 	return 0;
//DEL }

DWORD CSDriver::Positivo()
{
	return true;
}

DWORD CSDriver::Negativo()
{
	return true;
}
