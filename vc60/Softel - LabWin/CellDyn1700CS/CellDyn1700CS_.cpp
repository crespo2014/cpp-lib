// CellDyn1700CS_.cpp: implementation of the CCellDyn1700CS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CellDyn1700CS_.h"
#include "errorcodes.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK	','

#define ST_WAIT_STX		1
#define ST_GETTING		2	// Acumulando datos

//#define ANA_NO_INDEX	1
#define PAT_NAME_INDEX  9
//#define ANA_VAL_INDEX	3
//#define ANA_UNIT_INDEX	4
//#define ANA_NAME_INDEX	0
#define ANA_DAY_INDEX	6
#define ANA_TIME_INDEX	7
#define ANA_SEX_INDEX	10

#define MAX_RESULTS 600

char*	DeviceName = "Abbott CellDyn 1700 CS";

CCellDyn1700CS::CCellDyn1700CS()
{
	m_DeviceName = DeviceName;
	ResetStatus();
	m_status = ST_WAIT_STX;
}

CCellDyn1700CS::~CCellDyn1700CS()
{

}

DWORD CCellDyn1700CS::ProcessData(BYTE *lpData, DWORD dwSize)
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
			m_onstr = true;
			m_status = ST_GETTING;
			continue;
		} else
			if (m_status == ST_WAIT_STX) continue;
		if (m_status == ST_GETTING)
		{
			if ((m_lastByte == '\"') && (m_strPos == 0)) 
			{
				m_onstr = true;
				continue;
			}
			if ((m_lastByte == '\"') && (m_strPos != 0)) 
			{
				m_onstr = false;
				continue;
			}
			if (!m_onstr)
			{
				if ((m_lastByte == BREAK) || (m_lastByte == CR)) 
				{
					ProcessBlock();
					continue;
				}
				if (m_lastByte == ETX) 
				{
					m_status = ST_WAIT_STX;
					continue;
				}
			}
			// ver si le cabe mas al string
			if (m_strPos == MAX_STR_SIZE-1) continue;
			m_str[m_strPos] = m_lastByte;
			m_strPos++;
			continue;
		}
		
	}
	return ERR_NONE;
}

DWORD CCellDyn1700CS::ProcessBlock()
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
		*/
	case PAT_NAME_INDEX:
		{
			lstrcpyn(m_Analysis.PatientName,m_str,AN_PATIENT_SIZE);
			break;
		}
		/*
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
			break;
		}
	}
	return 0;
}

DWORD CCellDyn1700CS::AddAnalysis()
{
	DWORD dr;
	dr = CLabDevice::AddAnalysis();
	return 0;
}

DWORD CCellDyn1700CS::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_strPos = 0;
	m_blockIndex = 0;
	return 0;
}


