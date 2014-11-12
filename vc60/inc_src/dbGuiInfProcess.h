// dbGuiInfProcess.h: interface for the CdbGuiInfProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBGUIINFPROCESS_H__AC645B79_3494_4A22_8E55_1B54788DF958__INCLUDED_)
#define AFX_DBGUIINFPROCESS_H__AC645B79_3494_4A22_8E55_1B54788DF958__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Common.h"
#include "DBCommon.h"

class CdbGuiInfProcess : public IinfProcess  
{
	// IinfProcess
	virtual DWORD _stdcall OnStart();
	virtual DWORD _stdcall OnNewSection(char* name);	
	virtual DWORD _stdcall OnNewValue(char* name,char* value);
	virtual DWORD _stdcall OnFinish();
	DBGUI* m_Gui;
	WORD	m_Status;
	WORD	m_InfStatus;	// Indica de quien se reciven los datos
	WORD	m_InfExtra;		// Estatus extra
public:
	DWORD ProcessResource(char* lpzsResourceName);
	DWORD SetGui(DBGUI* lpGui);
	CdbGuiInfProcess();
	virtual ~CdbGuiInfProcess();


};

#endif // !defined(AFX_DBGUIINFPROCESS_H__AC645B79_3494_4A22_8E55_1B54788DF958__INCLUDED_)
