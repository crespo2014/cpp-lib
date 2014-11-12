// LotusItem.h: interface for the CLotusItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOTUSITEM_H__83C39CFF_A946_423E_A15C_DF3D781F5334__INCLUDED_)
#define AFX_LOTUSITEM_H__83C39CFF_A946_423E_A15C_DF3D781F5334__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lotusNote.h"
#include "memarray.h"

#define SIG_LONG	0
#define SIG_WORD	1
#define SIG_BIG		2

typedef struct
{
	WORD	Signature;	
	DWORD	Length;
	union 
	{
		LSIG lsig;
		WSIG wsig;
		BSIG bsig;
	};
} _SIGNATURE;

typedef struct
{
	WORD	Signature;	
	DWORD	Length;
	DWORD	Value_size;		// tamaño de los datos extra
	union
	{
		BYTE				data[1];
		CDALTERNATEBEGIN	alternate_begin;
		CDALTERNATEEND		alternate_end;
		CDALTTEXT			alt_text;
		CDANCHOR			anchor;
		CDBACKGROUNDPROPERTIES	background_properties;
		CDBAR				bar;
		CDBEGINRECORD		begin_record;
		CDPABDEFINITION		pab_definition;
		CDPABREFERENCE		pab_reference;
		CDTEXT				text;
		CDHOTSPOTBEGIN		hotspot_begin;
		CDHOTSPOTEND		hotspot_end;
		CDTEXTEFFECT		text_effect;
		CDGRAPHIC			graphic;
		CDBITMAPHEADER		bitmap_header;
		CDBITMAPSEGMENT		bitmap_segment;
	};
} _CD;

class CLotusItem  
{
public:
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
