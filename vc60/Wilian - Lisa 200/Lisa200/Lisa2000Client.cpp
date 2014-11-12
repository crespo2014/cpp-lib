// Lisa2000Client.cpp: implementation of the CLisa2000Client class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lisa2000Client.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/* 
Procesamiento de la informacion recivida

Cuando se reciven los tipos de analisis
m_tmpstatus	  // Indica que se está reciviendo 
*/

#define RCV_INDEX	1 // Indice
#define RCV_ANANAME	2 // Nombre 
#define RCV_MUNIT	3 // Unidad de medida
/*
	m_tmp02 almacena el indice del analisis cuando ya entro
*/

// Estados de recepcion de los resultados
#define RCV_POCIINDEX	1
#define RCV_POCINAME	2
#define RCV_ANAINDEX	3
#define RCV_ANAVAL		4
#define RCV_ANAREADS	5

#define TM_REQUEST	200	// Mensaje para solicitar los resultados

// Estados en los que se puede encontrar el cliente
#define CS_DISCONNECT	2	// Ver error
#define CS_CONECTING	3
#define CS_CONECTED		4
#define CS_GETINGDATA	5	// Solicitando datos
#define CS_DATAOK		6	// Datos solicitados
#define CS_INVDATA		7	// Hay incongruencia en la informacion




CLisa2000Client::CLisa2000Client()
{
	int i,j;
	SetSocketEvents(this);
	m_Status = CS_DISCONNECT;
	m_ErrorCode = 0;
	m_cmd = 0;
	for (i=0;i<MAX_POCI;i++)
		for (j=0;j<MAX_ANALYSIS;j++)
		{
			m_Poci[i].analysis[j].reads = 0;
		}
	for (j=0;j<MAX_ANALYSIS;j++)
	{
		m_Analysis[j].name[0] = 0;
	}
}

CLisa2000Client::~CLisa2000Client()
{

}

DWORD _stdcall CLisa2000Client::OnClose(LPVOID lpParam,int iErrorCode)
{
	m_ErrorCode = iErrorCode;
	m_Status = CS_DISCONNECT;
	return 0;
}
DWORD _stdcall CLisa2000Client::OnConnect(LPVOID lpParam)
{
	m_Status = CS_CONECTED;
	return 0;
}
DWORD _stdcall CLisa2000Client::OnConnectFailed(LPVOID lpParam,int iErrorCode)
{
	m_ErrorCode = iErrorCode;
	m_Status = CS_DISCONNECT;
	return 0;
}
DWORD _stdcall CLisa2000Client::OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)
{
	switch (lpMessage->Msg)
	{
	case TM_REQUEST : return ThreadRequestResults();

	}
	return 0;
}
DWORD _stdcall CLisa2000Client::OnWrite(LPVOID lpParam)
{
	return 0;
}
DWORD _stdcall CLisa2000Client::OnWriteFailed(LPVOID lpParam,int iErrorCode)
{
	m_ErrorCode = iErrorCode;
	m_Status = CS_INVDATA;
	return 0;
}
DWORD _stdcall CLisa2000Client::OnRead(BYTE* Buffer,DWORD dwCant,LPVOID lpParam)
{
	switch (m_cmd)
	{
	case CMD_ANAINFO : ThreadProcessAnalisysBuffer(Buffer,dwCant);break;
	case CMD_RESULTS : ThreadProcessResultsBuffer(Buffer,dwCant);break;
	}
	return 0;
}
DWORD _stdcall CLisa2000Client::OnReadFailed(LPVOID lpParam,int iErrorCode)
{
	m_ErrorCode = iErrorCode;
	m_Status = CS_INVDATA;
	return 0;
}

DWORD CLisa2000Client::ThreadProcessAnalisysBuffer(BYTE *Buffer, DWORD dwCant)
{
	DWORD i;
	BYTE val;
	for (i=0;i<dwCant;i++)
	{
		val = Buffer[i];
		switch (m_tmpstatus)
		{
		case RCV_INDEX:
			{
				if (val == 255) 
				{
					m_Status = CS_DATAOK;
					m_cmd = 0;
					return 0;
				}
				m_tmpana = val;
				m_tmpstatus = RCV_ANANAME;
				m_tmppos = 0;
				break;
			}
		case RCV_ANANAME:
			{
				m_tmpstr[m_tmppos] = val;
				m_tmppos++;
				if (val == 0)
				{
					m_tmpstatus = RCV_MUNIT;
					strcpy(m_Analysis[m_tmpana].name,m_tmpstr);
					m_tmppos = 0;
				}
				break;
			}
		case RCV_MUNIT:
			{
				m_tmpstr[m_tmppos] = val;
				m_tmppos++;
				if (val == 0)
				{
					m_tmpstatus = RCV_INDEX;
					strcpy(m_Analysis[m_tmpana].measured_unit,m_tmpstr);
					m_tmppos = 0;
				}
				break;
			}
		}
	}
	return 0;
}

DWORD CLisa2000Client::RequestResults()
{
	switch (m_Status)
	{
	case CS_CONECTING  :
	case CS_DISCONNECT : return CE_DISCONNECT;
	case CS_GETINGDATA : return CE_GETINGDATA;
	case CS_DATAOK	   : 
		{
			return 0;
		}
	case CS_INVDATA	   : return CE_INVDATA;
	}
	S_MESSAGE Message;
	Message.Msg=TM_REQUEST;
	if (SendMessage(&Message) != 0)
		return 1;
	if (Message.Result != 0)
		return 1;
	return CE_GETINGDATA;
}

DWORD CLisa2000Client::ThreadRequestResults()
{
	m_Status = CS_GETINGDATA;
	BYTE* buffer;
	DWORD size;
	m_cmd = CMD_RESULTS;
	ThreadGetSendBuffer(&buffer,&size);
	buffer[0] = CMD_RESULTS;
	m_tmpstatus = RCV_POCIINDEX;
	ThreadSend(1);
	return 0;
}

DWORD CLisa2000Client::Initialize()
{
	CTcpIpSocket::Initialize();
	return 0;
}

DWORD CLisa2000Client::ThreadProcessResultsBuffer(BYTE *Buffer, DWORD dwCant)
{
	DWORD i;
	BYTE val;
	for (i=0;i<dwCant;i++)
	{
		val = Buffer[i];
		switch (m_tmpstatus)
		{
		case RCV_POCIINDEX:
			{
				if (val == 255) 
				{
					return ThreadUpdateAnalisys();
				}
				m_tmppoci = val;
				m_tmpstatus = RCV_POCINAME;
				m_tmppos = 0;
				break;
			}
		case RCV_POCINAME:
			{
				m_tmpstr[m_tmppos] = val;
				m_tmppos++;
				if (val == 0)
				{
					m_tmpstatus = RCV_ANAINDEX;
					strcpy(m_Poci[m_tmppoci].name,m_tmpstr);
					m_tmppos = 0;
				}
				break;
			}
		case RCV_ANAINDEX:
			{
				if (val == 255) 
				{
					m_tmpstatus = RCV_POCIINDEX;
					break;
				}
				m_tmpana = val;
				m_tmpstatus = RCV_ANAVAL;
				m_tmppos = 0;
				break;
			}
		case RCV_ANAVAL:
			{
				((BYTE*)(&m_tmpval))[m_tmppos] = val;
				m_tmppos++;
				if (m_tmppos == sizeof(float))
				{
					m_tmpstatus = RCV_ANAREADS;
				}
				break;
			}
		case RCV_ANAREADS:
			{
				if (val > m_Poci[m_tmppoci].analysis[m_tmpana].reads) 
				{
					m_Poci[m_tmppoci].analysis[m_tmpana].reads = val;
					m_Poci[m_tmppoci].analysis[m_tmpana].val = m_tmpval;
				}
				m_tmpstatus = RCV_ANAINDEX;
				break;
			}
		}
	}
	return 0;
}

DWORD CLisa2000Client::Connect(unsigned char b1, unsigned char b2, unsigned char b3, unsigned char b4, unsigned short port)
{
	CTcpIpSocket::SetServer(b1,b2,b3,b4,port);
	switch (CTcpIpSocket::Connect())
	{
	case SE_CONNECTING : return CE_CONECTING;
	case SE_CONNECTFAILED: return CE_CONNECTFAILED;
	}
	return 0;
}

DWORD CLisa2000Client::ThreadUpdateAnalisys()
{
	int i,j;
	// Validar los analisis
	for (i=0;i<MAX_POCI;i++)
	{
		for (j=0;j<MAX_ANALYSIS;j++)
		{
			if (m_Poci[i].analysis[j].reads != 0)
			{
				if (m_Analysis[j].name[0] == 0)
				{
					m_Status = CS_GETINGDATA;
					BYTE* buffer;
					DWORD size;
					m_cmd = CMD_ANAINFO;
					ThreadGetSendBuffer(&buffer,&size);
					buffer[0] = CMD_ANAINFO;
					m_tmpstatus = RCV_INDEX;
					ThreadSend(1);
					return 0;
				}
			}
		}
	}
	m_Status = CS_DATAOK;
	m_cmd = 0;
	return 0;
}

DWORD CLisa2000Client::InvalidateResults()
{
	if (m_Status == CS_DATAOK)
		m_Status = CS_CONECTED;
	return 0;
}

DWORD CLisa2000Client::GetResultByName(char *PatName, char *AnaName, float *lpResult)
{
	// Buscar nombre del paciente
	int i,j;
	for (i=0;i<MAX_POCI;i++)
	{
		if (strcmp(PatName,m_Poci[i].name)== 0)
		{
			for (j=0;j<MAX_ANALYSIS;j++)
			{
				if (strcmp(AnaName,m_Analysis[j].name)==0)
				{
					if  (m_Poci[i].analysis[j].reads == 0)
						return ERR_NOANALISYS;
					*lpResult = m_Poci[i].analysis[j].val;
					return ERR_SUCCESS;
				}
			}
			return ERR_NOANALISYS;
		}
	}
	return ERR_NOPATIENT;
}

DWORD CLisa2000Client::GetResultByPos(DWORD PatPos, DWORD AnaPos, float *lpResult)
{
	if (m_Poci[PatPos].name[0] == 0)
		return ERR_NOPATIENT;
	if (m_Analysis[AnaPos].name[0] == 0)
		return ERR_NOANALISYS;
	if (m_Poci[PatPos].analysis[AnaPos].reads == 0)
		return ERR_NOANALISYS;
	*lpResult = m_Poci[PatPos].analysis[AnaPos].val;
	return ERR_SUCCESS; 
}
