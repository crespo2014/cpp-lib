// puertoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "puerto.h"
#include "puertoDlg.h"

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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPuertoDlg dialog

CPuertoDlg::CPuertoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPuertoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPuertoDlg)
	m_estado = _T("");
	m_curvas = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPuertoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPuertoDlg)
	DDX_Text(pDX, IDC_ESTADO, m_estado);
	DDX_Text(pDX, IDC_CURVAS, m_curvas);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPuertoDlg, CDialog)
	//{{AFX_MSG_MAP(CPuertoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnOpen)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPuertoDlg message handlers

BOOL CPuertoDlg::OnInitDialog()
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetTimer(1,500,NULL);
	Driver.Initialize();
	Driver.GetServoForBed(1,&lpServo);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPuertoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPuertoDlg::OnPaint() 
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
HCURSOR CPuertoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPuertoDlg::OnOpen() 
{
	Driver.SetCommunicationPort(2);
	Driver.StartCommunication();
}

void CPuertoDlg::OnTimer(UINT nIDEvent) 
{
	switch (lpServo->RequestGraph())
	{
	case COMMAND_OK:
		{
			lpServo->GetGraphs(NULL,NULL,NULL);
			m_curvas = "Curvas recibidas";
			break;
		}
	case COMMAND_TIMEOUT:
		{
			m_curvas = "Sin respuesta";
			break;
		}
	case COMMAND_INVALIDATA:
		{
			m_curvas = "Respuesta Incorrecta";
			break;
		}
		/*
	case COMMAND_UPDATING:
		{
			m_curvas = "Esperando respuesta";
			break;
		}
		*/
	}
	
/*
	
	switch (lpServo->IsConnect())
	{
	case CONNECTED:
		{
			m_estado = "Conectado";
			break;
		}
	case COMMAND_TIMEOUT:
		{
			m_estado = "Sin respuesta";
			break;
		}
	case COMMAND_INVALIDATA:
		{
			m_estado = "Respuesta Incorrecta";
			break;
		}
	case COMMAND_UPDATING:
		{
			m_estado = "Esperando respuesta";
			break;
		}
	}
*/
	UpdateData(false);
	CDialog::OnTimer(nIDEvent);
}
