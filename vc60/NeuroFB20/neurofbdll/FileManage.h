// FileManage.h: interface for the CFileManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEMANAGE_H__648CC124_B309_11D3_A372_0000E83D722B__INCLUDED_)
#define AFX_FILEMANAGE_H__648CC124_B309_11D3_A372_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>

class CFileManage  
{
public:
	bool RestoreFile(CString dir);
    bool SaveFile(CString dir);
	bool OpenFile(CString dir);
	CFileManage();
	virtual ~CFileManage();

};

#endif // !defined(AFX_FILEMANAGE_H__648CC124_B309_11D3_A372_0000E83D722B__INCLUDED_)
