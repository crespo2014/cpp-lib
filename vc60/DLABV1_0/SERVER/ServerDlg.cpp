// serverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "server.h"
#include "serverDlg.h"
#include "SyncSocket.h"
#include "SockAddr.h"
#include "SyncException.h"
#include "WndChat.h"
#include "DriverChat.h"
#include "ChatCSC.h"
#include "ChatCS.h"
////DLL ROBOT3D///
#include "SDriver.h"
//////////////////
////DLL IMAGE1_0//
#include "Camara.h"
#include "StoreImage.h" 
#include "Codec.h"

//////////////////
#include <afxwin.h>
#include "StoreImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

////////////////////GLOBAL DLG VARIABLES////////////////////////////
CCamara Cam;
CCodec *Compress;
char BufferImage[5050];
char buffer_info[100];
int buffer_info_cant;
CString BufferChatRecv;
CWndChat* lastchat;
CEvent g_eventShowChat;
CEvent g_event_kit;
bool kit_wait=false;
CPtrList users;
bool killchat;


int clientcant;
char i;
bool Kill;
CCriticalSection kill_chat;

unsigned short port=800;
CCriticalSection m_cs;

int tam=4001;
CChatCS g_sListen;
CSyncSocket g_sClient_Cant;

////KIT//////
CSDriver kit;

/////////////////////GLOBAL DLG THREADS///////////////////////////
UINT GetDriverImage(LPVOID pParam)
{
	CPoint org(20,20);
	char *Buffer_Complete;
	
	while (!Kill)
	
	{
	if (Cam.m_refresca)
		{
		m_cs.Lock();
		
		Buffer_Complete = Cam.GrabNext(Cam.cmsTimeout);
		
		if (Buffer_Complete)
		{
		Compress->Compress(Buffer_Complete);
		memcpy(BufferImage,Compress->OutputBuffer,5000);
		}
		Cam.Display(org);
		m_cs.Unlock();
	}
		else
		{
			Sleep(50);
		}
		//Cam.CopyBuffer(BufferImage,i);
	}
   
    Kill=false;
	return 0;
}
////////////////////////////////////////////////////////////////////
UINT SendClientInfo(LPVOID pParam)
{

	char* pBuff=new char[1025];
	CSockAddr saClient;
	CSyncSocket sConnect;
	CString recv;
	char Buffer[1];
	
	int retval;
	try
	{
	if(!g_sClient_Cant.Accept(sConnect,saClient))
	{
		return 0;
	}
	_itoa( clientcant, Buffer, 10 );
	buffer_info[0]=Buffer[0];
	AfxBeginThread(SendClientInfo,pParam);

    retval=sConnect.Receive(pBuff,1024,10);
    pBuff[retval]=NULL;
	recv=pBuff;
	if(recv=="request_client_info")
	 {
	  
		sConnect.Send(buffer_info,100,10);

	 }
	  
	}
	catch(CSyncException* e)
	{
		AfxMessageBox(e->GetErrorMsg());
		e->Delete();
	}
	sConnect.Close();
    return 0;

}
/////////////////////////////////////////////////////////////////////
UINT SendImage(LPVOID pParam)
{
	char buffer[1];
	int fromlen;
	char *pTemp;
	CSyncSocket video_server;
	port++;

	//creación de la estructura address del server

	CSockAddr local(INADDR_ANY,port),from;
	
	try
	{
	   video_server.Create(SOCK_DGRAM);
	   video_server.Bind(local);		
	
       video_server.ReceiveDatagram(buffer,1,from,10,fromlen);

	   AfxBeginThread(SendImage,pParam);
	   clientcant++;
	   while(true)
	   {
		kill_chat.Lock();
		if(Kill)
		{
			kill_chat.Unlock();
			video_server.Close();
			return 0;
		}
		kill_chat.Unlock();
			
			i=0;
			for(i=0;i<1;i++)
			{

		        m_cs.Lock();
		        pTemp=&BufferImage[i*(tam-1)];
				pTemp[(tam-1)]=i;
       	        video_server.SendDatagram(pTemp,tam,from,10,fromlen);
				m_cs.Unlock();
				Sleep(2);
				
	
			}
		
	}
	}
    catch(CSyncException* e)
	{
		AfxMessageBox(e->GetErrorMsg());
		e->Delete();
	}

	return 0;
}
/////////////////////////////////////////////////////////////////////
UINT ServerChatThread(LPVOID pParam)
{
	CSockAddr saClient;
	CChatCS sConnect;
	char* pBuff=new char[1025];
	CString cause,msg;
	int retval;
		
	  try
	  {
	    if(!g_sListen.Accept(sConnect,saClient))
		{
		 return 0;
		}
	    AfxBeginThread(ServerChatThread,pParam);

		/////
		while(true)
		{
			retval=sConnect.ReadChatMessage(cause,msg);
			if(cause=="move_robot")
			{
                sConnect.WriteChatMessage("Wait","n");
				//g_event_kit.Lock();
				//sConnect.WriteChatMessage("try_now","n");
				while(kit_wait)
				{}
				kit_wait=true;
				sConnect.WriteChatMessage("try_now","n");
				kit.SendString(msg,msg.GetLength());
				Sleep(60000);
				kit_wait=false;
				//g_event_kit.Unlock();
				sConnect.WriteChatMessage("movement_resolved","n");
				sConnect.Close();
				return 0;
							
			}
			else if(cause=="user_out")
			{
				return 0;
			}
		}
        
		/////

	  }
	  catch(CSyncException* e)
	  {
		AfxMessageBox(e->GetErrorMsg());
		e->Delete();
	  }
	
	return 0;

}
////////////////////////////////////////////////////////////////////

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
// CServerDlg dialog

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	killchat=false;
	on=true;
	one=true;
	Compress = new CCodec;
	//{{AFX_DATA_INIT(CServerDlg)

	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DRIVEROFF, OnDriveroff)
	ON_BN_CLICKED(IDC_DRIVERON, OnDriveron)
	ON_BN_CLICKED(IDC_Send, OnSend)
	ON_BN_CLICKED(IDC_Chat, OnChat)
	ON_BN_CLICKED(IDC_FINISH_CHAT, OnFinishChat)
	ON_BN_CLICKED(IDC_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_Finish_Video, OnFinishVideo)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SHOW,OnShow)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers
LRESULT CServerDlg::OnShow(WPARAM wParam,LPARAM lParam)
{
	
//	lastchat=new CWndChat(BufferChatRecv,"server"); 
//	lastchat->ShowWindow(SW_SHOWNORMAL);
//	lastchat->UpdateWindow();
	
	
//	g_eventShowChat.SetEvent();
	
	return 0;
} 

BOOL CServerDlg::OnInitDialog()
{
    if (!kit.Init())
		MessageBox(" Coneccion con el kit no establecida");
	Kill=false;
	Cam.tam=tam-1;
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerDlg::OnPaint() 
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CServerDlg::OnDriveroff() 
{
	Kill = true;
	if (!Kill)
	Cam.Desconecta();
	on=true;
}

void CServerDlg::OnDriveron() 
{
	LPBITMAPINFOHEADER header;
	BYTE sizeheader;
    CPoint org(20,20);
	if(on)
	{
	if (one)
	{
		Cam.LoadDriver();
        one=false;
		//--------------
        header=(LPBITMAPINFOHEADER)malloc(sizeof(BITMAPINFOHEADER));
        Cam.m_image.FillBitmapInfoHeader(header,32);
		header->biHeight=142;
		sizeheader = sizeof(BITMAPINFOHEADER);
		buffer_info[1] = sizeheader;
		
		//----------------------------------------------------------
		Compress->GetBitmapInfoHeader(header);
        Compress->FindCompress(m_hWnd,500);
        Compress->GetParamComp();
        header=Compress->bihOut;
        memcpy (&buffer_info[2],header,sizeheader);
		
		
	}
	Cam.GetHandle(this);
	Cam.Play();
	Cam.Display(org);
	AfxBeginThread(GetDriverImage,this);
    on=false;
	}

	
}

void CServerDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	AfxBeginThread(SendImage,GetSafeHwnd());
       
		try
	{
	   CSockAddr saServer(INADDR_ANY,port);
	   g_sClient_Cant.Create();
	   g_sClient_Cant.Bind(saServer);
	   g_sClient_Cant.Listen();
	   AfxBeginThread(SendClientInfo,GetSafeHwnd());
	    
	}
	catch(CSyncException *e)
	{
		AfxMessageBox(e->GetErrorMsg());
		e->Delete();
	
	}
	
}

void CServerDlg::OnChat() 
{
	
	try
	{
	   CSockAddr saServer(INADDR_ANY,4000);
	   g_sListen.Create();
	   g_sListen.Bind(saServer);
	   g_sListen.Listen();
	   AfxBeginThread(ServerChatThread,this);
	    
	}
	catch(CSyncException *e)
	{
		AfxMessageBox(e->GetErrorMsg());
		e->Delete();
	
	}

}

void CServerDlg::OnFinishChat() 
{
	g_sListen.Close();
    Kill=true;
	Sleep(300);
	
}

BOOL CServerDlg::DestroyWindow() 
{

	Kill = true;
	if (!Kill)
	Cam.Desconecta();
	return CDialog::DestroyWindow();
}



void CServerDlg::OnSettings() 
{
	Cam.Settings();
}



void CServerDlg::OnFinishVideo() 
{
	// TODO: Add your control notification handler code here
g_sClient_Cant.Close();
Kill=true;
Sleep(300);
	
}
