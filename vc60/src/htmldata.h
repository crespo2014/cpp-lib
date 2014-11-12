// HtmlData.h: interface for the CHtmlData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLDATA_H__BFB063A2_5D0B_4D7E_8EF3_D106A177EA7F__INCLUDED_)
#define AFX_HTMLDATA_H__BFB063A2_5D0B_4D7E_8EF3_D106A177EA7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bobject.h"
#include "imem.h"
#include "Mshtml.h"


#define F_NL	1	// new line
#define F_PWD	2	// contenido oculto, tipo password
#define F_TEXT	4	// esto es un texto puero y duro
#define F_EDT	8	// esto es un caja de texto

#define TYPE_NONE		0
#define TYPE_INPUT		1	
#define TYPE_BUTTOM		3
#define TYPE_TEXT		4
#define TYPE_P			5
#define TYPE_LI			6	
#define TYPE_H1			7	
#define TYPE_H2			8	
#define TYPE_H3			9	


struct _htmlnode {
	struct _htmlnode*	next;
	struct _htmlAttr*	firstAttr;
	char*	text;
	char*	id;
	WORD type;
	DWORD	dwFlags;
};

struct _htmlAttr {
	struct _htmlAttr*	next;
	WCHAR*	name;
	WCHAR*	value;
};

class CHtmlData  : public CbObject
{
public:
	CHtmlData(IMem *pMem);
	virtual ~CHtmlData();
	DWORD	load(IHTMLDocument2 *pHtmlDoc);
	WCHAR*	getAttribute(struct _htmlnode* node,WCHAR* name);
	struct _htmlnode* nextNode(struct _htmlnode* node,WORD type);
private:
	IMem *mpIMem;
	struct _htmlnode  *_newNext();
	struct _htmlnode *mfirstNode,*mlastNode;
	void pushText(IHTMLDOMNode *node);
	void processNode(IHTMLDOMNode *node);
	struct _htmlAttr	* getAttributes(IHTMLDOMNode *node);
};

#endif // !defined(AFX_HTMLDATA_H__BFB063A2_5D0B_4D7E_8EF3_D106A177EA7F__INCLUDED_)
