// Lisa2000ResultFilter.cpp: implementation of the CLisa2000ResultFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lisa2000ResultFilter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Estados del filtro
#define ST_WAIT_COMMAND	0	// Debe enviarse un comando
#define ST_WAIT_ANSWER	1	// Ya se envio el comando se espera una respuesta
#define ST_WAIT_DATA	2	// Se espera envio de datos de alguna parte respuesta 1B
#define ST_SND_DATA		3	// Se estan enviando datos
#define ST_RCV_DATA		4	// Se estan reciviendo datos

// Estados de la impresion
#define PRT_WAIT		0	// Esperando una impresion
#define PRT_COD_WAIT	1	// Se espera COD
#define PRT_COD_20		2	// Se espera el 20 antes del codigo
#define PRT_COD_GET		3	// Se espera el codigo
#define PRT_POCI_20		4	// Se espera 20 antes de POCI
#define PRT_POCI_READ	5	// Se espera leer POCI
#define PRT_POCI_WAIT	6	// Se espera 20 antes del numero de posillo
#define PRT_POCI_GET	7	// Se espera el numero de pocillo
#define PRT_FECH_20		8	// Se espera 20 antes de FECH
#define PRT_FECH_READ	9	// Se espera leer FECH
#define PRT_FECH_WAIT	10	// Se espera 20 antes de la fecha
#define PRT_FECH_GET	11	// Se espera leer la fecha
#define PRT_HORA_20		12	// Se espera el 20 antes de HORA
#define PRT_HORA_READ	13	// Se espera leer HORA
#define PRT_HORA_WAIT	14	// Se espera el 20 antes de la HORA
#define PRT_HORA_GET	15	// Se espera leer la hora
#define PRT_HORA_0D		16	// Se espera el fin de linea despues de la hora
#define PRT_ANA_0D		17	// Esperar fin de linea del analisis que acaba de terminar
#define PRT_ANA_20		18	// Se espera el 20 antes del nombre del analisis
#define PRT_ANA_GET		19	// Se espera el nombre del analisis
#define PRT_VAL_WAIT	20	// Se espera el 20 antes del valor del analisis
#define PRT_VAL_GET		21	// Se espera el valor del analisis.
#define PRT_MU_20		22	// Se espera el 20 antes de la unidad de medida
#define PRT_MU_GET		23	// Se espera la unidad de medida


#define PRT_NONE		0
#define PRT_IGNORE		1	// Ignorar la impresion en curso
#define PRT_USR			2

CLisa2000ResultFilter::CLisa2000ResultFilter()
{
	int i,j;
	m_Status = ST_WAIT_COMMAND;
	m_OnPrinting = false;
	m_PrintPos = 0;
	m_PrintStatus = PRT_WAIT;
	m_OnCmd05 = false;
	// Borrar todos los analisis
	for (i=0;i<MAX_ANALYSIS;i++)
		m_Analysis[i].name[0] = 0;
	for (i=0;i<MAX_POCI;i++)
		for (j=0;j<MAX_ANALYSIS;j++)
			m_Poci[i].analysis[j].reads = 0;

}

CLisa2000ResultFilter::~CLisa2000ResultFilter()
{

}

DWORD CLisa2000ResultFilter::ProcessSndBuffer(BYTE *buffer, DWORD dwSize)
{
	for (DWORD i=0;i<dwSize;i++)
	{
		if (m_OnPrinting)
			ProcessPrintByte(buffer[i]);
		else
			ProcessSndByte(buffer[i]);
	}
	return 0;
}


DWORD CLisa2000ResultFilter::ProcessRcvBuffer(BYTE *buffer, DWORD dwSize)
{
	for (DWORD i=0;i<dwSize;i++)
	{
		ProcessRcvByte(buffer[i]);
	}
	return 0;
}


DWORD CLisa2000ResultFilter::ProcessPrintByte(BYTE Val)
{
	m_PrintPos++;

	if (m_PrintPos == 1)
	{
		if (Val == 0x80) m_PrintStatus = PRT_COD_WAIT;	// Si aparece una ralla se incia el ciclo de nuevo

		if ((Val == 0x12) || (Val == 0x95) || (Val == 0x0F) || (Val == 0x1B) || (Val == 0x81))
		{
			m_PrintTmp = PRT_IGNORE;
		}
	}
	if (m_PrintTmp != PRT_IGNORE)
	{
		switch (m_PrintStatus)
		{
		case PRT_COD_WAIT:
			{
				if ((m_PrintPos == 1) && (Val == 'C')) m_PrintTmp = PRT_USR+1;
				if ((m_PrintPos == 2) && (Val == 'O') && m_PrintTmp == PRT_USR+1) m_PrintTmp = PRT_USR+2;
				if ((m_PrintPos == 3) && (Val == 'D') && m_PrintTmp == PRT_USR+2) m_PrintTmp = PRT_USR+3;
				if ((m_PrintPos == 4) && (Val == '.') && m_PrintTmp == PRT_USR+3)
				{
					m_PrintTmp = PRT_IGNORE;
					m_PrintStatus++;
				}
				break;
				
			}
		case PRT_COD_20:
		case PRT_POCI_20:
		case PRT_POCI_WAIT:
		case PRT_FECH_20:
		case PRT_FECH_WAIT:
		case PRT_HORA_20:
		case PRT_HORA_WAIT:
		case PRT_ANA_20:
		case PRT_VAL_WAIT:
		case PRT_MU_20:
			{
				if ((m_PrintPos == 1) && (Val == 0x20))
					m_PrintStatus++;				// pasar al proximo estatus
				else
					m_PrintStatus = PRT_COD_WAIT;	// esto no deberia suceder
				m_PrintTmp = PRT_IGNORE;
				break;
			}
		case PRT_COD_GET:
			{
				m_COD[m_PrintPos-1]=Val;
				if (Val ==0)
				{
					ClearString(m_COD);
					m_PrintTmp = PRT_IGNORE;
					m_PrintStatus++;
				}
				break;
			}
		case PRT_POCI_READ:
			{
				if ((m_PrintPos == 1) && (Val == 'P')) m_PrintTmp = PRT_USR+1;
				if ((m_PrintPos == 2) && (Val == 'O') && m_PrintTmp == PRT_USR+1) m_PrintTmp = PRT_USR+2;
				if ((m_PrintPos == 3) && (Val == 'C') && m_PrintTmp == PRT_USR+2) m_PrintTmp = PRT_USR+3;
				if ((m_PrintPos == 4) && (Val == 'I') && m_PrintTmp == PRT_USR+3)
				{
					m_PrintTmp = PRT_IGNORE;
					m_PrintStatus++;
				}
				if (m_PrintPos == 5)
					m_PrintStatus = PRT_COD_WAIT;
				break;
			}
		case PRT_POCI_GET:
			{
				if ((m_PrintPos == 1) && (Val == 0x20)) m_PrintTmp = PRT_USR+1;
				if ((m_PrintPos == 2) && m_PrintTmp == PRT_USR+1) m_NoPoci = Val-0x30;
				if ((m_PrintPos == 3) && m_PrintTmp == PRT_USR+1)
				{
					if (Val !=0x20)
					{
						m_NoPoci *=10;
						m_NoPoci += (Val-0x30);
					}
					m_PrintTmp = PRT_IGNORE;
					m_PrintStatus++;
				}
				if (m_PrintPos == 4)
					m_PrintStatus = PRT_COD_WAIT;
				break;
			}
		case PRT_FECH_READ:
			{
				if ((m_PrintPos == 1) && (Val == 'F')) m_PrintTmp = PRT_USR+1;
				if ((m_PrintPos == 2) && (Val == 'E') && m_PrintTmp == PRT_USR+1) m_PrintTmp = PRT_USR+2;
				if ((m_PrintPos == 3) && (Val == 'C') && m_PrintTmp == PRT_USR+2) m_PrintTmp = PRT_USR+3;
				if ((m_PrintPos == 4) && (Val == 'H') && m_PrintTmp == PRT_USR+3)
				{
					m_PrintTmp = PRT_IGNORE;
					m_PrintStatus++;
				}
				if (m_PrintPos == 5)
					m_PrintStatus = PRT_COD_WAIT;
				break;
			}
		case PRT_FECH_GET:
		case PRT_HORA_READ:
		case PRT_HORA_GET:
			{
				m_PrintTmp = PRT_IGNORE;
				m_PrintStatus++;
				break;
			}
		case PRT_HORA_0D:
		case PRT_ANA_0D:
			{
				// si aparece el fin de linea pasar al proximo estado 
				if ((m_PrintPos == 1) && (Val == 0x0D))
				{
					m_PrintStatus++;				// pasar al proximo estatus
					m_PrintTmp = PRT_IGNORE;
				}
				break;
			}
		case PRT_ANA_GET:
			{
				m_tmpAnalysis.name[m_PrintPos-1]=Val;
				if (Val ==0)
				{
					ClearString(m_tmpAnalysis.name);
					m_PrintTmp = PRT_IGNORE;
					m_PrintStatus++;
				}
				break;
			}
		case PRT_VAL_GET:
			{
				switch (m_PrintPos)
				{
				case 1:
					{
						if (Val != 0x20)
						{
							m_PrintTmp = PRT_IGNORE;
							m_PrintStatus = PRT_COD_WAIT;
						}
						break;
					}
				case 2:
					{
						m_AVal = (float)(Val-0x30);
						m_PrintTmp = PRT_USR+1;
						break;
					}
				default:
					{
						if (Val == '.')	{m_PrintTmp = 10;break;}
						if ((Val == 0x20)||(Val == 0x0)) 
						{
							m_PrintTmp = PRT_IGNORE;
							m_PrintStatus++;
							break;
						}
						if (m_PrintTmp == PRT_USR+1)
							m_AVal = m_AVal*10+Val-0x30;
						else
						{
							m_AVal = m_AVal+(float)(Val-0x30)/(float)m_PrintTmp;
							m_PrintTmp*=10;
						}
						break;
					}
				}
				break;
			}
		case PRT_MU_GET:
			{
				m_tmpAnalysis.measured_unit[m_PrintPos-1]=Val;
				if (Val ==0)
				{
					ClearString(m_tmpAnalysis.measured_unit);
					m_PrintTmp = PRT_IGNORE;
					m_PrintStatus = PRT_ANA_0D;
					ProcessResult();
				}
				break;
			}
		}
	}
	if (m_PrintPos == 50)
	{
		m_OnPrinting=false;
		m_Status = ST_WAIT_COMMAND;
	}
	return 0;
}

DWORD CLisa2000ResultFilter::ClearString(char *string)
{
	DWORD i;
	for (i=strlen(string);i>0;i--)
	{
		if (string[i]==0x20) string[i]=0;
		if (string[i]!=0) break;
	}
	return 0;
}


DWORD CLisa2000ResultFilter::ProcessResult()
{
	DWORD Index,SetIndex;
	// Buscar el analisi en la lista de analisis
	SetIndex = 50;
	for (Index=0;Index<24;Index++)
	{
		if ((m_Analysis[Index].name[0]==0) && (SetIndex == 50))
			SetIndex = Index;
		if (strcmp(m_Analysis[Index].name,m_tmpAnalysis.name)==0)
			break;
	}
	if (Index == 24)
	{
		m_Analysis[SetIndex] = m_tmpAnalysis;
		Index =  SetIndex;
	}
	m_Poci[m_NoPoci-1].analysis[Index].val = m_AVal;
	m_Poci[m_NoPoci-1].analysis[Index].reads++;
	strcpy(m_Poci[m_NoPoci-1].name,m_COD);
	return 0;
}

DWORD CLisa2000ResultFilter::ProcessSndByte(BYTE value)
{
	switch (value)
	{
	case 1: 
	case 2: 
	case 3: 
		{
			break;
		}
	case 4: 
		{
			m_Status = ST_WAIT_COMMAND;
			return 0;
		}
	default:
		{
			if ((m_Status == ST_WAIT_DATA)||(m_Status == ST_WAIT_COMMAND))
			{
				// Se envio un comando cuando se debia enviar informacion
				if (value == 0x05)
					m_OnCmd05 = true;
				if (value == 0x0F)
				{
					m_PrintTmp = PRT_NONE;
					m_OnPrinting=true;
					m_PrintPos = 0;
				}
				
				m_Status = ST_WAIT_ANSWER;
				return 0;
			}
			break;
		}
	}
	m_Status = ST_SND_DATA;
	return 0;
}

DWORD CLisa2000ResultFilter::ProcessRcvByte(BYTE Val)
{
	if ((m_OnCmd05) && (m_Status == ST_WAIT_ANSWER))
	{
		m_Status = ST_WAIT_COMMAND;
		m_OnCmd05=false;
		return 0;
	}
	switch(Val)
	{
	case 1: 
		{
			m_Status = ST_RCV_DATA;
			break;
		}
	case 2: 
		{
			break;
		}
	case 3: 
		{
			if (m_Status == ST_WAIT_ANSWER)
			{
				m_Status = ST_WAIT_COMMAND;
			}
			break;
		}
	case 4: 
		{
			m_Status = ST_WAIT_COMMAND;
			break;
		}
	case 0x1A:
		{
			m_Status = ST_WAIT_COMMAND;
			break;
		}
	case 0x1b:
		{
			m_Status = ST_WAIT_DATA;
			break;
		}
	default:
		{
			break;
		}
	}
	return 0;
}

DWORD CLisa2000ResultFilter::GetAnalysisInfo(DWORD Index,ANALYSIS_INFO* lpAnaInfo)
{
	*lpAnaInfo = m_Analysis[Index];
	return 0;
}

DWORD CLisa2000ResultFilter::GetName(DWORD Index, char **lpname)
{
	*lpname = m_Poci[Index].name;
	return 0;
}

DWORD CLisa2000ResultFilter::GetAnalysis(DWORD NoPoci, DWORD NoAnalysis, ANA_STATUS *Analysis)
{
	*Analysis = m_Poci[NoPoci].analysis[NoAnalysis];
	return 0;
}
