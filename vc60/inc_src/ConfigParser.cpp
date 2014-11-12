// ConfigParser.cpp: implementation of the CConfigParser class.
//
//////////////////////////////////////////////////////////////////////

#include "ConfigParser.h"

#define _FILENAME_ "configparser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define TYPE_SECTION	1
#define TYPE_PARAM		2
#define TYPE_VAL		3

CConfigParser::CConfigParser(IConfig *pConf, IMem* pMem)
{
	mpMem = pMem;
	mpConfig = pConf;
}

CConfigParser::~CConfigParser()
{
	
}

DWORD	CConfigParser::Start()
{
	mStatus = 0;
	return ERR_OK;
}

DWORD	CConfigParser::End()
{
	Push(0x0d);
	return ERR_OK;
}

DWORD	CConfigParser::Push(BYTE b)
{
	mlastChar = b;
	if ((b == 0x0d) || (b == 0x0a))		// Se ha llegado al fin de linea hay que procesar el estado actual y reiniciar status
	{
		switch (mStatus)
		{
		case 1:
			if (endData(TYPE_SECTION) != ERR_OK) return _LOG_AT;
			_LOG_WARNING "Unexpected end of section ] is missing");
			break;
		case 2:
			if (endData(TYPE_PARAM) != ERR_OK) return _LOG_AT;
			_LOG_WARNING "Unexpected end of param value is missing");			
			break;
		case 4:
			_LOG_WARNING "Unexpected end of line in value");			
			break;
		case 5:
			if (endData(TYPE_VAL) != ERR_OK) return _LOG_AT;
			break;			
		}
		mStatus = 0;
	}
	else switch (mStatus)
	{
		case 0:	// esperando un alfanumerico para iniciar seccion o parametro
			if (b > ' ')
			{
				if (b == '[') 
				{
					mStatus = 1;		// leyendo nombre de seccion
					if (mpMem->lock()	!= ERR_OK) return _LOG_AT;
				}else if ((b == '#') || (b == ';'))
				{
					// debe ser un comentario todo caracter que no se alfanumerico
					mStatus = 3;		// linea de comentario
				}
				else
				{
					mStatus = 2;		// nombre de parametro recibiendo
					if (mpMem->lock()			!= ERR_OK) return _LOG_AT;
					if (mpMem->lockAdd(&b,1)	!= ERR_OK) return _LOG_AT;
				}
			}
			break;
		case 1:		// leyendo nombre de seccion
			if (b == ']') 
			{
				if (endData(TYPE_SECTION) != ERR_OK) return _LOG_AT;
			}
			else if (b < ' ')
			{
				// caracter no permitido en el nombre de seccion
				_LOG_WARNING "Unexpected character 0x%02X in section name",b);
			}
			else
			{
				if ( mpMem->lockAdd(&b,1) != ERR_OK) return _LOG_AT;
			}
			break;
		case 2:		//leyendo nombre del parametro	
			if ((b <= ' ') || (b == '='))
			{
				if (endData(TYPE_PARAM)  != ERR_OK) return _LOG_AT;
			}
			else 
			{
				if ( mpMem->lockAdd(&b,1) != ERR_OK) return _LOG_AT;
			}
			break;
		case 6:		// se acabo el parametro pero no se recivio el =
			if (b == '=')
			{
				mStatus = 4;
			}
			break;
		case 3:		// linea de comentario
			break;
		case 4:			// esperando inicio de valor
			if (b > ' ')
			{
				mStatus = 5;		// leyendo valor
				if (mpMem->lock() != ERR_OK) return _LOG_AT;
				if (b != '\"')		// el " se utiliza solo para permitir empezar con espacios el valor
					if ( mpMem->lockAdd(&b,1) != ERR_OK) return _LOG_AT;
			}
			break;
		case 5:		// leyendo valor
			if ( mpMem->lockAdd(&b,1) != ERR_OK) return _LOG_AT;
			break;
		default:
			return _LOG_ERROR ERR_FATAL,"Invalid machine status");
			break;
			
	}
	return ERR_OK;
}

DWORD CConfigParser::endData(WORD type)
{
	char	*cstr;
	DWORD	size;
	bool	release = true;
	if (mpMem->lockAdd("",1)					!= ERR_OK) return _LOG_AT;
	if (mpMem->lockCompact((void**)&cstr,&size) != ERR_OK) return _LOG_AT;

	if (type == TYPE_SECTION)
	{
		if (size == 1)   
			_LOG_WARNING "Section name is blank");
		else 
			if (mpConfig->OnSection(cstr,&release)	!= ERR_OK) return _LOG_AT;
		mStatus = 0;

	}
	else if (type == TYPE_PARAM)
	{
		if (size == 1) 
			_LOG_WARNING "Param name is blank");
		else
			if (mpConfig->OnParam(cstr,&release)	!= ERR_OK) return _LOG_AT;
		if (mlastChar != '=')
			mStatus = 6;
		else
			mStatus = 4;

	}
	else if (type == TYPE_VAL)
	{
		if (size == 1) 	
			_LOG_WARNING "Value is blank");
		else
			if (mpConfig->OnValue(cstr,&release) != ERR_OK) return _LOG_AT;
		mStatus = 0;

	}
	if (release)
	{
		if (mpMem->lockFree()	!= ERR_OK) return _LOG_AT;
	}
	else
	{
		if (mpMem->lockClose()	!= ERR_OK) return _LOG_AT;
	}
	return ERR_OK;
}
