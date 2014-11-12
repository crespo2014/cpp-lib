// g_01c07.cpp: implementation of the C3DEscene class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "g_01c07.h"
#include "g_01c08.h"
#include "g_01c09.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ERR_FIRST			0
#define ERR_NORESOURCE		ERR_FIRST+1
#define ERR_NOHGLOBAL		ERR_FIRST+2
#define ERR_NOLPPOINTER		ERR_FIRST+2
#define ERR_INVALID_FILE	ERR_FIRST+3

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DEscene::C3DEscene()
{
	Initialize();
}

C3DEscene::~C3DEscene()
{
	Destroy();
}

DWORD C3DEscene::Initialize()
{
	m_lpdata=&m_data;
	m_first_mesh=NULL;
	m_onresource=false;
	m_first_material=NULL;
	return 0;
}

DWORD C3DEscene::Destroy()
{
	delete [] m_first_material;
	delete [] m_first_mesh;
	return 0;
}


DWORD C3DEscene::ReadFromResource(char *lpName,char* lpType)
{
	DWORD*	lpSize;		// Usado para conocer el tamano de las estructuras
	void*	lpPointer;	// Ubicacion en memoria del recurso
	BYTE*	lppos;		// Usado para recorrer la memoria
	DWORD	i;			// Cantidad de elementos

	HRSRC	m_hrsrc=	::FindResource(NULL,lpName,lpType);
	if (!m_hrsrc)
		return ERR_NORESOURCE;
	HGLOBAL m_hglobal=	::LoadResource(NULL,m_hrsrc);
	if (!m_hglobal)
		return ERR_NOHGLOBAL;
	
	lpPointer=LockResource(m_hglobal);
	if (!lpPointer)
		return ERR_NOLPPOINTER;

	lppos=(BYTE*)lpPointer;
	lpSize=(DWORD*)lpPointer;
	// Recoger toda la informacion del recurso
	m_lpdata = (S_3DESCENE*)lppos;
	lppos+=*lpSize;
	// Comprobar la validez del recurso
	// aunque esto puede ignorarse para asi lograr compatibilidad
	// entre versiones
	if (m_lpdata->m_version != sizeof (m_data))
		return ERR_INVALID_FILE;
	// Crear todas las clases
	m_first_mesh =	new C3DMesh[m_lpdata->m_mesh_cant];
	m_first_material = new C3DMaterial[m_lpdata->m_mat_cant];
	
	// Recoger toda la informacion de las variables
	for (i=0;i<m_lpdata->m_var_cant;i++)
	{
		lpSize=(DWORD*)lppos;
		lppos+=*lpSize;				//proxima variable
	}
	// Recoger toda la informacion de los materiales
	for (i=0;i<m_lpdata->m_mat_cant;i++)
	{
		lpSize=(DWORD*)lppos;
		m_first_material[i].ReadFromMemory(lppos);
		lppos+=*lpSize;	
	}
	// Recoger toda la informacion de las mallas
	for (i=0;i<m_lpdata->m_mesh_cant;i++)
	{
		lpSize=(DWORD*)lppos;
		m_first_mesh[i].Set3DEscene(this);
		m_first_mesh[i].ReadFromMemory(lppos);
		lppos+=*lpSize;	
	}
	return 0;
}

C3DMaterial* C3DEscene::GetMaterial(DWORD pindex)
{
	if (pindex > m_lpdata->m_mat_cant)
		return NULL;
	return &m_first_material[pindex];
}

C3DMesh* C3DEscene::Get3DMesh(DWORD pindex)
{
	if (pindex > m_lpdata->m_mesh_cant)
		return NULL;
	return &m_first_mesh[pindex];
}

C3DMesh* C3DEscene::Get3DMesh(char *pname)
{
	DWORD i;
	for (i=0;i<m_lpdata->m_mesh_cant;i++)
	{
		if (!strcmp(m_first_mesh[i].m_lpdata->m_name,pname))
				return &m_first_mesh[i];
	}
	return NULL;
}
