// dbDataInfoInfProcess.cpp: implementation of the CdbDataInfoInfProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dbDataInfoInfProcess.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Inf Status
#define INFS_TABLE	1
#define INFS_DATA	2

CdbDataInfoInfProcess::CdbDataInfoInfProcess()
{

}

CdbDataInfoInfProcess::~CdbDataInfoInfProcess()
{

}

DWORD CdbDataInfoInfProcess::SetdbTableInfo(DBTABLEINFO* lpdbTableInfo)
{
	m_dbTableInfo = lpdbTableInfo;
	return ERR_NONE;
}

DWORD _stdcall CdbDataInfoInfProcess::OnStart()
{
	m_dbTableInfo->dataCount = 0;
	m_dbTableInfo->index = 0;
	m_dbTableInfo->name[0] = 0;
	return ERR_NONE;
}

DWORD _stdcall CdbDataInfoInfProcess::OnNewSection(char* name)
{
	if (strcmp(name,"Table")==0)	m_Status = INFS_TABLE;
	if (strcmp(name,"Data")==0) 
	{
		WORD index = m_dbTableInfo->dataCount;
		m_dbTableInfo->dataCount++;
		m_Status = INFS_DATA;
		ZeroMemory(&m_dbTableInfo->lpDataInfo[index],sizeof(DBDATAINFO));
	}
	return ERR_NONE;
}	

DWORD _stdcall CdbDataInfoInfProcess::OnNewValue(char* name,char* value)
{
	int	val;
	if (m_Status == INFS_TABLE)
	{
		if (strcmp(name,"name")==0) strcpy(m_dbTableInfo->name,value);
		sscanf(value,"%d",&val);
		if (strcmp(name,"index")==0) m_dbTableInfo->index = val;
	}
	if (m_Status == INFS_DATA)
	{
		WORD index = m_dbTableInfo->dataCount-1;
		if (strcmp(name,"caption")==0)		strcpy(m_dbTableInfo->lpDataInfo[index].caption,value);
		if (strcmp(name,"name")==0)			strcpy(m_dbTableInfo->lpDataInfo[index].name,value);
		GetIntValue(value,&val);
		if (strcmp(name,"index")==0)		m_dbTableInfo->lpDataInfo[index].dbIndex = MAKELONG(val,m_dbTableInfo->index);
		if (strcmp(name,"flags")==0)		m_dbTableInfo->lpDataInfo[index].flags = val;
		if (strcmp(name,"size")==0)			m_dbTableInfo->lpDataInfo[index].size = val;
		if (strcmp(name,"tableIndex")==0)	m_dbTableInfo->lpDataInfo[index].tableIndex = val;
		if (strcmp(name,"type")==0)			m_dbTableInfo->lpDataInfo[index].type = val;
	}
	return ERR_NONE;
}

DWORD _stdcall CdbDataInfoInfProcess::OnFinish()
{
	return ERR_NONE;
}

DWORD CdbDataInfoInfProcess::ProcessResource(char *lpzsResourceName)
{
	void* lpvoid;
	lpvoid = GetResource(lpzsResourceName);
	if (!lpvoid) return ERR_NORESOURCE;
	ProcessInfBuffer((char*)lpvoid,this);
	return ERR_NONE;
}
