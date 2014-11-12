// Servo300.h: interface for the CServo300 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVO300_H__C726E3E5_7A18_4D90_A7FE_EC8F317B8B74__INCLUDED_)
#define AFX_SERVO300_H__C726E3E5_7A18_4D90_A7FE_EC8F317B8B74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SERVO\SVDef.h"
#include "ISerialPortEvents.h"
#include "errorcodes.h"
#include "ISerialPort.h"
#include "dlldef.h"

class CServo300 : public IServo, public ISerialPortEvents  
{
public:
	CServo300();
	~CServo300();
public:
	/*
		IUnknown
	*/
	virtual DWORD _stdcall QueryInterface(char* lpName,_IUnknown** lpInterfaz);
	virtual DWORD _stdcall AddRef();	
	virtual DWORD _stdcall Release();
	virtual DWORD _stdcall Initialize();
	virtual DWORD _stdcall GetInterfaz(char* lpName,_IUnknown** lpInterfaz);
private:
	/*
		ICommunicationEvents
	*/
	virtual DWORD _stdcall OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam);
	virtual DWORD _stdcall OnCommEvent(DWORD pEventMask,LPVOID lpParam);
	virtual DWORD _stdcall OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam);
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam);
	virtual DWORD _stdcall OnWaitTimeOut(LPVOID lpParam);
	virtual DWORD _stdcall OnTrigger(LPVOID lpParam);
	virtual DWORD _stdcall OnRequestData(LPVOID lpParam);
	virtual DWORD _stdcall OnSetSerialPort(ISerialPort* lpSerialPort);
	virtual DWORD _stdcall OnOpenPort(LPVOID lpParam);
public:
	DWORD UnInitialize();
	DWORD Cmd_RC();
	virtual DWORD _stdcall RequestCommand(DWORD CommandID,LPVOID lpCmdData);
	virtual DWORD _stdcall GetCommandExtError(DWORD CommandID);
private:
	DWORD NextCommand();
	DWORD Request_RC(LPVOID lpCmdData);
	DWORD ProcessRCData(BYTE *Buffer, DWORD dwcant);

	DWORD ProcessRV(BYTE* Buffer,DWORD cant);
	DWORD ProcessCC(BYTE* Buffer,DWORD cant);
	DWORD ProcessST(BYTE* Buffer,DWORD cant);
	DWORD ProcessAO(BYTE* Buffer,DWORD cant);
	DWORD ProcessRB(BYTE* Buffer,DWORD cant);
	DWORD ProcessTO(BYTE* Buffer,DWORD cant);
	DWORD ProcessBC(BYTE* Buffer,DWORD cant);
	DWORD ProcessAN(BYTE* Buffer,DWORD cant);

private:
	BYTE	m_CmdState;		// Maquina de estados del comando actual 
	/*
		RC - Read Curve
	*/
	float	m_RCtmpval;		// Temporal
	WORD	m_RCpos;		// Proxima Posicion en el array
	WORD	m_RCphase;		// I E o P
	WORD	m_RCStatus;		// Estatus de las curvas
	DWORD	m_RCError;
	SV_CRV	m_curves[3];	// Curvas obtenidas

	ISerialPort*	m_ISerialPort;
	DWORD	m_cRef;
	BOOL	OnOneRequest;	// si es falso ya se dio una vuelta
	BOOL	m_OnInitialize;

	/*
		Frank
	*/
	DWORD GetAlarmStatus();
	DWORD SetTime();
	DWORD CheckVersion();
	DWORD GetTrendOutput();
	DWORD GetPuntualParams();
	DWORD CheckConnection();
	DWORD ChangeTimeOut();
	DWORD BatteryCheck();
	DWORD GetAddressNo();

	//**************Buffer de comandos que se comparan respuestas
	BYTE m_CC_Buff[8];
	BYTE m_RV_Buff[100];
	BYTE m_ST_Buff[2];
	BYTE m_BC_Buff[3];

	BYTE m_CS_CT_ST_Buff[3];
	BYTE m_CC_Resp[8];
	BYTE m_CS_CT_ST_Resp[3];
	BYTE m_RV_Resp[6];

	//*********************ProcessRB
	int One_Value_Cont;
	int Channel_Cont;

	//*************Instancias de las estructuras donde se devuelven datos
	//*************Instancias de las estructuras donde se devuelven datos
//	SV_BATERY Battery_Val;
//	SV_PP  Buff_PPunt[31];
	
	int  Byte_Counter;//contador de la cantidad de bytes procesados
	bool OnCommand;
	bool VersionFlag;

	DWORD ConnectStatus;		// Estado de la coneccion
	DWORD AddressStatus;
	DWORD VersionStatus;
	DWORD SetTimeStatus;
	DWORD BatteryStatus;		// Estado del chequeo de bateria
	DWORD PPuntualStatus;		// Estado de los parametros puntuales
	DWORD AlarmStatus;
	DWORD TrendStatus;
	BYTE  m_CurrentCommand;	    // Comando que se esta procesando


};

#endif // !defined(AFX_SERVO300_H__C726E3E5_7A18_4D90_A7FE_EC8F317B8B74__INCLUDED_)
