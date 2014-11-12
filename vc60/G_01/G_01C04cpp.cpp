// G_01C04cpp.cpp: implementation of the C3DNave class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "G_01C04.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DNave::C3DNave()
{
	m_dist=0;
}

C3DNave::~C3DNave()
{

}

DWORD C3DNave::Fly(DWORD pTime)
{
	glTranslated(2,0,-m_dist);
	m_dist++;
	if (m_dist > 20) 
		m_dist=0;
	return 0;
}
