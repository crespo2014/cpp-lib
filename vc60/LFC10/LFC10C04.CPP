// sigc01.cpp : implementation file
//

#include "stdafx.h"
#include "LFC10C05.h"
#include "LFC10C04.h"
#include "lfc10def.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DLG_BAR_MAX_SIZE 317
#define DLG_BAR_MIN_SIZE 20
#define DLG_BAR_MED_SIZE 215

float MiliVoltPerDivTable[]={
	1.0f,2.0f,5.0f,10.0f,20.0f,50.0f,100.0f,200.0f,400.0f,500.0f,1000.0f,1500.0f
	};
float SamplesCantTable[]={
	100.0f,200.0f,300.0f,400.0f,500.0f
	};
#define MaxSamCant 5
#define MaxMiliPerDiv 12

static int EdgePosTable[]=
		{1,0,-1};
const char* EdgePosString[]={
			"Up","Center","Down"
			};

#define MAXEDGEPOS 3

// Tabla de los parametros que se 
// almacenan en el fichero de configuracion
const char* PT[] ={
	"GraphCant"     ,"ActiveGraph","SamplesCant","Graphics",
	"BufferLen"     ,"EdgeColor"  ,"EdgeXPos"   ,"MiliVoltsPerDiv",
	"MiliVoltsPerUC","Name"       ,"OnShow"     ,"FontName",
	"Italic"        ,"Bold"       ,"SignalColor","BackColor",
	"Port"          ,"ByteSize"   ,"StopBits"   ,"BaudRate",
	"Parity","FilterIndex"
	};
#define ParamTableMax 22
char FileName[300];

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

#define MAXBYTESIZE 4
#define MAXPORTS 4
#define MAXBAUDRATE 15
#define MAXPARITY 5
#define MAXSTOPBITS 3

/*
	Constantes que tienen que ver con los filtros
*/

#define FILTER_4_7_HZ_ORDER 7

double FILTER_4_7_HZ_A[] = {
	   1.0000000000000000e+000,
	   -5.9234125427462541e+000,
	   1.4658896085810349e+001,
	   -1.9399502411701370e+001,
		1.4479764721753707e+001,
	   -5.7795329447156725e+000,
		9.6378890531529104e-001};
double FILTER_4_7_HZ_B[] = {
       3.6731211833936897e-003,
  	  -1.4564371353847395e-002,
	   1.8109931047261871e-002,
	  -3.0992676196319782e-017,
	  -1.8109931047261840e-002,
	  1.4564371353847402e-002,
	  -3.6731211833936953e-003};

#define FILTER_8_14_HZ_ORDER 9
double FILTER_8_14_HZ_B[] = {
		3.1165385134352273e-002,
		-2.4007906586447444e-001,
		8.1797442458319647e-001,
		-1.6098103346414425e+000,
		2.0014993565156867e+000,
		-1.6098103346414416e+000,
		8.1797442458319569e-001,
		-2.4007906586447411e-001,
		3.1165385134352221e-002};
double FILTER_8_14_HZ_A[] = {
	   1.0000000000000000e+000,
	  -7.7164769151806736e+000,
	   2.6257281550986313e+001,
	  -5.1453208430963201e+001,
	   6.3502315231566634e+001,
	  -5.0544014933683997e+001,
	   2.5337591944747274e+001,
	  -7.3146785620600605e+000,
	   9.3119564811361466e-001};

#define FILTER_15_18_HZ_ORDER 7
double FILTER_15_18_HZ_B[] = {
	   3.6731211833936905e-003,
	   -1.3794758013584662e-002,
       1.6620568813262234e-002,
	   -1.6311934840168310e-018,
	   -1.6620568813262227e-002,
	   1.3794758013584653e-002,
	   -3.6731211833936866e-003 };
double FILTER_15_18_HZ_A[] = {
	   1.0000000000000000e+000,
	   -5.6104064265177795e+000,
	   1.3455170963417970e+001,
	   -1.7623592913989597e+001,
	   1.3290752822084357e+001,
	   -5.4741297421554860e+000,
	   9.6378890531529515e-001};

#define FILTER_15_21_HZ_ORDER 9
double FILTER_15_21_HZ_A[] = {
	   1.0000000000000000e+000,
	   -7.3693038832921598e+000,
	   2.4291679752728598e+001,
	   -4.6720204719748850e+001,
	   5.7306381375759173e+001,
	   -4.5894692167893112e+001,
	   2.3440862978972024e+001,
	   -6.9855828929361783e+000,
	   9.3119564811361355e-001};
	   
double FILTER_15_21_HZ_B[] = {
	   3.1165385134352273e-002,
	   -2.2927763690857897e-001,
	   7.5670915358430968e-001,
	   -1.4616136745190123e+000,
	   1.8060441707462676e+000,
	   -1.4616136745190118e+000,
	   7.5670915358430912e-001,
	   -2.2927763690857872e-001,
	   3.1165385134352231e-002};

#define FILTER_18_21_HZ_ORDER 7
double FILTER_18_21_HZ_A[] = {
	  1.0000000000000000e+000,
	 -5.4725068465655120e+000,
	  1.2945584071433071e+001,
	 -1.6880386903375836e+001,
	  1.2787394649014612e+001,
	 -5.3395797408437229e+000,
	  9.6378890531529271e-001};

double FILTER_18_21_HZ_B[] = {
	  3.6731211833936949e-003,
	 -1.3455693213105127e-002,
	  1.5990059855905698e-002,
	  1.3049547872134663e-017,
	 -1.5990059855905722e-002,
	  1.3455693213105144e-002,
	 -3.6731211833936983e-003};

#define FILTER_22_HZ_ORDER 7
double FILTER_22_HZ_A[] = {
	  1.0000000000000000e+000,
	 -4.4939973991338684e+000,
	  9.0459866086236733e+000,
	 -1.0310079076439550e+001,
	  7.0547230802964735e+000,
	 -2.7724885463573763e+000,
	  5.0499508471069354e-001};

double FILTER_22_HZ_B[] = {
	  4.3746408981714874e-001,
	 -2.4249306935974060e+000,
	  5.7895512181276523e+000,
	 -7.6032475837488338e+000,
	  5.7895512181276523e+000,
	 -2.4249306935974069e+000,
	  4.3746408981714902e-001};

S_FILTERDATA SIG2_FILTER_DATA[]={"4-7Hz",
				FILTER_4_7_HZ_ORDER,
				FILTER_4_7_HZ_A,
				FILTER_4_7_HZ_B};
S_FILTERDATA SIG3_FILTER_DATA[]={"8-14Hz",
				FILTER_8_14_HZ_ORDER,
				FILTER_8_14_HZ_A,
				FILTER_8_14_HZ_B};
S_FILTERDATA SIG4_FILTER_DATA[]={"15-18Hz",
				FILTER_15_18_HZ_ORDER,
				FILTER_15_18_HZ_A,
				FILTER_15_18_HZ_B,
				"15-21Hz",
				FILTER_15_21_HZ_ORDER,
				FILTER_15_21_HZ_A,
				FILTER_15_21_HZ_B,
				"18-21Hz",
				FILTER_18_21_HZ_ORDER,
				FILTER_18_21_HZ_A,
				FILTER_18_21_HZ_B};
S_FILTERDATA SIG5_FILTER_DATA[]={"> 22Hz",
				FILTER_22_HZ_ORDER,
				FILTER_22_HZ_A,
				FILTER_22_HZ_B};

#define SIG0_FILTER_CANT 0
#define SIG1_FILTER_CANT 0
#define SIG2_FILTER_CANT 1
#define SIG3_FILTER_CANT 1
#define SIG4_FILTER_CANT 3
#define SIG5_FILTER_CANT 1


S_SIGFILTERS SIGNALS_FILTERS[]={
		SIG0_FILTER_CANT,NULL,
		SIG1_FILTER_CANT,NULL,
		SIG2_FILTER_CANT,SIG2_FILTER_DATA,
		SIG3_FILTER_CANT,SIG3_FILTER_DATA,
		SIG4_FILTER_CANT,SIG4_FILTER_DATA,
		SIG5_FILTER_CANT,SIG5_FILTER_DATA,
		};

int CALLBACK EnumFontFamExProc(
  const ENUMLOGFONTEX *lpelfe,    // pointer to logical-font data
  const NEWTEXTMETRIC  *lpntme,  // pointer to physical-font data
  DWORD FontType,             // type of font
  LPARAM lParam             // application-defined data
)


{
	CSignalWnd* pSW=(CSignalWnd*)lParam;
	pSW->AddFont((char*)lpelfe->elfLogFont.lfFaceName);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CSignalWnd

CSignalWnd::CSignalWnd()
{
	InitSignalWnd();
}

CSignalWnd::~CSignalWnd()
{
	S_MESSAGE Message;
	Message.Msg=UM_CLOSETHREAD;
	m_SignalWnd->Message.SendMessage(&Message);
	WaitForSingleObject(m_SignalWnd->Thread->m_hThread,INFINITE);
	SaveDataToFile(FileName);
	delete m_SignalWnd;
}


BEGIN_MESSAGE_MAP(CSignalWnd, CWnd)
	//{{AFX_MSG_MAP(CSignalWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CLOSE, OnCloseFontDlg)
	ON_WM_LBUTTONDBLCLK()
	ON_CBN_SELCHANGE(FONT_COMBOBOX, OnFontChange)
	ON_BN_CLICKED(BOLD_CHECK, OnBoldChange)
	ON_BN_CLICKED(ITALIC_CHECK, OnItalicChange)
	ON_EN_CHANGE(IDC_GRAPH_NAME, OnChangeGraphName)
	ON_CBN_SELCHANGE(VOLT_POR_DIV_COMBO, OnSelchangePorDivCombo)
	ON_CBN_SELCHANGE(IDC_SAMPLES_CANT, OnSelchangeSamplesCant)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_SHOW, OnShow)
	ON_CBN_SELCHANGE(IDC_EDGE_POS, OnEdgePos)
	ON_BN_CLICKED(IDC_EDGE_COLOR, OnEdgeColor)
	ON_BN_CLICKED(IDC_SIGNAL_COLOR, OnSignalColor)
	ON_BN_CLICKED(IDC_BACK_COLOR, OnBackColor)
	ON_BN_CLICKED(IDC_OPEN_CLOSE2, OnOpenClose2)
	ON_CBN_SELCHANGE(IDC_BAUDRATE, OnSelchangeBaudrate)
	ON_CBN_SELCHANGE(IDC_BYTESIZE, OnSelchangeBytesize)
	ON_CBN_SELCHANGE(IDC_PARITY, OnSelchangeParity)
	ON_CBN_SELCHANGE(IDC_PORT, OnSelchangePort)
	ON_CBN_SELCHANGE(IDC_STOPBITS, OnSelchangeStopbits)
	ON_BN_CLICKED(IDC_PORT_OPEN, OnPortOpen)
	ON_BN_CLICKED(IDC_PORT_CLOSE, OnPortClose)
	ON_BN_CLICKED(IDC_PORT_APPLY, OnPortApply)
	ON_CBN_SELCHANGE(IDC_FILTER, OnSelchangeFilter)
	ON_MESSAGE(UM_DEVICE_STATE,OnDeviceState)
	ON_BN_CLICKED(IDC_DEVICESTART, OnDeviceStart)
	ON_BN_CLICKED(IDC_DEVICESTOP, OnDeviceStop)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSignalWnd message handlers

void CSignalWnd::OnPaint() 
{
	CPaintDC(this);
	m_SignalWnd->DlgBar.SetFocus();
}

int CSignalWnd::InitSignalWnd()
{
	m_SignalWnd=new S_SIGNALWND;
	LoadDefaultData();

	// Recogiendo informacion del fichero de configuracion
	::GetCurrentDirectory(255,FileName);
	strcat(FileName,"\\SigWnd.inf");
	ReadDataFromFile(FileName);	

	m_SignalWnd->OnPlay=false;
	m_SignalWnd->Device=NULL;
	m_SignalWnd->OnDevice=false;
	m_SignalWnd->OnWindow=false;
	m_SignalWnd->OnFontDlg=false;
	m_SignalWnd->OnCommDlg=false;
	m_SignalWnd->OnSize=false;
	m_SignalWnd->OnGraph=false;
	
	m_SignalWnd->Thread=AfxBeginThread(ThreadProc,this,THREAD_PRIORITY_ABOVE_NORMAL,0,0,NULL);
	return true;
}

int CSignalWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// Inicializacion de la barra de dialogo de propiedades
	CDialogBar*	DlgBar=&m_SignalWnd->DlgBar;
	CRect rect(0,0,200,200);
	DlgBar->Create(this,"FONT_DLGBAR",0,ID_FONT_DLGBAR);
	DlgBar->ShowWindow(SW_SHOW);
	
	InitDlgBar();
	
	S_MESSAGE	Message;
	Message.Msg=WM_CREATE;
	m_SignalWnd->Message.SendMessage(&Message);
	UpDateDlgBar();
	if (m_SignalWnd->OnDevice)
		m_SignalWnd->Device->SetNotifyWindow(this->GetSafeHwnd());
	return 0;
}

int CSignalWnd::AddFont(char *pFontName)
{
	CComboBox* Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(FONT_COMBOBOX);
	Combo->AddString(pFontName);
	return true;
}

UINT CSignalWnd::ThreadProc(LPVOID pParam)
{
	return ((CSignalWnd*)pParam)->ThreadMain();
}

UINT CSignalWnd::ThreadMain()
{
	ThreadInit();
	while (true)
	{
		if (m_SignalWnd->OnPlay) 
		{
			if (m_SignalWnd->Message.WaitMessage(1))
				if (!ThreadProcessMessage())
					return 0;
			DrawGraphics();
		}
		else
			if (!ThreadGetMessage())
				break;
	}
	return 0;
}
//
// Espera por un mensaje y lo despacha
//
int CSignalWnd::ThreadGetMessage()
{
	m_SignalWnd->Message.WaitMessage();
	if (!ThreadProcessMessage())
		return false;
	return true;
}

int CSignalWnd::ThreadProcessMessage()
{
	S_MESSAGE	Message;
	int			Result=true;
	S_GRAPHDATA* Graph;
	if (m_SignalWnd->ActiveGraph <m_SignalWnd->GraphCant)
		 Graph=&m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph];
	else
		Graph=NULL;

	if (!m_SignalWnd->Message.PeekMessage(&Message))
		return true;
	switch (Message.Msg)
	{
	case UM_NULL:
		{
			break;
		}
	case WM_CREATE:
		{
			CClientDC dc(this);
			m_SignalWnd->MemDC.Create(&dc);
			m_SignalWnd->OnWindow=true;
			break;
		}
	case WM_SIZE:
		{
			ThreadOnSize(&Message);
			break;
		}
	case WM_PAINT:
		{
			DrawGraphics();
			break;
		}
	case UM_CLOSETHREAD:
		{
			Result=false;
			break;
		}
	case UM_PARAMCHANGE:
		{
			if (!Graph)
				break;
			switch (Message.wParam)
			{
			case SHOW_CHANGE:
				{
					Graph->OnShow=Message.lParam;
					CalcGraphSize();
					break;
				}
			case NAME_CHANGE:
				{
					strcpy(m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph].name,
						(char*)Message.ExtraData);
					break;
				}
			case VOLTPERDIV_CHANGE:
				{
					m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph].MiliVoltsPerDiv=
						*(float*)Message.ExtraData;
					ResizeGraph(m_SignalWnd->ActiveGraph);
					break;
				}
			case FONT_CHANGE:
				{
					Graph->Font.DeleteObject();
 					Graph->Font.CreateFontIndirect(&Graph->LogFont);
					ResizeGraph(m_SignalWnd->ActiveGraph);
					break;
				}
			}
			if (m_SignalWnd->OnWindow & !m_SignalWnd->OnPlay)
				DrawGraphics();
			break;
		}
	}
	m_SignalWnd->Message.ReplyMessage(0);
	return Result;
}

LRESULT CSignalWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
	case WM_DESTROY:
		{
			m_SignalWnd->OnWindow=false;
			SendNullMessage();
			break;
		}
	case WM_SIZE:
		{
			ResizeDlgBar();
			break;
		}
	case WM_PAINT:
		{
			InvalidateGraph();
			break;
		}
	}
	return CWnd::WindowProc(message, wParam, lParam);
}

BOOL CSignalWnd::OnEraseBkgnd(CDC* pDC) 
{
	return true;
}

void CSignalWnd::OnCloseFontDlg()
{
	m_SignalWnd->OnFontDlg=!m_SignalWnd->OnFontDlg;
	ResizeDlgBar();
}

void CSignalWnd::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	OnCloseFontDlg();
	CWnd::OnLButtonDblClk(nFlags, point);
}
/*
	Esta funcion es invocada cuando un grafico
	deja de mostrarse o cuando se va a mostrar
*/
int CSignalWnd::CalcGraphSize()
{
	WORD GraphHeight;
	WORD GraphCant=0;
	WORD Top=m_SignalWnd->GraphTop;
	DWORD i;
	for (i=0;i<m_SignalWnd->GraphCant;i++)
	{
		if (m_SignalWnd->Grafica[i].OnShow)
			GraphCant++;
	}
	m_SignalWnd->OnGraph=GraphCant;
	if (!GraphCant)
	{
		return false;
	}
	GraphHeight=m_SignalWnd->GraphHeight/GraphCant;

	for (i=0;i<m_SignalWnd->GraphCant;i++)
		if (m_SignalWnd->Grafica[i].OnShow)
		{
			m_SignalWnd->Grafica[i].Top=Top;
			m_SignalWnd->Grafica[i].Height=GraphHeight;
			m_SignalWnd->Grafica[i].Left=0;
			m_SignalWnd->Grafica[i].Width=m_SignalWnd->GraphWidth;
			Top+=GraphHeight;
		}
	ResizeAllGraphics();
	return true;
}

int CSignalWnd::ResizeDlgBar()
{
	CDialogBar* Dlg=&m_SignalWnd->DlgBar;

	CRect Rect01;
	GetClientRect(&Rect01);
	WORD Width=Rect01.Width();
	WORD Height=Rect01.Height();
	// Enviar mensaje porque este miembro es llamado cada vez 
	// que la grafica debe cambiar de tamano
	S_MESSAGE Msg;
	Msg.Msg=WM_SIZE;
	Msg.lParam=MAKELPARAM(Width,Height);
	m_SignalWnd->Message.SendMessage(&Msg);

	// Si alguno de estos miembros es cero 
	// no se puede hacer nada
	if ((Width==0)||(Height ==0))
		return true;

	if (m_SignalWnd->OnFontDlg)
	{
		if (m_SignalWnd->OnCommDlg)
			Rect01.left=Rect01.right-DLG_BAR_MAX_SIZE;
		else
			Rect01.left=Rect01.right-DLG_BAR_MED_SIZE;
	}
	else
		Rect01.left=Rect01.right-DLG_BAR_MIN_SIZE;

	m_SignalWnd->DlgBar.MoveWindow(&Rect01,true);
	EnableCommProperties(m_SignalWnd->OnCommDlg);
	m_SignalWnd->DlgBar.Invalidate();
	return true;
}

void CSignalWnd::OnFontChange() 
{
	S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph];

	CComboBox* Font=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(FONT_COMBOBOX);
	Font->GetLBText(Font->GetCurSel(),Graph->LogFont.lfFaceName);
	S_MESSAGE	Message;
	Message.Msg=UM_PARAMCHANGE;
	Message.wParam=FONT_CHANGE;
	m_SignalWnd->Message.SendMessage(&Message);
}

void CSignalWnd::OnBoldChange() 
{
	S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph];

	CButton* Bold=(CButton*)m_SignalWnd->DlgBar.GetDlgItem(BOLD_CHECK);	
	if (Bold->GetState()&0x003)
		Graph->LogFont.lfWeight=FW_BOLD;
	else
		Graph->LogFont.lfWeight=FW_NORMAL;
	
	S_MESSAGE	Message;
	Message.Msg=UM_PARAMCHANGE;
	Message.wParam=FONT_CHANGE;
	m_SignalWnd->Message.SendMessage(&Message);
}

void CSignalWnd::OnItalicChange() 
{
	S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph];

	CButton* Italic=(CButton*)m_SignalWnd->DlgBar.GetDlgItem(ITALIC_CHECK);	
	Graph->LogFont.lfItalic=Italic->GetState()&0x003;
	S_MESSAGE	Message;
	Message.Msg=UM_PARAMCHANGE;
	Message.wParam=FONT_CHANGE;
	m_SignalWnd->Message.SendMessage(&Message);	
}

/*
	Esta funcion recalcula el area real del grafico
	teniendo en cuenta el espacio ocupado por
	las letras
*/
int CSignalWnd::ResizeGraph(DWORD pIndex)
{
	if (!m_SignalWnd->OnWindow)
		return false;
	S_GRAPHDATA*	GraphData=&m_SignalWnd->Grafica[pIndex];
	CClientDC		dc(this);
	CFont*			OldFont=dc.SelectObject(&GraphData->Font);

	float	MaxValue;	
	char	Cadena[20];
	char	Texto[10];
	DWORD	TextHeight;

	memset(Cadena,0,10);
	CRect	rect(0,0,10,10);
	dc.DrawText("qQgGaA,.yj;YJ",&rect,DT_SINGLELINE|DT_CALCRECT);
	GraphData->TextHeight=TextHeight=rect.Height();

	if (GraphData->EdgeXPos !=-1) Cadena[0]='-';
	if (GraphData->EdgeXPos == 0) 
		MaxValue=GraphData->MiliVoltsPerDiv*2;
	else
		MaxValue=GraphData->MiliVoltsPerDiv*4;
	sprintf(Texto,"%.1f",MaxValue);
	strcat(Cadena,Texto);
	
	dc.DrawText(Cadena,&rect,DT_SINGLELINE|DT_CALCRECT);
	GraphData->TextWidth=rect.Width();

	GraphData->GraphLeft=LEFT_SPACE1+LEFT_SPACE2+GraphData->TextWidth;
	GraphData->GraphRight=GraphData->Width-RIGHT_SPACE1;
	GraphData->GraphTop=TextHeight+TOP_SPACE1+TOP_SPACE2+TextHeight/2;
	GraphData->GraphBottom=GraphData->Height-BOTTOM_SPACE1-TextHeight/2;
	dc.SelectObject(OldFont);
	return true;
}
/*
	Dibuja el grafico especificado en el dc en memoria
*/
int CSignalWnd::DrawGraphic(DWORD pIndex)
{
	S_GRAPHDATA*	GraphData=&m_SignalWnd->Grafica[pIndex];
	CPen			EdgePen(PS_SOLID,0,GraphData->EdgesColor);
	CPen			SignalPen(PS_SOLID,0,GraphData->SignalColor);
	CMemDC*			dc=&m_SignalWnd->MemDC;
	CFont*			OldFont=dc->SelectObject(&GraphData->Font);
	CPen*			OldPen=dc->SelectObject(&EdgePen);

	DWORD Width=GraphData->Width;
	DWORD Height=GraphData->Height;
	DWORD Left=GraphData->GraphLeft;
	DWORD Right=GraphData->GraphRight;
	DWORD Top=GraphData->GraphTop;
	DWORD Bottom=GraphData->GraphBottom;
	DWORD TextHeight=GraphData->TextHeight;

	dc->SetBkMode(TRANSPARENT);
	dc->SetSize(Width,Height);
	dc->FillSolidRect(0,0,Width,Height,GraphData->BackColor);

	if (pIndex==m_SignalWnd->ActiveGraph)
	{
		CBrush	Brush(0x0000ff);
		CRect rect(0,0,Width,Height);
		dc->FrameRect(&rect,&Brush);
	}
	CRect rect(LEFT_SPACE1,TOP_SPACE1,Width-RIGHT_SPACE1,Top);
	dc->DrawText(GraphData->name,&rect,DT_SINGLELINE|DT_NOCLIP);

	// Ancho de la grafica
	Width=Right-Left;
	Height=Bottom-Top;
	DWORD PixelStep = (DWORD)(Width/GraphData->SamplesCant+1);
	float SamplesStep = (float)GraphData->SamplesCant/(float)Width+1;

	// Trazar eje Y
	dc->MoveTo(Left,Top);
	dc->LineTo(Left,Bottom);
	// Trazar lineas divisorias
	dc->MoveTo(Left,(Top+Bottom)/2);dc->LineTo(Right,(Top+Bottom)/2);
	dc->MoveTo(Left,Top);dc->LineTo(Right,Top);
	dc->MoveTo(Left,Bottom);dc->LineTo(Right,Bottom);
	dc->MoveTo(Left,Top+Height/4);dc->LineTo(Right,Top+Height/4);
	dc->MoveTo(Left,Bottom-Height/4);dc->LineTo(Right,Bottom-Height/4);
	dc->MoveTo(Right,Top);dc->LineTo(Right,Bottom);

	DWORD EjeXPos;
	float	MaxValue;	// Maximo vlor del grafico
	switch(GraphData->EdgeXPos)
	{
	case 1:
		{
			EjeXPos=Top;
			MaxValue=0;
			break;
		}
	case -1:
		{
			EjeXPos=Bottom;
			MaxValue=GraphData->MiliVoltsPerDiv*4;
			break;
		}
	default:
		{
			EjeXPos=(Bottom+Top)/2;
			MaxValue=GraphData->MiliVoltsPerDiv*2;
			break;
		}
	}
	// Dibujar los numeros 
	char Numero[500];
	DWORD PixelPerDiv=Height/4;
	rect.top=Top-TextHeight/2;
	rect.right=rect.left+GraphData->TextWidth;
	int i1;
	for (i1=0;i1<5;i1++)
	{
		sprintf(Numero,"%.1f",MaxValue);
		dc->DrawText(Numero,&rect,DT_SINGLELINE|DT_NOCLIP|DT_RIGHT);
		MaxValue-=GraphData->MiliVoltsPerDiv;
		rect.top+=PixelPerDiv;
	}

	float factor=GraphData->MiliVoltsPerUC*Height/(4*GraphData->MiliVoltsPerDiv);
	// Factor de conversion de UC a Pixels
	
	CRect rect2(LEFT_SPACE1,TOP_SPACE1,Width-RIGHT_SPACE1,Top);
	sprintf(Numero," Buffer Ptr %d Sample Step %.1f Pixel Step %d",GraphData->Buffer_Ptr,SamplesStep,PixelStep);
	dc->DrawText(Numero,&rect2,DT_SINGLELINE|DT_NOCLIP|DT_RIGHT);

	dc->SelectObject(&SignalPen);
	BOOL FirstPoint=true;
	dc->MoveTo(Right,EjeXPos);
	float i=(float)GraphData->Buffer_Ptr-1;
	float Pos;
	// Valor en Pixel de la salida
	for (DWORD x=Right;x>Left;x-=PixelStep)
	{
		if (i<0)
			i+=1024;
		Pos=EjeXPos-(GraphData->Buffer[(DWORD)i]*factor);
		if (Pos < Top) Pos=(float)Top;
		if (Pos > Bottom) Pos =(float)Bottom;
		
		if (FirstPoint)
		{
			dc->MoveTo(x,(int)Pos);
			FirstPoint=false;
		}
		else
			dc->LineTo(x,(int)Pos);
		i-=SamplesStep;
	}
	dc->SelectObject(OldPen);
	dc->SelectObject(OldFont);
	return true;
}

int CSignalWnd::DrawGraphics()
{
	if (!m_SignalWnd->OnWindow)
		return false;
	CClientDC dc(this);
	S_GRAPHDATA*	GraphData;
	DWORD i;
	for (i=0;i<m_SignalWnd->GraphCant;i++)
	{
		if (m_SignalWnd->OnPlay)
			GetSamples(i);
		GraphData=&m_SignalWnd->Grafica[i];
		if ((GraphData->OnShow)&&(m_SignalWnd->OnSize))
		{
			DrawGraphic(i);
			m_SignalWnd->MemDC.Swap(GraphData->Left,GraphData->Top,&dc);
		}
	}	
	if (!m_SignalWnd->OnGraph)
	{
		dc.FillSolidRect(m_SignalWnd->GraphLeft,
			m_SignalWnd->GraphTop,
			m_SignalWnd->GraphWidth,m_SignalWnd->GraphHeight,
			0x0);
		return false;
	}
	return true;
}

void CSignalWnd::OnChangeGraphName() 
{
	char	name[50];
	CEdit*	pWnd=(CEdit*)m_SignalWnd->DlgBar.GetDlgItem(IDC_GRAPH_NAME);
	pWnd->GetWindowText(name,49);
	S_MESSAGE	Message;
	Message.Msg=UM_PARAMCHANGE;
	Message.wParam=NAME_CHANGE;
	Message.ExtraData=name;
	m_SignalWnd->Message.SendMessage(&Message);
}

void CSignalWnd::OnSelchangePorDivCombo() 
{
	CComboBox* Volts=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(VOLT_POR_DIV_COMBO);
	DWORD Pos=Volts->GetCurSel();
	S_MESSAGE	Message;
	Message.ExtraData=&MiliVoltPerDivTable[Pos];
	Message.Msg=UM_PARAMCHANGE;
	Message.wParam=VOLTPERDIV_CHANGE;
	m_SignalWnd->Message.SendMessage(&Message);
}

// Tomar muestras de la grafica especifica
int CSignalWnd::GetSamples(DWORD pIndex)
{
	S_GRAPHDATA* pData=&m_SignalWnd->Grafica[pIndex];
	DWORD	Cant;
	DWORD	CantRead=0;
	// Desde Buffer_Ptr hacia atras estan las ultimas muestras
	// Cantidad de muestras que se pueden leer
	do 
	{
		Cant=pData->Buffer_Len-pData->Buffer_Ptr;
		ReadBuffer(pIndex,Cant,&CantRead,&pData->Buffer[pData->Buffer_Ptr]);
		pData->Buffer_Ptr+=CantRead;
		if (pData->Buffer_Ptr == pData->Buffer_Len)
			pData->Buffer_Ptr=0;
	} while (Cant==CantRead);
	return true;
}

int CSignalWnd::ReadBuffer(DWORD pIndex, DWORD pCant, DWORD *pCantRead, float *pBuffer)
{
	
	if (m_SignalWnd->OnDevice)
	{
		m_SignalWnd->Device->GetSignal(pIndex,pBuffer,pCant,(DWORD*)pCantRead);
		return true;
	}
	static int i=0;
	if (pCant > 1) pCant=1;
	for (DWORD j=0;j<pCant;j++)
	{
		pBuffer[j]=(float)(20*sin(i*3.14/180)-20*cos((i*2)*3.14/180)+5*sin(i*10*3.14/180));
		i++;
		if (i>360) i=0;
	}
	*pCantRead=pCant;
	return true;
}

int CSignalWnd::ResizeAllGraphics()
{
	for (DWORD i=0;i<m_SignalWnd->GraphCant;i++)
	{
		ResizeGraph(i);
	}
	return true;
}

int CSignalWnd::SetSignalDevice(CSignalDevice *pDevice)
{
	S_SIGNALWND* Data=m_SignalWnd;
	m_SignalWnd->Device=pDevice;
	m_SignalWnd->OnDevice=true;
	// Actualizacion de los parametros del puerto
	pDevice->SetPort(PORTS[Data->PortIndex]);
	pDevice->SetParity(PARITY[Data->ParityIndex].val);
	pDevice->SetStopBits((BYTE)STOPBITS[Data->StopBitsIndex].val);
	pDevice->SetByteSize((BYTE)BYTESIZE[Data->ByteSizeIndex].val);
	pDevice->SetBaudRate(BAUDRATE[Data->BaudRateIndex].val);
	// Actualizacion de la ventana de notificacion
	if (m_SignalWnd->OnWindow)
		pDevice->SetNotifyWindow(this->GetSafeHwnd());
	// Actualizar todos los coeficientes
	DWORD i;
	for (i=0;i<m_SignalWnd->GraphCant;i++)
	{
		S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[i];
		DWORD Pos=Graph->FilterIndex;
		if (SIGNALS_FILTERS[i].Cant)
		{
			m_SignalWnd->Device->SetFilterCoef(i,
				SIGNALS_FILTERS[i].Filters[Pos].CoefA,
				SIGNALS_FILTERS[i].Filters[Pos].CoefB,
				SIGNALS_FILTERS[i].Filters[Pos].Order);
		}
	}
	return true;
}

void CSignalWnd::OnSelchangeSamplesCant() 
{
	CComboBox* SC=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_SAMPLES_CANT);
	DWORD Pos=SC->GetCurSel();
	S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph];
	Graph->SamplesCant=SamplesCantTable[Pos];
	InvalidateGraph();
}

/*
	Lee toda la informacion de las variables de la clase
*/
int CSignalWnd::ReadDataFromFile(char *pFileName)
{
	FILE *fd;
	DWORD AG=0;
	S_GRAPHDATA* Graph;
	S_SIGNALWND* Data =m_SignalWnd;
	DWORD	Temp;
	if ((fd=fopen(pFileName,"rb"))==NULL)
	{
		return SaveDataToFile(pFileName);	
	}
	char Param[50];
	while(fscanf(fd,"%s",Param)>0)
	{
		DWORD i;
		for (i=0;i<ParamTableMax;i++)
		{
			if (strcmp(Param,PT[i])==0)
				break;
		}
		switch (i)
		{
		case 0:
			{
				fscanf(fd,"%d",&Temp);
				break;
			}
		case 1:
			{
				fscanf(fd,"%d",&m_SignalWnd->ActiveGraph);
				break;
			}
		case 2:
			{
				fscanf(fd,"%f",&m_SignalWnd->Grafica[AG].SamplesCant);
				break;
			}
		case 3:
			{
				fscanf(fd,"%d",&AG);
				if (AG >= m_SignalWnd->GraphCant)
				{
					fclose(fd);
					return SaveDataToFile(pFileName);
				}
				Graph=&m_SignalWnd->Grafica[AG];
				break;
			}
		case 4:
			{
				fscanf(fd,"%d",&Graph->Buffer_Len);
				break;
			}
		case 5:
			{
				fscanf(fd,"%d",&Graph->EdgesColor);
				break;
			}
		case 6:
			{
				fscanf(fd,"%d",&Graph->EdgeXPos);
				break;
			}
		case 7:
			{
				fscanf(fd,"%f",&Graph->MiliVoltsPerDiv);
				break;
			}
		case 8:
			{
				fscanf(fd,"%f",&Graph->MiliVoltsPerUC);
				break;
			}
		case 9:
			{
				fgets(Graph->name,2,fd);
				fgets(Graph->name,50,fd);
				Graph->name[strlen(Graph->name)-1]=0;
				break;
			}
		case 10:
			{
				fscanf(fd,"%d",&Graph->OnShow);
				break;
			}
		case 11:
			{
				fgets(Graph->LogFont.lfFaceName,2,fd);
				fgets(Graph->LogFont.lfFaceName,32,fd);
				Graph->LogFont.lfFaceName[strlen(Graph->LogFont.lfFaceName)-1]=0;
				break;
			}
		case 12:
			{
				fscanf(fd,"%d",&Graph->LogFont.lfItalic);
				break;
			}
		case 13:
			{
				fscanf(fd,"%d",&Graph->LogFont.lfWeight);
				break;
			}
		case 14:
			{
				fscanf(fd,"%d",&Graph->SignalColor);
				break;
			}
		case 15:
			{
				fscanf(fd,"%d",&Graph->BackColor);
				break;
			}
		case 16:
			{
				fscanf(fd,"%d",&Data->PortIndex);
				break;
			}
		case 17:
			{
				fscanf(fd,"%d",&Data->ByteSizeIndex);
				break;
			}
		case 18:
			{
				fscanf(fd,"%d",&Data->StopBitsIndex);
				break;
			}
		case 19:
			{
				fscanf(fd,"%d",&Data->BaudRateIndex);
				break;
			}
		case 20:
			{
				fscanf(fd,"%d",&Data->ParityIndex);
				break;
			}
		case 21:
			{
				fscanf(fd,"%d",&Graph->FilterIndex);
				break;
			}
		default:
			{
				fclose(fd);
				return SaveDataToFile(pFileName);
			}
		}
	}
	fclose(fd);
	return true;
}

int CSignalWnd::SaveDataToFile(char *pFileName)
{
	S_SIGNALWND* Data = m_SignalWnd;
	FILE *fd;
	if ((fd=fopen(pFileName,"wb"))==NULL)
	{
		return false;
	}
	fprintf(fd,"%s %d\n",PT[0],m_SignalWnd->GraphCant);
	fprintf(fd,"%s %d\n",PT[1],m_SignalWnd->ActiveGraph);
	fprintf(fd,"%s %d\n",PT[16],Data->PortIndex);
	fprintf(fd,"%s %d\n",PT[17],Data->ByteSizeIndex);
	fprintf(fd,"%s %d\n",PT[18],Data->StopBitsIndex);
	fprintf(fd,"%s %d\n",PT[19],Data->BaudRateIndex);
	fprintf(fd,"%s %d\n",PT[20],Data->ParityIndex);
	
	DWORD i;
	for (i=0;i<m_SignalWnd->GraphCant;i++)
	{
		S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[i];
		fprintf(fd,"%s %.2f\n",PT[2],Graph->SamplesCant);
		fprintf(fd,"%s %d\n",PT[3],i);
		fprintf(fd,"%s %d\n",PT[4],Graph->Buffer_Len);
		fprintf(fd,"%s %d\n",PT[5],Graph->EdgesColor);
		fprintf(fd,"%s %d\n",PT[6],Graph->EdgeXPos);
		fprintf(fd,"%s %.2f\n",PT[7],Graph->MiliVoltsPerDiv);
		fprintf(fd,"%s %.2f\n",PT[8],Graph->MiliVoltsPerUC);
		fprintf(fd,"%s %s\n",PT[9],Graph->name);
		fprintf(fd,"%s %d\n",PT[10],Graph->OnShow);
		fprintf(fd,"%s %s\n",PT[11],Graph->LogFont.lfFaceName);
		fprintf(fd,"%s %d\n",PT[12],Graph->LogFont.lfItalic);
		fprintf(fd,"%s %d\n",PT[13],Graph->LogFont.lfWeight);
		fprintf(fd,"%s %d\n",PT[14],Graph->SignalColor);
		fprintf(fd,"%s %d\n",PT[15],Graph->BackColor);
		fprintf(fd,"%s %d\n",PT[21],Graph->FilterIndex);
	}
	fclose(fd);
	return true;
}

/*
	Inicializa los valores por defecto de todas las 
	variables
*/
int CSignalWnd::LoadDefaultData()
{
	S_SIGNALWND* Data=m_SignalWnd;
	Data->PortIndex=1;
	Data->ByteSizeIndex=3;
	Data->ParityIndex=2;
	Data->StopBitsIndex=0;
	Data->BaudRateIndex=6;

	m_SignalWnd->GraphCant=6;
	
	for (DWORD i=0;i<m_SignalWnd->GraphCant;i++)
	{
		S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[i];
		Graph->Buffer_Ptr=0;
		Graph->SamplesCant=500;
		Graph->Top=0;
		Graph->Height=0;
		Graph->EdgesColor=16711680;
		Graph->BackColor=12632256;
		Graph->SignalColor=65535;
		Graph->MiliVoltsPerDiv=100;
		Graph->MiliVoltsPerUC=1;
		Graph->Buffer_Ptr=0;
		Graph->OnShow=true;
		Graph->EdgeXPos=0;
		Graph->Buffer_Len=1024;
		sprintf(Graph->name,"Graphic %d",i+1);
		Graph->FilterIndex=0;
		
		memset(&Graph->LogFont,0,sizeof(LOGFONT));
		strcpy(Graph->LogFont.lfFaceName,"Arial");
		Graph->LogFont.lfHeight=-12;
		Graph->LogFont.lfWidth=0;
		Graph->LogFont.lfWeight=FW_NORMAL;
		Graph->LogFont.lfOutPrecision=3;
		Graph->LogFont.lfClipPrecision=2;
		Graph->LogFont.lfQuality=1;
		Graph->LogFont.lfPitchAndFamily=34;
		Graph->LogFont.lfCharSet=ANSI_CHARSET;
		Graph->LogFont.lfItalic = false;

		for (unsigned long j=0;j< Graph->Buffer_Len;j++)
		{
			Graph->Buffer[j]=(float)(20*sin(j*3.14/180)-20*cos((j*2)*3.14/180)+5*sin(j*10*3.14/180));
		}
	}
	m_SignalWnd->ActiveGraph=0;
	m_SignalWnd->Grafica[1].OnShow =false;
	strcpy(m_SignalWnd->Grafica[0].name,"Input Signal");
	strcpy(m_SignalWnd->Grafica[1].name,"Temperature");
	strcpy(m_SignalWnd->Grafica[2].name,"IEEG");
	strcpy(m_SignalWnd->Grafica[3].name,"8-14Hz");
	strcpy(m_SignalWnd->Grafica[4].name,"REEG");
	strcpy(m_SignalWnd->Grafica[5].name,"Muscle (EMG)");
	return true;
}

/*
	Actualizar el Dialog Bar con los
	parametros de la grafica activa
*/
int CSignalWnd::UpDateDlgBar()
{
	if (m_SignalWnd->ActiveGraph >= m_SignalWnd->GraphCant)
		return false;
	DWORD AG=m_SignalWnd->ActiveGraph;
	S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[AG];
	// Actualizacion del font
	char Name[40];
	DWORD i;
	S_MESSAGE	Message;
	CComboBox* Combo;
	CButton* pButtom;
	CWnd*    pWnd;

	Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(FONT_COMBOBOX);
	for (i=0;i<(DWORD)Combo->GetCount();i++)
	{
		Combo->GetLBText(i,Name);
		if (strcmp(Name,Graph->LogFont.lfFaceName)==0)
			break;
	}
	if (i<(DWORD)Combo->GetCount())
		Combo->SetCurSel(i);
	else
	{
		Combo->GetLBText(0,Graph->LogFont.lfFaceName);
		Combo->SetCurSel(0);
		
		Message.Msg=UM_PARAMCHANGE;
		Message.wParam=FONT_CHANGE;
		m_SignalWnd->Message.SendMessage(&Message);
	}
	// Actualizacion de los MiliVolts por Div 
	
	Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(VOLT_POR_DIV_COMBO);
	for (i=0;i<MaxMiliPerDiv;i++)
	{
		if (MiliVoltPerDivTable[i]==Graph->MiliVoltsPerDiv)
			break;
	}
	if (i<MaxMiliPerDiv)
		Combo->SetCurSel(i);
	else 
	{
		Combo->SetCurSel(0);
		Message.Msg=UM_PARAMCHANGE;
		Message.wParam=VOLTPERDIV_CHANGE;
		Message.ExtraData=&MiliVoltPerDivTable[0];
		m_SignalWnd->Message.SendMessage(&Message);
	}

	// Actualizacion de la cantidad de muestras
	Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_SAMPLES_CANT);
	for (i=0;i<MaxSamCant;i++)
	{
		if (SamplesCantTable[i]==Graph->SamplesCant)
			break;
	}
	if (i<MaxSamCant)
		Combo->SetCurSel(i);
	else 
	{
		Combo->SetCurSel(0);
		Graph->SamplesCant=SamplesCantTable[0];
	}

	Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_EDGE_POS);
	for (i=0;i<MAXEDGEPOS;i++)
	{
		if (EdgePosTable[i]==Graph->EdgeXPos)
			break;
	}
	if (i<MAXEDGEPOS)
		Combo->SetCurSel(i);
	else 
	{
		Combo->SetCurSel(0);
		Graph->EdgeXPos=EdgePosTable[0];
	}

	CEdit*	pEdit=(CEdit*)m_SignalWnd->DlgBar.GetDlgItem(IDC_GRAPH_NAME);
	pEdit->SetWindowText(Graph->name);

	pButtom=(CButton*)m_SignalWnd->DlgBar.GetDlgItem(ITALIC_CHECK);	
	pButtom->SetCheck(Graph->LogFont.lfItalic);

	pButtom=(CButton*)m_SignalWnd->DlgBar.GetDlgItem(BOLD_CHECK);	
	if (Graph->LogFont.lfWeight==FW_BOLD)
		pButtom->SetCheck(true);
	else
		pButtom->SetCheck(false);

	pButtom=(CButton*)m_SignalWnd->DlgBar.GetDlgItem(IDC_SHOW);	
	pButtom->SetCheck(Graph->OnShow);

	pWnd=m_SignalWnd->DlgBar.GetDlgItem(IDC_GRAPH);	
	sprintf(Name,"Graph %d",AG+1);
	pWnd->SetWindowText(Name);
	/*
		Actualizacion del filtro de la senal
	*/
	Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_FILTER);
	Combo->ResetContent();
	DWORD	Cant=SIGNALS_FILTERS[m_SignalWnd->ActiveGraph].Cant;
	for (i=0;i<Cant;i++)
	{
		Combo->AddString(SIGNALS_FILTERS[m_SignalWnd->ActiveGraph].Filters[i].Caption);
	}
	Combo->EnableWindow(!Cant==0);
	if (Cant)
		Combo->SetCurSel(Graph->FilterIndex);
	return true;
}

/*
	Inicializa todos los combobox con los valores que 
	pueden tomar para esto se vale de todos los arreglos 
	definidos en el programa
*/
int CSignalWnd::InitDlgBar()
{
	LOGFONT LogFont;
	DWORD i;
	char Number[10];
	CButton* pButton;
	CComboBox* Combo;
	CDialogBar* Dlg=&m_SignalWnd->DlgBar;
	S_SIGNALWND* Data=m_SignalWnd;

	CClientDC dc(this);
	memset(&LogFont,0,sizeof(LOGFONT));
	LogFont.lfCharSet=ANSI_CHARSET;
	LogFont.lfFaceName[0] =0;
	LogFont.lfPitchAndFamily=0;
	::EnumFontFamiliesEx(dc,&LogFont,(FONTENUMPROC)EnumFontFamExProc,(DWORD)this,0);

	Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(FONT_COMBOBOX);
	Combo->SetCurSel(0);
	Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(VOLT_POR_DIV_COMBO);
	for (i=0;i<MaxMiliPerDiv;i++)
	{
		sprintf(Number,"%.1f mV",MiliVoltPerDivTable[i]);
		Combo->AddString(Number);
	}
	Combo->SetCurSel(0);

	Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_SAMPLES_CANT);
	for (i=0;i<MaxSamCant;i++)
	{
		sprintf(Number,"%.1f",SamplesCantTable[i]);
		Combo->AddString(Number);
	}
	Combo->SetCurSel(0);	

	Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_EDGE_POS);
	for (i=0;i<MAXEDGEPOS;i++)
	{
		Combo->AddString(EdgePosString[i]);
	}

	CEdit*	pWnd=(CEdit*)m_SignalWnd->DlgBar.GetDlgItem(IDC_GRAPH_NAME);
	pWnd->SetLimitText(49);

	CBitmap Bitmap;
	Bitmap.LoadBitmap("OPEN_BITMAP");
	pButton=(CButton*)m_SignalWnd->DlgBar.GetDlgItem(IDC_CLOSE);
	pButton->SetBitmap(Bitmap);
	pButton=(CButton*)m_SignalWnd->DlgBar.GetDlgItem(IDC_OPEN_CLOSE2);
	pButton->SetBitmap(Bitmap);
	Bitmap.Detach();

	// Actualizacion de los combobox que tienen que 
	// ver con el puerto

	Combo=(CComboBox*)Dlg->GetDlgItem(IDC_PORT);
	for (i=0;i<MAXPORTS;i++)
	{
		Combo->AddString(PORTS[i]);
	}
	Combo->SetCurSel(Data->PortIndex);

	Combo=(CComboBox*)Dlg->GetDlgItem(IDC_BYTESIZE);
	for (i=0;i<MAXBYTESIZE;i++)
	{
		Combo->AddString(BYTESIZE[i].str);
	}
	Combo->SetCurSel(Data->ByteSizeIndex);

	Combo=(CComboBox*)Dlg->GetDlgItem(IDC_STOPBITS);
	for (i=0;i<MAXSTOPBITS;i++)
	{
		Combo->AddString(STOPBITS[i].str);
	}
	Combo->SetCurSel(Data->StopBitsIndex);

	Combo=(CComboBox*)Dlg->GetDlgItem(IDC_PARITY);
	for (i=0;i<MAXPARITY;i++)
	{
		Combo->AddString(PARITY[i].str);
	}
	Combo->SetCurSel(Data->ParityIndex);

	Combo=(CComboBox*)Dlg->GetDlgItem(IDC_BAUDRATE);
	for (i=0;i<MAXBAUDRATE;i++)
	{
		Combo->AddString(BAUDRATE[i].str);
	}
	Combo->SetCurSel(Data->BaudRateIndex);

	return true;
}

void CSignalWnd::OnNext() 
{
	if (m_SignalWnd->ActiveGraph < m_SignalWnd->GraphCant-1)
		SetActiveGraph(m_SignalWnd->ActiveGraph+1);
}

void CSignalWnd::OnPrev() 
{
	if (m_SignalWnd->ActiveGraph > 0)
		SetActiveGraph(m_SignalWnd->ActiveGraph-1);
}

void CSignalWnd::OnShow() 
{
	CButton* pButtom=(CButton*)m_SignalWnd->DlgBar.GetDlgItem(IDC_SHOW);	
	S_MESSAGE	Message;
	Message.Msg=UM_PARAMCHANGE;
	Message.wParam=SHOW_CHANGE;		
	Message.lParam=pButtom->GetCheck();
	m_SignalWnd->Message.SendMessage(&Message);
}

void CSignalWnd::OnEdgePos() 
{
	CComboBox* Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_EDGE_POS);
	DWORD Pos=Combo->GetCurSel();
	S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph];
	Graph->EdgeXPos=EdgePosTable[Pos];
	InvalidateGraph();
}

void CSignalWnd::OnEdgeColor() 
{
	S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph];
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK)
	{
		Graph->EdgesColor=dlg.GetColor();
		InvalidateGraph();
	}
}

void CSignalWnd::OnSignalColor() 
{
	S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph];
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK)
	{
		Graph->SignalColor=dlg.GetColor();
		InvalidateGraph();
	}
}

void CSignalWnd::OnBackColor() 
{
	S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[m_SignalWnd->ActiveGraph];
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK)
	{
		Graph->BackColor=dlg.GetColor();
		InvalidateGraph();
	}
	
}

void CSignalWnd::OnOpenClose2() 
{
	m_SignalWnd->OnCommDlg=!m_SignalWnd->OnCommDlg;
	ResizeDlgBar();
}

int CSignalWnd::EnableCommProperties(BOOL pEnable)
{
	CDialogBar* Dlg=&m_SignalWnd->DlgBar;	
	Dlg->GetDlgItem(IDC_PORT)->EnableWindow(pEnable);
	Dlg->GetDlgItem(IDC_BYTESIZE)->EnableWindow(pEnable);
	Dlg->GetDlgItem(IDC_STOPBITS)->EnableWindow(pEnable);
	Dlg->GetDlgItem(IDC_PARITY)->EnableWindow(pEnable);
	Dlg->GetDlgItem(IDC_BAUDRATE)->EnableWindow(pEnable);
	Dlg->GetDlgItem(IDC_PORT_OPEN)->EnableWindow(pEnable);
	Dlg->GetDlgItem(IDC_PORT_CLOSE)->EnableWindow(pEnable);
	Dlg->GetDlgItem(IDC_PORT_APPLY)->EnableWindow(pEnable);
	return true;
}

void CSignalWnd::OnSelchangeBaudrate() 
{
	CComboBox* Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_BAUDRATE);
	m_SignalWnd->BaudRateIndex=Combo->GetCurSel();	
	if (m_SignalWnd->OnDevice)
		m_SignalWnd->Device->SetBaudRate(BAUDRATE[m_SignalWnd->BaudRateIndex].val);
	
}

void CSignalWnd::OnSelchangeBytesize() 
{
	CComboBox* Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_BYTESIZE);
	m_SignalWnd->ByteSizeIndex=Combo->GetCurSel();	
	if (m_SignalWnd->OnDevice)
		m_SignalWnd->Device->SetByteSize((BYTE)BYTESIZE[m_SignalWnd->ByteSizeIndex].val);
}

void CSignalWnd::OnSelchangeParity() 
{
	CComboBox* Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_PARITY);
	m_SignalWnd->ParityIndex=Combo->GetCurSel();	
	if (m_SignalWnd->OnDevice)
		m_SignalWnd->Device->SetParity(PARITY[m_SignalWnd->ParityIndex].val);
}

void CSignalWnd::OnSelchangePort() 
{
	CComboBox* Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_PORT);
	m_SignalWnd->PortIndex=Combo->GetCurSel();	
	if (m_SignalWnd->OnDevice)
		m_SignalWnd->Device->SetPort(PORTS[m_SignalWnd->PortIndex]);
}

void CSignalWnd::OnSelchangeStopbits() 
{
	CComboBox* Combo=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_STOPBITS);
	m_SignalWnd->StopBitsIndex=Combo->GetCurSel();	
	if (m_SignalWnd->OnDevice)
		m_SignalWnd->Device->SetStopBits((BYTE)STOPBITS[m_SignalWnd->StopBitsIndex].val);
}

void CSignalWnd::OnPortOpen() 
{
	if (m_SignalWnd->OnDevice)
		m_SignalWnd->Device->OpenDevice();
}

void CSignalWnd::OnPortClose() 
{
	if (m_SignalWnd->OnDevice)
		m_SignalWnd->Device->ClosePort();
}

void CSignalWnd::OnPortApply() 
{
}

int CSignalWnd::InvalidateGraph()
{
	if (m_SignalWnd->OnPlay)
		return true;
	S_MESSAGE	Message;
	Message.Msg=WM_PAINT;
	m_SignalWnd->Message.SendMessage(&Message);	
	return true;
}

void CSignalWnd::OnSelchangeFilter() 
{		
	DWORD AG=m_SignalWnd->ActiveGraph;
	CComboBox*	Filter=(CComboBox*)m_SignalWnd->DlgBar.GetDlgItem(IDC_FILTER);
	DWORD Pos=Filter->GetCurSel();
	S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[AG];
	Graph->FilterIndex=Pos;
	if (m_SignalWnd->OnDevice)
	{
		m_SignalWnd->Device->SetFilterCoef(AG,
			SIGNALS_FILTERS[AG].Filters[Pos].CoefA,
			SIGNALS_FILTERS[AG].Filters[Pos].CoefB,
			SIGNALS_FILTERS[AG].Filters[Pos].Order);
	}
}

int CSignalWnd::SendNullMessage()
{
	S_MESSAGE Msg;
	Msg.Msg=UM_NULL;
	m_SignalWnd->Message.SendMessage(&Msg);
	return true;
}

int CSignalWnd::Start()
{
	m_SignalWnd->OnPlay=true;
	SendNullMessage();
	return true;
}

int CSignalWnd::Stop()
{
	m_SignalWnd->OnPlay=false;
	SendNullMessage();
	return true;
}

LRESULT CSignalWnd::OnDeviceState(WPARAM wParam,LPARAM lParam)
{
	CWnd* pWnd=GetParent();
	switch (wParam)
	{
	case GETING_DATA:
		{
			Start();
			pWnd->SetWindowText("Device Sending Data");
			break;
		}
	case UKNOW_STATE:
		{
			Stop();
			pWnd->SetWindowText("Device No Present");
			break;
		}
	case  PRESENT:
		{
			pWnd->SetWindowText("Device Present");
			break;
		}
	}
	return 0;
}

void CSignalWnd::OnDeviceStart() 
{
	m_SignalWnd->Device->StartData();
	
}

void CSignalWnd::OnDeviceStop() 
{
	m_SignalWnd->Device->StopData();	
}

void CSignalWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetActiveGraph(PointToGraph(point));
}

/*
	Devuelve el indice de la grafica que se encuentra en ese pto
*/
DWORD CSignalWnd::PointToGraph(CPoint point)
{
	DWORD i;
	S_GRAPHDATA* Data;
	for (i=0;i<m_SignalWnd->GraphCant;i++)
	{
		Data=&m_SignalWnd->Grafica[i];
		DWORD Right=Data->Left+Data->Width ,Bottom=Data->Top+Data->Height ;
		if (Data->OnShow)
		{
			if ((point.x > Data->Left)&&(point.x < Right)
				&&( point.y > Data->GraphTop)&&(point.y < Bottom))
				return i;
		}
	}
	return i;
}
/*
	Cambia la grafica activa
*/
int CSignalWnd::SetActiveGraph(DWORD pIndex)
{
	if (m_SignalWnd->ActiveGraph!=pIndex)
	{
		m_SignalWnd->ActiveGraph=pIndex;
		UpDateDlgBar();	
		InvalidateGraph();
	}
	return true;
}

int CSignalWnd::ThreadOnSize(S_MESSAGE *pMsg)
{
	WORD nWidth = LOWORD(pMsg->lParam); 
	WORD nHeight = HIWORD(pMsg->lParam);
	if ((nWidth==0)||(nHeight==0))
	{
		m_SignalWnd->OnSize=false;
		return true;
	}
	m_SignalWnd->OnSize=true;
	// Quitar el area ocupada por el dialogo
	if (m_SignalWnd->OnFontDlg)
	{
		if (m_SignalWnd->OnCommDlg)
			nWidth-=DLG_BAR_MAX_SIZE;
		else
			nWidth-=DLG_BAR_MED_SIZE;
	}
	else
		nWidth-=DLG_BAR_MIN_SIZE;
	// comprobar si ha cambiado el tamaño del grafico
	if ((m_SignalWnd->GraphWidth !=nWidth)||(m_SignalWnd->GraphHeight!=nHeight))
	{
		m_SignalWnd->GraphLeft=0;
		m_SignalWnd->GraphTop=0;
		m_SignalWnd->GraphWidth=nWidth;
		m_SignalWnd->GraphHeight=nHeight;
		CalcGraphSize();
		ResizeAllGraphics();
	}
	return true;	
}

int CSignalWnd::ThreadInit()
{
	m_SignalWnd->GraphLeft=0;
	m_SignalWnd->GraphTop=0;
	m_SignalWnd->GraphWidth=0;
	m_SignalWnd->GraphHeight=0;
	ThreadCreateAllFonts();
	return true;
}

int CSignalWnd::ThreadCreateAllFonts()
{
	DWORD i;
	for (i=0;i<m_SignalWnd->GraphCant;i++)
	{
		S_GRAPHDATA* Graph=&m_SignalWnd->Grafica[i];
		Graph->Font.CreateFontIndirect(&Graph->LogFont);
	}
	return true;
}
