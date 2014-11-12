// T_MSG_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "Proyecto.h"
#include "T_MSG_DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T_MSG_DLG dialog


T_MSG_DLG::T_MSG_DLG(CWnd* pParent /*=NULL*/)
	: CDialog(T_MSG_DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(T_MSG_DLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void T_MSG_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(T_MSG_DLG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(T_MSG_DLG, CDialog)
	//{{AFX_MSG_MAP(T_MSG_DLG)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T_MSG_DLG message handlers

void T_MSG_DLG::OnOK() 
{
	EndDialog(0);	
}

void T_MSG_DLG::OnCancel() 
{
	EndDialog(1);	
}

void T_MSG_DLG::OnButton1() 
{
	EndDialog(2);	
}
