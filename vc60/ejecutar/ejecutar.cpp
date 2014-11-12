// ejecutar.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "stdio.h"
#include "logclient.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	DWORD	dr;
	STARTUPINFO			si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags  =STARTF_USESTDHANDLES;
	si.hStdInput=NULL;
	si.hStdOutput=NULL;
	si.hStdError=NULL;
	ZeroMemory( &pi, sizeof(pi));

	char	*patch = "C:\\Archivos de programa\\BMC Software\\EssClient";
	char	cmd_line[MAX_PATH];
		
	sprintf(cmd_line,"\"C:\\Archivos de programa\\BMC Software\\EssClient\\essclient.exe\" %s ",lpCmdLine);
	glog.CreateLogFile("c:\\ejecutar.log");
	
	dr = CreateProcess(NULL,cmd_line,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,patch,&si,&pi);
	if (dr) glog._log(LOG_ERROR,"ejecutando %s",cmd_line);
		else
		{
			glog.log_strings(LOG_ERROR,"ActualizarID -> Failed.. to Launch ActualizarID");
			glog.AddWin32ErrorMsg(GetLastError());
		}
	
	return 0;
}



