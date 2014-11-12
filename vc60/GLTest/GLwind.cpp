// GLWind.cpp : implementation file
//

#include "stdafx.h"
#include "GLTest.h"
#include "GLWind.h"
#include "..\gl10\gl10c3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLWind


char FichCant;
struct coord* Fichas;


CGLWind::CGLWind()
{
	ang=0;
	CurX=0;
	CurY=0;
	CurZ=0;
	lastx=0;lasty=0;lastz=0;
	memset(m_Ang,0,sizeof(m_Ang));
	OnRDown=false;
	OnLDown=false;
	OnCoord=false;
	LineStipple=0;
	OnEraseBackground=true;
	Fichas=NULL;
}

CGLWind::~CGLWind()
{
	ClearAllPoints();
	if (Fichas)
		delete Fichas;
}


BEGIN_MESSAGE_MAP(CGLWind, CMemDCView)
	//{{AFX_MSG_MAP(CGLWind)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGLWind message handlers



void CGLWind::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate(false);		
}

void CGLWind::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ((!OnRDown) && (!OnLDown))
		return;
	point-=pt;
	if (OnRDown)
		CurZ=lastz-(float)point.y/MZ;
		//CurZ=MESA_DZ-((float)(MESA_MINZ)+(float)(MESA_DZ)*point.y/rect.Height());
	if (OnLDown)
	{
		CurX=lastx+(float)point.x/MX;
		CurY=lasty-(float)point.y/MY;
		/*
		CurX=(float)(MESA_MINX)+(float)(MESA_DX)*point.x/rect.Width();
		CurY=(float)(MESA_MINY)+(float)(MESA_DY)*point.y/rect.Height();
		*/
	}

	// Acotamiento de la posicion de la ficha
	if (CurX > MESA_MINX+MESA_DX)
		CurX=MESA_MINX+MESA_DX;
	if (CurY > MESA_MINX+MESA_DY)
		CurY=MESA_MINY+MESA_DY;
	if (CurZ > MESA_MINZ+MESA_DZ)
		CurZ=MESA_MINZ+MESA_DZ;
	if (CurX  < MESA_MINX)
		CurX=MESA_MINX;
	if (CurY  < MESA_MINY)
		CurY=MESA_MINY;
	if (CurZ  < MESA_MINZ)
		CurZ=MESA_MINZ;
	CalcAng();
}

int CGLWind::RenderDC(CDC *dc)
{
	/*
	 Esto es usado para crear un efecto ormiga en las lineas
	*/
	if (LineStipple & 1)
	{
		LineStipple=LineStipple << 1;
	}
	else
	{
		LineStipple=LineStipple << 1;
		LineStipple|=1;
	}
	glLineStipple(4,LineStipple);
	// Fin del efecto

	// Inicializacion
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	if (OnEraseBackground)
	{
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	}
	else
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	glFinish();
		
	char coord[100];
	sprintf(coord,"X:%d Y:%d Z:%d",(int)CurX,(int)CurY,(int)CurZ);
	dc->TextOut(20,20,coord);
	/*
	sprintf(coord,"B:%d H:%d C:%d",(int)m_Ang[0],(int)m_Ang[1],(int)m_Ang[2]);
	dc->TextOut(20,40,coord);
	*/
	
	ang+=5;
	if (ang> 360) 
		ang=0;

	//gluLookAt(100*cos(ang*3.14/180),50,100*sin(ang*3.14/180),0,0,0,0,1,0);
	//gluLookAt(6,43,56,6,3,0,0,1,0);
	gluLookAt(6,43,100,6,3,0,0,1,0);
		
	glRotated(-90,1,0,0);
	int factor=10;

	
	glDisable(GL_LINE_STIPPLE);

	/*
		Aqui se dibuja la trayectoria a seguir
	*/
	glColor3ub(255,255,0);
	glBegin(GL_LINE_STRIP);
	  if (!Points.IsEmpty()) 
	  {
		  POSITION		pPos;
		  S_3DSPOINT*	point;
		  pPos=Points.GetHeadPosition();
		  do
		  {
			  point=(S_3DSPOINT*)Points.GetAt(pPos);
			  glVertex3f(point->x,point->y,point->z);
			  Points.GetNext(pPos);
		  } while (pPos != NULL);
	  }
	glEnd();
	// Fin de la trayectoria
	
	glColor3ub(255,255,255);
	glBegin(GL_LINES);
	  glColor3ub(255,0,0);
	  glVertex3d(0,0,0);
	  glVertex3d(factor,0,0);

	  glColor3ub(0,0,255);
	  glVertex3d(0,0,0);
	  glVertex3d(0,factor,0);

	  glColor3ub(0,255,0);
	  glVertex3d(0,0,0);
	  glVertex3d(0,0,factor);
	  // X
	  glColor3ub(255,0,0);
	  glVertex3d(1.1*factor,0.1*factor,0);
	  glVertex3d(1.3*factor,-0.1*factor,0);
	  glVertex3d(1.1*factor,-0.1*factor,0);
	  glVertex3d(1.3*factor,0.1*factor,0);
	  // Y
	  glColor3ub(0,0,255);
	  glVertex3d(-0.1*factor,1.1*factor,0);
	  glVertex3d(0.1*factor,1.3*factor,0);
	  glVertex3d(-0.1*factor,1.3*factor,0);
	  glVertex3d(0.0,1.2*factor,0);
	  // Z
	  glColor3ub(0,255,0);
	  glVertex3d(0,0.1*factor,1.3*factor);
	  glVertex3d(0,0.1*factor,1.1*factor);
	  glVertex3d(0,0.1*factor,1.1*factor);
	  glVertex3d(0,-0.1*factor,1.3*factor);
	  glVertex3d(0,-0.1*factor,1.3*factor);
	  glVertex3d(0,-0.1*factor,1.1*factor);
	glEnd();
	
	glPushMatrix();

	 glColor3ub(255,0,0);

	 //glEnable(GL_LINE_STIPPLE);
	 m_Escena.Paint();
	 glTranslated(CurX-20,CurY,CurZ);
	 CMeshMat* pMesh;
	 pMesh=m_Escena.GetMesh("Ficha");
	 if (pMesh)
		 pMesh->Paint();

	glPopMatrix();

	glDisable(GL_LINE_STIPPLE);
	glColor3ub(0,0,255);
	if (pMesh && OnCoord)
	{
		for (int i=0;i<FichCant;i++)
		{
			glPushMatrix();
			glTranslated(Fichas[i].x-20,-Fichas[i].y,0);
			pMesh->Paint();
			glPopMatrix();
			
		}

	}
	glFlush();
	glPopMatrix();
	return true;
}

BOOL CGLWind::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	//SetCursor(NULL);
	return true;
}

void CGLWind::OnLButtonDown(UINT nFlags, CPoint point) 
{
	OnLDown=true;
	OnRDown=false;
	CMemDCView::OnLButtonDown(nFlags, point);
	SetCapture();
	pt=point;
}

void CGLWind::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OnRDown=true;
	OnLDown=false;	
	CMemDCView::OnRButtonDown(nFlags, point);
	SetCapture();
	pt=point;
}

void CGLWind::OnLButtonUp(UINT nFlags, CPoint point) 
{
	MouseUp();
}

void CGLWind::OnRButtonUp(UINT nFlags, CPoint point) 
{
	MouseUp();
}

int CGLWind::MouseUp()
{
	lastx=CurX;
	lasty=CurY;
	lastz=CurZ;
	ReleaseCapture();
	OnLDown=false;	
	OnRDown=false;	
	double dbase=m_LastAng[0]-m_Ang[0];
	double dhombro=m_LastAng[1]-m_Ang[1];
	double dcodo=m_LastAng[2]-m_Ang[2];
	int    Tbase   = (int)dbase*196/180;
	int	   Thombro = (int)dhombro*138/90;
	int    Tcodo   = (int)dcodo*145/90;
	memcpy(m_LastAng,m_Ang,sizeof(m_Ang));

	CRect rect;
	GetClientRect(rect);
	ClientToScreen(rect);
	SetCursorPos((rect.left+rect.right)/2,(rect.top+rect.bottom)/2);
	SetFocus();
	return true;
}

int CGLWind::OpenFile(char *file)
{
	FILE*	pfile;
	pfile=fopen(file,"rb");
	m_Escena.ReadFromFile(pfile);
	return true;
}

CEscena* CGLWind::GetEscena()
{
	return &m_Escena;
}

int CGLWind::ReadCoord()
{
	OnCoord=true;
	return true;
}

int CGLWind::GetFichas(coord *fich, char cant)
{
	if (Fichas)
		delete Fichas;
	Fichas= new coord[cant];
	memcpy(Fichas,fich,sizeof(coord)*cant);
	FichCant=cant;
	OnCoord=true;
	return true;
}

// Cuando el Robot no puede alcanzar la Ficha
int CGLWind::OnInvalidPoint()
{
	CurX=lastcx;
	CurY=lastcy;
	CurZ=lastcz;
	return true;
}

int CGLWind::NewPoint()
{
	S_3DSPOINT* point= new S_3DSPOINT;
	point->x=lastcx;
	point->y=lastcy;
	point->z=lastcz;
	Points.AddTail(point);
	return true;
}

BOOL CGLWind::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case ' ':
			{
				NewPoint();
				return true;
			}
		case VK_DELETE:
			{
				DeleteLastPoint();
				return true;
			}
		case 13:
			{
				if (Points.IsEmpty())
					return true;
				// Enviar las coordenadas del robot al servidor
				POSITION		pPos;
				S_3DSPOINT*		point;
				pPos=Points.GetHeadPosition();
				do
				{
					point=(S_3DSPOINT*)Points.GetAt(pPos);
					Points.GetNext(pPos);
					
					// calcular angulos de dicho punto
					CurX=point->x;
					CurY=point->y;
					CurZ=point->z;
					CalcAng();
					// calcular la diferencia de angulo
					RobDAng[0]=m_Ang[0]-RobLastAng[0];
					RobDAng[1]=m_Ang[1]-RobLastAng[1];
					RobDAng[2]=m_Ang[2]-RobLastAng[2];
					// Angulos del Robot en tablas
					int    Tbase   = (int)RobDAng[0]*196/180;
					int	   Thombro = (int)RobDAng[1]*138/90;
					
					int    Tcodo   = (int)(RobDAng[1]-180+RobDAng[2])*145/90;
					// Crear la cadena de envio
					char	cadena[100];
					sprintf(cadena,"move %d %d %d 0 \n",Tbase,Thombro,Tcodo);
					// Actualizar la posicion del robot
					RobLastAng[0]=m_Ang[0];
					RobLastAng[1]=m_Ang[1];
					RobLastAng[2]=m_Ang[2];
				} while (pPos != NULL);
			}
		}
	}
	return CMemDCView::PreTranslateMessage(pMsg);
}

int CGLWind::ClearAllPoints()
{
	if (!Points.IsEmpty()) 
	{
		POSITION		pPos;
		pPos=Points.GetHeadPosition();
		do
		{
			delete Points.GetAt(pPos);
			Points.GetNext(pPos);
		} while (pPos != NULL);
		Points.RemoveAll();
	}
	return true;
}

int CGLWind::EraseBackground(BOOL state)
{
	OnEraseBackground=state;
	return true;
}

int CGLWind::DeleteLastPoint()
{
	S_3DSPOINT*	point;
	if (Points.IsEmpty())
		return true;
	point=(S_3DSPOINT*)Points.GetTail();
	delete point;
	Points.RemoveTail();

	if (Points.IsEmpty())
		return true;

	point=(S_3DSPOINT*)Points.GetTail();
	CurX=point->x;
	CurY=point->y;
	CurZ=point->z;

	lastx=CurX;
	lasty=CurY;
	lastz=CurZ;

	CalcAng();

	return true;
}

int CGLWind::CalcAng()
{
	double m_x,m_y,m_z;
	m_x=CurX;
	m_y=CurY;
	m_z=CurZ+10;

	// Largo de las articulaciones
	double a=19;
	double b=19;
	double c=0;
	// Transladar el eje al centro de giro de la base
	m_x-=8.5f;
	m_y-=5.0f;
	m_z-=13.0f;
	// Girando la Base
	// la y esta invertida si es negativa, los angulos son positivos
	m_Ang[0]=atan2(m_x,-m_y);   // Angulo de la base
	// Recalcular coordenadas
	m_y=sqrt(m_y*m_y+m_x*m_x);
	m_x=0;
	m_y-=1.0f;
	if (m_y < 0) // El objeto esta inlocalizable
	{
		OnInvalidPoint();
		return false;
	}	
	// porque se quedo atras cuando debia estar alante de la base

	// Subir al centro de giro del codo y el hombro
	m_z-=11.0;

	// Calculo de los angulos del Hombro y el Codo
	double alfa,betha,betha1;

	c=sqrt(m_y*m_y+m_z*m_z);

	if (c > a+b)      // El Robot no alcanza
	{
		OnInvalidPoint();
		return false;
	}

	alfa=acos((b*b+a*a-c*c)/(2*a*b));     //angulo del codo respecto al hombro
	betha=acos((c*c+a*a-b*b)/(2*c*a));	// Angulo del hombro respecto a 
	betha1=atan2(m_z,m_y);				// suma de estos dos
			
	// Calculo final de los angulos respecto al eje Z
	m_Ang[1]=betha+betha1;
	m_Ang[2]=alfa;
	

	// almacenando la ultima posicion valida
	lastcx=CurX;
	lastcy=CurY;
	lastcz=CurZ;
	// Conversion a grados
	double m=180/acos(-1);
	int i;
	for (i=0;i<3;m_Ang[i]*=m,i++);

	m_Escena.SetVarValue("Ang_Base",(float)(m_Ang[0]+180));
	m_Escena.SetVarValue("Ang_Hombro",(float)((-m_Ang[1])+180));
	m_Escena.SetVarValue("Ang_Codo",(float)((180-m_Ang[2])+90));
	m_Escena.SetVarValue("Ang_Pinza",(float)((-180+m_Ang[2]+m_Ang[1])+180));


	return true;
}

BOOL CGLWind::IsMoving()
{
	return (OnRDown||OnLDown);
}
