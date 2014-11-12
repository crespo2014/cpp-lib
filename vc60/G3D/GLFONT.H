// GLFont.h: interface for the CGLFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLFONT_H__2D41C043_A737_11D3_B87A_0000B490D4F4__INCLUDED_)
#define AFX_GLFONT_H__2D41C043_A737_11D3_B87A_0000B490D4F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define FONTLIST    256

enum GLFontType
{
	GL_FONT_SOLID,
    GL_FONT_LINE,
};


class CGLFont  
{
public:
	int CreateFont(CDC* pDrawDC, char* fontname);
	GLuint       m_ListBase;
	GLFontType   m_FontType;
	double       m_dThick; 
	int PrintString(LPCSTR pString);
	CGLFont();
	virtual ~CGLFont();

};

#endif // !defined(AFX_GLFONT_H__2D41C043_A737_11D3_B87A_0000B490D4F4__INCLUDED_)
