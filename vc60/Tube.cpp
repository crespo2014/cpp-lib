// Tube.cpp: implementation of the CTube class.
//
//////////////////////////////////////////////////////////////////////

#include "Tube.h"

#define _FILENAME_ "tube.c"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DWORD CTube::ReadFile(char *pcFileName, ITube *pITube)
{
	DWORD	dwr = 0;
	BYTE	*pb;
	BYTE	cache[100];
	int		count;
	FILE*	file;
	file = fopen(pcFileName,"r");
	if (file == NULL) return _LOG_ERROR ERR_NOT_FOUND,"Failed to open file %s",pcFileName);

	pITube->Start();
	while((count = fread(cache,1,sizeof(cache),file)) != 0)
	{
		pb = cache;
		while (count--)
		{
			dwr = pITube->Push(*(pb++)); if (dwr != ERR_OK) { _LOG_AT; break; }
		}
		if (dwr != ERR_OK) break;
	}
	pITube->End();
	fclose(file);
	return dwr;

}

DWORD CTube::ReadResource(char *res_type, char *res_name, HMODULE hModule, ITube *pITube)
{
	HRSRC	hres;
	HGLOBAL	hglobal;
	DWORD	res_size;
	BYTE	*pb;
	DWORD	dwr;

	hres = FindResourceA(hModule,res_name,res_type);
	if (hres == NULL) 
	{
		return _LOG_W32ERROR GetLastError(),ERR_API,"FindResource type,name (%s,%s) failed",res_type,res_name);
	}
	hglobal = LoadResource(hModule,hres);
	if (hglobal == NULL) 
	{
		return _LOG_W32ERROR GetLastError(),ERR_API,"LoadResource ");
	}
	pb = (BYTE*)LockResource(hglobal);
	res_size = SizeofResource(hModule,hres);

	pITube->Start();
	while(res_size--)
	{
		dwr = pITube->Push(*(pb++)); if (dwr != ERR_OK) { _LOG_AT; break; }
	}
	pITube->End();
	return ERR_OK;
}

DWORD CTube::Push_cs(char *cs, ITube *pTube)
{
	DWORD	dwr;
	dwr = pTube->Start();	if (dwr != ERR_OK) return dwr;
	while (*cs)
	{
		dwr = pTube->Push(*cs); if (dwr != ERR_OK) return dwr;
		cs++;
	}
	return pTube->End();
}
