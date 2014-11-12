// LabDevice.h: interface for the CLabDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LABDEVICE_H__C6ABC54B_30CB_4AEA_8831_D0DCD77F1B1B__INCLUDED_)
#define AFX_LABDEVICE_H__C6ABC54B_30CB_4AEA_8831_D0DCD77F1B1B__INCLUDED_

#include "..\interfaces\Ilabdevice.h"
#include "ISerialPort.h"
#include "ISerialPortEvents.h"
#include "virtualmem.h"

#define MAX_RESULTS 600

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STX		0x02
#define ETX		0x03
#define CR		0x0D
#define LF		0x0A

// tipos de protocolo
#define PROT_NONE	0
#define PROT_ASTM	1

// Tipos de registros
#define RECORD_NONE			0
#define RECORD_HEADER		1
#define RECORD_PATIENT		2
#define RECORD_OPERATION	3
#define RECORD_RESULT		4
#define RECORD_LAST			5

#define ST_NONE			0	// 
#define ST_HEADERBYTES	2	// Se estan procesando los primeros bytes del bloque
#define ST_DATABYTES	3	// Se estan reciviendo bytes de datos


#define FIELD_SIZE			20
#define INSTR_NAME_SIZE		15
#define INSTR_SERNO_SIZE	10

class CLabDevice : protected ILabDevice, 
				   protected CSerialPortEvents, 
				   protected CVirtualMem
{
protected:
	// Iunknown
	virtual DWORD _stdcall DeleteObject();
	virtual DWORD _stdcall Initialize();
	virtual DWORD _stdcall GetInterfaz(char* lpName,void** lpInterfaz);

	// ILabDevice
	virtual DWORD _stdcall SetPort(BYTE port);
	virtual DWORD _stdcall GetName(char* lpBuffer,DWORD* bufferSize);
	virtual DWORD _stdcall SetPortConfiguration(DWORD dwBaudRate,BYTE bParity,BYTE bStopBits);
	virtual DWORD _stdcall GetPortConfiguration(DWORD* dwBaudRate,BYTE* bParity,BYTE* bStopBits);
	virtual DWORD _stdcall Connect();
	virtual DWORD _stdcall Disconnect();
	virtual DWORD _stdcall GetResults(ANALYSIS* lpResults,DWORD* lpCount);
	virtual DWORD _stdcall ClearResults();
	virtual DWORD _stdcall ProcessFile(char* lpFileName);

	// ISerialPortEvents
	virtual DWORD _stdcall OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam);
	virtual DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize)=0;
	virtual DWORD _stdcall OnCommEvent(DWORD pEventMask,LPVOID lpParam);

	virtual DWORD _stdcall ProcessField();
	
	DWORD _stdcall AddAnalysis();
	DWORD ProcessFieldsFrame(BYTE *pbFrame, DWORD dwSize);
	DWORD AddBufferToReport(BYTE* pbBuffer,DWORD dwCant);
	DWORD AddToReport(char* pzsText,BOOL bInsertCRLF = true);
	DWORD CreateReportFile();

	CLabDevice();
	virtual ~CLabDevice();

	// member variables
	char*		m_DeviceName;
	WORD		m_ResultCount;
	ANALYSIS	m_Analysis;
	//BYTE		m_ProtocoloType;
	HANDLE		m_hReportFile;
	BOOL		m_OnReportingInput;	//Indica que lo ultimo que se envio al reporte es un dato de entrada

	// ASTM
	BYTE	m_FieldDelimiter;
	BYTE	m_RepeatDelimiter;
	BYTE	m_ComponentDelimiter;
	BYTE	m_EscapeDelimiter;
	BYTE	m_LastChar;			// Ultimo caracter recibido
	BYTE	m_FieldIndex;		// Indice del elemento dentro del bloque
	BYTE	m_ComponentIndex;	// Indice del componente
	BYTE	m_Status;			// Estado de la maquina de estados
	BYTE	m_HeaderSize;		// Cantidad de bytes de cabecera despues de STX
	char	m_Field[FIELD_SIZE];	//
	BYTE	m_FieldPos;
	BYTE	m_RecordType;		// Tipo de record que se esta procesando
	char	m_InstrumentName[INSTR_NAME_SIZE];
	char	m_InstrumentSerialNo[INSTR_SERNO_SIZE];

private:
	
	
public:
	DWORD PreProcessField();
};

#endif // !defined(AFX_LABDEVICE_H__C6ABC54B_30CB_4AEA_8831_D0DCD77F1B1B__INCLUDED_)
