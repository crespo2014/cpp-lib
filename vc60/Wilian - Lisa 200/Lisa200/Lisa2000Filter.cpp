// Lisa2000Filter.cpp: implementation of the CLisa2000Filter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lisa2000Filter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const char* SND_STR = ">> ";
const char* RCV_STR = "<< ";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLisa2000Filter::CLisa2000Filter()
{
	m_Status = ST_WAIT_COMMAND;
	m_LastCommand = 0;
	m_OutStr[0] = 0;
	m_Cmd05Ans = 0;
	m_EnbCmdTbl[0x05] = 0;
	m_EnbCmdTbl[0x06] = 0;
	m_EnbCmdTbl[0x07] = 0;
	m_EnbCmdTbl[0x08] = 1;
	m_EnbCmdTbl[0x0A] = 0;
	m_EnbCmdTbl[0x0F] = 0;
	m_EnbCmdTbl[0x10] = 0;
	m_EnbCmdTbl[0x12] = 0;
	m_EnbCmdTbl[0x13] = 0;
	m_EnbCmdTbl[0x14] = 0;
	m_EnbCmdTbl[0x16] = 0;
	m_EnbBusy = 0;
	/*
	m_PrintStatus = PRT_COD_WAIT;
	m_PrintExtra = PRT_NONE;
	::ZeroMemory(m_Analysis,sizeof(m_Analysis));
	::ZeroMemory(m_Poci,sizeof(m_Poci));
	*/
}

CLisa2000Filter::~CLisa2000Filter()
{

}

DWORD CLisa2000Filter::ProcessRcvByte(BYTE Val)
{
	if ((m_LastCommand == 5) && (m_Status == ST_WAIT_ANSWER))
	{
		strcat(m_OutStr,RCV_STR);
		PrintHexValue(Val,m_OutStr);
		strcat(m_OutStr,"\x0d\x0a");
		m_Status = ST_WAIT_COMMAND;
		if (m_Cmd05Ans == Val)
			return 0;
		m_Cmd05Ans = Val;
		if (m_EnbCmdTbl[m_LastCommand])
				return 2;
		return 0;
	}
	switch(Val)
	{
	case 1: 
		{
			strcat(m_OutStr,"SOH ");
			m_Status = ST_RCV_DATA;
			break;
		}
	case 2: 
		{
			if ((m_LastCommand == 0x13) || (m_LastCommand == 0x12))
			{
				strcat(m_OutStr,"\x0d\x0a");
				strcat(m_OutStr,RCV_STR);
			}
			strcat(m_OutStr,"STX ");
			break;
		}
	case 3: 
		{
			if (m_Status == ST_WAIT_ANSWER)
			{
				// Se recibio un ETX cuando se esperaba informacion
				m_OutStr[0]=0;
				m_Status = ST_WAIT_COMMAND;
			}
			else
			{
				strcat(m_OutStr," ETX");
			}
			break;
		}
	case 4: 
		{
			strcat(m_OutStr," EOT\x0d\x0a");
			m_Status = ST_WAIT_COMMAND;
			if (m_EnbCmdTbl[m_LastCommand])
				return 2;
			break;
		}
	case 0x1A:
		{
			m_Status = ST_WAIT_COMMAND;
			if (m_EnbBusy)
			{
				strcat(m_OutStr," BUSY\x0d\x0a");
				if (m_EnbCmdTbl[m_LastCommand])
					return 2;
			}
			break;
		}
	case 0x1b:
		{
			strcat(m_OutStr,RCV_STR);
			strcat(m_OutStr,"READY ");
			m_Status = ST_WAIT_DATA;
			break;
		}
	default:
		{
			m_OutStr[strlen(m_OutStr)+1]=0;
			m_OutStr[strlen(m_OutStr)]=Val;		
			break;
		}
	}
	return 0;
}

DWORD CLisa2000Filter::ProcessSndByte(BYTE Val)
{
	// Revisar Impresion
	if (m_LastCommand == 0x0f)
	{
		/*
		m_PrintCant++;
		ProcessPrintByte(Val);
		if (m_PrintCant == 50)
		{
			m_LastCommand = 0;
			m_Status = ST_WAIT_COMMAND;
		}
		*/
		return 0;
	}
	switch (Val)
	{
	case 1: 
		{
			if (m_Status == ST_WAIT_DATA)
				strcat(m_OutStr,"\x0d\x0a");
			strcat(m_OutStr,SND_STR);
			strcat(m_OutStr,"SOH ");
			break;
		}
	case 2: 
		{
			if ((m_LastCommand == 7) || (m_LastCommand == 8))
			{
				strcat(m_OutStr,"\x0d\x0a");
				strcat(m_OutStr,SND_STR);
			}
			strcat(m_OutStr,"STX ");
			break;
		}
	case 3: 
		{
			strcat(m_OutStr," ETX");
			break;
		}
	case 4: 
		{
			strcat(m_OutStr," EOT\x0d\x0a");
			m_Status = ST_WAIT_COMMAND;
			if (m_EnbCmdTbl[m_LastCommand])
				return 2;
			return 0;
			break;
		}
	default:
		{
			if ((m_Status == ST_WAIT_DATA)||(m_Status == ST_WAIT_COMMAND))
			{
				// Se envio un comando cuando se debia enviar informacion
				m_LastCommand = Val;
				/*
				if (m_LastCommand == 0x0F)
					m_PrintExtra = PRT_NONE;
					*/
				m_Status = ST_WAIT_ANSWER;
				strcpy(m_OutStr,SND_STR);
				PrintHexValue(Val,m_OutStr);
				strcat(m_OutStr,"  ");
				//strcat(m_OutStr,"\x0d\x0a");
				/*
				if (Val == 0x0f)
					m_PrintCant = 0;
					*/
				return 0;
			}
			char tmpstr[2];
			tmpstr[0] = Val;
			tmpstr[1] = 0;
			strcat(m_OutStr,tmpstr);
			/*
			m_OutStr[strlen(m_OutStr)+1]=0;
			m_OutStr[strlen(m_OutStr)]=Val;
			*/
			break;
		}
	}
	m_Status = ST_SND_DATA;
	return 0;
}

DWORD CLisa2000Filter::PrintHexValue(BYTE value, char *str)
{
	char tmp[3];
	tmp[0]=(value >> 4) + '0'; 
	tmp[1]=(value & 0x0F) + '0';

	if (tmp[0] > '9') tmp[0] += 7;
	if (tmp[1] > '9') tmp[1] += 7;
	tmp[2] = 0;
	strcat(str,tmp);
	return 0;	
}


DWORD CLisa2000Filter::SaveToFile(HANDLE hFile)
{
	DWORD BytesWritten;
	WriteFile(hFile,m_OutStr,strlen(m_OutStr),&BytesWritten,NULL);
	m_OutStr[0]=0;
	return 0;
}

DWORD CLisa2000Filter::EnableCommand(BYTE bCmd, BOOL bEnable)
{
	if (bCmd == 0)
		m_EnbBusy = bEnable;
	else
		m_EnbCmdTbl[bCmd] = bEnable;
	return 0;
}

DWORD CLisa2000Filter::ClearString(char *string)
{
	DWORD i;
	for (i=strlen(string);i>0;i--)
	{
		if (string[i]==0x20) string[i]=0;
		if (string[i]!=0) break;
	}
	return 0;
}

DWORD CLisa2000Filter::ProcessPrintByte(BYTE Val)
{
	/*
	if (m_PrintCant == 1)
	{
		if (Val == 0x80) m_PrintStatus = PRT_COD_WAIT;	// Si aparece una ralla se incia el ciclo de nuevo

		if ((Val == 0x12) || (Val == 0x95) || (Val == 0x0F) || (Val == 0x1B) || (Val == 0x81))
		{
			m_PrintExtra = PRT_IGNORE;
		}
	}
	if (m_PrintExtra == PRT_IGNORE)
		return 0;
	switch (m_PrintStatus)
	{
	case PRT_COD_WAIT:
		{
			switch (m_PrintCant)
			{
			case 1:
				{
					if (Val == 'C') 
						m_PrintExtra = PRT_USR+1;
					else
						m_PrintExtra = PRT_IGNORE;
					break;
				}
			case 2:
				{
					if ((Val == 'O') && (m_PrintExtra == PRT_USR+1))
						m_PrintExtra = PRT_USR+2;
					else
						m_PrintExtra = PRT_IGNORE;
					break;
				}
			case 3:
				{
					if ((Val == 'D') && (m_PrintExtra == PRT_USR+2))
						m_PrintExtra = PRT_USR+3;
					else
						m_PrintExtra = PRT_IGNORE;
					break;
				}
			case 4:
				{
					if ((Val == '.') && (m_PrintExtra == PRT_USR+3))
					{
						m_PrintExtra = PRT_IGNORE;
						m_PrintStatus = PRT_COD_20;
					}
					else
						m_PrintExtra = PRT_IGNORE;
					break;
				}
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
			if ((m_PrintCant == 1) && (Val == 0x20))
				m_PrintStatus++;				// pasar al proximo estatus
			else
				m_PrintStatus = PRT_COD_WAIT;	// esto no deberia suceder
			m_PrintExtra = PRT_IGNORE;
			break;
		}
	case PRT_COD_GET:
		{
			m_COD[m_PrintCant-1]=Val;
			if (Val ==0)
			{
				ClearString(m_COD);
				m_PrintExtra = PRT_IGNORE;
				m_PrintStatus++;
			}
			break;
		}
	case PRT_POCI_READ:
		{
			if ((m_PrintCant == 1) && (Val == 'P')) m_PrintExtra = PRT_USR+1;
			if ((m_PrintCant == 2) && (Val == 'O') && m_PrintExtra == PRT_USR+1) m_PrintExtra = PRT_USR+2;
			if ((m_PrintCant == 3) && (Val == 'C') && m_PrintExtra == PRT_USR+2) m_PrintExtra = PRT_USR+3;
			if ((m_PrintCant == 4) && (Val == 'I') && m_PrintExtra == PRT_USR+3)
			{
				m_PrintExtra = PRT_IGNORE;
				m_PrintStatus++;
			}
			if (m_PrintCant == 5)
				m_PrintStatus = PRT_COD_WAIT;
			break;
		}
	case PRT_POCI_GET:
		{
			if ((m_PrintCant == 1) && (Val == 0x20)) m_PrintExtra = PRT_USR+1;
			if ((m_PrintCant == 2) && m_PrintExtra == PRT_USR+1) m_NoPoci = Val-0x30;
			if ((m_PrintCant == 3) && m_PrintExtra == PRT_USR+1)
			{
				if (Val !=0x20)
				{
					m_NoPoci *=10;
					m_NoPoci += (Val-0x30);
				}
				m_PrintExtra = PRT_IGNORE;
				m_PrintStatus++;
			}
			if (m_PrintCant == 4)
				m_PrintStatus = PRT_COD_WAIT;
			break;
		}
	case PRT_FECH_READ:
		{
			if ((m_PrintCant == 1) && (Val == 'F')) m_PrintExtra = PRT_USR+1;
			if ((m_PrintCant == 2) && (Val == 'E') && m_PrintExtra == PRT_USR+1) m_PrintExtra = PRT_USR+2;
			if ((m_PrintCant == 3) && (Val == 'C') && m_PrintExtra == PRT_USR+2) m_PrintExtra = PRT_USR+3;
			if ((m_PrintCant == 4) && (Val == 'H') && m_PrintExtra == PRT_USR+3)
			{
				m_PrintExtra = PRT_IGNORE;
				m_PrintStatus++;
			}
			if (m_PrintCant == 5)
				m_PrintStatus = PRT_COD_WAIT;
			break;
		}
	case PRT_FECH_GET:
	case PRT_HORA_READ:
	case PRT_HORA_GET:
		{
			m_PrintExtra = PRT_IGNORE;
			m_PrintStatus++;
			break;
		}
	case PRT_HORA_0D:
	case PRT_ANA_0D:
		{
			// si aparece el fin de linea pasar al proximo estado 
			if ((m_PrintCant == 1) && (Val == 0x0D))
			{
				m_PrintStatus++;				// pasar al proximo estatus
				m_PrintExtra = PRT_IGNORE;
			}
			break;
		}
	case PRT_ANA_GET:
		{
			m_tmpAnalysis.name[m_PrintCant-1]=Val;
			if (Val ==0)
			{
				ClearString(m_tmpAnalysis.name);
				m_PrintExtra = PRT_IGNORE;
				m_PrintStatus++;
			}
			break;
		}
	case PRT_VAL_GET:
		{
			switch (m_PrintCant)
			{
			case 1:
				{
					if (Val != 0x20)
					{
						m_PrintExtra = PRT_IGNORE;
						m_PrintStatus = PRT_COD_WAIT;
					}
					break;
				}
			case 2:
				{
					m_AVal = (float)(Val-0x30);
					m_PrintExtra = PRT_USR+1;
					break;
				}
			default:
				{
					if (Val == '.')	{m_PrintExtra = 10;break;}
					if ((Val == 0x20)||(Val == 0x0)) 
					{
						m_PrintExtra = PRT_IGNORE;
						m_PrintStatus++;
						break;
					}
					if (m_PrintExtra == PRT_USR+1)
						m_AVal = m_AVal*10+Val-0x30;
					else
					{
						m_AVal = m_AVal+(float)(Val-0x30)/(float)m_PrintExtra;
						m_PrintExtra*=10;
					}
					break;
				}
			}
			break;
		}
	case PRT_MU_GET:
		{
			m_tmpAnalysis.measured_unit[m_PrintCant-1]=Val;
			if (Val ==0)
			{
				ClearString(m_tmpAnalysis.measured_unit);
				m_PrintExtra = PRT_IGNORE;
				m_PrintStatus = PRT_ANA_0D;
				ProcessResult();
			}
			break;
		}
	}
	*/
	return 0;
}

DWORD CLisa2000Filter::ProcessResult()
{
	/*
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
	m_Poci[m_NoPoci-1].status[Index].val = m_AVal;
	m_Poci[m_NoPoci-1].status[Index].stat = STAT_OK;
	strcpy(m_Poci[m_NoPoci-1].name,m_COD);
	*/
	return 0;
}

DWORD CLisa2000Filter::FillListBox(HWND hControl)
{
	/*
	// Recorre lista de analisis obtenidos
	DWORD i,j;
	char	string[300];
	::SendMessage(hControl,LB_RESETCONTENT,0,0);
	::SendMessage(hControl,LB_ADDSTRING,0,(long)"POCI   COD     ANALISIS   RESULTADO  U/M ");
	for (i=0;i<96;i++)
	{
		for (j=0;j<24;j++)
		{
			if (m_Poci[i].status[j].stat == STAT_OK)
			{
				sprintf(string," %-2.1d  %-10s %-10s %-7.2f  %-11s",i+1,m_Poci[i].name,m_Analysis[j].name,m_Poci[i].status[j].val,m_Analysis[j].measured_unit);
				::SendMessage(hControl,LB_ADDSTRING,0,(long)string);
			}
		}
	}
	*/
	return 0;
}

	


