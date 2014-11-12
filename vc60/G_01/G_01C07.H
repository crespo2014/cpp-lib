// g_01c07.h: interface for the C3DEscene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G_01C07_H__74D601C1_C917_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_G_01C07_H__74D601C1_C917_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
{
	DWORD	m_version;		// Tamano de la estructura
	DWORD	m_mat_cant;		// Cantidad de materiales
	DWORD	m_mesh_cant;	// Cantidad de mallas
	DWORD	m_var_cant;		// Usada solo por compatibilidad
} S_3DESCENE;

class C3DMesh;
class C3DMaterial;

class C3DEscene : public CObject  
{
public:
	C3DMesh* Get3DMesh(char* pname);
	C3DMesh* Get3DMesh(DWORD pindex);
	C3DMaterial* GetMaterial(DWORD pindex);
	DWORD ReadFromResource(char* lpName,char* lpType);
	DWORD Destroy();
	DWORD Initialize();
	C3DEscene();
	virtual ~C3DEscene();
private:
	S_3DESCENE		m_data,*m_lpdata;	// puntero o miembro estatico
	C3DMesh*		m_first_mesh;		// Usado para apuntar a una lista enlazada
	C3DMaterial*	m_first_material;	// Igual que el anterior
	BOOL			m_onresource;		// Indica que la escena ha sido leida de un recurso


};

#endif // !defined(AFX_G_01C07_H__74D601C1_C917_11D4_9126_0000E83D722B__INCLUDED_)
