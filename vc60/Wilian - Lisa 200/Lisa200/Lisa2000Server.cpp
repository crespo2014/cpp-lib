// Lisa2000Server.cpp: implementation of the CLisa2000Server class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lisa2000Server.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



CLisa2000Server::CLisa2000Server()
{
	int i;
	m_OnLisa2000Init = FALSE;
	for (i=0;i<MAX_CONECCTIONS;i++)
	{
		m_Conecctions[i].OnActive = false;
	}
	SetServerEvents(this);
	SetICommunicationBridgeEvents(this);
}

CLisa2000Server::~CLisa2000Server()
{
	Release();
}

DWORD _stdcall CLisa2000Server::OnBridgeSndBuffer(BYTE *buffer, DWORD dwsize)
{
	ProcessSndBuffer(buffer,dwsize);
	return 0;
}

DWORD _stdcall CLisa2000Server::OnBridgeRcvBuffer(BYTE *buffer, DWORD dwsize)
{
	ProcessRcvBuffer(buffer,dwsize);
	return 0;
}

DWORD _stdcall CLisa2000Server::OnBridgeSndPortEvent(DWORD pEventMask)
{
	return 0;
}

DWORD _stdcall CLisa2000Server::OnBridgeRcvPortEvent(DWORD pEventMask)
{
	return 0;
}


DWORD _stdcall CLisa2000Server::OnSocketClose(LPVOID lpParam,DWORD SockID,int iErrorCode)
{
	CONNECTION_INFO*	ptrcn;
	ptrcn = (CONNECTION_INFO*)lpParam;
	ptrcn->OnActive = false;
	return 0;
}

DWORD _stdcall CLisa2000Server::OnSocketConnect(DWORD SockID)
{
	// Buscar una coneccion vacia
	for (int i=0;i<MAX_CONECCTIONS;i++)
		if (!m_Conecctions[i].OnActive)
		{
			m_Conecctions[i].cmd = CMD_NONE;
			m_Conecctions[i].OnActive = true;
			ThreadSetSocketParam(SockID,&m_Conecctions[i]);
			return 0;
		}
	// en caso de estar todas llenas hay que cerrar el socket
	return 1;
}

DWORD _stdcall CLisa2000Server::OnServerProcessMessage(LP_MESSAGE lpMessage)
{
	return 0;
}

DWORD _stdcall CLisa2000Server::OnSocketWrite(LPVOID lpParam,DWORD SockID)
{
	// Ver si es la primera escritura
	CONNECTION_INFO*	ptrcn;
	ptrcn = (CONNECTION_INFO*)lpParam;
	if (ptrcn == NULL) return 1;
	if (ptrcn->OnActive == false) return 1;
	if (ptrcn->cmd == 0) return 0;
	// Ver el estado del comando
	switch(ptrcn->cmd)
	{
	case CMD_ANAINFO : SendAnalysisInfo(ptrcn,SockID);break;
	case CMD_RESULTS : ThreadSendResults(ptrcn,SockID);break;
	}
	return 0;
}

DWORD _stdcall CLisa2000Server::OnSocketWriteFailed(LPVOID lpParam,DWORD SockIDint,int iErrorCode)
{
	// Desconectar el socket que ocasiono el problema
	return 0;
}

DWORD _stdcall CLisa2000Server::OnSocketRead(BYTE* Buffer,DWORD dwCant,LPVOID lpParam,DWORD SockID)
{
	// Analizar el comando que se envia
	if (dwCant == 0) return 0;
	CONNECTION_INFO*	ptrcn;
	ptrcn = (CONNECTION_INFO*)lpParam;
	if (ptrcn == NULL) return 1;
	ptrcn->cmd = Buffer[0];
	ptrcn->tmp01 = 0;
	ptrcn->tmp02 = 0;
	OnSocketWrite(lpParam,SockID);
	return 0;
}

DWORD _stdcall CLisa2000Server::OnSocketReadFailed(LPVOID lpParam,DWORD SockID,int iErrorCode)
{
	// Desconectar el socket que ocasiono el problema
	return 0;
}


DWORD CLisa2000Server::Initialize()
{
	if (m_OnLisa2000Init == TRUE)
		return 0;
	for (;;)
	{
		if (CSerialPortBridge::Initialize() != 0) break;
		if (CTcpIpServer::Initialize() != 0) break;
		m_OnLisa2000Init = TRUE;
		return 0;
	}
	Release();
	return 1;
}

DWORD CLisa2000Server::Release()
{
	return 0;
}

DWORD CLisa2000Server::SendAnalysisInfo(CONNECTION_INFO* lpconinf,DWORD SockID)
{
	ANALYSIS_INFO anainfo;
	DWORD bufferpos = 0;
	BYTE* buffer;
	DWORD size;
	ThreadGetSendBuffer(SockID,&buffer,&size);
	for (;;)
	{
		// ver si hay espacio suficiente en el buffer
		if (size - bufferpos < ANALYSIS_MAXLEN+UNIT_MAXLEN+1)
		{
			// comprobar si es debido al poco tamaño del buffer
			if (bufferpos == 0) return 1;
			// Enviar el buffer hasta donde se lleno
			break;
		}
		// seguir por donde me quede
		if (lpconinf->tmp01 == MAX_ANALYSIS)
		{
			// Ya se enviaron todos los analisis
			buffer[bufferpos] = 255;
			bufferpos++;
			lpconinf->cmd = CMD_NONE;
			break;
		}
		GetAnalysisInfo(lpconinf->tmp01,&anainfo);
		if (anainfo.name[0] != 0)
		{
			// Enviar el analisis solo si tiene un nombre valido
			buffer[bufferpos] = lpconinf->tmp01;
			bufferpos++;
			int size = strlen(anainfo.name);
			memcpy(&buffer[bufferpos],anainfo.name,size+1);
			bufferpos+=(size+1);
			size = strlen(anainfo.measured_unit);
			memcpy(&buffer[bufferpos],anainfo.measured_unit,size+1);
			bufferpos+=size+1;
		}
		lpconinf->tmp01++;
	}
	ThreadSend(SockID,bufferpos);
	return 0;
}

DWORD CLisa2000Server::ThreadSendResults(CONNECTION_INFO *lpconinf, DWORD SockID)
{
	ANA_STATUS analisys;
	char*	name;
	DWORD bufferpos = 0;
	BYTE* buffer;
	DWORD size;
	ThreadGetSendBuffer(SockID,&buffer,&size);
	for (;;)
	{
		// Validar la posicion ya que puede ser cambiada 
		if (lpconinf->tmp02 == MAX_ANALYSIS)
		{
			lpconinf->tmp02 = 0;
			lpconinf->tmp01++;
		}
		if (lpconinf->tmp01 == MAX_POCI)
		{
			buffer[bufferpos] = 255;
			bufferpos++;
			lpconinf->cmd = CMD_NONE;
			break;
		}
		// verificar que cabe el nombre y la primera muestra o una muestra en caso de que ya este pueto el nombre
		if (size - bufferpos < ((lpconinf->tmp02 == 0) ? (1+POCI_MAXLEN+1+sizeof(float)4+1+1):(1+sizeof(float)4+1+1)))
		{
			// comprobar si es debido al poco tamaño del buffer
			if (bufferpos == 0) return 1;
			// Enviar el buffer hasta donde se lleno
			break;
		}
		if (lpconinf->tmp02 == 0)
		{
			for (;;)
			{
				// Validar el nombre del pocillo
				GetName(lpconinf->tmp01,&name);
				if (name[0]==0)
				{ 
					lpconinf->tmp02 = MAX_ANALYSIS;
					break;
				}
				// Buscar un analisis valido
				GetAnalysis(lpconinf->tmp01,lpconinf->tmp02,&analisys);
				if (analisys.reads != 0)
				{
					// Poner nombre del pocillo
					buffer[bufferpos] = lpconinf->tmp01;
					bufferpos++;
					int len = strlen(name);
					memcpy(&buffer[bufferpos],name,len+1);
					bufferpos+=(len+1);
					break;
				}
				else
					lpconinf->tmp02++;
				if (lpconinf->tmp02 == MAX_ANALYSIS)
					break;
			}
		}
		// Procesar solo si el analisis esta en un indice valido
		if (lpconinf->tmp02 != MAX_ANALYSIS)
		{
			GetAnalysis(lpconinf->tmp01,lpconinf->tmp02,&analisys);
			if (analisys.reads != 0)
			{
				// Enviar el analisis solo si tiene una lectura
				buffer[bufferpos] = lpconinf->tmp02;
				bufferpos++;
				memcpy(&buffer[bufferpos],&analisys.val,sizeof(float));
				bufferpos+=sizeof(float);
				buffer[bufferpos] = analisys.reads;
				bufferpos++;
			}
			lpconinf->tmp02++;
			// Si se alcanzo el ultimo analisis poner marca de fin
			if (lpconinf->tmp02 == MAX_ANALYSIS)
			{
				buffer[bufferpos] = 255;
				bufferpos++;
			}
		}
	}
	ThreadSend(SockID,bufferpos);
	return 0;
}
