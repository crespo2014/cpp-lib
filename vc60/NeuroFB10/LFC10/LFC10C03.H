// LFC10C03.h: interface for the CSignalDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LFC10C03_H__D2E3B8E1_7A87_11D4_8632_00D0093D4380__INCLUDED_)
#define AFX_LFC10C03_H__D2E3B8E1_7A87_11D4_8632_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "LFC10C01.h"
#include "LFC10C06.h"

class CApp;

/*
	Informacion perteneciente a cada una de las senales
	que se obtienen 
*/

typedef struct
{
	CSignalFilter Filter;
	float*	Buffer;
	DWORD	Read_Ptr;
	DWORD	Write_Ptr;
	DWORD	Buffer_Len;
	DWORD	Status;
}S_SIGNALDATA;

typedef struct 
{
	DWORD	DeviceState;
	// Tiempo a esperar por la respuesta de un comando
	DWORD	CommandTimeOut;
	// En caso de que lleguen datos que no sean un OK 
	// cantidad que pueden entrar antes de OK
	DWORD	CommandMaxBytes;
	// Indica que se esta procesando un comando
	BOOL	OnCommand;
	// Indica que ya entro el numero de canal
	BOOL	OnValue;
	// Numero de canal que entro;
	DWORD	Channel;	
	// Ultimo valor que entro por el puerto
	DWORD	LastValue;
	// Datos de las senales de entrada
	DWORD			SignalsCant;
	S_SIGNALDATA*	Signals;
	// Notificacion a una ventana
	BOOL	OnNotifyWindow;
	HWND	NotifyHWND;
} S_SIGNALDEVICE;

typedef struct
{
	DWORD  pIndex;
	float* pBuffer;
	DWORD  pCant;
	DWORD* pCantRead;
}S_BUFFER;


class CSignalDevice : public CAsyncCommPort  
{
public:
	int SetDeviceStatus(DWORD pStatus);
	int StopData();
	int StartData();
	int ThreadDestroy();
	int ThreadInit();
	int SendNullMessage();
	int NewSample(DWORD pIndex,float pValue);
	int UpDateSignalsBufferLen(DWORD pLen);
	int UpDateSignalsCant(DWORD pCant);
	int UpDateCoef(DWORD pIndex, double *pCoefA, double *pCoefB, DWORD pOrder);
	int SetFilterCoef(DWORD pIndex,double* pCoefA,double* pCoefB,DWORD pOrder);
	int SetNotifyWindow(HWND pHWnd);
	int SetSignalsBufferLen(DWORD pLen);
	int GetSignal(DWORD pIndex,float* pBuffer,DWORD pCant,DWORD* pCantRead);
	int ReadFromSignal(DWORD pIndex,float* pBuffer,DWORD pCant,DWORD* pCantRead);
	int SetSignalsCant(DWORD pCant);
	int AddToSignal(DWORD pIndex,float pValue);
	virtual int OnWaitTimeOut();
	int ReplyCommand();
	virtual int OnProcessMessage(S_MESSAGE *pMessage);
	virtual int OnReceiveData(BYTE *pBuffer, DWORD pCant);
	int InitSignalDevice();
	int IsDevice();
	int OpenDevice();
	CSignalDevice();
	virtual ~CSignalDevice();
private:
	S_SIGNALDEVICE* Data;
public:
	DWORD SetApp(CApp* lpApp);
	DWORD GameStart();
	DWORD SetParameters(struct parametros* lpparametros,struct datos** lpdatos);
	BOOL	m_disparar;
	DWORD	m_last_time;
	struct parametros*	m_lpparametros;
	struct datos**		m_lpdatos;
	BOOL				m_game_start;
	DWORD				m_cant_muestras;
	DWORD				m_cant_seconds;
	double				m_suma_ieeg_sec;
	double				m_suma_iemg_sec;
	double				m_suma_reeg_sec;
	double				m_suma_temp_sec;
	DWORD				m_burst;
	double				m_prom_ieeg;
	double				m_prom_iemg;
	double				m_prom_reeg;
	double				m_prom_temp;
	DWORD				m_minuto;
	CApp*				m_lpapp;
	double valor[10];				// valores puntuales de las senales
	double				m_prom_ieeg_sec;
	double				m_prom_iemg_sec;
	double				m_prom_reeg_sec;
	DWORD				m_burst_sec;
	DWORD				m_burst_time;

};

#endif // !defined(AFX_LFC10C03_H__D2E3B8E1_7A87_11D4_8632_00D0093D4380__INCLUDED_)
