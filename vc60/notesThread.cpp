// notesThread.cpp: implementation of the CnotesThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "notesThread.h"
#include "progressDlg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CnotesThread::CnotesThread()
{

}

CnotesThread::~CnotesThread()
{

}

UINT CnotesThread::Thread()
{
	// en este punto el flow esta conectado y funcionado perfecto
	// si el flujo se deconecta el hilo termina
	DWORD	dwr;
		
 	HANDLE	hmsg_event;
	WORD	event_type;

	DWORD	msg_id;
	DWORD	msg_param;
	void*	msg_pdata;
	DWORD	timeout;
	DWORD	count;

	m_plog->_log(LOG_ERROR,"Thread Start ...");
	
	m_thread_st	= TH_ST_OK;

	GetMessageEvent(&hmsg_event);
	
	dwr = ERR_OK;
	for (;;)
	{
		
		switch (m_thread_st)
		{
		case TH_ST_OK:
		case NT_TRS_CONNECTING:
			{
				if (m_thread_st == NT_TRS_CONNECTING) timeout = 500;	else timeout = INFINITE;
				dwr = GetMessage(&msg_id,&msg_param,&msg_pdata,timeout);
				if (dwr == ERR_TIMEOUT)
				{
					dwr = Thread_OnTimeOut();
					break;
				}
				if (dwr != ERR_OK) 
				{
					sprintf(m_thread_error,"CnotesThread::Thread -> GetMessage failed ... %s",GetErrorMsg());
					break;
				}
				dwr = Thread_ProcessMsg(msg_id,msg_param,msg_pdata);
				ReplyMessage(dwr);
				dwr = ERR_OK;
				break;
			}
		case NT_TRS_CONNECTED:
			{
				if (!m_bReading) 
				{
					dwr = SetupRead();
					break;
				}
				dwr = m_flow.WaitEvent_Flow(hmsg_event,&event_type);
				if (dwr != ERR_OK)
				{
					sprintf(m_thread_error,"CnotesThread::Thread -> %s",m_flow.GetErrorMsg());
					break;
				}
				if (event_type == IO_ONEVENT)
				{
					dwr = PeekMessage(&msg_id,&msg_param,&msg_pdata);
					if (dwr != ERR_OK)
					{
						sprintf(m_thread_error,"CnotesThread::Thread -> PeekMessage failed ... %s",GetErrorMsg());
					}
					else
						dwr = Thread_ProcessMsg(msg_id,msg_param,msg_pdata);
					ReplyMessage(dwr);
					dwr = ERR_OK;
				}
				if (event_type == IO_ONREAD)
				{
					m_bReading = false;
					m_flow.OnReadEvent(&count);
					m_th_rdcount += count;
					dwr = Thread_Read();
				}
				if (event_type == IO_ONWRITE)
				{
					m_flow.OnWriteEvent(&count);
					m_th_wrcount+= count;
					dwr = Thread_Write();			
				}
				break;
			}
		default:
			{
				dwr = ERR_FATAL;
				sprintf(m_thread_error,"CnotesThread::Thread -> Invalid Thread status = %u ",m_thread_st);
				break;
			}
		}
		// para terminar el hilo se devuelve codigo de error pero el mensaje en blanco
		if ((m_thread_st == TH_ST_END) ||
			(m_thread_st == TH_ST_FAILED)) break;
		{
			break;
		}
		if (dwr != ERR_OK) 
		{
			m_flow.Close();
			m_thread_st	= TH_ST_OK;
			break;
		}
	}
	m_flow.Close();
	if (dwr != ERR_OK)
	{
		m_plog->_log(LOG_ERROR,"Thread End because %s ",m_thread_error);
		m_thread_st = TH_ST_FAILED;
		return ERR_FATAL;
	}
	m_plog->_log(LOG_ERROR,"Thread End ...");
	m_thread_st = TH_ST_NULL;
	return ERR_OK;
}

DWORD CnotesThread::SetupRead()
{
	DWORD	dwr;
	DWORD	count;
	dwr = m_flow.Read(&m_th_rdbuff[m_th_rdcount],sizeof(m_th_rdbuff)-m_th_rdcount,&count);
	if (dwr == ERR_OK) 
	{
		m_th_rdcount += count;
		return Thread_Read();
	}
	if (dwr != ERR_PENDING)
	{
		sprintf(m_thread_error,"CnotesThread::SetupRead -> %s",m_flow.GetErrorMsg());
		return ERR_FATAL;
	}
	m_bReading = true;
	return ERR_OK;
}

// procesar el buffer de lectura para ver si hay una respuesta completa y analizarla
// conmutar de estado
//DEL DWORD CnotesThread::ProcessRead()
//DEL {
//DEL 	char*	cptr;
//DEL 	m_rdbuff[m_readpos + m_readcount] = 0;
//DEL 	m_readpos+= m_readcount;
//DEL 	cptr = strchr(m_rdbuff,'\n');
//DEL 	if (cptr == NULL)
//DEL 	{
//DEL 		cptr = strchr(m_rdbuff,0);
//DEL 		if (cptr - m_rdbuff == m_readpos) return ERR_OK;	// el cero fue puesto por mi
//DEL 	}
//DEL 
//DEL 	if (cptr != NULL)
//DEL 	{
//DEL 		*cptr = 0;
//DEL 		glog._log(LOG_ERROR,"Rcv :: %s",m_rdbuff);
//DEL 		strcpy(m_op_result,m_rdbuff);
//DEL 		m_op_status = NT_OP_OK;
//DEL 		m_readcount = 0;
//DEL 		m_readpos = 0;
//DEL 	}
//DEL 	return ERR_OK;
//DEL }

//DEL DWORD CnotesThread::SetupWrite()
//DEL {
//DEL 	DWORD	dwr;
//DEL 	m_BytesToWrite = strlen(m_wrbuff);if (m_BytesToWrite == 0) return ERR_OK;
//DEL 	m_op_status = NT_OP_SENDING;
//DEL 	dwr = m_flow.Write(m_wrbuff,m_BytesToWrite,&m_BytesWritten);
//DEL 	if (dwr == ERR_OK)
//DEL 	{
//DEL 		m_op_status = NT_OP_PENDING;
//DEL 		return ERR_OK;
//DEL 	}
//DEL 	if (dwr == ERR_TIMEOUT) return ERR_OK;
//DEL 	
//DEL 	sprintf(m_thread_error,"CnotesThread::SetupRead -> %s",GetErrorMsg());
//DEL 	return ERR_FATAL;
//DEL }

DWORD CnotesThread::Execute(WORD cmd)
{
	DWORD	dwr;
	//progressDlg.ShowModal();
	return ERR_OK;
}


DWORD CnotesThread::NextStatus(WORD etype)
{
	// siempre se pone un punto porque si no es timeout pues se pasa al proximo estado
	// hay que chequear el tiempo transcurrido para saber si se se pone un punto o que.
	DWORD	dwr;
	/*
	if (etype == NT_ET_DLGINIT)
	{
		dwr = CheckServer();
		switch (m_th_op)
		{
		case NT_TH_OP_INIT_GETID: return Srv_Init_GetID();
		}
	}
	*/
	return ERR_OK;


}

DWORD CnotesThread::Server_Start(char *exe_path)
{
	char	exec_cmd[255];
	DWORD	pid;
	DWORD	dwr;
	STARTUPINFO			si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags  =STARTF_USESTDHANDLES;
	si.hStdInput=NULL;
	si.hStdOutput=NULL;
	si.hStdError=NULL;
	ZeroMemory( &pi, sizeof(pi));

	pid = GetCurrentProcessId();
	if (exe_path == NULL) 
		sprintf(exec_cmd,"\"IDManager.exe\" -pid %u",pid);
	else
		sprintf(exec_cmd,"\"%s\" -pid %u",exe_path,pid);

	glog._log(LOG_TRACE,"Launching .... %s ",exec_cmd);
	if (!CreateProcess(NULL,exec_cmd,NULL,NULL,FALSE,CREATE_NO_WINDOW,NULL,NULL,&si,&pi))
	{
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CnotesThread::StartServer -> CreateProcess ... failed ");
	}
	m_srv_pid = pi.dwProcessId;
	m_srv_hprocess = pi.hProcess;
	CloseHandle(pi.hThread);
	return ERR_OK;
}

DWORD CnotesThread::CheckServer()
{
	if (m_thread_st == NT_TRS_CONNECTED) return ERR_OK;
	if (WaitForSingleObject(m_srv_hprocess,0) == WAIT_OBJECT_0)
	{
		GetExitCodeProcess(m_srv_hprocess,&m_srv_ecode);
		CloseHandle(m_srv_hprocess);
		m_srv_hprocess = NULL;
		m_srv_pid = 0;
		return ERR_EOF;
	}
	return ERR_OK;
	
}

DWORD CnotesThread::Dlg_Event(WORD etype)
{
	/*
	DWORD	dwr;
	if (etype == NT_ET_DLGINIT) 
	{
		dwr = CheckServer();
		switch (m_th_op)
		{
		case NT_TH_OP_INIT_GETID: return Srv_Init_GetID();
		}
	}
	*/
	return ERR_OK;
}

DWORD CnotesThread::Dlg_OnInit()
{
	/*
	DWORD	dwr;
	if (m_th_op == NT_TH_OP_INIT_GETID)
	{
		progressDlg.SetText("Starting IDManager server ");
		dwr = StartServer("D:\\Proyectos VC60\\IDManager\\Debug\\IDManager.exe");
		if (dwr == ERR_OK) return dwr;
	}
	*/
	return ERR_OK;

}

// se recivio el fin de line o return hay que analizar la respuesta y conmutar de estado

DWORD CnotesThread::Thread_OnEOL()
{
	return ERR_OK;	
}

// realizar la proxima operacion disponible y cambiar el estado del hilo
DWORD CnotesThread::Thread_Next(WORD etype)
{
	return ERR_OK;		
}

DWORD CnotesThread::Thread_ProcessMsg(DWORD msg_id, DWORD msg_param, void *msg_data)
{
	switch(msg_id)
	{
	case TH_MSG_KILL:
	case TH_MSG_EXIT:
		{
			m_thread_st = TH_ST_END;
			break;
		}
	case TH_MSG_TEST:	break;
	case TH_MSG_CONNECT:
		{
			m_thread_st = NT_TRS_CONNECTING;
			m_th_retry  = 0;
			break;
		}
	case TH_MSG_DISCONNECT:
		{
			m_thread_st = TH_ST_OK;
			m_flow.Close();
			break;
		}
	case TH_MSG_OP: return Thread_OP((WORD)msg_param);
	}
	return ERR_OK;
}

DWORD CnotesThread::Thread_OnTimeOut()
{
	DWORD	dwr;
	DWORD	pid = GetCurrentProcessId();
	char	pname[20];
	
	if (m_thread_st == NT_TRS_CONNECTING)
	{
		m_flow.EnableAsyncMode(true);
		sprintf(pname,"%u",pid);
		for (;;)
		{
			dwr = m_flow.WaitPipe(pname,100);
			if (dwr == ERR_TIMEOUT) 
			{
				// revisar la cantidad de intentos
				m_th_retry ++; 
				if (m_th_retry == 5) 
				{
					m_thread_st = TH_ST_OK;
				}
				return ERR_OK;
			}
			if (dwr != ERR_OK) break;
			dwr = m_flow.PipeConnect(pname);if (dwr != ERR_OK) break;
			m_thread_st = NT_TRS_CONNECTED;
			m_bReading = false;
			m_bWriting = false;
			m_th_rdcount = 0;
			m_th_wrcount = 0;
			m_th_wrpos	 = 0;
			return ERR_OK;
		}
		sprintf(m_thread_error,"CnotesThread::Thread_OnTimeOut -> %s",m_flow.GetErrorMsg());
		return dwr;
	}
	return ERR_OK;
}

DWORD CnotesThread::Reset_All()
{
	DWORD	dwr;
	DWORD	thr;

	if (m_thread_st != TH_ST_OK)
	{
		CMsgThread::Release();
		dwr = CMsgThread::Initialize();		if (dwr != ERR_OK) return dwr;
	}
	dwr = Server_Start("D:\\Proyectos VC60\\IDManager\\Debug\\IDManager.exe");	if (dwr != ERR_OK) return dwr;
	dwr = SendMessage(TH_MSG_CONNECT,0,&thr);									if (dwr != ERR_OK) return dwr;
	if (thr != ERR_OK) 
	{
		return SetError(true,ERR_FATAL,"CnotesThread::Reset_All -> failed .... ",m_thread_error);		
	}
	return ERR_OK;
}

DWORD CnotesThread::Reset_Server()
{
	DWORD	dwr;
	DWORD	thr;
	dwr = SendMessage(TH_MSG_DISCONNECT,0,&thr);	if (dwr != ERR_OK) return dwr;
	return Reset_All();
	if (thr != ERR_OK) 
	{
		return SetError(true,ERR_FATAL,"CnotesThread::Reset_All -> failed .... ",m_thread_error);		
	}
		return ERR_OK;
	
}

DWORD CnotesThread::Start_Thread()
{
	/*
	if (m_thread_st == TH_ST_OK) return ERR_OK;
	
	CMsgThread::Release();
	dwr = CMsgThread::Initialize();		if (dwr != ERR_OK) return dwr;
	*/
	return ERR_OK;
	
}

DWORD CnotesThread::Thread_OP(WORD operation)
{
	//if (m_th_op != NT_OP_NULL) return ERR_FATAL;
	Thread_Refresh_Dlg(NT_TH_OPS_SENDING);
	switch (operation)
	{
	case NT_OP_SET_SRV:
		{
			m_th_wrcount = sprintf(m_th_wrbuff,"init -f");
			return Thread_Write();
		}
	}
	return ERR_OK;
}

// envia los datos que quedan por enviar o todos y cambia de estado
DWORD CnotesThread::Thread_Write()
{
	DWORD	count;
	DWORD	dwr;

	if (m_th_wrpos == m_th_wrcount) return Thread_Refresh_Dlg(NT_TH_OPS_WAIT);

	dwr = m_flow.Write(&m_th_wrbuff[m_th_wrpos],m_th_wrcount-m_th_wrpos,&count);
	if (dwr == ERR_PENDING) return ERR_OK;
	if (dwr != ERR_OK)
	{
		sprintf(m_thread_error,"CnotesThread::SetupRead -> %s",GetErrorMsg());
		return ERR_FATAL;
	}
	m_th_wrpos += count;
	return Thread_Write();
}

DWORD CnotesThread::Thread_Read()
{
	if (m_th_op_st != NT_TH_OPS_WAIT)
	{
		m_th_rdcount = 0;
		return ERR_OK;			// ignorar bytes por gusto
	}

	char*	cptr;
	m_th_rdbuff[m_th_rdcount] = 0;
	cptr = strchr(m_th_rdbuff,'\n');
	if (cptr == NULL) return ERR_OK;		// faltan datos
	*cptr = 0;
	Thread_Refresh_Dlg(NT_TH_OPS_OK);
	m_th_rdcount = 0;
	return ERR_OK;
}

DWORD CnotesThread::Thread_Refresh_Dlg(DWORD op_st)
{
	m_th_op_st = op_st;
	return ERR_OK;
}
