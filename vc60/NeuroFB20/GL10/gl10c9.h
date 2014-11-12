 // gl10c9.h: interface for the CVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL10C9_H__C7C3BB44_F454_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_GL10C9_H__C7C3BB44_F454_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl10s.h"
typedef struct
{
	DWORD	version;
	char	name[21];
	DWORD	index;
	float	value;
	float	max;	// EL MINIMO ES CERO Y CADA INSTANCIA POSEE UN MINIMO Y 
					// UNA PENDIENTE
} S_VARIABLEINFO;
typedef struct
{
	S_VARIABLEINFO	info;
	S_TREELPARAM	treelparam;
	HTREEITEM		htree;
	CEscenaTree*	tree;
	CEscena*		escena;
	POSITION		pos;
}S_VARIABLE;

class CVariable : public CObject  
{
public:
	int ReadFromFile(FILE *pFile);
	int SaveToFile(FILE *pFile);
	int SetIndex(DWORD pIndex);
	int SetName(char* name);
	char* GetName();
	float GetMaxValue();
	int SetMaxValue(float max);
	int Change();
	DWORD GetIndex();
	int SetEscena(CEscena* pescena);
	int SetPos(POSITION pPos);
	int AttachToTree(CEscenaTree *pTree);
	int SetValue(float value);
	float GetValue();
	S_VARIABLE* m_Variable;
	int InitVariable();
	CVariable();
	virtual ~CVariable();

};

#endif // !defined(AFX_GL10C9_H__C7C3BB44_F454_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
