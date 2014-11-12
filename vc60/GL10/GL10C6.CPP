// gl10c6.cpp: implementation of the CMaterial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gl10c6.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMaterial::CMaterial()
{
	InitMaterial();
}

CMaterial::~CMaterial()
{
	delete m_Material;
}

int CMaterial::InitMaterial()
{
	m_Material=new S_MATERIAL;
	m_Material->info.m_index=0;
	m_Material->info.m_name[20]=0;
	m_Material->info.m_size=sizeof(S_3DMATERIAL);
	m_Material->htree=NULL;
	m_Material->treelparam.type=ID_MATERIAL;
	m_Material->treelparam.object=this;
	return true;
}

DWORD CMaterial::GetIndex()
{
	return m_Material->info.m_index;
}

CMaterial::CMaterial(material3ds *pmaterial)
{
	InitMaterial();
	m_Material->info.m_ambient.b=pmaterial->ambient.b;
	m_Material->info.m_ambient.r=pmaterial->ambient.r;
	m_Material->info.m_ambient.g=pmaterial->ambient.g;
	m_Material->info.m_diffuse.b=pmaterial->diffuse.b;
	m_Material->info.m_diffuse.r=pmaterial->diffuse.r;
	m_Material->info.m_diffuse.g=pmaterial->diffuse.g;
	m_Material->info.m_specular.b=pmaterial->specular.b;
	m_Material->info.m_specular.r=pmaterial->specular.r;
	m_Material->info.m_specular.g=pmaterial->specular.g;
	memcpy(m_Material->info.m_name,pmaterial->name,17);	
	m_Material->info.m_shininess=pmaterial->shininess;
	m_Material->info.m_twosides=pmaterial->twosided;
}

int CMaterial::MakeCurrent()
{
	float color[4];
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,m_Material->info.m_shininess);
	color[3]=1.0;
	memcpy(color,&m_Material->info.m_ambient,sizeof(float)*3);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,color);
	memcpy(color,&m_Material->info.m_diffuse,sizeof(float)*3);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,color);
	memcpy(color,&m_Material->info.m_specular,sizeof(float)*3);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
	memset(color,0,sizeof(float)*3);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,color);

	if (m_Material->info.m_twosides)
	{
		glDisable(GL_CULL_FACE);
	}
	else
	{
		glEnable(GL_CULL_FACE);
	}
	return true;
}

char* CMaterial::GetName()
{
	return m_Material->info.m_name;
}

int CMaterial::SetPos(POSITION pPos)
{
	m_Material->pos=pPos;
	return true;	
}

POSITION CMaterial::GetPos()
{
	return m_Material->pos;
}

int CMaterial::SetTreeHandle(HTREEITEM pHandle)
{
	m_Material->htree=pHandle;
	return true;
}

LPARAM CMaterial::GetTreeLParam()
{
	return (DWORD)&m_Material->treelparam;
}

int CMaterial::SetName(char *name)
{
	memcpy(m_Material->info.m_name,name,20);
	return true;
}

int CMaterial::SetIndex(DWORD pIndex)
{
	m_Material->info.m_index=pIndex;
	return true;
}

int CMaterial::SaveToFile(FILE *pFile)
{
	fwrite(&m_Material->info,sizeof(S_3DMATERIAL),1,pFile);
	return true;

}

int CMaterial::ReadFromFile(FILE *pFile)
{
	fread(&m_Material->info.m_size,sizeof(S_3DMATERIAL),1,pFile);
	if (m_Material->info.m_size !=sizeof(S_3DMATERIAL))
		return false;
	return true;
}
