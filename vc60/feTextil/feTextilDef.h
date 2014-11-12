// feTextilDef.h: interface for the feTextilDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FETEXTILDEF_H__3BE5A351_4BCB_44A0_89F1_4651C5A3E9CC__INCLUDED_)
#define AFX_FETEXTILDEF_H__3BE5A351_4BCB_44A0_89F1_4651C5A3E9CC__INCLUDED_

#include "DBCommon.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/* 
	Aqui van todas las definiciones de la base de datos
	tablas utilizadas, los campos de las tablas
	se definen como externas todas las estructuras con esta informacion
*/

// Tablas de la base de datos
#define CLIENTES_TINDEX	1

#define CLIENTE_ID_CINDEX			1
#define CLIENTE_EMPRESA_CINDEX		2	// CATALOGO
#define CLIENTE_CARGO_CINDEX		3
#define CLIENTE_DIRECCION_CINDEX	4
#define CLIENTE_TELEFONO_CINDEX		5
#define CLIENTE_FAX_CINDEX			6
#define CLIENTE_EMAIL_CINDEX		7
#define CLIENTE_BANCOUSD_CINDEX		8
#define CLIENTE_BANCOMN_CINDEX		10
#define CLIENTE_CUENTAUSD_CINDEX	9
#define CLIENTE_CUENTAMN_CINDEX		11
#define CLIENTE_OBSERVACION_CINDEX	12
#define CLIENTE_NOMBRE_CINDEX		13
#define CLIENTE_DBCOUNT				13	// cantidad de datos del cliente

extern DBTABLEINFO	ClientesTI;		// estructura con los datos de los campos

#endif // !defined(AFX_FETEXTILDEF_H__3BE5A351_4BCB_44A0_89F1_4651C5A3E9CC__INCLUDED_)
