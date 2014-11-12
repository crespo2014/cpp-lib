// Folder.h: interface for the CFolder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FOLDER_H__9C27E132_316D_4DEE_AFDE_E7BB1EF7F680__INCLUDED_)
#define AFX_FOLDER_H__9C27E132_316D_4DEE_AFDE_E7BB1EF7F680__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logclient.h"

class CFolder  
{
public:
	void SetFolder(char* folder_path);
	CFolder();
	virtual ~CFolder();

private:
	char	m_folder_path[MAX_PATH];


};

#endif // !defined(AFX_FOLDER_H__9C27E132_316D_4DEE_AFDE_E7BB1EF7F680__INCLUDED_)
