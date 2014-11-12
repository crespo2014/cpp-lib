// dbGuiInfProcess.cpp: implementation of the CdbGuiInfProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dbGuiInfProcess.h"
#include "errorcodes.h"
#include "common.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define INFS_FONT 1
#define INFS_CTRL 2


CdbGuiInfProcess::CdbGuiInfProcess()
{

}

CdbGuiInfProcess::~CdbGuiInfProcess()
{

}

DWORD CdbGuiInfProcess::SetGui(DBGUI *lpGui)
{
	m_Gui = lpGui;
	return ERR_NONE;
}

DWORD _stdcall CdbGuiInfProcess::OnStart()
{
	m_Gui->hfont = NULL;
	m_Gui->ctrlCount = 0;
	ZeroMemory(&m_Gui->font,sizeof(m_Gui->font));
	return ERR_NONE;
}

DWORD _stdcall CdbGuiInfProcess::OnNewSection(char* name)
{
	if (strcmp(name,"Font")==0)	m_Status = INFS_FONT;
	if (strcmp(name,"Control")==0) 
	{
		m_Gui->ctrlCount++;
		m_Status = INFS_CTRL;
		WORD index = m_Gui->ctrlCount-1;
		ZeroMemory(&m_Gui->ctrls[index],sizeof(DBGUI_CTRL));
	}
	return ERR_NONE;
}	

DWORD _stdcall CdbGuiInfProcess::OnNewValue(char* name,char* value)
{
	int	val;
	if (m_Status == INFS_FONT)
	{
		if (strcmp(name,"lfFaceName")==0) strcpy(m_Gui->font.lfFaceName,value);
		sscanf(value,"%d",&val);
		if (strcmp(name,"lfHeight")==0)			m_Gui->font.lfHeight = val;
		if (strcmp(name,"lfWidth")==0)			m_Gui->font.lfWidth = val;
		if (strcmp(name,"lfWeight")==0)			m_Gui->font.lfWeight = val;
		if (strcmp(name,"lfOutPrecision")==0)	m_Gui->font.lfOutPrecision = val;
		if (strcmp(name,"lfClipPrecision")==0)	m_Gui->font.lfClipPrecision = val;
		if (strcmp(name,"lfQuality")==0)		m_Gui->font.lfQuality = val;
		if (strcmp(name,"lfPitchAndFamily")==0) m_Gui->font.lfPitchAndFamily = val;
		if (strcmp(name,"lfCharSet")==0)		m_Gui->font.lfCharSet = val;
		if (strcmp(name,"lfItalic")==0)			m_Gui->font.lfItalic = val;
	}
	if (m_Status == INFS_CTRL)
	{
		WORD index = m_Gui->ctrlCount-1;
		if (strcmp(name,"caption")==0) strcpy(m_Gui->ctrls[index].caption,value);
		GetIntValue(value,&val);
		if (strcmp(name,"x")==0)			m_Gui->ctrls[index].x = val;
		if (strcmp(name,"y")==0)			m_Gui->ctrls[index].y = val;
		if (strcmp(name,"width")==0)		m_Gui->ctrls[index].width = val;
		if (strcmp(name,"height")==0)		m_Gui->ctrls[index].height = val;
		if (strcmp(name,"style")==0)		m_Gui->ctrls[index].style = val;
		if (strcmp(name,"type")==0)			m_Gui->ctrls[index].type = val;
		if (strcmp(name,"exstyle")==0)		m_Gui->ctrls[index].exstyle = val;
		if (strcmp(name,"id")==0)			m_Gui->ctrls[index].id = val;
		if (strcmp(name,"parentid")==0)		m_Gui->ctrls[index].parentid = val;
		if (strcmp(name,"dbIndex")==0)		m_Gui->ctrls[index].dbIndex = val;
	}
	return ERR_NONE;
}

DWORD _stdcall CdbGuiInfProcess::OnFinish()
{
	return ERR_NONE;
}

DWORD CdbGuiInfProcess::ProcessResource(char *lpzsResourceName)
{
	void* lpvoid;
	lpvoid = GetResource(lpzsResourceName);
	if (!lpvoid) return ERR_NORESOURCE;
	ProcessInfBuffer((char*)lpvoid,this);
	return ERR_NONE;
}
