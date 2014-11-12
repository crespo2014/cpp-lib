// db11c2.h: interface for the CCarta class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB11C2_H__4C018CD9_0E8B_11D4_BC42_0000E8DE4B3B__INCLUDED_)
#define AFX_DB11C2_H__4C018CD9_0E8B_11D4_BC42_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Usada para actaulizar los registros

class AFX_EXT_CLASS CCarta : public CObject  
{
public:
	int InitCarta();
	long	numero;
	char nombre[50];
	char apellido1[50];
	char apellido2[50];
	char	fechaent[20];
	char	fecharesp[20];
	long	municipio;
	char	sintesis[1024];
	long	sindicato;
	long	tsindicato;
	long	tprovincia;
	long	tdepartamento;
	long	respuesta;
	long	organismo;
	char	tema[10];
	CCarta();
	virtual ~CCarta();

};

#endif // !defined(AFX_DB11C2_H__4C018CD9_0E8B_11D4_BC42_0000E8DE4B3B__INCLUDED_)
