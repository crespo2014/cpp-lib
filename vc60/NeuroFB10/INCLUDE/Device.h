// Device.h: interface for the CDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICE_H__221B68E1_8D53_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_DEVICE_H__221B68E1_8D53_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyFilter.h"

// tama�o del buffer de muestras
#define BUFFER_TAM 1024

//
// Tipo de variable utilizada para el intercambio de informacion con el hilo
// de adquisicion
//

typedef struct S_ReadParams
{
	HANDLE m_HPort;
	OVERLAPPED m_Read_Overlapped;
	// Usadas para devolver informaci�n
	double* m_OutBuffer; // arreglo a ser llenado
	int   m_OutCant;     // cantidad a leer o leida
	double   m_LastValue; // devolver ultimo valor

	double* m_CoefA;
	double* m_CoefB;
	DWORD   m_Order;

	DWORD m_Status;
	CListBox* m_ListBox;

} Exchange;

class CDevice : public CComm32  
{
public:
	UINT ThreadMain();
	static UINT ThreadProc(LPVOID pParam);
	HANDLE m_hEvent1;
	HANDLE m_hEvent2;
	HANDLE m_hEvent3;
	int StartData();
	int GetAlphaDataBuffer(int *pMaxSize, double *pBuffer);
	int SetCoef(double *pCoefA, double *pCoefB, DWORD pOrder,WORD pSignal);
	int SetMuscleCoef(double *pCoefA, double *pCoefB, DWORD pOrder);
	int SetAlphaCoef(double *pCoefA, double *pCoefB, DWORD pOrder);
	int SetThetaCoef(double *pCoefA, double *pCoefB, DWORD pOrder);
	int SetBhetaCoef(double* pCoefA,double* pCoefB,DWORD pOrder);
	int GetDataBuffer(double *pBuffer,WORD pSignal);
	int GetTemperatureDataBuffer(int* pMaxSize,double* pBuffer);
	int GetMuscleDataBuffer(int* pMaxSize,double* pBuffer);
	int GetThetaDataBuffer(int* pMaxSize,double* pBuffer);
	int GetBetaDataBuffer(int* pMaxSize,double* pBuffer);
	int GetPlainDataBuffer( int* pMaxSize,double* pBuffer);
	int GetData( WORD pSignal);
	int GetPlainData();
	int GetBetaData();
	int Close();
	DWORD m_TempError;
	Exchange ThreadParams;
	DWORD InitDevice();
	CDevice();
	virtual ~CDevice();
protected:
	CWinThread* m_ReadThread;
	BOOL m_DeviceOpen;
	BOOL m_DeviceAck;
};

UINT ReadThread( LPVOID pParam );

#endif // !defined(AFX_DEVICE_H__221B68E1_8D53_11D3_A036_0000E8DE4B3B__INCLUDED_)
