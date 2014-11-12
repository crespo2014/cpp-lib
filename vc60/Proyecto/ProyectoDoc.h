// ProyectoDoc.h : interface of the CProyectoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROYECTODOC_H__AFC1C5C9_4B5F_4ACC_9997_8604B28F1FDF__INCLUDED_)
#define AFX_PROYECTODOC_H__AFC1C5C9_4B5F_4ACC_9997_8604B28F1FDF__INCLUDED_

#include "TCanal.h"	// Added by ClassView
#include "t_cd.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CProyectoDoc : public CDocument
{
protected: // create from serialization only
	CProyectoDoc();
	DECLARE_DYNCREATE(CProyectoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProyectoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	TCanal* Canal;
	BOOL m_OnDim;		// Indica que las dimensiones ya estan llenadas.
	BOOL m_OnChange;   //Indica que el canal ha cambiado
	virtual ~CProyectoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProyectoDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROYECTODOC_H__AFC1C5C9_4B5F_4ACC_9997_8604B28F1FDF__INCLUDED_)
