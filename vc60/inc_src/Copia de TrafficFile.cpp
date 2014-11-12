// TrafficFile.cpp: implementation of the CTrafficFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SockTest.h"
#include "TrafficFile.h"
#include "errorcodes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrafficFile::CTrafficFile()
{
	m_File = INVALID_HANDLE_VALUE;
	m_LastOp = TF_NONE;
	m_BufferCount = 0;
}

CTrafficFile::~CTrafficFile()
{

}

DWORD CTrafficFile::Create(char *pFileName)
{
	m_File = CreateFile(pFileName,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,NULL);
	if (m_File == INVALID_HANDLE_VALUE) return ERR_APIFAIL;

		/*
	DWORD	dr;
	BYTE buffer[255];
	DWORD	CantRead;
	do
	{
		dr = Recv(buffer,255,&CantRead);
		if (hFile != INVALID_HANDLE_VALUE) WriteFile(hFile,buffer,CantRead,&CantRead,NULL);
	} while (CantRead == 255);
	CloseHandle(hFile);
	return ERR_NONE;
	*/
	return 0;
}

DWORD CTrafficFile::Close()
{
	if (m_File != INVALID_HANDLE_VALUE) CloseHandle(m_File);
	m_File = INVALID_HANDLE_VALUE;
	m_LastOp = TF_NONE;
	m_BufferCount = 0;
	return 0;
}

DWORD CTrafficFile::AddRecvBuffer(BYTE *pBuffer, DWORD dwSize)
{
	ProcessBuffer(TF_RECV,pBuffer,dwSize);
	return 0;
}

DWORD CTrafficFile::AddSendBuffer(BYTE *pBuffer, DWORD dwSize)
{
	ProcessBuffer(TF_SEND,pBuffer,dwSize);
	return 0;
}

DWORD CTrafficFile::ProcessBuffer(BYTE bOp, BYTE *pBuffer, DWORD dwSize)
{
	DWORD count;
	if (dwSize == 0) return 0;
	if (bOp != m_LastOp) 
	{
		Write(m_LastOp,m_Buffer,m_BufferCount);
		m_LastOp = TF_NONE;
	}
	// Picar el buffer de 16 en 16
	DWORD start = 0;
	do
	{
		if (m_LastOp == bOp)
		{
			// rellenar el buffer
			count = min(dwSize - start,16-m_BufferCount);
			memcpy(m_Buffer,&pBuffer[m_BufferCount],count);
			m_BufferCount += count;
			if (m_BufferCount != 16) break;
			Write(bOp,m_Buffer,m_BufferCount);
			m_LastOp = TF_NONE;
			start += count;
		}
		m_BufferCount = dwSize - start;
		if (m_BufferCount > 16) 
			Write(bOp,&pBuffer[start],16);
		else
		{
			memcpy(m_Buffer,&pBuffer[start],m_BufferCount);
			m_LastOp = bOp;
		}
		start += 16;
	} while (start < dwSize);
	return 0;
}

DWORD CTrafficFile::Write(BYTE bOp, BYTE *pBuffer, DWORD dwSize)
{
	char str[200];
	int	i;
	BYTE val;
	DWORD writeen;
	if (bOp == TF_NONE) return 0;
	if (dwSize == 0) return 0;

#define SP0		7	// Cantidad de caracteres del tipo de bloque
#define SP1		1   // Cantidad de caracteres entre el tipo de bloque y el primer valor
#define SP2		1   // Cantidad de caracteres despues de cada valor
#define SP3		1	// Cantidad de espacios entre el ultimo byte y el primer ascii

	memset(str,' ',SP0+SP1+(2+SP2)*16+SP3+16);
	str[SP0+SP1+(2+SP2)*16+SP3+16] = 10;
	str[SP0+SP1+(2+SP2)*16+SP3+16+1] = 0;
	if (bOp == TF_RECV) memcpy(str,"Rcv ",4);
	if (bOp == TF_SEND) memcpy(str,"Snd ",4);
	for (i=0;i<dwSize;i++)
	{
		val = pBuffer[i];

		str[SP0+SP1+(2+SP2)*i] = (val >> 4) + '0';
		str[SP0+SP1+(2+SP2)*i+1] = (val & 0x0F) + '0';
		if (str[SP0+SP1+(2+SP2)*i] > '9') str[SP0+SP1+(2+SP2)*i] += 7;
		if (str[SP0+SP1+(2+SP2)*i+1] > '9') str[SP0+SP1+(2+SP2)*i+1] += 7;
		if (val < 32) 
			str[SP0+SP1+(2+SP2)*16+SP3+i] = '.';
		else
			str[SP0+SP1+(2+SP2)*16+SP3+i] = val;
	}
	WriteFile(m_File,str,SP0+SP1+(2+SP2)*16+SP3+16+1,&writeen,NULL);	
	return 0;
}
