// BFA_.cpp: implementation of the CBFA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BFA_.h"
#include "errorcodes.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK	0x17

#define ST_WAIT_STX		1
#define ST_GETTING		2	// Acumulando datos

#define FRM_PATIENT_NAME_INDEX	26
#define FRM_ANA_NAME_INDEX		36
#define FRM_ANA_VAL_INDEX		55
#define FRM_ANA_NO_INDEX		49

#define FRM_TYPE_DT			1
#define FRM_TYPE_EO			2
#define FRM_TYPE_UNKNOWN	3


char*	DeviceName = "Tecnigen - BFA";

CBFA::CBFA()
{
	m_DeviceName = DeviceName;
	ResetStatus();
}

CBFA::~CBFA()
{

}

DWORD CBFA::ProcessData(BYTE *lpData, DWORD dwSize)
{
	DWORD i;
	for (i=0;i<dwSize;i++)
	{
		m_lastByte = lpData[i];
		// esperar STX
		if (m_lastByte == STX) 
		{
			m_strPos = 0;
			m_frameIndex = 0;
			m_frameTopIndex = 3;
			m_frameType = FRM_TYPE_UNKNOWN;
			m_status = ST_GETTING;
			continue;
		} else
			if (m_status == ST_WAIT_STX) continue;
		if (m_status == ST_GETTING)
		{
			m_frameIndex++;
			// ver si aparecio una marca
			if (m_lastByte == 0x17)
			{
				m_status = ST_WAIT_STX;
				continue;
			}
			if (m_lastByte < 0x20) continue;  // error
			// Ignorar espacios al comienzo del bloque
			if ((m_lastByte != ' ') || (m_strPos != 0))
			{
				// no le cabe mas nada al string
				if (m_strPos < MAX_STR_SIZE-1)
				{
					m_str[m_strPos] = m_lastByte;
					m_strPos++;
				}
			}
			if (m_frameIndex >= m_frameTopIndex)
			{
				ProcessBlock();
				continue;
			}
			continue;
		}
	}
	return ERR_NONE;	
}

DWORD CBFA::ProcessBlock()
{
	m_str[m_strPos] = ' ';
	From0x20To0x00(m_str,m_strPos);
	m_strPos = 0;
	if (m_frameType == FRM_TYPE_UNKNOWN)
	{
		if (m_frameIndex != 3)
		{
			m_status = ST_WAIT_STX;
			return 0;
		}
	}
	if (m_frameType == FRM_TYPE_DT)
	{
		switch (m_frameIndex)
		{
		case 1:
			{
				m_frameTopIndex = 45; 
				break;
			}
		case 45:
			{
				m_frameTopIndex = FRM_ANA_NO_INDEX; 
				break;
			}
		case FRM_ANA_NO_INDEX:
			{
				lstrcpyn(m_Analysis.No,m_str,AN_NO_SIZE);	
				m_frameTopIndex = FRM_ANA_VAL_INDEX; 
				break;
			}
		case FRM_ANA_VAL_INDEX:
			{
				sscanf(m_str,"%f",&m_Analysis.Value);
				m_frameTopIndex = 58;
				AddAnalysis();
				break;
			}
		case 58:
			{
				m_frameIndex = 45;
				m_frameTopIndex = FRM_ANA_NO_INDEX;
				break;
			}
		}
	}
	return 0;
}

DWORD CBFA::AddAnalysis()
{
	DWORD dr;
	dr = CLabDevice::AddAnalysis();
	ResetStatus();
	return 0;
}

DWORD CBFA::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	return 0;
}

