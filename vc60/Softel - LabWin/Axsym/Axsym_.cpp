// Axsym_.cpp: implementation of the CAxsym class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Axsym_.h"
#include "errorcodes.h"
#include "dllcommon.h"
#include "Factory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK	0x7C

#define ST_WAIT_STX		1
#define ST_GETTING		2	// Acumulando datos

#define FRM_NONE		0
#define FRM_HEADER		1
#define FRM_PACIENT		2
#define FRM_OPERATION	3
#define FRM_RESULT		4
#define FRM_LAST		5

#define ANA_CANT_INDEX	10
#define PAT_NAME_INDEX  2
#define ANA_VAL_INDEX	12
#define ANA_UNIT_INDEX	13
#define VAL_ST_INDEX	14
#define ANA_NAME_INDEX	11

char*	DeviceName = "Abbott Axsym";

CAxsym::CAxsym()
{
	m_DeviceName = DeviceName;
	ResetStatus();
}

CAxsym::~CAxsym()
{

}

DWORD CAxsym::ProcessData(BYTE *lpData, DWORD dwSize)
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
	return ERR_NONE;	
}

DWORD CAxsym::ProcessBlock()
{
	BYTE block = m_blockIndex;
	m_blockIndex++;
	m_str[m_strPos] = 0;
	m_strPos = 0;
	if (block == 0)
	{
		switch (m_str[1])
		{
		case 'H':
			{
				m_status = ST_WAIT_STX;
				m_frametype = FRM_HEADER;
				break;
			}
		case 'P':
			{
				if (m_frametype != FRM_HEADER) m_status = ST_WAIT_STX;
				m_frametype = FRM_PACIENT;
				break;
			}
		case 'O':
			{
				if (m_frametype != FRM_PACIENT) m_status = ST_WAIT_STX;
				m_frametype = FRM_OPERATION;
				break;
			}
		case 'R':
			{
				if ((m_frametype != FRM_RESULT) && (m_frametype != FRM_OPERATION)) m_status = ST_WAIT_STX;
				m_frametype = FRM_RESULT;
				break;
			}
		case 'L':
			{
				m_status = ST_WAIT_STX;
				m_frametype = FRM_LAST;
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
	case FRM_HEADER:
		{
			break;
		}
	case FRM_PACIENT:
		{
			break;
		}
	}
	return 0;
}

DWORD CAxsym::AddAnalysis()
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

DWORD CAxsym::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_status = ST_WAIT_STX;
	return 0;
}

