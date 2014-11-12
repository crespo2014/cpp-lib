// ChangePass.cpp : implementation file
//

#include "stdafx.h"
#include "ChangePass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangePass dialog


CChangePass::CChangePass(CWnd* pParent /*=NULL*/)
	: CDialog("PASSWORD", pParent)
{
	//{{AFX_DATA_INIT(CChangePass)
	m_new_pass = _T("");
	m_retype_pass = _T("");
	//}}AFX_DATA_INIT
}


void CChangePass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangePass)
	DDX_Text(pDX, IDC_EDIT_NUEVA, m_new_pass);
	DDX_Text(pDX, IDC_EDIT_REESCRIBIR, m_retype_pass);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangePass, CDialog)
	//{{AFX_MSG_MAP(CChangePass)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangePass message handlers
bool CChangePass::CheckData()
{
	bool result=false;
    
	if (m_new_pass.IsEmpty() || m_retype_pass.IsEmpty())
	{
	  AfxMessageBox("Not all data is fill");
	}
	
	else
	{
		if (m_new_pass != m_retype_pass)
		{
		  AfxMessageBox("The retyped password is not the same to the new");
		  return false;
		}
		result = true;
	}
	
	return result;

}