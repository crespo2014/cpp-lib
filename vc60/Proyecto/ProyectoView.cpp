// ProyectoView.cpp : implementation of the CProyectoView class
//

#include "stdafx.h"
#include "Proyecto.h"

#include "ProyectoDoc.h"
#include "ProyectoView.h"

#include "T_CR_DLG.h"
#include "T_CT_DLG.h"
#include "T_CS_DLG.h"
#include "T_S_DLG.h"
#include "T_MSG_DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProyectoView

IMPLEMENT_DYNCREATE(CProyectoView, CView)

BEGIN_MESSAGE_MAP(CProyectoView, CView)
	//{{AFX_MSG_MAP(CProyectoView)
	ON_COMMAND(ID_CONFIGURAR_DIMENSIONES, OnConfigurarDimensiones)
	ON_COMMAND(ID_CONFIGURAR_RECEPTOR, OnConfigurarReceptor)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURAR_RECEPTOR, OnUpdateConfigurarReceptor)
	ON_COMMAND(ID_CONFIGURAR_SUPERFICIE, OnConfigurarSuperficie)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURAR_SUPERFICIE, OnUpdateConfigurarSuperficie)
	ON_COMMAND(ID_CONFIGURAR_TRANSMISOR, OnConfigurarTransmisor)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURAR_TRANSMISOR, OnUpdateConfigurarTransmisor)
	ON_COMMAND(ID_CERRAR, OnCerrar)
	ON_UPDATE_COMMAND_UI(ID_CERRAR, OnUpdateCerrar)
	ON_COMMAND(ID_GUARDAR, OnGuardar)
	ON_UPDATE_COMMAND_UI(ID_GUARDAR, OnUpdateGuardar)
	ON_COMMAND(ID_NUEVO, OnNuevo)
	ON_UPDATE_COMMAND_UI(ID_NUEVO, OnUpdateNuevo)
	ON_COMMAND(ID_SIMULACION, OnSimulacion)
	ON_UPDATE_COMMAND_UI(ID_SIMULACION, OnUpdateSimulacion)
	ON_COMMAND(ID_ABRIR, OnAbrir)
	ON_UPDATE_COMMAND_UI(ID_ABRIR, OnUpdateAbrir)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURAR_DIMENSIONES, OnUpdateConfigurarDimensiones)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProyectoView construction/destruction

CProyectoView::CProyectoView()
{
	// TODO: add construction code here

}

CProyectoView::~CProyectoView()
{
}

BOOL CProyectoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CProyectoView drawing

void CProyectoView::OnDraw(CDC* pDC)
{
	CProyectoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CProyectoView printing

BOOL CProyectoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProyectoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProyectoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CProyectoView diagnostics

#ifdef _DEBUG
void CProyectoView::AssertValid() const
{
	CView::AssertValid();
}

void CProyectoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProyectoDoc* CProyectoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProyectoDoc)));
	return (CProyectoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProyectoView message handlers

void CProyectoView::OnConfigurarDimensiones() 
{
	CProyectoDoc* pDoc = GetDocument();
 	T_CD	Dlg;
 	Dlg.m_altura=pDoc->Canal->altura;
 	Dlg.m_ancho=pDoc->Canal->ancho;
 	Dlg.m_largo=pDoc->Canal->largo;
 	if (Dlg.DoModal()== IDOK)
 	{
 		pDoc->Canal->SetAltura(Dlg.m_altura);
 		pDoc->Canal->SetAncho(Dlg.m_ancho);
 		pDoc->Canal->SetLargo(Dlg.m_largo);
 		pDoc->m_OnDim=TRUE;
		pDoc->m_OnChange=TRUE;
 	}	
}

void CProyectoView::OnConfigurarReceptor() 
{
	CProyectoDoc* pDoc = GetDocument();
	T_CR_DLG Dlg;
	Dlg.lpCanal=pDoc->Canal;
	if (Dlg.DoModal()== IDOK)
	{
		pDoc->m_OnChange=TRUE;
	}
}

void CProyectoView::OnUpdateConfigurarReceptor(CCmdUI* pCmdUI) 
{
	CProyectoDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->m_OnDim);
}

void CProyectoView::OnConfigurarSuperficie() 
{
	CProyectoDoc* pDoc = GetDocument();
	T_CS_DLG Dlg;
	Dlg.lpCanal=pDoc->Canal;
	if (Dlg.DoModal()== IDOK)
	{
		pDoc->m_OnChange=TRUE;
	}
}

void CProyectoView::OnUpdateConfigurarSuperficie(CCmdUI* pCmdUI) 
{
	CProyectoDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->m_OnDim);
}

void CProyectoView::OnConfigurarTransmisor() 
{
	CProyectoDoc* pDoc = GetDocument();
	T_CT_DLG Dlg;
	Dlg.lpCanal=pDoc->Canal;
	if (Dlg.DoModal()== IDOK)
	{
		pDoc->m_OnChange=TRUE;
	}
}

void CProyectoView::OnUpdateConfigurarTransmisor(CCmdUI* pCmdUI) 
{
	CProyectoDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->m_OnDim);
}

void CProyectoView::OnCerrar() 
{
	CProyectoDoc* pDoc = GetDocument();
	if (!CheckChanges())
		return;
	delete pDoc->Canal;
	pDoc->Canal=NULL;
	pDoc->m_OnDim=FALSE;
	pDoc->m_OnChange=FALSE;
}

void CProyectoView::OnUpdateCerrar(CCmdUI* pCmdUI) 
{
	CProyectoDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->Canal != NULL);
}

void CProyectoView::OnGuardar() 
{
	Save();
}

void CProyectoView::OnUpdateGuardar(CCmdUI* pCmdUI) 
{
	CProyectoDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->Canal != NULL);	
}

void CProyectoView::OnNuevo() 
{
	CProyectoDoc* pDoc = GetDocument();
	if (!CheckChanges())
		return;
	delete pDoc->Canal;
	pDoc->Canal = new TCanal();
}

void CProyectoView::OnUpdateNuevo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	
}

void CProyectoView::OnSimulacion() 
{
	CProyectoDoc* pDoc = GetDocument();
	T_S_DLG Dlg;
	Dlg.lpCanal=pDoc->Canal;
	Dlg.DoModal();
}

void CProyectoView::OnUpdateSimulacion(CCmdUI* pCmdUI) 
{
	CProyectoDoc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->m_OnDim);		
}

void CProyectoView::OnAbrir() 
{
	CProyectoDoc* pDoc = GetDocument();
	if (!CheckChanges())
		return;

	if (!pDoc->Canal)
		pDoc->Canal= new TCanal();
	static char Filter[] = "Ficheros de Datos (*.dat)|*.dat||";
 	CFileDialog Dlg(TRUE,"DAT",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,Filter,NULL);
	if (Dlg.DoModal()==IDOK)
	{
		CString filename = Dlg.GetPathName();
		FILE* file = fopen(filename,"rb");
		if (!file)
		{
			MessageBox("Error abriendo fichero");
			return ;
		}
		DWORD size= fread(pDoc->Canal,sizeof(TCanal),1,file);
		if (size ==0)
		{
			MessageBox("Fichero Invalido");
		}
		else
		{
			pDoc->m_OnDim=TRUE;
		}
		fclose(file);		
	};
}

void CProyectoView::OnUpdateAbrir(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	
}

void CProyectoView::OnUpdateConfigurarDimensiones(CCmdUI* pCmdUI) 
{
	CProyectoDoc* pDoc = GetDocument();
	if (pDoc->Canal != NULL)
		pCmdUI->Enable(!pDoc->m_OnDim);
	else
		pCmdUI->Enable(FALSE);

}

/*
	devuelve true si se puede seguir con la operacion
*/
BOOL CProyectoView::CheckChanges()
{
	CProyectoDoc* pDoc = GetDocument();
	if (pDoc->m_OnChange)
	{
		T_MSG_DLG Dlg;
		int Result=Dlg.DoModal();
		if (Result == 1)
			return false;
		if (Result == 0)
			Save();
	}
	return true;
}

void CProyectoView::Save()
{
	CProyectoDoc* pDoc = GetDocument();
	if (!pDoc->m_OnChange)
	{
		return;
	}
	static char Filter[] = "Ficheros de Datos (*.dat)|*.dat||";
 	CFileDialog Dlg(FALSE,"dat",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,Filter,NULL);
	if (Dlg.DoModal()==IDOK)
	{
		FILE* file = fopen(Dlg.GetPathName(),"wb");
		if (!file)
		{
			MessageBox("Error creando fichero");
			return ;
		}
		DWORD size= fwrite(pDoc->Canal,sizeof(TCanal),1,file);
		if (size ==0)
		{
			MessageBox("Error escribiendo en el fichero");
		}
		else
			pDoc->m_OnChange=FALSE;
		fclose(file);		
	};		
}

void CProyectoView::OnAppExit() 
{
	if (CheckChanges())
		AfxGetMainWnd()->DestroyWindow();
}
