// DlgTestView.cpp : implementation of the CDlgTestView class
//

#include "stdafx.h"
#include "DlgTest.h"

#include "DlgTestDoc.h"
#include "DlgTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTestView

IMPLEMENT_DYNCREATE(CDlgTestView, CView)

BEGIN_MESSAGE_MAP(CDlgTestView, CView)
	//{{AFX_MSG_MAP(CDlgTestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTestView construction/destruction

CDlgTestView::CDlgTestView()
{
	// TODO: add construction code here

}

CDlgTestView::~CDlgTestView()
{
}

BOOL CDlgTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgTestView drawing

void CDlgTestView::OnDraw(CDC* pDC)
{
	CDlgTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDlgTestView printing

BOOL CDlgTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDlgTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDlgTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDlgTestView diagnostics

#ifdef _DEBUG
void CDlgTestView::AssertValid() const
{
	CView::AssertValid();
}

void CDlgTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDlgTestDoc* CDlgTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDlgTestDoc)));
	return (CDlgTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgTestView message handlers
