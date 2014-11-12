// SrvrItem.h : interface of the CVLClient1SrvrItem class
//

#if !defined(AFX_SRVRITEM_H__B1D8C131_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_)
#define AFX_SRVRITEM_H__B1D8C131_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVLClient1SrvrItem : public CDocObjectServerItem
{
	DECLARE_DYNAMIC(CVLClient1SrvrItem)

// Constructors
public:
	CVLClient1SrvrItem(CVLClient1Doc* pContainerDoc);

// Attributes
	CVLClient1Doc* GetDocument() const
		{ return (CVLClient1Doc*)CDocObjectServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVLClient1SrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CVLClient1SrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRVRITEM_H__B1D8C131_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_)
