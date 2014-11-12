// g_01c08.h: interface for the C3DMesh class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G_01C08_H__74D601C2_C917_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_G_01C08_H__74D601C2_C917_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gdef.h"

class C3DMaterial;
class C3DEscene;

/*
	Usada por las mallas para almacenar la informacion de los materiales que la 
	componen y poder pedirle a la escena el material
*/
typedef struct 
{
	DWORD		m_faces_cant;
	DWORD		m_mat_index;	
}S_3DMESHMATDAT;

/*
	Usada por las mallas para almacenar el material y las caras que comprende
*/
typedef struct 
{
	S_3DMESHMATDAT m_data;
	DWORD		*m_faces;
	C3DMaterial	*m_material;
}S_3DMESHMAT;



class C3DMesh   
{
public:
	DWORD CalcSize();
	DWORD GetSize(S_3DSIZE* p3dsize);
	DWORD Destroy();
	DWORD Paint();
	DWORD Set3DEscene(C3DEscene* p3descene);
	DWORD ReadFromMemory(void* lpPointer);
	C3DMesh();
	virtual ~C3DMesh();
public:
	S_3DMESH	m_data,*m_lpdata;
	BOOL		m_onstatic;	// los punteros no deben ser destruidos porque son
							// estaticos
	S_3DSPOINT*		m_vertex;
	S_3DSFACE*		m_faces;
	S_3DMESHMAT*	m_materials;
	C3DEscene*		m_3descene;
	S_3DSIZE		m_size;
	
};

#endif // !defined(AFX_G_01C08_H__74D601C2_C917_11D4_9126_0000E83D722B__INCLUDED_)
