// ILabDevice.h: interface for the ILabDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILABDEVICE_H__576FCCA5_E822_43E5_91F0_76DF63DEAC41__INCLUDED_)
#define AFX_ILABDEVICE_H__576FCCA5_E822_43E5_91F0_76DF63DEAC41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_IUnknown.h"

#define AN_PATIENT_SIZE 50
#define AN_NO_SIZE		10
#define AN_NAME_SIZE	10
#define AN_UNIT_SIZE	10
#define AN_AN_ST_SIZE	12	
#define AN_VAL_ST_SIZE	12	

struct ANALYSIS
{
	DWORD	Flags;							// De proposito general y para soportar multiples versiones
	char	PatientName[AN_PATIENT_SIZE];	// Nombre del paciente
	char	sex;							// sexo M o F
	char	No[AN_NO_SIZE];					// No de analisis o consecutivo
	char	Name[AN_NAME_SIZE];				// Tipo de analisis
	char	Unit[AN_UNIT_SIZE];
	char	Analis_ST[AN_AN_ST_SIZE];		// estado del analisis NORMAL
	char	Value_ST[AN_VAL_ST_SIZE];		// estado del resultado < ó >
	float	Value;
	BYTE	Day;
	BYTE	Month;
	WORD	Year;
	BYTE	Hour;
	BYTE	Minute;
	BYTE	Second;
};

class ILabDevice : public CUnknown 
{
public:
	virtual DWORD _stdcall GetName(char* lpBuffer,DWORD* bufferSize) = 0;
	virtual DWORD _stdcall SetPort(BYTE port) = 0;
	virtual DWORD _stdcall SetPortConfiguration(DWORD dwBaudRate,BYTE bParity,BYTE bStopBits) = 0;
	virtual DWORD _stdcall GetPortConfiguration(DWORD* dwBaudRate,BYTE* bParity,BYTE* bStopBits) = 0;
	virtual DWORD _stdcall Connect() = 0;
	virtual DWORD _stdcall Disconnect() = 0;
	virtual DWORD _stdcall GetResults(ANALYSIS* lpResults,DWORD* lpCount) = 0;
	virtual DWORD _stdcall ClearResults() = 0;
	virtual DWORD _stdcall ProcessFile(char* lpFileName) = 0;
};



#endif // !defined(AFX_ILABDEVICE_H__576FCCA5_E822_43E5_91F0_76DF63DEAC41__INCLUDED_)
