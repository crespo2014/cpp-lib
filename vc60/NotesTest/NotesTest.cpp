// NotesTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lotusitem.h"
#include "ioflow.h"
#include "MsgThread.h"

int main(int argc, char* argv[])
{
	/*
	CLotusSection	section;
	CLotusDB		lotusDB(&section);
	CLotusNote		note(&lotusDB);
	CLotusNote		note2(&lotusDB);
	//CLotusItem		item(&note);
	CMemArray		data;
	BYTE			*dptr;
//	_SIGNATURE		sig;
	_CD				cd;
	char	*psInitServer = "w2kls6/sia";
	WORD	datasize;
	char	m_server[200];
	char*	f_name = "ctomas.id";
	char	a_file[200];
	int		i;
	FONTIDFIELDS   *pFont;
	WORD	w;
	char	*cptr;

  */
	CMsgThread	thread;

	glog.SetConsoleOutput(true);
	glog.CreateLogFile();

 	thread.Initialize();
	thread.SendMessage(TH_MSG_TEST,0);
	Sleep(5000);
	thread.SendMessage(TH_MSG_TEST,0);
	Sleep(5000);
	thread.Release();
	
	return 0;
	BYTE	buff[200];
	DWORD	count;
		
	CIOFlow	flow;
	flow.EnableAsyncMode(false);
	flow.PipeConnect("tonto");
	//flow.ConnectPipe():
	flow.Read(SSIZE(buff),&count);
//	flow.CreateNamedPipe("tonto",PIPE_ACCESS_DUPLEX|FILE_FLAG_FIRST_PIPE_INSTANCE,PIPE_TYPE_BYTE,1,1024,1024,5000);
	/*
	for (;;) 
	{
		if (section.NotesInit() != ERR_OK) break;
		DNAbbreviate(0L,NULL,psInitServer,m_server,sizeof(m_server),&datasize);
		
		
		if (lotusDB.Open("users.nsf") != ERR_OK) break;
		
		if (note.Open("Nombre Corto","lester") != ERR_OK) break;
		//note.AttachFile("idfile","c:\\id\\pmelo.id");
		note.AttachmentAdd("c:\\id\\pmelo.id","userid1");
		note.Update();

	

		break;
	}
	*/
	return 0;
}


