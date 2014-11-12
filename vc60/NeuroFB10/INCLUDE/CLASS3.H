// class3.h: interface for the CGLPrimitiva class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASS3_H__6531C781_DDFA_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_CLASS3_H__6531C781_DDFA_11D3_A036_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl10c2.h"

class C3DObject;

// esta estructura es la que esta asociada a cada elemento del tree
// y la deben poseer las primitivas y los objetos
typedef struct
{
	UINT	m_Type;		// Primitiva o objeto
	LPVOID	m_This;		// Puntero a la clase
} S_TreeObject;
/*
	Estructura para salvar los parametros de las primitivas en disco
	despues de ella vienen los vertices

*/
typedef struct
{
	DWORD		m_Version;
	DWORD		m_Type;
	DWORD		m_CantVert;
} S_PRIMITIVEINFO;

// 
// estructuras utilizadas
// 

typedef struct 
{
	float x,y,z;
} S_Normal;
typedef struct
{
	float S,T,R,Q;
} S_Texture;
typedef struct
{
	float R,G,B,A;
} S_Color;

// Definiciaon de arreglos para estas estructuras

typedef CArray<point3ds,point3ds>   CVertexArray;
typedef CArray<S_Normal,S_Normal>   CNormalArray;
typedef CArray<S_Texture,S_Texture> CTextureArray;
typedef CArray<S_Color,S_Color>     CColorArray;

class AFX_EXT_CLASS CGLPrimitiva : public CObject  
{
public:
	BOOL IsSelected();
	int SetSelect(BOOL pState);
	int SetNormal(float px,float py,float pz);
	int SetColor(float pR,float pG,float pB, float pA);
	int RemoveFromTree();
	int Destroy();
	int AddToTree();
	int SetTree(CTree3DObject *pTree);
	int SetParent(C3DObject* pParent);
	int GetMinPoint(float* pPoint);
	int GetMaxPoint(float* pPoint);
	int CalcDim();
	int Trasladar(float px,float py,float pz);
	int SetNormal(S_Normal* pNormals);
	int SetVertex(point3ds* pVertex);
	int SetPrimitiva(UINT pType);
	DWORD GetCantVert();
	int SetCantVert(DWORD pCant);
	int Paint();
	int ReadFromFile(FILE* pFile);
	int SaveToFile(FILE* pFile);

	S_PRIMITIVEINFO	m_Disk;
	// Nombre
	CString		m_Name;
	// Determina el tipo de primitiva
	UINT		m_Type;
	// Arreglo de vertices
	point3ds*	m_Vertices;
	GLsizei		m_VSize;
	// Arreglo de normales
	S_Normal*	m_Normales;
	// Arreglo de texturas
	S_Texture*	m_Texture;
	GLsizei		m_TSize;
	// Arreglo de clores
	S_Color*	m_Colors;
	GLsizei		m_CSize;
	// Arreglos habilitados
	float		m_Color[4];
	float		m_Normal[3];
	// Lista a que pertenece el objeto
	BOOL		m_OnList;
	UINT		m_List;
	// Dimesiones de la primitiva
	float		m_MaxX;
	float		m_MaxY;
	float		m_MaxZ;
	float		m_MinX;
	float		m_MinY;
	float		m_MinZ;
	// Indica que la primitiva a sido seleccionada en el tree
	BOOL		m_OnTreeSelect;

	// Necesitan saber a que objeto estan asociadas, para uso multiple
	C3DObject*	m_ParentObject;
	// tree asociado
	CTree3DObject* m_TreeCtrl;
	// Parametro del tree
	S_TreeObject	m_TreeObject;
	// Handle del item en el Tree
	HTREEITEM		m_hTreeItem;

	CGLPrimitiva();
	virtual ~CGLPrimitiva();

protected:
	void Init();
};

#endif // !defined(AFX_CLASS3_H__6531C781_DDFA_11D3_A036_0000E83D722B__INCLUDED_)
