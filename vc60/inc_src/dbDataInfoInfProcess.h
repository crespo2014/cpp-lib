// dbDataInfoInfProcess.h: interface for the CdbDataInfoInfProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBDATAINFOINFPROCESS_H__83C1A6CF_084A_4040_B781_5ADF5F314562__INCLUDED_)
#define AFX_DBDATAINFOINFPROCESS_H__83C1A6CF_084A_4040_B781_5ADF5F314562__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Common.h"
#include "DBCommon.h"

class CdbDataInfoInfProcess : public IinfProcess 
{
	// IinfProcess
	virtual DWORD _stdcall OnStart();
	virtual DWORD _stdcall OnNewSection(char* name);	
	virtual DWORD _stdcall OnNewValue(char* name,char* value);
	virtual DWORD _stdcall OnFinish();
	DBTABLEINFO* m_dbTableInfo;
	WORD	m_Status;
	WORD	m_InfStatus;	// Indica de quien se reciven los datos
	WORD	m_InfExtra;		// Estatus extra
public:
	DWORD ProcessResource(char* lpzsResourceName);
	DWORD SetdbTableInfo(DBTABLEINFO* lpdbTableInfo);
	CdbDataInfoInfProcess();
	virtual ~CdbDataInfoInfProcess();

};

#endif // !defined(AFX_DBDATAINFOINFPROCESS_H__83C1A6CF_084A_4040_B781_5ADF5F314562__INCLUDED_)
