// FileDriver.cpp: implementation of the CFileDriver class.
//
//////////////////////////////////////////////////////////////////////

#include "FileDriver.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileDriver::CFileDriver()
{
	m_hffile = NULL;
	m_curdir[0] = 0;
}

CFileDriver::~CFileDriver()
{
	ReleaseHandle();
}

DWORD CFileDriver::SetCurrentDir(char *dir)
{
	// cerrar handle de directorio si esta abierto
	strcpy(m_curdir,dir);
	return ERR_OK;
}

DWORD CFileDriver::FindFile(char *file_pattern)
{
	char	path[MAX_PATH];
	if (m_hffile) ReleaseHandle();
	sprintf(path,"%s\\%s",m_curdir,file_pattern);
	m_hffile = FindFirstFile(path,&m_find_data);
	if (m_hffile == INVALID_HANDLE_VALUE) 
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CFileDriver::FindFile -> FindFirstFile ... failed");
	return ERR_OK;	
}

DWORD CFileDriver::RenameFile(char *new_name)
{
	char	old_fn[MAX_PATH];
	char	new_fn[MAX_PATH];
	sprintf(old_fn,"%s\\%s",m_curdir,m_find_data.cFileName);
	sprintf(new_fn,"%s\\%s",m_curdir,new_name);
	if (!MoveFile(old_fn,new_fn))
		glog._log(LOG_ERROR,"CFileDriver::RenameFile ->MoveFile ... failed");

	return ERR_OK;
}

void CFileDriver::ReleaseHandle()
{
	if (m_hffile == NULL) return;
	if (FindClose(m_hffile) == 0) glog._log(LOG_ERROR,"CFileDriver::ReleaseHandle -> FindClose ... failed");
	m_hffile = NULL;
}

DWORD CFileDriver::GetFilePath(char *path, int max_size)
{
	_snprintf(path,max_size,"%s\\%s",m_curdir,m_find_data.cFileName);
	return ERR_OK;
}

void CFileDriver::GetFileName(char *fname, int max_size)
{
	_snprintf(fname,max_size,"%s",m_find_data.cFileName);	
}

DWORD CFileDriver::GetFileData(WIN32_FIND_DATA *pfile_data)
{
	*pfile_data = m_find_data;
	return ERR_OK;
}

DWORD CFileDriver::NextFile()
{
	DWORD dwr;
	if (m_hffile == NULL) return ERR_HANDLE;
	if (!FindNextFile(m_hffile,&m_find_data))
	{
		dwr = GetLastError();
		if (dwr ==	ERROR_NO_MORE_FILES) return ERR_EOF;
		glog._log(LOG_ERROR,"CFileDriver::NextFile -> FindNextFile ... failed");
		return ERR_FATAL;
	}
	return ERR_OK;
}

DWORD CFileDriver::Folder_Delete(char *folder, BOOL bDeleteAll)
{
	DWORD	dr = ERR_OK;
	DWORD	dr1;
	char	path[MAX_PATH];
	if (bDeleteAll)
	{
		CFileDriver	nfile;
		nfile.SetCurrentDir(folder);
		dr1 = nfile.FindFile("*.*");
		while (dr1 == ERR_OK)
		{
			path[MAX_PATH-1] = 0;
			_snprintf(path,sizeof(path)-1,"%s\\%s",nfile.m_curdir,nfile.m_find_data.cFileName);
			SetFileAttributes(path,FILE_ATTRIBUTE_NORMAL);
			if (nfile.IsFolder())
			{
				if (*nfile.m_find_data.cFileName != '.')
					Folder_Delete(path,true);
			}
			else
			{
				if (!DeleteFile(path)) 
				{
					SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CFileDriver::Folder_Delete -> DeleteFile (%s)",path);
					dr = ERR_API;
				}
			}
			dr1 = nfile.NextFile();
		}
	}
	if (!RemoveDirectory(folder)) 
	{
		SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CFileDriver::Folder_Delete -> RemoveDirectory (%s)",folder);
		dr = ERR_FATAL;
	}
	return dr;

}

BOOL CFileDriver::IsFolder(char* path)
{
	DWORD	dwr;	
	if (path == NULL) 
	{
		return (m_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	}
	dwr = GetFileAttributes(path);
	if (dwr == INVALID_FILE_ATTRIBUTES) 
	{
		SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CFileDriver::IsFolder -> GetFileAttributes (%s) ",path);
		return false;
	}
	return (dwr & FILE_ATTRIBUTE_DIRECTORY);
}

DWORD CFileDriver::File_Copy(char *src, char *dest)
{
	if (CopyFile(src,dest,true)) return ERR_OK;
	return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CFileDriver::File_Copy -> CopyFile");
}
