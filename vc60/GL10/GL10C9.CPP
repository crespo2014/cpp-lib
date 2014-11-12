 // gl10c9.cpp: implementation of the CVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gl10c9.h"
#include "gl10c5.h"
#include "gl10c7.h"
#include "gl10d5.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVariable::CVariable()
{
	InitVariable();
}

CVariable::~CVariable()
{
	delete m_Variable;
}

int CVariable::InitVariable()
{
	char	name[]="Variable";
	m_Variable=new S_VARIABLE;
	m_Variable->escena=NULL;
	m_Variable->htree=NULL;
	m_Variable->info.index=0;
	memcpy(m_Variable->info.name,name,sizeof(name));
	m_Variable->info.version=sizeof(S_VARIABLEINFO);
	m_Variable->info.max=100;
	m_Variable->pos=NULL;
	m_Variable->tree=NULL;
	m_Variable->info.value=0;
	m_Variable->treelparam.object=this;
	m_Variable->treelparam.type=ID_VARIABLE;
	return true;
}

float CVariable::GetValue()
{
	return m_Variable->info.value;
}

int CVariable::SetValue(float value)
{
	m_Variable->info.value=value;
	return true;
}

int CVariable::AttachToTree(CEscenaTree *pTree)
{
	m_Variable->tree=pTree;
	if (!pTree)
		return false;
	TV_INSERTSTRUCT tvi;
	tvi.hParent=m_Variable->escena->GetVarTreeHandle();
	tvi.hInsertAfter=TVI_FIRST;
	tvi.itemex.mask=TVIF_IMAGE|TVIF_TEXT|TVIF_SELECTEDIMAGE|TVIF_PARAM ;
	tvi.itemex.hItem=NULL;
	tvi.itemex.state=0;
	tvi.itemex.stateMask=0;
	tvi.itemex.cchTextMax=10;
	tvi.itemex.iSelectedImage=VARIABLE_ICON;
	tvi.itemex.cChildren=0;
	tvi.itemex.pszText=m_Variable->info.name;
	tvi.itemex.iImage=VARIABLE_ICON;
	tvi.itemex.lParam=(DWORD)&m_Variable->treelparam;
	m_Variable->htree=pTree->InsertItem(&tvi);
	return true;	
}

int CVariable::SetPos(POSITION pPos)
{
	m_Variable->pos=pPos;
	return true;
}

int CVariable::SetEscena(CEscena *pescena)
{
	m_Variable->escena=pescena;
	return true;
}

DWORD CVariable::GetIndex()
{
	return m_Variable->info.index;
}

int CVariable::Change()
{
	CVariableDlg	Dlg;
	Dlg.m_var=this;
	Dlg.DoModal();
	return true;
}

int CVariable::SetMaxValue(float max)
{
	m_Variable->info.max=max;
	return true;
}

float CVariable::GetMaxValue()
{
	return m_Variable->info.max;
}

char* CVariable::GetName()
{
	return m_Variable->info.name;
}

int CVariable::SetName(char *name)
{
	memcpy(m_Variable->info.name,name,20);
	return true;
}

int CVariable::SetIndex(DWORD pIndex)
{
	m_Variable->info.index=pIndex;
	return true;
}

int CVariable::SaveToFile(FILE *pFile)
{
	fwrite(&m_Variable->info,sizeof(S_VARIABLEINFO),1,pFile);
	return true;
}

int CVariable::ReadFromFile(FILE *pFile)
{
	fread(&m_Variable->info.version,sizeof(S_VARIABLEINFO),1,pFile);
	if (m_Variable->info.version != sizeof(S_VARIABLEINFO))
		return false;
	return true;
}
