// LabDevice.cpp: implementation of the CLabDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\INCLUDE\LabDevice.h"
#include "errorcodes.h"
#include "dllcommon.h"
#include "Factory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




CLabDevice::CLabDevice()
{
	// Puerto serie
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
	m_PortConfig.lParam = NULL;
	m_bAsyncRead = true;
	m_WaitTimeout = INFINITE;
	m_lpParam = NULL;
	m_ReadBufferLen = -1;
	m_ReadIntervalTimeout = 1; 
	m_ReadTotalTimeoutMultiplier = 0; 
	m_ReadTotalTimeoutConstant = 0;

	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_ResultCount = 0;
	SetMaxSize(sizeof(ANALYSIS)*MAX_RESULTS);
	SetSize(0);
	m_hReportFile = INVALID_HANDLE_VALUE;
	m_OnReportingInput = false;
	// Protocolo
	m_FieldDelimiter = 0;
	m_RepeatDelimiter = 0;
	m_ComponentDelimiter = 0;
	m_EscapeDelimiter = 0;
	m_LastChar = 0;			
	m_FieldIndex = 0;		
	m_ComponentIndex = 0;	
	m_Status = 0;			
	m_HeaderSize = 0;		
	m_FieldPos = 0;
	m_RecordType = 0;		
}

CLabDevice::~CLabDevice()
{

}

// Interfaz IUnknown
DWORD _stdcall CLabDevice::DeleteObject()
{
	if (m_ISerialPort) DeleteInstance(m_ISerialPort);
	if (m_hReportFile) CloseHandle(m_hReportFile);
	CVirtualMem::Release();
	m_ISerialPort = NULL;
	m_hReportFile = INVALID_HANDLE_VALUE;
	DLLDestroyInstance(this);
	return 0;				
}

DWORD _stdcall CLabDevice::Initialize()
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
		CreateReportFile();
		AddToReport("CLabDevice initialize OK ...");
		return ERR_NONE;
	}
	return dr;
}

DWORD _stdcall CLabDevice::GetInterfaz(char* lpName,void** lpInterfaz)
{
	*lpInterfaz = NULL;
	if (strcmp(lpName,"ILabDevice") == 0)	*lpInterfaz = (ILabDevice*)this;
	if (strcmp(lpName,"ISerialPortEvents") == 0) *lpInterfaz = (ISerialPortEvents*)this;
	if (*lpInterfaz == NULL) return ERR_NOINTERFACE;
	return ERR_NONE;
}

DWORD _stdcall CLabDevice::GetName(char* lpBuffer,DWORD* bufferSize)
{
	DWORD len = lstrlen(m_DeviceName);
	if (lpBuffer == NULL) 
	{
		*bufferSize = len;
		return ERR_NONE;
	}
	lstrcpyn(lpBuffer,m_DeviceName,*bufferSize);
	if (*bufferSize < len+1) return ERR_OUT_RANGE;
	*bufferSize = len;
	return ERR_NONE;
}

DWORD _stdcall CLabDevice::SetPortConfiguration(DWORD dwBaudRate,BYTE bParity,BYTE bStopBits)
{
	DWORD dr;
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
	dr = m_ISerialPort->SetPortConfiguration(&m_PortConfig);
	if (dr == 0)
	{
		char tmpStr[100];
		sprintf(tmpStr,"\r\nPort Configuration sucess \r\nBaudRate : %d\r\nParity : %d\r\nStopBits : %d",m_PortConfig.BaudRate,m_PortConfig.Parity,m_PortConfig.StopBits);
		AddToReport(tmpStr);
	}
	return dr;
}

DWORD _stdcall CLabDevice::GetPortConfiguration(DWORD* dwBaudRate,BYTE* bParity,BYTE* bStopBits)
{
	if (!m_ISerialPort) return ERR_NO_INITIALIZE;
	*dwBaudRate = m_PortConfig.BaudRate;
	*bParity = m_PortConfig.Parity;
	*bStopBits = m_PortConfig.StopBits;
	return ERR_NONE;
}

DWORD _stdcall CLabDevice::SetPort(BYTE port)
{
	if (!m_ISerialPort) return ERR_NO_INITIALIZE;
	return m_ISerialPort->SetPort(port);
}

DWORD _stdcall CLabDevice::Connect()
{
	if (!m_ISerialPort) return ERR_NO_INITIALIZE;
	DWORD dr;
	dr = m_ISerialPort->OpenPort();
	if (dr) return dr;
	AddToReport("\r\nOpen Port Sucess ...");
	dr = m_ISerialPort->SetPortConfiguration(&m_PortConfig);
	if (dr == ERR_NONE)
	{
		char tmpStr[100];
		sprintf(tmpStr,"Port Configuration sucess \r\nBaudRate : %d\r\nParity : %d\r\nStopBits : %d",m_PortConfig.BaudRate,m_PortConfig.Parity,m_PortConfig.StopBits);
		AddToReport(tmpStr);
	}
	return ERR_NONE;
}

DWORD _stdcall CLabDevice::Disconnect()
{
	if (!m_ISerialPort) return ERR_NO_INITIALIZE;
	DWORD dr;
	dr = m_ISerialPort->ClosePort();
	return dr;
}

DWORD _stdcall CLabDevice::GetResults(ANALYSIS* lpResults,DWORD* lpCount)
{
	if (lpResults == NULL) 
	{
		*lpCount = m_ResultCount;
		return ERR_NONE;
	}
	*lpCount = min (*lpCount,m_ResultCount);
	memcpy(lpResults,Data(),(*lpCount)*sizeof(ANALYSIS));
	return ERR_NONE;
}

DWORD _stdcall CLabDevice::ClearResults()
{
	m_ResultCount = 0;
	return ERR_NONE;	
}

DWORD _stdcall CLabDevice::ProcessFile(char* lpFileName)
{
	HANDLE	hFile;
	DWORD	BytesRead;
	BYTE	buffer[200];
	hFile = CreateFile(lpFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == INVALID_HANDLE_VALUE) return ERR_APIFAIL;
	AddToReport("Processing file ... : ",false);
	AddToReport(lpFileName);
	for(;;)
	{
		if (::ReadFile(hFile,buffer,200,&BytesRead,NULL)) 
		{
			AddBufferToReport(buffer,BytesRead);
			ProcessData(buffer,BytesRead);
		}
		if (!BytesRead) break;
	}
	CloseHandle(hFile);
	return ERR_NONE;
	
}

DWORD _stdcall CLabDevice::OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam)
{
	AddBufferToReport(Buffer,cant);
	return ProcessData(Buffer,cant);
}

DWORD _stdcall CLabDevice::OnCommEvent(DWORD pEventMask,LPVOID lpParam)
{
	char* str1[100];
	str1[0]=0;
	char* str = (char*)str1;
	DWORD error;
	if (pEventMask & EV_BREAK) AddToReport("\r\nComunication error : Line break detected (Se desconecto el equipo)");
	if (pEventMask & EV_ERR)
	{
		strcpy(str,"\r\nComunication error ocurred :");
		m_ISerialPort->GetCommunicationError(&error);
		if (error & CE_FRAME) AddToReport("Framing Error (Revisar parametros del puerto)");
		if (error & CE_OVERRUN) AddToReport("Character-buffer overrun (No deberia pasar)");
		if (error & CE_RXPARITY) AddToReport("Parity error (Revisar parametros del puerto)");
		if (error & CE_BREAK) AddToReport("Line Break (Posible perdida de comunicacion o desconeccion del equipo)");
		if (error & CE_RXOVER) AddToReport("Input buffer overflow - (No deberia pasar)");
		if (error & CE_TXFULL) AddToReport("Output buffer full - (No deberia pasar)");
	}
	return 0;
}

//DEL DWORD _stdcall CLabDevice::OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam)
//DEL {
//DEL 	return ERR_NONE;
//DEL }

//DEL DWORD _stdcall CLabDevice::OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)
//DEL {
//DEL 	return ERR_NONE;
//DEL }

//DEL DWORD _stdcall CLabDevice::OnWaitTimeOut(LPVOID lpParam)
//DEL {
//DEL 	return ERR_NONE;
//DEL }

//DEL DWORD _stdcall CLabDevice::OnTrigger(LPVOID lpParam)
//DEL {
//DEL 	return ERR_NONE;
//DEL }

//DEL DWORD _stdcall CLabDevice::OnRequestData(LPVOID lpParam)
//DEL {
//DEL 	return ERR_NONE;
//DEL }

DWORD CLabDevice::AddAnalysis()
{
	DWORD dr;
	dr = SetSize(sizeof(ANALYSIS)*(m_ResultCount+1));
	if (dr != ERR_NONE) return dr;
	ANALYSIS* analysis;
	analysis = (ANALYSIS*)&(Data()[sizeof(ANALYSIS)*m_ResultCount]);
	*analysis = m_Analysis;
	m_ResultCount++;
	char	tmpStr[255];
	sprintf(tmpStr,"\r\nAnalysis Add ...\r\nPatient : %s\r\nAnalysis : %s\r\nValue : %f %s",analysis->PatientName,analysis->Name,analysis->Value,analysis->Unit);
	AddToReport(tmpStr);
	return 0;
}

DWORD CLabDevice::CreateReportFile()
{
	SYSTEMTIME systemTime;
	char		fileName[30];
	if (m_hReportFile != INVALID_HANDLE_VALUE) CloseHandle(m_hReportFile);
	::GetSystemTime(&systemTime);
	sprintf(fileName,"R%04d%02d%02d_%02d%02d%02d%03d.txt",systemTime.wYear,systemTime.wMonth,systemTime.wDay,systemTime.wHour,systemTime.wMinute,systemTime.wSecond,systemTime.wMilliseconds);
	m_hReportFile = ::CreateFile(fileName,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (m_hReportFile == INVALID_HANDLE_VALUE) return ERR_APIFAIL;
	m_OnReportingInput = false;
	AddToReport("Report File ...\r\nDevice : ",false);
	AddToReport(m_DeviceName);
	return ERR_NONE;
}

DWORD CLabDevice::AddToReport(char *pzsText,BOOL bInsertCRLF)
{
	DWORD	bytesWritten;
	if (m_hReportFile == INVALID_HANDLE_VALUE) return ERR_NO_FILE;
	if (m_OnReportingInput) WriteFile(m_hReportFile,"\r\n\r\n",4,&bytesWritten,NULL);
	WriteFile(m_hReportFile,pzsText,strlen(pzsText),&bytesWritten,NULL);
	if (bInsertCRLF) WriteFile(m_hReportFile,"\r\n",2,&bytesWritten,NULL);
	m_OnReportingInput = false;
	return 0;
}

DWORD CLabDevice::AddBufferToReport(BYTE *pbBuffer, DWORD dwCant)
{
	DWORD	i;
	char	tmpStr[10];
	if (m_hReportFile == INVALID_HANDLE_VALUE) return ERR_NO_FILE;
	if (dwCant != 0)
	{
		if (!m_OnReportingInput) AddToReport("\r\nReceived : ",false);
		m_OnReportingInput = false;
		for (i=0;i<dwCant;i++)
		{
			if ((pbBuffer[i] > 32) && (pbBuffer[i] < 128))
			{
				tmpStr[0] = pbBuffer[i];
				tmpStr[1] = 0x0;
			}
			else
				sprintf(tmpStr,"<%02X>",pbBuffer[i]);
			AddToReport(tmpStr,false);
		}
		m_OnReportingInput = true;
	}
	return ERR_NONE;
}

DWORD CLabDevice::ProcessFieldsFrame(BYTE *pbFrame, DWORD dwSize)
{
	DWORD i;
	for (i=0;i<dwSize;i++)
	{
		m_LastChar = pbFrame[i];
		if ((m_LastChar == STX)||
			(m_LastChar == CR)||
			(m_LastChar == LF)||
			(m_LastChar == ETX)||
			(m_LastChar == m_ComponentDelimiter)||
			(m_LastChar == m_FieldDelimiter))
		{
			if ((m_FieldIndex != 0) || (m_LastChar != STX))
				PreProcessField();
			if (m_LastChar == m_ComponentDelimiter) 
			{
				m_ComponentIndex++;
				continue;
			}
			if (m_LastChar == STX) 
			{
				m_Status = ST_HEADERBYTES;
				m_FieldIndex = 0;
				PreProcessField();
				continue;
			}
			m_ComponentIndex = 0;
			m_FieldIndex++;
			continue;
		}
		m_Field[m_FieldPos] = m_LastChar;
		m_FieldPos++;
		if ((m_Status == ST_HEADERBYTES) && (m_FieldPos == m_HeaderSize))
		{
			m_Status = ST_DATABYTES;
			PreProcessField();
			m_FieldIndex++;
		}

	}
	return 0;
}

DWORD _stdcall CLabDevice::ProcessField()
{
	return 0;
}

DWORD CLabDevice::PreProcessField()
{
	m_Field[m_FieldPos] = 0;
	ProcessField();
	m_FieldPos = 0;
	return 0;
}
