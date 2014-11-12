// Pos.cpp: implementation of the CPos class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Pos.h"
#include "Formas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPos::CPos()
{

}

CPos::~CPos()
{

}

LPCSTR CPos::GetMov()
{
	return " ";

}

void CPos::SetPos(double *points)
{
	memcpy(m_Position,points,sizeof(double)*3);
}

void CPos::GetPos(double *points)
{
	memcpy(points,m_Position,sizeof(double)*3);
}

void CPos::Paint()
{

}
