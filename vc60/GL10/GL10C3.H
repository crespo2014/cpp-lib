 // gl10c3.h: interface for the CMeshMat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL10C3_H__65966600_F1E0_11D3_A037_0000E83D722B__INCLUDED_)
#define AFX_GL10C3_H__65966600_F1E0_11D3_A037_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl10S.h"
#include "..\g_01\g_01def.h"

// esta estructura es debido a que un mesh posee
//	varios materiales
typedef struct
{
	DWORD		nfaces;
	DWORD		index;
} S_MATDATINFO;					// datos del material

typedef struct
{
	S_MATDATINFO	info;
	DWORD*			facesindex;
	CMaterial*		pMaterial;
}S_MATDAT;

typedef struct
{
	S_3DMESH		info;
	S_TREELPARAM	treelparam;
	S_3DSPOINT*		vertexarray;
	S_3DSFACE*		facearray;
	CEscena*		view;
	S_MATDAT*		matarray;
	HTREEITEM		htree;
	POSITION		pos;
} S_MESHMAT;

/*
	Esta clase posee toda la funcionalidad de una malla
	posee vertices y caras mas un material
*/
class AFX_EXT_CLASS CMeshMat : public CObject  
{
public:
	int ReadFromFile(FILE *pFile);
	int UpdateIndex();
	int ReadMesh3DS(mesh3ds *pmesh);
	int SaveToFile(FILE *pFile);
	int SetIndex(DWORD pIndex);
	int InitMeshMat();
	int SetName(char* name);
	POSITION GetPos();
	DWORD GetIndex();
	LPARAM GetTreeLParam();
	char* GetName();
	int SetTreeHandle(HTREEITEM pHandle);
	int SetEscena(CEscena* pEscena);
	int SetFace(DWORD pPos,S_3DSFACE pFace);
	int SetVertex(DWORD pPos,S_3DSPOINT pPoint);
	int SetCantFaces(WORD pCant);
	int SetCantVertex(WORD pCant);
	CMeshMat(WORD pnvertex, WORD pnfaces);
	int Paint();
	CMeshMat();
	virtual ~CMeshMat();

private:
	S_MESHMAT* m_MeshMat;
};

#endif // !defined(AFX_GL10C3_H__65966600_F1E0_11D3_A037_0000E83D722B__INCLUDED_)
