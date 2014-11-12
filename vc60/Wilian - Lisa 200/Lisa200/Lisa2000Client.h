// Lisa2000Client.h: interface for the CLisa2000Client class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISA2000CLIENT_H__B5CC624C_1ADA_4EB8_AC4F_F9F60CB88873__INCLUDED_)
#define AFX_LISA2000CLIENT_H__B5CC624C_1ADA_4EB8_AC4F_F9F60CB88873__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TcpIpSocket.h"
#include "ISocketEvents.h"
#include "lisa2000def.h"

// Codigos de error
#define CE_DISCONNECT	10	// No hay coneccion establecida
#define CE_GETINGDATA	11	// Solicitando datos
#define CE_INVDATA		12	// Hay incongruencia en la información
#define CE_CONECTING	13	// Se esta estableciendo una conección
#define CE_CONNECTFAILED 14 // Falla de coneccion

class CLisa2000Client : public CTcpIpSocket,
						private	ITcpIpSocketEvents
{
public:
	DWORD GetResultByPos(DWORD PatPos,DWORD AnaPos,float* lpResult);
	DWORD GetResultByName(char* PatName,char* AnaName,float* lpResult);
	DWORD InvalidateResults();
	DWORD ThreadUpdateAnalisys();
	DWORD Connect(unsigned char b1,unsigned char b2,unsigned char b3,unsigned char b4,unsigned short port);
	DWORD ThreadProcessResultsBuffer(BYTE *Buffer, DWORD dwCant);
	DWORD Initialize();
	DWORD ThreadRequestResults();
	DWORD RequestResults();
	CLisa2000Client();
	virtual ~CLisa2000Client();

private:
	virtual DWORD _stdcall OnClose(LPVOID lpParam,int iErrorCode);
	virtual DWORD _stdcall OnConnect(LPVOID lpParam);
	virtual DWORD _stdcall OnConnectFailed(LPVOID lpParam,int iErrorCode);
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam);
	virtual DWORD _stdcall OnWrite(LPVOID lpParam);	// Ya se proceso la ultima escritura
	virtual DWORD _stdcall OnWriteFailed(LPVOID lpParam,int iErrorCode);
	virtual DWORD _stdcall OnRead(BYTE* Buffer,DWORD dwCant,LPVOID lpParam);
	virtual DWORD _stdcall OnReadFailed(LPVOID lpParam,int iErrorCode);

	// Variables
	POCI_INFO		m_Poci[MAX_POCI];			// Resultados
	ANALYSIS_INFO	m_Analysis[MAX_ANALYSIS];	// Nombre de los analisis
	DWORD			m_ErrorCode;				// Indica si la coneccion fue exitosa o si hubo algun problema
	// estado del cliente
	BYTE m_Status;

	// Relacionadas con la coneccion
	BYTE m_cmd;		// Comando enviado
	char m_tmpstr[50];
	BYTE m_tmppos;

	// Recepcion de resultados
	BYTE m_tmpstatus;	// Estado de la recepcion
	BYTE m_tmppoci;		// No de poci
	BYTE m_tmpana;		// No ana
	float m_tmpval;		// Valor del analisis
	BYTE m_tmpreads;	// Cantidad de lecturas



protected:
	DWORD ThreadProcessAnalisysBuffer(BYTE* Buffer,DWORD dwCant);
};

#endif // !defined(AFX_LISA2000CLIENT_H__B5CC624C_1ADA_4EB8_AC4F_F9F60CB88873__INCLUDED_)


