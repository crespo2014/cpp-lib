// G_01C02.h: interface for the C3DObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G_01C02_H__56304441_C74D_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_G_01C02_H__56304441_C74D_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class C3DMesh;

class C3DObject   
{
public:
	DWORD Set3DMesh(C3DMesh* lp3dmesh);
	DWORD SetPrev(C3DObject* pprev);
	DWORD SetNext(C3DObject* pnext);
	C3DObject* GetNext();
	virtual DWORD Paint();
	virtual DWORD Fly(DWORD pTime);
	DWORD initialize();
	C3DObject();
	virtual ~C3DObject();
	double	m_startx,m_starty,m_startz;
	double	m_currentx,m_currenty,m_currentz;
	double	m_lastz,m_lastx,m_lasty;
	double	m_speed;
	DWORD	m_starttime;	//Tiempo en el que se creo (ms)
	C3DObject	*m_next,*m_prev;
	BOOL		m_active;	//Usado para evitar la creacion dinamica
	BOOL		m_delete;
	C3DMesh*	m_lp3dmesh;
	
};

#endif // !defined(AFX_G_01C02_H__56304441_C74D_11D4_9126_0000E83D722B__INCLUDED_)
