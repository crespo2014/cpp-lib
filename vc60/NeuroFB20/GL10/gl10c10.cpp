 // gl10c10.cpp: implementation of the CVariableInstance class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gl10c10.h"
#include "gl10c9.h"
#include "gl10d6.h"
#include "gl10c4.h"
#include "gl10c5.h"
#include "gl10c7.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVariableInstance::CVariableInstance()
{
	InitVariableInstance();
}

CVariableInstance::~CVariableInstance()
{
	delete m_VariableInstance;
}

int CVariableInstance::InitVariableInstance()
{
	m_VariableInstance=new S_VARIABLEINSTANCE;
	m_VariableInstance->info.version=sizeof(S_VARIABLEINSTANCEINFO);
	m_VariableInstance->info.factor=1;
	m_VariableInstance->info.varindex=0;
	m_VariableInstance->htree=0;
	m_VariableInstance->parent=NULL;
	m_VariableInstance->pos=NULL;
	m_VariableInstance->var=NULL;
	m_VariableInstance->info.factor=1.0f;
	m_VariableInstance->info.change=MOD_POS;
	m_VariableInstance->info.minimo=0;
	memset(m_VariableInstance->info.posfac,0,3*sizeof(float));
	memset(m_VariableInstance->info.rotpto,0,3*sizeof(float));
	memset(m_VariableInstance->info.rotvect,0,3*sizeof(float));
	m_VariableInstance->treelparam.object=this;
	m_VariableInstance->treelparam.type=ID_VARIABLEINSTANCE;
	return true;
}

CVariableInstance::CVariableInstance(CVariable *pvar)
{
	InitVariableInstance();
	SetVar(pvar);
}

int CVariableInstance::SetVar(CVariable *pvar)
{
	m_VariableInstance->var=pvar;
	m_VariableInstance->info.varindex=pvar->GetIndex();
	return true;
}

WORD CVariableInstance::GetModifier()
{
	return m_VariableInstance->info.change;
}

int CVariableInstance::SetModifier(WORD change)
{
	m_VariableInstance->info.change=change;
	return true;
}


int CVariableInstance::ApplyModifier()
{
	float value=m_VariableInstance->var->GetValue();
	value*=m_VariableInstance->info.factor;
	value+=m_VariableInstance->info.minimo;
	if (m_VariableInstance->info.change== MOD_POS)
	{
		glTranslatef(value*m_VariableInstance->info.posfac[0],
			value*m_VariableInstance->info.posfac[1],
			value*m_VariableInstance->info.posfac[2]);
	}
	else
	{
		glTranslatef(m_VariableInstance->info.rotpto[0],
			m_VariableInstance->info.rotpto[1],
			m_VariableInstance->info.rotpto[2]);
		glRotatef(value,m_VariableInstance->info.rotvect[0],
			m_VariableInstance->info.rotvect[1],
			m_VariableInstance->info.rotvect[2]);
		glTranslatef(-m_VariableInstance->info.rotpto[0],
			-m_VariableInstance->info.rotpto[1],
			-m_VariableInstance->info.rotpto[2]);

	}
	return true;
}

float CVariableInstance::GetFactor()
{
	return m_VariableInstance->info.factor;
}

float CVariableInstance::GetMin()
{
	return m_VariableInstance->info.minimo;
}

int CVariableInstance::GetRotationVector(float *vector)
{
	memcpy(vector,m_VariableInstance->info.rotvect,3*sizeof(float));
	return true;
}

int CVariableInstance::SetRotationVector(float *vector)
{
	memcpy(m_VariableInstance->info.rotvect,vector,3*sizeof(float));
	return true;	
}

int CVariableInstance::Propiedades()
{
	CVariableInstanceDlg Dlg;
	Dlg.m_Object=this;
	return Dlg.DoModal();

}

int CVariableInstance::GetRotationPoint(float *rotpto)
{
	memcpy(rotpto,m_VariableInstance->info.rotpto,3*sizeof(float));
	return true;	
}

int CVariableInstance::SetRotationPoint(float *rotpto)
{
	memcpy(m_VariableInstance->info.rotpto,rotpto,3*sizeof(float));
	return true;
}

int CVariableInstance::GetPosition(float *pos)
{
	memcpy(pos,m_VariableInstance->info.posfac,3*sizeof(float));
	return true;	
}

int CVariableInstance::SetPosition(float *pos)
{
	memcpy(m_VariableInstance->info.posfac,pos,3*sizeof(float));
	return true;	
}

int CVariableInstance::SetPos(POSITION pos)
{
	m_VariableInstance->pos=pos;
	return true;
}

int CVariableInstance::DetachFromTree()
{
	if (m_VariableInstance->htree)
	{
		m_VariableInstance->tree->DeleteItem(m_VariableInstance->htree);
	}
	return true;
}

int CVariableInstance::SetParent(CMeshGroup *parent)
{
	m_VariableInstance->parent=parent;
	return true;
}

int CVariableInstance::Delete()
{
	return m_VariableInstance->parent->DeleteVariableInstance(m_VariableInstance->pos);
}

int CVariableInstance::SaveToFile(FILE *pFile)
{
	UpdateIndex();
	fwrite(&m_VariableInstance->info,sizeof(S_VARIABLEINSTANCEINFO),1,pFile);
	return true;
}

int CVariableInstance::UpdateIndex()
{
	m_VariableInstance->info.varindex=m_VariableInstance->var->GetIndex();
	return true;
}

int CVariableInstance::ReadFromFile(FILE *pFile)
{
	fread(&m_VariableInstance->info,sizeof(S_VARIABLEINSTANCEINFO),1,pFile);
	if (m_VariableInstance->info.version != sizeof(S_VARIABLEINSTANCEINFO))
		return false;
	m_VariableInstance->var=m_VariableInstance->parent->GetEscena()->GetVariable(m_VariableInstance->info.varindex);
	return true;
}

int CVariableInstance::SetTree(CEscenaTree *pTree)
{
	m_VariableInstance->tree=pTree;
	return true;
}

int CVariableInstance::AttachToTree()
{
	if (!m_VariableInstance->tree)
		return false;
	TV_INSERTSTRUCT tvi;
	tvi.hParent=m_VariableInstance->parent->GetTreeHandle();
	tvi.hInsertAfter=TVI_FIRST;
	tvi.itemex.mask=TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM ;
	tvi.itemex.hItem=NULL;
	tvi.itemex.state=0;
	tvi.itemex.stateMask=0;
	tvi.itemex.cchTextMax=10;
	tvi.itemex.iSelectedImage=VARIABLE_ICON;
	tvi.itemex.cChildren=0;
	tvi.itemex.pszText=m_VariableInstance->var->GetName();
	tvi.itemex.iImage=VARIABLE_ICON;
	tvi.itemex.lParam=(DWORD)&m_VariableInstance->treelparam;
	m_VariableInstance->htree=m_VariableInstance->tree->InsertItem(&tvi);	
	return true;
}

int CVariableInstance::SetMin(float min)
{
	m_VariableInstance->info.minimo=min;
	return true;
}
