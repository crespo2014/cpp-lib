// TestDLLsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDLLs.h"
#include "TestDLLsDlg.h"
#include "classfactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

	SV_CRV crv;

/////////////////////////////////////////////////////////////////////////////
// CTestDLLsDlg dialog

CTestDLLsDlg::CTestDLLsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDLLsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDLLsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_IServo = NULL;
	m_ISerialPort = NULL;
}

void CTestDLLsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDLLsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDLLsDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDLLsDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SERIALPORT, OnSerialport)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SV300, OnSv300)
	ON_BN_CLICKED(IDC_ATTACH, OnAttach)
	ON_BN_CLICKED(IDC_RC, OnRc)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDLLsDlg message handlers

BOOL CTestDLLsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDLLsDlg::OnPaint() 
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

HCURSOR CTestDLLsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDLLsDlg::OnSerialport() 
{
	DWORD dr;
	dr = CreateInstance("SerialPort32.dll","ISerialPort",(_IUnknown**)&m_ISerialPort);	
	if (dr != 0)
		MessageBox("Error creating instance");
	
	
}

void CTestDLLsDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	if (m_IServo) DeleteInstance(m_IServo);
	if (m_ISerialPort) DeleteInstance(m_ISerialPort);
	m_ISerialPort = NULL;

}

void CTestDLLsDlg::OnSv300() 
{
	DWORD dr;
	dr = CreateInstance("SV300.dll","IServo",(_IUnknown**)&m_IServo);	
	if (dr != 0)	MessageBox("Error creating instance");
	dr = m_IServo->Initialize();
	if (dr != 0)	MessageBox("Error initializing serial port");
}

void CTestDLLsDlg::OnAttach() 
{
	DWORD dr;
	dr = m_ISerialPort->Attach(m_IServo);
	if (dr != 0)	
		MessageBox("Error attaching instance");
	dr = m_ISerialPort->Initialize();
	if (dr != 0)	
		MessageBox("Error initializing instance");
	dr = m_ISerialPort->SetPort(1);
	dr = m_ISerialPort->OpenPort();
}

void CTestDLLsDlg::OnRc() 
{
	SV_CRV	graph[3];
	m_IServo->RequestCommand(SV_READCURVES,&graph);	
}


void CTestDLLsDlg::OnButton1() 
{
	SetTimer(0,1000,NULL);	
}

void CTestDLLsDlg::OnTimer(UINT nIDEvent) 
{
//	m_IServo->RequestCommand(SV_CHECKCONNECTION,NULL);
	static bool first=true;
	if (first)
	{
		DWORD dr;
		dr = m_IServo->InitializeDevice();
		if (dr != 0) return;
		first = false;
	}
	bool alarm;
	m_IServo->RequestCommand(SV_ALARMSTATUS,&alarm);	
	//m_IServo->RequestCommand(SV_READCURVES,&crv);	
	//m_IServo->RequestCommand(SV_READPARAMS,NULL);	
	CDialog::OnTimer(nIDEvent);
}
