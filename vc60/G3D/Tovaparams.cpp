// TovaParams.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "TovaParams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTovaParams dialog


CTovaParams::CTovaParams(CWnd* pParent /*=NULL*/)
	: CDialog(CTovaParams::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTovaParams)
	m_TBO = 0;
	m_TP = 0;
	//}}AFX_DATA_INIT
}


void CTovaParams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTovaParams)
	DDX_Text(pDX, IDC_G3D_EDIT1, m_TBO);
	DDX_Text(pDX, IDC_G3D_EDIT2, m_TP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTovaParams, CDialog)
	//{{AFX_MSG_MAP(CTovaParams)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTovaParams message handlers
