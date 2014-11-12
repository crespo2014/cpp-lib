// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"
#include "logclient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define MAXLINE	255
/*
CIniFile::CIniFile()
{

}

CIniFile::~CIniFile()
{
	Release();
}
*/
/*
	quitar espacios el comienzo
	si empieza con [ es una seccion sino es una keyword
	despues del = quitar espacios y hasta que no se encuentre 10 o 13 cojer todo
	no admitir carateres por debajo de 32
*/
/*
DWORD CIniFile::ReadFromFile(char *filepath)
{
	DWORD	dwr;
	BOOL	br;
	HANDLE	hfile;
	DWORD	filesize;
	DWORD	bytesread;
	char	strend;		// caracter de termiancion del valor
	char*	cptr;		// posicion que se esta tratando
	char*	section;	// seccion que se esta tratando
	WORD	type;		// tipo de dato 0 - seccion 1 - key 0 - valor
	WORD	keypos;		// key que se esta adicionando
	
	m_keys.count = 0;
	keypos	= 0;

	do
	{
		// open file + get size + reserve memory
		hfile = CreateFile(filepath,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		filesize = GetFileSize(hfile,NULL);
		if (filesize == INVALID_FILE_SIZE) break;
		m_keys.data = (char*)VirtualAlloc(NULL,filesize+1,MEM_COMMIT,PAGE_READWRITE);
		br = ReadFile(hfile,m_keys.data,filesize,&bytesread,NULL);
		CloseHandle(hfile);

		m_keys.data[bytesread] = 0;

		// se espera inicio de seccio
		section	= NULL;					// Inicialmente no hay seccion
		cptr = m_keys.data;

		for (;cptr[0] != 0;)
		{
			for (;(cptr[0] <= ' ')&&(cptr[0] != 0);cptr++);	// ignorar los espacios y los fines de linea
			if (cptr[0] == 0) break;		// se termino el fichero
			if (cptr[0] == ';')
			{
				for (;cptr[0] > ' ';cptr++);
				continue;
			}
			if (cptr[0] == '[')
			{
				// seccion procesarla la seccion termina con un ]
				cptr++;
				section = cptr;
				for (;(cptr[0] > ' ')&&(cptr[0] != ']');cptr++);		// pasar por alto los caracteres validos
				if (cptr[0] == 0) break;	// Se termino el fichero
				cptr[0] = 0;
				_strupr(section);
				continue;
			}
			// key + values
			strend = 0;
			m_keys.keys[keypos].section = section;
			m_keys.keys[keypos].name = cptr;
			m_keys.keys[keypos].value = NULL;
			for (;(cptr[0] > ' ')&&(cptr[0] != '=');cptr++);	// recorrer caracteres validos
			if (cptr[0] == 0) break;		// fin
			if (cptr[0] == '=')
			{
				cptr[0] = 0;
				_strupr(m_keys.keys[keypos].name);
				// leer valor
				for (;cptr[0] == ' ';cptr++);
				if (cptr[0] == '\"') {strend = '\"';cptr++;}
				
				m_keys.keys[keypos].value = cptr;
				for (;(cptr[0] >= ' ');cptr++);	// recorrer caracteres validos
				if (cptr[0] == 0) break;		// fin
				cptr[0] = 0;
				cptr++;
			}
			keypos++;
			if (keypos >= MAXINIKEYS) break;
		}
		m_keys.count = keypos;
	}while(false);

	/*
	// procesamiento de caracteres
	for(;;)
	{
		kptr[0] = 0;	//nueva key es cero
		
		
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
	
	return ERR_OK;
}
*/

DWORD CIniFile::SaveToFile(char *filepath)
{
	return ERR_OK;
}

DWORD CIniFile::GetKeyValue(char* section,char *key, char **value)
{
	return ERR_OK;
}

DWORD CIniFile::Release()
{
	return ERR_OK;
}
