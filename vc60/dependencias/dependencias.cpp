// dependencias.cpp : Defines the entry point for the console application.
//

/*
	hay que incluir los ficheros de la sdk antes que ninguno porque si no da problemas

*/
#include "windows.h"

#include <winhttp.h>
#include <Mshtml.h>
#include <initguid.h>

#include "blockmem.h"
#include "bstr.h"
#include "configparser.h"
#include "tube.h"
#include "b64.h"
#include "crypter.h"
#include "bapp.h"

//#import <mshtml.idl>

/*
kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib 
advapi32.lib shell32.lib ole32.lib oleaut32.lib odbc32.lib
 odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib 
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib
 odbc32.lib odbccp32.lib winhttp.lib
*/

int main(int argc, char* argv[])
{
	CLogClient::get()->SetConsoleOutput(true);
	CLogClient::get()->SetLevel(9);
	CbApp	app;
	app.ParseCmdLine_c("-pwd \"sdlsmdskd mk mkmd \" ks ks -lkl ks dskds kjsk 'skajla' k 'ldoñk' ");

	/*
	char	*cptr;
	char	c;
	char	*texto = "abcdefghijklmnopq";

	cptr = texto;
	while ((c=*(cptr++)) != 0)
	{
		if (*cptr != 'b')
		{
		printf("%c",*cptr);
		}
	}
	
	cptr=texto;
	for (;(c=*(cptr++)) != 0;)
	{
		if (c =='b') continue;
		printf("%c",c);
	}

	while (*cptr)
	{
		c = *(cptr++);
		if (c != 'b')
		{
		printf("%c",c);
		}
	}

	cptr = texto;
	while ((c=*(cptr++)) != 0)
	{
		if (*cptr != 'b')
		{
		printf("%c",*cptr);
		}
	}
	*/

	/*
	char *pchar;
	DWORD size;
	void	*pdata;
	DWORD	pass;
	BOOL  br = FALSE;
	CBlockMem mem;

	char*	head1   = "\r\nContent-Type: application/x-www-form-urlencoded; charset=iso-8859-1\r\n";
	char*	head_es = "\r\nAccept-Language: es\r\n";
	char*	head_en = "\r\nAccept-Language: en\r\n";
	char*	head;
	char*	dt;
	DWORD	head_size;

	LPCWSTR		uhead;
	LPCWSTR		udata;
	LPCWSTR		agent= CbBSTR::toUnicode("Mozilla/4.0",&mem);
	LPCWSTR		lang = CbBSTR::toUnicode("es",&mem);
	LPCWSTR		server = CbBSTR::toUnicode("10.10.0.66",&mem);
	LPCWSTR		url = CbBSTR::toUnicode("idm/suite/basic-login.do",&mem);
	LPCWSTR		mtd = CbBSTR::toUnicode("POST",&mem);
	LPCWSTR		protocol = CbBSTR::toUnicode("HTTP/1.1",&mem);

	HINTERNET m_hOpen = WinHttpOpen(agent, WINHTTP_ACCESS_TYPE_NO_PROXY,WINHTTP_NO_PROXY_NAME, NULL, 0);

	HINTERNET hConn= WinHttpConnect( m_hOpen,server,8080,0);
	HINTERNET hPeticion = WinHttpOpenRequest( hConn,mtd,url, protocol ,NULL,NULL,0);

	// crear la cabecera
	mem.lock();
	mem.lockAdd(head1,CbObject::clen(head1));
	mem.lockAdd(head_es,CbObject::clen(head_es));
	mem.lockAdd("",1);
	mem.lockCompact((void**)&head,&head_size);
	mem.lockClose();						// la memoria no se libera pero da igual
	uhead = CbBSTR::toUnicode(head,&mem);

	// datos a enviar
	dt = "colChkbx_Tab1=rtve0";
	udata = CbBSTR::toUnicode(dt,&mem);

	br = WinHttpSendRequest( hPeticion,uhead,-1L,dt,CbObject::clen(dt),CbObject::clen(dt),0);

	if (br)
        br = WinHttpReceiveResponse( hPeticion, NULL);

	mem.lock();
	
	pass = 0;

	if (br)
	{
		//br = WinHttpQueryDataAvailable( hRequest, &pass);if (!br) break;	//ERROR
		for(;;)
		{
			mem.lockAvaliable(&pdata,&size);
			br = WinHttpReadData(hPeticion,pdata,size,&pass);if (!br) break;	//ERROR
			mem.lockCommit(pass);
			if (!pass) break;		//EOF
		}
	}
	if (!br)
	{
		int err = GetLastError();
	}

	mem.lockCompact(&pdata,&size);
	// Cargar el modelo DOM

	HRESULT hr;	

	//Creo un safearray
	SAFEARRAY* psa = SafeArrayCreateVector(VT_VARIANT, 0, 1);
	VARIANT *param;	
	
	hr =  SafeArrayAccessData(psa, (LPVOID*)&param);
	param->vt = VT_BSTR;
	param->bstrVal = SysAllocString((OLECHAR*)pdata);

	*/
	/*
	IHTMLDocument2 *pHTMLDoc;		
	
	hr = CoCreateInstance( CLSID_HTMLDocument, NULL, CLSCTX_INPROC_SERVER,IID_IHTMLDocument2, (void**)&pHTMLDoc);

	if (hr!=S_OK) return 0;
	pHTMLDoc->write(psa);
	pHTMLDoc->close();
	*/
	/*

	mem.lockFree();
	

		WinHttpCloseHandle(hConn);
	WinHttpCloseHandle(hPeticion);
	*/
	return 0;
}

