// HtmlCoder.h: interface for the CHtmlCoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLCODER_H__02B18C5C_DC59_42D2_B0D1_22601401FA88__INCLUDED_)
#define AFX_HTMLCODER_H__02B18C5C_DC59_42D2_B0D1_22601401FA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ITube.h"
#include "bObject.h"

/*
	Codificador decodificar de HTML
	los caracteres que necesitan ser escapados en html porque son usados por el lenguaje
	como < > & " ' 
	se utilizan todas la entidades html definidas desde un origen unicode
*/

class CHtmlCoder : 
	public CbObject, 
	public ITube  
{
public:
	CHtmlCoder();
	virtual ~CHtmlCoder();

};

#endif // !defined(AFX_HTMLCODER_H__02B18C5C_DC59_42D2_B0D1_22601401FA88__INCLUDED_)
