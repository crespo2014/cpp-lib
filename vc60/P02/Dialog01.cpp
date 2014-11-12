// Dialog01.cpp : implementation file
//

#include "stdafx.h"
#include "P02.h"
#include "Dialog01.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog01 dialog


CDialog01::CDialog01(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog01::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog01)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialog01::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog01)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog01, CDialog)
	//{{AFX_MSG_MAP(CDialog01)
	ON_BN_CLICKED(IDC_PRINT, OnPrint)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog01 message handlers

void CDialog01::OnPrint() 
{
	float	Width_mm;
	float	Height_mm;
	float	Width_pixel;
	float	Height_pixel;
	float Width_pXi;
	float Height_pXi;
	float Width_DU;
	float Height_DU;
	float OffX;
	float OffY;
	LONG Width_LU;
	LONG Height_LU;
	
	PRINTDLG	PrintData;
	memset(&PrintData,0,sizeof(PrintData));
	PrintData.lStructSize=sizeof(PrintData);
	PrintData.hwndOwner=NULL;
	PrintData.hDevMode=NULL;
	PrintData.hDevNames=NULL;
	PrintData.hDC=NULL;
	PrintData.Flags=PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC;
	PrintData.nFromPage=0xFFFF;
	PrintData.nToPage=0xFFFF;
	PrintData.nMinPage=1;
	PrintData.nMaxPage=0xFFFF;
	PrintData.nCopies=1;
	PrintData.hInstance=NULL;
	PrintData.lCustData=NULL;
	PrintData.lpfnPrintHook=NULL;
	PrintDlg(&PrintData);
	CDC	dc;
	dc.Attach(PrintData.hDC);
	GlobalFree(PrintData.hDevMode);
	GlobalFree(PrintData.hDevNames);
	DOCINFO	di;
	di.cbSize=sizeof(di);
	di.fwType=0;
	di.lpszDatatype=NULL;
	di.lpszDocName="Lester";
	di.lpszOutput=NULL;
	StartDoc(PrintData.hDC,&di);
	StartPage(PrintData.hDC);
		
	//CClientDC	dc(this);
	dc.SetMapMode(MM_LOENGLISH);
	Width_mm=dc.GetDeviceCaps(HORZSIZE);
	Height_mm=dc.GetDeviceCaps(VERTSIZE);
	Width_pixel=dc.GetDeviceCaps(HORZRES);
	Height_pixel=dc.GetDeviceCaps(VERTRES);
	Width_pXi=dc.GetDeviceCaps(LOGPIXELSX);
	Height_pXi=dc.GetDeviceCaps(LOGPIXELSY);
	Width_DU=dc.GetDeviceCaps(PHYSICALWIDTH);
	Height_DU=dc.GetDeviceCaps(PHYSICALHEIGHT);
	OffX=dc.GetDeviceCaps(PHYSICALOFFSETX);
	OffY=dc.GetDeviceCaps(PHYSICALOFFSETY);

	Width_LU=(Width_pixel/Width_pXi)*100;
	Height_LU=(Height_pixel/Height_pXi)*100;

	m_Grid.DrawMX=Width_LU;
	m_Grid.DrawMY=-Height_LU;
	m_Grid.DrawSX=0;
	m_Grid.DrawSY=0;
	m_Grid.DrawDX=1;
	m_Grid.DrawDY=-1;
	m_Grid.PrintToPaper(dc);

	EndPage(PrintData.hDC);
	EndDoc(PrintData.hDC);

	
}

BOOL CDialog01::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Recordset=NULL;
	// TODO: Add extra initialization here
	
	CRect rect(10,10,300,300);
	m_Grid.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,rect,this,1001,NULL);
	m_Grid.SetColumnCant(2);
	m_Grid.SetColumnParam(0,VT_I4,4,0,"id","id");
	//m_Grid.SetColumnParam(1,VT_BSTR,100,1,"cve_concepto","Nombre");
	m_Grid.SetColumnParam(1,VT_I4,4,1,"nombre1","nombre1");
	m_Grid.SetArrayCant(100);
	//m_Grid.SetColumnParam(2,VT_I4,0,2,"id","ID");
	Database.Open("c:\\corres97.mdb");
	Recordset= new CDaoRecordset(&Database);
	Recordset->Open(dbOpenDynaset,"SELECT * FROM remitentes");
	m_Grid.SetRecordSet(Recordset);
	
	memset(&lf,0,sizeof(LOGFONT));
	strcpy(lf.lfFaceName,"Arial");
	lf.lfHeight=-100;
	lf.lfWidth=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfOutPrecision=3;
	lf.lfClipPrecision=2;
	lf.lfQuality=1;
	lf.lfPitchAndFamily=34;
	lf.lfCharSet=ANSI_CHARSET;
	lf.lfItalic = false;
	Font.CreateFontIndirect(&lf);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialog01::OnClose() 
{
	if (Recordset)
		delete Recordset;
	CDialog::OnClose();
}
