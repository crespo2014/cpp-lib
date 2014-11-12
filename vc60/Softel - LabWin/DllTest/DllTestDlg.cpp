// DllTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DllTest.h"
#include "DllTestDlg.h"
#include "factory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDllTestDlg dialog

CDllTestDlg::CDllTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDllTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDllTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDllTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDllTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDllTestDlg, CDialog)
	//{{AFX_MSG_MAP(CDllTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDllTestDlg message handlers

BOOL CDllTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDllTestDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDllTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDllTestDlg::OnButton1() 
{
	DWORD dr;
	char*	Filter = "DLL files (*.dll)\0*.dll\0\0";
	char	filename[300];
	
	filename[0]=0;
	OPENFILENAME ofn;
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.Flags = OFN_HIDEREADONLY|OFN_NONETWORKBUTTON|
				OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
	ofn.hInstance = NULL;
	ofn.lCustData = NULL;
	ofn.lpfnHook = NULL;
	ofn.lpstrCustomFilter = NULL;
	ofn.lpstrDefExt = NULL;
	ofn.lpstrFile = filename;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrFilter = (char*)Filter;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = "Select file to save traffic";
	ofn.lpTemplateName = NULL;
	ofn.nFileExtension = NULL;
	ofn.nFileOffset = NULL;
	ofn.nFilterIndex = 1;
	ofn.nMaxCustFilter = 0;
	ofn.nMaxFile = 299;
	ofn.nMaxFileTitle = 10;
	if (!GetOpenFileName(&ofn)) return;
	dr = CreateInstance(ofn.lpstrFile,"ILabDevice",(_IUnknown**)&m_LabDevice);
}

void CDllTestDlg::OnButton2() 
{
	if (!m_LabDevice) return;
	char*	Filter = "All files (*.*)\0*.*\0\0";
	char	filename[300];
	
	filename[0]=0;
	OPENFILENAME ofn;
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.Flags = OFN_HIDEREADONLY|OFN_NONETWORKBUTTON|
				OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
	ofn.hInstance = NULL;
	ofn.lCustData = NULL;
	ofn.lpfnHook = NULL;
	ofn.lpstrCustomFilter = NULL;
	ofn.lpstrDefExt = NULL;
	ofn.lpstrFile = filename;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrFilter = (char*)Filter;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = "Select file to save traffic";
	ofn.lpTemplateName = NULL;
	ofn.nFileExtension = NULL;
	ofn.nFileOffset = NULL;
	ofn.nFilterIndex = 1;
	ofn.nMaxCustFilter = 0;
	ofn.nMaxFile = 299;
	ofn.nMaxFileTitle = 10;
	if (!GetOpenFileName(&ofn)) return;
	m_LabDevice->ProcessFile(ofn.lpstrFile);	
}
