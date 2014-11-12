// dbQueryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dbQuery.h"
#include "dbQueryDlg.h"
#include "errorcodes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbQueryDlg dialog

CDbQueryDlg::CDbQueryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDbQueryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDbQueryDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_lpICommand = NULL;
}

void CDbQueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDbQueryDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDbQueryDlg, CDialog)
	//{{AFX_MSG_MAP(CDbQueryDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnConectar)
	ON_BN_CLICKED(IDC_BUTTON2, OnEjecutar)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbQueryDlg message handlers

BOOL CDbQueryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Grid.Initialize();
	m_Grid.SetDBArray(&m_MemArray);
	m_Grid.Create(WS_VISIBLE|WS_CHILD,WS_EX_CLIENTEDGE,10,70,550,210,0,GetSafeHwnd());
	::SendMessage(m_Grid,GM_SHOWHEADER,false,0);
	m_MemArray.SetMaxSize(300*1024*1024);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDbQueryDlg::OnPaint() 
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
HCURSOR CDbQueryDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDbQueryDlg::OnConectar() 
{
	DWORD					rc;
	HRESULT					hr;
	IDataInitialize *		pIDataInitialize    = NULL;
	IDBInitialize *			pIDBInitialize      = NULL;
	IDBCreateSession*		pIDBCreateSession	= NULL;
	IUnknown *				pUnkSession			= NULL;
	ICommandText*			pICommandText		= NULL;
	IDBCreateCommand*		pICreateCommand		= NULL;
	OLECHAR					connectstr[200];
	IDBPromptInitialize*	pIDBPromptInitialize;
	/*
	HWND hconnectEdit;
	GetDlgItem(EDT_CONNECT,&hconnectEdit);
	::GetWindowText(hconnectEdit,(char*)connectstr,200);
	db_CharToWChar((char*)connectstr);
	*/
	if (m_lpICommand) rc = m_lpICommand->Release();
	for(;;)
	{
		hr = CoCreateInstance(CLSID_DataLinks, NULL, CLSCTX_INPROC_SERVER,IID_IDBPromptInitialize, (void **)&pIDBPromptInitialize);
		if (hr != S_OK) break;
		hr = pIDBPromptInitialize->PromptDataSource(NULL, GetSafeHwnd(),DBPROMPTOPTIONS_PROPERTYSHEET, 0, NULL, NULL, IID_IDBInitialize,(IUnknown **)&pIDBInitialize);
		if (hr != S_OK) break;
		hr = pIDBInitialize->Initialize();
		if (hr != S_OK) break;
		/*
		hr = CoCreateInstance(CLSID_MSDAINITIALIZE,NULL,CLSCTX_INPROC_SERVER,IID_IDataInitialize,(VOID **)&pIDataInitialize);
		if (hr != S_OK) break;
		hr = pIDataInitialize->GetDataSource(NULL,CLSCTX_INPROC_SERVER,connectstr,IID_IDBInitialize,(IUnknown **)&pIDBInitialize);
		if (hr != S_OK) break;
		hr = pIDBInitialize->Initialize();
		*/
		if (hr != S_OK) break;
		hr = pIDBInitialize->QueryInterface(IID_IDBCreateSession, (void**)&pIDBCreateSession);
		if (hr != S_OK) break;
		hr = pIDBCreateSession->CreateSession(NULL,IID_IOpenRowset,&pUnkSession );
		if (hr != S_OK) break;
		hr = pUnkSession->QueryInterface(IID_IDBCreateCommand,(void**)&pICreateCommand);
		if (hr != S_OK) break;
		hr = pICreateCommand->CreateCommand(NULL,IID_ICommand,(IUnknown**)&m_lpICommand);
		if (hr != S_OK) break;
		break;
	};
	if (pIDBPromptInitialize)
		pIDBPromptInitialize->Release();
	if (pIDataInitialize)
		rc = pIDataInitialize->Release();
	if (pIDBInitialize)
		rc = pIDBInitialize->Release();
	if (pIDBCreateSession)
		rc = pIDBCreateSession->Release();
	if (pUnkSession)
		rc = pUnkSession->Release();
	if (pICreateCommand)
		rc = pICreateCommand->Release();
	if (hr == S_OK) 
	{
		MessageBox("Open Database OK");
		return;
	}
	if (m_lpICommand)
		rc = m_lpICommand->Release();
	m_lpICommand = NULL;
	MessageBox("Open Database Failed");
}

void CDbQueryDlg::OnEjecutar() 
{
	// preparar consulta
	DWORD			dr;
	DWORD			rc;	// Reference count
	long			pRowsCant;
	HRESULT			hr;
	IRowset*		pIRowset		= NULL;
	ICommandText*	pICommandText	= NULL;
	OLECHAR			querystr[200];
	HWND			hqueryEdit;
	for(;;)
	{
		hr = m_lpICommand->QueryInterface(IID_ICommandText,(void**)&pICommandText);
		if (hr != S_OK) break;
		GetDlgItem(EDT_QUERY,&hqueryEdit);
		::GetWindowText(hqueryEdit,(char*)querystr,200);
		db_CharToWChar((char*)querystr);
		hr = pICommandText->SetCommandText(DBGUID_DEFAULT,querystr);
		if (hr != S_OK) break;
		hr = m_lpICommand->Execute(NULL,IID_IRowset,NULL,&pRowsCant,(IUnknown **)&pIRowset);
		if (hr != S_OK) break;
		dr = m_MemArray.ResetContent();
		dr = m_MemArray.SetData(pIRowset,MA_F_NO_READ_DBINFO);

		dr = m_Grid.InvalidateData();
		break;
	};
	if (pICommandText)
		rc = pICommandText->Release();
	if (pIRowset)
		rc = pIRowset->Release();
	if ((hr == S_OK) && (dr == ERR_NONE)) 
	{
		char	str[100];
		sprintf(str,"%d records",m_MemArray.GetRowCount());
		MessageBox(str);
		return;
	}
	if (hr != S_OK) dr = ERR_OLEDBFAIL;
	MessageBox("Failed to get records");
	m_MemArray.ResetContent();
}

void CDbQueryDlg::OnButton3() 
{
	::SendMessage(m_Grid,GM_SHOWHEADER,true,0);	
}

void CDbQueryDlg::OnButton4() 
{
	::SendMessage(m_Grid,GM_SHOWHEADER,false,0);	
}

void CDbQueryDlg::OnButton5() 
{
	m_Grid.ShowScrollBar(SB_HORZ,false);	
}

  

void CDbQueryDlg::OnOK() 
{
	_asm
	{
		mov dx,0x378;
		out dx,al;
	}
	CDialog::OnOK();
}
