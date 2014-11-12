// LotusNote.h: interface for the CLotusNote class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOTUSNOTE_H__5A715235_5064_4C38_A3EE_115B82C65DAB__INCLUDED_)
#define AFX_LOTUSNOTE_H__5A715235_5064_4C38_A3EE_115B82C65DAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "imem.h"
#include "lotusdb.h"

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

typedef struct
{
	WORD	type;
	union
	{
		DWORD	dwsize;
		WORD	wsize;
	};
	union
	{
		WORD		count;	// cantidad de elementos en un text list
		TIMEDATE	time;
		NUMBER		number;
		LONG		long_number;
	};
} NOTE_ITEM;



class CLotusNote : public CbObject
{
private:
	CLotusDB	*m_db;
	NOTEHANDLE	m_hnote;
	NOTEID		m_note_id;
	union
	{
		UNID			m_note_uid;
		ORIGINATORID	m_note_oid;
	};
	BYTE		m_noteid_type;
	STATUS		m_sr;
	bool		m_closeondestroy;
	bool	m_bprofile;		//indica que la nota es un profile
	char	m_name[100];	// nombre del profile
	char	m_uname[255];	// usuario del profile

	DWORD Error_Handle(char *function) { return SetError(false,ERR_HANDLE,"%s failed the note is not open yet (handle is NULL)",function); };

public:
	DWORD getText(char* item,char** val,WORD* size,WORD* count,IMem* pmem);
	DWORD getItemText(char* iname,char** value,IMem* pmem);
	DWORD getAttachmentInfo(char* file_name,WORD* index, BLOCKID *blockid = NULL, DWORD *file_size = NULL, WORD *file_attr = NULL, WORD *host_type = NULL, TIMEDATE *date_create = NULL, TIMEDATE *date_modified = NULL);
	
	DWORD getID() { return m_note_id; };
	DWORD ItemQuery(BLOCKID  item_bid,char *name,WORD  name_max,WORD *pname_len,WORD *pflags,WORD *pvalue_type,BLOCKID *pvalue_bid,DWORD *pvalue_len);
	DWORD ItemInfoNext(BLOCKID  prevItem,char *name,BLOCKID *pblockid,WORD *ptype,BLOCKID *pvalue_blockid,DWORD *pvalue_len);
	DWORD ProfileUpdate();
	DWORD ProfileOpen(char *name, char *uname= NULL, BOOL bCopy = TRUE);
	DWORD OpenByUNID(char* sunid);
	DWORD Item_GetAllListEntries(char *item_name, char *ptext, WORD max_size,WORD* text_size = NULL);
	void Clean()
	{
		m_ver = "Class CLotusNote " CLASS_VER;
		m_hnote = NULL;
		m_note_id = 0;
		m_noteid_type = 0;
		m_closeondestroy = true;
		m_bprofile = false;
	};
	DWORD CLotusNote::Look(char *view, char *key);
	DWORD Close();
	CLotusNote(CLotusDB* pLotusDB)
	{
		Clean();
		m_db = pLotusDB;
	};
	CLotusNote()
	{
		Clean();	
	};
	virtual ~CLotusNote();
	void SetDB(CLotusDB* pLotusDB) { m_db = pLotusDB; };
	void GetUNID(char* sunid,UNID* pUNID);
	NOTEID	GetNoteID()		{ return m_note_id; };
	void  GetNoteUNID(UNID* pUID);
	DWORD Attachment_GetInfo(char* file_name,WORD* index, BLOCKID *blockid = NULL, DWORD *file_size = NULL, WORD *file_attr = NULL, WORD *host_type = NULL, TIMEDATE *date_create = NULL, TIMEDATE *date_modified = NULL);
	DWORD Open();
	DWORD OpenByUNID(UNID* note_uid);
	DWORD OpenByNoteID(DWORD noteid);
	DWORD Item_GetTextListEntry(char* item_name,WORD index, char* strval,WORD max_size,WORD* size = NULL);
	DWORD Item_GetTextListEntries(char* item_name,WORD* count);
	DWORD CopyItem(CLotusNote* srcnote,char* src_item,char* dest_item);
	DWORD Refresh();
	DWORD CallAgent(char* agentName);
	DWORD Delete(WORD flags = 0);
	DWORD Create_CompoundText(char* name,HANDLE* phRichText);
	DWORD Create();
	DWORD Open(char* view,char *key);
	DWORD Attach(NOTEHANDLE hnote,bool closeondestroy = false);
	DWORD ItemAddTextList(char *item_name,char *item_value,BOOL duplicate = FALSE);
	DWORD ItemAdd(char* item_name,WORD item_type,WORD item_flags,char* item_value,DWORD item_len);
	DWORD AttachmentExtract(WORD index, char *file_path);
	DWORD Error(char* msg);
	DWORD AttachmentExtractTo(WORD index, char *path);
	DWORD AttachmentExtractFile(char* file_path);
	DWORD ItemGetNumber(char* item_name,NUMBER* number);
	DWORD ItemSetNumber(char* item_name,NUMBER* number);
	DWORD ItemDelete(char* item_name);
	DWORD AttachmentExtract(BLOCKID blockid,char* file_path);
	DWORD AttachmentAdd(char* file_path,char* file_name = NULL);
	BOOL AttachmentGetInfo(WORD index,BLOCKID* blockid,char* file_name,DWORD* file_size,WORD* file_attr,WORD* host_type,TIMEDATE* date_create,TIMEDATE* date_modified);
	BOOL HasObjects(BLOCKID* item_blockid);
	DWORD DetachFile(BLOCKID item_blockid);
	DWORD ExtractFile(BLOCKID item_blockid,char* file_path,ENCRYPTION_KEY* key = NULL);
	DWORD ItemInfo(char* item_name,BLOCKID* item_blockid,WORD* item_datatype,BLOCKID* value_blockid, DWORD* value_len);
	DWORD AttachFile(char* item,char* file_path,WORD encoding = COMPRESS_NONE);
	DWORD ItemGetText(char* item_name,char* ptext,WORD max_size,WORD* text_size = NULL);
	BOOL  IsValid() {return m_hnote != NULL;}
	DWORD ItemSetTime(char* itemname,TIMEDATE* ptime);
	DWORD ComputeWithForm(NOTEHANDLE frm_handle = NULL,DWORD flag = 0);
	DWORD Update(WORD flags = 0);
	DWORD LogLotusErrorMsg(STATUS sr,char* msg = NULL);
	DWORD ItemSetText(char* item_name,char*  text,WORD length = MAXWORD);

	static void	ItemFlagsToChar(WORD iflags,char* str, WORD max_str);
	static void ItemTypeToChar(WORD itype, char *str, WORD max_str);
	
};

#endif // !defined(AFX_LOTUSNOTE_H__5A715235_5064_4C38_A3EE_115B82C65DAB__INCLUDED_)

