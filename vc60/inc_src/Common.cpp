#include "stdafx.h"
#include "common.h"


typedef struct
{
	char* str;
	DWORD val;
} FS_UNIT;

FS_UNIT Units[] = { "bytes",1,
					"KBytes",1024,
					"MBytes",1024*1024,
					"GBytes",1024*1024*1024,
					"GBytes",1024*1024*1024};

void* GetResource(char* lpName)
{
	HRSRC hrscr = ::FindResource(NULL/*GetModuleHandle(NULL)*/,lpName,"Resources");
	if (hrscr == NULL) return NULL;
	HGLOBAL hGlobal =::LoadResource(GetModuleHandle(NULL),hrscr);
	if (hGlobal == NULL) return NULL;
	return ::LockResource(hGlobal);
}

DWORD _stdcall ProcessInfResource(char* lpszResourceName,IinfProcess* lpInfProcess)
{
	void* lpvoid;
	lpvoid = GetResource(lpszResourceName);
	if (!lpvoid) return ERR_NORESOURCE;
	ProcessInfBuffer((char*)lpvoid,lpInfProcess);
	return ERR_NONE;
}

DWORD ProcessInfBuffer(char* buffer,IinfProcess* lpInfProcess)
{
#define ST_NONE			0
#define ST_SECTION		1
//#define ST_ENDSECTION	2
#define ST_VAR			3
#define ST_VAL			4
#define ST_ENDVAL		5
#define ST_IGNORE		6
	BYTE	car;
	char	name[20];
	char	val[255];
	WORD	nameIndex;
	WORD	valIndex;
	WORD	status;
	WORD	index;
	BOOL	onstr;
//	BOOL	onescape;
	onstr = false;
	nameIndex = 0;
	valIndex = 0;
	status = ST_NONE;
	index = 0;
	lpInfProcess->OnStart();
	for (;;)
	{
		car = buffer[index];
		index ++;
		if ((car == 0x0D)||(car == 0x00))
		{
			if (status == ST_VAL)
			{
				status = ST_ENDVAL;
				val[valIndex]=' ';
				From0x20To0x00(val,valIndex);
			}
			if (status == ST_ENDVAL) lpInfProcess->OnNewValue(name,val);
			status = ST_NONE;
			if (car == 0) break;
			continue;
		}
		if (car < ' ') continue;
		if (status == ST_NONE)
		{
			if (car == '[') 
			{
				status = ST_SECTION; 
				nameIndex = 0;
				continue;
			}
			if (car == ' ') continue;	// ignorar espacios al comienzo
			if (car == '.') break;		// fin por un punto
			name[0] = car;
			nameIndex = 1;
			status = ST_VAR;
			continue;
		}
		if (status == ST_VAR)
		{
			if (car == '=')
			{
				name[nameIndex]=' ';
				From0x20To0x00(name,nameIndex);
				onstr = false;
				status = ST_VAL;
				valIndex = 0;
				continue;
			}
			if ((car == ' ')&&(nameIndex == 0)) continue;
			name[nameIndex] = car;
			nameIndex ++;
			continue;
		}
		if (status == ST_SECTION)
		{
			if (car == ']')
			{
				status = ST_IGNORE;
				name[nameIndex]=' ';
				From0x20To0x00(name,nameIndex);
				lpInfProcess->OnNewSection(name);
				continue;
			}
			if ((car == ' ')&&(nameIndex == 0)) continue;
			name[nameIndex] = car;
			nameIndex ++;
			continue;
		}
		if (status == ST_VAL)
		{
			// Si la cadena posee espacios al comienzo o un ; poner " al principio
			if ((car == '"') && (valIndex == 0))
			{
				onstr = true;
				continue;
			}
			if (!onstr)
			{
				if (car == ';') 
				{
					status = ST_ENDVAL;
					val[valIndex]=' ';
					From0x20To0x00(val,valIndex);
				}
				if ((car == ' ')&&(valIndex == 0)) continue;

			}
			val[valIndex]=car;
			valIndex++;
			continue;
		}
	}
	lpInfProcess->OnFinish();
	return 0;
}

DWORD FileSizeToString(DWORD dwSize,char* str)
{
	BYTE i;
	i=0;
	for (i=0;i<4;i++)
	{
		if (dwSize < Units[i+1].val) break;
	}
	sprintf(str,"%.2f ",(float)dwSize/(float)Units[i].val);
	strcat(str,Units[i].str);
	return 0;
}




DWORD LoadIniFile(char* filename,IIniFile* lpIIniFile,void* lpParam)
{
	// Lectura desde un fichero
	char	var[20];
	BYTE	strpos;
	BOOL	OnStr;		// Se esta leyendo la variable y no el valor
	double	val;
	BYTE	valtmp1;	// Temporal

	char	inval;		// Valor de entrada
	char	buffer[100];
	DWORD	bytesread;
	DWORD	i;
	HANDLE m_hFile = CreateFile(filename,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (m_hFile == INVALID_HANDLE_VALUE) return 1;
	OnStr = true;
	strpos = 0;
	for (;;)
	{
		ReadFile(m_hFile,buffer,100,&bytesread,NULL);
		if (bytesread == 0) break;
		for (i=0;i<bytesread;i++)
		{
			inval = buffer[i];
			switch (inval)
			{
			case '=': 
				{
					val=0;
					var[strpos]=0;
					valtmp1 = 1;
					OnStr=false;
					break;
				}
			case ';': 
				{
					lpIIniFile->OnProcessParam(var,val,lpParam);
					OnStr = true;
					strpos = 0;
					break;
				}
			default:
				{
					if ((inval < 32) || (inval > 127)) break;
					if (OnStr)
					{
						var[strpos] = (char)towupper(inval);
						strpos++;
						break;
					}
					// procesar valor
					if (inval == '.')
					{
						valtmp1 = 10;
						break;
					}
					if (valtmp1 == 1)
						val = val*10+(inval-0x30);
					else
					{
						val = val+(float)(inval-0x30)/(float)valtmp1;
						valtmp1*=10;
					}
					break;
				}
			}
		}
	}
	return 0;
}

DWORD _stdcall From0x20To0x00(char *lpBuffer, DWORD dwIndex, BOOL bForward)
{
	while (lpBuffer[dwIndex] == 0x20)
	{
		lpBuffer[dwIndex] = 0x00;
		if (dwIndex == 0) break;
		dwIndex --;
	}
	return 0;
}

DWORD _stdcall GetIntValue(char* lpszStringVal,int* lpiVal)
{
	if ((lpszStringVal[1] == 'x') ||
		(lpszStringVal[1] == 'X'))
	{
		sscanf(&lpszStringVal[2],"%x",lpiVal);
	}
	else
		sscanf(lpszStringVal,"%d",lpiVal);

	return 0;
}