// g_01c09.cpp: implementation of the C3DMaterial class.
//
//////////////////////////////////////////////////////////////////////

#include "gc09.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DMaterial::C3DMaterial()
{
	m_lpdata=&m_data;
}

C3DMaterial::~C3DMaterial()
{

}

DWORD C3DMaterial::ReadFromMemory(void *lppointer)
{
	m_lpdata = (S_3DMATERIAL*)lppointer;
	if (m_lpdata->m_size != sizeof(m_data))
		return 1;
	return 0;
}

DWORD C3DMaterial::MakeCurrent()
{
	float color[4];
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,m_lpdata->m_shininess);
	color[3]=1.0;
	memcpy(color,&m_lpdata->m_ambient,sizeof(m_lpdata->m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,color);
	memcpy(color,&m_lpdata->m_diffuse,sizeof(m_lpdata->m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,color);
	glColor3fv(color);
	memcpy(color,&m_lpdata->m_specular,sizeof(m_lpdata->m_specular));
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
	memset(color,0,sizeof(color));
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,color);
	if (m_lpdata->m_twosides)
	{
		glDisable(GL_CULL_FACE);
	}
	else
	{
		glEnable(GL_CULL_FACE);
	}
	return 0;
}
