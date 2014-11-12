// db11c2.cpp: implementation of the CCarta class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "db11c2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCarta::CCarta()
{
	InitCarta();
}

CCarta::~CCarta()
{

}

int CCarta::InitCarta()
{
	apellido1[0]=0;
	apellido2[0]=0;
	fechaent[0]=0;
	fecharesp[0]=0;
	municipio=0;
	nombre[0]=0;
	numero=0;
	respuesta=0;
	sindicato=0;
	sintesis[0]=0;
	tdepartamento=0;
	tema[0]=0;
	tprovincia=0;
	tsindicato=0;
	organismo=0;
	return true;
}
