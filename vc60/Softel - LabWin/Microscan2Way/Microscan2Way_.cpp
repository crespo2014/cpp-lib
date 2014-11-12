// Microscan2Way_.cpp: implementation of the CMicroscan2Way class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Microscan2Way_.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK	','

#define ST_WAIT_STX		1
#define ST_GETTING		2	// Acumulando datos

#define FRM_NONE	0
#define FRM_H		1
#define FRM_P		2
#define FRM_B		3
#define FRM_R		4
#define FRM_M		5
#define FRM_L		6

#define ANA_CANT_INDEX	10
#define PAT_NAME_INDEX  2
#define ANA_VAL_INDEX	12
#define ANA_UNIT_INDEX	13
#define VAL_ST_INDEX	14
#define ANA_NAME_INDEX	11

#define MAX_RESULTS 600

char*	DeviceName = "Tecnigen Microscan 2-Way";

CMicroscan2Way::CMicroscan2Way()
{
	m_DeviceName = DeviceName;
	ResetStatus();
}

CMicroscan2Way::~CMicroscan2Way()
{

}

DWORD CMicroscan2Way::ProcessData(BYTE *lpData, DWORD dwSize)
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
		if (m_status == ST_GETTING)
		{
			if (m_lastByte == '\"') continue;
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
			m_str[m_strPos] = m_lastByte;
			m_strPos++;
			continue;
		}
		
	}
	return ERR_NONE;	
}

DWORD CMicroscan2Way::ProcessBlock()
{
	BYTE block = m_blockIndex;
	m_blockIndex++;
	m_str[m_strPos] = 0;
	m_strPos = 0;
	if (block == 0)
	{
		switch (m_str[0])
		{
		case 'H':
			{
				m_status = ST_WAIT_STX;
				m_frametype = FRM_H;
				break;
			}
		case 'P':
			{
				//if (m_frametype != FRM_HEADER) m_status = ST_WAIT_STX;
				m_frametype = FRM_P;
				break;
			}
		case 'B':
			{
				//if (m_frametype != FRM_PACIENT) m_status = ST_WAIT_STX;
				m_frametype = FRM_B;
				break;
			}
		case 'R':
			{
				//if ((m_frametype != FRM_RESULT) && (m_frametype != FRM_OPERATION)) m_status = ST_WAIT_STX;
				m_frametype = FRM_R;
				break;
			}
		case 'L':
			{
				m_status = ST_WAIT_STX;
				m_frametype = FRM_L;
				break;
			}
		default:
			{
				m_status = ST_WAIT_STX;
				m_frametype = FRM_NONE;
				break;
			}
		}
		return 0;
	}
	switch (m_frametype)
	{
	case FRM_H:
		{
			break;
		}
	case FRM_P:
		{
			break;
		}
	}
	return 0;
}

DWORD CMicroscan2Way::AddAnalysis()
{
	DWORD dr;
	dr = CLabDevice::AddAnalysis();
	m_Analysis.Name[0] = 0;
	m_Analysis.Analis_ST[0] = 0;
	m_Analysis.Value = 0;
	m_Analysis.Unit[0] = 0;
	m_Analysis.Value_ST[0] = 0;
	return 0;
}

DWORD CMicroscan2Way::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_status = ST_WAIT_STX;
	return 0;
}


