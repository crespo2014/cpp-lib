// CServoSV900CDriver.cpp: implementation of the CServoSV900CDriver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServoSV900CDriver.h"

#define SM_REQUESTDATA 200
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServoSV900CDriver::CServoSV900CDriver()
{
	OnInitialize = FALSE;
	for (BYTE i=0;i<MAX_BED;i++)
	{
		ServosSV900C[i].SetMasterDriverInterfaz(this);
		ServosSV900C[i].SetSerialInterfaz(&SerialPort);
		ServosSV900C[i].SetBedNo(i+1);
	}
	m_CurrentDriver = 0;
	OnOneRequest = FALSE;
	SerialPort.SetCommunicationEvents(this);
	SerialPort.SetAsyncRead(false);
	SerialPort.SetWaitTimeOut(INFINITE);
}

CServoSV900CDriver::~CServoSV900CDriver()
{

}

DWORD CServoSV900CDriver::GetInterfaz(char *Interfaz, void** lpInterfaz)
{
	if (strcmp(Interfaz,"CServoSV900CDriver") == 0)
	{
		*lpInterfaz = this;
		return 0;
	}
	if (strcmp(Interfaz,"IServoDriver")==0)
	{
		IServoDriver* Interfaz = this;
		*lpInterfaz = Interfaz;
		return 0;
	}
	*lpInterfaz = NULL;
	return ERR_NOINTERFACE;
}

DWORD CServoSV900CDriver::NextDriverRequest()
{
	while (true)
	{
		if (m_CurrentDriver >= MAX_BED)
		{
			m_CurrentDriver = 0;
			if (!OnOneRequest) 
			{
				// si se llego al ultimo y nadie a pedido se queda asi
				SerialPort.SetWaitTimeOut(INFINITE);
				return ERR_NONE;
			}
			// se llego al ultimo y alguien habia pedido, seguir buscando
			OnOneRequest = false;
		}
		if (ServosSV900C[m_CurrentDriver].RequestData() == ERR_PENDING)
		{
			OnOneRequest = true;
			return ERR_NONE;
		}
		m_CurrentDriver++;
	}
	return ERR_NONE;
}

DWORD CServoSV900CDriver::RequestData()
{
	if (!SerialPort.IsOpen())
		return 2;
	if (!OnOneRequest) 
	{
		S_MESSAGE	Message;
		Message.Msg = SM_REQUESTDATA;
		SerialPort.SendThreadMessage(&Message);
	}
	return ERR_NONE;
}

/*
	Implementacion de la interfaz 
	IServoDriver
*/
DWORD _stdcall CServoSV900CDriver::GetName(char** pName)
{
	*pName = "Servo SV900C Siemens Electra";
	return 0;
}

DWORD _stdcall CServoSV900CDriver::GetParamsCant(DWORD* pcant)
{
	*pcant=0;
	return 0;
}

DWORD _stdcall CServoSV900CDriver::GetParamData(DWORD pIndex,char** pName,char** pMeasureUnit)
{
	return 1;
}
DWORD _stdcall CServoSV900CDriver::GetServoForBed(DWORD pBedNo,IServo** pServo)
{
	if ((pBedNo > MAX_BED-1) || (pBedNo < 1))
		return 1;
	*pServo = &ServosSV900C[pBedNo-1];
	return 0;
}

DWORD _stdcall CServoSV900CDriver::StartCommunication(DWORD pPortNo)
{
	SerialPort.SetPort((BYTE)pPortNo);
	SerialPort.SetPortConfiguration(CBR_19200,8,NOPARITY,ONESTOPBIT);
	SerialPort.SetCommMask(EV_TXEMPTY);
	SerialPort.SetReadTimeOuts(0,1,0);
	return SerialPort.OpenPort();
}

DWORD _stdcall CServoSV900CDriver::QueryInterface(char* InterfazName,void** lpInterfaz)
{
	return ERR_NOINTERFACE;
}

DWORD _stdcall CServoSV900CDriver::Release()
{
	SerialPort.Release();
	return ERR_NONE;
}


DWORD _stdcall CServoSV900CDriver::Initialize()
{
	DWORD rs;
	if (OnInitialize == TRUE)
		return ERR_NONE;
	rs = SerialPort.Initialize();
	if (rs != ERR_NONE) return rs;
	for (BYTE i=0;i<MAX_BED;i++)
	{
		if (ServosSV900C[i].Initialize() != 0)
			return 1;
	}
	OnInitialize = TRUE;
	return 0;
}

/*
	Implementacion de la Interfaz ICommunicationEvents
*/
DWORD _stdcall CServoSV900CDriver::OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam)
{
	if (m_CurrentDriver < MAX_BED)
		ServosSV900C[m_CurrentDriver].OnReceivedData(Buffer,cant);
	return 0;
}

DWORD _stdcall CServoSV900CDriver::OnCommEvent(DWORD pEventMask,LPVOID lpParam)
{
	return 0;
}

DWORD _stdcall CServoSV900CDriver::OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam)
{
	if (m_CurrentDriver < MAX_BED)
		ServosSV900C[m_CurrentDriver].OnSendBytes(BytesWritten);
	return 0;
}

DWORD _stdcall CServoSV900CDriver::OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)
{
	if (lpMessage->Msg == SM_REQUESTDATA)
	{
		// si nadie esta solicitando informacion
		if (!OnOneRequest)
		{
			return NextDriverRequest();
		}
	}
	return 0;
}

DWORD _stdcall CServoSV900CDriver::OnWaitTimeOut(LPVOID lpParam)
{
	if (m_CurrentDriver < MAX_BED)
		ServosSV900C[m_CurrentDriver].OnWaitTimeOut();
	return 0;
}

DWORD _stdcall CServoSV900CDriver::OnTrigger(LPVOID lpParam)
{
	return 0;
}