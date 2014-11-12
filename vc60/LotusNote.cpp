// LotusNote.cpp: implementation of the CLotusNote class.
//
//////////////////////////////////////////////////////////////////////

#include "LotusNote.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WORD _stdcall gCWF_ERROR_PROC(const void far *pCDField,WORD phase,STATUS error,HANDLE ErrorText,WORD wErrorTextSize,void far *ctx)
{
	_CD		*cd = (_CD*)OSLockObject(ErrorText);
	CDFIELD	*field = (CDFIELD*)pCDField;

//	Dump_Text((char*)dump_ptr,pcd->text.Header.Length - sizeof(pcd->text));


	char	*cptr = (char*)cd;
	glog._log(LOG_ERROR,"gCWF_ERROR_PROC phase = %u, error = %X, text = %s",phase,error,cptr);
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
	if (m_hnote == NULL) return SetError(false,ERR_HANDLE,"CLotusNote::ItemSetText ...");
	return CLotusSection::Add_NApi_code_msg(NSFItemSetText(m_hnote,item_name,text,length),SSIZE(m_err_msg),"CLotusNote::ItemSetText->NSFItemSetText(%s,%s)",item_name,text);
}

DWORD CLotusNote::LogLotusErrorMsg(STATUS sr,char* msg)
{
	if (msg != NULL) glog.log_strings(LOG_ERROR,msg);
	if (sr != NOERROR)
	{
		glog.log_strings(LOG_ERROR,"Lotus message ->",false);
		OSLoadString(NULLHANDLE,ERR(sr),m_err_msg,sizeof(m_err_msg));
		OSTranslate(OS_TRANSLATE_LMBCS_TO_NATIVE,m_err_msg,sizeof(m_err_msg),m_err_msg,sizeof(m_err_msg));
		glog.log_strings(LOG_ERROR,m_err_msg);
	}
	return ERR_API;
}

DWORD CLotusNote::Update(WORD flags)
{
	if (m_hnote == NULL) return Error_Handle("CLotusNote::Update");
	return CLotusSection::Add_NApi_code_msg(NSFNoteUpdate(m_hnote,flags),SSIZE(m_err_msg),"CLotusNote::Update->NSFNoteUpdate");
}

DWORD CLotusNote::ComputeWithForm(NOTEHANDLE frm_handle,DWORD flag)
{
	if (m_hnote == NULL) return Error_Handle("CLotusNote::ComputeWithForm");
	return CLotusSection::Add_NApi_code_msg(NSFNoteComputeWithForm(m_hnote,frm_handle,flag,gCWF_ERROR_PROC,this),SSIZE(m_err_msg),"CLotusNote::ComputeWithForm->NSFNoteComputeWithForm");
}

DWORD CLotusNote::ItemSetTime(char *itemname, TIMEDATE *ptime)
{
	if (m_hnote == NULL) return Error_Handle("CLotusNote::ItemSetTime");
	return CLotusSection::Add_NApi_code_msg(NSFItemSetTime(m_hnote,itemname,ptime),SSIZE(m_err_msg),"CLotusNote::ItemSetTime->NSFItemSetTime");
}

DWORD CLotusNote::ItemGetText(char *item_name, char *ptext, WORD max_size,WORD* text_size)
{
	WORD	size;
	ptext[0] = 0;	//limpiar el texto
	if (m_hnote == NULL) return Error_Handle("ItemGetText ... failed");
	size = NSFItemGetText(m_hnote,item_name,ptext,max_size);
	if (text_size != NULL) *text_size = size;
	ptext[size] = 0;
	return ERR_OK;
}

DWORD CLotusNote::AttachFile(char *item, char *file_path, WORD encoding)
{
	char*	filename = file_path;
	char*	cptr = file_path;

	if (m_hnote == NULL) return Error_Handle("AttachFile ... failed");

	for(;;)
	{
		cptr = strstr(cptr,"\\");
		if (cptr == NULL) break;
		cptr++;
		filename = cptr;
	}
	return CLotusSection::Add_NApi_code_msg(NSFNoteAttachFile(m_hnote,item,strlen(item),file_path,filename,encoding),SSIZE(m_err_msg),"CLotusNote::AttachFile->NSFNoteAttachFile");
}

DWORD CLotusNote::ItemInfo(char *item_name, BLOCKID *item_blockid, WORD *item_datatype, BLOCKID *value_blockid, DWORD *value_len)
{
	WORD	size = 0;
	if (m_hnote == NULL) return Error_Handle("GetItemInfo ... failed");
	if (item_name != NULL) size = strlen(item_name);
	return CLotusSection::Add_NApi_code_msg(NSFItemInfo(m_hnote,item_name,size,item_blockid,item_datatype,value_blockid,value_len),SSIZE(m_err_msg),"CLotusNote::ItemInfo->NSFItemInfo");
}

DWORD CLotusNote::ExtractFile(BLOCKID item_blockid, char *file_path, ENCRYPTION_KEY *key)
{
	if (m_hnote == NULL) return Error_Handle("ExtractFile ... failed");
	return CLotusSection::Add_NApi_code_msg(NSFNoteExtractFile(m_hnote,item_blockid,file_path,key),SSIZE(m_err_msg),"CLotusNote::ExtractFile->NSFNoteExtractFile");
}

DWORD CLotusNote::DetachFile(BLOCKID item_blockid)
{
	if (m_hnote == NULL) return Error_Handle("ExtractFile ... failed");
	return CLotusSection::Add_NApi_code_msg(NSFNoteDetachFile(m_hnote,item_blockid),SSIZE(m_err_msg),"CLotusNote::DetachFile->NSFNoteDetachFile");
}

BOOL CLotusNote::HasObjects(BLOCKID *item_blockid)
{
	if (m_hnote == NULL) 
	{
		Error_Handle("HasObjects ... failed");
		return false;
	}
	return NSFNoteHasObjects(m_hnote,item_blockid);
}

BOOL CLotusNote::AttachmentGetInfo(WORD index, BLOCKID *blockid, char *file_name, DWORD *file_size, WORD *file_attr, WORD *host_type, TIMEDATE *date_create, TIMEDATE *date_modified)
{
	if (m_hnote == NULL) 
	{
		if (m_hnote == NULL) Error_Handle("GetAttachmentInfo ... failed");
		return false;
	}
	return MailGetMessageAttachmentInfo(m_hnote,index,blockid,file_name,file_size,file_attr,host_type,date_create,date_modified);
}

DWORD CLotusNote::AttachmentAdd(char *file_path, char *file_name)
{
	char*	filename = file_path;
	char*	cptr = file_path;

	if (m_hnote == NULL) return Error_Handle("CLotusNote::AttachmentAdd ... failed");

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

	return CLotusSection::Add_NApi_code_msg(MailAddMessageAttachment(m_hnote,file_path,filename),SSIZE(m_err_msg),"CLotusNote::AttachmentAdd->MailAddMessageAttachment");
}

DWORD CLotusNote::AttachmentExtract(BLOCKID blockid, char *file_path)
{
	if (m_hnote == NULL) return Error_Handle("AttachmentExtract ... failed");
	return CLotusSection::Add_NApi_code_msg(MailExtractMessageAttachment(m_hnote,blockid,file_path),SSIZE(m_err_msg),"CLotusNote::AttachmentExtract->MailExtractMessageAttachment");
}

DWORD CLotusNote::ItemDelete(char *item_name)
{
	if (m_hnote == NULL) return Error_Handle("ItemDelete ... failed");
	return CLotusSection::Add_NApi_code_msg(NSFItemDelete(m_hnote,item_name,strlen(item_name)),SSIZE(m_err_msg),"CLotusNote::ItemDelete->NSFItemDelete");
}

DWORD CLotusNote::ItemSetNumber(char *item_name, NUMBER *number)
{
	if (m_hnote == NULL) return Error_Handle("ItemSetText ... failed");
	return CLotusSection::Add_NApi_code_msg(NSFItemSetNumber(m_hnote,item_name,number),SSIZE(m_err_msg),"CLotusNote::ItemSetNumber->NSFItemSetNumber");
}

DWORD CLotusNote::ItemGetNumber(char *item_name, NUMBER *number)
{
	if (m_hnote == NULL) return Error_Handle("ItemSetText ... failed");
	if (!NSFItemGetNumber(m_hnote,item_name,number)) return ERR_FALSE;
	return ERR_OK;
}

/*
	Extrae el fichero que corresponda con el nombre especificado
*/
DWORD CLotusNote::AttachmentExtractFile(char *file_path)
{
	if (m_hnote == NULL) return Error_Handle("AttachmentExtract ... failed");

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
			return SetError(false,ERR_FATAL,"AttachmentExtractFile ... file not found with FileName = %s",file_name);
		}
		// llevar a mayusculas el fichero
		strupr(file);
		if (strcmp(file,file_name) != 0) continue;
		return CLotusSection::Add_NApi_code_msg(MailExtractMessageAttachment(m_hnote,blockid,file_path),SSIZE(m_err_msg),"CLotusNote::AttachmentExtractFile->MailExtractMessageAttachment");
	}
	return ERR_FATAL;
}
/*
	Extrae el fichero en la ruta especificada
*/
DWORD CLotusNote::AttachmentExtractTo(WORD index, char *path)
{
	BLOCKID blockid;
	char	file_name[50];
	char	file_path[MAX_PATH];
	if (m_hnote == NULL) return Error_Handle("AttachmentExtract ... failed");
	if (!MailGetMessageAttachmentInfo(m_hnote,index,&blockid,file_name,NULL,NULL,NULL,NULL,NULL)) 
	{
		return SetError(false,ERR_API,"CLotusNote::AttachmentExtractTo -> MailGetMessageAttachmentInfo failed ... file is missing ");
	}
	sprintf(file_path,"%s\\%s",path,file_name);
	return CLotusSection::Add_NApi_code_msg(MailExtractMessageAttachment(m_hnote,blockid,file_path),SSIZE(m_err_msg),"CLotusNote::AttachmentExtractTo->MailExtractMessageAttachment");
}

DWORD CLotusNote::Error(char *msg)
{
	strcpy(m_err_msg,msg);
	glog.log_strings(LOG_ERROR,msg);
	return ERR_FATAL;
}

/*
	Extraer el fichero a file_path
*/
DWORD CLotusNote::AttachmentExtract(WORD index, char *file_path)
{
	BLOCKID blockid;
	if (m_hnote == NULL) return Error_Handle("AttachmentExtract ... failed");
	if (!MailGetMessageAttachmentInfo(m_hnote,index,&blockid,NULL,NULL,NULL,NULL,NULL,NULL))
	{
		return SetError(false,ERR_API,"CLotusNote::AttachmentExtract -> MailGetMessageAttachmentInfo failed ... file is missing ");
	}
	return CLotusSection::Add_NApi_code_msg(MailExtractMessageAttachment(m_hnote,blockid,file_path),SSIZE(m_err_msg),"CLotusNote::AttachmentExtract->MailExtractMessageAttachment %s",file_path);
}

DWORD CLotusNote::ItemAdd(char *item_name, WORD item_type, WORD item_flags, char *item_value, DWORD item_len)
{
	if (m_hnote == NULL) return Error_Handle("ItemAdd ... failed");
	return CLotusSection::Add_NApi_code_msg(NSFItemAppend(m_hnote,item_flags,item_name,strlen(item_name),item_type,item_value,item_len),SSIZE(m_err_msg),"CLotusNote::ItemAdd->NSFItemAppend");
}

DWORD CLotusNote::ItemAddTextList(char *item_name, char *item_value,BOOL duplicate)
{
	if (m_hnote == NULL) return Error_Handle("ItemAddTextList ... failed");
	return CLotusSection::Add_NApi_code_msg(NSFItemAppendTextList(m_hnote,item_name,item_value,MAXWORD,duplicate),SSIZE(m_err_msg),"CLotusNote::ItemAddTextList->NSFItemAppendTextList");
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
	DWORD	dwr;
	if (m_hnote != NULL) Close();
	dwr = m_db->NoteLook(view,key,&m_note_id);
	if (dwr != ERR_OK)
	{
		sprintf(m_err_msg,"CLotusNote::Open view = <%s>, key = <%s> failed because %s",view,key,m_db->GetErrorMsg());
		glog.log_strings(LOG_ERROR,m_err_msg);
		return ERR_FATAL;
	}
	if (m_note_id == 0)
	{
		sprintf(m_err_msg,"CLotusNote::Open view = <%s>, key = <%s> failed because document not found ",view,key);
		glog.log_strings(LOG_ERROR,m_err_msg);
		return ERR_FATAL;
	}
	m_noteid_type = 1;
	dwr = m_db->NoteOpen(&m_hnote,m_note_id);
	if (dwr != ERR_OK)
	{
		sprintf(m_err_msg,"CLotusNote::Open note id = <%d> failed because %s",m_note_id,m_db->GetErrorMsg());
		glog.log_strings(LOG_ERROR,m_err_msg);
		return ERR_FATAL;
	}

	m_closeondestroy = true;
	return ERR_OK;
}

DWORD CLotusNote::Create()
{
	DWORD	dwr;
	Close();
	dwr = m_db->NoteCreate(&m_hnote);
	if (dwr != ERR_OK)
	{
		sprintf(m_err_msg,"CLotusNote::Create failed because %s",m_db->GetErrorMsg());
		glog.log_strings(LOG_ERROR,m_err_msg);
		return ERR_FATAL;
	}
	m_closeondestroy = true;
	return ERR_OK;	
}

DWORD CLotusNote::Create_CompoundText(char *name, HANDLE *phRichText)
{
	if (m_hnote == NULL) return Error_Handle("CLotusNote::Create_CompoundText");
	return CLotusSection::Add_NApi_code_msg(CompoundTextCreate(m_hnote,name,phRichText),SSIZE(m_err_msg),"CLotusNote::Create_CompoundText->CompoundTextCreate");
}

DWORD CLotusNote::Look(char *view, char *key)
{
	DWORD	dwr;
	Close();
	dwr = m_db->NoteLook(view,key,&m_note_id);
	if (dwr != ERR_OK)
	{
		sprintf(m_err_msg,"CLotusNote::Look view = <%s>, key = <%s> failed because %s",view,key,m_db->GetErrorMsg());
		glog.log_strings(LOG_ERROR,m_err_msg);
		return ERR_FATAL;
	}
	m_noteid_type = 1;
	return ERR_OK;
}

DWORD CLotusNote::Delete(WORD flags)
{
	DWORD	dwr;
	if ((m_noteid_type != 1) || (m_note_id == 0))
	{
		if (m_hnote == NULL) return Error_Handle("CLotusNote::Delete Note Closed with NoteID invalid");
		NSFNoteGetInfo(m_hnote,_NOTE_ID,&m_note_id);
	}
	Close();
	if (m_db->NoteDelete(m_note_id,flags) != ERR_OK) return SetError(false,ERR_FATAL,"CLotusNote::Delete noteID = <%u> failed because %s",m_note_id,m_db->GetErrorMsg());
	return ERR_OK;
}

DWORD CLotusNote::CallAgent(char *agentName)
{
	DWORD	dwr;
	if (m_hnote == NULL) return Error_Handle("CLotusNote::CallAgent");
	dwr = m_db->CallAgent(agentName,m_hnote);
	return dwr;
}

DWORD CLotusNote::Refresh()
{
	DWORD	dwr;
	if (m_hnote == NULL) return Error_Handle("CLotusNote::Refresh");
	dwr = m_db->NoteRefresh(m_hnote);
	return dwr;
}

DWORD CLotusNote::CopyItem(CLotusNote *srcnote, char *src_item, char *dest_item)
{
	char		text[256];
	NOTE_ITEM	item;
	int			i;
	if (srcnote->ItemInfo(src_item,NULL,&item.type,NULL,&item.dwsize) != ERR_OK)
	{
		sprintf(m_err_msg,"CLotusNote::CopyItem (%s) to (%s) failed because %s",src_item,dest_item,srcnote->GetErrorMsg());
		glog.log_strings(LOG_ERROR,m_err_msg);
		return ERR_FATAL;
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
						sprintf(m_err_msg,"CLotusNote::CopyItem (%s) to (%s) failed because data has been trunc ",src_item,dest_item);
						glog.log_strings(LOG_ERROR,m_err_msg);
						return ERR_FATAL;
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
	if (m_hnote == NULL) return Error_Handle("CLotusNote::Item_GetTextListEntries");
	*count = NSFItemGetTextListEntries(m_hnote,item_name);
	return ERR_OK;
}

DWORD CLotusNote::Item_GetTextListEntry(char *item_name, WORD index, char *strval, WORD max_size, WORD *size)
{
	WORD	len;
	if (m_hnote == NULL) return Error_Handle("CLotusNote::Item_GetTextListEntry");
	len = NSFItemGetTextListEntry(m_hnote,item_name,index,strval,max_size);
	if (size != NULL) *size = len;
	return ERR_OK;
}

DWORD CLotusNote::OpenByNoteID(DWORD noteid)
{
	DWORD	dwr;
	Close();
	m_note_id = noteid;
	m_noteid_type = 1;
	dwr = m_db->NoteOpen(&m_hnote,m_note_id);
	if (dwr != ERR_OK)
	{
		sprintf(m_err_msg,"CLotusNote::OpenByNoteID note id = %X failed because %s",m_note_id,m_db->GetErrorMsg());
		glog.log_strings(LOG_ERROR,m_err_msg);
		return ERR_FATAL;
	}
	m_closeondestroy = true;
	return ERR_OK;
}

DWORD CLotusNote::OpenByUNID(UNID *note_uid)
{
	DWORD	dwr;
	Close();
	m_note_uid = *note_uid;
	m_noteid_type = 2;
	dwr = m_db->NoteOpen_UNID(&m_hnote,&m_note_uid);
	if (dwr != ERR_OK)
	{
		sprintf(m_err_msg,"CLotusNote::OpenByUNID failed because %s",m_db->GetErrorMsg());
		glog.log_strings(LOG_ERROR,m_err_msg);
		return ERR_FATAL;
	}
	m_closeondestroy = true;
	return ERR_OK;
}

DWORD CLotusNote::Open()
{
	if (m_note_id == 0)	return SetError(true,ERR_FATAL,"CLotusNote::Open failed ...  invalid note id");
	if (m_noteid_type == 2) return OpenByUNID(&m_note_uid);
	if (m_noteid_type == 1) return OpenByNoteID(m_note_id);
	return SetError(true,ERR_FATAL,"CLotusNote::Open failed ...  invalid note id type ");
}

DWORD CLotusNote::Attachment_GetInfo(char *file_name, WORD *index, BLOCKID *blockid, DWORD *file_size, WORD *file_attr, WORD *host_type, TIMEDATE *date_create, TIMEDATE *date_modified)
{
	if (m_hnote == NULL) return Error_Handle("Attachment_GetInfo ... failed");

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
			sprintf(m_err_msg,"Attachment_GetInfo ... file not found with FileName = %s",file_name);
			glog.log_strings(LOG_ERROR,m_err_msg);
			return ERR_FATAL;
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
		if (slen > max_size-(cptr-ptext)) return SetError(true,ERR_FATAL,"CLotusNote::Item_GetAllListEntries ... buffer so short");
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
	if (strlen(sunid) != 32) return SetError(true,ERR_FATAL,"CLotusNote::OpenByUNID ... invalid len");
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
	DWORD	dwr;
	Close();
	
	dwr = m_db->ProfileOpen(&m_hnote,name,uname,bCopy);
	if (dwr != ERR_OK) return SetError(true,dwr,"CLotusNote::ProfileOpen->%s",m_db->GetErrorMsg());
	m_closeondestroy = true;
	m_bprofile = true;
	return ERR_OK;
}

DWORD CLotusNote::ProfileUpdate()
{
	STATUS	sr;
	if (m_hnote == NULL) return Error_Handle("CLotusNote::ProfileUpdate ... failed");
	if (!m_bprofile)	 return SetError(true,ERR_FATAL,"CLotusNote::ProfileUpdate note handle is not a profile");
	sr = NSFProfileUpdate(m_hnote,m_name,strlen(m_name),m_uname,strlen(m_uname));
	if (sr != NOERROR)
		return CLotusSection::Add_NApi_code_msg(sr,m_err_msg,sizeof(m_err_msg),"CLotusNote::ProfileUpdate %s,%s",m_name,m_uname);

	return ERR_OK;
}

DWORD CLotusNote::ItemInfoNext(BLOCKID prevItem, char *name, BLOCKID *pblockid, WORD *ptype, BLOCKID *pvalue_blockid, DWORD *pvalue_len)
{
	STATUS sr;
	WORD	nlen;

	if (m_hnote == NULL) return Error_Handle("CLotusNote::ItemInfoNext ... failed");
	if (name == NULL) nlen = 0; else nlen = strlen(name);

	sr = NSFItemInfoNext(m_hnote,prevItem,name,nlen,pblockid,ptype,pvalue_blockid,pvalue_len);
	return CLotusSection::Add_NApi_code_msg(sr,m_err_msg,sizeof(m_err_msg),"CLotusNote::ItemInfoNext %s",name);
}

DWORD CLotusNote::ItemQuery(BLOCKID item_bid, char *name, WORD name_max, WORD *pname_len, WORD *pflags, WORD *pvalue_type, BLOCKID *pvalue_bid, DWORD *pvalue_len)
{
	STATUS sr;
	if (m_hnote == NULL) return Error_Handle("CLotusNote::NSFItemQuery ... failed");
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
	struct
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
	char	*cptr = str;
	int		i,j;
	*str = 0;

	for (j=0;item_types[j].type_str != 0;j++)
	{
		if (itype != item_types[j].type) continue;
		strncat(str,item_types[j].type_str,max_str);
		break;
	}
}
