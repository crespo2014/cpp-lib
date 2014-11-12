// CellDyn3500_.cpp: implementation of the CCellDyn3500 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CellDyn3500_.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK	','

#define ST_WAIT_STX		1
#define ST_GETTING		2	// Acumulando datos
#define ST_WAIT_BREAK	3	// se espera el recivo de un separador no es obligado si no llega se acumula lo recibido

#define ANA_NO_INDEX	0
#define PAT_NAME_INDEX  0
#define ANA_VAL_INDEX	0
#define ANA_UNIT_INDEX	0
#define ANA_NAME_INDEX	0
#define ANA_DAY_INDEX	7
#define ANA_TIME_INDEX	8

#define MAX_RESULTS 600

char*	DeviceName = "Abbott CellDyn 3500";

CCellDyn3500::CCellDyn3500()
{
	m_DeviceName = DeviceName;
	ResetStatus();
}

CCellDyn3500::~CCellDyn3500()
{

}

DWORD CCellDyn3500::ProcessData(BYTE *lpData, DWORD dwSize)
{
	DWORD i;
	for (i=0;i<dwSize;i++)
	{
		m_lastByte = lpData[i];
		// maquina de procesamiento
		if (m_lastByte == STX) 
		{
			m_strPos = 0;
			m_blockIndex = 0;
			m_status = ST_GETTING;
			continue;
		} else
			if (m_status == ST_WAIT_STX) continue;
		// Ignorar espacios al comienzo del bloque
		if ((m_lastByte == ' ') && (m_strPos == 0)) continue;
		// ignorar delimitadores de string
		if (m_lastByte == '\"') continue;
		// Revisar fin de bloque
		if ((m_lastByte == BREAK) || (m_lastByte == ETX))
		{
			ProcessBlock();
			continue;
		}
		// no le cabe mas nada al string
		if (m_strPos == MAX_STR_SIZE-1) continue; // error
		m_str[m_strPos] = m_lastByte;
		m_strPos++;
		continue;
	}
	return ERR_NONE;	
}

DWORD CCellDyn3500::ProcessBlock()
{
	BYTE block = m_blockIndex;
	m_blockIndex++;
	m_str[m_strPos] = ' ';
	From0x20To0x00(m_str,m_strPos);
	m_strPos = 0;
	switch (block)
	{
		/*
	case ANA_NO_INDEX:
		{
			lstrcpyn(m_anaNo,m_str,AN_NO_SIZE);
			break;
		}
	case PAT_NAME_INDEX:
		{
			lstrcpyn(m_patientName,m_str,AN_PATIENT_SIZE);
			break;
		}
	case ANA_VAL_INDEX:
		{
			sscanf(m_str,"%f",&m_anaVal);
			break;
		}
	case ANA_UNIT_INDEX:
		{
			lstrcpyn(m_anaUnit,m_str,AN_UNIT_SIZE);
			break;
		}
	case ANA_NAME_INDEX:
		{
			lstrcpyn(m_anaName,m_str,AN_NAME_SIZE);
			break;
		}
		*/
	case ANA_DAY_INDEX:
		{
			int tmp;
			sscanf(m_str,"%d",&tmp);
			m_Analysis.Day = tmp;
			sscanf(&m_str[3],"%d",&tmp);
			m_Analysis.Month = tmp;
			sscanf(&m_str[6],"%d",&tmp);
			m_Analysis.Year = tmp;
			break;
		}
	case ANA_TIME_INDEX:
		{
			int tmp;
			sscanf(m_str,"%d",&tmp);
			m_Analysis.Hour = tmp;
			sscanf(&m_str[3],"%d",&tmp);
			m_Analysis.Minute = tmp;
			sscanf(&m_str[6],"%d",&tmp);
			m_Analysis.Second = tmp;
			AddAnalysis();
			break;
		}
	default:
		{
			// resultados de los analisis
			break;
		}
	}
	if (m_lastByte == ETX) ResetStatus();
	return 0;
}

DWORD CCellDyn3500::AddAnalysis()
{
	DWORD dr;
	dr = CLabDevice::AddAnalysis();
	return 0;
}

DWORD CCellDyn3500::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_strPos = 0;
	m_blockIndex = 0;
	m_status = ST_WAIT_STX;
	return 0;
}