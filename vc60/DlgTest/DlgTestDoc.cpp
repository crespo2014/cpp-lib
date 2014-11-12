// DlgTestDoc.cpp : implementation of the CDlgTestDoc class
//

#include "stdafx.h"
#include "DlgTest.h"

#include "DlgTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTestDoc

IMPLEMENT_DYNCREATE(CDlgTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CDlgTestDoc, CDocument)
	//{{AFX_MSG_MAP(CDlgTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTestDoc construction/destruction

CDlgTestDoc::CDlgTestDoc()
{
	// TODO: add one-time construction code here

}

CDlgTestDoc::~CDlgTestDoc()
{
}

BOOL CDlgTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDlgTestDoc serialization

void CDlgTestDoc::Serialize(CArchive& ar)
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
// CDlgTestDoc diagnostics

#ifdef _DEBUG
void CDlgTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDlgTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgTestDoc commands
