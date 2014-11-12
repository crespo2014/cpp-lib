// Immulite2000_.cpp: implementation of the CImmulite2000 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Immulite2000_.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK	','

#define ANA_NO_INDEX	1
#define PAT_NAME_INDEX  2
#define ANA_VAL_INDEX	3
#define ANA_UNIT_INDEX	4
#define ANA_NAME_INDEX	0
#define ANA_DAY_INDEX	8
#define ANA_TIME_INDEX	9

#define MAX_RESULTS 600

char*	DeviceName = "Immulite 2000";

CImmulite2000::CImmulite2000()
{
	m_DeviceName = DeviceName;
	ResetStatus();
}

CImmulite2000::~CImmulite2000()
{

}

DWORD CImmulite2000::ProcessData(BYTE *lpData, DWORD dwSize)
{
	DWORD i;
	for (i=0;i<dwSize;i++)
	{
		m_lastByte = lpData[i];
		// Ignorar espacios al comienzo del bloque
		if ((m_lastByte == ' ') && (m_strPos == 0)) continue;
		// Revisar fin de bloque
		if (m_lastByte == CR) ResetStatus();
		if (m_lastByte == LF) continue;
		if (m_lastByte < 0x20) continue;  // error
		if (m_lastByte == BREAK) 
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
	return ERR_NONE;	
}

DWORD CImmulite2000::ProcessBlock()
{
	BYTE block = m_blockIndex;
	m_blockIndex++;
	m_str[m_strPos] = ' ';
	From0x20To0x00(m_str,m_strPos);
	m_strPos = 0;
	switch (block)
	{
	case ANA_NO_INDEX:
		{
			lstrcpyn(m_Analysis.No,m_str,AN_NO_SIZE);
			break;
		}
	case PAT_NAME_INDEX:
		{
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
	}
	return 0;
}

DWORD CImmulite2000::AddAnalysis()
{
	DWORD dr;
	dr = CLabDevice::AddAnalysis();
	return 0;
}

DWORD CImmulite2000::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_strPos = 0;
	m_blockIndex = 0;
	return 0;
}


