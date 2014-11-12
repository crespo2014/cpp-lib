// Acs180_.cpp: implementation of the CAcs180 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Acs180_.h"
#include "errorcodes.h"
#include "dllcommon.h"
#include "Factory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BREAK	0x7C

#define ST_WAIT_STX		1
#define ST_GETTING		2	// Acumulando datos
#define ST_WAIT_BREAK	4	// se espera el recivo de un separador no es obligado si no llega se acumula lo recibido

/*
// m_frame
#define FRM_NONE		0
#define FRM_HEADER		1
#define FRM_PACIENT		2
#define FRM_OPERATION	3
#define FRM_RESULT		4
#define FRM_LAST		5
*/

// posicion de los separadores
#define FIELD_RECORD_TYPE	0	// Tipo de registro
#define FRM_TYPE_INDEX		0	// Indica el tipo de frame
#define ANA_PATIENT_INDEX	5
#define ANA_NO_INDEX		2
#define ANA_NAME_INDEX		2
#define ANA_VAL_INDEX		3
#define ANA_UNIT_INDEX		4
#define ANA_DATE_INDEX		12	

#define MAX_RESULTS 600

char*	DeviceName = "Tecnigen Bayer ACS:180";

CAcs180::CAcs180()
{
	m_DeviceName = DeviceName;
	m_HeaderSize = 2;
	m_RecordType = RECORD_NONE;
	ResetStatus();
}

CAcs180::~CAcs180()
{

}

DWORD CAcs180::ProcessData(BYTE *lpData, DWORD dwSize)
{
	return ProcessFieldsFrame(lpData,dwSize);
}

DWORD CAcs180::ResetStatus()
{
	memset(&m_Analysis,0,sizeof(m_Analysis));
	m_status = ST_WAIT_STX;
	return 0;
}

DWORD _stdcall CAcs180::ProcessField()
{
	BOOL	bError = false;
	do
	{
		if (m_FieldIndex == 0)	// Tipo de record 
		{
			if (m_LastChar == STX)	// Se recibio STX
			{
				m_HeaderSize = 2;	// Recibir dos bytes de identificacion de registro
				break;
			}
			if ((m_FieldPos != 2)||(m_Field[1] != m_LastChar)) 
			{
				AddToReport("Record Type Error (Especial char received)");
				bError = true;
				break;
			}
			switch (m_Field[1])
			{
			case 'H':
				{
					if (m_RecordType != RECORD_NONE)
					{
						AddToReport("Warning: Header record received without last record");
					}
					m_Status = ST_HEADERBYTES;
					m_HeaderSize = 4;
					m_RecordType = RECORD_HEADER;
					m_FieldDelimiter = 0;
					m_RepeatDelimiter = 0;
					m_EscapeDelimiter = 0;
					m_ComponentDelimiter = 0;
					AddToReport("\r\nHeader Block received");
					break;
				}
			case 'P':
				{
					if (m_RecordType != RECORD_HEADER) 
					{
						AddToReport("Patient Block received without header block");
						bError = true;
						break;
					}
					m_RecordType = RECORD_PATIENT;
					AddToReport("Patient Block received");
					break;
				}
			case 'O':
				{
					if (m_RecordType != RECORD_PATIENT)
					{
						AddToReport("Operation Block received without patient block");
						bError = true;
						break;
					}
					m_RecordType = RECORD_OPERATION;
					AddToReport("Operation Block received");
					break;
				}
			case 'R':
				{
					if (m_RecordType != RECORD_OPERATION) 
					{
						AddToReport("Result Block received without operation block");
						bError = true;
						break;
					}
					m_RecordType = RECORD_RESULT;
					AddToReport("Result Block received");
					break;
				}
			case 'L':
				{
					m_RecordType = RECORD_LAST;
					AddToReport("Last Block received");
					break;
				}
			default:
				{
					AddToReport("Unknown Block received");
					bError = true;
					break;
				}
			}
			break;
		}
		// tipo de record
		if (m_RecordType == RECORD_HEADER) 
		{
			if (m_FieldIndex == 1)
			{
				// Delimitadores
				if ((m_FieldPos != 4)||(m_Field[3] != m_LastChar)) 
				{
					AddToReport("Delimiters errors");
					bError = true;
					break;
				}
				m_FieldDelimiter = m_Field[0];
				m_RepeatDelimiter = m_Field[1];
				m_ComponentDelimiter = m_Field[2];
				m_EscapeDelimiter = m_Field[3];
			}
			if (m_FieldIndex == 5)
			{
				// Nombre del instrumento
				if (m_LastChar != m_FieldDelimiter) 
				{
					AddToReport("Error: Instrument name break"); 
					bError = true;
					break;
				}
				lstrcpyn(m_InstrumentName,m_Field,INSTR_NAME_SIZE);
			}
			if (m_FieldIndex == 13)
			{
				if (m_LastChar != 0x0d)
				{
					AddToReport("Error: No CR received in header block");
					bError = true;
					break;
				}
			}
			if (m_FieldIndex == 14)
			{
				if (m_LastChar != 0x0A)
				{
					AddToReport("Error: No LF received in header block");
					bError = true;
					break;
				}
			}
			if (m_FieldIndex == 15)
			{
				if (m_LastChar != ETX)
				{
					AddToReport("Error: No ETX received in header block");
					bError = true;
					break;
				}
			}
			if (m_FieldIndex == 16)
			{
				// CRC
				if (m_LastChar != 0x0D)
				{
					AddToReport("Error: No CR received in checksum - header block");
					bError = true;
					break;
				}
			}
			if (m_FieldIndex == 17)
			{
				// CRC
				if (m_LastChar != 0x0A)
				{
					AddToReport("Error: No LF received in checksum - header block");
					bError = true;
					break;
				}
			}
			if (m_FieldIndex == 18)
			{
				// CRC
				if (m_LastChar != STX)
				{
					AddToReport("Error: No STX received before checksum - header block");
					bError = true;
					break;
				}
			}
		}
		if (m_RecordType == RECORD_PATIENT)
		{
			if (m_FieldIndex == 6) 
			{
				if (m_ComponentIndex == 0) ::lstrcpyn(m_Analysis.PatientName,m_Field,AN_PATIENT_SIZE);
				if (m_ComponentIndex == 1) strcat(m_Analysis.PatientName,m_Field);
			}
		}
		if (m_RecordType ==RECORD_OPERATION)
		{
			if (m_FieldIndex == 3) ::lstrcpyn(m_Analysis.No,m_Field,AN_NO_SIZE);
		}
		if (m_RecordType ==RECORD_RESULT)
		{
			if (m_FieldIndex == 13) 
			{
				if (m_LastChar != CR) 
				{
					AddToReport("Error: Result record ending without CR "); 
					bError = true;
					break;
				}
				int tmp;
				sscanf(&m_Field[10],"%d",&tmp);
				m_Analysis.Minute = tmp;
				m_Field[10] = 0;
				sscanf(&m_Field[8],"%d",&tmp);
				m_Analysis.Hour = tmp;
				m_Field[8] = 0;
				sscanf(&m_Field[6],"%d",&tmp);
				m_Analysis.Day = tmp;
				m_Field[6] = 0;
				sscanf(&m_Field[4],"%d",&tmp);
				m_Analysis.Month = tmp;
				m_Field[4] = 0;
				sscanf(&m_Field[0],"%d",&tmp);
				m_Analysis.Year = tmp;
				AddAnalysis();
				ResetStatus();
				break;
			}
			if (m_FieldIndex == 3)
			{
				if (m_ComponentIndex == 3) ::lstrcpyn(m_Analysis.Name,m_Field,AN_NAME_SIZE);
				break;
			}
			if (m_LastChar != m_FieldDelimiter) 
			{
				AddToReport("Error: Result record break "); 
				bError = true;
				break;
			}
			if (m_FieldIndex == 4)
			{
				m_Analysis.Value = 0.0f;
				sscanf(m_Field,"%f",&m_Analysis.Value);
			}
			if (m_FieldIndex == 5) ::lstrcpyn(m_Analysis.Unit,m_Field,AN_UNIT_SIZE);
		}
	}
	while (false);
	if (bError) m_RecordType = RECORD_NONE;
	return 0;
}
