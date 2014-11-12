// db11c1.h: interface for the CCartasDatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DB11C1_H__244C9632_EFBE_11D3_BC40_0000E8DE4B3B__INCLUDED_)
#define AFX_DB11C1_H__244C9632_EFBE_11D3_BC40_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "db11s.h"
#include "db11c2.h"

typedef struct
{
	CDaoWorkspace	daoworkspace;
	CDaoDatabase*	daodatabase;
	CDaoRecordset*	Explorer;
	CDaoRecordset*	cartas;
	S_RECORDINFO	municipios;
	S_RECORDINFO	provincias;
	S_RECORDINFO	sindicatos;
	S_RECORDINFO	departamentos;
	S_RECORDINFO	temas;
	S_RECORDINFO	clasificaciones;
	S_RECORDINFO	organismos;
	BOOL			OnOpen;
	BOOL			OnNew;			// Se esta creando una nueva carta
}S_CARTASDATABASE;

class AFX_EXT_CLASS CCartasDatabase : public CObject  
{
public:
	int First(CCarta* carta);
	int Prev(CCarta* carta);
	int Next(CCarta* carta);
	int LeerOrganismos();
	int Close();
	S_RECORDINFO* GetTable(char* table);
	int New(CCarta* pcarta);
	int Save(CCarta* pcarta);
	int UpDate(CCarta* carta);
	int Buscar();
	int LeerDepartamentos();
	int LeerSindicatos();
	int LeerMunicipios();
	int LeerCampo(S_RECORDINFO* recordinfo,char* tabla);
	int LeerProvincias();
	int OpenDatabase();
	int InitCartasDatabase();
	S_CARTASDATABASE* m_CartasDatabase;
	CCartasDatabase();
	virtual ~CCartasDatabase();

};

#endif // !defined(AFX_DB11C1_H__244C9632_EFBE_11D3_BC40_0000E8DE4B3B__INCLUDED_)
