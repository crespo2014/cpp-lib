// gC02.cpp: implementation of the C3DObject class.
//
//////////////////////////////////////////////////////////////////////

#include "gC02.h"
//#include "..\gl10\gl10c3.h"
#include "gc06.h"
#include "gc08.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DObject::C3DObject()
{
	initialize();
}

C3DObject::~C3DObject()
{

}

DWORD C3DObject::initialize()
{
	m_currentx=0;
	m_currenty=0;
	m_currentz=0;
	m_active=false;
	m_delete=false;
	m_lp3dmesh=NULL;
	m_next=NULL;
	m_prev=NULL;
	m_speed=0;
	m_starttime=0;
	m_startx=0;
	m_starty=0;
	m_startz=0;
	return 0;
}

/*
	Si Fly devuelve false es porque el objeto debe ser removido de la lista
	El tiepo esta dado en ms
*/
DWORD C3DObject::Fly(DWORD pTime)
{
	return 0;
}

DWORD C3DObject::Paint()
{
	if (m_lp3dmesh)
		m_lp3dmesh->Paint();
	return 0;
}

/*
	Devuelve el proximo objeto en la lista de objetos
	aqui es cuando se destruye el objeto si debe destruirse
*/
C3DObject* C3DObject::GetNext()
{
	return m_next;
}

DWORD C3DObject::SetNext(C3DObject *pnext)
{
	m_next=pnext;
	return 0;
}

DWORD C3DObject::SetPrev(C3DObject *pprev)
{
	m_prev=pprev;
	return 0;
}

DWORD C3DObject::Set3DMesh(C3DMesh *lp3dmesh)
{
	m_lp3dmesh=lp3dmesh;
	return 0;
}
