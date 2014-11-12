// CT10Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "CT10.h"
#include "CT10Dlg.h"
#include "..\LFC10\clases.h"
#include "ct10c1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCT10Dlg dialog

CPort	Port;

char	sentbytes[1024];
WORD	sentbytescant=0;
WORD	sentbytespos=0;
char	receivedbytes[1024];
WORD	receivedbytescant=0;
char	filebuffer[2048];
WORD	filebuffersize=0;

CCT10Dlg::CCT10Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCT10Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCT10Dlg)
	m_sendtoo = -1;
	m_sendmessage = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCT10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCT10Dlg)
	DDX_Control(pDX, IDC_RECEIVEDBYTESEDIT, m_recbytesedit);
	DDX_Control(pDX, IDC_RECEIVEDBYTESCANT, m_receivedbytescant);
	DDX_Control(pDX, IDC_SENTBYTES, m_sentbytes);
	DDX_Control(pDX, IDC_SENTBYTESEDIT, m_sentbytesedit);
	DDX_Control(pDX, IDC_SEND, m_sendedit);
	DDX_CBIndex(pDX, IDC_COMBO2, m_sendtoo);
	DDX_Text(pDX, IDC_SENDMESSAGE, m_sendmessage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCT10Dlg, CDialog)
	//{{AFX_MSG_MAP(CCT10Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_MESSAGE(RECEIVED_DATA,OnData)
	ON_BN_CLICKED(IDC_BUTTON3, OnSend)
	ON_BN_CLICKED(IDC_BUTTON6, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCT10Dlg message handlers

BOOL CCT10Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
	GetDlgItem(IDC_BUTTON3)->SetFocus();
	
	m_sendedit.SetLimitText(10);
	m_sentbytesedit.SetLimitText(1024);
	m_recbytesedit.SetLimitText(1024);
	m_sentbytes.SetWindowText("0 Bytes Sent");
	m_receivedbytescant.SetWindowText("0 Bytes Received ");
	// TODO: Add extra initialization here
	Port.Dlg=this;
	return false;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCT10Dlg::OnPaint() 
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
HCURSOR CCT10Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCT10Dlg::OnButton1() 
{
	Port.OpenPort();		
}

void CCT10Dlg::OnButton5() 
{
	Port.ClosePort();	
}

void CCT10Dlg::OnButton2() 
{
	//Port.ShowConfigDlg();	
}

void CCT10Dlg::OnButton4() 
{
	EndDialog(0);	
}


LRESULT CCT10Dlg::OnData(WPARAM wParam, LPARAM lParam)
{
	if (!lParam)
		return false;
	receivedbytescant+=lParam;
	char	temp[300];
	char	temp1[300];
	char*	ptr=(char*)wParam;
	memcpy(temp1,ptr,lParam);
	ptr=temp1;
	for(int i=0;i<lParam;i++)
	{
		if (ptr[i] < 32 )
			ptr[i]='.';
	}
	ptr[i]=0;
	strcpy(temp,"RS-232:<");
	strcat(temp,ptr);
	strcat(temp,">\r\n");
	WORD	cant=strlen(temp);
	if (strlen(temp)+strlen(receivedbytes) < 1024 )
	{
		strcat(receivedbytes,temp);
		m_recbytesedit.SetWindowText(receivedbytes);
		// Cantidad de bytes recividos
		sprintf(temp1,"%d Bytes Received ",receivedbytescant);
		m_receivedbytescant.SetWindowText(temp1);
		// llenando buffer del fichero
		strcpy(temp,"RS-232:<");
		memcpy(&temp[strlen(temp)],(LPVOID)wParam,lParam);
		memcpy(&temp[cant-3],">\r\n",3);
		memcpy(&filebuffer[filebuffersize],temp,cant);
		filebuffersize+=cant;
	}
	return true;
}

void CCT10Dlg::OnSend() 
{
	char	temp[20];
	char	temp1[20];
	char	send[15];
	WORD	sendlen;
	UpdateData(true);
	memset(send,0,15);
	m_sendedit.GetWindowText(send,15);
	sendlen=strlen(send);

	if (!sendlen)
		return;
	if (!Port.IsOpen())
	{
		MessageBeep(10);
		m_sendmessage="Open the port first";
		UpdateData(false);
		return;
	}
	switch(m_sendtoo)
	{
	case 1:{send[sendlen]=13;send[sendlen+1]=10;sendlen+=2;break;}
	case 2:{send[sendlen]=10;send[sendlen+1]=13;sendlen+=2;break;}
	case 3:{send[sendlen]=13;sendlen++;break;}
	case 4:{send[sendlen]=10;sendlen++;break;}
	}
	strcpy(temp,"PC:<");
	strcat(temp,send);
	strcat(temp,">\r\n");
	sentbytescant+=sendlen;
	sprintf(temp1,"%d Bytes Sent ",sentbytescant);
	m_sentbytes.SetWindowText(temp1);
	if (Port.SendBuffer((BYTE*)send,sendlen))
	{
		m_sendmessage="Text Sent Succesfully";
		m_sendedit.SetWindowText("");
		if ((strlen(temp)+strlen(sentbytes) < 1024))
		{
			strcat(sentbytes,temp);
			m_sentbytesedit.SetWindowText(sentbytes);
			// llenado del fichero
			memcpy(&filebuffer[filebuffersize],temp,strlen(temp));
			filebuffersize+=strlen(temp);
		}
		else
		{
			m_sendmessage="Buffer Full Save or Close";
		}
	} else
	{
		m_sendmessage="Error Sending Text";
	}
	UpdateData(false);
}

void CCT10Dlg::OnSave() 
{
	if (receivedbytescant==0)
	{
		MessageBeep(1);
		AfxMessageBox("You most Received some Data before to Save \r\n  Check The configuration and try again ");
		return;
	}
	CString	m_FileName;
	static char ExtFilter[] = "Dat Files (*.DAT) |*.DAT||"; 
	CFileDialog Dlg(false,NULL,NULL,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,ExtFilter);
	if (Dlg.DoModal() == IDOK)	
	{
		m_FileName=Dlg.GetFileName();
		FILE* file=fopen(m_FileName,"wb");
		fwrite((LPVOID)filebuffer,1,filebuffersize,file);
		fprintf(file,"%d Bytes Recibidos \r\n %d Bytes Enviados ",receivedbytescant,sentbytescant);
		fclose(file);
	}
}
