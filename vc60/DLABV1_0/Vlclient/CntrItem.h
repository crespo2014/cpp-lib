// CntrItem.h : interface of the CVLClient1CntrItem class
//

#if !defined(AFX_CNTRITEM_H__B1D8C135_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_)
#define AFX_CNTRITEM_H__B1D8C135_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVLClient1Doc;
class CVLClient1View;

class CVLClient1CntrItem : public COleClientItem
{
	DECLARE_SERIAL(CVLClient1CntrItem)

// Constructors
public:
	CVLClient1CntrItem(CVLClient1Doc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CVLClient1Doc* GetDocument()
		{ return (CVLClient1Doc*)COleClientItem::GetDocument(); }
	CVLClient1View* GetActiveView()
		{ return (CVLClient1View*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVLClient1CntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	virtual BOOL CanActivate();
	//}}AFX_VIRTUAL

// Implementation
public:
	~CVLClient1CntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__B1D8C135_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_)
