// AJ_4270.cpp: implementation of the CAJ_4270 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AJ_4270.h"
#include "errorcodes.h"
#include "..\include\Common.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define STX				0x02
#define ETX				0x03
#define CR				0x0D
#define BREAK			0x7C

// estados
#define ST_WAIT_STX		1	// esperando comienzo de bloque
#define ST_GETTING		2	// almacenando lo recibido

char*	DeviceName = "Arquimed AJ-4270";

CAJ_4270::CAJ_4270()
{
	m_DeviceName = DeviceName;
	ResetStatus();
}

CAJ_4270::~CAJ_4270()
{

}


DWORD CAJ_4270::ProcessBlock()
{
	char	str[20];
	int		val;
	if (m_blockIndex == 25)
	{
		// determinacion
		From0x20To0x00(m_block,5);			// limpiar espacios en la determinacion
		lstrcpyn(m_Analysis.Name,m_block,AN_NAME_SIZE);	// Tomar determinacion
		// estado del analisis
		From0x20To0x00(m_block,12);			// limpiar espacios en el estado del analisis
		if (m_block[6] != 0x20)
			lstrcpyn(m_Analysis.Analis_ST,&m_block[6],AN_AN_ST_SIZE);
		else
			lstrcpyn(m_Analysis.Analis_ST,&m_block[7],AN_AN_ST_SIZE);
		From0x20To0x00(m_block,18);			// limpiar espacios del resultado
		if ((m_block[13] == '<') || (m_block[13] == '>'))
		{
			lstrcpyn(m_Analysis.Value_ST,&m_block[13],AN_VAL_ST_SIZE);
			m_Analysis.Value = 0.0;
		}
		else
		{
			m_Analysis.Value_ST[0] = 0x00;
			if (m_block[13] != 0x0)
			{
				lstrcpyn(str,&m_block[13],7);
				sscanf(str,"%f",&m_Analysis.Value);
			}else
				m_Analysis.Value = 0;
		}
		// unidad de medida
		From0x20To0x00(m_block,24);
		lstrcpyn(m_Analysis.Unit,&m_block[19],AN_UNIT_SIZE);
		// almacenar todo lo obtenido en un paciente
		if (m_onPatient)
		{
			AddAnalysis();
			// borrar datos

		}
		if (m_status == ST_WAIT_STX) m_onPatient = false;
		m_blockIndex = 0;
		return 0;
	}
	if (m_blockIndex == 8)
	{
		lstrcpyn(str,m_block,9);
		if (strcmp(str,"VAJ-4270")==0) {m_blockSize = 74;return 0;}
		if (strcmp(str,"        ")==0) 
		{
			m_onPatient = false;
			m_status = ST_WAIT_STX;
			return 0;
		}
		m_blockSize = 25;
	}
	if (m_blockIndex == 74)
	{
		if (m_status != ST_WAIT_STX) ; // error en protocolo
		
		lstrcpyn(str,&m_block[18],7);	// ??
		lstrcpyn(str,&m_block[32],5);	// año
		sscanf(str,"%d",&val);
		m_Analysis.Year = val;
		lstrcpyn(str,&m_block[37],3);	// mes
		sscanf(str,"%d",&val);
		m_Analysis.Month = val;
		lstrcpyn(str,&m_block[40],3);	// dia
		sscanf(str,"%d",&val);
		m_Analysis.Day = val;
		lstrcpyn(str,&m_block[43],3);	// hora
		sscanf(str,"%d",&val);
		m_Analysis.Hour = val;
		lstrcpyn(str,&m_block[46],3);	// minuto
		sscanf(str,"%d",&val);
		m_Analysis.Minute = val;
		lstrcpyn(str,&m_block[52],5);	// ??
		m_onPatient = true;
		m_blockIndex = 0;
		m_status = ST_WAIT_STX;
	}
	return 0;

}

DWORD CAJ_4270::ProcessData(BYTE *lpData, DWORD dwSize)
{
	DWORD i;
	BYTE  val;
	for (i=0;i<dwSize;i++)
	{
		val = lpData[i];
		if (m_status == ST_WAIT_STX)
		{
			if (val != STX) continue;
			m_status = ST_GETTING;
			m_blockIndex = 0;
			m_blockSize = 8;
			continue;
		}
		if (m_status == ST_GETTING)
		{
			if (val == 0x17) 
			{
				m_status = ST_WAIT_STX;
				ProcessBlock();
				continue;
			}
			if (m_blockIndex == m_blockSize) ProcessBlock();
			if (m_blockIndex == MAX_BLOCKSIZE) // error
			{
				m_blockIndex = 0;
				m_status = ST_WAIT_STX;
			}
			m_block[m_blockIndex] = val;
			m_blockIndex++;
			continue;
		}
	}
	return ERR_NONE;
}

DWORD CAJ_4270::AddAnalysis()
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

DWORD CAJ_4270::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_status = ST_WAIT_STX;
	m_onPatient = false;
	return 0;
}