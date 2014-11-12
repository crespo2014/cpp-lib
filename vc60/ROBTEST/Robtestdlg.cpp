// RobTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RobTest.h"
#include "RobTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobTestDlg dialog

CRobTestDlg::CRobTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRobTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRobTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRobTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRobTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRobTestDlg, CDialog)
	//{{AFX_MSG_MAP(CRobTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_RADIO17, OnRadio17)
	ON_BN_CLICKED(IDC_RADIO18, OnRadio18)
	ON_BN_CLICKED(IDC_RADIO19, OnRadio19)
	ON_BN_CLICKED(IDC_RADIO20, OnRadio20)
	ON_BN_CLICKED(IDC_RADIO21, OnRadio21)
	ON_BN_CLICKED(IDC_RADIO22, OnRadio22)
	ON_BN_CLICKED(IDC_RADIO23, OnRadio23)
	ON_BN_CLICKED(IDC_RADIO24, OnRadio24)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	ON_BN_CLICKED(IDC_RADIO11, OnRadio11)
	ON_BN_CLICKED(IDC_RADIO12, OnRadio12)
	ON_BN_CLICKED(IDC_RADIO13, OnRadio13)
	ON_BN_CLICKED(IDC_RADIO14, OnRadio14)
	ON_BN_CLICKED(IDC_RADIO15, OnRadio15)
	ON_BN_CLICKED(IDC_RADIO16, OnRadio16)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobTestDlg message handlers

BOOL CRobTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Pareja_1=0;
	m_Pareja_2=0;
	m_Pareja_3=0;

	SetTimer(1000,1000,NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRobTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRobTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CRobTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRobTestDlg::OnRadio1() 
{
	m_Pareja=1;
    m_Pareja_1^=1;
	AjustRadio();
}

void CRobTestDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=1;
	m_Pareja_1^=2;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=1;
	m_Pareja_1^=4;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=1;
	m_Pareja_1^=8;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=1;
	m_Pareja_1^=16;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio6() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=1;
	m_Pareja_1^=32;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio7() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=1;
	m_Pareja_1^=64;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio8() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=1;
	m_Pareja_1^=128;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio17() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=2;
	m_Pareja_2^=1;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio18() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=2;
	m_Pareja_2^=2;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio19() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=2;
	m_Pareja_2^=4;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio20() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=2;
	m_Pareja_2^=8;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio21() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=2;
	m_Pareja_2^=16;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio22() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=2;
	m_Pareja_2^=32;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio23() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=2;
	m_Pareja_2^=64;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio24() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=2;
	m_Pareja_2^=128;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio9() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=3;
	m_Pareja_3^=1;
	AjustRadio();

	
}

void CRobTestDlg::OnRadio10() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=3;
	m_Pareja_3^=2;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio11() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=3;
	m_Pareja_3^=4;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio12() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=3;
	m_Pareja_3^=8;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio13() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=3;
	m_Pareja_3^=16;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio14() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=3;
	m_Pareja_3^=32;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio15() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=3;
	m_Pareja_3^=64;
	AjustRadio();
	
}

void CRobTestDlg::OnRadio16() 
{
	// TODO: Add your control notification handler code here
	m_Pareja=3;
	m_Pareja_3^=128;
	AjustRadio();
	
}

void CRobTestDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	
}

void CRobTestDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
}

void CRobTestDlg::AjustRadio()
{
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(m_Pareja_1&1);	
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(m_Pareja_1&2);	
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(m_Pareja_1&4);	
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(m_Pareja_1&8);	
	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(m_Pareja_1&16);	
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(m_Pareja_1&32);	
	((CButton*)GetDlgItem(IDC_RADIO7))->SetCheck(m_Pareja_1&64);	
	((CButton*)GetDlgItem(IDC_RADIO8))->SetCheck(m_Pareja_1&128);	
	
	((CButton*)GetDlgItem(IDC_RADIO17))->SetCheck(m_Pareja_2&1);	
	((CButton*)GetDlgItem(IDC_RADIO18))->SetCheck(m_Pareja_2&2);	
	((CButton*)GetDlgItem(IDC_RADIO19))->SetCheck(m_Pareja_2&4);	
	((CButton*)GetDlgItem(IDC_RADIO20))->SetCheck(m_Pareja_2&8);	
	((CButton*)GetDlgItem(IDC_RADIO21))->SetCheck(m_Pareja_2&16);	
	((CButton*)GetDlgItem(IDC_RADIO22))->SetCheck(m_Pareja_2&32);	
	((CButton*)GetDlgItem(IDC_RADIO23))->SetCheck(m_Pareja_2&64);	
	((CButton*)GetDlgItem(IDC_RADIO24))->SetCheck(m_Pareja_2&128);	
	
	((CButton*)GetDlgItem(IDC_RADIO9))->SetCheck(m_Pareja_3&1);	
	((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(m_Pareja_3&2);	
	((CButton*)GetDlgItem(IDC_RADIO11))->SetCheck(m_Pareja_3&4);	
	((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(m_Pareja_3&8);	
	((CButton*)GetDlgItem(IDC_RADIO13))->SetCheck(m_Pareja_3&16);	
	((CButton*)GetDlgItem(IDC_RADIO14))->SetCheck(m_Pareja_3&32);	
	((CButton*)GetDlgItem(IDC_RADIO15))->SetCheck(m_Pareja_3&64);	
	((CButton*)GetDlgItem(IDC_RADIO16))->SetCheck(m_Pareja_3&128);	
	
	_outp(0x378,m_Pareja_1);
	_outp(0x378,m_Pareja_1);
	_outp(0x37A,0x0b);
	_outp(0x37A,0x0b);
	_outp(0x37A,0x04);
	_outp(0x37A,0x04);

	_outp(0x378,m_Pareja_2);
	_outp(0x378,m_Pareja_2);
	_outp(0x37A,0x0f);
	_outp(0x37A,0x0f);
	_outp(0x37A,0x07);
	_outp(0x37A,0x07);

	_outp(0x378,m_Pareja_3);
	_outp(0x378,m_Pareja_3);
	_outp(0x37A,0x03);
	_outp(0x37A,0x03);
	_outp(0x37A,0x07);
	_outp(0x37A,0x07);
	
}

void CRobTestDlg::OnTimer(UINT nIDEvent) 
{
	if (!((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
		return;
	m_Pos=0xff;
	switch(m_Pareja)
	{
	case 1:
		{
			m_Pareja_1^=m_Pos;
			break;
		}
	case 2:
		{
			m_Pareja_2^=m_Pos;
			break;
		}
	case 3:
		{
			m_Pareja_3^=m_Pos;
			break;
		}
	}
	AjustRadio();
	CDialog::OnTimer(nIDEvent);
}
