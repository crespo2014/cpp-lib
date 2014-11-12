// PortConfiguration.cpp : implementation file
//

#include "stdafx.h"
#include "PortConf.h"
#include "app.h"
#include "..\ngsig\sigdef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Constantes que tienen que ver con el puerto
// de comunicaciones
typedef struct
{
	char* str;
	DWORD val;
} S_PORTDATA;

char* PORTS[]={"COM1","COM2","COM3","COM4"};

S_PORTDATA	BYTESIZE[]={"5 Bits",5,
						"6 Bits",6,
						"7 Bits",7,
						"8 Bits",8};
S_PORTDATA	STOPBITS[]={"1",	ONESTOPBIT,
						"1.5",	ONE5STOPBITS,
						"2",	TWOSTOPBITS};
S_PORTDATA  PARITY[]=  {"Even",		EVENPARITY,
						"Mark",		MARKPARITY,
						"No parity",ODDPARITY,
						"Odd",		SPACEPARITY,
						"Space",	NOPARITY};
S_PORTDATA BAUDRATE[]= {"110 Bits/s",	CBR_110,
						"300 Bits/s",	CBR_300,
						"600 Bits/s",	CBR_600,
						"1K2 Bits/s",	CBR_1200,
						"2K4 Bits/s",	CBR_2400,
						"4K8 Bits/s",	CBR_4800,
						"9K6 Bits/s",	CBR_9600,
						"14K4 Bits/s",	CBR_14400,
						"19K2 Bits/s",	CBR_19200,
						"38K4 Bits/s",	CBR_38400,
						"56 KBits/s",	CBR_56000,
						"57K6 Bits/s",	CBR_57600,
						"115K2 Bits/s",	CBR_115200,
						"128 KBits/s",	CBR_128000,
						"256 KBits/s",	CBR_256000};


/////////////////////////////////////////////////////////////////////////////
// CPortConf dialog

CPortConf::CPortConf(CWnd* pParent /*=NULL*/)
	: CDialog(IDD, pParent)
{
	//{{AFX_DATA_INIT(CPortConf)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPortConf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPortConf)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPortConf, CDialog)
	//{{AFX_MSG_MAP(CPortConf)
	ON_CBN_SELCHANGE(IDC_BAUDRATE, OnSelchangeBaudrate)
	ON_CBN_SELCHANGE(IDC_BYTESIZE, OnSelchangeBytesize)
	ON_CBN_SELCHANGE(IDC_PARITY, OnSelchangeParity)
	ON_CBN_SELCHANGE(IDC_PORT, OnSelchangePort)
	ON_CBN_SELCHANGE(IDC_STOPBITS, OnSelchangeStopbits)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPortConf message handlers

void CPortConf::OnSelchangeBaudrate() 
{
	
	CComboBox* Combo=(CComboBox*)GetDlgItem(IDC_BAUDRATE);
	((CApp*)pApp)->m_Signal_Wnd.m_SignalWnd->BaudRateIndex=Combo->GetCurSel();	
}

void CPortConf::OnSelchangeBytesize() 
{
	CComboBox* Combo=(CComboBox*)GetDlgItem(IDC_BYTESIZE);
	((CApp*)pApp)->m_Signal_Wnd.m_SignalWnd->ByteSizeIndex=Combo->GetCurSel();	
}

void CPortConf::OnSelchangeParity() 
{
    CComboBox* Combo=(CComboBox*)GetDlgItem(IDC_PARITY);
	((CApp*)pApp)->m_Signal_Wnd.m_SignalWnd->ParityIndex=Combo->GetCurSel();	
}

void CPortConf::OnSelchangePort() 
{
	CComboBox* Combo=(CComboBox*)GetDlgItem(IDC_PORT);
	((CApp*)pApp)->m_Signal_Wnd.m_SignalWnd->PortIndex=Combo->GetCurSel();	
}

void CPortConf::SetPointer(void *p)
{
  pApp = p;
}

BOOL CPortConf::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Actualizacion de los combobox que tienen que 
	// ver con el puerto

	
	CComboBox* Combo=(CComboBox*)GetDlgItem(IDC_PORT);
	for (int i=0;i<MAXPORTS;i++)
	{
		Combo->AddString(PORTS[i]);
	}
	Combo->SetCurSel(((CApp*)pApp)->m_Signal_Wnd.m_SignalWnd->PortIndex);

	Combo=(CComboBox*)GetDlgItem(IDC_BYTESIZE);
	for (i=0;i<MAXBYTESIZE;i++)
	{
		Combo->AddString(BYTESIZE[i].str);
	}
	Combo->SetCurSel(((CApp*)pApp)->m_Signal_Wnd.m_SignalWnd->ByteSizeIndex);

	Combo=(CComboBox*)GetDlgItem(IDC_STOPBITS);
	for (i=0;i<MAXSTOPBITS;i++)
	{
		Combo->AddString(STOPBITS[i].str);
	}
	Combo->SetCurSel(((CApp*)pApp)->m_Signal_Wnd.m_SignalWnd->StopBitsIndex);

	Combo=(CComboBox*)GetDlgItem(IDC_PARITY);
	for (i=0;i<MAXPARITY;i++)
	{
		Combo->AddString(PARITY[i].str);
	}
	Combo->SetCurSel(((CApp*)pApp)->m_Signal_Wnd.m_SignalWnd->ParityIndex);

	Combo=(CComboBox*)GetDlgItem(IDC_BAUDRATE);
	for (i=0;i<MAXBAUDRATE;i++)
	{
		Combo->AddString(BAUDRATE[i].str);
	}
	Combo->SetCurSel(((CApp*)pApp)->m_Signal_Wnd.m_SignalWnd->BaudRateIndex);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPortConf::OnSelchangeStopbits() 
{

	CComboBox* Combo=(CComboBox*)GetDlgItem(IDC_STOPBITS);
	((CApp*)pApp)->m_Signal_Wnd.m_SignalWnd->StopBitsIndex=Combo->GetCurSel();	
}
