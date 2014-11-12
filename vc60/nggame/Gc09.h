// g_01c09.h: interface for the C3DMaterial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G_01C09_H__74D601C4_C917_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_G_01C09_H__74D601C4_C917_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gdef.h"

typedef struct
{
	DWORD		m_size;
	char		m_name[21];
	DWORD		m_index;
	S_3DSCOLOR	m_ambient;
	S_3DSCOLOR	m_diffuse;
	S_3DSCOLOR	m_specular;
	BOOL		m_twosides;
	float		m_shininess;
	float		m_transparecy;
} S_3DMATERIAL;	

class C3DMaterial 
{
public:
	DWORD MakeCurrent();
	DWORD ReadFromMemory(void* lppointer);
	C3DMaterial();
	virtual ~C3DMaterial();
private:
	S_3DMATERIAL m_data;
	S_3DMATERIAL *m_lpdata;
};

#endif // !defined(AFX_G_01C09_H__74D601C4_C917_11D4_9126_0000E83D722B__INCLUDED_)
