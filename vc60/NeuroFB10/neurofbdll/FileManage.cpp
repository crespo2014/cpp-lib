// FileManage.cpp: implementation of the CFileManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileManage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileManage::CFileManage()
{

}

CFileManage::~CFileManage()
{

}

bool CFileManage::OpenFile(CString dir)
{
	
	CString current;
	current = dir + "\\database\\*.mdb";
	CFileDialog open(TRUE,"mdb",current);
	CString pathnew;
	pathnew = dir + "\\database\\patientdb.mdb";
    CString pathdelete;
    pathdelete = dir + "\\database\\patientdb.mdb";
	CString pathold;
	
	
	if (open.DoModal()==IDOK)
	{
		pathold =open.GetPathName();
		if(!DeleteFile(pathdelete))
		{
			AfxMessageBox("Can't delete old files");
			return false;	
		}
		if (!CopyFile(pathold,pathnew,FALSE))
		{
			AfxMessageBox("Can't copy new data file");
			return false;
		}
		return true;
	}
	
	else
		return false;
	
}


bool CFileManage::SaveFile(CString dir)
{
	
	CString current;
	current = dir + "\\sintitulo.mdb";
    CString pathold;
	pathold = dir;
	CString pathnew;
	CFileDialog save(FALSE,"mdb", current);
    
	if (save.DoModal()==IDOK)
        {
			pathnew =save.GetPathName();
            if (!CopyFile(pathold,pathnew,FALSE))
			{
			AfxMessageBox("Can't copy data file");
			return false;
			}
		    return true;    
        }
		
		else
		return false;;
    
}



bool CFileManage::RestoreFile(CString dir)
{

	CString pathdest;
	pathdest = dir + "\\database\\patientdb.mdb";
    CString pathorg;
    pathorg = dir + "\\database\\backup\\patientdb.mdb";
	
    if(!DeleteFile(pathdest))
		{
			AfxMessageBox("Can't delete old files");
			return false;	
		}
	if (!CopyFile(pathorg,pathdest,FALSE))
		{
			AfxMessageBox("Can't copy new data file");
			return false;
		}
				return true;
	
			
}
