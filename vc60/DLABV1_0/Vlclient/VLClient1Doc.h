// VLClient1Doc.h : interface of the CVLClient1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VLCLIENT1DOC_H__B1D8C12C_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_)
#define AFX_VLCLIENT1DOC_H__B1D8C12C_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVLClient1SrvrItem;

class CVLClient1Doc : public COleServerDoc
{
protected: // create from serialization only
	CVLClient1Doc();
	DECLARE_DYNCREATE(CVLClient1Doc)

// Attributes
public:
	CVLClient1SrvrItem* GetEmbeddedItem()
		{ return (CVLClient1SrvrItem*)COleServerDoc::GetEmbeddedItem(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVLClient1Doc)
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVLClient1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual CDocObjectServer* GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite);

// Generated message map functions
protected:
	//{{AFX_MSG(CVLClient1Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VLCLIENT1DOC_H__B1D8C12C_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_)
