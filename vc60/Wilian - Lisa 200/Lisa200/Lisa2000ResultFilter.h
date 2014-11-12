// Lisa2000ResultFilter.h: interface for the CLisa2000ResultFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISA2000RESULTFILTER_H__A0CCFF77_9E9A_4D60_A870_AC1F8BCB237D__INCLUDED_)
#define AFX_LISA2000RESULTFILTER_H__A0CCFF77_9E9A_4D60_A870_AC1F8BCB237D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lisa2000def.h"


class CLisa2000ResultFilter  
{
public:
	DWORD GetAnalysis(DWORD NoPoci,DWORD NoAnalysis,ANA_STATUS* Analysis);
	DWORD GetName(DWORD Index,char** lpname);
	DWORD GetAnalysisInfo(DWORD Index,ANALYSIS_INFO* lpAnaInfo);
	DWORD ProcessSndByte(BYTE value);
	DWORD ProcessPrintByte(BYTE Val);
	DWORD ProcessRcvBuffer(BYTE* buffer, DWORD dwSize);
	DWORD ProcessSndBuffer(BYTE* buffer, DWORD dwSize);
	DWORD ProcessRcvByte(BYTE Val);
	CLisa2000ResultFilter();
	virtual ~CLisa2000ResultFilter();
	DWORD ClearString(char *string);
	DWORD ProcessResult();

private:
	BOOL	m_OnPrinting;	// Indica que hay una impresion en curso
	BYTE	m_PrintPos;		// Cantidad de bytes que se han impreso
	BYTE	m_Status;		// Estado en que se encuentra el filtro
	BYTE	m_PrintStatus;
	DWORD	m_PrintTmp;		// Variable extra para el filtro de impresion
	BOOL    m_OnCmd05;		//Indica que se recibio un comando 05	
	// Variables que tienen que ver con los analisis
	char	m_COD[10];
	ANALYSIS_INFO m_tmpAnalysis;	// Nombre y unidad de medida del analisis

	float	m_AVal;					// Resultado del analisis
	BYTE	m_NoPoci;				// Numero de pocillo que entro

	//Resultados y nombres de analisis
	POCI_INFO m_Poci[MAX_POCI];
	ANALYSIS_INFO m_Analysis[MAX_ANALYSIS];
};

#endif // !defined(AFX_LISA2000RESULTFILTER_H__A0CCFF77_9E9A_4D60_A870_AC1F8BCB237D__INCLUDED_)
