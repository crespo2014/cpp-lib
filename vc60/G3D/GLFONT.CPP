// GLFont.cpp: implementation of the CGLFont class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GLFont.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




CGLFont::CGLFont()
{
	m_dThick = 0.2;
	m_ListBase=0;
	m_FontType=GL_FONT_SOLID;
}

CGLFont::~CGLFont()
{

}

int CGLFont::PrintString(LPCSTR pString)
{
	if (m_ListBase == 0  || pString== NULL)
	{
		return false;
	}
	glPushAttrib (GL_LIST_BASE);
    glListBase(m_ListBase);
    glCallLists(strlen(pString), GL_UNSIGNED_BYTE, (GLubyte *) pString);
    glPopAttrib ();
	return true;
}

int CGLFont::CreateFont(CDC *pDrawDC, char *fontname)
{
	m_ListBase = glGenLists(FONTLIST);

	if(pDrawDC == NULL || m_ListBase == 0)
	{
        return FALSE;
	}

	//Create the font to display
	CFont newfont;
	CFont* oldfont;
	BOOL  bresult;
	GLYPHMETRICSFLOAT gmf[FONTLIST];

	if(fontname != NULL)
	{	
        bresult = newfont.CreateFont(-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 
		       OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
               FF_DONTCARE|DEFAULT_PITCH, fontname);

	    //if new font failed to be created
	    if(!bresult)
		{
		    return FALSE;
		}

	    oldfont = pDrawDC->SelectObject(&newfont);
	}
	else
	{
	    oldfont = (CFont*)pDrawDC->SelectStockObject(SYSTEM_FONT);
	}

	if(m_FontType == GL_FONT_SOLID)
	{
        bresult = wglUseFontOutlines(pDrawDC->m_hDC, 0, FONTLIST, m_ListBase, 
			0.0f, (float)m_dThick, WGL_FONT_POLYGONS, gmf);	
	}
	else if(m_FontType == GL_FONT_LINE)
	{
        bresult = wglUseFontOutlines(pDrawDC->m_hDC, 0, FONTLIST, m_ListBase, 
			0.0f, (float)m_dThick, WGL_FONT_LINES, gmf);	
	}
	
	pDrawDC->SelectObject(oldfont);
	newfont.DeleteObject();
	
	if(!bresult)
	{
		return FALSE;
	}
	return true;
}
