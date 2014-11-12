// IServoSV900C.h: interface for the IServoSV900C class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISERVOSV900C_H__8F7AADC1_6B6C_447B_ACA6_573F3C746A58__INCLUDED_)
#define AFX_ISERVOSV900C_H__8F7AADC1_6B6C_447B_ACA6_573F3C746A58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\clases\SerialPort.h"
#include "..\interfaces\IServo.h"
#include "..\interfaces\IServoDriver.h"

// Caracteres especiales utilizados en la comunicacion
#define ACK		0x80		// Respuesta confirmativa
#define EOT		0x81		// Fin de transmicion de datos
#define MEXP	0xf1		// Marca de expiracion
#define MEND	0xf3		// Marca de fin de curva

#define LC		1			// LECTURA DE LAS CURVAS
#define LPP		2			// LECTURA DE LOS PARAMETROS PUNTUALES
#define LA		3			// LECTURA DE LAS ALARMAS
#define CC		4			// CHEQUEO DE CONECCION

#define CantParam   21		// Cantidad base de parametros puntuales
#define CantMinutes 15		//  Cantidad base maxima de minutos a guardar de PPuntuales

//BYTES de control utilizados en ProcessPP
#define NextMin	0xf4	// Indica el fin de los 21 parametro y comienz de otro min
#define BUSY	0x91	// El 8031 esta ocupado procesando


#define MAX_GRAPH	100	//Maxima cantidad de valores de las graficas

class CServoSV900C : public IServo   
{
public:
	//Interfaz IServo
	virtual DWORD _stdcall GetGraphs(float* pPressBuff,float* pFlowBuff,float* pVolBuff);
	virtual DWORD _stdcall GetDataLength(DWORD CommandID,DWORD* plength);
	virtual DWORD _stdcall RequestCommand(DWORD CommandID);
	virtual DWORD _stdcall GetExtError(DWORD CommandID);
	virtual DWORD _stdcall GetPuntualParams(float* BufferPPuntuals);
	virtual DWORD _stdcall GetAlarmsStatus(BYTE* AlarmMaskValue);
	
	DWORD SetBedNo(BYTE bBedNo);
	DWORD Initialize();
	DWORD OnSendBytes(DWORD dwBytesWritten);
	DWORD OnReceivedData(BYTE *Buffer, DWORD cant);
	DWORD OnWaitTimeOut();
	DWORD SetMasterDriverInterfaz(void* lpIServoDriver);
	DWORD RequestData();
	DWORD SetSerialInterfaz(CSerialPort* lpISerialPort);
	CServoSV900C();
	~CServoSV900C();
private:
	DWORD GetGraphs();
	DWORD CheckConnection();
	DWORD ProcessCtrlByteCC(BYTE bValue);
	DWORD GetExtErrorLA();
	DWORD GetLPPExtError();
	DWORD LPPOnWaitTimeOut();
	DWORD RequestLA();
	DWORD RequestLC();
	DWORD RequestPP();
	DWORD RequestCC();
	DWORD ProcessDataCC(BYTE Value);
	DWORD ProcessDataLA(BYTE Value);
	DWORD ProcessDataLC(BYTE Value);
	DWORD ProcessDataLPP(BYTE Value);
	DWORD ProcessCtrlBytePP(BYTE CtrlByte);
	DWORD ProcessCtrlByteLC(BYTE bValue);
	DWORD LAOnWaitTimeOut();
	DWORD LCOnWaitTimeOut();
	DWORD CCOnWaitTimeOut();
	DWORD GetExtErrorCC();
	DWORD GetExtErrorLC();
	DWORD ConnectStatus;		// Estado de la coneccion
	DWORD PPuntualStatus;		// Estado de los parametros puntuales
	DWORD GraphStatus;		// Estado de las curvas
	DWORD AlarmErrStatus;		// Estado de las alarmas
	DWORD AlarmDataStatus;		// Estados de la maquina para armar 1DWORD A PARTIR DE 3BYTE 
	DWORD m_ExtErrLC;		// Estado o error extendido
	DWORD m_ExtErrCC;			// Chequeo de coneccion error extendido
	DWORD m_ExtErrPP;			// Parametros puntuales error extendido
	DWORD m_ExtErrLA;			// Lectura de Alarmas   error extendido
	
	CSerialPort* SerialPort;
	void*	MasterDriver;
	BYTE	BedNo;				//Numero de cama
	BYTE	m_CurrentCommand;	// Comando que se esta procesando
	BYTE	m_CmdState;			// Maquina de estado para el procesamiento de comandos

	float	GraphPressE[MAX_GRAPH];
	float	GraphFlow[MAX_GRAPH];
	float	GraphPressI[MAX_GRAPH];
	DWORD	GraphPos;			// Posicion en la curva del proximo valor de entrada
	BYTE	GraphTmpHi;			// Parte alta de la ultima muestra recogida

	int		ContMin,ContParam;
	BYTE	TempHiNibble;
	float	BuffPPunt[CantMinutes][CantParam];
	BYTE   AlarmValue;
	BOOL	OnEot;				// Indica que ya llego el eot

	bool FlagHiNibble;
	bool FlagBedno;
	bool FlagBusy;
};

#endif // !defined(AFX_ISERVOSV900C_H__8F7AADC1_6B6C_447B_ACA6_573F3C746A58__INCLUDED_)
