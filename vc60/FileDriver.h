// FileDriver.h: interface for the CFileDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEDRIVER_H__57A89554_7636_45CE_B3E3_7AE3AB092525__INCLUDED_)
#define AFX_FILEDRIVER_H__57A89554_7636_45CE_B3E3_7AE3AB092525__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

class CFileDriver  : public CbObject
{
public:
	DWORD File_Copy(char* src,char* dest);
	BOOL IsFolder(char* path = NULL);
	DWORD Folder_Delete(char* folder,BOOL bDeleteAll = false);
	DWORD NextFile();
	DWORD GetFileData(WIN32_FIND_DATA* pfile_data);
	void GetFileName(char* fname,int max_size);
	DWORD GetFilePath(char* path,int max_size);
	void ReleaseHandle();
	DWORD RenameFile(char* new_name);
	DWORD FindFile(char* file_pattern);
	DWORD SetCurrentDir(char* dir);
	CFileDriver();
	virtual ~CFileDriver();

private:
	char	m_curdir[MAX_PATH];
	HANDLE	m_hffile;

	WIN32_FIND_DATA	m_find_data;

};

#endif // !defined(AFX_FILEDRIVER_H__57A89554_7636_45CE_B3E3_7AE3AB092525__INCLUDED_)
