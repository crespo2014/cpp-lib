// Selectra_.cpp: implementation of the CSelectra class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Selectra_.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK	';'

#define ST_WAIT_STX		1
#define ST_GETTING		2	// Acumulando datos
#define ST_WAIT_START	3	// Se espera comienzo de bloque

#define ANA_NO_INDEX	3
#define PAT_SEX_INDEX	6
#define ANA_VAL_INDEX	9
#define ANA_UNIT_INDEX	11
#define ANA_NAME_INDEX	8
#define BLCK_TYPE_INDEX	0
//#define ANA_DAY_INDEX	8
//#define ANA_TIME_INDEX	9

char*	DeviceName = "Tecnigen Vitalab Selectra";

CSelectra::CSelectra()
{
	m_DeviceName = DeviceName;
	ResetStatus();
}

CSelectra::~CSelectra()
{

}

DWORD CSelectra::ProcessData(BYTE *lpData, DWORD dwSize)
{
	DWORD i;
	for (i=0;i<dwSize;i++)
	{
		m_lastByte = lpData[i];
		// esperar STX
		if (m_lastByte == STX) 
		{
			m_strPos = 0;
			m_blockIndex = 0;
			m_status = ST_WAIT_START;
			continue;
		} else
			if (m_status == ST_WAIT_STX) continue;
		// esperar inicio de bloque
		if ((m_status == ST_WAIT_START) && (m_lastByte == '{'))
		{
			m_status = ST_GETTING;
			ResetStatus();
			continue;
		}
		if (m_status == ST_GETTING)
		{
			// Ignorar espacios al comienzo del bloque
			if ((m_lastByte == ' ') && (m_strPos == 0)) continue;
			// Revisar fin de bloque
			if (m_lastByte == '}') 
			{
				AddAnalysis();
				m_status = ST_WAIT_STX;
			}
			if (m_lastByte == CR) continue;
			if (m_lastByte == LF) continue;
			if (m_lastByte < 0x20) continue;  // error
			if ((m_lastByte == BREAK)||(m_lastByte == '}'))
			{
				ProcessBlock();
				continue;
			}
			// no le cabe mas nada al string
			if (m_strPos == MAX_STR_SIZE-1) continue;
			m_str[m_strPos] = m_lastByte;
			m_strPos++;
			continue;
		}
	}
	return ERR_NONE;	
}

DWORD CSelectra::ProcessBlock()
{
	BYTE block = m_blockIndex;
	m_blockIndex++;
	if (m_strPos == 0) return 0;
	m_str[m_strPos] = ' ';
	From0x20To0x00(m_str,m_strPos);
	m_strPos = 0;
	switch (block)
	{
	case BLCK_TYPE_INDEX:
		{
			if (m_str[0] != 'R')  m_status = ST_WAIT_STX;
			break;
		}
	case ANA_NO_INDEX:
		{
			lstrcpyn(m_Analysis.No,m_str,AN_NO_SIZE);
			break;
		}
	case PAT_SEX_INDEX:
		{
			m_Analysis.sex = m_str[0];
			lstrcpyn(m_Analysis.PatientName,m_str,AN_PATIENT_SIZE);
			break;
		}
	case ANA_VAL_INDEX:
		{
			sscanf(m_str,"%f",&m_Analysis.Value);
			break;
		}
	case ANA_UNIT_INDEX:
		{
			lstrcpyn(m_Analysis.Unit,m_str,AN_UNIT_SIZE);
			break;
		}
	case ANA_NAME_INDEX:
		{
			lstrcpyn(m_Analysis.Name,m_str,AN_NAME_SIZE);
			break;
		}
	}
	return 0;
}

DWORD CSelectra::AddAnalysis()
{
	DWORD dr;
	dr = CLabDevice::AddAnalysis();
	return 0;
}

DWORD CSelectra::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_strPos = 0;
	m_blockIndex = 0;
	return 0;
}
