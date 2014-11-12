// AsmFilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AsmFilter.h"
#include "AsmFilterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAsmFilterDlg dialog

CAsmFilterDlg::CAsmFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAsmFilterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAsmFilterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsmFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAsmFilterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAsmFilterDlg, CDialog)
	//{{AFX_MSG_MAP(CAsmFilterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnDoIt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAsmFilterDlg message handlers

BOOL CAsmFilterDlg::OnInitDialog()
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

void CAsmFilterDlg::OnPaint() 
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
HCURSOR CAsmFilterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAsmFilterDlg::OnDoIt() 
{
	HANDLE m_hInFile;
	HANDLE m_hOutFile;
	char*	Filter = "All files (*.*)\0*.*\0\0";
	char	filename[300];

	filename[0]=0;
	OPENFILENAME ofn;
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.Flags = OFN_CREATEPROMPT|OFN_HIDEREADONLY|OFN_NONETWORKBUTTON|
				OFN_OVERWRITEPROMPT;
	ofn.hInstance = NULL;
	ofn.lCustData = NULL;
	ofn.lpfnHook = NULL;
	ofn.lpstrCustomFilter = NULL;
	ofn.lpstrDefExt = NULL;
	ofn.lpstrFile = filename;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrFilter = (char*)Filter;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = "Select input file";
	ofn.lpTemplateName = NULL;
	ofn.nFileExtension = NULL;
	ofn.nFileOffset = NULL;
	ofn.nFilterIndex = 1;
	ofn.nMaxCustFilter = 0;
	ofn.nMaxFile = 299;
	ofn.nMaxFileTitle = 10;
	if (!GetOpenFileName(&ofn)) return;
	m_hInFile = CreateFile(ofn.lpstrFile,GENERIC_READ,FILE_SHARE_READ,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	// Seleccionar fichero de salida

	filename[0]=0;
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.Flags = OFN_CREATEPROMPT|OFN_HIDEREADONLY|OFN_NONETWORKBUTTON|
				OFN_OVERWRITEPROMPT;
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
	if (!GetSaveFileName(&ofn)) return;
	m_hOutFile = CreateFile(ofn.lpstrFile,GENERIC_WRITE,FILE_SHARE_READ,NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	
	
	BYTE Buffer[100];
	DWORD CantRead,i,CantWrite;
	BOOL OnIgnore;		// Indica que deben ser ignorados todos los bytes hasta el fin de linea
	DWORD Pos;
	OnIgnore = false;  
	Pos = 0;

	while(ReadFile(m_hInFile,Buffer,99,&CantRead,NULL))
	{
		if (!CantRead)
		{
			break;
		}
		for (i=0;i<CantRead;i++)
		{
			BYTE car = Buffer[i];
			if (car == ';')
			{
				OnIgnore = true;
				continue;
			}
			if (OnIgnore)
			{
				if ((car == 0x0a) || (car == 0x0d))
				{
					OnIgnore = false;
					if (Pos == 0) continue;
				}
				else
					continue;
			}
			if ((car == 0x0a) || (car == 0x0d))
			{
				if (Pos == 0) continue;
			}
			Pos++;
			WriteFile(m_hOutFile,&Buffer[i],1,&CantWrite,NULL);
			if (car == 0x0a) Pos = 0;

		}
	}
	CloseHandle(m_hInFile);
	CloseHandle(m_hOutFile);
}
