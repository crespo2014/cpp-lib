// Comm32.h: interface for the CComm32 class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_COMM32_H__83B8A541_6076_11D3_A264_0000E856599A__INCLUDED_)
#define AFX_COMM32_H__83B8A541_6076_11D3_A264_0000E856599A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define COM1 1
#define COM2 2

#define COMM1 _T("COM1")
#define COMM2 _T("COM2")

class AFX_EXT_CLASS CComm32  
{
public:
	void SetStopBits(BYTE pStopBits);
	void SetByteSize(BYTE pByteSize);
	void SetParity(DWORD pParity);
	void SetBaudRate(DWORD pBaudRate);
	DWORD ConfigComm();
	void CloseComm();
	DWORD ReadString(LPVOID lpBuffer,LPDWORD lpNumberOfBytesRead);
	DWORD SendString(LPCSTR lpBuffer,DWORD nNumberOfBytesToWrite);
	void SetPort(BYTE port);
	int OpenComm();
	CComm32();
	virtual ~CComm32();

private:
	DWORD m_ModemStat;
	DWORD m_EvtMask;
	void CloseAll();
	// Variable temporal usada para llamada a funciones
	DWORD m_Error;
	// Indica que la clase mostrara mensajes de error
	BOOL m_OnMessage;
	// Indica que el Puerto ya esta abierto
	BOOL m_OnOpen;
	// Usadas para comunicacion asyncronica
	OVERLAPPED m_Read_Overlapped;
	OVERLAPPED m_Write_Overlapped;
	// Configuracion del dispositivo de comunicacion
	COMMCONFIG m_CommConfig;
	// Propiedades del driver de comunicacion
	COMMPROP m_CommProp;
	// Tamaño del buffer de salida
	DWORD m_OutQueue;
	// Tamaño del buffer de entrada
	DWORD m_InQueue;
	// Utilizada para configurar los tiempos del puerto
	COMMTIMEOUTS m_CommTimeOuts;
	// Estructura utilizada para configurar el puerto de comunicacion
	DCB m_DCB;
	// Nombre del puerto parametro pasado a createfile
	char m_Name[6];
	// Handle del Puerto cuando es abierto usada para aceder al mismo
	HANDLE m_HPort;
};

#endif // !defined(AFX_COMM32_H__83B8A541_6076_11D3_A264_0000E856599A__INCLUDED_)
