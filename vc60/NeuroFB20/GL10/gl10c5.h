 // gl10c5.h: interface for the CEscena class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GL10C5_H__039B87A0_F27B_11D3_A037_0000E83D722B__INCLUDED_)
#define AFX_GL10C5_H__039B87A0_F27B_11D3_A037_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gl10c4.h"
#include "..\g_01\g_01c07.h"

/*
typedef struct
{
	DWORD	version;
	WORD	nmaterials;
	WORD	nmeshes;
	WORD	nvariables;
} S_ESCENAINFO;
*/

typedef struct
{
	S_3DESCENE		info;
	S_TREELPARAM	treelparam;
	CMeshGroup		meshgroup;   // este es el grupo principal
	CObList			materials;
	CObList			meshes;
	CObList			vars;
	CEscenaTree*	tree;
	HTREEITEM		htree;
	HTREEITEM		hmaterialfolder;
	HTREEITEM		hmeshfolder;
	HTREEITEM		hvarfolder;
	BOOL			wireframe;
} S_ESCENA;

class AFX_EXT_CLASS CEscena : public CObject  
{
public:
	CMeshMat* GetMesh(char* name);
	int SetVarValue(char* name,float value);
	CVariable* GetVariable(char* name);
	int SetWireFrame(BOOL state);
	BOOL IsWireFrame();
	CVariable* GetVariable(DWORD pIndex);
	int Read();
	int ReadFromFile(FILE* pFile);
	int Save();
	int UpdateIndex();
	int SaveToFile(FILE* pFile);
	int NewVar();
	int DeleteAllVariables();
	HTREEITEM GetVarTreeHandle();
	int AddVar(CVariable* pvar);
	HTREEITEM GetTreeHandle();
	CMeshMat* GetMesh(POSITION pPos);
	CMeshMat* GetMesh(DWORD index);
	LPARAM GetTreeLParam();
	int UpDateTree();
	int AttachTree(CEscenaTree* pTree);
	CMaterial* GetMaterial(char* pname);
	int Paint();
	int AddMesh(CMeshMat* pMesh);
	int AddMaterial(CMaterial* pMaterial);
	int Read3DS();
	CMaterial* GetMaterial(POSITION pPos);
	CMaterial* GetMaterial(DWORD pIndex);
	int DeleteAllMeshes();
	int DeleteAllMaterials();
	int InitEscena();
	S_ESCENA* m_Escena;
	CEscena();
	virtual ~CEscena();

};

#endif // !defined(AFX_GL10C5_H__039B87A0_F27B_11D3_A037_0000E83D722B__INCLUDED_)



// calculo de los angulos del robot ARM010
/*
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
*/