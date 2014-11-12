// IDUploadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IDUpload.h"
#include "IDUploadDlg.h"
#include "lotusnote.h"
#include "cifrado.h"
#include "filedriver.h"
#include "utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIDUploadDlg dialog

CIDUploadDlg::CIDUploadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIDUploadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIDUploadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIDUploadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIDUploadDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIDUploadDlg, CDialog)
	//{{AFX_MSG_MAP(CIDUploadDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnAdminLook)
	ON_BN_CLICKED(BTN_UPALL, OnUpload)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDUploadDlg message handlers

BOOL CIDUploadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	SetDlgItemText(EDT_AID,"C:\\Archivos de programa\\lotus\\notes\\data\\$dummy");
	SetDlgItemText(EDT_APWD,"dummy");
	SetDlgItemText(EDT_SRV,"sccor01.renfe.es");
	SetDlgItemText(EDT_IDPWD,"tonto");
	SetDlgItemText(EDT_IDFOLDER,"c:\\ids");

	
	
	// TODO: Add extra initialization here
	
	return FALSE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIDUploadDlg::OnPaint() 
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

HCURSOR CIDUploadDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIDUploadDlg::OnAdminLook() 
{

		
}

void CIDUploadDlg::OnUpload() 
{
//	WIN32_FIND_DATA	filedata;

	CLotusSection	section;
	CLotusDB		db(&section);
	CLotusNote		note(&db);
	CCifrado		cif;
	CFileDriver		files;

	char	admin_id[255];
	char	admin_pwd[50];
	char	ids_pwd[50];
	char	*ids_epwd;
	char	ids_folder[255];
	char	server[50];
	char	id_file[255];
	char	user_id[40];
	char*	emsg;
	char	*cptr;
	DWORD	dwr;
	WORD	index;
	BLOCKID blockid;
	int		idf_count;
	int		idf_pass;


	glog.SetConsoleOutput();
	cif.SetKey("Coged las rosas mientras podais veloz el tiempo vuela la misma flor que hoy admirais mañana estara muerta");
	cif.Key_Dec();
	

	GetDlgItemText(EDT_AID,admin_id,sizeof(admin_id));
	GetDlgItemText(EDT_APWD,admin_pwd,sizeof(admin_pwd));
	GetDlgItemText(EDT_IDPWD,ids_pwd,sizeof(ids_pwd));
	GetDlgItemText(EDT_SRV,server,sizeof(server));
	GetDlgItemText(EDT_IDFOLDER,ids_folder,sizeof(ids_folder));

	cif.Cifrar(ids_pwd,&ids_epwd);

	for (;;)
	{
		emsg = section.GetErrorMsg();
		if (section.NotesInit() != ERR_OK) break;

		if (section.Login(admin_id,admin_pwd) != ERR_OK) break;
		emsg = db.GetErrorMsg();
		if (db.OpenDBServer(server,"logon.nsf") != ERR_OK) break;
		// recorrer todos los ficheros de la carpeta
		emsg = files.GetErrorMsg();
		files.SetCurrentDir(ids_folder);
		if (files.FindFile("*.id") != ERR_OK) break;
		idf_count = 0;
		idf_pass = 0;
		
		for (dwr = ERR_OK;dwr == ERR_OK;dwr = files.NextFile())
		{
			idf_count ++;
			files.GetFilePath(id_file,sizeof(id_file));
			files.GetFileName(user_id,sizeof(user_id));
			cptr = user_id;
			cptr += (strlen(cptr)-3);
			*cptr = 0;
			section.To_LMBCS(user_id);
			//files.GetFileData(&filedata);
			if (section.Password_Check(id_file,ids_pwd) != ERR_OK) continue;
			if (note.Open("USERID",user_id)!= ERR_OK) continue;
						
			note.ItemSetText("idf_chg","0");
			note.ItemSetText("idf_p",ids_epwd);

			if (note.Attachment_GetInfo("UserID",&index,&blockid,NULL,NULL,NULL,NULL,NULL) == ERR_OK) 
				if (note.DetachFile(blockid) != ERR_OK) continue;
			if (note.AttachmentAdd(id_file,"UserID") != ERR_OK) continue;
			if (note.Update() != ERR_OK) continue;
			idf_pass++;
		}
		sprintf(ids_folder,"%u files checked\n %u files accepted",idf_count,idf_pass);
		emsg = ids_folder;
		break;				
	}
	MessageBox(emsg);
	
}	


