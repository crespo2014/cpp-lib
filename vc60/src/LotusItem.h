// LotusItem.h: interface for the CLotusItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOTUSITEM_H__83C39CFF_A946_423E_A15C_DF3D781F5334__INCLUDED_)
#define AFX_LOTUSITEM_H__83C39CFF_A946_423E_A15C_DF3D781F5334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "memarray.h"
#include "lotusnote.h"


struct _sig_dt
{
	WORD sig;
	BYTE size; 
	WORD ods_type;
};

class CLotusItem : public CbObject
{
public:
	static struct _sig_dt* getSigData();
	DWORD Dump_CDBITMAPSEGMENT(_CD* pcd);
	DWORD Dump_CDBITMAPHEADER(_CD* pcd);
	DWORD Dump_LogData();
	DWORD Dump_CDTEXT(_CD *pcd);
	DWORD Dump_Text(char* str,DWORD size);
	DWORD AddToNote(char* item_name,WORD item_flags);
	DWORD Data_Add(_CD *pcd,void* pdata = NULL);
	DWORD Data_Reset(DWORD max_size = 0);
	DWORD Dump_CDHOTSPOTBEGIN(_CD* pcd);
	void CheckCDSize(_CD* pcd);
	DWORD	Dump_LogCD(_CD* pcd);
	DWORD	Dump_Next(_CD *pcd);
	void	Dump_GetData(void* pbuff,DWORD max_size,BOOL toCanonical = true);
	DWORD	Dump_start();
	DWORD	GetItemData(CMemArray* pMemory);
	void	Release();
	DWORD	Error(char* msg,DWORD error = ERR_FATAL);
	DWORD	GetInfo(char* item_name);

	CLotusItem(CLotusNote*	pnote);
	virtual ~CLotusItem();

	//BYTE*	data_ptr;
	//WORD	*dump_data_type;
	BYTE	*dump_ptr;

	WORD	data_type;
//	DWORD	data_size;
	
private:
	CLotusNote*	m_pnote;
	BLOCKID		m_blockid;
	char		m_name[200];
	BLOCKID		m_data_blockid;
	char		m_err_msg[300];
	CMemArray	m_mem_data;

	// variables para el dump
	_SIGNATURE	m_last_sig;	// ultima signatura leida
	BYTE	*m_last_ptr;	// ultima posicion del dump_ptr
	
	// variables para crear un nuevo richtext.
	BYTE	*m_data_start;
	BYTE	*m_data_ptr;
	DWORD	m_data_size;


};

#endif // !defined(AFX_LOTUSITEM_H__83C39CFF_A946_423E_A15C_DF3D781F5334__INCLUDED_)
