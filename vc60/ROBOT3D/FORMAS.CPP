// Formas.cpp: implementation of the Formas class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Formas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

double senos[91];
int	Resolucion;     //Resolucion de las figuras circulares

void FillSin()
{
	int i;
	for (i=0;i<91;i++)
	{
		senos[i]=sin(i*3.14/180);
	}
	senos[90]=1.0;
	Resolucion=18;
}

void SetResolution( int param)
{
	int divisor;
	divisor=90/param;
	Resolucion=90/divisor;
}
int GetResolution()
{
	return Resolucion;

}

double Seno(int angulo)
{
	while (angulo > 360)
		angulo=angulo-360;
	while (angulo < 0)
		angulo=angulo+360;
	if (angulo < 90) 
		return senos[angulo];
	if (angulo < 180) 
		return senos[180-angulo];
	if (angulo < 270) 
		return -senos[angulo-180];
	return -senos[360-angulo];
}

double Coseno(int angulo)
{
	while (angulo > 360)
		angulo=angulo-360;
	while (angulo < 0)
		angulo=angulo+360;
	if (angulo < 90) 
		return senos[89-angulo];
	if (angulo < 180) 
		return -senos[89-(180-angulo)];
	if (angulo < 270) 
		return -senos[89-(angulo-180)];
	return senos[89-(360-angulo)];
}


CCilindroXY::CCilindroXY()
{

}

CCilindroXY::CCilindroXY(double pradio,double paltura)
{
	radio=pradio;
	altura=paltura;
}

CCilindroXY::Paint()
{
	glPushMatrix();
	glRotated(90.0,1.0,0.0,0.0);
	CCilindroXZ::Paint();
	glPopMatrix();
}



CCilindroXZ::CCilindroXZ()
{
	Tape0=TRUE;
	Tape1=TRUE;

}

CCilindroXZ::CCilindroXZ(double pradio,double paltura)
{
	radio=pradio;
	altura=paltura;
}
CCilindroXZ::Set(double pradio,double paltura)
{
	radio=pradio;
	altura=paltura;
}
CCilindroXZ::Paint()
{
	int grad;
	double dx,dz,dx1,dz1;

	glBegin(GL_TRIANGLES);
	for (grad=0;grad<90;grad=grad+Resolucion)
    {
		dx=radio*Seno(grad);
	    dz=radio*Coseno(grad);
		dx1=radio*Seno(grad+Resolucion);
		dz1=radio*Coseno(grad+Resolucion);
        // cuatro triangulos dobles
		// pareja 1
		if (altura < 0 )
		{
		  glNormal3d(dx/radio,0.0,dz/radio); 
		  glVertex3d(dx,0.0,dz);
		  glVertex3d(dx,altura,dz);
		  glNormal3d(dx1/radio,0.0,dz1/radio); 
		  glVertex3d(dx1,altura,dz1);

		  glNormal3d(dx1/radio,0.0,dz1/radio);
		  glVertex3d(dx1,altura,dz1);
		  glVertex3d(dx1,0.0,dz1);
		  glNormal3d(dx/radio,0.0,dz/radio);
		  glVertex3d(dx,0.0,dz);

		  // pareja 2
		  glNormal3d(-dx/radio,0.0,dz/radio); 
		  glVertex3d(-dx,altura,dz);
		  glVertex3d(-dx,0.0,dz);
		  glNormal3d(-dx1/radio,0.0,dz1/radio); 
		  glVertex3d(-dx1,altura,dz1);

		  glNormal3d(-dx1/radio,0.0,dz1/radio);
		  glVertex3d(-dx1,0.0,dz1);
		  glVertex3d(-dx1,altura,dz1);
		  glNormal3d(-dx/radio,0.0,dz/radio);
		  glVertex3d(-dx,0.0,dz);

		  // pareja 3
		  glNormal3d(-dx/radio,0.0,-dz/radio); 
		  glVertex3d(-dx,0.0,-dz);
		  glVertex3d(-dx,altura,-dz);
		  glNormal3d(-dx1/radio,0.0,-dz1/radio); 
		  glVertex3d(-dx1,altura,-dz1);

		  glNormal3d(-dx1/radio,0.0,-dz1/radio);
		  glVertex3d(-dx1,altura,-dz1);
		  glVertex3d(-dx1,0.0,-dz1);
		  glNormal3d(-dx/radio,0.0,-dz/radio);
		  glVertex3d(-dx,0.0,-dz);

		  // pareja 4
		  glNormal3d(dx/radio,0.0,-dz/radio); 
		  glVertex3d(dx,altura,-dz);
		  glVertex3d(dx,0.0,-dz);
		  glNormal3d(dx1/radio,0.0,-dz1/radio); 
		  glVertex3d(dx1,altura,-dz1);

		  glNormal3d(dx1/radio,0.0,-dz1/radio);
		  glVertex3d(dx1,0.0,-dz1);
		  glVertex3d(dx1,altura,-dz1);
		  glNormal3d(dx/radio,0.0,-dz/radio);
		  glVertex3d(dx,0.0,-dz);

		  if (Tape0) 
		  {
			   glNormal3d(0.0,1.0,0.0);
			   
			   glVertex3d(0.0,0.0,0.0);
			   glVertex3d(dx,0.0,dz);
			   glVertex3d(dx1,0.0,dz1);
			   
			   glVertex3d(-dx,0.0,dz);
			   glVertex3d(0.0,0.0,0.0);
			   glVertex3d(-dx1,0.0,dz1);
			   
			   glVertex3d(-dx1,0.0,-dz1);
			   glVertex3d(0.0,0.0,0.0);
			   glVertex3d(-dx,0.0,-dz);
			   
			   glVertex3d(dx,0.0,-dz);
			   glVertex3d(0.0,0.0,0.0);
			   glVertex3d(dx1,0.0,-dz1);
		  }
		  if (Tape1)
		  {
			  glNormal3d(0.0,-1.0,0.0);
			  
			  glVertex3d(0.0,altura,0.0);
			  glVertex3d(dx1,altura,dz1);
			  glVertex3d(dx,altura,dz);
			  
			  glVertex3d(-dx1,altura,dz1);
			  glVertex3d(0.0,altura,0.0);
			  glVertex3d(-dx,altura,dz);
			  
			  glVertex3d(0.0,altura,0.0);
			  glVertex3d(-dx1,altura,-dz1);
			  glVertex3d(-dx,altura,-dz);
			  
			  glVertex3d(dx1,altura,-dz1);
			  glVertex3d(0.0,altura,0.0);
			  glVertex3d(dx,altura,-dz);	  
		  }
		} else 
		{
			// pareja 1
			glNormal3d(dx/radio,0.0,dz/radio); 
			glVertex3d(dx,altura,dz);
			glVertex3d(dx,0.0,dz);
			glNormal3d(dx1/radio,0.0,dz1/radio); 
			glVertex3d(dx1,altura,dz1);

			glNormal3d(dx1/radio,0.0,dz1/radio);
			glVertex3d(dx1,0.0,dz1);
			glVertex3d(dx1,altura,dz1);
			glNormal3d(dx/radio,0.0,dz/radio);
			glVertex3d(dx,0.0,dz);

			// pareja 2
			glNormal3d(-dx/radio,0.0,dz/radio); 
			glVertex3d(-dx,0.0,dz);
			glVertex3d(-dx,altura,dz);
			glNormal3d(-dx1/radio,0.0,dz1/radio); 
			glVertex3d(-dx1,altura,dz1);

			glNormal3d(-dx1/radio,0.0,dz1/radio);
			glVertex3d(-dx1,altura,dz1);
			glVertex3d(-dx1,0.0,dz1);
			glNormal3d(-dx/radio,0.0,dz/radio);
			glVertex3d(-dx,0.0,dz);

		  // pareja 3
		  glNormal3d(-dx/radio,0.0,-dz/radio); 
		  glVertex3d(-dx,altura,-dz);
		  glVertex3d(-dx,0.0,-dz);
		  glNormal3d(-dx1/radio,0.0,-dz1/radio); 
		  glVertex3d(-dx1,altura,-dz1);

		  glNormal3d(-dx1/radio,0.0,-dz1/radio);
		  glVertex3d(-dx1,0.0,-dz1);
		  glVertex3d(-dx1,altura,-dz1);
		  glNormal3d(-dx/radio,0.0,-dz/radio);
		  glVertex3d(-dx,0.0,-dz);

		  // pareja 4
		  glNormal3d(dx/radio,0.0,-dz/radio); 
		  glVertex3d(dx,0.0,-dz);
		  glVertex3d(dx,altura,-dz);
		  glNormal3d(dx1/radio,0.0,-dz1/radio); 
		  glVertex3d(dx1,altura,-dz1);

		  glNormal3d(dx1/radio,0.0,-dz1/radio);
		  glVertex3d(dx1,altura,-dz1);
		  glVertex3d(dx1,0.0,-dz1);
		  glNormal3d(dx/radio,0.0,-dz/radio);
		  glVertex3d(dx,0.0,-dz);

  		  if (Tape0) 
		  {
			   glNormal3d(0.0,-1.0,0.0);

			   glVertex3d(dx,0.0,dz);
			   glVertex3d(0.0,0.0,0.0);
			   glVertex3d(dx1,0.0,dz1);

			   glVertex3d(0.0,0.0,0.0);
			   glVertex3d(-dx,0.0,dz);
			   glVertex3d(-dx1,0.0,dz1);

			   glVertex3d(0.0,0.0,0.0);
			   glVertex3d(-dx1,0.0,-dz1);
			   glVertex3d(-dx,0.0,-dz);

			   glVertex3d(0.0,0.0,0.0);
			   glVertex3d(dx,0.0,-dz);
			   glVertex3d(dx1,0.0,-dz1);

		  }
		  if (Tape1)
		  {
			  glNormal3d(0.0,1.0,0.0);

			  glVertex3d(dx1,altura,dz1);
			  glVertex3d(0.0,altura,0.0);
			  glVertex3d(dx,altura,dz);

			  glVertex3d(0.0,altura,0.0);
			  glVertex3d(-dx1,altura,dz1);
			  glVertex3d(-dx,altura,dz);

			  glVertex3d(-dx1,altura,-dz1);
			  glVertex3d(0.0,altura,0.0);
			  glVertex3d(-dx,altura,-dz);

			  glVertex3d(0.0,altura,0.0);
			  glVertex3d(dx1,altura,-dz1);
			  glVertex3d(dx,altura,-dz);	  
		  }
		}
	}
	glEnd();
}

CCilindroYZ::CCilindroYZ()
{

}

CCilindroYZ::CCilindroYZ(double pradio,double paltura)
{
	radio=pradio;
	altura=paltura;
}


CCilindroYZ::Paint()
{
	glPushMatrix();
	glRotated(-90.0,0.0,0.0,1.0);
	CCilindroXZ::Paint();
	glPopMatrix();
}

CCaja::Paint()
{

	glBegin(GL_POLYGON);
	  glNormal3d(0.0,-1.0,0.0);
	  glVertex3d(0.0  ,0.0,0.0);
	  glVertex3d(0.0  ,0.0,Depth);
	  glVertex3d(Width,0.0,Depth);
	  glVertex3d(Width,0.0,0.0);
	glEnd();

	glBegin(GL_POLYGON);
	  glNormal3d(0.0,1.0,0.0);
	  glVertex3d(0.0  ,Height,0.0);
	  glVertex3d(Width,Height,0.0);
	  glVertex3d(Width,Height,Depth);
	  glVertex3d(0.0  ,Height,Depth);
	glEnd();

	glBegin(GL_POLYGON);
	  glNormal3d(-1.0,0.0,0.0);
	  glVertex3d(0.0,0.0   ,0.0);
	  glVertex3d(0.0,0.0   ,Depth);
	  glVertex3d(0.0,Height,Depth);
	  glVertex3d(0.0,Height,0.0);
	glEnd();

	glBegin(GL_POLYGON);
	  glNormal3d(1.0,0.0,0.0);
	  glVertex3d(Width,0.0   ,0.0);
	  glVertex3d(Width,Height,0.0);
	  glVertex3d(Width,Height,Depth);
	  glVertex3d(Width,0.0   ,Depth);
	glEnd();

	glBegin(GL_POLYGON);
	  glNormal3d(0.0,0.0,-1.0);
	  glVertex3d(0.0  ,0.0   ,0.0);
	  glVertex3d(0.0  ,Height,0.0);
	  glVertex3d(Width,Height,0.0);
	  glVertex3d(Width,0.0   ,0.0);
	glEnd();

	glBegin(GL_POLYGON);
	  glNormal3d(0.0,0.0,1.0);
	  glVertex3d(0.0  ,0.0   ,Depth);
	  glVertex3d(Width,0.0   ,Depth);
	  glVertex3d(Width,Height,Depth);
	  glVertex3d(0.0  ,Height,Depth);
	glEnd();
}

CCaja::CCaja()
{
	Set(1,1,1);
}

CCaja::CCaja(double pHeight, double pWidth,double pDepth)
{
	Set(pHeight,pWidth,pDepth);
}

CEsfera::CEsfera()
{

}

CEsfera::CEsfera(double pradio)
{
	radio=pradio;

}

CEsfera::Set(double pradio)
{
	radio=pradio;

}

CEsfera::Paint()
{
	double radio1,radio2;
	double y1,y2;
	double x1,x2,x3,x4;
	double z1,z2,z3,z4;
	int ang,ang1;

	glBegin(GL_TRIANGLES);
	for (ang=0;ang<90;ang=ang+Resolucion)
	{
		radio1=radio*Coseno(ang);
		radio2=radio*Coseno(ang+Resolucion);
		y1=radio*Seno(ang);
		y2=radio*Seno(ang+Resolucion);
		for (ang1=0;ang1<90;ang1=ang1+Resolucion)
		{
			x1=radio1*Coseno(ang1);
			x2=radio2*Coseno(ang1);
			x3=radio1*Coseno(ang1+Resolucion);
			x4=radio2*Coseno(ang1+Resolucion);
			z1=radio1*Seno(ang1);
			z2=radio2*Seno(ang1);
			z3=radio1*Seno(ang1+Resolucion);
			z4=radio2*Seno(ang1+Resolucion);
			
			// Triangulos de la cara  I
			glNormal3d(x1/radio,y1/radio,z1/radio);
			glVertex3d(x1,y1,z1);
			glNormal3d(x2/radio,y2/radio,z2/radio);
			glVertex3d(x2,y2,z2);
			glNormal3d(x4/radio,y2/radio,z4/radio);
			glVertex3d(x4,y2,z4);

			glNormal3d(x3/radio,y1/radio,z3/radio);
			glVertex3d(x3,y1,z3);
			glNormal3d(x1/radio,y1/radio,z1/radio);
			glVertex3d(x1,y1,z1);
			glNormal3d(x4/radio,y2/radio,z4/radio);
			glVertex3d(x4,y2,z4);

			// Triangulos de la cara  II
			glNormal3d(-x2/radio,y2/radio,z2/radio);
			glVertex3d(-x2,y2,z2);
			glNormal3d(-x1/radio,y1/radio,z1/radio);
			glVertex3d(-x1,y1,z1);
			glNormal3d(-x4/radio,y2/radio,z4/radio);
			glVertex3d(-x4,y2,z4);

			glNormal3d(-x1/radio,y1/radio,z1/radio);
			glVertex3d(-x1,y1,z1);
			glNormal3d(-x3/radio,y1/radio,z3/radio);
			glVertex3d(-x3,y1,z3);
			glNormal3d(-x4/radio,y2/radio,z4/radio);
			glVertex3d(-x4,y2,z4);

			// Triangulos de la cara  III
			glNormal3d(-x1/radio,y1/radio,-z1/radio);
			glVertex3d(-x1,y1,-z1);
			glNormal3d(-x2/radio,y2/radio,-z2/radio);
			glVertex3d(-x2,y2,-z2);
			glNormal3d(-x4/radio,y2/radio,-z4/radio);
			glVertex3d(-x4,y2,-z4);

			glNormal3d(-x3/radio,y1/radio,-z3/radio);
			glVertex3d(-x3,y1,-z3);
			glNormal3d(-x1/radio,y1/radio,-z1/radio);
			glVertex3d(-x1,y1,-z1);
			glNormal3d(-x4/radio,y2/radio,-z4/radio);
			glVertex3d(-x4,y2,-z4);

			// Triangulos de la cara  IV
			glNormal3d(x2/radio,y2/radio,-z2/radio);
			glVertex3d(x2,y2,-z2);
			glNormal3d(x1/radio,y1/radio,-z1/radio);
			glVertex3d(x1,y1,-z1);
			glNormal3d(x4/radio,y2/radio,-z4/radio);
			glVertex3d(x4,y2,-z4);

			glNormal3d(x1/radio,y1/radio,-z1/radio);
			glVertex3d(x1,y1,-z1);
			glNormal3d(x3/radio,y1/radio,-z3/radio);
			glVertex3d(x3,y1,-z3);
			glNormal3d(x4/radio,y2/radio,-z4/radio);
			glVertex3d(x4,y2,-z4);


			// Zona que posee la y negativa
			// Triangulos de la cara  I
			
			glNormal3d(x2/radio,-y2/radio,z2/radio);
			glVertex3d(x2,-y2,z2);
			glNormal3d(x1/radio,-y1/radio,z1/radio);
			glVertex3d(x1,-y1,z1);
			glNormal3d(x4/radio,-y2/radio,z4/radio);
			glVertex3d(x4,-y2,z4);

			glNormal3d(x1/radio,-y1/radio,z1/radio);
			glVertex3d(x1,-y1,z1);
			glNormal3d(x3/radio,-y1/radio,z3/radio);
			glVertex3d(x3,-y1,z3);
			glNormal3d(x4/radio,-y2/radio,z4/radio);
			glVertex3d(x4,-y2,z4);

			// Triangulos de la cara  II
			glNormal3d(-x1/radio,-y1/radio,z1/radio);
			glVertex3d(-x1,-y1,z1);
			glNormal3d(-x2/radio,-y2/radio,z2/radio);
			glVertex3d(-x2,-y2,z2);
			glNormal3d(-x4/radio,-y2/radio,z4/radio);
			glVertex3d(-x4,-y2,z4);

			
			glNormal3d(-x3/radio,-y1/radio,z3/radio);
			glVertex3d(-x3,-y1,z3);
			glNormal3d(-x1/radio,-y1/radio,z1/radio);
			glVertex3d(-x1,-y1,z1);
			glNormal3d(-x4/radio,-y2/radio,z4/radio);
			glVertex3d(-x4,-y2,z4);

			// Triangulos de la cara  III
			
			glNormal3d(-x2/radio,-y2/radio,-z2/radio);
			glVertex3d(-x2,-y2,-z2);
			glNormal3d(-x1/radio,-y1/radio,-z1/radio);
			glVertex3d(-x1,-y1,-z1);
			glNormal3d(-x4/radio,-y2/radio,-z4/radio);
			glVertex3d(-x4,-y2,-z4);

			glNormal3d(-x1/radio,-y1/radio,-z1/radio);
			glVertex3d(-x1,-y1,-z1);
			glNormal3d(-x3/radio,-y1/radio,-z3/radio);
			glVertex3d(-x3,-y1,-z3);
			glNormal3d(-x4/radio,-y2/radio,-z4/radio);
			glVertex3d(-x4,-y2,-z4);

			// Triangulos de la cara  IV
			
			
			glNormal3d(x1/radio,-y1/radio,-z1/radio);
			glVertex3d(x1,-y1,-z1);
			glNormal3d(x2/radio,-y2/radio,-z2/radio);
			glVertex3d(x2,-y2,-z2);
			glNormal3d(x4/radio,-y2/radio,-z4/radio);
			glVertex3d(x4,-y2,-z4);

			
			glNormal3d(x3/radio,-y1/radio,-z3/radio);
			glVertex3d(x3,-y1,-z3);
			glNormal3d(x1/radio,-y1/radio,-z1/radio);
			glVertex3d(x1,-y1,-z1);
			glNormal3d(x4/radio,-y2/radio,-z4/radio);
			glVertex3d(x4,-y2,-z4);
		}
	}
	glEnd();
}

CEngraneXZ::CEngraneXZ()
{
	Tape0=true;
	Tape1=true;
}

CEngraneXZ::CEngraneXZ(double pradio1,double pradio2,double paltura,int pdientes)
{
	radio1=pradio1;
	radio2=pradio2;
	altura=paltura;
	dientes=pdientes;
}

CEngraneXZ::Set(double pradio1,double pradio2,double paltura,int pdientes)
{
	radio1=pradio1;
	radio2=pradio2;
	altura=paltura;
	dientes=pdientes;
}

CEngraneXZ::Enabled(int param)
{
	Tape0=(BOOL)((param & 1)!=0);
	Tape1=(BOOL)((param & 2)!=0);
}

CEngraneXZ::Paint()
{
	
	int ang;
	int Paso=360/dientes;
	double dx1,dz1,dx2,dz2,dx3,dz3;
	double Normal1,Normal2;
	double NorTemp;

	for (ang=0;ang<360;ang=ang+Paso)
	{
		dx1=radio1*Coseno(ang);
		dz1=radio1*Seno(ang);
		dx2=radio2*Coseno(ang+Paso/2);
		dz2=radio2*Seno(ang+Paso/2);
		dx3=radio1*Coseno(ang+Paso);
		dz3=radio1*Seno(ang+Paso);

		Normal1=fabs(dx2-dx1);
		NorTemp=fabs(dz2-dz1);
		if (Normal1 < NorTemp ) Normal1=NorTemp;
		Normal2=fabs(dx3-dx2);
		NorTemp=fabs(dz3-dz2);
		if (Normal2 < NorTemp ) Normal2=NorTemp;


		glBegin(GL_TRIANGLES);
		// Triangulos del diente


		if (altura > 0)
		{
			// cara 1
			glNormal3d((dz2-dz1)/Normal1,0.0,-(dx2-dx1)/Normal1);
			
			glVertex3d(dx1,0.0,dz1);
			glVertex3d(dx1,altura,dz1);
			glVertex3d(dx2,0.0,dz2);
			
			glVertex3d(dx1,altura,dz1);
			glVertex3d(dx2,altura,dz2);
			glVertex3d(dx2,0.0,dz2);
			
			// Cara II
			glNormal3d((dz3-dz2)/Normal2,0.0,- (dx3-dx2)/Normal2);
			
			glVertex3d(dx2,0.0,dz2);
			glVertex3d(dx2,altura,dz2);
			glVertex3d(dx3,0.0,dz3);
			
			glVertex3d(dx2,altura,dz2);
			glVertex3d(dx3,altura,dz3);
			glVertex3d(dx3,0.0,dz3);

			if (Tape1)
			{
				glNormal3d(0.0,1.0,0.0);

			
				glVertex3d(dx1,altura,dz1);
				glVertex3d(0.0,altura,0.0);
				glVertex3d(dx2,altura,dz2);
				
				glVertex3d(dx2,altura,dz2);
				glVertex3d(0.0,altura,0.0);
				glVertex3d(dx3,altura,dz3);
			}
			if (Tape0)
			{
				glNormal3d(0.0,-1.0,0.0);
				
				glVertex3d(0.0,0.0,0.0);
				glVertex3d(dx1,0.0,dz1);
				glVertex3d(dx2,0.0,dz2);
				
				glVertex3d(0.0,0.0,0.0);
				glVertex3d(dx2,0.0,dz2);
				glVertex3d(dx3,0.0,dz3);
			}
		}   // end if altura > 0
		glEnd();
	}  // end of for i
	
}


CEngraneYZ::CEngraneYZ()
{

}

CEngraneYZ::CEngraneYZ(double pradio1,double pradio2,double paltura,int pdientes)
{
	radio1=pradio1;
	radio2=pradio2;
	altura=paltura;
	dientes=pdientes;
}

CEngraneYZ::Paint()
{
	glPushMatrix();
	glRotated(-90.0,0.0,0.0,1.0);
	CEngraneXZ::Paint();
	glPopMatrix();

}

CEngraneXY::CEngraneXY()
{

}

CEngraneXY::CEngraneXY(double pradio1,double pradio2,double paltura,int pdientes)
{
	radio1=pradio1;
	radio2=pradio2;
	altura=paltura;
	dientes=pdientes;
}

CEngraneXY::Paint()
{
	glPushMatrix();
	glRotated(90.0,1.0,0.0,0.0);
	CEngraneXZ::Paint();
	glPopMatrix();

}

CCilindroXZ::Enabled(int param)
{
	Tape0=(BOOL)((param & 1)!=0);
	Tape1=(BOOL)((param & 2)!=0);
}


CPoleaXZ::CPoleaXZ()
{
	Tapa0=TRUE;
	Tapa1=TRUE;
	Cilindro0=TRUE;
	Cilindro1=TRUE;
}

CPoleaXZ::CPoleaXZ(double pradioExt, double pradioInt, double phExt, double phInt)
{

	radioExt=pradioExt;
	radioInt=pradioInt;
	hExt=phExt;
	hInt=phInt;
}

CPoleaXZ::Set(double pradioExt, double pradioInt, double phExt, double phInt)
{

	radioExt=pradioExt;
	radioInt=pradioInt;
	hExt=phExt;
	hInt=phInt;
}

CPoleaXZ::Enabled(int param)
{
	Tapa0=(BOOL)((param & 1)!=0);
	Tapa1=(BOOL)((param & 2)!=0);
	Cilindro0=(BOOL)((param & 4)!=0);
	Cilindro1=(BOOL)((param & 8)!=0);
}

CPoleaXZ::Paint()
{
	int activar;
	glPushMatrix();
	if (Cilindro0)
	{
		if (!Tapa0)
			CCilindroXZ::Enabled(2);  // Pintar Tapa 1
		CCilindroXZ::Set(radioExt,hExt);
		CCilindroXZ::Paint();
		glTranslated(0.0,hExt,0.0);
	}

	if ((!Cilindro0) & (Tapa0))
		activar=1;
	else
		activar=0;

	if ((!Cilindro1) & (Tapa1))
		activar=activar | 2;

	CCilindroXZ::Enabled(activar);

	CCilindroXZ::Set(radioInt,hInt);
	CCilindroXZ::Paint();

	CCilindroXZ::Enabled(3);
	if (Cilindro1)
	{
		if (!Tapa1)
			CCilindroXZ::Enabled(1);
	glTranslated(0.0,hInt,0.0);
	CCilindroXZ::Set(radioExt,hExt);
	CCilindroXZ::Paint();
	}

	glPopMatrix();

}	

CPoleaXY::CPoleaXY()
{

}

CPoleaXY::Paint()
{
	glPushMatrix();
	glRotated(90.0,1.0,0.0,0.0);
	CPoleaXZ::Paint();
	glPopMatrix();


}

CPoleaXY::CPoleaXY(double pradioExt, double pradioInt, double phExt, double phInt)
{
	radioExt=pradioExt;
	radioInt=pradioInt;
	hExt=phExt;
	hInt=phInt;
}

CPoleaZY::CPoleaZY()
{
	
}

CPoleaZY::Paint()
{
	glPushMatrix();
	glRotated(-90.0,0.0,0.0,1.0);
	CPoleaXZ::Paint();
	glPopMatrix();


}

CPoleaZY::CPoleaZY(double pradioExt, double pradioInt, double phExt, double phInt)
{
	radioExt=pradioExt;
	radioInt=pradioInt;
	hExt=phExt;
	hInt=phInt;
}

void CAnilloXZ::Paint()
{
	int grad;
	double dx2,dz2,dx1,dz1;
	double dx3,dz3,dx4,dz4;

	glBegin(GL_TRIANGLES);

	for (grad=0;grad<90;grad=grad+Resolucion)
	{
		dx1=RadioExt*Seno(grad);
	    dz1=RadioExt*Coseno(grad);
		dx2=RadioExt*Seno(grad+Resolucion);
		dz2=RadioExt*Coseno(grad+Resolucion);

		dx3=RadioInt*Seno(grad);
	    dz3=RadioInt*Coseno(grad);
		dx4=RadioInt*Seno(grad+Resolucion);
		dz4=RadioInt*Coseno(grad+Resolucion);

		if (Tape0)
		{
			glNormal3d(0.0,-1.0,0.0);
			// cuadrante I
			glVertex3d(dx1,0.0,dz1);
			glVertex3d(dx3,0.0,dz3);
			glVertex3d(dx4,0.0,dz4);

			glVertex3d(dx2,0.0,dz2);
			glVertex3d(dx1,0.0,dz1);
			glVertex3d(dx4,0.0,dz4);

			// Cuadrante II
			glVertex3d(-dx3,0.0,dz3);
			glVertex3d(-dx1,0.0,dz1);
			glVertex3d(-dx4,0.0,dz4);

			glVertex3d(-dx1,0.0,dz1);
			glVertex3d(-dx2,0.0,dz2);
			glVertex3d(-dx4,0.0,dz4);

			// Cuadrante III
			glVertex3d(-dx1,0.0,-dz1);
			glVertex3d(-dx3,0.0,-dz3);
			glVertex3d(-dx4,0.0,-dz4);

			glVertex3d(-dx2,0.0,-dz2);
			glVertex3d(-dx1,0.0,-dz1);
			glVertex3d(-dx4,0.0,-dz4);

			// Cuadrante IV
			glVertex3d(dx3,0.0,-dz3);
			glVertex3d(dx1,0.0,-dz1);
			glVertex3d(dx4,0.0,-dz4);

			glVertex3d(dx1,0.0,-dz1);
			glVertex3d(dx2,0.0,-dz2);
			glVertex3d(dx4,0.0,-dz4);
		}

		if (Tape1)
		{
			glNormal3d(0.0,1.0,0.0);
			// cuadrante I
			glVertex3d(dx3,altura,dz3);
			glVertex3d(dx1,altura,dz1);
			glVertex3d(dx4,altura,dz4);

			glVertex3d(dx1,altura,dz1);
			glVertex3d(dx2,altura,dz2);
			glVertex3d(dx4,altura,dz4);

			// Cuadrante II
			glVertex3d(-dx3,altura,dz3);
			glVertex3d(-dx4,altura,dz4);
			glVertex3d(-dx1,altura,dz1);

			glVertex3d(-dx1,altura,dz1);
			glVertex3d(-dx4,altura,dz4);
			glVertex3d(-dx2,altura,dz2);

			// Cuadrante III
			glVertex3d(-dx3,altura,-dz3);
			glVertex3d(-dx1,altura,-dz1);
			glVertex3d(-dx4,altura,-dz4);

			glVertex3d(-dx1,altura,-dz1);
			glVertex3d(-dx2,altura,-dz2);
			glVertex3d(-dx4,altura,-dz4);

			// Cuadrante IV
			glVertex3d(dx1,altura,-dz1);
			glVertex3d(dx3,altura,-dz3);
			glVertex3d(dx4,altura,-dz4);

 			glVertex3d(dx2,altura,-dz2);
			glVertex3d(dx1,altura,-dz1);
			glVertex3d(dx4,altura,-dz4);
		}
		
		// Tapa Externa
		if (TapeExt)
		{
			// Cuadrante I
			glNormal3d(dx1/RadioExt,0.0,dz1/RadioExt); 
			glVertex3d(dx1,altura,dz1);
			glVertex3d(dx1,0.0,dz1);
			glNormal3d(dx2/RadioExt,0.0,dz2/RadioExt); 
			glVertex3d(dx2,altura,dz2);
			
			glNormal3d(dx2/RadioExt,0.0,dz2/RadioExt);
			glVertex3d(dx2,0.0,dz2);
			glVertex3d(dx2,altura,dz2);
			glNormal3d(dx1/RadioExt,0.0,dz1/RadioExt);
			glVertex3d(dx1,0.0,dz1);

			// Cuadrante II
			glNormal3d(-dx1/RadioExt,0.0,-dz1/RadioExt); 
			glVertex3d(-dx1,altura,-dz1);
			glVertex3d(-dx1,0.0,-dz1);
			glNormal3d(-dx2/RadioExt,0.0,-dz2/RadioExt); 
			glVertex3d(-dx2,altura,-dz2);
			
			glNormal3d(-dx2/RadioExt,0.0,-dz2/RadioExt);
			glVertex3d(-dx2,0.0,-dz2);
			glVertex3d(-dx2,altura,-dz2);
			glNormal3d(-dx1/RadioExt,0.0,-dz1/RadioExt);
			glVertex3d(-dx1,0.0,-dz1);

			// Cuadrante III
			glNormal3d(-dx1/RadioExt,0.0,dz1/RadioExt); 
			glVertex3d(-dx1,0.0,dz1);
			glVertex3d(-dx1,altura,dz1);
			glNormal3d(-dx2/RadioExt,0.0,dz2/RadioExt); 
			glVertex3d(-dx2,altura,dz2);
			
			glNormal3d(-dx2/RadioExt,0.0,dz2/RadioExt);
			glVertex3d(-dx2,altura,dz2);
			glVertex3d(-dx2,0.0,dz2);
			glNormal3d(-dx1/RadioExt,0.0,dz1/RadioExt);
			glVertex3d(-dx1,0.0,dz1);

			// Cuadrante IV
			glNormal3d(dx1/RadioExt,0.0,-dz1/RadioExt); 
			glVertex3d(dx1,0.0,-dz1);
			glVertex3d(dx1,altura,-dz1);
			glNormal3d(dx2/RadioExt,0.0,-dz2/RadioExt); 
			glVertex3d(dx2,altura,-dz2);
			
			glNormal3d(dx2/RadioExt,0.0,-dz2/RadioExt);
			glVertex3d(dx2,altura,-dz2);
			glVertex3d(dx2,0.0,-dz2);
			glNormal3d(dx1/RadioExt,0.0,-dz1/RadioExt);
			glVertex3d(dx1,0.0,-dz1);


		}
        // Tapa Interna
		if (TapeInt)
		{
			
			// Cuadrante I
			glNormal3d(-dx3/RadioInt,0.0,-dz3/RadioInt); 
			glVertex3d(dx3,0.0,dz3);
			glVertex3d(dx3,altura,dz3);
			glNormal3d(-dx4/RadioInt,0.0,-dz4/RadioInt); 
			glVertex3d(dx4,altura,dz4);
			
			glNormal3d(-dx4/RadioInt,0.0,-dz4/RadioInt);
			glVertex3d(dx4,altura,dz4);
			glVertex3d(dx4,0.0,dz4);
			glNormal3d(-dx3/RadioInt,0.0,-dz3/RadioInt);
			glVertex3d(dx3,0.0,dz3);

			// Cuadrante II
			glNormal3d(dx3/RadioInt,0.0,dz3/RadioInt); 
			glVertex3d(-dx3,0.0,-dz3);
			glVertex3d(-dx3,altura,-dz3);
			glNormal3d(dx4/RadioInt,0.0,dz4/RadioInt); 
			glVertex3d(-dx4,altura,-dz4);
			
			glNormal3d(dx4/RadioInt,0.0,dz4/RadioInt);
			glVertex3d(-dx4,altura,-dz4);
			glVertex3d(-dx4,0.0,-dz4);
			glNormal3d(dx3/RadioInt,0.0,dz3/RadioInt);
			glVertex3d(-dx3,0.0,-dz3);

			// Cuadrante III
			glNormal3d(dx3/RadioInt,0.0,-dz3/RadioInt); 
			glVertex3d(-dx3,altura,dz3);
			glVertex3d(-dx3,0.0,dz3);
			glNormal3d(dx4/RadioInt,0.0,-dz4/RadioInt); 
			glVertex3d(-dx4,altura,dz4);
			
			glNormal3d(dx4/RadioInt,0.0,-dz4/RadioInt);
			glVertex3d(-dx4,0.0,dz4);
			glVertex3d(-dx4,altura,dz4);
			glNormal3d(dx3/RadioInt,0.0,-dz3/RadioInt);
			glVertex3d(-dx3,0.0,dz3);

			// Cuadrante IV
			glNormal3d(-dx3/RadioInt,0.0,dz3/RadioInt); 
			glVertex3d(dx3,altura,-dz3);
			glVertex3d(dx3,0.0,-dz3);
			glNormal3d(-dx4/RadioInt,0.0,dz4/RadioInt); 
			glVertex3d(dx4,altura,-dz4);
			
			glNormal3d(-dx4/RadioInt,0.0,dz4/RadioInt);
			glVertex3d(dx4,0.0,-dz4);
			glVertex3d(dx4,altura,-dz4);
			glNormal3d(-dx3/RadioInt,0.0,dz3/RadioInt);
			glVertex3d(dx3,0.0,-dz3);
		}
		
    }
	glEnd();
}

CAnilloXZ::CAnilloXZ()
{
	Tape0=TRUE;
	Tape1=TRUE;
	TapeExt=TRUE;
	TapeInt=TRUE;
}

CAnilloXZ::~CAnilloXZ()
{

}

void CAnilloXZ::Set(double pradioInt, double pradioExt, double paltura)
{
	RadioInt=pradioInt;
	RadioExt=pradioExt;
	altura=paltura;

}

void CAnilloXZ::Enable(int param)
{
	Tape0=(BOOL)((param & 1)!=0);
	Tape1=(BOOL)((param & 2)!=0);
	TapeInt=(BOOL)((param & 4)!=0);
	TapeExt=(BOOL)((param & 8)!=0);
}

void CCaja::Set(double pHeight, double pWidth, double pDepth)
{
	Height=pHeight;
	Width=pWidth;
	Depth=pDepth;
	if (pHeight <0) Height=-1*Height;
	if (pWidth  <0) Width =-1*Width;
	if (pDepth  <0) Depth =-1*Depth;
}
