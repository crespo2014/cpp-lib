// VLClient1View.cpp : implementation of the CVLClient1View class
//

#include "stdafx.h"
#include "VLClient1.h"

#include "VLClient1Doc.h"
#include "CntrItem.h"
#include "VLClient1View.h"
#include "..\sync\SyncSocket.h"
#include "..\sync\SockAddr.h"
#include "..\sync\SyncException.h"

#include "..\sync\ChatCS.h"

/////ROBOT3D.DLL///
#include "..\robot3d\robot1.h" 
#include "..\robot3d\Ficha.h"
/////////////
/*
//////IMAGE1_0.DLL
#include "..\image1_0\Cambuff.h"
#include "..\image1_0\Codec.h"
/////////////////
*/
#include <afxwin.h>
#include <memory.h>
#include <afxmt.h>
#include <afxcoll.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVLClient1View

////////////////VIEW GLOBAL VARIABLES /////////////////////////////////
//CString host="Pcimrobot";
CString host="Pcimrobot";
/////ADDRESS////

in_addr myaddr;


////////////////
//char *Buffer;
char buffer_info[100];
char Buffer[4000];
char i;
CString mensaje;
unsigned short port=800;
//CCamBuff cambuff;
//CCodec *Decompress;
CCriticalSection g_cs;
CEvent g_eventShowChat;
CCriticalSection kill_chat;
bool Kill=false;
bool killchat;
//bool buffer_info_recv=false;
//bool recv_video_enable=false;
//bool decompress_enable=false;
CEvent buffer_info_recv;
CEvent recv_video_enable;
CEvent decompress_enable;

///OPENGL/////
CRobot1 m_scene;
PVOID m_Tablero[100];
BYTE m_Tablero_Count;
//////////////

////////////////////////////////////////////////////////////////////

////////////////VIEW GLOBAL THREADS/////////////////////////////////

////////////////////////////////////////////////////////////////////
UINT muestra(LPVOID pParam)
{
   //AfxMessageBox("se hecha a andar el hilo de muestra");
   CClientDC* dc = new CClientDC((CVLClient1View*)pParam);
   CPoint org(70,50);
   
	while(true)
   {
   
   //while(!decompress_enable) {}
   WaitForSingleObject(decompress_enable,INFINITE);
   
   g_cs.Lock();
   //decompress_enable=false;
   decompress_enable.ResetEvent();
   //AfxMessageBox("muestra");
   //Beep(1000,10000);
//   Decompress->DeCompress(Buffer);
   g_cs.Unlock();
   /*
   Decompress->biOut->bmiHeader.biHeight=-142;
   Decompress->biOut->bmiHeader.biSizeImage=0;

   Decompress->PintaBmp(dc,org,Decompress->OutputBuffer,Decompress->biOut);
   
   Decompress->biOut->bmiHeader.biHeight=142;
   */
   }
   return 0;
}

////////////////////////////////////////////////////////////////////

UINT StartThreadProc(LPVOID pParam)
{

int tam;
tam=4001;
CSyncSocket sClient;
CString request="request_client_info";
int size=tam;
BYTE i=0;
char *Ptemp;

Ptemp = (char*) malloc(tam);
char client_cant[1];

    mensaje="Getting Host by Name";

    CSockAddr saServer;
	
	try
	{
	sClient.Create();
	saServer.sin_addr.s_addr=myaddr.S_un.S_addr;
	saServer.sin_family=2;
	saServer.sin_port=sClient.GetBigIndianOrder(port);
	int zero;
	for(zero=0;zero<8;zero++)
	{
		saServer.sin_zero[zero]=0;     
	}
	

	mensaje="Host Resolved";
	sClient.Connect(saServer);


	sClient.Send(LPCTSTR(request),request.GetLength(),10);

//Recibe la cantidad de clientes conectados y la informacion de los header de compactacion


	sClient.Receive(buffer_info,100,10);

	client_cant[0]=buffer_info[0];
	
//variable global port que indica por cual puerta 
//se va a conectar este cliente
	
	port=atoi(client_cant)+port+1;

    sClient.Close();

   //buffer_info_recv=true;
   buffer_info_recv.SetEvent();

///////////	/////////////////////////////////////////////////////////////////////////////////////

CSyncSocket video_client;
CSockAddr saServer_Video;
CString request_video="g";


    
    video_client.Create(SOCK_DGRAM);
	saServer.sin_port=video_client.GetBigIndianOrder(port);
	video_client.Connect(saServer);
	//while(!recv_video_enable)
	//{}
	WaitForSingleObject(recv_video_enable,INFINITE);
    recv_video_enable.ResetEvent();

    mensaje="sending trigger"; 
    video_client.Send(LPCTSTR(request_video),request_video.GetLength(),10);

while(!video_client.Receive(Ptemp,size,5))
{
	video_client.Send(LPCTSTR(request_video),request_video.GetLength(),10);
}
mensaje="receiving video";

while(true)
{
if(video_client.Receive(Ptemp,size,10)==size)
{
  
	g_cs.Lock();
	memcpy((void *)&Buffer[Ptemp[tam-1]*(tam-1)],Ptemp,tam-1);
	if(Ptemp[tam-1]==0)
	//Beep(500,10000);
    //decompress_enable=true;
	decompress_enable.SetEvent();	
	g_cs.Unlock();
	Sleep(2);}
if(Kill==true)
{
	video_client.Close();
	return 0;
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

////////////////////////////////////////////////////////////////////
UINT ClientChatThread(LPVOID pParam)
{
	CString cause;
	CString msg;
	CChatCS sClient;
	CSockAddr saServer;
	try
	{
	sClient.Create();
	saServer.sin_addr.s_addr=940576940;
	saServer.sin_family=2;
	saServer.sin_port=sClient.GetBigIndianOrder(4000);
	int zero;
	for(zero=0;zero<8;zero++)
	{
		saServer.sin_zero[zero]=0;     
	}
	sClient.Connect(saServer);

	sClient.WriteChatMessage("move_robot",m_scene.GetCmdChar());
	while(true)
	{
	  sClient.ReadChatMessage(cause,msg);
	  if(cause=="movement_resolved")
	  {
		 sClient.Close();
		 return 0;
			
	  }
	  else if(cause=="Wait")
	  {
		  mensaje="Wait for Your turn";
	  }
	  else if(cause=="try_now")
	  {
		  mensaje="try now";
	  }
	}
	
	}

	catch(CSyncException* e)
	{
    sClient.Close();
	AfxMessageBox(e->GetErrorMsg());
	e->Delete();
		
	}
	return 0;
	
}



IMPLEMENT_DYNCREATE(CVLClient1View, CFormView)

BEGIN_MESSAGE_MAP(CVLClient1View, CFormView)
	//{{AFX_MSG_MAP(CVLClient1View)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_BN_CLICKED(IDC_CONECT, OnConect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Request_Chat, OnRequestChat)
	ON_LBN_DBLCLK(IDC_USERS_LIST, OnDblclkUsersList)
	ON_BN_CLICKED(IDC_SEND_PUBLIC, OnSendPublic)
	ON_BN_CLICKED(IDC_FINISH_CHAT, OnFinishChat)
	ON_BN_CLICKED(IDC_Finish_Video, OnFinishVideo)
	ON_BN_CLICKED(IDC_Get_Ficha, OnGetFicha)
	ON_BN_CLICKED(IDC_SIMULATION, OnSimulation)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_MESSAGE(WM_SHOW_USERS,OnShowUsers)
END_MESSAGE_MAP()
////////////////////////////////////////////////////////////
//User messages handler
LRESULT CVLClient1View::OnShowUsers(WPARAM wParam,LPARAM lParam)
{
    
    
	return 0;
} 


/////////////////////////////////////////////////////////////////////////////
// CVLClient1View construction/destruction

CVLClient1View::CVLClient1View()
	: CFormView(CVLClient1View::IDD)
{
	//{{AFX_DATA_INIT(CVLClient1View)
	m_cant = 0;
	m_lines = 0;
	m_msg = _T("");
	m_nick = _T("");
	m_public = _T("");
	m_XPos = 0.0;
	m_ZPos = 0.0;
	m_Value = 0;
	//}}AFX_DATA_INIT
	m_pSelection = NULL;
	// TODO: add construction code here
	visualiza=false;
	rect = new CRect(0,0,192,142);
	m_cant=0;
	m_lines=0;
	killchat=false;
//	Decompress = new CCodec;
	
	//SetTimer(1000,100,NULL);

}

CVLClient1View::~CVLClient1View()
{
}

void CVLClient1View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVLClient1View)
	DDX_Control(pDX, IDC_OPENGL, m_GLButton);
	DDX_Text(pDX, IDC_STATUS, m_msg);
	DDX_Text(pDX, IDC_COORDENADA_X, m_XPos);
	DDX_Text(pDX, IDC_COORDENADA_Z, m_ZPos);
	DDX_Text(pDX, IDC_VALUE, m_Value);
	//}}AFX_DATA_MAP
}

BOOL CVLClient1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CVLClient1View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

	///OPENGL//////
	CRect rect;
	m_GLButton.SetDlgCtrlID(0xffff);
	m_GLButton.GetWindowRect(rect);
	ScreenToClient(&rect);
	m_scene.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,rect,this,IDC_OPENGL);
	m_scene.Init();
	m_Tablero_Count=0;
	SetTimer(100,1,NULL);
	////////////////////
	CIPAddressCtrl* cIP;
	cIP=(CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1);
	cIP->SetAddress(172,16,16,56);
	//////////////

}

/////////////////////////////////////////////////////////////////////////////
// CVLClient1View printing

BOOL CVLClient1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVLClient1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVLClient1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVLClient1View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

void CVLClient1View::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CFormView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CVLClient1View::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CVLClient1CntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CVLClient1View::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CVLClient1CntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CVLClient1CntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CVLClient1Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CVLClient1CntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CVLClient1View::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CVLClient1View::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CFormView::OnSetFocus(pOldWnd);
}

void CVLClient1View::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CVLClient1View::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CVLClient1View diagnostics

#ifdef _DEBUG
void CVLClient1View::AssertValid() const
{
	CFormView::AssertValid();
}

void CVLClient1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVLClient1Doc* CVLClient1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVLClient1Doc)));
	return (CVLClient1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVLClient1View message handlers

void CVLClient1View::OnConect() 
{
	CIPAddressCtrl* cIP;
	cIP=(CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1);
	cIP->GetAddress(myaddr.S_un.S_un_b.s_b1,myaddr.S_un.S_un_b.s_b2,myaddr.S_un.S_un_b.s_b3,myaddr.S_un.S_un_b.s_b4);
	
	LPBITMAPINFOHEADER header;


	mensaje="Getting Host by Name";

	

	m_msg=mensaje;
	UpdateData(false);
	CPoint org(70,30);

	AfxBeginThread(StartThreadProc,this);
	
	WaitForSingleObject(buffer_info_recv,INFINITE);
    buffer_info_recv.ResetEvent();

	header = (LPBITMAPINFOHEADER) malloc(buffer_info[1]);
	memcpy(header,&buffer_info[2],buffer_info[1]);
	/*
	Decompress->GetBitmapInfoHeader(header);
	Decompress->FindDecompress(m_hWnd);
    Decompress->GetParamDecomp();
	*/
	AfxBeginThread(muestra,this);
	recv_video_enable.SetEvent();
	
}

void CVLClient1View::OnTimer(UINT nIDEvent) 
{
	m_scene.CheckPos();
	CEdit* pCE;
	pCE=(CEdit*)GetDlgItem(IDC_STATUS);
	pCE->SetWindowText(mensaje);
	CFormView::OnTimer(nIDEvent);
}

void CVLClient1View::OnRequestChat() 
{
	AfxBeginThread(ClientChatThread,this);
	
}

void CVLClient1View::OnDblclkUsersList() 
{
	
}





void CVLClient1View::OnSendPublic() 
{
	
}

void CVLClient1View::OnFinishChat() 
{
    killchat=true;
	Sleep(300);
	//WSACleanup();	
}

void CVLClient1View::OnFinishVideo() 
{
	// TODO: Add your control notification handler code here
	Kill=true;
	Sleep(300);
	
}

void CVLClient1View::OnGetFicha() 
{
	// TODO: Add your control notification handler code here
	if (m_Tablero_Count<2)
	{
		double Coord[3];
		CFicha* m_FichTemp;
		m_FichTemp=new CFicha;
		UpdateData(TRUE);
		Coord[0]=m_XPos;
		Coord[1]=0.0;
		Coord[2]=m_ZPos;
		m_FichTemp->SetPos(Coord);
		m_FichTemp->SetValue(m_Value);
		m_Tablero[m_Tablero_Count]=m_FichTemp;
		m_Tablero_Count++;
	}
	
}

void CVLClient1View::OnSimulation() 
{
	// TODO: Add your control notification handler code here
	m_scene.ExecuteList(m_Tablero,m_Tablero_Count);

}

HBRUSH CVLClient1View::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
		
    	
	// TODO: Return a different brush if the default is not desired
	if(nCtlColor==CTLCOLOR_DLG)
	{
		CBrush my(RGB(0,0,0));
		
		pDC->SetBkColor(RGB(0,0,0));
		return (HBRUSH)my;
	}
	return hbr;	
}
