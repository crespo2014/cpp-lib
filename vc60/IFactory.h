// IFactory.h: interface for the IFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IFACTORY_H__ACC3FE71_62C0_4B91_A2AC_EB92B367D061__INCLUDED_)
#define AFX_IFACTORY_H__ACC3FE71_62C0_4B91_A2AC_EB92B367D061__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IFactory  
{
public:
	virtual DWORD Free(void* pObject);
	virtual void* New();
};

#endif // !defined(AFX_IFACTORY_H__ACC3FE71_62C0_4B91_A2AC_EB92B367D061__INCLUDED_)

// ideas

// para destruir un objeto basta con volver a construirlo
// esta interfaz permite delegar la responsabilida en la clase fatory para liberar el objeto
//
/*
	CLotusDB	*pldb = new CLotusDB();
	CLotusDB db;

	char	ldb[sizeof(CLotusDB)];
	memset(ldb,0,sizeof(ldb));
	pldb = (CLotusDB*)ldb;
	
	CLotusDB::CLotusDB(*pldb);
	usar un classfacory con un array en memoria virtual
	hay que definir una estructura 

  donde un miembro inidca si la clase a sido liberada o no ( contruida destriuda)
  se puede indicar ademas el siguiente objeto de la lista de objetos.


*/