#if !defined(AFX_SIGC01_H__F977AE6C_67EC_11D4_8632_00D0093D4380__INCLUDED_)
#define AFX_SIGC01_H__F977AE6C_67EC_11D4_8632_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sigC02.h"
#include "sigC03.h"
#include "sigC05.h"

#define GRAPH_CANT	12
#define BAR_SIZE	0.1

/////////////////////////////////////////////////////////////////////////////
// CSignalWnd window

// Datos que posee un grafico en especifico
typedef struct
{
	int		EdgeXPos;   // 0 Centro 1 arriba -1 abajo
	char	name[50];
	char	Unit[10];	// Unidad de medida
	// Posicion del grafico dentro de  la ventana
	WORD	Left,Top,Width,Height;
	// Posicion de la grafica dentro del grafico
	WORD	GraphLeft,GraphTop,GraphRight,GraphBottom;

	float	MiliVoltsPerUC;
	float	MiliVoltsPerDiv;
	float	SamplesPerSecond;
	float	SecondsPerDiv;
	//buffer de datos
	float	Buffer[1024];
	DWORD	Buffer_Ptr;
	DWORD	Buffer_Len;
	float	SamplesCant; // Cantidad de muestras en pantalla
	WORD	TextWidth;
	WORD	TextHeight;
	BOOL	OnShow;
	COLORREF		EdgesColor;
	COLORREF		SignalColor;
	COLORREF		BackColor;
	LOGFONT	LogFont;
	CFont	Font;
	DWORD	FilterIndex;

} S_GRAPHDATA;

typedef struct 
{
	//CDialogBar	DlgBar;
	// Mensajes al hilo de ejecucion
	CMessageEvent	Message;
	CWinThread*		Thread;
	// VARIABLES DEL HILO
	CMemDC	MemDC;
	/*
	BOOL	OnFontDlg;
	BOOL	OnCommDlg;
	*/
	// Posicion de la grafica dentro de la ventana
	int	GraphLeft,GraphTop,GraphWidth,GraphHeight;
	// Cantidad de graficos que se estan mostrando
	DWORD	GraphCant;
	// Grafica Activa
	DWORD	ActiveGraph;
	// Propiedades de las graficas
	S_GRAPHDATA	Grafica[GRAPH_CANT];    // Cantidad de graficas
	
	// Dispositivo que entrega las senales
	CSignalDevice*	Device;
	BOOL			OnDevice;
	// Configiracion del dispositivo
	UINT PortIndex,ParityIndex,
		 StopBitsIndex,BaudRateIndex,ByteSizeIndex;
	// Sincronizacion
	// Indica al hilo que debe adquirir muetras
	BOOL	OnPlay;
	// Indica al hilo que la ventana es valida y se puede dibujar
	BOOL	OnWindow;
	// Indica que no hay graficas por dibujar
	BOOL	OnGraph;
	// Indica que la ventana posee un tamano valido
	BOOL	OnSize;
	// Indica que se estan mostrando el espectro de frecuencia y las barras
	BOOL	OnFrecGraph,OnBarGraph;
} S_SIGNALWND;


struct graphic_state
{
  int index;
  bool state;
  char *name;
};

typedef struct graphic_state Graphic_State; 

class AFX_EXT_CLASS CSignalWnd : public CWnd
{
// Construction
public:
	CSignalWnd();
    Graphic_State st;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSignalWnd)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD DrawGraphicBar(DWORD pIndex);
	void ChangeViewFrec(bool state);
	void ChangeAxisPosition(DWORD Pos);
	void ChangeSamplesCant(DWORD Cant);
	void OnGridColor();
	void ChangeVoltPorDiv(DWORD Pos);
	void ChangeGraphName(char *name, int index);
	void ShowGraphic(bool state, int index);
	DWORD ShowAll();
	int ThreadInit();
	int ThreadOnSize(S_MESSAGE* pMsg);
	int SetActiveGraph(DWORD pIndex);
	DWORD PointToGraph(CPoint point);
	int Stop();
	int Start();
	int SendNullMessage();
	int InvalidateGraph();
	int LoadDefaultData();
	int SaveDataToFile(char* pFileName);
	int ReadDataFromFile(char* pFileName);
	int SetSignalDevice(CSignalDevice* pDevice);
	int ResizeAllGraphics();
	int ReadBuffer(DWORD pIndex,DWORD pCant,DWORD* pCantRead,float* pBuffer);
	int GetSamples(DWORD pIndex);
	int DrawGraphics();
	int DrawGraphic(DWORD pIndex);
	int ResizeGraph(DWORD pIndex);
	int CalcGraphSize();
	int ThreadCreateAllFonts();
	
	UINT ThreadMain();
	int InitSignalWnd();
	S_SIGNALWND* m_SignalWnd;
	virtual ~CSignalWnd();
	// Generated message map functions
//protected:
	int ThreadGetMessage();
	int ThreadProcessMessage();
	//{{AFX_MSG(CSignalWnd)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNext();
	afx_msg void OnPrev();
	afx_msg void OnEdgeColor();
	afx_msg void OnSignalColor();
	afx_msg void OnBackColor();
	afx_msg void OnPortOpen();
	afx_msg void OnPortClose();
	afx_msg LRESULT OnDeviceState(WPARAM wParam,LPARAM lParam);
	afx_msg void OnDeviceStart();
	afx_msg void OnDeviceStop();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static UINT ThreadProc(LPVOID pParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIGC01_H__F977AE6C_67EC_11D4_8632_00D0093D4380__INCLUDED_)
