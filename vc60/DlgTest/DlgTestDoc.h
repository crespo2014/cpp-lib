// DlgTestDoc.h : interface of the CDlgTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGTESTDOC_H__D22C05FE_093E_4A6A_9C00_1E31E6EF424F__INCLUDED_)
#define AFX_DLGTESTDOC_H__D22C05FE_093E_4A6A_9C00_1E31E6EF424F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDlgTestDoc : public CDocument
{
protected: // create from serialization only
	CDlgTestDoc();
	DECLARE_DYNCREATE(CDlgTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDlgTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDlgTestDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTESTDOC_H__D22C05FE_093E_4A6A_9C00_1E31E6EF424F__INCLUDED_)
