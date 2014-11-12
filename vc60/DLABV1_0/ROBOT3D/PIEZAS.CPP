// Piezas.cpp: implementation of the Pieza_01 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Piezas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int i;
int Paso=10;

CPieza_01::CPieza_01()
{

}

CPieza_01::~CPieza_01()
{

}

void CPieza_01::Paint()
{
	glNormal3d(-1.0, 0.0,  0.0);
	glBegin(GL_TRIANGLES);

	  glVertex3d(0.0, 11.0,-4.0);
	  glVertex3d(0.0,11+4*Seno(40),-4-4*Coseno(40));
	  glVertex3d(0.0, 7.0,-17.0);

  	  glVertex3d(10.0, 11.0,-4.0);
	  glVertex3d(10.0,11+4*Seno(40),-4-4*Coseno(40));
	  glVertex3d(10.0, 7.0,-17.0);

	  for (i=40;i<180;i=i+Paso)
	  {
		  glVertex3d(0.0,11.0,-4.0);
		  glVertex3d(0.0,11+4*Seno(i+Paso),-4-4*Coseno(i+Paso));
		  glVertex3d(0.0,11+4*Seno(i),-4-4*Coseno(i));

		  glVertex3d(10.0,11.0,-4.0);
		  glVertex3d(10.0,11+4*Seno(i+Paso),-4-4*Coseno(i+Paso));
		  glVertex3d(10.0,11+4*Seno(i),-4-4*Coseno(i));
	  }

	  glVertex3d(0.0,11.0,-4.0);
	  glVertex3d(0.0, 7.0,-17.0);
	  glVertex3d(0.0, 7.0,-4.0);

	  glVertex3d(0.0, 7.0,-17.0);
	  glVertex3d(0.0,0.0,-17.0);
	  glVertex3d(0.0, 7.0,-4.0);

	  glVertex3d(0.0,0.0,-17.0);
	  glVertex3d(0.0, 0.0,-4.0);
	  glVertex3d(0.0, 7.0,-4.0);

	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(0.0,11.0,0.0);
	  glVertex3d(0.0,11.0,-4.0);

	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(0.0,11.0,-4.0);
	  glVertex3d(0.0,0.0,-4.0);

  	  glVertex3d(10.0,11.0,-4.0);
	  glVertex3d(10.0, 7.0,-17.0);
	  glVertex3d(10.0, 7.0,-4.0);

	  glVertex3d(10.0, 7.0,-17.0);
	  glVertex3d(10.0,0.0,-17.0);
	  glVertex3d(10.0, 7.0,-4.0);

	  glVertex3d(10.0,0.0,-17.0);
	  glVertex3d(10.0, 0.0,-4.0);
	  glVertex3d(10.0, 7.0,-4.0);

	  glVertex3d(10.0,0.0,0.0);
	  glVertex3d(10.0,11.0,0.0);
	  glVertex3d(10.0,11.0,-4.0);

	  glVertex3d(10.0,0.0,0.0);
	  glVertex3d(10.0,11.0,-4.0);
	  glVertex3d(10.0,0.0,-4.0);


	glEnd();
}

CPieza_02::CPieza_02()
{

}

CPieza_02::~CPieza_02()
{

}

void CPieza_02::Paint()
{
	glNormal3d(-1.0, 0.0,  0.0);
	glBegin(GL_TRIANGLES);
	  for (i=-90;i<90;i=i+Paso)
	  {
		  glVertex3d(0.0,0.0,0.0);
		  glVertex3d(0.0,4*Seno(i+Paso),-4*Coseno(i+Paso));
		  glVertex3d(0.0,4*Seno(i),-4*Coseno(i));

  		  glVertex3d(7.0,0.0,0.0);
		  glVertex3d(7.0,4*Seno(i+Paso),-4*Coseno(i+Paso));
		  glVertex3d(7.0,4*Seno(i),-4*Coseno(i));

	  }

	  for (i=90;i<271;i=i+Paso)
	  {
		  glVertex3d(0.0,0.0,19.0);
		  glVertex3d(0.0,3*Seno(i+Paso),19-3*Coseno(i+Paso));
		  glVertex3d(0.0,3*Seno(i),19-3*Coseno(i));

		  glVertex3d(7.0,0.0,19.0);
		  glVertex3d(7.0,3*Seno(i+Paso),19-3*Coseno(i+Paso));
		  glVertex3d(7.0,3*Seno(i),19-3*Coseno(i));
		 
		 
	  }


	  glVertex3d(0.0,4.0,0.0);
	  glVertex3d(0.0,-4.0,0.0);
	  glVertex3d(0.0,-3.0,19.0);

	  glVertex3d(0.0,3.0,19.0);
	  glVertex3d(0.0,4.0,0.0);
	  glVertex3d(0.0,-3.0,19.0);

	  glVertex3d(7.0,4.0,0.0);
	  glVertex3d(7.0,-4.0,0.0);
	  glVertex3d(7.0,-3.0,19.0);

	  glVertex3d(7.0,3.0,19.0);
	  glVertex3d(7.0,4.0,0.0);
	  glVertex3d(7.0,-3.0,19.0);


	glEnd();


}

CPieza_03::CPieza_03()
{

}

CPieza_03::~CPieza_03()
{

}

void CPieza_03::Paint()
{
	glNormal3d(  -1.0, 0.0,  0.0);
	glBegin(GL_TRIANGLES);
	  for (i=-90;i<90;i=i+Paso)
	  {
		  glVertex3d(0.0,0.0,0.0);
		  glVertex3d(0.0,3*Seno(i+Paso),-3*Coseno(i+Paso));
		  glVertex3d(0.0,3*Seno(i),-3*Coseno(i));

  		  glVertex3d(5.9,0.0,0.0);
		  glVertex3d(5.9,3*Seno(i+Paso),-3*Coseno(i+Paso));
		  glVertex3d(5.9,3*Seno(i),-3*Coseno(i));

	  }

	  for (i=90;i<271;i=i+Paso)
	  {
		  glVertex3d(0.0,0.0,19.0);
		  glVertex3d(0.0,2*Seno(i+Paso),19-2*Coseno(i+Paso));
		  glVertex3d(0.0,2*Seno(i),19-2*Coseno(i));

		  glVertex3d(5.9,0.0,19.0);
		  glVertex3d(5.9,2*Seno(i+Paso),19-2*Coseno(i+Paso));
		  glVertex3d(5.9,2*Seno(i),19-2*Coseno(i));
	  }


	  glVertex3d(0.0,3.0,0.0);
	  glVertex3d(0.0,-3.0,0.0);
	  glVertex3d(0.0,-2.0,19.0);

	  glVertex3d(0.0,3.0,0.0);
	  glVertex3d(0.0,-2.0,19.0);
	  glVertex3d(0.0,2.0,19.0);

	  glVertex3d(5.9,3.0,0.0);
	  glVertex3d(5.9,-3.0,0.0);
	  glVertex3d(5.9,-2.0,19.0);

	  glVertex3d(5.9,3.0,0.0);
	  glVertex3d(5.9,-2.0,19.0);
	  glVertex3d(5.9,2.0,19.0);

	glEnd();
}

CPieza_04::CPieza_04()
{
	Direccion=1;
}

CPieza_04::~CPieza_04()
{

}

void CPieza_04::Paint()
{
	GLfloat YellowSurface[]={1.0f,1.0f,0.0,1.0f};
	GLfloat GraySurface[]={0.5f,0.5f,0.5f,1.0f};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT|GL_SPECULAR,YellowSurface);

	glPushMatrix();
	CAnilloXZ Anillo;
	Anillo.Set(2.25,2.55,0.2*Direccion);
	Anillo.Paint();
	glTranslated(0.0,0.2*Direccion,0.0);
	CEngraneXZ Rueda01(2.25,2.3,0.8*Direccion,36);
	Rueda01.Enabled(1);
	Rueda01.Paint();
	glTranslated(0.0,0.5*Direccion,0.0);
	Anillo.Set(1.95,2.25,0.3*Direccion);
	Anillo.Enable(2+4);
	Anillo.Paint();
	Anillo.Set(0.85,1.95,-Direccion);
	Anillo.Enable(1);
	Anillo.Paint();
	Anillo.Set(0.55,0.85,0.3*Direccion);
	Anillo.Enable(2+8);
	Anillo.Paint();
	Rueda01.Set(0.5,0.55,1.0*Direccion,18);
	Rueda01.Enabled(2);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT|GL_SPECULAR,GraySurface);
	Rueda01.Paint();
	
	glPopMatrix();

}

CMotorXZ::CMotorXZ()
{
	Direccion=1;

}

CMotorXZ::~CMotorXZ()
{

}

GLfloat Negro[]={0.0f,0.0f,0.0,1.0f};

void CMotorXZ::Paint()
{
	
	/*
	Set(3.25,2.5*Direccion);
	Enabled(2);
	CCilindroXZ::Paint();
	glTranslated(0.0,2.5*Direccion,0.0);
	Set(0.5,0.2*Direccion);
	Enabled(2);
	glMaterialfv(GL_FRONT,GL_AMBIENTESPECULAR,Negro);
	CCilindroXZ::Paint();
	glTranslated(0.0,-2.5*Direccion,0.0);
	*/

}


void CMotorXZ::SetDir(BOOL param)
{
	if (param) Direccion=1;
	else Direccion=-1;

}

CMotorXY::CMotorXY()
{

}

CMotorXY::~CMotorXY()
{

}

void CMotorXY::Paint()
{
	glPushMatrix();
	glRotated(90.0,1.0,0.0,0.0);
	CMotorXZ::Paint();
	glPopMatrix();
}


CMotorZY::CMotorZY()
{

}

CMotorZY::~CMotorZY()
{

}

void CMotorZY::Paint()
{
	glPushMatrix();
	glRotated(-90.0,0.0,0.0,1.0);
	CMotorXZ::Paint();
	glPopMatrix();
}

CCabezaXZ::CCabezaXZ()
{
	Direccion=TRUE;
}

CCabezaXZ::~CCabezaXZ()
{

}

void CCabezaXZ::Paint()
{
	int ang;
	double dx,dz,dx1,dz1;
	double  radio=0.3;
	double altura=0.4;
	
	glBegin(GL_TRIANGLES);
	for (ang=0;ang<360;ang=ang+60)
	{
		dx=radio*Seno(ang);
	    dz=radio*Coseno(ang);
		dx1=radio*Seno(ang+60);
		dz1=radio*Coseno(ang+60);

		glNormal3d((dx1+dx)/2/radio,0.0,(dz1+dz)/2/radio);
		glVertex3d(dx,altura*Direccion,dz);
		glVertex3d(dx1,altura*Direccion,dz1);
		glVertex3d(dx1,0.0,dz1);

		glVertex3d(dx,altura*Direccion,dz);
		glVertex3d(dx,0.0,dz);
		glVertex3d(dx1,0.0,dz1);

		if (Direccion == 1)
			glNormal3d(0.0,1.0,0.0);
		else
			glNormal3d(0.0,-1.0,0.0);

		glVertex3d(0.0,altura*Direccion,0.0);
		glVertex3d(dx,altura*Direccion,dz);
		glVertex3d(dx1,altura*Direccion,dz1);
	}
	glEnd();

}

void CCabezaXZ::SetDir(BOOL param)
{
	if (param) Direccion=1;
	else Direccion=-1;
}

CCabezaYZ::CCabezaYZ()
{

}

CCabezaYZ::~CCabezaYZ()
{

}

void CCabezaYZ::Paint()
{
	glPushMatrix();
	glRotated(-90.0,0.0,0.0,1.0);
	CCabezaXZ::Paint();
	glPopMatrix();

}

CPieza_04_YZ::CPieza_04_YZ()
{

}

CPieza_04_YZ::~CPieza_04_YZ()
{

}

void CPieza_04_YZ::Paint()
{
	glPushMatrix();
	glRotated(-90.0,0.0,0.0,1.0);
	CPieza_04::Paint();
	glPopMatrix();

}


CPieza_05::CPieza_05()
{
	
}

CPieza_05::~CPieza_05()
{

}



void CPieza_05::Paint()
{
	glBegin(GL_TRIANGLES);

	// tapas laterales
	  glNormal3i(-1,0,0);
	  glVertex3d(0.0,0.0,-2.0);
	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(0.0,2.0,0.0);

	  glVertex3d(0.0,2.0,-2.0);
	  glVertex3d(0.0,0.0,-2.0);
	  glVertex3d(0.0,2.0,0.0);

	  glNormal3i(1,0,0);
	  glVertex3d(2.0,0.0,0.0);
	  glVertex3d(2.0,0.0,-2.0);
	  glVertex3d(2.0,2.0,0.0);

	  glVertex3d(2.0,0.0,-2.0);
	  glVertex3d(2.0,2.0,-2.0);
	  glVertex3d(2.0,2.0,0.0);

	// tapas frontal y trasera
	  glNormal3i(0,0,1);
	  // tapa 1
	  glVertex3d(0.0,0.4,0.0);
	  glVertex3d(0.4,0.4,0.0);
	  glVertex3d(0.0,2.0,0.0);


	  glVertex3d(0.4,0.4,0.0);
	  glVertex3d(0.4,2.0,0.0);
	  glVertex3d(0.0,2.0,0.0);

	  // tapa II
	  glVertex3d(1.6,0.4,0.0);
	  glVertex3d(2.0,0.4,0.0);
	  glVertex3d(1.6,2.0,0.0);


	  glVertex3d(2.0,0.4,0.0);
	  glVertex3d(2.0,2.0,0.0);
	  glVertex3d(1.6,2.0,0.0);

	  // Tapa III
	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(2.0,0.0,0.0);
	  glVertex3d(2.0,0.4,0.0);


	  glVertex3d(0.0,0.4,0.0);
	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(2.0,0.4,0.0);

  	  glNormal3i(0,0,-1);
	  // tapa 1

	  glVertex3d(0.4,0.4,-2.0);
	  glVertex3d(0.0,0.4,-2.0);
	  glVertex3d(0.0,2.0,-2.0);

	  glVertex3d(0.4,2.0,-2.0);
	  glVertex3d(0.4,0.4,-2.0);
	  glVertex3d(0.0,2.0,-2.0);

	  // tapa II

	  glVertex3d(2.0,0.4,-2.0);
	  glVertex3d(1.6,0.4,-2.0);
	  glVertex3d(1.6,2.0,-2.0);

	  glVertex3d(2.0,2.0,-2.0);
	  glVertex3d(2.0,0.4,-2.0);
	  glVertex3d(1.6,2.0,-2.0);

	  // Tapa III
	  glVertex3d(2.0,0.0,-2.0);
	  glVertex3d(0.0,0.0,-2.0);
	  glVertex3d(2.0,0.4,-2.0);

	  glVertex3d(0.0,0.0,-2.0);
	  glVertex3d(0.0,0.4,-2.0);
	  glVertex3d(2.0,0.4,-2.0);

	  //Tapa de abajo
	  glNormal3i(0,-1,0);
	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(0.0,0.0,-2.0);
	  glVertex3d(2.0,0.0,-2.0);
	  
	  glVertex3d(2.0,0.0,0.0);
	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(2.0,0.0,-2.0);

	  //Tapa de arriba
	  glNormal3i(0,1,0);
	  glVertex3d(0.4,0.4,-2.0);
	  glVertex3d(0.4,0.4,0.0);
	  glVertex3d(1.6,0.4,-2.0);

	  glVertex3d(0.4,0.4,0.0);
	  glVertex3d(1.6,0.4,0.0);
	  glVertex3d(1.6,0.4,-2.0);

	  // Tapitas de arriba
	  glNormal3i(0,1,0);
	  glVertex3d(0.0,2.0,0.0);
	  glVertex3d(0.4,2.0,0.0);
	  glVertex3d(0.4,2.0,-2.0);

	  glVertex3d(0.0,2.0,-2.0);
	  glVertex3d(0.0,2.0,0.0);
	  glVertex3d(0.4,2.0,-2.0);

	  glVertex3d(1.6,2.0,0.0);
	  glVertex3d(2.0,2.0,0.0);
	  glVertex3d(2.0,2.0,-2.0);

	  glVertex3d(1.6,2.0,-2.0);
	  glVertex3d(1.6,2.0,0.0);
	  glVertex3d(2.0,2.0,-2.0);

	  //Tapas de adentro
	  glNormal3i(1,0,0);
	  glVertex3d(0.4,0.4,0.0);
	  glVertex3d(0.4,0.4,-2.0);
	  glVertex3d(0.4,2.0,0.0);

	  glVertex3d(0.4,0.4,-2.0);
	  glVertex3d(0.4,2.0,-2.0);
	  glVertex3d(0.4,2.0,0.0);

	  glNormal3i(-1,0,0);
	  glVertex3d(1.6,0.4,-2.0);
	  glVertex3d(1.6,0.4,0.0);
	  glVertex3d(1.6,2.0,0.0);

	  glVertex3d(1.6,2.0,-2.0);
	  glVertex3d(1.6,0.4,-2.0);
	  glVertex3d(1.6,2.0,0.0);

	glEnd();

	CPoleaZY Polea;
	Polea.Set(0.55,0.5,0.2,0.8);
	glPushMatrix();
	glTranslated(0.4,1.1,-0.4);
	Polea.Paint();
	glTranslated(0.0,0.0,-1.2);
	Polea.Paint();
	glPopMatrix();
	glTranslated(1.0,0.0,-1.0);
	glTranslated(0.0,-0.7,0.0);
	CCilindroXZ Cilindro;
	Cilindro.Set(1.55,-0.5);
	Cilindro.Enabled(0);
	Cilindro.Paint();
	glTranslated(0.0,-0.5,0.0);
	Cilindro.Set(1.85,-0.3);
	Cilindro.Enabled(2+1);
	Cilindro.Paint();
	glTranslated(0.0,-0.3,0.0);

	glPushMatrix();
	glDisable(GL_CULL_FACE);

	glTranslated(0.85,0.0,0.0);

	CPieza_05_01::Paint();

	glPopMatrix();
	glPushMatrix();

	glRotated(120.0,0.0,1.0,0.0);
	glTranslated(0.85,0.0,0.0);

	CPieza_05_01::Paint();

	glPopMatrix();
	
	glRotated(240.0,0.0,1.0,0.0);
	glTranslated(0.85,0.0,0.0);
	CPieza_05_01::Paint();
	
}

CPieza_05_01::CPieza_05_01()
{
	ang=0;
	
}

CPieza_05_01::~CPieza_05_01()
{

}

void CPieza_05_01::Paint()
{
	glPushMatrix();
	glTranslated(0.0,0.0,0.55);

	glBegin(GL_TRIANGLES);
	  glNormal3i(0,0,1);

	  glVertex3d(2.8,0.0,0.0);
	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(-0.4,-1.5,0.0);

	  glVertex3d(2.8,-1.0,0.0);
	  glVertex3d(2.8,0.0,0.0);
	  glVertex3d(-0.4,-1.5,0.0);

	  glVertex3d(2.8,0.0,-1.1);
	  glVertex3d(0.0,0.0,-1.1);
	  glVertex3d(-0.4,-1.5,-1.1);

	  glVertex3d(2.8,-1.0,-1.1);
	  glVertex3d(2.8,0.0,-1.1);
	  glVertex3d(-0.4,-1.5,-1.1);

	glEnd();

	glTranslated(0.0,0.0,-0.1);
	glTranslated(2.0,-0.8,0.0);

	// los angulos van de -80 a -100
	glRotated(-80.0-ang,0.0,0.0,1.0);
	glTranslated(0.0,0.9,0.0);

	glBegin(GL_TRIANGLES);

	  glNormal3i(0,0,-1);

	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(4.0,0.0,0.0);
	  glVertex3d(0.0,-1.8,0.0);


	  glVertex3d(4.0,0.0,0.0);
	  glVertex3d(3.3,-1.8,0.0);
	  glVertex3d(0.0,-1.8,0.0);

  	  glVertex3d(0.0,0.0,-0.9);
	  glVertex3d(4.0,0.0,-0.9);
	  glVertex3d(0.0,-1.8,-0.9);


	  glVertex3d(4.0,0.0,-0.9);
	  glVertex3d(3.3,-1.8,-0.9);
	  glVertex3d(0.0,-1.8,-0.9);


	glEnd();
	
	glTranslated(3.5,-0.5,-0.15);
	// rotacion
	// los angulos van de cero a -10;
	glRotated(0.0-ang,0.0,0.0,1.0);
	glTranslated(0.0,0.5,0.0);

	glBegin(GL_TRIANGLES);
	  glNormal3i(0,0,-1);
	  glVertex3d(0.0,0.0,0.0);
	  glVertex3d(3.1,0.0,0.0);
	  glVertex3d(0.0,-1.5,0.0);

	  glVertex3d(0.0,0.0,-0.6);
	  glVertex3d(3.1,0.0,-0.6);
	  glVertex3d(0.0,-1.5,-0.6);


	glEnd();

	glPopMatrix();
}
