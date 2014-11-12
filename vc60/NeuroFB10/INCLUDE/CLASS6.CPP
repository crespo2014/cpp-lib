// class6.cpp: implementation of the CGLCilinder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "class6.h"
#include "class2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLCilinder::CGLCilinder()
{
	m_GLCilinder=new S_GLCilinder;
	Init();
}

CGLCilinder::~CGLCilinder()
{
	delete m_GLCilinder;
}

int CGLCilinder::VPaint()
{
	// si ya es una primitiva entonces fue pintada 
	if (IsPrimitive())
		return true;

	if ((m_GLCilinder->m_Disk.radio<=0)|(m_GLCilinder->m_Disk.altura<=0))
		return false;

	double grad;
	double dx,dz;
	BOOL   Exit=false;

	glBegin(GL_TRIANGLE_STRIP);

	for(grad=m_GLCilinder->m_Disk.begin_ang;;grad+=m_GLCilinder->m_Disk.resolucion)
	{
		if (grad > m_GLCilinder->m_Disk.end_ang)
		{
			grad =m_GLCilinder->m_Disk.end_ang;
			if (grad >= 2*acos(-1)) grad=0;
			Exit=true;
		}
		dx=m_GLCilinder->m_Disk.radio*sin(grad);
		dz=m_GLCilinder->m_Disk.radio*cos(grad);

		glNormal3d(dx/m_GLCilinder->m_Disk.radio,0.0,dz/m_GLCilinder->m_Disk.radio); 
		glVertex3d(dx,m_GLCilinder->m_Disk.altura,dz);
		glVertex3d(dx,0.0,dz);

		if (Exit) 
			break;
	}
	glEnd();
	// cara superior del cilindro 
	if (m_GLCilinder->m_Disk.Tapa1)
	{
		
		glBegin(GL_TRIANGLE_FAN);
		glVertex3d(0,m_GLCilinder->m_Disk.altura,0);
		glNormal3d(0,1,0);
		
		for(grad=m_GLCilinder->m_Disk.begin_ang,Exit=false;;grad+=m_GLCilinder->m_Disk.resolucion)
		{
			if (grad > m_GLCilinder->m_Disk.end_ang)
			{
				grad =m_GLCilinder->m_Disk.end_ang;
				if (grad >= 2*acos(-1)) grad=0;
				Exit=true;
			}
			
			dx=m_GLCilinder->m_Disk.radio*sin(grad);
			dz=m_GLCilinder->m_Disk.radio*cos(grad);
			
			glVertex3d(dx,m_GLCilinder->m_Disk.altura,dz);
			
			if (Exit) 
				break;
		}
		glEnd();
	}
	if (m_GLCilinder->m_Disk.Tapa0)
	{
		glBegin(GL_TRIANGLE_FAN);
		glVertex3d(0,0,0);
		glNormal3d(0,-1,0);
		
		for(grad=m_GLCilinder->m_Disk.begin_ang,Exit=false;;grad+=m_GLCilinder->m_Disk.resolucion)
		{
			if (grad > m_GLCilinder->m_Disk.end_ang)
			{
				grad =m_GLCilinder->m_Disk.end_ang;
				if (grad >= 2*acos(-1)) grad=0;
				Exit=true;
			}
			dx=m_GLCilinder->m_Disk.radio*sin(grad);
			dz=m_GLCilinder->m_Disk.radio*cos(grad);
			
			glVertex3d(dx,0.0,dz);
			
			if (Exit) 
				break;
		}
		
		glEnd();
	}
	
	return true;
}

int CGLCilinder::EnabledFaces(DWORD pFaces)
{
	m_GLCilinder->m_Disk.Tapa0=(BOOL)((pFaces & 1)!=0);
	m_GLCilinder->m_Disk.Tapa1=(BOOL)((pFaces & 2)!=0);
	return true;
}

int CGLCilinder::Set(double pradio, double paltura)
{
	m_GLCilinder->m_Disk.radio=pradio;
	m_GLCilinder->m_Disk.altura=paltura;
	return true;
}

int CGLCilinder::SetAng(double pBegin, double pEnd)
{
	m_GLCilinder->m_Disk.begin_ang=pBegin;
	m_GLCilinder->m_Disk.end_ang=pEnd;
	return true;
}

int CGLCilinder::SaveDataToFile(FILE *pFile)
{
	if (IsPrimitive())
		return false;
	fprintf(pFile,"[Library]\n[Cilinder]\n");
	fprintf(pFile,"[End]\n");
	return true;
}

int CGLCilinder::VConfigure()
{
	CDlgCilinder Dlg;
	Dlg.m_pAltura=m_GLCilinder->m_Disk.altura;
	Dlg.m_pRadio=m_GLCilinder->m_Disk.radio;
	Dlg.m_pTapa0=m_GLCilinder->m_Disk.Tapa0;
	Dlg.m_pTapa1=m_GLCilinder->m_Disk.Tapa1;
	Dlg.m_pInicial=m_GLCilinder->m_Disk.begin_ang*180/3.14;
	Dlg.m_pFinal=m_GLCilinder->m_Disk.end_ang*180/3.14;
	if (Dlg.DoModal()== IDOK)
	{
		m_GLCilinder->m_Disk.altura=Dlg.m_pAltura;
		m_GLCilinder->m_Disk.radio=Dlg.m_pRadio;
		m_GLCilinder->m_Disk.Tapa0=Dlg.m_pTapa0;
		m_GLCilinder->m_Disk.Tapa1=Dlg.m_pTapa1;
		m_GLCilinder->m_Disk.begin_ang=Dlg.m_pInicial*3.14/180;
		m_GLCilinder->m_Disk.end_ang=Dlg.m_pFinal*3.14/180;
		return true;
	};
	return false;

}

int CGLCilinder::VGeneratePrimitive()
{
	// Si este objeto es asociado entonces genero las primitivas  se
	// borra de la lista
	// pero si hay dependencias en las variables tan solo pierdo la condicion
	// de ser libreria y cuando me salvo no salvo nada
	double grad;
	double dx,dz;
	UINT Cant;
	UINT Pos;
	BOOL Continue;

	// conteo de la cantidad de vertices
	Continue=true;
	grad=m_GLCilinder->m_Disk.begin_ang;
	Cant=1;
	do
	{
		grad+=m_GLCilinder->m_Disk.resolucion;
		if (grad >= m_GLCilinder->m_Disk.end_ang)
		{
			Continue=false;
			grad=m_GLCilinder->m_Disk.end_ang;
		}
		Cant++;		
	} while (Continue);

	CGLPrimitiva* pNew=new CGLPrimitiva();
	point3ds*	pVertex=new point3ds[Cant*2];
	S_Normal*	pNormal=new S_Normal[Cant*2];

	pNew->SetPrimitiva(GL_TRIANGLE_STRIP);
	Continue=true;
	grad=m_GLCilinder->m_Disk.begin_ang;
	Pos=0;
	do
	{
		dx=m_GLCilinder->m_Disk.radio*sin(grad);
		dz=m_GLCilinder->m_Disk.radio*cos(grad);
		pVertex[Pos*2].x=dx;
		pVertex[Pos*2].y=0;
		pVertex[Pos*2].z=dz;
		pVertex[Pos*2+1].x=dx;
		pVertex[Pos*2+1].y=m_GLCilinder->m_Disk.altura;
		pVertex[Pos*2+1].z=dz;
		pNormal[Pos*2].x=dx/m_GLCilinder->m_Disk.radio;
		pNormal[Pos*2].y=0;
		pNormal[Pos*2].z=dz/m_GLCilinder->m_Disk.radio;
		pNormal[Pos*2+1].x=dx/m_GLCilinder->m_Disk.radio;
		pNormal[Pos*2+1].y=0;
		pNormal[Pos*2+1].z=dz/m_GLCilinder->m_Disk.radio;
		grad+=m_GLCilinder->m_Disk.resolucion;
		if (grad >= m_GLCilinder->m_Disk.end_ang)
		{
			grad=m_GLCilinder->m_Disk.end_ang;
		}
		Pos++;		
	} while (Pos<Cant);
	pNew->SetCantVert(Cant*2);
	pNew->SetNormal(pNormal);
	pNew->SetVertex(pVertex);
	AddPrimitive(pNew);

	pNew=new CGLPrimitiva();
	pNew->SetPrimitiva(GL_TRIANGLE_FAN);
	pNew->SetNormal(0,1,0);
	pVertex[0].x=0;
	pVertex[0].y=m_GLCilinder->m_Disk.altura;
	pVertex[0].z=0;

	Pos=1;
	grad=m_GLCilinder->m_Disk.begin_ang;
	do
	{
		dx=m_GLCilinder->m_Disk.radio*sin(grad);
		dz=m_GLCilinder->m_Disk.radio*cos(grad);
		pVertex[Pos].x=dx;
		pVertex[Pos].y=m_GLCilinder->m_Disk.altura;
		pVertex[Pos].z=dz;
		grad+=m_GLCilinder->m_Disk.resolucion;
		if (grad >= m_GLCilinder->m_Disk.end_ang)
		{
			grad=m_GLCilinder->m_Disk.end_ang;
		}
		Pos++;
	} while (Pos-1 < Cant);
	pNew->SetCantVert(Cant+1);
	pNew->SetVertex(pVertex);
	AddPrimitive(pNew);

	pNew=new CGLPrimitiva();
	pNew->SetPrimitiva(GL_TRIANGLE_FAN);
	pNew->SetNormal(0,-1,0);
	pVertex[0].x=0;
	pVertex[0].y=0;
	pVertex[0].z=0;

	Pos=1;
	grad=m_GLCilinder->m_Disk.begin_ang;
	do
	{
		dx=m_GLCilinder->m_Disk.radio*sin(grad);
		dz=m_GLCilinder->m_Disk.radio*cos(grad);
		pVertex[Pos].x=dx;
		pVertex[Pos].y=0;
		pVertex[Pos].z=dz;
		grad+=m_GLCilinder->m_Disk.resolucion;
		if (grad >= m_GLCilinder->m_Disk.end_ang)
		{
			grad=m_GLCilinder->m_Disk.end_ang;
		}
		Pos++;
	} while (Pos-1 < Cant);
	pNew->SetCantVert(Cant+1);
	pNew->SetVertex(pVertex);
	AddPrimitive(pNew);
	delete pVertex;
	delete pNormal;
	return true;
}

int CGLCilinder::VSaveData(FILE *pFile)
{
	fwrite(&m_GLCilinder->m_Disk,sizeof(S_CILINDERINFO),1,pFile);
	return true;
}

int CGLCilinder::VReadData(FILE *pFile)
{
	fread(&m_GLCilinder->m_Disk,sizeof(S_CILINDERINFO),1,pFile);
	return true;
}

int CGLCilinder::Init()
{
	m_GLCilinder->m_Disk.Tapa0=true;
	m_GLCilinder->m_Disk.Tapa1=true;
	m_GLCilinder->m_Disk.radio=0.5;
	m_GLCilinder->m_Disk.altura=0.5;
	m_GLCilinder->m_Disk.begin_ang=0;
	m_GLCilinder->m_Disk.end_ang=2*acos(-1)/2;
	m_GLCilinder->m_Disk.resolucion=m_GLCilinder->m_Disk.end_ang/36;
	SetName("Cilindro");
	m_3DObject->m_Header.m_Type=TYPE_CILINDER;
	return true;
}
