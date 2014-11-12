// EntradaSistema.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "EntradaSistema.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEntradaSistema dialog


CEntradaSistema::CEntradaSistema(CWnd* pParent /*=NULL*/)
	: CDialog("IDD_PASSWORD", pParent)
{
	//{{AFX_DATA_INIT(CEntradaSistema)
	m_Password = _T("");
	//}}AFX_DATA_INIT
}


void CEntradaSistema::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntradaSistema)
	DDX_Text(pDX, IDC_PASSWORD, m_Password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEntradaSistema, CDialog)
	//{{AFX_MSG_MAP(CEntradaSistema)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntradaSistema message handlers

bool CEntradaSistema::CheckData()
{
	bool result=false;
    
	if (m_Password.IsEmpty())
	  result = false; 
	else
      result = true;

	return result;

}
