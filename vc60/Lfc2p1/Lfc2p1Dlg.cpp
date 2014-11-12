// Lfc2p1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lfc2p1.h"
#include "Lfc2p1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLfc2p1Dlg dialog

CLfc2p1Dlg::CLfc2p1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLfc2p1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLfc2p1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLfc2p1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLfc2p1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLfc2p1Dlg, CDialog)
	//{{AFX_MSG_MAP(CLfc2p1Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnOpen)
	ON_BN_CLICKED(IDC_BUTTON2, OnCreate)
	ON_BN_CLICKED(IDC_BUTTON3, OnWait)
	ON_BN_CLICKED(IDC_BUTTON4, OnSet)
	ON_BN_CLICKED(IDC_BUTTON5, OnRun)
	ON_BN_CLICKED(IDC_BUTTON6, OnBeep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLfc2p1Dlg message handlers

BOOL CLfc2p1Dlg::OnInitDialog()
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

void CLfc2p1Dlg::OnPaint() 
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
HCURSOR CLfc2p1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CLfc2p1Dlg::OnOpen() 
{
	if (m_SSignalDevice.Open()!=0)
	{
		AfxMessageBox("Error");
		return;
	}
	m_hevent=::OpenEvent(EVENT_ALL_ACCESS,TRUE,"evento");
}

void CLfc2p1Dlg::OnCreate() 
{
	SECURITY_ATTRIBUTES	sa;
	ZeroMemory(&sa,sizeof(sa));
	sa.nLength=sizeof(sa);
	sa.bInheritHandle=TRUE;
	m_hevent=::CreateEvent(&sa,FALSE,FALSE,"evento");

	if(m_SSignalDevice.Create()!=0)
		AfxMessageBox("Error");
}

void CLfc2p1Dlg::OnWait() 
{
	/*
	if(m_SSignalDevice.lpSignalDevice==NULL)
		AfxMessageBox("Error");
	for (int i=0;i<12;i++)
	{
		m_SSignalDevice.lpSignalDevice->WaitMessage();
		MessageBeep(-1);
	}
	*/
	WaitForSingleObject(m_hevent,INFINITE);
	WaitForSingleObject(m_hevent,INFINITE);
	EndDialog(0);
}

void CLfc2p1Dlg::OnSet() 
{
	SetEvent(m_hevent);
	/*
	if(m_SSignalDevice.lpSignalDevice==NULL)
	{
		AfxMessageBox("Error");
		return;
	}
	if (!SetEvent(m_SSignalDevice.lpSignalDevice->hSendEvent))
		AfxMessageBox("Set Event Failed");
	if (!SetEvent(m_SSignalDevice.lpSignalDevice->hSendEvent))
		AfxMessageBox("Set Event Failed");
		*/
	
}

void CLfc2p1Dlg::OnRun() 
{
	STARTUPINFO	StartupInfo;
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi,sizeof(pi));
	ZeroMemory(&StartupInfo,sizeof(StartupInfo));
	StartupInfo.cb=sizeof(StartupInfo);
	StartupInfo.lpReserved=NULL;
	StartupInfo.lpDesktop=NULL;
	StartupInfo.lpTitle=NULL;
	StartupInfo.dwX=0;
	StartupInfo.dwY=0;
	StartupInfo.dwXSize=0;
	StartupInfo.dwYSize=0;
	StartupInfo.dwXCountChars=0;
	StartupInfo.dwYCountChars=0;
	StartupInfo.dwFillAttribute =0;
	StartupInfo.dwFlags =0;
	StartupInfo.wShowWindow =SW_SHOWDEFAULT;
	StartupInfo.cbReserved2 =0;
	StartupInfo.lpReserved2=NULL;
	StartupInfo.hStdInput=NULL;
	StartupInfo.hStdOutput=NULL;
	StartupInfo.hStdError =NULL;

	::CreateProcess("c:\lfc2p1.exe",
					NULL,
					NULL,
					NULL,
					TRUE,
					0,
					NULL,
					NULL,
					&StartupInfo,
					&pi);

}

void CLfc2p1Dlg::OnBeep() 
{
	MessageBeep(-1);	
}
