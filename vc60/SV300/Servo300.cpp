// Servo300.cpp: implementation of the CServo300 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Servo300.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define EOT		4
/*
	Maquina de estados
	I 0 0 0 0  9 0 0 0  8 0  0  0  P   E <EOT>
	| | | | |  | | | |  | |  |  |  |   |   |
	0 1 2 3 4  5 6 7 8  9 10 11 12 13  13  15
*/
#define SV_RC_I		0
#define SV_RC_E		1
#define SV_RC_P		2

#define SV_RC_ST0	0
#define SV_RC_ST1	1
#define SV_RC_ST2	2
#define SV_RC_ST3	3
#define SV_RC_ST4	4
#define SV_RC_ST5	5
#define SV_RC_ST6	6
#define SV_RC_ST7	7
#define SV_RC_ST8	8
#define SV_RC_ST9	9
#define SV_RC_ST10	10
#define SV_RC_ST11	11
#define SV_RC_ST12	12
#define SV_RC_ST13	13
#define SV_RC_STEOT	15
#define SV_RC_STERR	20

// Se esta recibiendo un mensaje de error
#define SV_ERR_ST1	1	//Recibida la E
#define SV_ERR_ST2	2
#define SV_ERR_ST3	3
/*
	ICommunicationEvents
*/
DWORD _stdcall CServo300::OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam)
{
	switch (m_CurrentCommand)
	{
	case SV_DEFINECURVE		: ProcessDC(Buffer,cant);break;
	case SV_DEFINEBREATH	: ProcessDB(Buffer,cant);break;
	case SV_READCURVES		: ProcessRCData(Buffer,cant);break;
	case SV_CHECKCONNECTION : ProcessCC(Buffer,cant);break;
	case SV_CHECKVERSION	: ProcessRV(Buffer,cant);break;//chequeo de versión 
	case SV_SETTIME			: ProcessST(Buffer,cant);break;
	case SV_ALARMSTATUS		: ProcessAO(Buffer,cant);break;
	case SV_READPARAMS		: ProcessRB(Buffer,cant);break;
	case SV_READTRENDS		: ProcessTO(Buffer,cant);break;
	case SV_READBATERY		: ProcessBC(Buffer,cant);break;
	case SV_READADDRESS		: ProcessAN(Buffer,cant);break;
	}
	if (cant != 0) m_ISerialPort->ThreadRead(NULL,0);
	return 0;
}
DWORD _stdcall CServo300::OnCommEvent(DWORD pEventMask,LPVOID lpParam)
{
	return 0;
}
DWORD _stdcall CServo300::OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam)
{
	m_ISerialPort->ThreadRead(NULL,0);
	return 0;
}
DWORD _stdcall CServo300::OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)
{
	return 0;
}
DWORD _stdcall CServo300::OnWaitTimeOut(LPVOID lpParam)
{
	return 0;
}
DWORD _stdcall CServo300::OnTrigger(LPVOID lpParam)
{
	return 0;
}
DWORD _stdcall CServo300::OnRequestData(LPVOID lpParam)
{
	if (m_CurrentCommand == SV_NONE) return NextCommand();
	return 0;
}
DWORD _stdcall CServo300::OnOpenPort(LPVOID lpParam)
{
	PORT_CONFIG	config;
	config.BaudRate = CBR_9600;
	config.ByteSize = 8;
	config.Parity = EVENPARITY;
	config.StopBits = ONESTOPBIT;
	config.CheckParity = false;
	config.DSRStopOutFlow = false;	 
	config.CTSStopOutFlow = false;			
	config.DSRStopInFlow = false;
	config.RTSMode = RTS_CONTROL_ENABLE;
	config.DTRMode = DTR_CONTROL_ENABLE;
	m_ISerialPort->SetPortConfiguration(&config);
	m_ISerialPort->SetCommMask(0);
	m_ISerialPort->SetReadTimeOuts(0,1500,1);
	return 0;
}


DWORD _stdcall  CServo300::OnSetSerialPort(ISerialPort* lpSerialPort)
{
	m_ISerialPort = lpSerialPort;
	if (!m_ISerialPort) return ERR_NOINTERFACE;
	m_ISerialPort->SetCommunicationMode(false,INFINITE,0,100);
	return ERR_NONE;
}

/*
	IUnknown
*/
DWORD _stdcall CServo300::QueryInterface(char* lpName,_IUnknown** lpInterfaz)
{
	DWORD dr;
	dr = GetInterfaz(lpName,lpInterfaz);
	if (dr == 0) AddRef();
	return dr;
}
DWORD _stdcall CServo300::AddRef()	
{
	InterlockedIncrement((long*)&m_cRef);
	return 0;
}
DWORD _stdcall CServo300::Release()
{
	DWORD dr;
	if (InterlockedDecrement((long*)&m_cRef) == 0)
	{
		dr = UnInitialize();
		DLLDestroyInstance(this);
		if (dr != 0) dr = -1;
		return dr;				// Error grave en destruccion del objeto
	}
	return m_cRef;
}

DWORD _stdcall CServo300::Initialize()
{
	m_OnInitialize = true;
	return ERR_NONE;
}

DWORD _stdcall CServo300::GetInterfaz(char* lpName,_IUnknown** lpInterfaz)
{
	*lpInterfaz = NULL;
	if (strcmp(lpName,"IUnknown") == 0)	*lpInterfaz = (IServo*)this;
	if (strcmp(lpName,"IServo") == 0) *lpInterfaz = (IServo*)this;
	if (strcmp(lpName,"ISerialPortEvents") == 0) *lpInterfaz = (_IUnknown*)(ISerialPortEvents*)this;
	if (*lpInterfaz == NULL) return ERR_NOINTERFACE;
	return ERR_NONE;
}

CServo300::CServo300()
{
	OnOneRequest  = false;
	m_OnInitialize = false;
	m_RCStatus = ERR_UNKNOWN;
	m_CurrentCommand = SV_NONE;
	m_RCphase = SV_RC_I;

	ConnectStatus = ERR_UNKNOWN;
	
	AddressStatus = ERR_UNKNOWN;
	VersionStatus = ERR_UNKNOWN;
	SetTimeStatus = ERR_UNKNOWN;
	BatteryStatus = ERR_UNKNOWN;
	PPuntualStatus = ERR_UNKNOWN;
	AlarmStatus = ERR_UNKNOWN;
	TrendStatus = ERR_UNKNOWN;
	DefineBreathStatus = ERR_UNKNOWN;
	DefineCurveStatus = ERR_UNKNOWN;
	// Frank
	Byte_Counter=0;
	VersionFlag=false;

	BYTE a[7]   = {57,48,48,80,67,73,04};//900PCIEOT EOT=04
	BYTE b[3]   = {42,48,52};				//*EOT	
	BYTE c[6]   = {83,89,51,48,48,47};		//SV300/
	memcpy(m_CC_Resp,a,sizeof(a));
	memcpy(m_CS_CT_ST_Resp,b,sizeof(b));
	memcpy(m_RV_Resp,c,sizeof(c));     
	Byte_Counter=0;
	VersionFlag=false;
	One_Value_Cont=0;
	Channel_Cont=0;
	ZeroMemory(Buff_PPunt,sizeof(Buff_PPunt));
	
	Buff_Scale_Factor[0]=5;
	Buff_Scale_Factor[1]=5;
	Buff_Scale_Factor[2]=50;
	Buff_Scale_Factor[3]=5;
	Buff_Scale_Factor[4]=50;
	Buff_Scale_Factor[5]=4.883f;
	Buff_Scale_Factor[6]=(float)4.883;
	Buff_Scale_Factor[7]=50;
	Buff_Scale_Factor[8]=50;
	Buff_Scale_Factor[9]=50;
	Buff_Scale_Factor[10]=200;
	Buff_Scale_Factor[11]=50;
	Buff_Scale_Factor[12]=50;
	Buff_Scale_Factor[13]=50;
	Buff_Scale_Factor[15]=1;
	Buff_Scale_Factor[29]=100;

}

CServo300::~CServo300()
{

}

DWORD _stdcall CServo300::RequestCommand(DWORD CommandID,LPVOID lpCmdData)
{
	if (CommandID == SV_READCURVES) return Request_RC(lpCmdData);
	switch (CommandID)
	{
	case SV_CHECKVERSION:
		{
			if (VersionStatus==ERR_UNKNOWN)
			{
				VersionStatus=ERR_PENDING;
				break;
			}
			VersionStatus=ERR_UNKNOWN;
			return VersionStatus;
		}
	case SV_SETTIME:
		{
			if (SetTimeStatus==ERR_UNKNOWN)
			{
				SetTimeStatus=ERR_PENDING;
				break;
			}
			SetTimeStatus=ERR_UNKNOWN;
			return SetTimeStatus;
		}
		
	case SV_ALARMSTATUS:
		{
			if (AlarmStatus==ERR_UNKNOWN)
			{
				AlarmStatus=ERR_PENDING;
				break;
			}
			AlarmStatus=ERR_UNKNOWN;
			return AlarmStatus;
		}
	case SV_READTRENDS:		
		{
			if (TrendStatus==ERR_UNKNOWN)
			{
				TrendStatus=ERR_PENDING;
				break;
			}
			TrendStatus=ERR_UNKNOWN;
			return TrendStatus;
		}
		
	case SV_READBATERY:
		{
			if (BatteryStatus==ERR_UNKNOWN)
			{
				BatteryStatus=ERR_PENDING;
				break;
			}
			BatteryStatus=ERR_UNKNOWN;
			return BatteryStatus;
		}
		
	case SV_READPARAMS:
		{
			if (PPuntualStatus==ERR_UNKNOWN)
			{
				PPuntualStatus=ERR_PENDING;
				break;
			}
			PPuntualStatus=ERR_UNKNOWN;
			return PPuntualStatus;
		}
		
	case SV_READADDRESS:
		{
			if (AddressStatus==ERR_UNKNOWN)
			{
				AddressStatus=ERR_PENDING;
				break;
			}
			AddressStatus=ERR_UNKNOWN;
			return AddressStatus;
		}
		
	case SV_CHECKCONNECTION:
		{
			if (ConnectStatus==ERR_UNKNOWN)
			{
				ConnectStatus=ERR_PENDING;
				break;
			}
			ConnectStatus=ERR_UNKNOWN;
			return ConnectStatus;
		}
		
	}
	if (!OnOneRequest) m_ISerialPort->RequestData();
	return 0;
}

DWORD _stdcall CServo300::GetCommandExtError(DWORD CommandID)
{
	return 0;
}

DWORD CServo300::ProcessRCData(BYTE *Buffer, DWORD dwcant)
{
	DWORD i;
	BYTE val;
	if (dwcant == 0)
	{
		if (m_CmdState == SV_RC_STEOT) 
		{
			m_curves[0].Count = m_RCpos;
			m_curves[1].Count = m_RCpos;
			m_curves[2].Count = m_RCpos;
			m_RCStatus = ERR_NONE;
		}
		else
		{
			m_RCError = ERX_COMM_BREAK;
			m_RCStatus = ERR_INVANSWER;
		}
		// Se llego al final del comando
		return NextCommand();
	}
	for (i=0;i<dwcant;i++)
	{
		if (m_RCStatus != ERR_PENDING) return 0;
		val = Buffer[i];
		// Maquina de estado
		if (m_CmdState == SV_RC_ST0)
		{
			if (val == 'E')// && (val != 'I') && (val != 'P'))
			{
				// Recibiendo un error
				m_CmdState = SV_ERR_ST1;
				continue;
			}
			if (val == 'I')
			{
				// Inicializacion se recivio la I inicial
				m_CmdState = SV_RC_ST1;
				m_RCtmpval = 0;
				m_RCpos = 0;
				m_RCphase = SV_RC_I;
				continue;
			}
			m_RCStatus = ERR_INVANSWER;
			break;
		}
		if (m_CmdState == SV_RC_ST1)
		{
			if (val == EOT)
			{
				m_CmdState = SV_RC_STEOT;
				continue;
			}
			if ((val != 'E') && (val != 'I') && (val != 'P'))
			{
				m_RCStatus = ERR_INVANSWER;
				continue;
			}
			m_RCtmpval = 0;
			continue;
		}
		if ((val < '0') ||( val > '9'))
		{
			m_RCStatus = ERR_INVANSWER;
			continue;
		}
		// Estados numericos
		m_RCtmpval*= 10;
		m_RCtmpval+= (val-'0');
		if (m_CmdState == SV_RC_ST4)	m_curves[0].Samples[m_RCpos] = Convert_UI(m_RCtmpval,0);
		if (m_CmdState == SV_RC_ST8)	m_curves[1].Samples[m_RCpos] = Convert_UI(m_RCtmpval,2);
		if (m_CmdState == SV_RC_ST12) 
		{
			m_curves[2].Samples[m_RCpos] = Convert_UI(m_RCtmpval,12);
			m_CmdState = SV_RC_ST1;
			m_RCpos ++;
		}
		else
			m_CmdState++;
		continue;
	}
	return 0;
}

DWORD CServo300::Request_RC(LPVOID lpCmdData)
{
	if (m_RCStatus == ERR_UNKNOWN)	
	{
		m_RCStatus = ERR_PENDING;
		if (!OnOneRequest) m_ISerialPort->RequestData();
	}
	if (m_RCStatus == ERR_NONE)	
	{
		m_RCStatus = ERR_UNKNOWN;
		memcpy(lpCmdData,m_curves,sizeof(m_curves));
		return ERR_NONE;
	}
	DWORD dwtmp = m_RCStatus;
	if (m_RCStatus != ERR_PENDING)	m_RCStatus = ERR_UNKNOWN;
	return dwtmp;
}

DWORD CServo300::NextCommand()
{
	OnOneRequest = true;
	for (;;)
	{
		switch (m_CurrentCommand)
		{
		case SV_NONE:
		case SV_CHECKVERSION:
			if (DefineBreathStatus == ERR_PENDING) 
			{
				m_CurrentCommand = SV_DEFINEBREATH;
				return DefineBreath();
			}
		case SV_DEFINEBREATH:
			if (DefineCurveStatus == ERR_PENDING) 
			{
				m_CurrentCommand = SV_DEFINECURVE;
				return DefineCurve();
			}
		case SV_DEFINECURVE:		
			if (SetTimeStatus == ERR_PENDING) 
			{
				m_CurrentCommand = SV_SETTIME;
				return SetTime();
			}
		case SV_SETTIME:
			if (AlarmStatus == ERR_PENDING)
			{
				m_CurrentCommand = SV_ALARMSTATUS;
				return GetAlarmStatus();
			}
		case SV_ALARMSTATUS:
			if (m_RCStatus == ERR_PENDING)
			{
				m_CurrentCommand = SV_READCURVES;
				return Send_RC();
			}
		case SV_READCURVES:
			if (TrendStatus == ERR_PENDING)
			{
				m_CurrentCommand = SV_READTRENDS; 
				return GetTrendOutput();
			}
		case SV_READTRENDS:		
			if (BatteryStatus== ERR_PENDING) 
			{
				m_CurrentCommand = SV_READBATERY;
				return BatteryCheck();
			}
		case SV_READBATERY:
			if (PPuntualStatus==ERR_PENDING)
			{
				m_CurrentCommand=SV_READPARAMS;
				return GetPuntualParams();
			}
		case SV_READPARAMS:
			if (AddressStatus== ERR_PENDING)
			{
				m_CurrentCommand = SV_READADDRESS;
				return GetAddressNo();
			}
		case SV_READADDRESS:
			if (ConnectStatus==ERR_PENDING)			
			{
				m_CurrentCommand=SV_CHECKCONNECTION;
				return CheckConnection();
			}
		case SV_CHECKCONNECTION:
			if (VersionStatus==ERR_PENDING)			
			{
				m_CurrentCommand=SV_CHECKVERSION;
				return CheckVersion();
			}
		}
		if (OnOneRequest == false)
		{
			m_CurrentCommand = SV_NONE;
			break;	// for
		}
		OnOneRequest = false;
		m_CurrentCommand = SV_CHECKVERSION;
	}
	return 0;

}


DWORD CServo300::GetAddressNo()
{
	BYTE*	lpBuffer;
	DWORD	size;
	m_ISerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = 65;//A
	lpBuffer[1] = 78;//N
	lpBuffer[2] = EOT;
	m_ISerialPort->ThreadSend(lpBuffer,3);
	//Envio de buffer por puerto serie
	return 0;
}

DWORD CServo300::GetAlarmStatus()
{
	BYTE*	lpBuffer;
	DWORD	size;
	m_ISerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = 'A';//A
	lpBuffer[1] = 'O';//O
	lpBuffer[2] = EOT;
	//Envio de buffer por puerto serie
	m_ISerialPort->ThreadSend(lpBuffer,3);
	return 0;
}


DWORD CServo300::BatteryCheck()
{
	BYTE*	lpBuffer;
	DWORD	size;
	m_ISerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = 66;//B
	lpBuffer[1] = 67;//C
	lpBuffer[2] = EOT;
	//Envio de buffer por puerto serie
	m_ISerialPort->ThreadSend(lpBuffer,3);
	return 0;

}

DWORD CServo300::ChangeTimeOut()
{
	BYTE*	lpBuffer;
	DWORD	size;
	m_ISerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = 67;//C
	lpBuffer[1] = 84;//T
	lpBuffer[2] = 0;//Value;
	lpBuffer[3] = EOT;
	//Envio de buffer por puerto serie
	m_ISerialPort->ThreadSend(lpBuffer,4);
	return 0;
}


DWORD CServo300::CheckConnection()
{
	BYTE*	lpBuffer;
	DWORD	size;
	m_ISerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = 72;//H
	lpBuffer[1] = 79;//O
	lpBuffer[2] = EOT;
	m_ISerialPort->ThreadSend(lpBuffer,3);
	//Envio de buffer por puerto serie 
	return 0;
}


DWORD CServo300::GetPuntualParams()
{
	BYTE*	lpBuffer;
	DWORD	size;
	m_ISerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = 82;//R
	lpBuffer[1] = 66;//B
	lpBuffer[2] = EOT;
	//Envio de buffer por puerto serie
	m_ISerialPort->ThreadSend(lpBuffer,3);
	return 0;
}


DWORD CServo300::GetTrendOutput() //Canal a leer y duración 
{
	BYTE*	lpBuffer;
	DWORD	size;
	m_ISerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = 84;//T
	lpBuffer[1] = 79;//O
	lpBuffer[2] = EOT;
	m_ISerialPort->ThreadSend(lpBuffer,3);
	return 0;
}

DWORD CServo300::CheckVersion()
{
	BYTE*	lpBuffer;
	DWORD	size;
	m_ISerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = 52;//R
	lpBuffer[1] = 56;//V
	lpBuffer[2] = EOT;
	//Envio de buffer por puerto serie
	m_ISerialPort->ThreadSend(lpBuffer,3);
	return 0;
}

DWORD CServo300::SetTime()
{
	return 0;
}

DWORD CServo300::Send_RC()
{
	DWORD dr;
	static BYTE	cmd[] = {'R','C','0','3','0','0',EOT};
	m_CmdState = SV_RC_ST0;
	dr = m_ISerialPort->ThreadSend(cmd,sizeof(cmd));
	return 0;
}

DWORD CServo300::UnInitialize()
{
	m_ISerialPort = NULL;
	return 0;
}

DWORD CServo300::ProcessCC(BYTE* Buffer,DWORD cant)
{

	//BYTE Data;
	if (cant==0)
	{
		if (ConnectStatus==ERR_PENDING)
		{
			ConnectStatus=ERR_INVANSWER;
		}
		return NextCommand();
	}
	for (DWORD i=0;i< cant;i++)
	{
		//Data=Buffer[i];
		if (Buffer[i]==EOT)//Verificar si es EOT
		{	
			 m_CC_Buff[Byte_Counter]=Buffer[i];
		
			 if (!memcmp(m_CC_Buff,m_CC_Resp,sizeof(m_CC_Buff)))
				{
					ConnectStatus=ERR_NONE;  //TODO  OK
					Byte_Counter=0;
					continue;
				}
					ConnectStatus=ERR_INVANSWER;//si los buffer no son iguales 
					Byte_Counter=0;				//status de respuesta invalida
					continue;
		}
		if (Byte_Counter<8)// si llegan mas de 7 bytes la respuesta no es 900pci4
		{
			m_CC_Buff[Byte_Counter]=Buffer[i]; //si no es EOT y no se han recibido 7bytes
			Byte_Counter++;						//lo almaceno en el buffer
		}
		else 
		{
			ConnectStatus=ERR_INVANSWER;
			Byte_Counter=0;		
		}		
	}
	return 0;
}




DWORD CServo300::ProcessRV(BYTE* Buffer,DWORD cant)
{
	
	if (cant==0)
	{
		if (VersionStatus==ERR_PENDING)
		{
			VersionStatus=ERR_INVANSWER;
			return 1;
		}
		NextCommand();
		return 0;
	}
	
	if(VersionStatus==ERR_PENDING)
	{
			for (DWORD i=0;i< cant;i++)
			{
				if (!(VersionStatus==ERR_INVANSWER))//mientras no hay error proceso bytes  
				{
					if(Buffer[i]==EOT)
					{
						if (VersionFlag)
						{
							m_RV_Buff[Byte_Counter]=Buffer[i];
							VersionStatus=ERR_NONE;  //TODO  OK
							Byte_Counter=0;
							VersionFlag=0;
							break;
						}
						VersionStatus=ERR_INVANSWER;//si se recibio EOT antes de chequear
						Byte_Counter=0;				//el estado de SV300/ hay error
						break;
					}
					if (Byte_Counter==5)
					{
						m_RV_Buff[Byte_Counter]=Buffer[i];//almaceno el sexto byte
						Byte_Counter++;
						if (!memcmp(m_RV_Buff,m_RV_Resp,sizeof(m_RV_Resp)))
						{
							VersionFlag=true;
							break;
						}
						VersionStatus=ERR_INVANSWER;//si los 1 eros 6 bytes no son
						Byte_Counter=0;				//SV300/ hay error
						break;
					}
					m_RV_Buff[Byte_Counter]=Buffer[i];//si no es EOT y no es el sexto byte 
					Byte_Counter++;				//solo se almacena y se pasa al otro	
				}
			}
	}
return 1;
}

DWORD CServo300::ProcessBC(BYTE* Buffer,DWORD cant)
{
	
	if (cant==0)
	{
		if (BatteryStatus==ERR_PENDING)
		{
			BatteryStatus=ERR_INVANSWER;
			return 1;
		}
		NextCommand();// ****************cuando retorne de NextCommand
		return 0; //////****************que pasa
	}
	if (BatteryStatus==	ERR_PENDING)
	{
		for (DWORD i=0;i< cant;i++)
		{		
			if (!(BatteryStatus==ERR_INVANSWER)) //mientras no hay error proceso datos
			{
				if(Buffer[i]==EOT)
				{
					if (Byte_Counter==3)
					{
					//convertir tres ascci a #
					//convertir el numero a unidades de ingenieria
					//almacenar valor en estructura 
					Battery_Val.volt=(float)(((m_BC_Buff[0]-48)*100)+((m_BC_Buff[1]-48)*10)+(m_BC_Buff[2]-48))/100;
					Byte_Counter=0;				
					return 0;//Todo OK
					}
					BatteryStatus=ERR_INVANSWER;//si llega EOT sin tener tres valores de batería
					Byte_Counter=0;				//hay error
					return 1;
				}
				if(Byte_Counter<3)
				{
					if ((Buffer[i]>47)&&(Buffer[i]<58))
					{
						m_BC_Buff[Byte_Counter]=Buffer[i];
						Byte_Counter++;
						break;			
					}
					BatteryStatus=ERR_INVANSWER;//llego un ascii que no es #
					Byte_Counter=0;				
					break;
				}
				BatteryStatus=ERR_INVANSWER;//Mas de tres Digitos sin llegar EOT
				Byte_Counter=0;				
				break;
			}
		}
	}
return 1;//si cant=0 y BatteryStatus no es pending hay error
} 


DWORD CServo300::ProcessST(BYTE* Buffer,DWORD cant)
{
	//BYTE Data=0;
	if (cant==0)
	{
		if (SetTimeStatus==ERR_PENDING)
		{
			SetTimeStatus=ERR_INVANSWER;
			return 1;
		}
		NextCommand();
		return 0;
	}

	if (SetTimeStatus==ERR_PENDING)
	{
		for (DWORD i=0;i< cant;i++)
		{
			if (!(SetTimeStatus==ERR_INVANSWER)) //mientras no hay error proceso datos
			{
				if (Buffer[i]==EOT)//Verificar si es EOT
				{	
					m_ST_Buff[Byte_Counter]=Buffer[i];
					if (!memcmp(m_ST_Buff,m_CS_CT_ST_Resp,sizeof(m_CS_CT_ST_Resp)))
					{
					SetTimeStatus=ERR_NONE;  //TODO  OK
					Byte_Counter=0;
					return 0;
					}
					SetTimeStatus=ERR_INVANSWER;//si los buffer no son iguales 
					Byte_Counter=0;				//status de respuesta invalida
					return 1;
				}
				if (Byte_Counter<3)
				{
					m_ST_Buff[Byte_Counter]=Buffer[i]; //Si el dato no es EOT lo almaceno y me voy
					Byte_Counter++;
				}
				else
				{
					SetTimeStatus=ERR_INVANSWER;
					Byte_Counter=0;				
				}
			}
		}
	}
	return 1;//si entra con el status que no sea pending hay error
}

DWORD CServo300::ProcessAO(BYTE* Buffer,DWORD cant)//Retorna 0 si todo OK, 1 si Error
{
	  if (cant==0)
	 {
		if (AlarmStatus==ERR_PENDING)
		{
			AlarmStatus=ERR_INVANSWER;
			return 1;
		}
		NextCommand();
		return 0;
	 }
	 int i=0;
	 int Temp=Buffer[i];
	 i++;
		 if (Buffer[i]==EOT)
		 {
			 if (Temp=='1')
			 {
			 //si hay alarma
			 AlarmStatus=ERR_NONE;
			 return 1;
			 }
			 if (Temp=='0')
			 {
			 //si no hay alarma
			 AlarmStatus=ERR_NONE;
			 return 0;
			 }
		 }
		AlarmStatus=ERR_INVANSWER;//si el 2do byte no es EOT y el primero no es 1 ni 0 Error
		return 1;
}

DWORD CServo300::ProcessRB(BYTE* Buffer,DWORD cant)
{
    if (cant==0)
	{
		if (PPuntualStatus==ERR_PENDING)
		{
			PPuntualStatus=ERR_INVANSWER;
			return 1;
		}
		Channel_Cont=0;
		NextCommand();
		return 0;
	}

	for (DWORD i=0;i< cant;i++)
	{
		if (!(PPuntualStatus==ERR_INVANSWER)) //mientras no hay error proceso datos
		{
			if (Buffer[Byte_Counter]==EOT)//Verificar si es EOT
			{
                if (One_Value_Cont==0)
				{
					if (Channel_Cont<31)//No pueden llegar mas de 31 valores de canales
					{
						PPuntualStatus=ERR_NONE;//**TODO OK********/
						Byte_Counter=0;
						return 0;
					}
						PPuntualStatus=ERR_INVANSWER;//Llegaron mas de 31 valore
						return 1;
				}
						PPuntualStatus=ERR_INVANSWER;//Llego EOT sin terminar 1valor
						return 1;
			}
			if ((Buffer[Byte_Counter]>0x29)&&(Buffer[Byte_Counter]<0x40))//Si el numero es valido lo almaceno
			{
				m_PP_Buff[One_Value_Cont]=Buffer[Byte_Counter];
				One_Value_Cont++;
				Byte_Counter++;
				if (One_Value_Cont==4)//voy agrupando 4 bytes ascii para formar un #  
				{
						// si ya se completaron  bytes
					//formo con el buffer un numero de cifras y lo almaceno
					int TempVal=(((m_PP_Buff[0]-0x30)*1000)+((m_PP_Buff[1]-0x30)*100)+((m_PP_Buff[2]-0x30)*10)+(m_PP_Buff[3]-0x30));
					//i--;
					//Convierte a unidades de ingenieria el valor obtenido de cada canal
					//Asigna a cada celda del buffer su canal verdadero
					switch (Channel_Cont)
					{
						case 0://InpTidalVol
							{
								Buff_PPunt[Channel_Cont].channel=1;
							break;
							}
						case 1://ExpTidalVol
							{
								Buff_PPunt[Channel_Cont].channel=3;
							break;
							}
						case 2://O2 Conc
							{
								Buff_PPunt[Channel_Cont].channel=4;
							break;
							}
						case 3://BaroPreassure
							{
								Buff_PPunt[Channel_Cont].channel=5;
							break;
							}
						case 4://PausePressure
							{
								Buff_PPunt[Channel_Cont].channel=7;
							break;
							}
						case 5://RespRateCalc
							{
								Buff_PPunt[Channel_Cont].channel=8;
							break;
							}
						case 6://PeakPreassure
							{
								Buff_PPunt[Channel_Cont].channel=9;
							break;
							}
						case 7://ExpMinVolumne
							{
								Buff_PPunt[Channel_Cont].channel=10;
							break;
							}
						case 8://MeanAirwayPress
							{
								Buff_PPunt[Channel_Cont].channel=11;
							break;
							}
						case 9://EndexpPressure
							{
								Buff_PPunt[Channel_Cont].channel=29;
							break;
							}
						default:
							{
								
							}
					}
						Buff_PPunt[Channel_Cont].fValue=Convert_UI(TempVal,Buff_PPunt[Channel_Cont].channel);
						Channel_Cont++;
						One_Value_Cont=0;
						continue;
				}
				continue;
			}
					PPuntualStatus=ERR_INVANSWER;// si no era ascii valido cambio status y me voy
					break;
		}
	}
return 1;
}




DWORD CServo300::ProcessTO(BYTE* Buffer,DWORD cant)
{
return 0;
}


DWORD CServo300::ProcessAN(BYTE* Buffer,DWORD cant)
{
return 0;
}

float CServo300::Convert_UI(int Value, int Channel)
{
	return (float)((Value-2048)*4.883)/Buff_Scale_Factor[Channel];
}

DWORD CServo300::DefineBreath()
{
	DWORD dr;
	static BYTE	cmd[] = {'D','B','0','1','0','3',
								 '0','4','0','5',
								 '0','7','0','8',
								 '0','9','1','0',
								 '1','1','2','9',EOT};
	dr = m_ISerialPort->ThreadSend(cmd,sizeof(cmd));
	return 0;


}

DWORD CServo300::ProcessDB(BYTE* Buffer,DWORD cant)
{
	if (cant==0)
	{
		if (DefineBreathStatus==ERR_PENDING)
		{
			DefineBreathStatus=ERR_INVANSWER;
			return 1;
		}
		NextCommand();
		return 0;
	}
	if (cant>2)
	{
		DefineBreathStatus=ERR_INVANSWER;
		return 1;
	}
	if (DefineBreathStatus==ERR_PENDING)
	{
		for (DWORD i=0;i< cant;i++)
		{
			if (!(DefineBreathStatus==ERR_INVANSWER)) //mientras no hay error proceso datos
			{
				if (Buffer[i]==EOT)//Verificar si es EOT
				{	
					m_ST_Buff[Byte_Counter]=Buffer[i];
					if (!memcmp(m_ST_Buff,m_CS_CT_ST_Resp,1))
					{
					DefineBreathStatus=ERR_NONE;  //TODO  OK
					Byte_Counter=0;
					return 0;
					}
					DefineBreathStatus=ERR_INVANSWER;//si los buffer no son iguales 
					Byte_Counter=0;				//status de respuesta invalida
					return 1;
				}
				if (Byte_Counter<3)
				{
					m_ST_Buff[Byte_Counter]=Buffer[i]; //Si el dato no es EOT lo almaceno y me voy
					Byte_Counter++;
				}
			}
		}
	}
	return 1;//si entra con el status que no sea pending hay error
}

DWORD CServo300::DefineCurve()
{
	DWORD dr;
	static BYTE	cmd[] = {'D','C','0','0','0','2',
								 '1','2',EOT};
	dr = m_ISerialPort->ThreadSend(cmd,sizeof(cmd));
	return 0;
}

DWORD CServo300::ProcessDC(BYTE *Buffer, DWORD cant)
{
	if (cant==0)
	{
		if (DefineCurveStatus==ERR_PENDING)
		{
			DefineCurveStatus=ERR_INVANSWER;
			//return 1;
		}
		NextCommand();
		return 0;
	}
	if (cant>2)
	{
		DefineCurveStatus=ERR_INVANSWER;
		return 1;
	}
	if (DefineCurveStatus==ERR_PENDING)
	{
		for (DWORD i=0;i< cant;i++)
		{
			if (!(DefineCurveStatus==ERR_INVANSWER)) //mientras no hay error proceso datos
			{
				if (Buffer[i]==EOT)//Verificar si es EOT
				{	
					m_ST_Buff[Byte_Counter]=Buffer[i];
					if (!memcmp(m_ST_Buff,m_CS_CT_ST_Resp,1))
					{
					DefineCurveStatus=ERR_NONE;  //TODO  OK
					Byte_Counter=0;
					return 0;
					}
					DefineCurveStatus=ERR_INVANSWER;//si los buffer no son iguales 
					Byte_Counter=0;				//status de respuesta invalida
					return 1;
				}
				if (Byte_Counter<3)
				{
					m_ST_Buff[Byte_Counter]=Buffer[i]; //Si el dato no es EOT lo almaceno y me voy
					Byte_Counter++;
				}
			}
		}
	}
	return 1;//si entra con el status que no sea pending hay error
}

DWORD _stdcall CServo300::InitializeDevice()
{
	if (DefineBreathStatus == ERR_UNKNOWN)
	{
		DefineBreathStatus = ERR_PENDING;
		DefineCurveStatus = ERR_PENDING;
		if (!OnOneRequest) m_ISerialPort->RequestData();
		return ERR_PENDING;
	}
	if ((DefineBreathStatus == ERR_PENDING) || (DefineCurveStatus == ERR_PENDING))
	{
		return ERR_PENDING;
	}
	if (DefineBreathStatus != ERR_NONE)
		return DefineBreathStatus;
	if (DefineCurveStatus != ERR_NONE)
		return DefineCurveStatus;
	return 0;
	
}
