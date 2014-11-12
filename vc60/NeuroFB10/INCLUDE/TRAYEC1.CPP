// Trayectoria.cpp: implementation of the CTrayectoria class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Trayectoria.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Esta clase solo es util para el Robot ARM0R10 que hay 
// en nuestro laboratorio

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrayectoria::CTrayectoria()
{

}

CTrayectoria::~CTrayectoria()
{

}

// Usada para recoger las coordenadas x,y,z
// con las cuales se hara el calculo
void CTrayectoria::SetPoint(double *points)
{
	m_x=points[0];
	m_y=points[1];
	m_z=points[2];
}

// Calculo del angulo que deben moverse las articulaciones
int CTrayectoria::CalcAng()
{
	int l_Hombro=19;
	int l_Codo=19;
	// Transladar el eje al centro de giro de la base
	m_x+=8.5;
	m_y-=13;
	m_z+=4.48;
	// Girando la Base
	m_Ang[0]=atan2(m_x,m_z);
	// Recalcular coordenadas
	m_z=sqrt(m_x*m_x+m_z*m_z);
	m_x=0;
	m_z-=0.7625;
	if (m_z < 0) return -1; // El objeto esta inlocalizable
	// porque se quedo atras cuando debia estar alante de la base

	// Subir al centro de giro del codo y el hombro
	m_y-=11.0;

	// Calculo de los angulos del Hombro y el Codo

	double t1,t2;  // Relaciones temporales para el calculo de angulos
	double h1,a1;
	h1=sqrt(m_z*m_z+m_y*m_y);  // Hipotenusas intermedia
	if (h1> l_Hombro+l_Codo) return -2; // Fuera de alcance
	
	// Angulo entre codo y hombro entre 0 y 180
	t2=(l_Codo*l_Codo+l_Hombro*l_Hombro-h1*h1)/(2*l_Codo*l_Hombro);
	// Angulo entre la hipotenusa y el Hombro siempre >0
	t1=(h1*h1+l_Hombro*l_Hombro-l_Codo*l_Codo)/(2*h1*l_Hombro);
	// Angulo entre el eje y la hipotenusa
	a1=atan2(m_y,m_z);

	// Calculo final de los angulos respecto al eje Z
	m_Ang[1]=-(acos(t1)+a1);
	m_Ang[2]=(acos(t2)-acos(-1))-m_Ang[1];

	// Conversion a grados
	double m=180/acos(-1);
	int i;
	for (i=0;i<3;m_Ang[i]*=m,i++);
	return 0;
}

void CTrayectoria::GetAng(int Pos[])
{
	Pos[0]=(int)m_Ang[0]*196/180;
	Pos[1]=(int)m_Ang[1]*138/90;
	Pos[2]=(int)m_Ang[2]*145/90;
}
