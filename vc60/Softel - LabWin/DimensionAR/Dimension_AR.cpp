// Dimension_AR.cpp: implementation of the CDimension_AR class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dimension_AR.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK			0x1C

#define ST_WAIT_STX		1
#define ST_GETTING		2	// Acumulando datos
#define ST_WAIT_BREAK	3	// se espera el recivo de un separador no es obligado si no llega se acumula lo recibido

#define ANA_CANT_INDEX	10
#define PAT_NAME_INDEX  2
#define ANA_VAL_INDEX	12
#define ANA_UNIT_INDEX	13
#define VAL_ST_INDEX	14
#define ANA_NAME_INDEX	11

#define MAX_RESULTS 600

char*	DeviceName = "Tecnigen Dimension AR";

CDimension_AR::CDimension_AR()
{
	m_DeviceName = DeviceName;
	ResetStatus();
}

CDimension_AR::~CDimension_AR()
{

}

DWORD CDimension_AR::ProcessData(BYTE *lpData, DWORD dwSize)
{
	DWORD i;
	BYTE  val;
	for (i=0;i<dwSize;i++)
	{
		val = lpData[i];
		// maquina de procesamiento
		if (val == STX) 
		{
			m_strpos = 0;
			m_blockIndex = 0;
			m_status = ST_GETTING;
			continue;
		} else
			if (m_status == ST_WAIT_STX) continue;
		if (m_status == ST_GETTING)
		{
			if (val == BREAK) 
			{
				ProcessBlock();
				m_str[0] = 0;
				continue;
			}
			if (val == ETX) 
			{
				m_status = ST_WAIT_STX;
				continue;
			}
			m_str[m_strpos] = val;
			m_strpos++;
			continue;
		}
		
	}
	return ERR_NONE;	
}

DWORD CDimension_AR::ProcessBlock()
{
	BYTE block = m_blockIndex;
	m_blockIndex++;
	m_str[m_strpos] = 0;
	m_strpos = 0;
	switch (block)
	{
	case 0 : 
		{
			if (m_str[0] == 'P') m_status = ST_WAIT_STX;
			else
				if (m_str[0] != 'R') m_status = ST_WAIT_STX;
			break;
		}
	case PAT_NAME_INDEX:
		{
			lstrcpyn(m_Analysis.PatientName,m_str,AN_PATIENT_SIZE);
			break;
		}
	case ANA_CANT_INDEX:
		{
			int tmp;
			sscanf(m_str,"%d",&tmp);
			m_anacant = tmp;
			break;
		}
	case ANA_NAME_INDEX:
		{
			lstrcpyn(m_Analysis.Name,m_str,AN_NAME_SIZE);
			break;
		}
	case ANA_VAL_INDEX:
		{
			float tmp;
			if (sscanf(m_str,"%f",&tmp) == 1) 
				m_Analysis.Value = tmp;
			else
				m_Analysis.Value = 0;
			break;
		}
	case ANA_UNIT_INDEX:
		{
			if (m_str[0] == 0) break;
			lstrcpyn(m_Analysis.Unit,m_str,AN_UNIT_SIZE);
			AddAnalysis();
			break;
		}
	case VAL_ST_INDEX:
		{
			lstrcpyn(m_Analysis.Value_ST,m_str,AN_VAL_ST_SIZE);
			AddAnalysis();
			break;
		}
	} // switch
	return 0;
}

DWORD CDimension_AR::AddAnalysis()
{
	DWORD dr;
	dr = CLabDevice::AddAnalysis();
	m_anacant --;
	if (m_anacant == 0)
		ResetStatus();
	else
	{
		m_Analysis.Name[0] = 0;
		m_Analysis.Analis_ST[0] = 0;
		m_Analysis.Value = 0;
		m_Analysis.Unit[0] = 0;
		m_Analysis.Value_ST[0] = 0;
		m_blockIndex = ANA_NAME_INDEX;
	}
	return 0;
}

DWORD CDimension_AR::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_status = ST_WAIT_STX;
	return 0;
}
