// Mega_.cpp: implementation of the CMega class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mega_.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK	0x17

#define ST_WAIT_STX		1
#define ST_GETTING		2	// Acumulando datos

#define FRM_VAL_INDEX	55
#define FRM_NO_INDEX	49

#define FRM_TYPE1		1
#define FRM_TYPE2		2


#define MAX_RESULTS 600

char*	DeviceName = "Tecnigen MERCK Mega";

CMega::CMega()
{
	m_DeviceName = DeviceName;
	ResetStatus();
}

CMega::~CMega()
{

}

DWORD CMega::ProcessData(BYTE *lpData, DWORD dwSize)
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
			m_frameTopIndex = 1;
			m_frameType = FRM_TYPE1;
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

DWORD CMega::ProcessBlock()
{
	m_str[m_strPos] = ' ';
	From0x20To0x00(m_str,m_strPos);
	m_strPos = 0;
	if (m_frameType == FRM_TYPE1)
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
				m_frameTopIndex = FRM_NO_INDEX; 
				break;
			}
		case FRM_NO_INDEX:
			{
				lstrcpyn(m_Analysis.No,m_str,AN_NO_SIZE);	
				m_frameTopIndex = FRM_VAL_INDEX; 
				break;
			}
		case FRM_VAL_INDEX:
			{
				sscanf(m_str,"%f",&m_Analysis.Value);
				m_frameTopIndex = 58;
				AddAnalysis();
				break;
			}
		case 58:
			{
				m_frameIndex = 45;
				m_frameTopIndex = FRM_NO_INDEX;
				break;
			}
		}
	}
	return 0;
}

DWORD CMega::AddAnalysis()
{
	DWORD dr;
	dr = CLabDevice::AddAnalysis();
	ResetStatus();
	return 0;
}

DWORD CMega::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_strPos = 0;
	return 0;
}
