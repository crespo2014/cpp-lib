// notesThread.h: interface for the CnotesThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTESTHREAD_H__B49D4D57_531D_4081_BFBF_C20779E9AE0A__INCLUDED_)
#define AFX_NOTESTHREAD_H__B49D4D57_531D_4081_BFBF_C20779E9AE0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MsgThread.h"
#include "ioflow.h"

/*
	estados del hilo
	-	stankdby	:	sin  hacer nada
	-	Coonecting	:	intentando conectar con el servidor (pipe)
	-	connected	:	conecta y transmitiendo datos
	-	lost		:	conexion perdida
*/

/*
	Posibles estado que coupa esta clase
	:: Apagado - no hay conexion ni servidor activo
	- Servidor lanzado y ejecutado correctamente
	- Servidor caido, perdida de conexion, se tiene el handle del proceso
	- servidor is up todo ok
	- envio de comandos y respuesta ( es un subestado)
	- inicializado el servidor
	- toma del fichero id
	- fin de la conexion
	- chequeo del fichero id
	se puede chequear la conecion y si esta caida se pierde el estado actual y todo
*/

// estados de la clase en cuestion
#define NT_ST_NULL			0	// Clase recien creada no hay conexion con pipe ni nada por el estilo
#define NT_ST_SRV_WAIT		1	// el hilo intenta conectarse cada 500ms, despues de varios intentos desiste
#define NT_ST_SRV_OK		2	// conectado de forma correcta al servidor
#define NT_ST_FAILD			3	// ocurrio un error y se espera por un accion del usuario

#define NT_TRS_CONNECTING	TH_ST_LAST + 2		// conectandose al servidor, esperando por el pipe
#define NT_TRS_CONNECTED	TH_ST_LAST + 3		// el hilo esta conectado al pipe y ok

// operaciones a realizar
#define NT_OP_NULL		0	// no hay operacion a realizar
#define NT_OP_SET_SRV	1	// setando parametros del servidor
#define NT_OP_GETID		2	// client option get id, descargar el fichero id, automaticamente se arranca el servidor
#define NT_OP_END		3	// Terminado aplicacion de forma satisfactoria

// estado de la operacion
//#define	NT_TH_OPS_WAIT		0	// por enviar, es la proxima operacion a realizar		
#define	NT_TH_OPS_SENDING	1	// escribiendo write
#define NT_TH_OPS_WAIT		2	// pendiente de respuesta
#define NT_TH_OPS_OK		4	// ya respondida y OK
//#define NT_TH_OPS_FAILD		5	// respuesta incorrecta

#define TH_MSG_CONNECT		TH_MSG_LAST + 1		// indicar al hilo que debe conectarse con el pipe
#define TH_MSG_DISCONNECT	TH_MSG_LAST + 2
#define TH_MSG_OP			TH_MSG_LAST + 3		// realizar la operacion cliente indicada en el parametro 

// Eventos generados que recive la clase con el dialogo activo
#define NT_ET_TIMEOUT		1	// 	tipo de evento que genera el proximo estado
#define NT_ET_THREAD		2	// mensaje enviado desde el hilo
#define NT_ET_DLGINIT		3	// el dialogo se he inicializado
#define NT_ET_RESET			4	// se ha reiniciado 
#define NT_ET_RETRY			5	// se ha reintentado
#define NT_ET_ABORT			6	// se ha abortado
#define NT_ET_END			7	// fin de la seccion en notes y de todas las operaciones

class CnotesThread : public CMsgThread 
{
public:
	DWORD Thread_Refresh_Dlg(DWORD op_st);
	DWORD Thread_Read();
	DWORD Thread_Write();
	DWORD Thread_OP(WORD operation);
	DWORD Start_Thread();
	DWORD Reset_Server();
	DWORD Reset_All();
	DWORD Thread_OnTimeOut();
	DWORD Thread_ProcessMsg(DWORD msg_id, DWORD msg_param, void *msg_data);
	DWORD Thread_Next(WORD etype);
	DWORD Thread_OnEOL();
	DWORD Dlg_OnInit();
	DWORD Dlg_Event(WORD etype);
	DWORD CheckServer();
	DWORD Server_Start(char* exe_path = NULL);
	DWORD NextStatus(WORD etype);	//tipo de evento que genera el proximo estado
	DWORD Execute(WORD cmd);
	DWORD SetupRead();
	CnotesThread();
	virtual ~CnotesThread();

	//variables de la clase
protected:
	WORD	m_gStatus;		// estado global
	WORD	m_gOp;			// proxima operacion realizada o realizando

	char	*m_op_str;		// indica la operacion que se esta realizando seteada por el hilo

	// variables del thread
	WORD	m_th_op;				// operacion que se esta realizando
	WORD	m_th_op_st;				// estado de la operacion actual
	WORD	m_th_op_step;			// suboperaciones o pasos
	char	m_th_rdbuff[255];
	char	m_th_wrbuff[512];
	DWORD	m_th_wrcount;			// cantidad de bytes a enviar
	DWORD	m_th_wrpos;			// posicion actual de envio
	DWORD	m_th_rdcount;			// cantidad de bytes leidos
	BOOL	m_th_srv_init;			// indica que se han inicializado todos los parametros del servidor
	WORD	m_th_retry;
	CIOFlow	m_flow;

private:
	BOOL	m_bReading;		//operacion de lectura pendiente
	BOOL	m_bWriting;
	char	m_thread_error[255];	// aqui va el mensaje de error de la ultima operacion que fallo en el hilo
	
	// servidor de operaciones
	DWORD	m_srv_pid;
	HANDLE	m_srv_hprocess;
	DWORD	m_srv_ecode;		//exit code
	
	virtual UINT Thread();
};

extern CnotesThread	notesThread;

#endif // !defined(AFX_NOTESTHREAD_H__B49D4D57_531D_4081_BFBF_C20779E9AE0A__INCLUDED_)
