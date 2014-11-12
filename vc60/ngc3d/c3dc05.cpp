// c3dc05.cpp: implementation of the CDXMesh class.
//
//////////////////////////////////////////////////////////////////////

#include "c3dc05.h"
#include "c3dc03.h"   // CDXEscene

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDXMesh::CDXMesh()
{
	m_lpdata=&m_data;
	m_lpdxescene=NULL;
	m_lpdata->facescant=0;
	m_lpdata->id=0;
	m_lpdata->matcant=0;
	m_lpdata->name[0]=0;
	m_lpdata->vertexcant=0;
}

CDXMesh::~CDXMesh()
{

}

DWORD CDXMesh::SetEscene(CDXEscene *lpdxescene)
{
	m_lpdxescene=lpdxescene;
	return 0;
}

CDXEscene* CDXMesh::GetEscene()
{
	return m_lpdxescene;
}

DWORD CDXMesh::Initialize()
{
	return 0;
}

DWORD CDXMesh::Release()
{
	return 0;
}

DWORD CDXMesh::Paint()
{
	if (!m_lpdxescene)
		goto failed;
	if (!m_lpdxescene->m_lpd3ddevice)
		goto failed;
	/*
	m_lpdxescene->m_lpd3ddevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		m_lpdata->m_vertextype,
		m_lpvertex,
		m_lpdata->vertexcant,
		m_
		*/
	return 0;
failed:
	return 0;
}

DWORD CDXMesh::ReadFromStaticMemory(void *lpvoid)
{
	return 0;
}
