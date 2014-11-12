 // gl10c6.h: interface for the CMaterial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL10C6_H__039B87A1_F27B_11D3_A037_0000E83D722B__INCLUDED_)
#define AFX_GL10C6_H__039B87A1_F27B_11D3_A037_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl10s.h"
#include "..\g_01\g_01c09.h"
/*
typedef struct
{
	DWORD		version;
	char		name[21];
	DWORD		index;
	S_3DSCOLOR	ambient;
	S_3DSCOLOR	diffuse;
	S_3DSCOLOR	specular;
	BOOL		twosides;
	float		shininess;
	float		transparecy;
}S_MATERIALINFO;
*/

typedef struct
{
	S_3DMATERIAL	info;
	S_TREELPARAM	treelparam;
	POSITION		pos;
	HTREEITEM		htree;
}S_MATERIAL;

class CMaterial : public CObject  
{
public:
	int ReadFromFile(FILE *pFile);
	int SaveToFile(FILE *pFile);
	int SetIndex(DWORD pIndex);
	int SetName(char* name);
	LPARAM GetTreeLParam();
	int SetTreeHandle(HTREEITEM pHandle);
	POSITION GetPos();
	int SetPos(POSITION pPos);
	char* GetName();
	int MakeCurrent();
	CMaterial(material3ds* pmaterial);
	DWORD GetIndex();
	int InitMaterial();
	S_MATERIAL* m_Material;
	CMaterial();
	virtual ~CMaterial();
};

#endif // !defined(AFX_GL10C6_H__039B87A1_F27B_11D3_A037_0000E83D722B__INCLUDED_)
