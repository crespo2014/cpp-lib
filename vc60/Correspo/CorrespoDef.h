// CorrespoDef.h: interface for the CCorrespoDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CORRESPODEF_H__9BCE08F4_7E97_4A6F_B0F3_0D5A4FBB5C7F__INCLUDED_)
#define AFX_CORRESPODEF_H__9BCE08F4_7E97_4A6F_B0F3_0D5A4FBB5C7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBCommon.h"

// Tablas del sistema
#define CARTAS_TINDEX		1
#define PROVINCIA_TINDEX	2
#define MUNICIPIO_TINDEX	3

// Provincia
struct _PROVINCIA
{
	DWORD	id;
	char	name[25];
	char	dbname[16];
	char	abrev[4];
	short	cod;
};

struct _MUNICIPIO
{
	DWORD	id;
	char	codigo[5];
	char	name[26];
	DWORD	provincia;
};


#define PROV_NAME_CINDEX	2
#define PROV_ABREV_CINDEX	10
#define PROV_DBNAME_CINDEX	11
#define PROV_CODIGO_CINDEX	12

#define PROVINCIA_DBCOUNT	5    // 4+ id column

extern _PROVINCIA	Provincia[];
extern DWORD		ProvinciaCount;
extern DBTABLEINFO	ProvinciaTableInfo;

#define MUN_NAME_CINDEX		2
#define MUN_CODIGO_CINDEX	3
#define MUN_PROVID_CINDEX	4

#define MUNICIPIO_DBCOUNT	4

extern _MUNICIPIO	Municipio[];
extern DWORD		MunicipioCount;
extern DBTABLEINFO	MunicipioTableInfo;


// Carta
#define SINTESIS1_CINDEX	2
#define SINTESIS2_CINDEX	3
#define SINTESIS3_CINDEX	4
#define SINTESIS4_CINDEX	5
#define SINTESIS5_CINDEX	6
#define EXPTE_CINDEX		7
#define NOMBRE_CINDEX		8
#define DIRECCION_CINDEX	9
#define TEMA_CINDEX			10
#define FECHAE_CINDEX		11
#define PROVINCIA_ID_CINDEX	12
#define RESPUESTA_CINDEX	13
#define SINTESIS_CINDEX		14
#define SINDICATO_CINDEX	15
#define MUNICIPIO_ID_CINDEX	16
#define CARTA_MUNI_CINDEX	17
#define CARTA_DBCOUNT	16

extern DBTABLEINFO	CartaTableInfo;

// Interfaz grafica
#define TEXTTOPMARGIN	1
#define TEXTRIGHTMARGIN 1
#define TEXTLEFTMARGIN	3


#endif // !defined(AFX_CORRESPODEF_H__9BCE08F4_7E97_4A6F_B0F3_0D5A4FBB5C7F__INCLUDED_)
