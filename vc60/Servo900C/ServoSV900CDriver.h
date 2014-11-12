// IServoSV900CDriver.h: interface for the IServoSV900CDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISERVOSV900CDRIVER_H__F82DAFC8_95A9_4807_95A7_C8E604D63FA0__INCLUDED_)
#define AFX_ISERVOSV900CDRIVER_H__F82DAFC8_95A9_4807_95A7_C8E604D63FA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\clases\SerialPort.h"	
#include "..\interfaces\IServoDriver.h"
#include "..\clases\errorcodes.h"	
#include "ServoSV900C.h"	// Added by ClassView

#define MAX_BED 8	//Hasta 8 camas

class CServoSV900CDriver : public IServoDriver,ICommunicationEvents 
{
public:

	// Interfaz IServoDriver
	virtual DWORD _stdcall Initialize();
	virtual DWORD _stdcall Release();
	virtual DWORD _stdcall GetInterfaz(char* InterfazName,void** lpInterfaz);
	virtual DWORD _stdcall QueryInterface(char* InterfazName,void** lpInterfaz);

	virtual DWORD _stdcall GetParamsCant(DWORD* pcant);
	virtual DWORD _stdcall GetParamData(DWORD pIndex,char** pName,char** pMeasureUnit);
	virtual DWORD _stdcall GetName(char** pName);
	virtual DWORD _stdcall GetServoForBed(DWORD pBedNo,IServo** pServo);
	virtual DWORD _stdcall StartCommunication(DWORD pPortNo);
	
	
	// Interfaz ICommunicationEvents
	virtual DWORD _stdcall OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam);
	virtual DWORD _stdcall OnCommEvent(DWORD pEventMask,LPVOID lpParam);
	virtual DWORD _stdcall OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam);
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam);
	virtual DWORD _stdcall OnWaitTimeOut(LPVOID lpParam);
	virtual DWORD _stdcall OnTrigger(LPVOID lpParam);

public:
	DWORD NextDriverRequest();
	DWORD RequestData();
	CServoSV900CDriver();
	~CServoSV900CDriver();
private:
	CSerialPort SerialPort;
	BOOL OnInitialize;
	BOOL OnOneRequest;	// Indica que al menos un driver adquirio informacion
	BYTE m_CurrentDriver;	// proximo driver a solicitar informacion
	CServoSV900C ServosSV900C[MAX_BED]; //Hasta 8 camas
};

#endif // !defined(AFX_ISERVOSV900CDRIVER_H__F82DAFC8_95A9_4807_95A7_C8E604D63FA0__INCLUDED_)
