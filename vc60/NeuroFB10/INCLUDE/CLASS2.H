// class2.h: interface for the C3DObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASS2_H__79E3A1CD_DD5B_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_CLASS2_H__79E3A1CD_DD5B_11D3_A036_0000E83D722B__INCLUDED_

#include "class3.h"
#include "gl10c2.h"
#include "gl10c3.h"
#include "gl10c5.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
	Tipos de objetos basicos 
*/
enum 
{
	TYPE_VIEW,
	TYPE_3DOBJECT,
	TYPE_PRIMITIVA,
	TYPE_CILINDER,
};
/*
#define TYPE_VIEW		0
#define TYPE_3DOBJECT	1
#define TYPE_PRIMITIVA	2
#define TYPE_CILINDER	3
*/

/*
 Esto es lo primero que aparece cuando se lee un objeto 3D
 despues de leida esta estructura ya se puede crear el objeto
 de acuerdo al tipo que sea
*/

typedef struct 
{
	DWORD		m_Version;	// Tamano (compatibilidad)
	DWORD		m_Type;		// Identifica el tipo de objeto
} S_3D0BJECTHEADER;

/*
	Parametros de la vista
*/
typedef struct
{
	DWORD	m_Version;		// Tamano de la estructura (Compatibildad)
	DWORD	m_Type;			// Indica si es una vista o un objeto
	DWORD	m_ObjectsCant;	// Cantidad de objetos
} S_3DVIEWINFO;


/*
	Estructura utilizada para salvar en disco
	la informacion de un objeto
*/
typedef struct 
{
	DWORD		m_Version;			// tamano de la estructura (compatibilidad)
	DWORD		m_NameLength;		// Longitud del nombre 
	float		m_AmbientR;			// Propiedades del material
	float		m_AmbientG;
	float		m_AmbientB;
	float		m_AmbientA;
	float		m_DiffuseR;
	float		m_DiffuseG;
	float		m_DiffuseB;
	float		m_DiffuseA;
	float		m_SpecularR;
	float		m_SpecularG;
	float		m_SpecularB;
	float		m_SpecularA;
	float		m_EmissionR;
	float		m_EmissionG;
	float		m_EmissionB;
	float		m_EmissionA;
	float		m_ShininessR;
	float		m_ShininessG;
	float		m_ShininessB;
	float		m_ShininessA;
	float		m_PosX;				// Posicion del Objeto
	float		m_PosY;
	float		m_PosZ;
	float		m_RotateX;			// angulo de giro respecto a cada eje
	float		m_RotateY;
	float		m_RotateZ;
	float		m_ColorR;			// Cuando no hay iluminacion
	float		m_ColorG;
	float		m_ColorB;
	float		m_ColorA;
	DWORD		m_AssociatesCant;	// Cantidad de objetos asociados
	DWORD		m_ChildsCant;		// Cantidad de objetos hijos
	DWORD		m_PrimitivesCant;	// Cantidad de primitivas

} S_3DOBJECTINFO;


/*
	variable de C3DObject
*/

typedef struct 
{
	S_3D0BJECTHEADER	m_Header;
	S_3DOBJECTINFO		m_Disk;

	// Nombre del objeto en 3D
	CString m_Name;
	// Lista a que pertenece el objeto
	BOOL		m_OnList;
	UINT		m_List;
	// Lista de Objetos Hijos
	CObList		m_Childs; 	
	// Lista de primitivas asociadas
	CObList	    m_Primitives;
	// Lista de objetos asociados es decir varios objetos pueden formar uno
	CObList		m_Associates;
	// Se activa despues de la generacion de primitivas para indicar que estan generadas
	BOOL		m_OnPrimitive;
	// Handle del item en el Tree
	HTREEITEM	m_hTreeItem;
	// puntero al tree
	CTree3DObject*	m_TreeCtrl;
	S_TreeObject	m_TreeObject;
	// Objeto padre al cual pertenece
	C3DObject*  m_Parent;
	C3DObject*	m_Partner;
	// Usado para saber como insertar el objeto cuando se genera
	BOOL		m_OnAsociar;

} S_3DObject;



class AFX_EXT_CLASS C3DObject : public CObject  
{
public:
	int AddMesh(CMeshMat* pMesh);
	int Import3ds(); //Addiciona primitivas desde un 3ds
	int SaveAllChildObject(FILE* pFile);
	int SaveData(FILE* pFile);
	int SaveAllAssociatesObjects(FILE *pFile);
	int AddAssociatesObjects(DWORD pCant, FILE *pFile);
	int AddChildsObjects(DWORD pCant,FILE *pFile);
	C3DObject* ReadObject(FILE *pFile);
	virtual int VSaveData(FILE *pFile);
	virtual int VReadData(FILE *pFile);
	int ReadData(FILE* pFile);
	virtual int VConfigure();
	HTREEITEM GetTreeItemHandle();
	int SetTree(CTree3DObject *pTree);
	int RemoveFromTree();
	int SetPartner(C3DObject* p3DObject);
	int SetParent(C3DObject* pParent);
	int AddAssociateObject(C3DObject* pObject);
	int AddChildObject(C3DObject* pObject);
	int AddToTree();
	int AddNewObject();
	int PaintBox(float* pUp,float* pDown);
	virtual int VPaint();
	virtual int VGeneratePrimitive();
	int Destroy();
	int Init();
	int Configure();
	int IsPrimitive();
	int GeneratePrimitive();
	virtual int EnabledFaces(DWORD pFaces);
	int AddPrimitive(CGLPrimitiva* pPrimitiva);
	virtual int Paint();
	int ReadFromFile(FILE* pFile);
	int SetName(CString pName);
	int SaveToFile(FILE* pFile);
	// Puntero asociado a todas las variables de la clase
	S_3DObject* m_3DObject;
	CObList		m_MeshList;
	C3DObject();
	virtual ~C3DObject();

};

#endif // !defined(AFX_CLASS2_H__79E3A1CD_DD5B_11D3_A036_0000E83D722B__INCLUDED_)
