// LotusNote.cpp: implementation of the CLotusNote class.
//
//////////////////////////////////////////////////////////////////////

#include "LotusNote.h"

#define _FILENAME_ "lotusnote.c"

#define _CHECK_HANDLE_ 	if (m_hnote == NULL) return _LOG_ERROR ERR_HANDLE,"Invalid handle (not open note)");
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WORD _stdcall gCWF_ERROR_PROC(const void far *pCDField,WORD phase,STATUS error,HANDLE ErrorText,WORD wErrorTextSize,void far *ctx)
{
	_CD		*cd = (_CD*)OSLockObject(ErrorText);
	CDFIELD	*field = (CDFIELD*)pCDField;

//	Dump_Text((char*)dump_ptr,pcd->text.Header.Length - sizeof(pcd->text));


	char	*cptr = (char*)cd;
	CLogClient::get()->Write(LOG_LERROR,_FILENAME_,__LINE__,ERR_FATAL,"gCWF_ERROR_PROC phase = %u, error = %X, text = %s",phase,error,cptr);
	OSUnlockObject(ErrorText);
	return CWF_NEXT_FIELD;
}

CLotusNote::~CLotusNote()
{
	Close();
}

DWORD CLotusNote::Close()
{
	STATUS	sr;
	if (m_hnote == NULL) return ERR_OK;
	if (!m_closeondestroy) return ERR_OK;
	sr = NSFNoteClose(m_hnote);
	m_hnote = NULL;
	// se mantine el identificador de nota
	return ERR_OK;
}

DWORD CLotusNote::ItemSetText(char *item_name, char *text, WORD length)
{
	_CHECK_HANDLE_
	STATUS	sr;
	sr = NSFItemSetText(m_hnote,item_name,text,length); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemSetText item,value %s,%s failed : %s",item_name,text,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::Update(WORD flags)
{
	_CHECK_HANDLE_
	STATUS	sr;
	sr = NSFNoteUpdate(m_hnote,flags); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFNoteUpdate failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ComputeWithForm(NOTEHANDLE frm_handle,DWORD flag)
{
	_CHECK_HANDLE_
	STATUS	sr;
	sr = NSFNoteComputeWithForm(m_hnote,frm_handle,flag,gCWF_ERROR_PROC,this);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFNoteComputeWithForm failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ItemSetTime(char *itemname, TIMEDATE *ptime)
{
	_CHECK_HANDLE_
	STATUS	sr;
	sr = NSFItemSetTime(m_hnote,itemname,ptime);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemSetTime for %s failed : %s",itemname,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ItemGetText(char *item_name, char *ptext, WORD max_size,WORD* text_size)
{
	WORD	size;
	ptext[0] = 0;	//limpiar el texto
	_CHECK_HANDLE_
	size = NSFItemGetText(m_hnote,item_name,ptext,max_size);
	if (text_size != NULL) *text_size = size;
	ptext[size] = 0;
	return ERR_OK;
}

DWORD CLotusNote::AttachFile(char *item, char *file_path, WORD encoding)
{
	char*	filename = file_path;
	char*	cptr = file_path;
	STATUS	sr;

	_CHECK_HANDLE_
	for(;;)
	{
		cptr = strstr(cptr,"\\");
		if (cptr == NULL) break;
		cptr++;
		filename = cptr;
	}
	sr = NSFNoteAttachFile(m_hnote,item,strlen(item),file_path,filename,encoding);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFNoteAttachFile item,file %s,%s failed : %s",item,file_path,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ItemInfo(char *item_name, BLOCKID *item_blockid, WORD *item_datatype, BLOCKID *value_blockid, DWORD *value_len)
{
	WORD	size = 0;
	STATUS	sr;
	_CHECK_HANDLE_
	if (item_name != NULL) size = strlen(item_name);
	sr = NSFItemInfo(m_hnote,item_name,size,item_blockid,item_datatype,value_blockid,value_len); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemInfo for %s failed : %s",item_name,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ExtractFile(BLOCKID item_blockid, char *file_path, ENCRYPTION_KEY *key)
{
	_CHECK_HANDLE_
	STATUS	sr;
	sr = NSFNoteExtractFile(m_hnote,item_blockid,file_path,key);
	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFNoteExtractFile file %s failed : %s",file_path,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::DetachFile(BLOCKID item_blockid)
{
	STATUS	sr;
	_CHECK_HANDLE_
	sr = NSFNoteDetachFile(m_hnote,item_blockid); if (sr != NOERROR) return _LOG_ERROR ERR_API,"DetachFile failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;
}

BOOL CLotusNote::HasObjects(BLOCKID *item_blockid)
{
	if (m_hnote == NULL)
	{
		_LOG_ERROR ERR_HANDLE,"Invalid handle (not open note)");
		return false;
	}
	return NSFNoteHasObjects(m_hnote,item_blockid);
}

BOOL CLotusNote::AttachmentGetInfo(WORD index, BLOCKID *blockid, char *file_name, DWORD *file_size, WORD *file_attr, WORD *host_type, TIMEDATE *date_create, TIMEDATE *date_modified)
{
	if (m_hnote == NULL)
	{
		_LOG_ERROR ERR_HANDLE,"Invalid handle (not open note)");
		return false;
	}
	return MailGetMessageAttachmentInfo(m_hnote,index,blockid,file_name,file_size,file_attr,host_type,date_create,date_modified);
}

DWORD CLotusNote::AttachmentAdd(char *file_path, char *file_name)
{
	STATUS	sr;
	char*	filename = file_path;
	char*	cptr = file_path;

	_CHECK_HANDLE_

	if (file_name == NULL)
		for(;;)
		{
			cptr = strstr(cptr,"\\");
			if (cptr == NULL) break;
			cptr++;
			filename = cptr;
		}
	else
		filename = file_name;

	sr = MailAddMessageAttachment(m_hnote,file_path,filename); if (sr != NOERROR) return _LOG_ERROR ERR_API,"MailAddMessageAttachment path,name %s,%s failed : %s",file_path,file_name,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::AttachmentExtract(BLOCKID blockid, char *file_path)
{
	STATUS	sr;
	_CHECK_HANDLE_
	sr = MailExtractMessageAttachment(m_hnote,blockid,file_path);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"MailExtractMessageAttachment path %s failed : %s",file_path,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ItemDelete(char *item_name)
{
	STATUS	sr;
	_CHECK_HANDLE_
	sr = NSFItemDelete(m_hnote,item_name,clen(item_name));
	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemDelete for %s failed : %s",item_name,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ItemSetNumber(char *item_name, NUMBER *number)
{
	STATUS	sr;
	_CHECK_HANDLE_
	sr  = NSFItemSetNumber(m_hnote,item_name,number);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemSetNumber for %s failed : %s",item_name,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ItemGetNumber(char *item_name, NUMBER *number)
{
	_CHECK_HANDLE_
	if (!NSFItemGetNumber(m_hnote,item_name,number)) return ERR_FALSE;
	return ERR_OK;
}

/*
	Extrae el fichero que corresponda con el nombre especificado
*/
DWORD CLotusNote::AttachmentExtractFile(char *file_path)
{
	STATUS	sr;
	_CHECK_HANDLE_

	BLOCKID blockid;
	WORD	index;
	char	file[50];
	char	file_name[100];
	char*	cptr;
	char*	pfile_name;
//	char	err[100];

	cptr = file_path;
	pfile_name = cptr;
	for (;;)
	{
		cptr = strstr(cptr,"\\");
		if (cptr == NULL) break;
		cptr++;
		pfile_name = cptr;
	}
	strcpy(file_name,pfile_name);
	strupr(file_name);
	
	for (index = 0;;index++)
	{
		if (!MailGetMessageAttachmentInfo(m_hnote,index,&blockid,file,NULL,NULL,NULL,NULL,NULL))
		{
			return _LOG_ERROR ERR_FATAL,"AttachmentExtractFile ... file not found with FileName = %s",file_name);
		}
		// llevar a mayusculas el fichero
		strupr(file);
		if (strcmp(file,file_name) != 0) continue;
		sr = MailExtractMessageAttachment(m_hnote,blockid,file_path);
		if (sr != NOERROR) return _LOG_ERROR ERR_API,"MailExtractMessageAttachment for %s failed : %s",file_path,CLNotesError().getErrorString(sr));
		return ERR_OK;
	}
	return _LOG_ERROR ERR_FATAL,"File not found for %s",file_path);
}

/*
	Extrae el fichero en la ruta especificada
*/
DWORD CLotusNote::AttachmentExtractTo(WORD index, char *path)
{
	STATUS	sr;
	BLOCKID blockid;
	char	file_name[50];
	char	file_path[MAX_PATH];
	_CHECK_HANDLE_
	if (!MailGetMessageAttachmentInfo(m_hnote,index,&blockid,file_name,NULL,NULL,NULL,NULL,NULL)) 
	{
		return _LOG_ERROR ERR_API,"MailGetMessageAttachmentInfo file no found %s",path);
	}
	sprintf(file_path,"%s\\%s",path,file_name);
	sr = MailExtractMessageAttachment(m_hnote,blockid,file_path); if (sr != NOERROR) return _LOG_ERROR ERR_API,"MailExtractMessageAttachment for %s failed : %s",path,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

/*
	Extraer el fichero a file_path
*/
DWORD CLotusNote::AttachmentExtract(WORD index, char *file_path)
{
	STATUS	sr;
	BLOCKID blockid;
	_CHECK_HANDLE_
	if (!MailGetMessageAttachmentInfo(m_hnote,index,&blockid,NULL,NULL,NULL,NULL,NULL,NULL))
	{
		return _LOG_ERROR ERR_API,"MailGetMessageAttachmentInfo file not found at index %d %s",index,file_path);
	}
	sr = MailExtractMessageAttachment(m_hnote,blockid,file_path); if (sr != NOERROR) return _LOG_ERROR ERR_API,"MailExtractMessageAttachment failed : %s",file_path,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ItemAdd(char *item_name, WORD item_type, WORD item_flags, char *item_value, DWORD item_len)
{
	STATUS	sr;
	_CHECK_HANDLE_
	sr = NSFItemAppend(m_hnote,item_flags,item_name,strlen(item_name),item_type,item_value,item_len);
	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemAppend name,value %s,%s failed : %s",item_name,item_value,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ItemAddTextList(char *item_name, char *item_value,BOOL duplicate)
{
	STATUS	sr;
	_CHECK_HANDLE_
	sr = NSFItemAppendTextList(m_hnote,item_name,item_value,MAXWORD,duplicate);
	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemAppendTextList name,val %s,%s failed : %s",item_name,item_value,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::Attach(NOTEHANDLE hnote, bool closeondestroy)
{
	Close();
	m_hnote = hnote;
	m_closeondestroy = closeondestroy;
	return ERR_OK;
}

DWORD CLotusNote::Open(char *view, char *key)
{
	if (m_hnote != NULL) Close();
	if (m_db->NoteLook(view,key,&m_note_id) != ERR_OK)	return _LOG_AT;
	if (m_note_id == 0)	return _LOG_ERROR ERR_API,"Document not found view(%s),key(%s)",view,key);

	m_noteid_type = 1;
	if (m_db->NoteOpen(&m_hnote,m_note_id) != ERR_OK) return _LOG_AT; 
	m_closeondestroy = true;
	return ERR_OK;
}

DWORD CLotusNote::Create()
{
	Close();
	if (m_db->NoteCreate(&m_hnote) != ERR_OK) return _LOG_AT;
	m_closeondestroy = true;
	return ERR_OK;	
}

DWORD CLotusNote::Create_CompoundText(char *name, HANDLE *phRichText)
{
	STATUS	sr;
	_CHECK_HANDLE_
	sr = CompoundTextCreate(m_hnote,name,phRichText);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"CompoundTextCreate for %s  failed : %s",name,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::Look(char *view, char *key)
{
	Close();
	if (m_db->NoteLook(view,key,&m_note_id) != ERR_OK)	return _LOG_AT;
	m_noteid_type = 1;
	return ERR_OK;
}

DWORD CLotusNote::Delete(WORD flags)
{
	if ((m_noteid_type != 1) || (m_note_id == 0))
	{
		if (m_hnote == NULL) return _LOG_ERROR ERR_API,"Note Closed with NoteID invalid");
		NSFNoteGetInfo(m_hnote,_NOTE_ID,&m_note_id);
	}
	Close();
	if (m_db->NoteDelete(m_note_id,flags) != ERR_OK) return _LOG_AT;
	return ERR_OK;
}

DWORD CLotusNote::CallAgent(char *agentName)
{
	_CHECK_HANDLE_
	return m_db->CallAgent(agentName,m_hnote);
}

DWORD CLotusNote::Refresh()
{
	_CHECK_HANDLE_
	return m_db->NoteRefresh(m_hnote);
}

DWORD CLotusNote::CopyItem(CLotusNote *srcnote, char *src_item, char *dest_item)
{
	char		text[256];
	NOTE_ITEM	item;
	int			i;
	if (srcnote->ItemInfo(src_item,NULL,&item.type,NULL,&item.dwsize) != ERR_OK)
	{
		return _LOG_ERROR ERR_FATAL,"CLotusNote::CopyItem (%s) to (%s) Failed",src_item,dest_item);
	}
	switch (item.type)
	{
		case TYPE_TEXT_LIST:
			{
				srcnote->Item_GetTextListEntries(src_item,&item.count);
				ItemDelete(dest_item);
				for (i=0;i<item.count;i++)
				{
					srcnote->Item_GetTextListEntry(src_item,i,text,sizeof(text),&item.wsize);
					if (item.wsize > sizeof(text))
					{
						return _LOG_ERROR ERR_FATAL,"CLotusNote::CopyItem (%s) to (%s) failed because data has been trunc ",src_item,dest_item);
					}
					ItemAddTextList(dest_item,text,TRUE);
				}
				break;
			}
			//case 
	}
	return ERR_OK;
}

DWORD CLotusNote::Item_GetTextListEntries(char *item_name, WORD *count)
{
	_CHECK_HANDLE_
	*count = NSFItemGetTextListEntries(m_hnote,item_name);
	return ERR_OK;
}

DWORD CLotusNote::Item_GetTextListEntry(char *item_name, WORD index, char *strval, WORD max_size, WORD *size)
{
	WORD	len;
	_CHECK_HANDLE_
	len = NSFItemGetTextListEntry(m_hnote,item_name,index,strval,max_size);
	if (size != NULL) *size = len;
	return ERR_OK;
}

DWORD CLotusNote::OpenByNoteID(DWORD noteid)
{
	Close();
	if (m_db->NoteOpen(&m_hnote,noteid) != ERR_OK) return _LOG_AT;
	m_note_id = noteid;
	m_noteid_type = 1;
	m_closeondestroy = true;
	return ERR_OK;
}

DWORD CLotusNote::OpenByUNID(UNID *note_uid)
{
	Close();
	m_note_uid = *note_uid;
	if (m_db->NoteOpen_UNID(&m_hnote,&m_note_uid) != ERR_OK) return _LOG_AT;
	m_noteid_type = 2;
	m_closeondestroy = true;
	return ERR_OK;
}

DWORD CLotusNote::Open()
{
	if (m_note_id == 0)	return _LOG_ERROR ERR_FATAL,"CLotusNote::Open failed ...  invalid note id");
	if (m_noteid_type == 2) return OpenByUNID(&m_note_uid);
	if (m_noteid_type == 1) return OpenByNoteID(m_note_id);
	return _LOG_ERROR ERR_FATAL,"CLotusNote::Open failed ...  invalid note id type ");
}

DWORD CLotusNote::Attachment_GetInfo(char *file_name, WORD *index, BLOCKID *blockid, DWORD *file_size, WORD *file_attr, WORD *host_type, TIMEDATE *date_create, TIMEDATE *date_modified)
{
	_CHECK_HANDLE_

	char	file[MAXPATH+1];
	char	fname[100];
	WORD	i;
	BLOCKID	bid,*pbid;

	strcpy(fname,file_name);
	_strupr(fname);
	if (blockid == NULL) pbid = &bid; else pbid = blockid;

	for (i = 0;;i++)
	{
		if (!MailGetMessageAttachmentInfo(m_hnote,i,pbid,file,file_size,file_attr,host_type,date_create,date_modified))
		{
			return _LOG_ERROR ERR_FATAL,"Attachment_GetInfo ... file not found with FileName = %s",file_name);
		}
		// llevar a mayusculas el fichero
		strupr(file);
		if (strcmp(file,fname) != 0) continue;
		*index = i;
		return ERR_OK;
	}
	return ERR_FATAL;

}

void  CLotusNote::GetNoteUNID(UNID* pUID)
{
	memset(pUID,0,sizeof(*pUID));
	if (m_noteid_type > 1) {*pUID = m_note_uid;return;}
	if (m_hnote == NULL) return;
	NSFNoteGetInfo(m_hnote,_NOTE_OID,&m_note_oid);
	m_noteid_type = 3;
	*pUID = m_note_uid;
}

void CLotusNote::GetUNID(char* sunid,UNID* pUNID)
{
	char	s_unid[36];
	int		i;
	char	*cptr;
	DWORD	*dwptr;
	UNID	gt_uid;
	memset(pUNID,0,sizeof(*pUNID));
	if (strlen(sunid) != 32) return;
	strcpy(s_unid,sunid);
	cptr = s_unid + 32;
	for (i=0;i<4;i++)
	{
		*cptr = 0;
		cptr -= 8;
		dwptr = 0;
		switch (i) 
		{
		case 0:dwptr = &gt_uid.Note.Innards[0];break;
		case 1:dwptr = &gt_uid.Note.Innards[1];break;
		case 2:dwptr = &gt_uid.File.Innards[0];break;
		case 3:dwptr = &gt_uid.File.Innards[1];break;
		}
		sscanf(cptr,"%8X",dwptr);
	}
	*pUNID = gt_uid;
}


DWORD CLotusNote::Item_GetAllListEntries(char *item_name, char *ptext, WORD max_size, WORD *text_size)
{
	//char		text[256];
	NOTE_ITEM	item;
	int			i;
	DWORD		dwr;
	char		*cptr;
	WORD		slen;
	dwr = ItemInfo(item_name,NULL,&item.type,NULL,&item.dwsize); if (dwr != ERR_OK) return dwr;
	cptr = ptext;
	if (item.type != TYPE_TEXT_LIST)
	{
		ItemGetText(item_name,ptext,max_size,text_size);
		cptr += strlen(ptext);
		cptr++;*cptr=0;
		return ERR_OK;
	}
	dwr = Item_GetTextListEntries(item_name,&item.count);		 if (dwr != ERR_OK) return dwr;
	for (i=0;i<item.count;i++)
	{
		Item_GetTextListEntry(item_name,i,cptr,max_size-(cptr-ptext),&slen);
		if (slen > max_size-(cptr-ptext)) return _LOG_ERROR ERR_FATAL,"CLotusNote::Item_GetAllListEntries ... buffer so short");
		cptr += (slen+1);
	}
	*cptr = 0;
	if (text_size != NULL) *text_size = (cptr-ptext);
	return ERR_OK;
}

DWORD CLotusNote::OpenByUNID(char *sunid)
{
	char	s_unid[36];
	int		i;
	char	*cptr;
	DWORD	*dwptr;
	UNID	gt_uid;
	if (strlen(sunid) != 32) return _LOG_ERROR ERR_FATAL,"CLotusNote::OpenByUNID ... invalid len");
	strcpy(s_unid,sunid);
	cptr = s_unid + 32;
	for (i=0;i<4;i++)
	{
		*cptr = 0;
		cptr -= 8;
		switch (i) 
		{
		case 0:dwptr = &gt_uid.Note.Innards[0];break;
		case 1:dwptr = &gt_uid.Note.Innards[1];break;
		case 2:dwptr = &gt_uid.File.Innards[0];break;
		case 3:dwptr = &gt_uid.File.Innards[1];break;
		}
		sscanf(cptr,"%8X",dwptr);
	}
	return OpenByUNID(&gt_uid);
}

DWORD CLotusNote::ProfileOpen(char *name, char *uname,BOOL bCopy)
{
	Close();
	
	if (m_db->ProfileOpen(&m_hnote,name,uname,bCopy) != ERR_OK) return  _LOG_AT;
	m_closeondestroy = true;
	m_bprofile = true;
	return ERR_OK;
}

DWORD CLotusNote::ProfileUpdate()
{
	STATUS	sr;
	_CHECK_HANDLE_
	if (!m_bprofile)	 return _LOG_ERROR ERR_FATAL,"CLotusNote::ProfileUpdate note handle is not a profile");
	sr = NSFProfileUpdate(m_hnote,m_name,strlen(m_name),m_uname,strlen(m_uname)); if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFProfileUpdate for %s failed : %s",m_name,CLNotesError().getErrorString(sr));
	return ERR_OK;
}

DWORD CLotusNote::ItemInfoNext(BLOCKID prevItem, char *name, BLOCKID *pblockid, WORD *ptype, BLOCKID *pvalue_blockid, DWORD *pvalue_len)
{
	STATUS sr;
	WORD	nlen;

	_CHECK_HANDLE_
	if (name == NULL) nlen = 0; else nlen = strlen(name);

	sr = NSFItemInfoNext(m_hnote,prevItem,name,nlen,pblockid,ptype,pvalue_blockid,pvalue_len);	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemInfoNext failed : %s",CLNotesError().getErrorString(sr));
	return ERR_OK;	
}

DWORD CLotusNote::ItemQuery(BLOCKID item_bid, char *name, WORD name_max, WORD *pname_len, WORD *pflags, WORD *pvalue_type, BLOCKID *pvalue_bid, DWORD *pvalue_len)
{
	_CHECK_HANDLE_
	NSFItemQuery(m_hnote,item_bid,name,name_max,pname_len,pflags,pvalue_type,pvalue_bid,pvalue_len);
	return ERR_OK;

}

void CLotusNote::ItemFlagsToChar(WORD iflags, char *str, WORD max_str)
{
	struct
	{
		char *flag_str;
		WORD  flag;
	} item_flags[] = {
		{"ITEM_SIGN",		ITEM_SIGN},
		{"ITEM_SEAL",		ITEM_SEAL},
		{"ITEM_SUMMARY",	ITEM_SUMMARY},
		{"ITEM_READWRITERS",ITEM_READWRITERS},
		{"ITEM_NAMES",		ITEM_NAMES},
		{"ITEM_PLACEHOLDER",ITEM_PLACEHOLDER},
		{"ITEM_PROTECTED",	ITEM_PROTECTED},
		{"ITEM_READERS",	ITEM_READERS},
		{"ITEM_UNCHANGED",	ITEM_UNCHANGED},
		{0,0}
	};

	char	*cptr = str;
	int		i,j;
	
	for (j=0;item_flags[j].flag != 0;j++)
	{
		if ((iflags & item_flags[j].flag) == 0) continue;
		i = _snprintf(cptr,str+max_str-cptr,"%s|",item_flags[j].flag_str);
		if (i<0) break;
		cptr += i;
	}
	if (cptr != str) cptr[-1] = 0;
}

void CLotusNote::ItemTypeToChar(WORD itype, char *str, WORD max_str)
{
	static struct
	{
		char *type_str;
		WORD  type;
	} item_types[] = {
		{"TYPE_ERROR",			TYPE_ERROR},
		{"TYPE_UNAVAILABLE",	TYPE_UNAVAILABLE},
		{"TYPE_TEXT",			TYPE_TEXT},              
		{"TYPE_TEXT_LIST",		TYPE_TEXT_LIST},    
		{"TYPE_NUMBER",			TYPE_NUMBER},          
		{"TYPE_NUMBER_RANGE",	TYPE_NUMBER_RANGE},
		{"TYPE_TIME",			TYPE_TIME},              
		{"TYPE_TIME_RANGE",		TYPE_TIME_RANGE},  
		{"TYPE_FORMULA",		TYPE_FORMULA},        
		{"TYPE_USERID",			TYPE_USERID},          
		{"TYPE_INVALID_OR_UNKNOWN",TYPE_INVALID_OR_UNKNOWN},
		{"TYPE_COMPOSITE",		TYPE_COMPOSITE},    
		{"TYPE_COLLATION",		TYPE_COLLATION},    
		{"TYPE_OBJECT",			TYPE_OBJECT},          
		{"TYPE_NOTEREF_LIST",	TYPE_NOTEREF_LIST},
		{"TYPE_VIEW_FORMAT",	TYPE_VIEW_FORMAT},
		{"TYPE_ICON",			TYPE_ICON},              
		{"TYPE_NOTELINK_LIST",	TYPE_NOTELINK_LIST},
		{"TYPE_SIGNATURE",		TYPE_SIGNATURE},    
		{"TYPE_SEAL",			TYPE_SEAL},              
		{"TYPE_SEALDATA",		TYPE_SEALDATA},      
		{"TYPE_SEAL_LIST",		TYPE_SEAL_LIST},    
		{"TYPE_HIGHLIGHTS",		TYPE_HIGHLIGHTS},  
		{"TYPE_WORKSHEET_DATA",	TYPE_WORKSHEET_DATA},
		{"TYPE_USERDATA",		TYPE_USERDATA},      
		{"TYPE_QUERY",			TYPE_QUERY},            
		{"TYPE_ACTION",			TYPE_ACTION},          
		{"TYPE_ASSISTANT_INFO",	TYPE_ASSISTANT_INFO},
		{"TYPE_VIEWMAP_DATASET",TYPE_VIEWMAP_DATASET},
		{"TYPE_VIEWMAP_LAYOUT",	TYPE_VIEWMAP_LAYOUT},
		{"TYPE_LSOBJECT",		TYPE_LSOBJECT},      
		{"TYPE_HTML",			TYPE_HTML},              
		{"TYPE_SCHED_LIST",		TYPE_SCHED_LIST},  
		{"TYPE_CALENDAR_FORMAT",TYPE_CALENDAR_FORMAT},
		{"TYPE_MIME_PART",		TYPE_MIME_PART},    
		{"TYPE_RFC822_TEXT",	TYPE_RFC822_TEXT},
		{0,0}
	};
	int		j;
	*str = 0;

	for (j=0;item_types[j].type_str != 0;j++)
	{
		if (itype != item_types[j].type) continue;
		strncat(str,item_types[j].type_str,max_str);
		break;
	}
}

/*
	devuelve el indice del fichero especifico.
	si el fichero no esta se devuelve ERR_NOT_FOUND
*/
//DEL DWORD CLotusNote::isAttachement(char *file_name, WORD *pindex)
//DEL {
//DEL 	// recorrer la lista de ficheros de la nota
//DEL 	_CHECK_HANDLE_
//DEL 
//DEL //	BLOCKID blockid;
//DEL 	// determinar si la nota tiene objetos asociados
//DEL //	if (!NSFNoteHasObjects(m_hnote,&blockid))	return ERR_NOT_FOUND;
//DEL 
//DEL 	if (Attachment_GetInfo(file_name,pindex,NULL,NULL,NULL,NULL,NULL,NULL)) return ERR_OK;
//DEL 	return ERR_NOT_FOUND;
//DEL 	
//DEL }

DWORD CLotusNote::getAttachmentInfo(char *file_name, WORD *index, BLOCKID *blockid, DWORD *file_size, WORD *file_attr, WORD *host_type, TIMEDATE *date_create, TIMEDATE *date_modified)
{
	_CHECK_HANDLE_

	char	file[MAXPATH+1];
	char	fname[100];
	WORD	i;
	BLOCKID	bid;

	strcpy(fname,file_name);
	_strupr(fname);

	for (i = 0;;i++)
	{
		if (!MailGetMessageAttachmentInfo(m_hnote,i,&bid,file,file_size,file_attr,host_type,date_create,date_modified)) return ERR_NOT_FOUND;
		if (_stricmp(file_name,file) == 0) break;
	}
	if (blockid) *blockid = bid;
	if (index)  	*index = i;
	return ERR_OK;
}

DWORD CLotusNote::getItemText(char *iname, char **value, IMem *pmem)
{
	// Obtener tamaño de item
	_CHECK_HANDLE_
	STATUS	st;
	DWORD	dwr;
	BLOCKID	iblock;		//item block
	BLOCKID	dblock;		//data block
	DWORD	dlen;
	char	*text;
	WORD	size;

	WORD	type;

	st = NSFItemInfo(m_hnote,iname,clen(iname),NULL,&type,&dblock,&dlen); 
	if (st != NOERROR) return _LOG_ERROR ERR_API,"NSFItemInfo for %s failed : %s",iname,CLNotesError().getErrorString(st));
	dlen = dlen - sizeof(WORD) + 1;

	dwr = pmem->getU(dlen,(void**)&text);	if (dwr != ERR_OK) return _LOG_EXIT(dwr);
	size = NSFItemGetText(m_hnote,iname,text,dlen);
	text[size] = 0;
	m_db->getSection()->To_Native(text,size);

	*value = text;
	return ERR_OK;
}

//DEL DWORD CLotusNote::getItemTextList(char *iname, struct _cs_list **list, IMem *pmem)
//DEL {
//DEL 	// recorrer toda la lista y formar una lista
//DEL 	_CHECK_HANDLE_
//DEL 	STATUS	st;
//DEL 	DWORD	dlen;
//DEL 	char	*text;
//DEL 	WORD	size;
//DEL 	WORD	type;
//DEL 	WORD	count;
//DEL 	struct _cs_list	*first = NULL;
//DEL 
//DEL 	sr = NSFItemInfo(m_hnote,iname,clen(iname),NULL,&type,&dblock,&dlen);
//DEL 	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemInfo for %s failed : %s",iname,CLNotesError().getErrorString(sr));
//DEL 
//DEL 	if (item.type != TYPE_TEXT_LIST)
//DEL 	{
//DEL 		// se trata como un solo string
//DEL 		if (mdata.get(sizeof(*first),(void**)&first) != ERR_OK) return _LOG_EXIT(ERR_NOMEMORY);
//DEL 		first->next = NULL;
//DEL 		dwr = getItemText(iname,&first->cs,pmem); if (dwr != ERR_OK) return _LOG_EXIT(dwr);
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		count = NSFItemGetTextListEntries(m_hnote,iname);
//DEL 		for (i=0;i<item.count;i++)
//DEL 		{
//DEL 			NSFItemGetTextListEntry(m_hnote,item_name,index,strval,max_size);
//DEL 
//DEL 			Item_GetTextListEntry(item_name,i,cptr,max_size-(cptr-ptext),&slen);
//DEL 			if (slen > max_size-(cptr-ptext)) return _LOG_ERROR ERR_FATAL,"CLotusNote::Item_GetAllListEntries ... buffer so short");
//DEL 			cptr += (slen+1);
//DEL 		}
//DEL 
//DEL 	}
//DEL 	*cptr = 0;
//DEL 	*list = first;
//DEL 	return ERR_OK;
//DEL 
//DEL }

//DEL DWORD CLotusNote::getItemTextListEntry(char *iname, WORD pos, char **value, IMem *pmem)
//DEL {
//DEL 	// Obtener tamaño de item
//DEL 	_CHECK_HANDLE_
//DEL 	STATUS	st;
//DEL 	DWORD	dwr;
//DEL 	BLOCKID	iblock;		//item block
//DEL 	BLOCKID	dblock;		//data block
//DEL 	DWORD	dlen;
//DEL 	char	*text;
//DEL 	WORD	size;
//DEL 
//DEL 	WORD	type;
//DEL 
//DEL 	sr = NSFItemInfo(m_hnote,iname,clen(iname),NULL,&type,&dblock,&dlen); 
//DEL 	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemInfo for %s failed : %s",iname,CLNotesError().getErrorString(sr));
//DEL 	dlen = dlen - sizeof(WORD) + 1;
//DEL 
//DEL 	dwr = pmem->getU(dlen,(void**)text);	if (dwr != ERR_OK) return _LOG_EXIT(dwr);
//DEL 	size = NSFItemGetText(m_hnote,iname,text,dlen);
//DEL 	text[size] = 0;
//DEL 	*value = text;
//DEL 	return ERR_OK;
//DEL }


/*
Obtener el texto de un item, el tamaño del item y la cantidad de elementos
si es multiline
*/

DWORD CLotusNote::getText(char *item, char **val, WORD *size, WORD *count, IMem *pmem)
{
	// Obtener tamaño de item
	_CHECK_HANDLE_
	STATUS	sr;
	DWORD	dwr;
	BLOCKID	iblock;		//item block
	BLOCKID	dblock;		//data block
	DWORD	dlen;
	char	*text;
	WORD	type;
	WORD	isize;
	WORD	icount;

	sr = NSFItemInfo(m_hnote,item,clen(item),NULL,&type,&dblock,&dlen); 
	if (sr != NOERROR) return _LOG_ERROR ERR_API,"NSFItemInfo for %s failed : %s",item,CLNotesError().getErrorString(sr));
	dlen = dlen - sizeof(WORD) + 1;

	dwr = pmem->getU(dlen,(void**)&text);	if (dwr != ERR_OK) return _LOG_EXIT(dwr);
	isize = NSFItemGetText(m_hnote,item,text,dlen);
	text[isize] = 0;

	m_db->getSection()->To_Native(text,isize);

	if (type == TYPE_TEXT_LIST)
	{
		icount = NSFItemGetTextListEntries(m_hnote,item);
	}
	if (size) *size = isize;
	if (count) *count = icount;
	*val = text;
	return ERR_OK;
}
