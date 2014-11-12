// cmdLineParser.cpp: implementation of the CcmdLineParser class.
//
//////////////////////////////////////////////////////////////////////

#include "cmdLineParser.h"

#define _FILENAME_	"cmdLineParser.c"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define ST_NONE		0	// leyendo espacios en blanco que son ignorados
#define ST_NO_COUTE	1	// se esta leyendo un valor que finalizara cuando se reciva un espacio
#define ST_COUTE	2	// leyendo valor que esta entrecomillado
#define ST_SCOUTE	3	// leyendo valor que esta entrecomillado simple

CcmdLineParser::CcmdLineParser(ICmdLineEvent* plistener,IMem* pMem)
{
	mListener = plistener;
	mpMem = pMem;
}

CcmdLineParser::~CcmdLineParser()
{

}

DWORD	CcmdLineParser::Start()
{
	mStatus = ST_NONE;
	return mListener->OnStart();
}

DWORD	CcmdLineParser::End()
{
	DWORD	dwr;
	if (mStatus == ST_NO_COUTE)
	{
		// simulamos un cierre normal con
		//dwr = Push(' '); if (dwr != ERR_OK) return _LOG_EXIT(dwr);
		dwr = endValue(); if (dwr != ERR_OK) return _LOG_EXIT(dwr);
	}
	else if (mStatus != ST_NONE)
	{
		// hay que cerrar el valor aunque sea de forma abrupta
		dwr = endValue(); if (dwr != ERR_OK) return _LOG_EXIT(dwr);
	}
	dwr = mListener->OnEnd();
	return dwr;
}

DWORD	CcmdLineParser::Push(BYTE b)
{
	switch (mStatus)
	{
	case ST_NONE:
		{
			if (b == ' ')	return ERR_OK;
			else if (b == '\"')  mStatus = ST_COUTE;
			else if (b == '\'') mStatus = ST_SCOUTE;
			else
				mStatus = ST_NO_COUTE;
			// hay que empezar el lock porque hemos empezado un estado
			if (mpMem->lock()			!= ERR_OK) return _LOG_AT;		
			// el valor no se almacena porque es una marca de inicio 
			if (mStatus != ST_NO_COUTE)	return ERR_OK;					
			break;
		}
	case ST_NO_COUTE:
		{
			if (b == ' ')	return endValue();
			break;
		}
	case ST_COUTE:
		{
			if (b == '\"')	return endValue();
		}
	case ST_SCOUTE:
		{
			if (b == '\'')	return endValue();
		}

	}
	// se puede validar el caracter 

	// hay que almacenar el valor recibido si no ha sido procesado por ningun estado
	if (mpMem->lockAdd(&b,1) != ERR_OK) return _LOG_AT;	// se almacena el espacio porque es parte del valor
	return ERR_OK;
}

DWORD CcmdLineParser::endValue()
{
	DWORD	dwr;
	char	*cstr;
	DWORD	size;
	BOOL	release = true;
	dwr = mpMem->lockAdd("",1);						if (dwr != ERR_OK) return _LOG_EXIT(dwr);
	dwr = mpMem->lockCompact((void**)&cstr,&size);	if (dwr != ERR_OK) return _LOG_EXIT(dwr);
	if (size != 1) 
	{
		dwr = mListener->OnValue_c(cstr,&release);	if (dwr != ERR_OK) return _LOG_EXIT(dwr);
	}
	if (release)
	{
		dwr = mpMem->lockFree();	if (dwr != ERR_OK) return _LOG_EXIT(dwr);
	}
	else
	{
		dwr = mpMem->lockClose();	if (dwr != ERR_OK) return _LOG_EXIT(dwr);
	}
	mStatus = ST_NONE;
	return ERR_OK;

}
