// Pos.h: interface for the CPos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POS_H__B17EB9E1_6514_11D3_A767_0000E856599A__INCLUDED_)
#define AFX_POS_H__B17EB9E1_6514_11D3_A767_0000E856599A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CPos  
{
public:
	virtual void Paint();
	void GetPos(double* points);
	void SetPos(double* points);
	virtual LPCSTR GetMov();
	CPos();
	virtual ~CPos();

	double m_Position[3];
private:

};

#endif // !defined(AFX_POS_H__B17EB9E1_6514_11D3_A767_0000E856599A__INCLUDED_)
