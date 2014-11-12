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
	char	*fnc_name = "CFileDriver::FindFile";
	char	path[MAX_PATH];
	if (m_hffile) ReleaseHandle();
	sprintf(path,"%s\\%s",m_curdir,file_pattern);
	m_hffile = FindFirstFile(path,&m_find_data);
	if (m_hffile == INVALID_HANDLE_VALUE) 
		return log_w32error  GetLastError(),ERR_FATAL,"CFileDriver::FindFile -> FindFirstFile ... failed");
	return ERR_OK;	
}

DWORD CFileDriver::RenameFile(char *new_name)
{
	char	*fnc_name = "CFileDriver::RenameFile";
	char	old_fn[MAX_PATH];
	char	new_fn[MAX_PATH];
	sprintf(old_fn,"%s\\%s",m_curdir,m_find_data.cFileName);
	sprintf(new_fn,"%s\\%s",m_curdir,new_name);
	if (!MoveFile(old_fn,new_fn)) return log_w32error  GetLastError(),ERR_FATAL,"MoveFile");
	return ERR_OK;
}

void CFileDriver::ReleaseHandle()
{
	char	*fnc_name = "ReleaseHandle";
	if (m_hffile == NULL) return;
	if (FindClose(m_hffile) == 0) log_w32error  GetLastError(),ERR_FATAL,"FindClose");
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
	char	*fnc_name = "CFileDriver::NextFile";
	DWORD dwr;
	if (m_hffile == NULL) return ERR_HANDLE;
	if (!FindNextFile(m_hffile,&m_find_data))
	{
		dwr = GetLastError();
		if (dwr ==	ERROR_NO_MORE_FILES) return ERR_EOF;
		return log_w32error  GetLastError(),ERR_FATAL,"FindNextFile");
	}
	return ERR_OK;
}

DWORD CFileDriver::Folder_Delete(char *folder, BOOL bDeleteAll)
{
	char	*fnc_name = "CFileDriver::Folder_Delete";
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
					log_w32error  GetLastError(),ERR_FATAL,"DeleteFile (%s)",path);
					dr = ERR_API;
				}
			}
			dr1 = nfile.NextFile();
		}
	}
	if (!RemoveDirectory(folder)) 
	{
		return log_w32error  GetLastError(),ERR_FATAL,"RemoveDirectory (%s)",folder);
	}
	return dr;

}

BOOL CFileDriver::IsFolder(char* path)
{
	char	*fnc_name = "CFileDriver::IsFolder";
	DWORD	dwr;	
	if (path == NULL) 
	{
		return (m_find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	}
	dwr = GetFileAttributes(path);
	if (dwr == INVALID_FILE_ATTRIBUTES) 
	{
		log_w32error  GetLastError(),ERR_FATAL,"GetFileAttributes (%s) ",path);
		return false;
	}
	return (dwr & FILE_ATTRIBUTE_DIRECTORY);
}

DWORD CFileDriver::File_Copy(char *src, char *dest)
{
	char	*fnc_name = "CFileDriver::File_Copy";
	if (CopyFile(src,dest,true)) return ERR_OK;
	return log_w32error  GetLastError(),ERR_FATAL,"CopyFile");
}
