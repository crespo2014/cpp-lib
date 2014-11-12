 // gl10c10.h: interface for the CVariableInstance class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL10C10_H__9FE5EC06_F5A9_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_GL10C10_H__9FE5EC06_F5A9_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl10s.h"

typedef enum
{
	MOD_POS,
	MOD_ROT
};

typedef struct
{
	DWORD	version;
	DWORD	varindex;
	float	factor;
	float	minimo;
	WORD	change;
	float	rotpto[3];
	float	rotvect[3];
	float	posfac[3];
}S_VARIABLEINSTANCEINFO;

typedef struct
{
	S_VARIABLEINSTANCEINFO	info;
	POSITION				pos;
	HTREEITEM				htree;
	CMeshGroup*				parent;
	CVariable*				var;
	CEscenaTree*			tree;
	S_TREELPARAM			treelparam;
} S_VARIABLEINSTANCE;

class CVariableInstance : public CObject  
{
public:
	int SetMin(float min);
	int AttachToTree();
	int SetTree(CEscenaTree *pTree);
	int ReadFromFile(FILE *pFile);
	int UpdateIndex();
	int SaveToFile(FILE *pFile);
	int Delete();
	int SetParent(CMeshGroup *parent);
	int DetachFromTree();
	int SetPos(POSITION pos);
	int SetPosition(float* pos);
	int GetPosition(float* pos);
	int SetRotationPoint(float* rotpto);
	int GetRotationPoint(float* rotpto);
	int Propiedades();
	int SetRotationVector(float* vector);
	int GetRotationVector(float* vector);
	float GetMin();
	float GetFactor();
	int ApplyModifier();
	int SetModifier(WORD change);
	WORD GetModifier();
	int SetVar(CVariable* pvar);
	CVariableInstance(CVariable* pvar);
	S_VARIABLEINSTANCE* m_VariableInstance;
	int InitVariableInstance();
	CVariableInstance();
	virtual ~CVariableInstance();

};

#endif // !defined(AFX_GL10C10_H__9FE5EC06_F5A9_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
