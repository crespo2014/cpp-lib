// SerialBus.cpp: implementation of the CSerialBus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Switch.h"
#include "SerialBus.h"
#include "errorcodes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerialBus::CSerialBus()
{
	m_id = 0;
	m_bOnConfigure = true;	
}

CSerialBus::~CSerialBus()
{

}

DWORD CSerialBus::ThreadGetData(BYTE *pbBuffer, WORD wSize, WORD *pwCant)
{
	// No hay equipo conectado
	if (!m_bOnDevice)
	{
		pbBuffer[0] = IE;
		*pwCant = 1;
		return ERR_NONE;
	}
	if (!m_bOnConfigure)
	{
		// comando de configuracion de puerto
		return ERR_NONE;
	}

	if (m_WriteBufferCant)
	{
		if (m_byDeviceBStatus == 0)
		{
			pbBuffer[0] = DE;
			*pwCant = 1;
			return ERR_NONE;
		}
		if (m_bOnReadCmd) 
			pbBuffer[0] = DQ;
		else 
			pbBuffer[0] = DE;
		memmove(&pbBuffer[1],m_WriteBuffer,m_WriteBufferCant);
	}
	return 0;
}

DWORD _stdcall CSerialBus::ThreadWrite(BYTE* lpBuffer,DWORD dwCant)
{
	// Revisar el buffer en busca de caracteres especiales
	
	// Rellenar el buffer de 40 bytes
	DWORD cant = min(dwCant,40-m_WriteBufferCant);
	memmove(&m_WriteBuffer[m_WriteBufferCant],lpBuffer,cant);
	m_WriteBufferCant += cant;
	if (cant == dwCant)
	{
		m_SendBuffer = NULL;
		m_pSerComEvents->OnSendBytes(lpBuffer,dwCant,m_pSerComParam);
	}
	else
	{
		// No caben
		m_SendBuffer = lpBuffer;
		m_SendBufferSize = dwCant;
		m_SendBufferPos = cant;
	}
	return 0;
}

DWORD _stdcall CSerialBus::ThreadRead(BYTE* lpBuffer,DWORD dwCant)
{
	/*
		Si los bytes a enviar son pocos, el comando es escritura corta
		sino
			Ultimo bloque a enviar antes de leer.
		si no hay bytes entonces generar un read.
	*/
	m_bOnReadCmd = true;
	m_OnLastBlock = false;
	return 0;
}

DWORD CSerialBus::SetID(DWORD dwID)
{
	m_id = dwID;
	return ERR_NONE;
}

DWORD CSerialBus::ThreadProcessData(BYTE *pbBuffer, WORD wCant)
{

	return 0;
}

DWORD CSerialBus::OnTrigger()
{
	// Revisar trigger de escritura para generar OnSend
	//if (m_OnWriteTrigger) m_pSerComEvents->OnSendBytes(m_WriteBuffer,m_WriteBufferSize,m_pSerialParam);
	if (m_OnReadTrigger) return OnReadTrigger();
	return 0;
}

DWORD CSerialBus::DispatchReadData(BYTE *pbBuffer, DWORD dwSize)
{
	BOOL	Notify = false;
	// Acumular bytes recividos en m_ReadSubBuffer
	if ((pbBuffer) && (dwSize))
	{
		DWORD cant = min(dwSize,100-m_ReadBufferCant);
	}
	if (!((m_OnReading)||(m_OnAsyncRead))) return 0;
	if (m_OnReading)	
	{
		//	Operacion de lectura con ThreadRead
		if ((m_ReadBuff != NULL) && (m_ReadBuff != m_ReadBuffer) && (m_ReadBuffSize))	
		{
			// Copiar datos en el buffer brindado
			DWORD cant = min(m_ReadBuffSize-m_ReadBuffCant,m_ReadBufferCant);
			memcpy(m_ReadBuff,m_ReadBuffer,cant);
			m_ReadBuffCant += cant;
			//	Desplazar subbuffer
			if (m_ReadBufferCant > cant)
				memmove(m_ReadBuffer,&m_ReadBuffer[cant],m_ReadBufferCant - cant);
			m_ReadBufferCant -= cant;
		}
	}

	if (((m_ReadBufferCant != 0) && (m_OnAsyncRead)) ||
		((m_ReadBuffSize == m_ReadBuffCant)) ||
		((m_OnLastBlock)))
	{
		//	Notificar con trigger.
	}
	return ERR_NONE;
}

/*
	Usado para notificar que se leyeron bytes
	Aqui se llega por timeout o porque se leyeron todos los bytes solicitados
*/

DWORD CSerialBus::OnReadTrigger()
{
	if ((m_OnReading)&&(m_ReadBuffSize != 0)&&(m_ReadBuff != NULL)&&(m_ReadBuffCant))
	{
		// Reportar los bytes obtenidos
	}
	
	if (((m_ReadBuffSize == 0)||(m_ReadBuff == NULL))&&
		((m_ReadBufferCant)))	
	{
		// Reportar el buffer de lectura completo
		m_ReadBufferCant = 0;	// Vaciar el buffer
	}
	m_OnReading = false;	//	Lectura terminada
	if (m_OnLastBlock)
	{
		// Reportar ultimo bloque
		m_OnLastBlock = false;
	}
	return 0;

}
