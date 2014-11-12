// CServoSV900C.cpp: implementation of the CServoSV900C class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServoSV900C.h"
#include "ServoSV900CDriver.h"
#include "..\clases\errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Estados en los que se puede encontrar el procesamiento de la curvas

#define ST_WBED		0		// se espera el numero de cama
#define ST_BED		1		// ya se recibio el numero de cama
#define ST_WEOT		2		// Se espera el eot
#define ST_EOT		3		// Ya se recibio el eot
// estado de la lectura de curvas
#define ST_FHI		4
#define ST_FLOW		5
#define ST_PIHI		6
#define ST_PILOW	7
#define ST_PEHI		8
#define ST_PELOW	9
// 
//Estados de la maquina de lectura de alarmas
#define ST_BYTE1	1		// Se espera el 1er Byte
#define ST_BYTE2	2		// Ya se recibio el 1 y se espera el 2
#define ST_BYTE3	3		// Ya se recibio el 2 y se espera el 3
#define ST_FINISH	4		// Se termino el procesamineto de datos

CServoSV900C::CServoSV900C()
{
	ConnectStatus = ERR_UNKNOWN;
	PPuntualStatus= ERR_UNKNOWN;
	GraphStatus   = ERR_UNKNOWN;
	AlarmErrStatus= ERR_UNKNOWN;
	BedNo = 0;
	MasterDriver = NULL;
	m_CurrentCommand = CMD_CC;
}

CServoSV900C::~CServoSV900C()
{

}

DWORD CServoSV900C::SetSerialInterfaz(CSerialPort *lpISerialPort)
{
	SerialPort = lpISerialPort;
	return 0;
}

DWORD CServoSV900C::RequestData()
{
	// Revisa todos ls comandos de uno en uno
	switch (m_CurrentCommand)
	{
	case CMD_CC:
		if (ConnectStatus == ERR_PENDING) return RequestCC();
		m_CurrentCommand = CMD_LPP;
	case CMD_LPP:
		if (PPuntualStatus == ERR_PENDING) return RequestPP();
		m_CurrentCommand = CMD_LC;
	case CMD_LC:
		if (GraphStatus == ERR_PENDING) return RequestLC();
		m_CurrentCommand = CMD_LA;
	case CMD_LA:
		if (AlarmErrStatus == ERR_PENDING) return RequestLA();
		m_CurrentCommand = CMD_CC;
	}
	return ERR_NONE;	// No se proceso comando alguno
}

DWORD CServoSV900C::SetMasterDriverInterfaz(void *lpIServoDriver)
{
	MasterDriver = lpIServoDriver;
	return 0;
}



DWORD CServoSV900C::OnReceivedData(BYTE *Buffer, DWORD cant)
{
	if (cant==0) return OnWaitTimeOut();
	for (DWORD i=0;i< cant;i++)
	{
		switch (m_CurrentCommand)
		{
		case CMD_CC: ProcessDataCC(Buffer[i]);break;
		case CMD_LC: ProcessDataLC(Buffer[i]);break;
		case CMD_LPP: if (PPuntualStatus==ERR_PENDING) ProcessDataLPP(Buffer[i]);break;
		case CMD_LA: if (AlarmErrStatus==ERR_PENDING) ProcessDataLA(Buffer[i]);break;
		}
	}
	SerialPort->SetupRead();
	return 0;
}

DWORD CServoSV900C::OnSendBytes(DWORD dwBytesWritten)
{
	SerialPort->SetupRead();
	return 0;
}

DWORD CServoSV900C::Initialize()
{
	return 0;
}

DWORD CServoSV900C::SetBedNo(BYTE bBedNo)
{
	BedNo = bBedNo | 0xC0;
	return 0;
}

DWORD CServoSV900C::ProcessDataCC(BYTE Value)
{
	if (Value >= 0x80) return ProcessCtrlByteCC(Value);
	if (ConnectStatus != ERR_PENDING)
		return ERR_NONE;
	switch (m_CmdState)
	{
	case ST_BED:
		{
			if (Value != ACK)
				ConnectStatus = ERR_INVANSWER;
			m_CmdState = ST_EOT;
			break;
		}
	}
	return 0;
}

DWORD _stdcall CServoSV900C::RequestCommand(DWORD CommandID)
{
	switch (CommandID)
	{
	case CMD_CC: return CheckConnection();
	case CMD_LC: return GetGraphs();
	//case CMD_LPP: return GetPuntualParams();
	default:
		return ERR_INVCMD;
	}
	return ERR_NONE;
}

DWORD _stdcall CServoSV900C::GetGraphs(float *pPressBuff, float *pFlowBuff, float *pVolBuff)
{
	if (GraphStatus != ERR_NONE)
		return GraphStatus;
	GraphStatus = ERR_UNKNOWN;
	memcpy(pPressBuff,GraphPressE,GraphPos*sizeof(float));
	memcpy(pFlowBuff,GraphFlow,GraphPos*sizeof(float));
	memcpy(pVolBuff,GraphPressI,GraphPos*sizeof(float));
	return ERR_NONE;	
}

DWORD _stdcall CServoSV900C::GetPuntualParams(float* BufferPPuntuals)
{
	switch (PPuntualStatus)
	{
	case ERR_UNKNOWN:
		{
			PPuntualStatus = ERR_PENDING;
			((CServoSV900CDriver*)MasterDriver)->RequestData();
			return ERR_PENDING;
		}
	case ERR_NONE:
		{
			PPuntualStatus = ERR_UNKNOWN;
			memcpy(BufferPPuntuals,BuffPPunt,sizeof(BuffPPunt));
			return ERR_NONE;
		}
	case ERR_PENDING	: return ERR_PENDING;
	case ERR_INVANSWER	: return ERR_INVANSWER;
	default             : return 0;
	}
}	
	
DWORD _stdcall CServoSV900C::GetAlarmsStatus(BYTE* AlarmMaskValue)
{	
	switch (AlarmErrStatus)
	{
	case ERR_UNKNOWN:
		{
			AlarmErrStatus = ERR_PENDING;
			((CServoSV900CDriver*)MasterDriver)->RequestData();
			return ERR_PENDING;
		}
	case ERR_NONE:
		{
			AlarmErrStatus = ERR_UNKNOWN;
			*AlarmMaskValue=AlarmValue;
			return ERR_NONE;
		}
	case ERR_PENDING	: return ERR_PENDING;
	case ERR_INVANSWER	: return ERR_INVANSWER;
	default             : return 0;
	}
	return 0;
}


DWORD _stdcall CServoSV900C::GetExtError(DWORD CommandID)
{
	switch (CommandID)
	{
	case CMD_CC	: return GetExtErrorCC();
	case CMD_LC	: return GetExtErrorLC();
	case CMD_LPP: return GetLPPExtError();
	case CMD_LA	: return GetExtErrorLA();		
	default: 
		return ERR_OUT_RANGE;
	}
	return 0;
}

DWORD _stdcall CServoSV900C::GetDataLength(DWORD CommandID,DWORD* plength)
{
	switch (CommandID)
	{
	case CMD_LC: *plength = GraphPos;break;
	default :
		return ERR_INVCMD;
	}
	return 0;
}

DWORD CServoSV900C::ProcessDataLPP(BYTE Value)//retorna 0 si todo OK
{											  //retorna 1 si un problema
		
	if (!(FlagBedno^(Value==BedNo)))
	{
		m_ExtErrPP= ERX_INV_BED_ORDER;//Error de # de cama enviado mas de una vez en una trama	
		PPuntualStatus= ERR_INVANSWER;//Status del comando en error
		return 1;
	}
	
	if ((!FlagBedno)&&(Value==BedNo))
	{
			FlagBedno=true;//pongo Flag en uno porque en el 1erbyte llego BedNo
			return 0; //todo OK	
	}

	////////////Llego aqui solo cuando FlagBedno=1 y el byte no es BedNo
	if (Value & 0x80)
	{
		return ProcessCtrlBytePP(Value);
	}
	if (!FlagHiNibble)
	{
		if (ContParam==CantParam)
		{
		m_ExtErrPP= ERX_INV_PARAM_CANT;//Error mas de 21 parametros en un minuto
		PPuntualStatus= ERR_INVANSWER;//Status del comando en error
		return 1;
		}
		TempHiNibble=Value;
		FlagHiNibble= 1;
		return 0;
	}
	else
	{
		BuffPPunt[ContMin][ContParam]= float(TempHiNibble*64 + Value);//*64 debido a que son 6 bits de datos
		FlagHiNibble= 0;
		ContParam++;
		return 0;
	}
	
	
	return 0;
}

DWORD CServoSV900C::ProcessCtrlBytePP(BYTE CtrlByte)// Retorna 0 si todo OK
{													//         1 si hay problema
	if ((FlagBusy)&(CtrlByte!=EOT))
	{
		m_ExtErrPP=ERX_INVBUSY_FRAME;
		PPuntualStatus=ERR_INVANSWER;
		return 1;
	}
	
	switch (CtrlByte)
	{
	case NextMin:
		{
			if (!(ContMin==CantMinutes))
			{
				if (ContParam==CantParam)
				{
					ContParam=0;
					FlagHiNibble=0;
					ContMin++;
					return 0;// si se llega aqui es que todo ok y se espera nextmin
				}
				 m_ExtErrPP=ERX_INV_NEXTMIN;//Error fin de min sin haber fin de 21 param
				 PPuntualStatus=ERR_INVANSWER;
				 return 1;
			}
				m_ExtErrPP=ERX_INV_MINUT_CANT;//Error de 16 minutos 
				PPuntualStatus=ERR_INVANSWER;
			 return 1;
			break;
		}
	case EOT:
		{
			if (FlagBusy)//si se activo busy entonces como se recibio EOT entonces todo OK
			{
				PPuntualStatus=ERR_NONE;//Termino el Comando BUSY
				return 0;
			}
			if (ContParam==CantParam)
			{
				//ContParam=0;
				//FlagHiNibble=0;
				//int ReturnCantMin=ContMin;//Puede servir en futuro para return CantMin
				//ContMin=0;
				OnEot = true;
			 //PPuntualStatus=ERR_NONE;// Terminó la Lectura de Parámetros Puntuales 
			 return	0;
			}
			 m_ExtErrPP=ERX_INV_EOT;//Si aun no están los 21 parametros EOT es invalido
			 PPuntualStatus=ERR_INVANSWER;
			 return 1;
			break;
		}
	case BUSY:
		{	
			if ((!FlagBusy)&&(ContParam==0)&&(ContMin==0)&&(!FlagHiNibble))
			{	
				FlagBusy=true;
				return 0;
			}
			m_ExtErrPP=ERX_INVBUSY_FRAME;
			PPuntualStatus=ERR_INVANSWER;
			break;
		}
	default:
		{
			m_ExtErrPP=ERX_INV_CTRL_BYTE;// error de byte de control no permitido
			PPuntualStatus=ERR_INVANSWER;
			break;
		}
	
	}
	return 0;
}


DWORD CServoSV900C::ProcessDataLC(BYTE Value)
{
	if (Value >= 0x80) return ProcessCtrlByteLC(Value);
	if (GraphStatus != ERR_PENDING)
		return ERR_NONE;
	switch (m_CmdState)
	{
	case ST_FHI:
		{
			m_CmdState = ST_FLOW;
			GraphTmpHi = Value;
			break;
		}
	case ST_FLOW:
		{
			m_CmdState = ST_PIHI;
			GraphFlow[GraphPos] = GraphTmpHi*64.0f+Value;
			break;
		}
	case ST_PIHI:	
		{
			m_CmdState = ST_PILOW;
			GraphTmpHi = Value;
			break;
		}
	case ST_PILOW:	
		{
			m_CmdState = ST_PEHI;
			GraphPressI[GraphPos] = GraphTmpHi*64.0f+Value;
			break;
		}
	case ST_PEHI:	
		{
			m_CmdState = ST_PELOW;
			GraphTmpHi = Value;
			break;
		}
	case ST_PELOW:
		{
			m_CmdState = ST_FHI;
			GraphPressE[GraphPos] = GraphTmpHi*64.0f+Value;
			GraphPos++;
			break;
		}
	default:
		{
			GraphStatus = ERR_FAIL;
			break;
		}
	}
	return 0;
}

DWORD CServoSV900C::ProcessDataLA(BYTE Value)
{
	if (AlarmErrStatus==ERR_PENDING)
	{
		if (!(FlagBedno^(Value==BedNo)))
		{
			m_ExtErrLA= ERX_INV_BED_ORDER;//Error de # de cama enviado mas de una vez en una trama	
			AlarmErrStatus= ERR_INVANSWER;//Status del comando en error
			return 1;
		}
		
		if ((!FlagBedno)&&(Value==BedNo))
		{
			FlagBedno=true;//pongo Flag en uno porque en el 1erbyte llego BedNo
			return 0; //todo OK	
		}
		
		if (Value & 0x80)//si es byte de control
		{
			//ver estado de la maquina y decidir si el eot esta donde debe
			if (AlarmDataStatus==ST_FINISH)
			{
				if (Value==EOT)
				{
					FlagBedno=0;//Preparo los estados para la 
					AlarmDataStatus=ST_BYTE1;//proxima respuesta
					m_ExtErrLA=ERX_NONE;
					OnEot = true;
					//AlarmErrStatus=ERR_NONE;
					return 0;
				}
					m_ExtErrLA=ERX_INV_CTRL_BYTE;//Si es byte de control y no se recibe EOT
					AlarmErrStatus=ERR_INVANSWER;
					return 1;
			}
				m_ExtErrLA=ERX_INV_EOT;//Llego Byte de control sin haber terminado datos
				AlarmErrStatus=ERR_INVANSWER;
				return 1;
		}
		///////////////////////FINALMENTE SI ES BYTE DE DATO//////////////
		if (AlarmDataStatus==ST_BYTE1)
		{
			AlarmValue=Value;//Carga el valor de alarma en la variable que usa la interfaz
			AlarmDataStatus=ST_FINISH;
			return 0;
		}
		
		m_ExtErrLA=ERX_MUCH_DATA;//Llego Byte de dato cuando ya se habia acabado
		AlarmErrStatus=ERR_INVANSWER;
		return 1;
	}
	return 1;//Si se llega aqui es que hay algun error regresa con1 y AlarmErr el valor del error	
}

DWORD CServoSV900C::RequestCC()
{
	m_CmdState = ST_WBED;
	BYTE*	lpBuffer;
	DWORD	size;
	SerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = BedNo | 0xC0;
	lpBuffer[1] = CC; 
	lpBuffer[2] = EOT;
	SerialPort->Send(3);
	return ERR_PENDING;
}

DWORD CServoSV900C::RequestPP()
{
	//inicialización de los estados
	OnEot = false;
	ContParam=0;
	ContMin=0;
	FlagHiNibble=0;
	FlagBedno=false;
	FlagBusy=false;
	// inicialización del buffer de parametros puntuales
	int Min=0;int Param=0;
	for (Min=0;Min<CantMinutes;Min++)
		for (Param=0;Param<CantParam;Param++)
		{
			BuffPPunt[Min][Param]=5000;//valor a rellenar, 
					//cuando se encuentre nos esiguen tomando valores
		}	

	BYTE*	lpBuffer;
	DWORD	size;
	SerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = BedNo | 0xC0;
	lpBuffer[1] = LPP; 
	lpBuffer[2] = EOT;
	SerialPort->Send(3);
	return ERR_PENDING;
}

DWORD CServoSV900C::RequestLC()
{
	GraphPos = 0;
	m_CmdState = ST_WBED;
	BYTE*	lpBuffer;
	DWORD	size;
	SerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = BedNo;
	lpBuffer[1] = LC; 
	lpBuffer[2] = EOT;
	SerialPort->Send(3);
	return ERR_PENDING;
}

DWORD CServoSV900C::RequestLA()
{
	///Inicializacion de las variables utilizadas en ProcessLA
	OnEot = false;
	AlarmDataStatus=ST_BYTE1;
	AlarmValue=0;
	FlagBedno=0;
	///declaración de variables temporales a utilizar
	BYTE*	lpBuffer;
	DWORD	size;
	 
	SerialPort->GetWriteBuffer(&lpBuffer,&size);
	lpBuffer[0] = BedNo;
	lpBuffer[1] = LA; 
	lpBuffer[2] = EOT;
	SerialPort->Send(3);
	return ERR_PENDING;
}

DWORD CServoSV900C::ProcessCtrlByteLC(BYTE bValue)
{
	// Si se espera el numero de cama y no llega
	if (m_CmdState == ST_WBED)
	{
		if ((bValue != BedNo))
		{
			// error
			GraphStatus = ERR_INVANSWER;
			m_ExtErrLC = ERX_INVBED;
			return 0;
		}
		// si es el numero de cama entonces esperar datos
		m_CmdState = ST_FHI;
		return ERR_NONE;
	}
	switch (bValue)
	{
	case EOT:
		{
			if (m_CmdState == ST_FHI)
			{
				m_CmdState = ST_EOT;
				return 0;
			}
			GraphStatus = ERR_INVANSWER;
			break;
		}
	case MEXP:
		{
			// chequear el estatus
			if (m_CmdState != ST_FHI)
			{
				GraphStatus = ERR_INVANSWER;
				return ERR_NONE;
			}
			GraphFlow[GraphPos] = - 1000.0f;
			GraphPressI[GraphPos] = - 1000.0f;
			GraphPressE[GraphPos] = - 1000.0f;
			GraphPos++;
			break;
		}
	default:
		{
			GraphStatus = ERR_INVANSWER;
		}
	}
	return 0;
}

DWORD CServoSV900C::LCOnWaitTimeOut()
{
	// verificar que el comando no haya tenido error
	if (GraphStatus == ERR_PENDING)
	{
		if (m_CmdState == ST_EOT) 
			GraphStatus = ERR_NONE;
		else
		{
			m_ExtErrLC = ERX_COMM_BREAK;
			GraphStatus = ERR_INVANSWER;
		}
	}
	m_CurrentCommand = 	CMD_LA;
	if (RequestData() != ERR_PENDING)
		((CServoSV900CDriver*)MasterDriver)->NextDriverRequest();
	return 0;
}


DWORD CServoSV900C::CCOnWaitTimeOut()
{
	// si ya habia un error mantenerlo 
	if (ConnectStatus == ERR_PENDING)
	{
		switch (m_CmdState)
		{
		case ST_EOT:	ConnectStatus = ERR_NONE;break;
		case ST_WBED:	
			{
				m_ExtErrCC = ERX_NOANSWER;
				ConnectStatus = ERR_INVANSWER;
				break;
			}
		default:	
			{
				m_ExtErrCC = ERX_COMM_BREAK;
				ConnectStatus = ERR_INVANSWER;
				break;
			}
		}
	}
	m_CurrentCommand = 	CMD_LPP;
	if (RequestData() != ERR_PENDING)
		((CServoSV900CDriver*)MasterDriver)->NextDriverRequest();
	return ERR_NONE;
}

DWORD CServoSV900C::OnWaitTimeOut()
{
	// Chequear el status del comando
	switch (m_CurrentCommand)
	{
	case CMD_CC:	return CCOnWaitTimeOut();break;
	case CMD_LPP:	return LPPOnWaitTimeOut();break;
	case CMD_LC:	return LCOnWaitTimeOut();break;
	case CMD_LA:	return LAOnWaitTimeOut();break;
	}
	return 0;
}


DWORD CServoSV900C::LAOnWaitTimeOut()
{	
	if (AlarmErrStatus==ERR_PENDING)	
	{
		if (OnEot) 
		{
			OnEot = false;
			AlarmErrStatus = ERR_NONE;
		}
		else
		switch	(AlarmDataStatus)
		{
			case ST_BYTE1 :
				{
					AlarmErrStatus=ERR_INVANSWER;
					m_ExtErrLA=ERX_NOANSWER;
					break;
				}
			case ST_FINISH: 
				{
					AlarmErrStatus=ERR_NONE;
					break;
				}
			default:
				{
					AlarmErrStatus=ERR_INVANSWER;
					m_ExtErrLA=ERX_COMM_BREAK;		
					break;
				}
		}

	}	
	m_CurrentCommand = 	CMD_CC;
	((CServoSV900CDriver*)MasterDriver)->NextDriverRequest();
	return 0;
}


DWORD CServoSV900C::LPPOnWaitTimeOut()
{
	if (PPuntualStatus==ERR_PENDING)	
	{
		if (OnEot) 
		{
			OnEot = false;
			PPuntualStatus = ERR_NONE;
		}
		else
		{
		if (!FlagBedno)
			m_ExtErrPP=ERX_NOANSWER;
	
		else
			m_ExtErrPP=ERX_COMM_BREAK;

		PPuntualStatus=ERR_INVANSWER;
		}
	}	

	m_CurrentCommand = 	CMD_LC;
	if (RequestData() != ERR_PENDING)
		((CServoSV900CDriver*)MasterDriver)->NextDriverRequest();
	return 0;
}


DWORD CServoSV900C::ProcessCtrlByteCC(BYTE bValue)
{
	// si se esta esperando numero de cama, solo debe llegar numero de cama
	if (m_CmdState == ST_WBED)
	{
		if ((bValue != BedNo))
		{
			// error
			m_ExtErrCC = ERX_INVBED;
			ConnectStatus = ERR_INVANSWER;
			return ERR_NONE;
		}
		// si es el numero de cama entonces indicar que ya llego
		m_CmdState = ST_BED;
		return ERR_NONE;
	}
	// ver que byte de control llego y si se esperaba dicho byte
	switch (bValue)
	{
	case ACK:
		{
			if (m_CmdState != ST_BED)
			{
				ConnectStatus = ERR_INVANSWER;
				return ERR_NONE;
			}
			m_CmdState = ST_WEOT;
			break;
		}
	case EOT:
		{
			if (m_CmdState != ST_WEOT)
			{
				ConnectStatus = ERR_INVANSWER;
				return ERR_NONE;
			}
			m_CmdState = ST_EOT;
			break;
		}
	default:
		{
			ConnectStatus = ERR_INVANSWER;
			return ERR_NONE;
		}
	}
	return 0;
}

DWORD CServoSV900C::CheckConnection()
{
	switch (ConnectStatus)
	{
	case ERR_UNKNOWN: 
		{
			ConnectStatus = ERR_PENDING;
			((CServoSV900CDriver*)MasterDriver)->RequestData();
			break;
		}
	case ERR_PENDING:
	case ERR_INVANSWER: break;
	default : 
		{
			DWORD dwtmp = ConnectStatus;
			ConnectStatus = ERR_UNKNOWN;
			return dwtmp;
		}
	}
	return ConnectStatus;
}

DWORD CServoSV900C::GetGraphs()
{
	switch (GraphStatus)
	{
	case ERR_UNKNOWN:
		{
			GraphStatus = ERR_PENDING;
			((CServoSV900CDriver*)MasterDriver)->RequestData();
			break;
		}
	case ERR_INVANSWER: 
	case ERR_NONE:		
	case ERR_PENDING:	break;
	default:
		{
			DWORD tmpdw = GraphStatus;
			GraphStatus = ERR_UNKNOWN;
			return tmpdw;
		}
	}
	return  GraphStatus;
}

DWORD CServoSV900C::GetLPPExtError()
{
	if (PPuntualStatus==ERR_INVANSWER)
	{
		PPuntualStatus=ERR_UNKNOWN;
		return m_ExtErrPP;
	}
	return ERX_NONE;
}

DWORD CServoSV900C::GetExtErrorLC()
{
	if (GraphStatus != ERR_INVANSWER)	return ERR_NONE;
	GraphStatus = ERR_UNKNOWN;
	return m_ExtErrLC;

}

DWORD CServoSV900C::GetExtErrorCC()
{
	if (ConnectStatus != ERR_INVANSWER)	return ERR_NONE;
	ConnectStatus = ERR_UNKNOWN;
	return m_ExtErrCC;
}

DWORD CServoSV900C::GetExtErrorLA()
{
	if (AlarmErrStatus != ERR_INVANSWER) return ERR_NONE;
	AlarmErrStatus = ERR_UNKNOWN;
	return m_ExtErrLA;
}
