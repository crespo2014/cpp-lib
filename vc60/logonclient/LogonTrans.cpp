// LogonTrans.cpp: implementation of the CLogonTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogonTrans.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogonTrans::CLogonTrans()
{

}

CLogonTrans::~CLogonTrans()
{

}

DWORD CLogonTrans::OpenFile(char *sFilePath)
{
	DWORD dwr;
	m_hFile = CreateFile(sFilePath,
						GENERIC_WRITE|GENERIC_READ,
						FILE_SHARE_WRITE,				// Solo se puede abrir en modo escritura
						NULL,							// Seguridad nula
						OPEN_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,NULL);
	dwr = GetLastError();
	//if (m_hFile == INVALID_HANDLE_VALUE) 
	return 0;
}

// extraer de una lista lineal separadas por 0 las keyword y valores 
DWORD CLogonTrans::ExtracKeywords(char *keys, KEYWORD *keyword, WORD *maxkeys)
{
	char*	cptr;
	WORD	count;
	count = 0;
	cptr = keys;
	while (cptr[0] != 0)
	{
		keyword[count].name = cptr;
		while (cptr[0] != 0) cptr++;	//buscar el valor
		cptr++;
		keyword[count].value = cptr;
		while (cptr[0] != 0) cptr++;	//ir al final del valor
		cptr++;
		count++;
	}
	*maxkeys = count;
	return 0;
}

// Convertir las keyword en una lista lineal separado por 0
//DEL DWORD CLogonTrans::MakeBuffer(KEYWORD *keyword, WORD maxkeys, char *keys)
//DEL {
//DEL 	char*	cptr;
//DEL 	WORD	count;
//DEL 
//DEL 	count = 0;
//DEL 	cptr = keys;
//DEL 	while (count < maxkeys)
//DEL 	{
//DEL 		strcpy(cptr,keyword[count].name);
//DEL 		while (cptr[0] != 0) cptr++;
//DEL 		cptr++;
//DEL 		strcpy(cptr,keyword[count].value);
//DEL 		while (cptr[0] != 0) cptr++;
//DEL 		cptr++;
//DEL 	}
//DEL 	cptr[0] = 0;	//fin de las keys
//DEL 	return 0;
//DEL }

/*
	de un argumento con los keyword crear un buffer lineal

	-KEYWORD "value" -KEYWORD value
	se quitan los espacios al comienzo del valor a menos que se especifique "
	la cadena termina con espacio a menos que haya empezado con "
*/

DWORD CLogonTrans::MakeBuffer(char *cmdstr, char *keys,DWORD* psize)
{
	char*	cptr;
	char*	kptr;
	char*	tptr;
	char	strend;		//delimitador de string
	cptr = cmdstr;
	kptr = keys;
	
	for(;;)
	{
		kptr[0] = 0;	//nueva key es cero
		// recorrer espacios hasta -
		for (;cptr[0] == ' ';cptr++);
		
		if (cptr[0] == 0) break;
		if (cptr[0] != '-') break;	// solo se admite esto
		cptr++;
	
		// copiar nombre del key
		tptr = kptr;						// para convertir a mayusculas
		for (;;cptr++,kptr++)
		{
			if (cptr[0] == 0) break;
			if (cptr[0] == ' ')	break;
			kptr[0] = cptr[0];
		}
		kptr[0] = 0;
		kptr++;
		_strupr(tptr);

		// valor
		strend = ' ';
		for (;cptr[0] == ' ';cptr++);	
		
		if (cptr[0] == '-')  {cptr--;break;}			// falta el valor de la variable
		if (cptr[0] == '\"') {strend = '\"';cptr++;}
		if (cptr[0] == 0)	 {cptr--;break;}			//fin key sin valor
		
		BOOL	bflag;
		bflag = false;
		for (;;cptr++,kptr++)
		{
			kptr[0] = cptr[0];		// tomar char sea cual sea
			if (cptr[0] == '\"')
			{
				if (cptr[1] == '\"') {cptr++;continue;}
			}
			if (cptr[0] == strend) break;
			if (cptr[0] == 0) {cptr--;break;}
		}
		kptr[0] = 0;	// fin de la variable
		kptr++;
		cptr++;
	}
	// calculo del tamaño del buffer
	*psize = kptr - keys;
	return 0;
}

/*
	Adiciona una key a un cmd y coloca el puntero despues del 0
	si el valor comienza con espacios incorpora al comienzo "
*/

DWORD CLogonTrans::AddToBuffer(char **sptr, char *key, char *value)
{
	char*	pcmd;
	char*	kptr;
	WORD	count;
	char	strend;

	strend = ' ';
	pcmd = *sptr;
	count = 0;

	pcmd[0] = 0;
	if (key[0] == 0) return 0;

	pcmd[0] = '-';
	pcmd++;
	kptr = key;
	for (;kptr[0] != 0;pcmd++,kptr++) pcmd[0] = kptr[0];
	pcmd[0] = ' ';
	pcmd++;
	if (value[0] == ' ') {pcmd[0] = '\"';pcmd++;strend = '\"';}

	for (;value[0] != 0;pcmd++,value++) 
	{
		pcmd[0] = value[0];
		if (value[0] == '\"') {pcmd++;pcmd[0]='\"';}
	}
	pcmd[0] = strend;
	pcmd[1] = 0;
	pcmd++;
	*sptr = pcmd;
	return 0;
}

DWORD CLogonTrans::SetTransactionFile(char *sFilepath)
{
	m_filepath[0] = 0;
	strncat(m_filepath,sFilepath,sizeof(m_filepath)-1);
	return 0;
}

DWORD CLogonTrans::AddTransationToFile(FILEPACK *filepack)
{
	DWORD dwr;
	long dwhigh = 0;
	// Utilizar un mutex para escribir al final del fichero
	// Bloquear el comienzo del fichero
	//LockFileEx(m_hFile,LOCKFILE_EXCLUSIVE_LOCK,0,0,4,0,NULL);
	// ir al final del fichero
	dwr = SetFilePointer(m_hFile,0,NULL,FILE_END);
	if (dwr == -1) return 1;
	
	//if (dwr != 0) return 1;

	DWORD	byteswritten;
	if (!WriteFile(m_hFile,filepack,filepack->size+sizeof(filepack->size),&byteswritten,NULL))
	{
		// esto es grave
		return 1;
	}
	if (byteswritten != filepack->size+sizeof(filepack->size))
	{
		// esto es peor
		return 1;
	}
	return 0;
}

/*
	Procesa una linea de comando 
	abre el fichero de transaciones y adiciona la transacion
*/
DWORD CLogonTrans::ProcessCmd(char *scmd)
{
	DWORD	dwr;
	DWORD	size;
	do
	{
		dwr = OpenFile("c:\\trans.dat");
		if (dwr != 0) break;
		dwr = MakeBuffer(scmd,m_filepack.m_keys,&size);
		if (dwr != 0) break;
		m_filepack.status = 0;
		m_filepack.size = size + sizeof(m_filepack.status);	
		dwr = AddTransationToFile(&m_filepack);
		if (dwr != 0) break;
	} while (false);
	return dwr;

}
