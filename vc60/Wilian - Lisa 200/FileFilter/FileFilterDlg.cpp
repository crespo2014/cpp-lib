// FileFilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileFilter.h"
#include "FileFilterDlg.h"

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
	CString string;

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
// CFileFilterDlg dialog

CFileFilterDlg::CFileFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileFilterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileFilterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileFilterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileFilterDlg, CDialog)
	//{{AFX_MSG_MAP(CFileFilterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BTN_DOIT, OnDoit)
	ON_BN_CLICKED(BTN_INFILE, OnInfile)
	ON_BN_CLICKED(BTN_OUTFILE, OnOutfile)
	ON_BN_CLICKED(CHK_05, OnEnableCommand)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(CHK_06, OnEnableCommand)
	ON_BN_CLICKED(CHK_07, OnEnableCommand)
	ON_BN_CLICKED(CHK_08, OnEnableCommand)
	ON_BN_CLICKED(CHK_10, OnEnableCommand)
	ON_BN_CLICKED(CHK_0F, OnEnableCommand)
	ON_BN_CLICKED(CHK_12, OnEnableCommand)
	ON_BN_CLICKED(CHK_13, OnEnableCommand)
	ON_BN_CLICKED(CHK_14, OnEnableCommand)
	ON_BN_CLICKED(CHK_BUSY, OnEnableCommand)
	ON_BN_CLICKED(BTN_RESULT, OnResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileFilterDlg message handlers

BOOL CFileFilterDlg::OnInitDialog()
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
	Initialize();
	SetTimer(0,1000,NULL);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileFilterDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileFilterDlg::OnPaint() 
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
HCURSOR CFileFilterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileFilterDlg::OnDoit() 
{
	BYTE Buffer[100];
	DWORD CantRead,i;
	BYTE  Val;			// Valor del numero leido
	BYTE Valor;
	DWORD LinePos;		// Posicion dentro de la linea que se esta procesando
	char TmpBuf[10];	// Buffer temporal que almacena valores para su posterior uso
	BOOL OnRcv;			// Indica que se esta reciviendo informacion
	BOOL OnIgnore;		// Indica que deben ser ignorados todos los bytes hasta el fin de linea
	BOOL OnHiChar;
	LinePos = 0;
	OnHiChar = false;
	OnIgnore = false;      

	// Limpiar el listBox
	HWND hControl = ::GetDlgItem(m_hWnd,LBX_FILTER);
	::SendMessage(hControl,LB_RESETCONTENT,0,0);

	::SetFilePointer(m_hInFile,0,0,FILE_BEGIN);
	while(ReadFile(m_hInFile,Buffer,99,&CantRead,NULL))
	{
		if (!CantRead)
		{
			break;
		}
		for (i=0;i<CantRead;i++)
		{
			LinePos++;
			Valor = Buffer[i]; 
			if (Valor == 0x0a)
			{
				// Fin de linea
				LinePos = 0;
				OnIgnore = false;
				OnHiChar = false;
			}
			else
			switch (LinePos)
			{
			case 1:
			case 2:
			case 3:
				{
					TmpBuf[LinePos-1] = Buffer[i];
					break;
				}
			case 4:
				{
					TmpBuf[3] = 0;
					if (strcmp(TmpBuf,"Rcv") == 0)
					{
						OnRcv = true;
						break;
					}
					if (strcmp(TmpBuf,"Snd") == 0)
					{
						OnRcv = false;
						break;
					}
					if (strcmp(TmpBuf,"Cmt") == 0)
					{
						OnIgnore = true;
						break;
					}
					TmpBuf[2]=0;
					if (strcmp(TmpBuf,"//") == 0)
					{
						OnIgnore = true;
						break;
					}
					// Se queda en el ultimo estado que estaba
//					strcat(OutBuffer,"Error");
//					OnIgnore = true;
					break;
				}
			default:
				{
					if (OnIgnore) break;
					if (LinePos>57) break;
					if (Buffer[i]==' ') break;
					if ((Buffer[i] >= '0') && (Buffer[i] <= 'F'))
					{
						BYTE tmpval;
						if (Buffer[i] > '9') tmpval = Buffer[i]-'A'+10;
						else
							tmpval = Buffer[i]-'0';
						if (OnHiChar) 
							Val = Val*16+tmpval;
						else
							Val = tmpval;
						OnHiChar = !OnHiChar;
						if (!OnHiChar)
						{
							DWORD result;
							if (OnRcv)
								result = LisaFilter.ProcessRcvByte(Val);
							else
								result = LisaFilter.ProcessSndByte(Val);
							if (result == 2)
								ProcessFilter();
						}
					}
					break;
				}
			}
		} 
	}
	//CloseHandle(m_hInFile);
	CloseOutFile();
}

DWORD CFileFilterDlg::CloseOutFile()
{
	CloseHandle(m_hOutFile);
	m_hOutFile = NULL;
	return 0;
}

DWORD CFileFilterDlg::Initialize()
{
	m_hOutFile = NULL;
	m_hInFile = NULL;
	OnEnableCommand();
	return 0;
}

DWORD CFileFilterDlg::CloseInFile()
{
	CloseHandle(m_hInFile);
	m_hInFile = NULL;
	return 0;
}

void CFileFilterDlg::OnInfile() 
{
	char*	Filter = "Text files (*.TXT)\0*.txt\0All files (*.*)\0*.*\0\0";
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
	CloseHandle(m_hInFile);
	m_hInFile = CreateFile(ofn.lpstrFile,GENERIC_READ,FILE_SHARE_READ,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	return;
}

void CFileFilterDlg::OnOutfile() 
{
	char*	Filter = "Text files (*.TXT)\0*.txt\0All files (*.*)\0*.*\0\0";
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
	ofn.lpstrTitle = "Select file to save traffic";
	ofn.lpTemplateName = NULL;
	ofn.nFileExtension = NULL;
	ofn.nFileOffset = NULL;
	ofn.nFilterIndex = 1;
	ofn.nMaxCustFilter = 0;
	ofn.nMaxFile = 299;
	ofn.nMaxFileTitle = 10;
	if (!GetSaveFileName(&ofn)) return;
	CloseHandle(m_hOutFile);
	m_hOutFile = CreateFile(ofn.lpstrFile,GENERIC_WRITE,FILE_SHARE_READ,NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	return;
}

DWORD CFileFilterDlg::PrintHexValue(BYTE value, char *str)
{
	char tmp[3];
	tmp[0]=(value >> 4) + '0'; 
	tmp[1] = (value & 0x0F) + '0';

	if (tmp[0] > '9') tmp[0] += 7;
	if (tmp[1] > '9') tmp[1] += 7;
	tmp[2] = 0;
	strcat(str,tmp);
	return 0;	
}

DWORD CFileFilterDlg::ProcessFilter()
{
	DWORD SPos,EPos;	// Posicion de inicio y fin
	LRESULT Index;
	// Procesar el buffer
	HWND hControl = ::GetDlgItem(m_hWnd,LBX_FILTER);
	for (SPos = 0,EPos=0;;EPos++)
	{
		if (LisaFilter.m_OutStr[EPos] == 0) break;
		if (LisaFilter.m_OutStr[EPos] == 0x0d)
		{
			LisaFilter.m_OutStr[EPos] = 0;
			::SendMessage(hControl,LB_ADDSTRING,0,(long)&LisaFilter.m_OutStr[SPos]);
			Index =::SendMessage(hControl,LB_GETCOUNT,0,0);
			::SendMessage(hControl,LB_SETCURSEL,Index-1,0);
			EPos++;
			SPos = EPos+1;
		}
	}
	if (m_hOutFile)
		LisaFilter.SaveToFile(m_hOutFile);
	return 0;
}


void CFileFilterDlg::OnEnableCommand() 
{
	HWND	hcontrol;
	LRESULT result;
	hcontrol = ::GetDlgItem(m_hWnd,CHK_05);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	LisaFilter.EnableCommand(0x05,result & BST_CHECKED);

	hcontrol = ::GetDlgItem(m_hWnd,CHK_06);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	LisaFilter.EnableCommand(0x06,result & BST_CHECKED);

	hcontrol = ::GetDlgItem(m_hWnd,CHK_07);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	LisaFilter.EnableCommand(0x07,result & BST_CHECKED);

	hcontrol = ::GetDlgItem(m_hWnd,CHK_08);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	LisaFilter.EnableCommand(0x08,result & BST_CHECKED);

	hcontrol = ::GetDlgItem(m_hWnd,CHK_10);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	LisaFilter.EnableCommand(0x10,result & BST_CHECKED);

	hcontrol = ::GetDlgItem(m_hWnd,CHK_0F);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	LisaFilter.EnableCommand(0x0F,result & BST_CHECKED);

	hcontrol = ::GetDlgItem(m_hWnd,CHK_12);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	LisaFilter.EnableCommand(0x12,result & BST_CHECKED);

	hcontrol = ::GetDlgItem(m_hWnd,CHK_13);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	LisaFilter.EnableCommand(0x13,result & BST_CHECKED);

	hcontrol = ::GetDlgItem(m_hWnd,CHK_14);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	LisaFilter.EnableCommand(0x14,result & BST_CHECKED);

	hcontrol = ::GetDlgItem(m_hWnd,CHK_BUSY);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	LisaFilter.EnableCommand(0x0,result & BST_CHECKED);
	
}

void CFileFilterDlg::OnClose() 
{
	CloseInFile();
	CDialog::OnClose();
}

void CFileFilterDlg::OnTimer(UINT nIDEvent) 
{
	
	CDialog::OnTimer(nIDEvent);
}

void CFileFilterDlg::OnResult() 
{
	HWND	hcontrol;
	hcontrol = ::GetDlgItem(m_hWnd,LB_RESULT);
	LisaFilter.FillListBox(hcontrol);
}
