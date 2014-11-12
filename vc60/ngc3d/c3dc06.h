// c3dc06.h: interface for the CDXMaterial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_C3DC06_H__FE0EBFE1_0201_11D5_8D3A_00D0093D4380__INCLUDED_)
#define AFX_C3DC06_H__FE0EBFE1_0201_11D5_8D3A_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "c3ddef.h"

typedef struct
{
	char			m_name[30];
	D3DMATERIAL7	data;	
	BOOL			m_twosides;
}S_DXMATERIAL;

class CDXMaterial  
{
public:
	CDXMaterial();
	virtual ~CDXMaterial();
	D3DMATERIAL7	m_data,*m_lpdata;
	DWORD			m_id;

};

#endif // !defined(AFX_C3DC06_H__FE0EBFE1_0201_11D5_8D3A_00D0093D4380__INCLUDED_)
