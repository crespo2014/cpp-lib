// SerialBus.h: interface for the CSerialBus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALBUS_H__FE0EBFCB_320F_41BC_BB7E_3ADC988FD0FD__INCLUDED_)
#define AFX_SERIALBUS_H__FE0EBFCB_320F_41BC_BB7E_3ADC988FD0FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "iserialport.h"
#include "ISerialPortEvents.h"
#include "ISerialBus.h"

#define SB_CMD_READ			1
#define SB_CMD_TIMEOUT		2
#define SB_CMD_GETSIGNAL	3
#define SB_CMD_SETSIGNAL	4
#define SB_CMD_STOPSEND		5
#define SB_CMD_WRITE		6	// Write command
#define SB_CMD_WRITERD		7	// Write and read

#define DC 0
#define DQ 1
#define DE 2
#define RS 3
#define ES 4
#define IE 5

class CSerialBus : public CISerialPort  
{
private:
	DWORD _stdcall ThreadWrite(BYTE* lpBuffer,DWORD dwCant);
	DWORD _stdcall ThreadRead(BYTE* lpBuffer,DWORD dwCant);
public:
	DWORD OnReadTrigger();
	DWORD DispatchReadData(BYTE* pbBuffer,DWORD dwSize);
	DWORD OnTrigger();
	DWORD ThreadProcessData(BYTE* pbBuffer,WORD wCant);
	DWORD SetID(DWORD dwID);
	DWORD ThreadGetData(BYTE* pbBuffer,WORD wSize,WORD* pwCant);
	CSerialBus();
	virtual ~CSerialBus();
private:
	DWORD	m_id;				// Usado por el switch para identificar el bus
	void*	m_pSerComParam;		// lParam en puerto serie
	BYTE	m_byDeviceBStatus;	// Device Buffer Status, (Empty,Full)

	BYTE*	m_SendBuffer;		// Datos que deben enviarse generados con (ThreadSend) este puntero se desplaza
	WORD	m_SendBufferSize;	// Cuando se agota este buffer se genera un onsend
	WORD	m_SendBufferPos;	// Posicion a tomar el proximo dato

	BYTE	m_WriteSubBuffer[255];	// SubBuffer de escritura, solicitado por el cliente

	BOOL	m_bOnDevice;		// Indica que hay un equipo conectado
	BOOL	m_bOnConfigure;		// Indica que ya el puerto esta configurado y no requiere el envio de dicho comando
	//BOOL	m_bOnDeviceBSize;	// Indica que se tiene disponible el tamaño del buffer del dispositivo 
	//BOOL	m_bOnWriteCmd;		// Comando de escritura solicitado
	BOOL	m_bOnReadCmd;		// Solicitud de lectura el tipo de comando lo determina la cantidad de bytes a escribir solo escritura WR, escritura mas lectura WR_RD, escritura corta FWR, escritura corta + lectura FWR_RD,									lectura RD,
	BOOL	m_OnConfigureCmd;	// El dispositivo necesita configurar los parametros del puerto.

	// Variables del metodo ThreadRead
	BYTE*	m_ReadBuff;			//	Buffer enviado (ThreadRead)
	WORD	m_ReadBuffSize;		//	Cantidad a leer (ThreadRead) usado en lectura asincronica como la menor cantidad de bytes
	WORD	m_ReadBuffCant;		//	Cantidad de datos leidos
	BOOL	m_OnAsyncRead;		//	Lectura asyncronica
	BOOL	m_OnReading;		//	Indica que no ha terminado el comando ThreadRead
	BOOL	m_OnLastBlock;		//	Cuando es true indica que se leyo un bloque de datos con timeout

	// Variables realacionadas con la lectura
	BYTE	m_ReadBuffer[100];	//	Buffer de lectura los bytes recividos se almacenan aqui
	WORD	m_ReadBufferCant;	//	Cantidad de bytes en el buffer de lectura

	WORD	m_WriteBuffer[40];	// Buffer de escritura 
	WORD	m_WriteBufferCant;	// Cantidad de bytes en el buffer de escritura
	
	// Variables del Trigger
	BOOL	m_OnReadTrigger;	// Trigger de lectura
	BOOL	m_OnWriteTrigger;	// Trigger de escritura
	BOOL	m_OnTrigger;		// Trigger
	BOOL	m_OnRequestTrigger;	// Pedido de datos
	
	
	ISerComEvents*	m_pSerComEvents;
	ISwitch*	m_pISwitch;


};

#endif // !defined(AFX_SERIALBUS_H__FE0EBFCB_320F_41BC_BB7E_3ADC988FD0FD__INCLUDED_)
