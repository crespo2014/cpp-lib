// Robot1.cpp: implementation of the CRobot1 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Robot1.h"
#include "Piezas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

    GLfloat RedSurface[]={1.0f,0.0f,0.0f,1.0f};
	GLfloat GreenSurface[]={0.0f,1.0f,0.0f,1.0f};
	GLfloat BlueSurface[]={0.0f,0.0f,1.0f,1.0f};
	GLfloat WhiteSurface[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat GraySurface[]={0.5f,0.5f,0.5f,1.0f};
	GLfloat Gray2Surface[]={1.0f,0.2f,0.2f,1.0f};
	GLfloat YellowSurface[]={1.0f,1.0f,0.0,1.0f};
	GLfloat BlackSurface[]={0.0f,0.0f,0.0,1.0f};
	GLfloat CarmelitaSurface[]={0.2f,0.2f,0.2f,1.0f};
	GLfloat OrangeSurface[]={1.0f,0.541176f,0.0823529f,1.0f};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Motor que se pinta con sentido positivo
// Base XZ

void Motor_01()
{
	glMaterialfv(GL_FRONT,GL_AMBIENT|GL_SPECULAR,GraySurface);
	CCilindroXZ Cilindro;
	Cilindro.Set(3.25,2.5);
	Cilindro.Enabled(2);
	Cilindro.Paint();
	glTranslated(0.0,2.5,0.0);
	Cilindro.Set(0.5,0.2);
	glMaterialfv(GL_FRONT,GL_AMBIENT|GL_SPECULAR,BlackSurface);
	Cilindro.Paint();
	glTranslated(0.0,-2.5,0.0);
}

// Engranaje dientado amarrillo en los motores 
// Direccion Positiva Base XZ

void Ruedita_01()
{
	glMaterialfv(GL_FRONT,GL_AMBIENT|GL_SPECULAR,YellowSurface);
	CEngraneXZ Diente;
	Diente.Set(0.4,0.45,1.0,18);
	Diente.Paint();
	glTranslated(0.0,1.0,0.0);
	CCilindroXZ Cilindro(0.6,0.2);
	glMaterialfv(GL_FRONT,GL_AMBIENT|GL_SPECULAR,GraySurface);
	Cilindro.Paint();
	// Recuperar eje de coordenadas
	glTranslated(0.0,-1.0,0.0);
}

// Tornillo que soporta los engranes
// Direccion Positiva de Y base XZ
void Tornillo_02()
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

		// pareja de triangulos 
		glNormal3d((dx1+dx)/2/radio,0.0,(dz1+dz)/2/radio);
		glVertex3d(dx1,altura,dz1);
		glVertex3d(dx,altura,dz);
		glVertex3d(dx1,0.0,dz1);

		glVertex3d(dx,altura,dz);
		glVertex3d(dx,0.0,dz);
		glVertex3d(dx1,0.0,dz1);

		glNormal3d(0.0,1.0,0.0);
		
		glVertex3d(0.0,altura,0.0);
		glVertex3d(dx,altura,dz);
		glVertex3d(dx1,altura,dz1);
	}
	glEnd();
}

// Engrane amarrillo que es muy complicado 
void Ruedita_02()
{
	glMaterialfv(GL_FRONT,GL_AMBIENT|GL_SPECULAR,YellowSurface);
	glPushMatrix();
	CAnilloXZ Anillo;
	Anillo.Set(2.25,2.55,0.2);
	Anillo.Paint();
	glTranslated(0.0,0.2,0.0);
	CEngraneXZ Rueda01(2.25,2.3,0.8,36);
	Rueda01.Enabled(1);
	Rueda01.Paint();
	glTranslated(0.0,0.5,0.0);
	Anillo.Set(1.95,2.25,0.3);
	Anillo.Enable(2+4);
	Anillo.Paint();
	Anillo.Set(0.85,1.95,0);
	Anillo.Enable(2);
	Anillo.Paint();
	Anillo.Set(0.55,0.85,0.3);
	Anillo.Enable(2+8);
	Anillo.Paint();
	Rueda01.Set(0.5,0.55,1.0,18);
	Rueda01.Enabled(2);
	glMaterialfv(GL_FRONT,GL_AMBIENT|GL_SPECULAR,GraySurface);
	Rueda01.Paint();
	
	glPopMatrix();
}


CRobot1::CRobot1()
{
//	test=(char*)malloc(2000);
//	m_CmdChar=new CString(test,2000);
	m_OnWaiting=false;
	m_OnExecute=false;
}

CRobot1::~CRobot1()
{

}

void CRobot1::PaintNow()
{
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT|GL_SPECULAR,WhiteSurface);
	//glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
	  glVertex3d(-50.0,0.0,-100);glTexCoord2d(0,0);
	  glVertex3d(50.0,0.0,-100);glTexCoord2d(1,0);
	  glVertex3d(50.0,0.0,50);glTexCoord2d(1,1);
	  glVertex3d(-50.0,0.0,50);glTexCoord2d(0,1);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT|GL_SPECULAR,BlueSurface);
	double point[3];
	DWORD i;
	if (m_OnExecute)
		for (i=m_ListPos;i<m_ListCant;i++)
		{
			((CPos*)m_List[i])->GetPos(point);
			glTranslated(point[0],point[1],point[2]);
			((CPos*)m_List[i])->Paint();
			glTranslated(-point[0],-point[1],-point[2]);
		}
	
	
     // Pintar el soporte del Robot y dejar el eje
	// Justo arriba y en el centro del cilindro
	glMaterialfv(GL_FRONT,GL_AMBIENT|GL_SPECULAR,RedSurface);
	glCallList(m_List_Base);

	// Rotacion de la Base
	glRotated(m_Robot_Data[0]*180/196,0.0,1.0,0.0);
	// Pintar la base
	glCallList(m_List_Base+1);

	//Hombros
	//Rotacion del Hombro
	glRotated(m_Robot_Data[1]*90/138,1.0,0.0,0.0);
	glCallList(m_List_Base+2);

	// Rotacion del Codo
	glRotated(-(m_Robot_Data[2]*90/145+m_Robot_Data[1]*90/138),1.0,0.0,0.0);
	glCallList(m_List_Base+6);

	//Rotacion del angulo de la pinza
	glRotated(m_Robot_Data[2]*90/145,1.0,0.0,0.0);
	glTranslated(1.95,-1.0,1.0);

	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,BlackSurface);
	glEnable(GL_CULL_FACE);
	CPieza_05 Pieza1;
	Pieza1.ang=(float)m_Robot_Data[3]/5;
	Pieza1.Paint();

	glFlush();
	glFinish();
}

int CRobot1::Init()
{
	m_Driver.Init();
	//m_Comm32.Init();
	
	// definiendo color de fondo
	COLORREF color = ::GetSysColor(COLOR_3DFACE);
	glClearColor((float)GetRValue(color)/255.0f,
				 (float)GetGValue(color)/255.0f,
				 (float)GetBValue(color)/255.0f,
				 1.0);

	// definiendo las propiedades de los materiales
	glMaterialfv(GL_FRONT,GL_DIFFUSE,WhiteSurface);
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,0);

	// Definiendo propiedades de la iluminacion
	GLfloat LightAmbient[] ={0.2f,0.2f,0.2f,1.0f};
	GLfloat LightDiffuse[] ={0.2f,0.2f,0.2f,1.0f};
	GLfloat LightSpecular[] ={0.5f,0.5f,0.5f,1.0f};
	GLfloat LightPosition[] ={100.0,0.0,0.0,1.0};
	GLfloat LightDirection[] ={0.0f,0.0f,-1.0f,1.0f};

	GLfloat LightAmbient0[] ={0.2f,0.2f,0.2f,1.0f};
	GLfloat LightDiffuse0[] ={0.2f,0.2f,0.2f,1.0f};
	GLfloat LightSpecular0[] ={0.5f,0.5f,0.5f,1.0f};
	GLfloat LightPosition0[] ={-100.0,0.0,0.0,1.0};
	GLfloat LightDirection0[] ={0.0f,0.0f,-1.0f,1.0f};

	glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbient0);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,LightDiffuse0);
	glLightfv(GL_LIGHT0,GL_SPECULAR,LightSpecular0);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,LightDirection0);
	
	glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmbient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,LightSpecular);
	glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,LightDirection);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glLightfv(GL_LIGHT1,GL_POSITION,LightPosition);
	glLightfv(GL_LIGHT0,GL_POSITION,LightPosition0);
	glPopMatrix();

	// definicion de los parametros de la textura
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	/*
	// Modulate : texture lighting
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	if(m_Texture.GetData() != NULL)
		glTexImage2D(GL_TEXTURE_2D,0,3,
		             m_Texture.GetWidth(),
					 m_Texture.GetHeight(),0,
					 GL_RGB,GL_UNSIGNED_BYTE,
					 m_Texture.GetData());
	*/
	// habilitando capacidades de las OpenGl
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// No Pintar las Caras traseras 
	glCullFace(GL_BACK);
	// activar modelo de iluminacion de dos caras
	// pero el hecho de haber Cull_Face no genera iluminacion
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1); 
	
	// Generacion de listas
	m_List_Base=glGenLists(10);

	// Soporte del Robot
	glNewList(m_List_Base,GL_COMPILE);
	  // optimizacion
	  glTranslated(-17,0,0);
	  // Hay que trasladar el eje para que coincida con el 
	  // dibujado en el Robot
	  glEnable(GL_CULL_FACE);
	  glBegin(GL_POLYGON);  // Tapa de abajo
	    glNormal3d(  0.0, -1.0,  0.0);
		glVertex3d(  0.0,  0.0,  0.0);
		glVertex3d(  0.0,  0.0, -17.0);
		glVertex3d(  17.0, 0.0, -17.0);
		glVertex3d(  17.0, 0.0,   0.0);
      glEnd();
	  glBegin(GL_POLYGON); // Tapa de los lados
	    glNormal3d( -1.0,  0.0,   0.0);
		glVertex3d(  0.0,  5.5,   0.0);
		glVertex3d(  0.0,  5.5, -17.0);
		glVertex3d(  0.0,  0.0, -17.0);
		glVertex3d(  0.0,  0.0,   0.0);
	  glEnd();
	  glBegin(GL_POLYGON);
	    glNormal3d(  1.0,  0.0,   0.0);
		glVertex3d(  17.0,  0.0,   0.0);
		glVertex3d(  17.0,  0.0, -17.0);
		glVertex3d(  17.0,  5.5, -17.0);
		glVertex3d(  17.0,  5.5,   0.0);
	  glEnd();
	  glBegin(GL_POLYGON); //Tapa Frontal
	    glNormal3d(  0.0,  0.0,   1.0);
		glVertex3d(  0.0,  0.0,   0.0);
		glVertex3d(  17.0,  0.0,   0.0);
		glVertex3d(  17.0,  5.5,   0.0);
		glVertex3d(  0.0,  5.5,   0.0);
	  glEnd();
	  glBegin(GL_POLYGON); //Tapa trasera
	    glNormal3d(  0.0,  0.0,  -1.0);
		glVertex3d(  0.0,  5.5, -17.0);
		glVertex3d(  17.0,  5.5,-17.0);
		glVertex3d(  17.0,  0.0,-17.0);
		glVertex3d(  0.0,  0.0, -17.0);
      glEnd();
	  glBegin(GL_POLYGON); //Tapas Inclinadas
	    glNormal3d(  -4.25/5.5,1.0,0.0);
		glVertex3d(  4.25,  11.0,   0.0);
		glVertex3d(  4.25, 11.0,  -17.0);
		glVertex3d(  0.0,  5.5,   -17.0);
		glVertex3d(  0.0,  5.5,   0.0);
	  glEnd();
	  glBegin(GL_POLYGON);
	    glNormal3d(  4.25/5.5,1.0,0.0);
		glVertex3d(  17.0,  5.5,   0.0);
		glVertex3d(  17.0,  5.5,   -17.0);
		glVertex3d(  12.25, 11.0,  -17.0);
		glVertex3d(  12.25,  11.0,   0.0);
	  glEnd();
	  glBegin(GL_POLYGON); // Tapa frontal de arriba
	    glNormal3d(  0.0,0.0,1.0);
		glVertex3d(  0.0,  5.5,   0.0);
		glVertex3d(  17.0,  5.5,   0.0);
		glVertex3d(  12.25, 11.0,  0.0);
		glVertex3d(  4.25,  11.0, 0.0);
	  glEnd();
	  glBegin(GL_POLYGON); 
	    glNormal3d(  0.0,0.0,-1.0);
		glVertex3d(  4.25,  11.0,-17.0);
		glVertex3d(  12.25, 11.0,-17.0);
		glVertex3d(  17.0,  5.5, - 17.0);
		glVertex3d(  0.0,  5.5,  -17.0);
	  glEnd();
	  glBegin(GL_POLYGON); // Tapa de arriba
	    glNormal3d(  0.0,  1.0,   0.0);
		glVertex3d(  4.25, 11.0,  0.0);
		glVertex3d(  12.25,  11.0,  0.0);
		glVertex3d(  12.25, 11.0, -17.0);
		glVertex3d(  4.25, 11.0,   -17.0);
	  glEnd();
	  // Salimos del soporte y vamos para el centro de giro 
	  glTranslated(8.5,11.0,-4.48);
	  glMaterialfv(GL_FRONT,GL_AMBIENT|GL_SPECULAR,GraySurface);
	  CCilindroXZ cilindro(2.2,1.4);
	  // No pintar tapas del cilindro
	  cilindro.Enabled(0);
	  cilindro.Paint();
	  glTranslated(0.0,1.4,0.0);        // Subimos arriba del cilindro
    glEndList();


	// Creando lista para la Base con todos los motores que 
	// tiene
	glNewList(m_List_Base+1,GL_COMPILE);

	  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT|GL_SPECULAR,BlackSurface);
  	  CEngraneXZ Engrane1(4.2,4.4,0.6,36);
	  Engrane1.Enabled(1);
	  Engrane1.Paint();
 	  glTranslated(0.0,0.6,0.0);       //arriba del engrane

	  // Esquina de la base 
	  glTranslated(-5.0,0.0,4.7625);
	  
	  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT|GL_SPECULAR,RedSurface);
	  
  	  // codigo de optimizacion
	  glDisable(GL_CULL_FACE);

	  // Tapa de abajo
	  glBegin(GL_POLYGON);
	  glNormal3d(  0.0, -1.0,   0.0);
	  glVertex3d(  0.0, 0.0,  0.0);
	  glVertex3d(  0.0, 0.0,   -17.0);
      glVertex3d(  10.0, 0.0, -17.0);
	  glVertex3d(  10.0, 0.0,  0.0);
	  glEnd();
	  
	  // Joroba frontal
	  glBegin(GL_POLYGON);
	  glNormal3d(  0.0, 0.0,   1.0);
	  glVertex3d(  0.0, 0.0,  0.0);
	  glVertex3d(  10.0, 0.0,  0.0);
      glVertex3d(  10.0, 1.0,  0.0);
	  glVertex3d(  0.0, 1.0,  0.0);
	  glEnd();
	  
	  // Joroba Trasera
	  glBegin(GL_POLYGON);
	  glNormal3d(  0.0,  0.0,   1.0);
	  glVertex3d(  0.0,  0.0, -17.0);
	  glVertex3d(  10.0, 0.0, -17.0);
      glVertex3d(  10.0, 1.0, -17.0);
	  glVertex3d(  0.0,  1.0, -17.0);
	  glEnd();
	  
	  //Tapas laterales
	  CPieza_01 Pieza01;
	  Pieza01.Paint();
	  
	  // Codigo de optimizacion
	  glEnable(GL_CULL_FACE);
	  
	  glTranslated(0.0,4.15,-4.15);
	  glRotated(90,0,0,1);
	  Motor_01();
	  glTranslated(0,0,-7);
	  Motor_01();
	  glRotated(-180,0,0,1);
	  glCallList(m_List_Base+5);
	  glTranslated(0,0,7);
	  glCallList(m_List_Base+5);
	  glRotated(90,0,0,1);
	  // ir a la esquina de la base
	  glTranslated(0.0,-4.15,4.15);
	  
	  // Ir a la Tapa de la derecha a pintar los motores
	  // con sus engranes
	  glTranslated(10.0,4.15,-4.15);
	  glRotated(-90,0,0,1);
	  Motor_01();
	  glTranslated(0,0,-7);
	  Motor_01();
	  glRotated(180,0,0,1);
	  glCallList(m_List_Base+5);
	  glTranslated(0,0,7);
	  glCallList(m_List_Base+5);
	  glRotated(-90,0,0,1);
	  // Regresar a la esquina de la base
	  glTranslated(-10.0,-4.15,4.15);
	  
	  CEngraneYZ Engrane(4.0,4.2,0.6,36);
	    
	  glTranslated(2.0,11.0,-4.0);
	  glPushMatrix();
	  
	  glTranslated(-2.0,0.0,0.0);
	  // Pintando eje de sujecion con tornillo
	  CCilindroYZ Cilindro_01(0.65,10.0);
	  Cilindro_01.Enabled(0);
	  glMaterialfv(GL_FRONT,GL_SPECULAR,GraySurface);
	  Cilindro_01.Paint();

	  glRotated(90,0,0,1);
	  Tornillo_02();
	  glRotated(-90,0,0,1);
	 

	  glTranslated(2.0,0.0,0.0);
	  CPoleaZY Polea(1.5,1.3,0.1,0.4);
	  
	  glMaterialfv(GL_FRONT,GL_SPECULAR,BlackSurface);
	  glTranslated(0.5,0.0,0.0);
	  Polea.Enabled(1+4);
	  Polea.Paint();
	  glTranslated(0.5,0.0,0.0);
	  glCallList(m_List_Base+3);
	  glTranslated(0.6,0.0,0.0);
	  Polea.Enabled(4+8);
	  Polea.Paint();
	  glTranslated(0.6,0.0,0.0);
	  Polea.Enabled(4);
	  Polea.Paint();
	  glTranslated(0.5,0.0,0.0);
	  glCallList(m_List_Base+3);
	  glTranslated(2.1,0.0,0.0);
	  glCallList(m_List_Base+3);
	  glTranslated(0.6,0.0,0.0);
	  Polea.Enabled(8);
	  Polea.Paint();
	  glTranslated(0.5,0.0,0.0);
	  Polea.Set(2.3,2.15,0.1,0.4);
	  Polea.Enabled(1+4);
	  Polea.Paint();
	  glTranslated(0.5,0.0,0.0);
	  Engrane.Enabled(1);
	  Engrane.Paint();
	  glPopMatrix();
	glEndList();

	// Creacion de la lista para el Hombro 
	//  
	glNewList(m_List_Base+2,GL_COMPILE);
		glMaterialfv(GL_FRONT,GL_SPECULAR|GL_AMBIENT,BlackSurface);

	glTranslated(-0.6,0.0,0.0);
	Engrane.Enabled(1);   // Activar Cara0
	Engrane.Paint();
	glTranslated(0.6,0.0,0.0);


	
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT|GL_SPECULAR,RedSurface);
	// Codigo de optimizacion
	glDisable(GL_CULL_FACE);

	CPieza_02 Pieza02;
	Pieza02.Paint();

	// ir al centro del codo
	glTranslated(0.1,0.0,19.0);
	glPushMatrix();
	// Dibujar todas las poleas
	glMaterialfv(GL_FRONT,GL_SPECULAR|GL_AMBIENT,BlackSurface);
	// Codigo de optimizacion
	glEnable(GL_CULL_FACE);

	glTranslated(0.4,0.0,0.0);
	Polea.Set(1.5,1.3,0.1,0.4);
	Polea.Enabled(15);
	Polea.Paint();
	glTranslated(1.1,0.0,0.0);
	Polea.Paint();
	glTranslated(0.8,0.0,0.0);
	Polea.Paint();
	glTranslated(2.7,0.0,0.0);
	Polea.Paint();
	glTranslated(0.9,0.0,0.0);
	Polea.Set(2.3,2.15,0.1,0.4);
	Polea.Enabled(2+8);
	Polea.Paint();

	glPopMatrix();
	glPushMatrix();

	// Dibujar el eje que soporta las poleas 
	glMaterialfv(GL_FRONT,GL_SPECULAR|GL_AMBIENT,GraySurface);
	CCilindroYZ Cilindro_02;
	Cilindro_02.Set(0.5,0.4);
	Cilindro_02.Enabled(0);
	Cilindro_02.Paint();
	glTranslated(1.0,0.0,0.0);
	Cilindro_02.Set(0.3,4.0);
	Cilindro_02.Paint();
	glTranslated(4.6,0.0,0.0);
	Cilindro_02.Set(0.5,0.3);
	Cilindro_02.Paint();
	glTranslated(0.8,0.0,0.0);
	Cilindro_02.Set(0.65,0.5);
	Cilindro_02.Paint();
	glPopMatrix();

	glEndList(); // Lista 2

////////////////////////////////////////////////////////////////////
// Piezas muy usadas 
////////////////////////////////////////////////////////////////////
	// Engranaje Negro YZ
	glNewList(m_List_Base+3,GL_COMPILE);
	  CEngraneYZ Temp01(4.0,4.2,0.6,36);
	  Temp01.Paint();
	glEndList();   // Lista 3

	//Piezas amarrillas Una por cada motor
	glNewList(m_List_Base+4,GL_COMPILE);
	  Ruedita_02();
	glEndList();   // Lista 4

	// Engranes en los ejes del Motor
	// Direccion positiva, Base en XZ
	glNewList(m_List_Base+5,GL_COMPILE);
	  Ruedita_01();
	glEndList();   // Lista 5

	// Codo con todas sus piezas
	glNewList(m_List_Base+6,GL_COMPILE);

	  glMaterialfv(GL_FRONT,GL_AMBIENT|GL_SPECULAR,RedSurface);
	  glDisable(GL_CULL_FACE);
	  CPieza_03 Pieza03;
	  Pieza03.Paint();
	  glTranslated(0.0,0.0,19.0);
	  glMaterialfv(GL_FRONT,GL_AMBIENT|GL_SPECULAR,BlackSurface);
	  // Codigo de optimizacion
	  glEnable(GL_CULL_FACE);
	  glPushMatrix();
	  CCilindroYZ Cilindro_001(2.0,0.4);
	  Cilindro_001.Enabled(2);
	  Cilindro_001.Paint();
	  glTranslated(0.4,0.0,0.0);
	  Cilindro_001.Enabled(0);
	  Cilindro_001.Set(1.3,0.5);
	  Cilindro_001.Paint();
	  glTranslated(4.6,0.0,0.0);
	  Cilindro_001.Paint();
	  glTranslated(0.5,0.0,0.0);
	  Cilindro_001.Set(2.0,0.4);
	  Cilindro_001.Enabled(1);
	  Cilindro_001.Paint();
	  glPopMatrix();
	glEndList();

	// inicializacion de los parametros de la camara
	Camara_toy=20;
	Camara_angx=0;
	
	return 0;
}

void CRobot1::MouseMoving()
{
	if (m_On_RButton)
	{
		if (abs(m_dCursor.cx)>20)
			m_Driver.SetDPos(0,(m_Prev_Data[0]+m_dCursor.cx)-m_Robot_Data[0]);
		m_Driver.SetDPos(1,(m_Prev_Data[1]+m_dCursor.cy*2)-m_Robot_Data[1]);
	}
	if (m_On_LButton)
	{
		m_Driver.SetDPos(2,(m_Prev_Data[0]+m_dCursor.cx)-m_Robot_Data[2]);
	}
		
}

void CRobot1::MouseClick()
{
	memcpy(m_Prev_Data,m_Robot_Data,6*sizeof(int));
}

BOOL CRobot1::GoToPoint(double points[])
{
	char a[20],b[20],c[20];
	int i;
	SetPoint(points);
	if (CalcAng()==0)
	{
		GetAng(m_Pos);

		// Esto para trabajar con el quick
		m_Comm32.GetPos(m_Temp_Pos);
		_itoa(m_Pos[0]-m_Temp_Pos[0],a,10);
		_itoa(m_Pos[1]-m_Temp_Pos[1],b,10);
		_itoa(m_Pos[2]-m_Temp_Pos[2],c,10);
		//m_String=m_String+"M0 "+a+" M1 "+b+" M2 "+c+ " ";
		//m_Comm32.SendString(m_String,m_String.GetLength());	
		for (i=0;i<3;i++)
			m_Temp_Pos[i]=m_Pos[i]-m_Temp_Pos[i];
		m_Temp_Pos[3]=0;
		m_Comm32.RefreshPos(m_Temp_Pos);
		if (m_OnExecute)
		{
			m_CmdChar=m_CmdChar+"M0 "+a+" M1 "+b+" M2 "+c+ " ";
		}
		for (i=0;i<3;i++)
			m_Driver.SetDPos(i,m_Pos[i]-m_Driver.m_Motor_Pos[i]);
		return true;
	} 
	// ya que mientras se ejecuta un comando hay que apagar el timer
	if (m_OnExecute) 
		return false;
	AfxMessageBox(" Punto Fuera de alcance ");
	return false;
}

//DEL void CRobot1::GetAng(double points[], double Ang[])
//DEL {
//DEL    GoToPoint(points);
//DEL 
//DEL }

void CRobot1::ExecuteList(PVOID *param, DWORD pCant)
{
	if (pCant==0) return;
	int i;
	// detener todos los motores
	for (i=0;i<6;i++)
		Stop(i);
	m_CmdChar.Empty();
	m_Timer_ID=SetTimer(10,1,NULL);
	if (m_Timer_ID)
	{
		m_OnExecute=true;
		m_ListCant=pCant;
		m_ListPos=0;
		m_List=param;
		m_Buffer=((CPos*)m_List[0])->GetMov();
	} else
		AfxMessageBox(" Error Interno ",0,0);

}

// Este procedimiento ejecuta cada un tiempo la secuenia de comandos 
// de una lista
void CRobot1::Executor()
{
	// variables temporales para reconstruir la cadena
//	char a[20],b[20];

	if (!m_OnExecute) return;
	if (m_OnWaiting)
	{
		m_OnWaiting=false;
		int i;
		for (i=0;i<6;i++)
			if (m_Driver.m_Motor_DPos[i]!=0) m_OnWaiting=true;
		return;
	}
	GetChar();
	switch(m_Char)
	{
	case 'G':
		{
			GetChar();
			if (m_Char!=32) break;
			if (!Negativo()) break;
			m_Point[0]=m_Num;
			if (!Negativo()) break;
			m_Point[1]=m_Num;
			if (!Negativo()) break;
			m_Point[2]=m_Num;
			if (!GoToPoint(m_Point))
			{
				StopExecutor();
				AfxMessageBox(" Punto Fuera de alcance ");
			}
			break;
		}
	case 'M':
		{
			if (Positivo()) m_Motor=(BYTE)m_Num;
			{
				_itoa(m_Num,a,10);
				if (Negativo())
				{
					m_Driver.SetDPos(m_Motor,m_Num);
					_itoa(m_Num,b,10);
					m_CmdChar=m_CmdChar+"M" +a+" "+b+" ";
				}
			}
			break;
		}
	case 'W':
		{
			m_CmdChar=m_CmdChar+"W ";
			m_OnWaiting=true;
			break;
		}
	case 'C':
		{
			if (Positivo()) m_Driver.SetMoving((BYTE)m_Num,true);
			break;
		}
	case 'S':
		{
			if (Positivo()) m_Driver.SetMoving((BYTE)m_Num,false);
			break;
		}
	case 0:
		{
			// Se acabo esta lista
			m_ListPos++;
			if (m_ListPos==m_ListCant)
			{
				ResetPos();
				StopExecutor();
				m_CmdChar=m_CmdChar+"\r";
			}
			else
			{
				m_Buffer=((CPos*)m_List[m_ListPos])->GetMov();
			}
			break;
		}
	case 32:
		{
			break;
		}
	default:
		{
			StopExecutor();
			AfxMessageBox("Invalid Comand",0,0);
			break;
		}
	}
}


// Devuelve un numero positivo
BOOL CRobot1::Positivo()
{
	m_Num=0;
	GetChar();
	while (true)
	{
		// Validar numero
		if ((m_Char < 0x30)|(m_Char > 0x39))
			return false;
		m_Num=m_Num*10;
		m_Num+=m_Char&0x0f;

		GetChar();
		if (m_Char==32) return true;
		if (m_Char==0)
		{
			m_Buffer--;
			return true;
		}
	}
}

BOOL CRobot1::Negativo()
{
	GetChar();
	if (m_Char== '-')
	{
		if (Positivo())
		{
			m_Num=-m_Num;
			return true;
		}
		return false;
	}
	m_Buffer--;
	return Positivo();
}

// Si las coordenadas del Robot and cambiado entonces es repintado
void CRobot1::CheckPos()
{
	if (memcmp(&m_Robot_Data,m_Driver.m_Motor_Pos,6*sizeof(int)))
	{
		memcpy(&m_Robot_Data,m_Driver.m_Motor_Pos,6*sizeof(int));
		Invalidate(true);
	}
}

// Esta funcion es llamada cuando la clase hija
// recibe un evento OnTimer con identificador
// distinto de 1
void CRobot1::Timer()
{
	if (m_OnExecute)
		Executor();
}

void CRobot1::GetChar()
{
	m_Char=*m_Buffer;
	m_Buffer++;
}

DWORD CRobot1::Move(BYTE pMotor, int pPosiciones)
{
	if (!m_OnExecute)
		m_Driver.SetDPos(pMotor,pPosiciones);
	return 0;
}

DWORD CRobot1::Run(BYTE pMotor, BYTE pDireccion)
{
	if (!m_OnExecute)
		m_Driver.SetMoving(pMotor,pDireccion+1);
	return 0;
}

DWORD CRobot1::Stop(BYTE pMotor)
{
	if (!m_OnExecute)
		m_Driver.SetMoving(pMotor,0);
	return 0;
}

void CRobot1::Close()
{
	m_Driver.Close();
}

void CRobot1::StopExecutor()
{
	m_OnExecute=false;
	KillTimer(m_Timer_ID);
}

// llevar el robot a la posicion inicial
void CRobot1::ResetPos()
{
	if (m_OnExecute)
	for (m_TempI=0;m_TempI<4;m_TempI++)
	{
		_itoa(-m_Driver.m_Motor_Pos[m_TempI],a,10);
		_itoa(m_TempI,b,10);
		m_CmdChar=m_CmdChar+" M"+b+" "+a+" ";
	}
	for (m_TempI=0;m_TempI<6;m_TempI++)
			m_Driver.SetDPos(m_TempI,-m_Driver.m_Motor_Pos[m_TempI]);
}

CString CRobot1::GetCmdChar()
{
	return m_CmdChar;
}
