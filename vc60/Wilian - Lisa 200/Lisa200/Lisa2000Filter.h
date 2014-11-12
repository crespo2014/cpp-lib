// Lisa2000Filter.h: interface for the CLisa2000Filter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISA2000FILTER_H__19DAB8E7_907A_4AB2_8062_A349F2AF06E0__INCLUDED_)
#define AFX_LISA2000FILTER_H__19DAB8E7_907A_4AB2_8062_A349F2AF06E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lisa2000def.h"

// Estados del filtro
#define ST_WAIT_COMMAND	0	// Debe enviarse un comando
#define ST_WAIT_ANSWER	1	// Ya se envio el comando se espera una respuesta
#define ST_WAIT_DATA	2	// Se espera envio de datos de alguna parte respuesta 1B
#define ST_SND_DATA		3	// Se estan enviando datos
#define ST_RCV_DATA		4	// Se estan reciviendo datos

// Estados de la impresion
#define PRT_WAIT		0	// Esperando una impresion
#define PRT_COD_WAIT	1	// Se espera COD
#define PRT_COD_20		2	// Se espera el 20 antes del codigo
#define PRT_COD_GET		3	// Se espera el codigo
#define PRT_POCI_20		4	// Se espera 20 antes de POCI
#define PRT_POCI_READ	5	// Se espera leer POCI
#define PRT_POCI_WAIT	6	// Se espera 20 antes del numero de posillo
#define PRT_POCI_GET	7	// Se espera el numero de pocillo
#define PRT_FECH_20		8	// Se espera 20 antes de FECH
#define PRT_FECH_READ	9	// Se espera leer FECH
#define PRT_FECH_WAIT	10	// Se espera 20 antes de la fecha
#define PRT_FECH_GET	11	// Se espera leer la fecha
#define PRT_HORA_20		12	// Se espera el 20 antes de HORA
#define PRT_HORA_READ	13	// Se espera leer HORA
#define PRT_HORA_WAIT	14	// Se espera el 20 antes de la HORA
#define PRT_HORA_GET	15	// Se espera leer la hora
#define PRT_HORA_0D		16	// Se espera el fin de linea despues de la hora
#define PRT_ANA_0D		17	// Esperar fin de linea del analisis que acaba de terminar
#define PRT_ANA_20		18	// Se espera el 20 antes del nombre del analisis
#define PRT_ANA_GET		19	// Se espera el nombre del analisis
#define PRT_VAL_WAIT	20	// Se espera el 20 antes del valor del analisis
#define PRT_VAL_GET		21	// Se espera el valor del analisis.
#define PRT_MU_20		22	// Se espera el 20 antes de la unidad de medida
#define PRT_MU_GET		23	// Se espera la unidad de medida


#define PRT_NONE		0
#define PRT_IGNORE		1	// Ignorar la impresion en curso
#define PRT_USR			2

class CLisa2000Filter  
{
public:
	DWORD FillListBox(HWND hControl);
	DWORD ProcessResult();
	DWORD ProcessPrintByte(BYTE Val);
	DWORD ClearString(char* string);
	DWORD EnableCommand(BYTE bCmd,BOOL bEnable);
	DWORD SaveToFile(HANDLE hFile);
	DWORD ProcessSndByte(BYTE Val);
	DWORD ProcessRcvByte(BYTE Val);
	
	CLisa2000Filter();
	virtual ~CLisa2000Filter();

	char m_OutStr[3000];
	//POCI_INFO m_Poci[96];

private:
	DWORD PrintHexValue(BYTE value, char *str);
	BYTE m_Status;
	BYTE m_LastCommand;	// Ultimo comando enviado
//	BYTE m_PrintCant;	// Cantidad de bytes que se han impreso
	BYTE m_Cmd05Ans;	// Respuesta al comando 05
	// Comandos habilitados y desabilitados
	BOOL m_EnbCmdTbl[0x17];	//Enable Command Table
	BOOL m_EnbBusy;			// Habilitar ocupado

	/*
	ANALYSIS_INFO m_Analysis[24];
	BYTE m_PrintStatus;
	DWORD m_PrintExtra;		// Variable extra para el filtro de impresion
	
	// Variables que tienen que ver con los analisis
	char	m_COD[10];
	ANALYSIS_INFO m_tmpAnalysis;	// Nombre y unidad de medida del analisis
	float	m_AVal;					// Resultado del analisis
	BYTE	m_NoPoci;				// Numero de pocillo que entro
	*/


};

#endif // !defined(AFX_LISA2000FILTER_H__19DAB8E7_907A_4AB2_8062_A349F2AF06E0__INCLUDED_)
