// g30c04.h: interface for the CDXMesh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G30C04_H__3A4EC7E3_14C2_11D5_BCB7_00D0093D4380__INCLUDED_)
#define AFX_G30C04_H__3A4EC7E3_14C2_11D5_BCB7_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "g30c05.h"
#include "g_01c08.h"
#include "g30def.h"

/*
	Informacion del material de las caras de la malla
*/
typedef struct
{
	DWORD	first_face;
	DWORD	face_cant;
	CDXMaterial	*lpmaterial;
}S_MATS;
/*
	Datos del directx mesh
*/
typedef struct
{
	DWORD	m_version;
	char	m_name[20];			// Nombre del mesh
	DWORD	m_vertex_cant;		// Cantidad de vertices
	DWORD	m_vertex_type;		// Tipo de vertices almecenados en el arreglo
	DWORD	m_material_cant;	// Cantidad de materiales
	DWORD	m_faces_cant;
}S_DXMESH;

class CDXEscene;

class CDXMesh  
{
public:
	DWORD DeleteAll();
	virtual ~CDXMesh();
	DWORD SetPrimitiveType(D3DPRIMITIVETYPE ptype);
	DWORD Paint();
	DWORD SetVertex(DWORD cant,DWORD vtype,LPVOID lpvertex);
	DWORD Initialize();
	DWORD Read(C3DMesh* lp3dmesh);
	DWORD Release();
	DWORD SetEscene(CDXEscene* lpdxescene);
	CDXMesh();

	CDXMaterial	*m_lpmaterial;	// Material si es uno.
	S_MATS		*m_lpmaterials;	// Materiales del mesh
	LPVOID		m_lpvertex;		// Puntero a los vertices
	DWORD		m_memory_size;	// Espacio requerid para la informacion del mesh
	DWORD		m_on_init;		// Indica que esta clase ya ha sido inicializada
	S_DXFACE	*m_lpfaces;
	CDXEscene	*m_lpescene;
	S_DXMESH	m_info;
	CDXMesh		*m_next,*m_prev;// Soporte para listas dinamicas
	D3DPRIMITIVETYPE	m_ptype;

};

#endif // !defined(AFX_G30C04_H__3A4EC7E3_14C2_11D5_BCB7_00D0093D4380__INCLUDED_)
