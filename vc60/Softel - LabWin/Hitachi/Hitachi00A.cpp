// Hitachi00A.cpp: implementation of the CHitachi00A class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Hitachi00A.h"
#include "errorcodes.h"
#include "dllCommon.h"
#include "Factory.h"
#include "..\include\SL_Common.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK			0x7C

// m_nextframe
#define WAIT_HEADER		1
#define WAIT_PACIENT	2
#define WAIT_OPERATION	3
#define WAIT_RESULT		4
#define WAIT_LAST		5

// m_frame
#define IN_NOFRAME		0
#define IN_HEADER		1
#define IN_PACIENT		2
#define IN_OPERATION	3
#define IN_RESULT		4
#define IN_LAST			5

// framechar
#define HEADER_CHAR		'H'
#define PACIENT_CHAR	'P'
#define OPERATION_CHAR	'O'
#define RESULT_CHAR		'R'
#define LAST_CHAR		'L'

// posicion de los separadores
#define TYPE_POS		0	// Indica el tipo de frame
#define NAME_POS		5
#define NOMUESTRA_POS	2
#define ANALISYS_POS	2
#define VALUE_POS		3
#define UNIT_POS		4
#define DATE_POS		12	

//m_framestatus
#define WAIT_STX		1	// se espera el stx
#define WAIT_SEPARATOR	4	// se espera el recivo de un separador no es obligado si no llega se acumula lo recibido

//#define WAIT_TYPE1		2	// se espera el primer byte del tipo de frame
//#define WAIT_TYPE		3	// se espera el tipo de frame

const char*	DeviceName = "Hitachi serie 00A";

CHitachi00A::CHitachi00A()
{
	m_cRef = 0;
	m_ISerialPort = NULL;
	m_PortConfig.BaudRate = CBR_9600;
	m_PortConfig.Parity = NOPARITY;
	m_PortConfig.StopBits = ONESTOPBIT;
	m_PortConfig.ByteSize = 8;
	m_PortConfig.CheckParity = false;
	m_PortConfig.CTSStopOutFlow = false;
	m_PortConfig.DSRStopInFlow = false;
	m_PortConfig.DSRStopOutFlow = false;
	m_PortConfig.DTRMode = DTR_CONTROL_ENABLE;
	m_PortConfig.RTSMode = RTS_CONTROL_ENABLE;
	m_PortConfig.lParam = 0;
	m_ResultCount = 0;
	ResetBufferStatus();	
}

CHitachi00A::~CHitachi00A()
{

}

// Interfaz IUnknown
DWORD _stdcall CHitachi00A::QueryInterface(char* lpName,_IUnknown** lpInterfaz)
{
	DWORD dr;
	dr = GetInterfaz(lpName,lpInterfaz);
	if (dr == 0) AddRef();
	return dr;
}
DWORD _stdcall CHitachi00A::AddRef()
{
	InterlockedIncrement((long*)&m_cRef);
	return 0;
}
DWORD _stdcall CHitachi00A::Release()
{
	if (InterlockedDecrement((long*)&m_cRef) == 0)
	{
		if (m_ISerialPort) DeleteInstance(m_ISerialPort);
		m_ISerialPort = NULL;
		DLLDestroyInstance(this);
		return 0;				
	}
	return m_cRef;
}

DWORD _stdcall CHitachi00A::Initialize()
{
	DWORD dr;
	for (;;)
	{
		// Cargar instancia de puerto serie
		dr = CreateInstance("SerialPort32.dll","ISerialPort",(_IUnknown**)&m_ISerialPort);
		if (dr != 0) break;
		dr = m_ISerialPort->Attach(this);
		if (dr != 0) break;
		dr = m_ISerialPort->Initialize();
		if (dr != 0) break;
		return ERR_NONE;
	}
	return dr;
}

DWORD _stdcall CHitachi00A::GetInterfaz(char* lpName,_IUnknown** lpInterfaz)
{
	*lpInterfaz = NULL;
	if (strcmp(lpName,"ILabDevice") == 0)	*lpInterfaz = (ILabDevice*) this;
	if (strcmp(lpName,"ISerialPortEvents") == 0) *lpInterfaz = (_IUnknown*)(ISerialPortEvents*)this;
	if (*lpInterfaz == NULL) return ERR_NOINTERFACE;
	return ERR_NONE;
}

DWORD _stdcall CHitachi00A::GetName(char* lpBuffer,DWORD* bufferSize)
{
	DWORD len = lstrlen(DeviceName);
	if (lpBuffer == NULL) 
	{
		*bufferSize = len;
		return ERR_NONE;
	}
	lstrcpyn(lpBuffer,DeviceName,*bufferSize);
	if (*bufferSize < len+1) return ERR_OUT_RANGE;
	*bufferSize = len;
	return ERR_NONE;
}

DWORD _stdcall CHitachi00A::SetPortConfiguration(DWORD dwBaudRate,BYTE bParity,BYTE bStopBits)
{
	if (!m_ISerialPort) return ERR_NO_INITIALIZE;
	m_PortConfig.BaudRate = dwBaudRate;
	m_PortConfig.Parity = bParity;
	m_PortConfig.StopBits = bStopBits;
	m_PortConfig.ByteSize = 8;
	m_PortConfig.CheckParity = false;
	m_PortConfig.CTSStopOutFlow = false;
	m_PortConfig.DSRStopInFlow = false;
	m_PortConfig.DSRStopOutFlow = false;
	m_PortConfig.DTRMode = DTR_CONTROL_ENABLE;
	m_PortConfig.RTSMode = RTS_CONTROL_ENABLE;
	m_PortConfig.lParam = 0;
	return m_ISerialPort->SetPortConfiguration(&m_PortConfig);
}

DWORD _stdcall CHitachi00A::GetPortConfiguration(DWORD* dwBaudRate,BYTE* bParity,BYTE* bStopBits)
{
	if (!m_ISerialPort) return ERR_NO_INITIALIZE;
	*dwBaudRate = m_PortConfig.BaudRate;
	*bParity = m_PortConfig.Parity;
	*bStopBits = m_PortConfig.StopBits;
	return ERR_NONE;
}

DWORD _stdcall CHitachi00A::SetPort(BYTE port)
{
	if (!m_ISerialPort) return ERR_NO_INITIALIZE;
	return m_ISerialPort->SetPort(port);
}

DWORD _stdcall CHitachi00A::Connect()
{
	if (!m_ISerialPort) return ERR_NO_INITIALIZE;
	DWORD dr;
	dr = m_ISerialPort->OpenPort();
	if (dr) return dr;
	dr = m_ISerialPort->SetPortConfiguration(&m_PortConfig);
	return ERR_NONE;
}

DWORD _stdcall CHitachi00A::Disconnect()
{
	if (!m_ISerialPort) return ERR_NO_INITIALIZE;
	DWORD dr;
	dr = m_ISerialPort->ClosePort();
	return dr;
}

DWORD _stdcall CHitachi00A::GetResults(ANALYSIS* lpResults,DWORD* lpCount)
{
	if (lpResults == NULL) 
	{
		*lpCount = m_ResultCount;
		return ERR_NONE;
	}
	*lpCount = min (*lpCount,m_ResultCount);
	memcpy(lpResults,m_Results,(*lpCount)*sizeof(m_Results[1]));
	return ERR_NONE;
}

DWORD _stdcall CHitachi00A::ClearResults()
{
	m_ResultCount = 0;
	return ERR_NONE;	
}

DWORD _stdcall CHitachi00A::ProcessFile(char* lpFileName)
{
	return SL_ProcessFile(lpFileName,this,ProcessBuffer);
}

DWORD _stdcall CHitachi00A::OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam)
{
	return ProcessData(Buffer,cant);
}
DWORD _stdcall CHitachi00A::OnCommEvent(DWORD pEventMask,LPVOID lpParam)
{
	return ERR_NONE;
}
DWORD _stdcall CHitachi00A::OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam)
{
	return ERR_NONE;
}
DWORD _stdcall CHitachi00A::OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)
{
	return ERR_NONE;
}
DWORD _stdcall CHitachi00A::OnWaitTimeOut(LPVOID lpParam)
{
	return ERR_NONE;
}
DWORD _stdcall CHitachi00A::OnTrigger(LPVOID lpParam)
{
	return ERR_NONE;
}
DWORD _stdcall CHitachi00A::OnRequestData(LPVOID lpParam)
{
	return ERR_NONE;
}
DWORD _stdcall CHitachi00A::OnSetSerialPort(ISerialPort* lpSerialPort)
{
	m_ISerialPort = lpSerialPort;
	if (!m_ISerialPort) return ERR_NOINTERFACE;
	m_ISerialPort->SetCommunicationMode(true,INFINITE,0,-1);
	return ERR_NONE;
}
DWORD _stdcall CHitachi00A::OnOpenPort(LPVOID lpParam)
{
	m_ISerialPort->SetReadTimeOuts(1,0,0);
	m_ISerialPort->SetPortConfiguration(&m_PortConfig);
	return ERR_NONE;
}

DWORD CHitachi00A::ResetBufferStatus()
{
	// Maquina de estados
	m_frame = IN_NOFRAME;
	m_nextframe = WAIT_HEADER;
	m_separator = 0;
	m_strpos = 0;
	return 0;
}

DWORD CHitachi00A::ProcessBlock()
{
	BYTE block = m_separator;
	m_separator++;
	m_str[m_strpos] = 0;
	m_strpos = 0;
	// revisar si entro un nuevo frame
	if (block == TYPE_POS)
	{
		if ((m_str[1] == HEADER_CHAR)/*&&(m_frame == IN_NOFRAME)*/)
		{
			m_frame = IN_HEADER;
			m_nextframe = WAIT_PACIENT;
			return 0;
		}
		if ((m_str[1] == PACIENT_CHAR)&&(m_nextframe == WAIT_PACIENT))
		{
			m_frame = IN_PACIENT;
			m_nextframe = WAIT_OPERATION;
			return 0;
		}
		if ((m_str[1] == OPERATION_CHAR)&&(m_nextframe == WAIT_OPERATION))
		{
			m_frame = IN_OPERATION;
			m_nextframe = WAIT_RESULT;
			return 0;
		}
		if ((m_str[1] == RESULT_CHAR)&&(m_nextframe == WAIT_RESULT))
		{
			m_frame = IN_RESULT;
			m_nextframe = WAIT_HEADER;
			return 0;
		}
		if ((m_str[1] == LAST_CHAR)&&(m_nextframe == WAIT_LAST))
		{
			m_frame = IN_LAST;
			m_nextframe = WAIT_HEADER;
			return 0;
		}
	}
	// revisar dentro de cual frame estamos
	if ((m_frame == IN_HEADER)||(m_frame == IN_LAST)) return 0;
	if (m_frame == IN_PACIENT)
	{
		if (block == NAME_POS) ::lstrcpyn(m_patient,m_str,200);
		return 0;
	}
	if (m_frame == IN_OPERATION)
	{
		if (block == NOMUESTRA_POS) ::lstrcpyn(m_sample,m_str,10);
		return 0;
	}
	if (m_frame == IN_RESULT)
	{
		if (block == ANALISYS_POS) ::lstrcpyn(m_analysis,m_str,10);
		if (block == VALUE_POS) ::lstrcpyn(m_value,m_str,10);
		if (block == UNIT_POS) ::lstrcpyn(m_unit,m_str,10);
		if (block == DATE_POS) 
		{
			::lstrcpyn(m_time,m_str,20);
			// almacenar todo lo obtenido en un arreglo
			lstrcpy(m_Results[m_ResultCount].Name,m_analysis);
			lstrcpy(m_Results[m_ResultCount].Value_ST,m_value);
			lstrcpy(m_Results[m_ResultCount].No,m_sample);
//			lstrcpy(m_Results[m_ResultCount].Time,m_time);
			lstrcpy(m_Results[m_ResultCount].Unit,m_unit);
			lstrcpy(m_Results[m_ResultCount].PatientName,m_patient);
			m_ResultCount++;
		}
		return 0;
	}
	m_framestatus = WAIT_STX;
	m_frame = IN_NOFRAME;
	m_nextframe = WAIT_HEADER;
	m_separator = 0;
	return 0;
}

DWORD _stdcall CHitachi00A::ProcessBuffer(BYTE *lpBuffer, DWORD dwSize, void *lParam)
{
	return ((CHitachi00A*)lParam)->ProcessData(lpBuffer,dwSize);
}

DWORD CHitachi00A::ProcessData(BYTE *lpData, DWORD dwSize)
{
	DWORD i;
	BYTE  val;
	for (i=0;i<dwSize;i++)
	{
		val = lpData[i];
		// maquina de procesamiento
		if (val == STX) 
		{
			m_strpos = 0;
			m_separator = 0;
			m_framestatus = WAIT_SEPARATOR;
			continue;
		} else
			if (m_framestatus == WAIT_STX) continue;
		if (m_framestatus == WAIT_SEPARATOR)
		{
			if ((val == BREAK) || (val == CR)) 
			{
				ProcessBlock();
				continue;
			}
			if (val == ETX) 
			{
				m_frame = IN_NOFRAME;
				m_framestatus = WAIT_STX;
				continue;
			}
			if (val == 0x5E) val = 0x20;
			m_str[m_strpos] = val;
			m_strpos++;
			continue;
		}
		
	}
	return ERR_NONE;	
}
