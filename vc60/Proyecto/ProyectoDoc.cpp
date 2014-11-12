// ProyectoDoc.cpp : implementation of the CProyectoDoc class
//

#include "stdafx.h"
#include "Proyecto.h"

#include "ProyectoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProyectoDoc

IMPLEMENT_DYNCREATE(CProyectoDoc, CDocument)

BEGIN_MESSAGE_MAP(CProyectoDoc, CDocument)
	//{{AFX_MSG_MAP(CProyectoDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProyectoDoc construction/destruction

CProyectoDoc::CProyectoDoc()
{
	 m_OnDim=false;
	 m_OnChange=false;
	 Canal=NULL;
}

CProyectoDoc::~CProyectoDoc()
{
	delete Canal;
}

BOOL CProyectoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CProyectoDoc serialization

void CProyectoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CProyectoDoc diagnostics

#ifdef _DEBUG
void CProyectoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProyectoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProyectoDoc commands

