// DataBaseAplication.h: interface for the CDataBaseAplication class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATABASEAPLICATION_H__318E8E81_8C43_11D3_9126_0000E83D722B__INCLUDED_)
#define AFX_DATABASEAPLICATION_H__318E8E81_8C43_11D3_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ENTERO 0
#define STRING 1
#define MAXENTERO 10
#define MAXSTRING 40

#include "MSFlexGrid.h"
#include <afxdao.h>

class CDataBaseAplication  
{
public:
	bool Crack(CString &str, COleVariant var);
	bool ShowRecordGrid(CMSFlexGrid *pgrid, CDaoRecordset *pRecordset, CWnd* pWnd, CString *pNoMostrar, int cantidad);
	CString bd_root; //camino donde se encuentra corriendo la aplicacion
	bool CopiarRecords(CString query_org, CString query_dest, CDaoRecordset *pRsorg, CDaoRecordset *pRsdest);
	bool AbreLeer(CDaoRecordset* pRs, CString query);
	bool AbreActualizar(CDaoRecordset* pRs, CString query);
	bool AbreAdicionar(CDaoRecordset* pRs, CString query);
	bool CalcSelSize(CMSFlexGrid *pgrid, CWnd* pWnd);
	CString* PutColString(int *cant, CDaoRecordset* pRS, CString Col);
	bool GetComboBoxSel(CComboBox *pCB, CString &Value);
	bool CleanGrid(CMSFlexGrid *pgrid);
	bool ShowFieldComboBox( CComboBox* pComboBox, CDaoRecordset *pRecordset, CString Field);
	bool GetRecordsetSize(CDaoRecordset *pRecordset, int *Rows, int *Fields);
	bool ShowRecordGrid(CMSFlexGrid *pgrid, CDaoRecordset *pRecordset, CWnd* pWnd);
	bool AdjustString(CString &str, int kind);
	bool ShowRecordList(CListBox* pList, CDaoRecordset* pRecordset);
	CDataBaseAplication();
	virtual ~CDataBaseAplication();

};

#endif // !defined(AFX_DATABASEAPLICATION_H__318E8E81_8C43_11D3_9126_0000E83D722B__INCLUDED_)
