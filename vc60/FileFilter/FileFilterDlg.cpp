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
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hFile = NULL;
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
	ON_BN_CLICKED(IDC_BTN_OPEN, OnOpenFile)
	ON_BN_CLICKED(IDC_BTN_PORTFILTER, OnPortMonFilter)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
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

HCURSOR CFileFilterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileFilterDlg::OnOpenFile() 
{
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
	m_File = fopen(ofn.lpstrFile,"r");
	if (m_File == NULL) ::MessageBox(NULL,"Open File Error","File Filter Mesage",MB_OK);
	/*
	m_hFile = CreateFile(ofn.lpstrFile,GENERIC_READ,FILE_SHARE_READ,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (m_hFile == INVALID_HANDLE_VALUE) ::MessageBox(NULL,"Open File Error","File Filter Mesage",MB_OK);
	*/
}

void CFileFilterDlg::OnPortMonFilter() 
{
	if (m_File == NULL) 
	{
		::MessageBox(NULL,"No File Select","File Filter Mesage",MB_OK);		
		return;
	}
	char	line[1024];
	char*	lineptr;
	DWORD	number;
	float	time;
	char	process[20];
	char	request[50];
	char	port[20];
	FILE*	outFile;
	int		scanCode;
	DWORD	op_code;
	char	tmp[50];
	char	filebuff[100];
	DWORD	read_pos = -1;

#define OP_NONE		0
#define OP_READ		1
#define OP_WRITE	2
#define OP_SETBAUD	3
#define OP_SETRTS	4
#define OP_SETDTR	5
#define OP_SETLINECTRL	6
#define OP_SETCHAR		7
#define OP_SETHANDFLOW	8
#define OP_PURGE		9
#define OP_CLRRTS		10
#define OP_CLRDTR		11
#define OP_SETMASK		12
#define OP_SETQUEUE		13
#define OP_SETTIMEOUTS	14
#define OP_SUCESS		15
#define OP_READSUCCESS	16


	outFile = fopen("c:\\PotMon.txt","w");
	if (outFile == NULL)
	{
		::MessageBox(NULL,"Failed To Create OutPut File","File Filter Mesage",MB_OK);		
		return;
	}
	for (;;)
	{
		if (fgets(line,1023,m_File) == NULL) break;
		scanCode = sscanf(line,"%d",&number);
		if (scanCode == 0) continue;			// Proxima linea
		lineptr = strchr(line,' ');				// Buscar el espacio
		lineptr = _tcsspnp(lineptr," ");		// Buscar el primer caracter
		scanCode = sscanf(lineptr,"%f",&time);
		lineptr = strchr(lineptr,' ');			// Buscar el espacio
		lineptr = _tcsspnp(lineptr," ");		// Buscar el primer caracter
		scanCode = sscanf(lineptr,"%s",process);
		lineptr = strchr(lineptr,' ');			
		lineptr = _tcsspnp(lineptr," ");
		if (strcmp(process,"SUCCESS") == 0) 
		{
			if (read_pos == number) 
				op_code = OP_READSUCCESS;
			else
				op_code = OP_SUCESS;
		}
		else
		{
			scanCode = sscanf(lineptr,"%s",request);
			lineptr = strchr(lineptr,' ');			
			if (lineptr == NULL) continue;
			lineptr = _tcsspnp(lineptr," ");
			if (lineptr == NULL) continue;
			scanCode = sscanf(lineptr,"%s",port);
			lineptr = strchr(lineptr,' ');
			if (lineptr == NULL) continue;
			lineptr = _tcsspnp(lineptr," ");
			op_code = OP_NONE;
			if (strcmp(request,"IRP_MJ_CREATE") == 0)					op_code	= OP_NONE;
			if (strcmp(request,"IOCTL_SERIAL_SET_QUEUE_SIZE") == 0)		op_code = OP_SETQUEUE;
			if (strcmp(request,"IOCTL_SERIAL_SET_TIMEOUTS") == 0)		op_code	= OP_SETTIMEOUTS;
			if (strcmp(request,"IOCTL_SERIAL_SET_BAUD_RATE") == 0)		op_code	= OP_SETBAUD;
			if (strcmp(request,"IOCTL_SERIAL_SET_RTS") == 0)			op_code	= OP_SETRTS;
			if (strcmp(request,"IOCTL_SERIAL_SET_DTR") == 0)			op_code = OP_SETDTR;
			if (strcmp(request,"IOCTL_SERIAL_SET_LINE_CONTROL") == 0)	op_code = OP_SETLINECTRL;
			if (strcmp(request,"IOCTL_SERIAL_SET_CHAR") == 0)			op_code = OP_SETCHAR;
			if (strcmp(request,"IOCTL_SERIAL_SET_HANDFLOW") == 0)		op_code = OP_SETHANDFLOW;
			if (strcmp(request,"IOCTL_SERIAL_PURGE") == 0)				op_code = OP_PURGE;
			if (strcmp(request,"IOCTL_SERIAL_CLR_RTS") == 0)			op_code = OP_CLRRTS;
			if (strcmp(request,"IRP_MJ_READ") == 0)						op_code = OP_READ;
			if (strcmp(request,"IRP_MJ_WRITE") == 0)					op_code = OP_WRITE;
			if (strcmp(request,"IOCTL_SERIAL_CLR_DTR") == 0)			op_code = OP_CLRDTR;
			if (strcmp(request,"IOCTL_SERIAL_SET_WAIT_MASK") == 0)		op_code = OP_SETMASK;
		}
		switch (op_code)
		{
		case OP_NONE:
			{
				break;
			}
#define SP0		7	// Cantidad de caracteres del tipo de bloque
#define SP1		1   // Cantidad de caracteres entre el tipo de bloque y el primer valor
#define SP2		1   // Cantidad de caracteres despues de cada valor
#define SP3		1	// Cantidad de espacios entre el ultimo byte y el primer ascii
		case OP_READ:
			{
				read_pos = number;
				break;
			}
		case OP_READSUCCESS:
			{
				int cant;
				int i;
				BYTE j;
				int val;
				
				lineptr = strchr(lineptr,' ');
				lineptr = _tcsspnp(lineptr," ");
				scanCode = sscanf(lineptr,"%d",&cant);
				lineptr = strchr(lineptr,':');	// Buscar dos puntos
				lineptr++;

				memset(filebuff,' ',SP0+SP1+(2+SP2)*16+SP3+16);
				filebuff[SP0+SP1+(2+SP2)*16+SP3+16] = 0;
				memcpy(filebuff,"Rcv ",4);
				j = 0;
				for (i=0;i<cant;i++)
				{
					// Modo hex
				//	lineptr = _tcsspnp(lineptr," ");
				//	scanCode = sscanf(lineptr,"%x",&val);
				//	lineptr = strchr(lineptr,' ');
					// Modo Ascii
					val = lineptr[0];
					lineptr++;
					

					filebuff[SP0+SP1+(2+SP2)*j] = (val >> 4) + '0';
					filebuff[SP0+SP1+(2+SP2)*j+1] = (val & 0x0F) + '0';
					if (filebuff[SP0+SP1+(2+SP2)*j] > '9') filebuff[SP0+SP1+(2+SP2)*j] += 7;
					if (filebuff[SP0+SP1+(2+SP2)*j+1] > '9') filebuff[SP0+SP1+(2+SP2)*j+1] += 7;
					if (val < 32) 
						filebuff[SP0+SP1+(2+SP2)*16+SP3+j] = '.';
					else
						filebuff[SP0+SP1+(2+SP2)*16+SP3+j] = val;
					j++;
					if ((j==16) || (i==cant-1))
					{
						fprintf(outFile,"\n");
						fprintf(outFile,filebuff);
						j = 0;
						memset(filebuff,' ',SP0+SP1+(2+SP2)*16+SP3+16);
					}
				}
				break;
			}
		case OP_WRITE:
			{
				int i;
				BYTE j;
				int cant;
				int val;

				scanCode = sscanf(lineptr,"%s %d",tmp,&cant);
				lineptr = strchr(lineptr,':');	// Buscar dos puntos
				lineptr++;
				memset(filebuff,' ',SP0+SP1+(2+SP2)*16+SP3+16);
				filebuff[SP0+SP1+(2+SP2)*16+SP3+16] = 0;
				memcpy(filebuff,"Snd ",4);
				j = 0;
				for (i=0;i<cant;i++)
				{
					// Modo Hex
			//		lineptr = _tcsspnp(lineptr," ");
			//		scanCode = sscanf(lineptr,"%x",&val);
			//		lineptr = strchr(lineptr,' ');
					//Modo ASCII
					val = lineptr[0];
					lineptr++;

					filebuff[SP0+SP1+(2+SP2)*j] = (val >> 4) + '0';
					filebuff[SP0+SP1+(2+SP2)*j+1] = (val & 0x0F) + '0';
					if (filebuff[SP0+SP1+(2+SP2)*j] > '9') filebuff[SP0+SP1+(2+SP2)*j] += 7;
					if (filebuff[SP0+SP1+(2+SP2)*j+1] > '9') filebuff[SP0+SP1+(2+SP2)*j+1] += 7;
					if (val < 32) 
						filebuff[SP0+SP1+(2+SP2)*16+SP3+j] = '.';
					else
						filebuff[SP0+SP1+(2+SP2)*16+SP3+j] = val;
					j++;
					if ((j==16) || (i==cant-1))
					{
						fprintf(outFile,"\n");
						fprintf(outFile,filebuff);
						j = 0;
						memset(filebuff,' ',SP0+SP1+(2+SP2)*16+SP3+16);
					}
				}
				break;
			}
		case OP_SETBAUD:
			{
				DWORD baud;
				scanCode = sscanf(lineptr,"%s %d",tmp,&baud);
				fprintf(outFile,"\nBaudRate = %d",baud);
				break;
			}
		case OP_SETDTR:
			{
				//fprintf(outFile,"\nDTR ON");
				break;
			}
		case OP_SETLINECTRL:
			{
				DWORD StopBits;
				char	Parity[10];
				DWORD	ByteSize;
				scanCode = sscanf(lineptr,"%s %d %s %s %s %d",tmp,&StopBits,tmp,Parity,tmp,&ByteSize);
				fprintf(outFile,"\nStopBits = %d Parity = %s WordLength = %d",StopBits,Parity,ByteSize);

				break;
			}
		case OP_SETCHAR:
			{
				int		ErrorChar;
				int		XonChar;
				int		XoffChar;
				int		EofChar;
				int		EvtChar;
				char*	pstr;
				pstr = strchr(lineptr,':');	// Buscar dos puntos
				lineptr = &pstr[1];
				scanCode = sscanf(lineptr,"%d",&EofChar);
				pstr = strchr(lineptr,':');
				lineptr = &pstr[1];
				scanCode = sscanf(lineptr,"%d",&ErrorChar);
				pstr = strchr(lineptr,':');
				lineptr = &pstr[1];
				//scanCode = sscanf(lineptr,"%d",&timeouts.ReadTotalTimeoutConstant);
				pstr = strchr(lineptr,':');
				lineptr = &pstr[1];
				scanCode = sscanf(lineptr,"%d",&EvtChar);
				pstr = strchr(lineptr,':');
				lineptr = &pstr[1];
				scanCode = sscanf(lineptr,"%d",&XonChar);
				pstr = strchr(lineptr,':');
				lineptr = &pstr[1];
				scanCode = sscanf(lineptr,"%d",&XoffChar);
				/*
				fprintf(outFile,"\nCaracteres ERROR = %d XON = %d XOFF = %d EOF = %d EVENT = %d",
						ErrorChar,XonChar,XoffChar,EofChar,EvtChar);
						*/
				break;
			}
		case OP_SETHANDFLOW:
			{
				break;
			}
		case OP_PURGE:
			{
				break;
			}
		case OP_CLRRTS:
			{
				//fprintf(outFile,"\nRTS OFF");
				break;
			}
		case OP_CLRDTR:
			{
				//fprintf(outFile,"\nDTR OFF");
				break;
			}
		case OP_SETMASK:
			{
				break;
			}
		case OP_SETQUEUE:
			{
				break;
			}
		case OP_SETTIMEOUTS:
			{
				COMMTIMEOUTS timeouts;
				char*	pstr;
				pstr = strchr(lineptr,':');	// Buscar dos puntos
				lineptr = &pstr[1];
				scanCode = sscanf(lineptr,"%d",&timeouts.ReadIntervalTimeout);
				pstr = strchr(lineptr,':');
				lineptr = &pstr[1];
				scanCode = sscanf(lineptr,"%d",&timeouts.ReadTotalTimeoutMultiplier);
				pstr = strchr(lineptr,':');
				lineptr = &pstr[1];
				scanCode = sscanf(lineptr,"%d",&timeouts.ReadTotalTimeoutConstant);
				pstr = strchr(lineptr,':');
				lineptr = &pstr[1];
				scanCode = sscanf(lineptr,"%d",&timeouts.WriteTotalTimeoutMultiplier);
				pstr = strchr(lineptr,':');
				lineptr = &pstr[1];
				scanCode = sscanf(lineptr,"%d",&timeouts.WriteTotalTimeoutConstant);
				/*
				fprintf(outFile,"\nTimeouts  RInterval = %d RMultiplier = %d RConstant = %d WMultiplier = %d WConstant = %d",
						timeouts.ReadIntervalTimeout,timeouts.ReadTotalTimeoutMultiplier,timeouts.ReadTotalTimeoutConstant,timeouts.WriteTotalTimeoutMultiplier,timeouts.WriteTotalTimeoutConstant);
				*/
				break;
			}
		}
	}
	fclose(outFile);
}

void CFileFilterDlg::OnBtnClose() 
{
	
}
