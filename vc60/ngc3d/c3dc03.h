// c3dc03.h: interface for the CDXEscene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_C3DC03_H__D55FA0C0_01FF_11D5_8D3A_00D0093D4380__INCLUDED_)
#define AFX_C3DC03_H__D55FA0C0_01FF_11D5_8D3A_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "c3ddef.h"

class CDXMaterial;
class CDXMesh;

typedef struct
{
	DWORD	meshcant;
	DWORD	matcant;
}S_DXESCENE;

class CDXEscene  
{
public:
	DWORD SetD3DDevice(LPDIRECT3DDEVICE7 lpd3ddevice);
	DWORD ReadFromResource(char* lpname,char* lptype);
	CDXEscene();
	virtual ~CDXEscene();
	S_DXESCENE			m_data,*m_lpdata;
	CDXMesh*			m_lpmesh;
	CDXMaterial*		m_lpmat;
	BOOL				m_OnStatic;
	LPDIRECT3DDEVICE7	m_lpd3ddevice;

};

#endif // !defined(AFX_C3DC03_H__D55FA0C0_01FF_11D5_8D3A_00D0093D4380__INCLUDED_)
