 // gl10c4.h: interface for the CMeshGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL10C4_H__B69A0025_F1EF_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_GL10C4_H__B69A0025_F1EF_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl10s.h"

typedef struct
{
	DWORD		version;
	char		name[21];
	/*
	S_3DSPOINT	position;
	S_3DSPOINT	rotation;
	*/
	DWORD		nvar;		//cantidad de variables
	DWORD		nmesh;		//cantidad de MeshMat
	DWORD		nmeshgroup; //cantidad de mesgroup
} S_MESHGROUPINFO;

typedef struct
{
	S_MESHGROUPINFO	info;
	S_TREELPARAM	treelparam;
	HTREEITEM		htree;
	CObList			MeshList;
	CObList			VarList;
	CObList			grouplist;
	CMeshGroup*		parent;
	POSITION		pos;		//ubicacion en el padre
	CGLView*		view;
	CEscena*		escena;
	CEscenaTree*	tree;
} S_MESHGROUP;

class CMeshGroup : public CObject  
{
public:
	int AttachToTree();
	int SetTree(CEscenaTree *pTree);
	int AddMeshInstance(CMeshInstance* pMI);
	int AddVariableInstance(CVariableInstance* pVariableInstance);
	int ReadFromFile(FILE *pFile);
	int SaveToFile(FILE *pFile);
	int SetName(char* name);
	int DeleteVariableInstance(POSITION pos);
	int Delete();
	int DetachFromTree();
	int DeleteMeshGroup(POSITION pos);
	int DeleteMeshInstance(POSITION pos);
	CMeshGroup* GetParent();
	int DeleteAllVariables();
	int DeleteAllMesh();
	int DeleteAllMeshGroup();
	int AddMeshGroup(CMeshGroup* pmeshgroup=NULL);
	int InitMeshGroup();
	int AddVariable(CVariable* pvariable);
	HTREEITEM GetTreeHandle();
	CEscena* GetEscena();
	int SetEscena(CEscena* pEscena);
	LPARAM GetTreeLParam();
	int AddMesh(CMeshMat* pMesh);
	int SetPos(POSITION pPos);
	int SetParent(CMeshGroup* pMeshGroup);
	int Paint();
	CMeshGroup();
	virtual ~CMeshGroup();
private:
	S_MESHGROUP* m_MeshGroup;
};

#endif // !defined(AFX_GL10C4_H__B69A0025_F1EF_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
