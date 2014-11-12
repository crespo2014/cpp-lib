// Trayectoria.h: interface for the CTrayectoria class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAYECTORIA_H__7B6E4681_5EC1_11D3_A264_0000E856599A__INCLUDED_)
#define AFX_TRAYECTORIA_H__7B6E4681_5EC1_11D3_A264_0000E856599A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTrayectoria  
{
public:
	void GetAng(int Pos[3]);
	int CalcAng();
	void SetPoint(double* points);
	CTrayectoria();
	virtual ~CTrayectoria();

private:
	double m_x,m_y,m_z;
	double m_Ang[3];    //angulo de las articulaciones en radianes
						// el angulo del codo es relativo al piso

};

#endif // !defined(AFX_TRAYECTORIA_H__7B6E4681_5EC1_11D3_A264_0000E856599A__INCLUDED_)
