 // gl10c8.h: interface for the CMeshInstance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL10C8_H__BAA0A804_F423_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_GL10C8_H__BAA0A804_F423_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl10s.h"

/*
	Esta clase se encuentra en la lista de los CMeshGroup
*/
typedef struct
{
	DWORD	version;
	DWORD	index;		// indice del mesh

}S_MESHINSTANCEINFO;

typedef struct
{
	S_MESHINSTANCEINFO	info;
	S_TREELPARAM		treelparam;
	POSITION			pos;
	HTREEITEM			htree;
	CMeshGroup*			parent;
	CEscenaTree*		tree;
	CMeshMat*			mesh;
}S_MESHINSTANCE;

class CMeshInstance : public CObject  
{
public:
	int AttachToTree();
	int SetTree(CEscenaTree *pTree);
	int ReadFromFile(FILE *pFile);
	int UpdateIndex();
	int SaveToFile(FILE *pFile);
	int SetPos(POSITION pos);
	int DetachFromTree();
	int Delete();
	CMeshMat* GetMesh();
	int SetParent(CMeshGroup* parent);
	int InitMeshInstance();
	int SetMesh(CMeshMat* pmesh);
	S_MESHINSTANCE* m_MeshInstance;
	int UpDateMeshByIndex();
	CMeshInstance();
	virtual ~CMeshInstance();

};

#endif // !defined(AFX_GL10C8_H__BAA0A804_F423_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
