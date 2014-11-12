// SerialPortBridge.cpp: implementation of the CSerialPortBridge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SerialPortBridge.h"
#include "Winsock2.h"
#include "factory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Interfaz IUnknown

DWORD _stdcall CSerialPortBridge::Initialize()
{
	DWORD dr;
	for (;;)
	{
		dr = CreateInstance("SerialPort32.dll","ISerialPort",(_IUnknown**)&m_SndSerialPort);
		if (dr != 0) break;
		dr = CreateInstance("SerialPort32.dll","ISerialPort",(_IUnknown**)&m_RcvSerialPort);
		if (dr != 0) break;
		m_SndSerialPort->Attach(this);
		m_RcvSerialPort->Attach(this);
		m_RcvSerialPort->SetCommunicationMode(TRUE,INFINITE,(void*)1,-1);
		m_SndSerialPort->SetCommunicationMode(TRUE,INFINITE,(void*)2,-1);
		if (m_SndSerialPort->Initialize() != 0) break;
		if (m_RcvSerialPort->Initialize() != 0) break;
		if (CLockEvent::Initialize() != 0) break;
		m_SndPortBuffer.SerialPort = m_SndSerialPort;
		m_RcvPortBuffer.SerialPort = m_RcvSerialPort;
		return 0;
	}
	UnInitialize();
	return ERR_APIFAIL;
}

DWORD _stdcall CSerialPortBridge::GetInterfaz(char* lpName,void** lpInterfaz)
{
	*lpInterfaz = NULL;
	if (strcmp(lpName,"IUnknown") == 0)	*lpInterfaz = (_IUnknown*) this;
	if (strcmp(lpName,"ISerialPortEvents") == 0) *lpInterfaz = (_IUnknown*)(ISerialPortEvents*)this;
	if (*lpInterfaz == NULL) return ERR_NOINTERFACE;
	return ERR_NONE;
}


CSerialPortBridge::CSerialPortBridge()
{

	// Buffers
	m_RcvPortBuffer.SerialPort = m_RcvSerialPort;
	m_RcvPortBuffer.OnWriting = FALSE;
	m_RcvPortBuffer.ReadIndex = 0;
	m_RcvPortBuffer.WriteIndex = 0;

	m_SndPortBuffer.SerialPort = m_SndSerialPort;
	m_SndPortBuffer.OnWriting = FALSE;
	m_SndPortBuffer.ReadIndex = 0;
	m_SndPortBuffer.WriteIndex = 0;

	m_lpCommunicationBridgeEvents = NULL;

	m_BridgeStatus = BS_OK;
	m_BridgeError = 0;
}

CSerialPortBridge::~CSerialPortBridge()
{
	UnInitialize();
}


DWORD CSerialPortBridge::SetICommunicationBridgeEvents(LPCOMMUNICATIONBRIDGEEVENTS lpCommunicationBridgeEvents)
{
	m_lpCommunicationBridgeEvents = lpCommunicationBridgeEvents;
	return 0;
}

DWORD _stdcall CSerialPortBridge::OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam)
{
	if (cant == 0) return 0;
	if (m_BridgeStatus != BS_OK) return 0;
	COMM_BUFFER* buffer;
	if (Lock() != 0)
	{
		m_BridgeError = GetLastError();
		m_BridgeStatus = BS_ERROR;
		return 1;
	}
	for (;;)
	{
		if (lpParam == (void*)1) 
			buffer = &m_SndPortBuffer;
		else
			buffer = &m_RcvPortBuffer;

		// Adicionar datos al buffer
		if (buffer->WriteIndex + cant > COMM_BUFFER_SIZE)
		{
			cant = COMM_BUFFER_SIZE-buffer->WriteIndex;
			/*
			contar este overflow
			m_BridgeError = GetLastError();
			m_BridgeStatus = BS_OVERFLOW;
			break;
			*/
		}
		if (cant)
		{
			memmove(&buffer->Buffer[buffer->WriteIndex],Buffer,cant);
			buffer->WriteIndex += cant;
			if (!buffer->OnWriting) buffer->SerialPort->SetTrigger();
		}
		break;
	}
	if (UnLock() != 0)
	{
		m_BridgeError = GetLastError();
		m_BridgeStatus = BS_ERROR;
		return 1;
	}
	return 0;
}
DWORD _stdcall CSerialPortBridge::OnCommEvent(DWORD pEventMask,LPVOID lpParam)
{
	ISerialPort* SerialPort;
	DWORD	InSignals;
	DWORD	OutSignals=0;
	if (lpParam == (void*)1)
	{
		m_RcvSerialPort->GetInputSignals(&InSignals);
		SerialPort = m_SndSerialPort;
		if (m_lpCommunicationBridgeEvents)
			m_lpCommunicationBridgeEvents->OnBridgeRcvPortEvent(pEventMask);
	}
	else
	{
		m_SndSerialPort->GetInputSignals(&InSignals);
		SerialPort = m_RcvSerialPort;
		if (m_lpCommunicationBridgeEvents)
			m_lpCommunicationBridgeEvents->OnBridgeSndPortEvent(pEventMask);
	}
	if (pEventMask & (EV_CTS|EV_DSR|EV_RLSD))
	{
		if (InSignals & MS_CTS_ON) 
			SerialPort->ChangeOutputSignal(SETRTS);
		else
			SerialPort->ChangeOutputSignal(CLRRTS);
		if (InSignals & MS_DSR_ON) 
			SerialPort->ChangeOutputSignal(SETDTR);
		else
			SerialPort->ChangeOutputSignal(CLRDTR);
	}
	return 0;
}
DWORD _stdcall CSerialPortBridge::OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam)
{
	DWORD	result = 0;
	COMM_BUFFER* buffer;
	DWORD	Size;
	if (Lock() != 0)
	{
		m_BridgeError = GetLastError();
		m_BridgeStatus = BS_ERROR;
		return 1;
	}
	for (;;)
	{
		if (lpParam == (void*)1) 
		{
			// bytes que envia el 1 son bytes que llegan por el 2
			if (m_lpCommunicationBridgeEvents)
				m_lpCommunicationBridgeEvents->OnBridgeRcvBuffer(Buffer,BytesWritten);
			buffer = &m_RcvPortBuffer;
		}
		else
		{
			// bytes que envia el 2 son bytes que llegaron por el 1
			if (m_lpCommunicationBridgeEvents)
				m_lpCommunicationBridgeEvents->OnBridgeSndBuffer(Buffer,BytesWritten);
			buffer = &m_SndPortBuffer;
		}
		Size = buffer->WriteIndex-BytesWritten; // bytes que faltan
		buffer->WriteIndex = Size;
		memmove(buffer->Buffer,&buffer->Buffer[BytesWritten],Size);
		if (Size)
		{
			buffer->OnWriting = TRUE;
		}
		else
			buffer->OnWriting = FALSE;
		break;
	}
	if (UnLock() != 0)
	{
		m_BridgeError = GetLastError();
		m_BridgeStatus = BS_ERROR;
		buffer = NULL;
		return 1;
	}
	// No se puede enviar dentro del bloqueo
	if (Size) buffer->SerialPort->ThreadSend(buffer->Buffer,Size);
	return 0;

}
DWORD _stdcall CSerialPortBridge::OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)
{
	return 0;
}
DWORD _stdcall CSerialPortBridge::OnWaitTimeOut(LPVOID lpParam)
{
	return 0;
}
DWORD _stdcall CSerialPortBridge::OnTrigger(LPVOID lpParam)
{
	return OnSendBytes(NULL,0,lpParam);
}

DWORD _stdcall CSerialPortBridge::OnRequestData(LPVOID lpParam)
{
	return 0;
}
DWORD _stdcall CSerialPortBridge::OnSetSerialPort(ISerialPort* lpSerialPort)
{
	return 0;
}

DWORD CSerialPortBridge::Start()
{
	if (m_BridgeStatus != BS_STOP)	// Si hubo un error hay que detener el hilo
		return 0;
	for (;;)
	{
		m_BridgeStatus = BS_OK;	// Por si acaso un hilo genera error
		if (m_RcvSerialPort->OpenPort() != 0) break;
		if (m_SndSerialPort->OpenPort() != 0) break;
		return 0;
	}
	m_RcvSerialPort->ClosePort();
	m_BridgeStatus = BS_STOP;
	return 1;
}

DWORD CSerialPortBridge::SetPortConfiguration(BOOL rcvport, PORT_CONFIG *lpPortConfig)
{
	return (rcvport) ? (m_RcvSerialPort->SetPortConfiguration(lpPortConfig)) : (m_SndSerialPort->SetPortConfiguration(lpPortConfig));
}

DWORD CSerialPortBridge::GetPortConfiguration(BOOL rcvport, PORT_CONFIG *lpPortConfig)
{
	return (rcvport) ? (m_RcvSerialPort->GetPortConfiguration(lpPortConfig)) : (m_SndSerialPort->GetPortConfiguration(lpPortConfig));
}

DWORD CSerialPortBridge::GetSerialPort(BOOL rcvport,ISerialPort** lplpISerialPort)
{
	(rcvport) ? (*lplpISerialPort = m_RcvSerialPort) : (*lplpISerialPort = m_SndSerialPort);
	return 0;

}

DWORD CSerialPortBridge::GetPortSignals(BOOL rcvport, DWORD *lpdwSignals)
{
	return (rcvport) ? (m_RcvSerialPort->GetInputSignals(lpdwSignals)) : (m_SndSerialPort->GetInputSignals(lpdwSignals));
}

DWORD CSerialPortBridge::GetCommError(BOOL rcvport, LPDWORD lpErrors)
{
	return (rcvport) ? (m_RcvSerialPort->GetCommunicationError(lpErrors)) : (m_SndSerialPort->GetCommunicationError(lpErrors));
}

DWORD CSerialPortBridge::Stop()
{
	m_SndSerialPort->ClosePort();
	m_RcvSerialPort->ClosePort();
	m_BridgeStatus = BS_STOP;
	return 0;
}

DWORD CSerialPortBridge::GetBridgeStatus(DWORD *dwStatus, int *iError)
{
	/*
	m_SndSerialPort->GetStatus(dwStatus,iError);
	if (*dwStatus != ERR_NONE)
	{
		*dwStatus = BS_PERROR;
		return 0;
	}
	m_RcvSerialPort->GetStatus(dwStatus,iError);
	if (*dwStatus != ERR_NONE)
	{
		*dwStatus = BS_PERROR;
		return 0;
	}
	*dwStatus = m_BridgeStatus;
	*iError = m_BridgeError;
	*/
	return 0;
}

DWORD CSerialPortBridge::OnOpenPort(LPVOID lpParam)
{
	return m_lpCommunicationBridgeEvents->OnBridgePortOpen(lpParam);
}

DWORD _stdcall CSerialPortBridge::UnInitialize()
{
	if (m_SndSerialPort) m_SndSerialPort->Release();
	if (m_RcvSerialPort) m_RcvSerialPort->Release();
	CLockEvent::UnInitialize();
	m_SndSerialPort = NULL;
	m_RcvSerialPort = NULL;
	return 0;
}
