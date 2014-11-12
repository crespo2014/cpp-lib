// LotusItem.cpp: implementation of the CLotusItem class.
//
//////////////////////////////////////////////////////////////////////

#include "LotusItem.h"

#define _FILENAME_	"lotusitem.c"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define SIG_SIZE(x) {SIG_CD_##x,sizeof(CD##x),_CD##x}



CLotusItem::CLotusItem(CLotusNote*	pnote)
{
	m_ver = "Class CLotusItem " CLASS_VER;

	m_pnote = pnote;
	m_data_size = 0;
	data_type = 0;
	m_name[0] = 0;
	m_err_msg[0] = 0;
//	data_ptr = NULL;
}

CLotusItem::~CLotusItem()
{
	Release();
}

DWORD CLotusItem::GetInfo(char *item_name)
{
	Release();
	if (m_pnote->ItemInfo(item_name,&m_blockid,&data_type,&m_data_blockid,&m_data_size) != ERR_OK) return _LOG_AT;
	_snprintf(SSIZE(m_name),"%s",item_name);
	return ERR_OK;
}

//DEL DWORD CLotusItem::LockData()
//DEL {
//DEL 	/*
//DEL 		la estructura es la siguiente el pool posee bloques 
//DEL 		cada bloque es un desplazamiento dentro del pool
//DEL 		el comienzo de los datos parece ser el tama�o o algo desconocido de tipo USHORT 2 bytes
//DEL 		despues vienen los datos hasta completar el tama�o del item, las lista string se dividen por ceros en las cadenas
//DEL 	*/
//DEL 
//DEL 	if (data_size == 0) return Error("CLotusItem::LockData ... not data to lock, data size = 0");
//DEL 	data_ptr =  (BYTE*)OSLockObject(m_data_blockid.pool);
//DEL 	data_ptr += m_data_blockid.block;
//DEL 	//data_ptr += sizeof(USHORT);	
//DEL 	return ERR_OK;
//DEL }

DWORD CLotusItem::Error(char *msg, DWORD error)
{
	strcpy(m_err_msg,msg);
	return error;
}

//DEL void CLotusItem::UnLockData()
//DEL {
//DEL 	if (data_ptr == NULL) return;
//DEL 	OSUnlockBlock(m_data_blockid);
//DEL 	data_ptr = NULL;
//DEL }

void CLotusItem::Release()
{
	m_data_size = 0;
	data_type = 0;
	m_name[0] = 0;
}

DWORD CLotusItem::GetItemData(CMemArray *pMemory)
{
	pMemory->Release();
	pMemory->SetMaxMemorySize(m_data_size);
	pMemory->SetSize(m_data_size);
	//memcpy(pMemory->GetMemBuffer(),data_ptr,data_size);
	return ERR_OK;
}

DWORD CLotusItem::Dump_start()
{
	BYTE*	data_ptr;
	if (m_data_size == 0) return Error("CLotusItem::LockData ... not data to lock, data size = 0");
	data_ptr =  (BYTE*)OSLockObject(m_data_blockid.pool);
	data_ptr += m_data_blockid.block;

	m_mem_data.Release();
	m_mem_data.SetMaxMemorySize(m_data_size);
	m_mem_data.SetSize(m_data_size);
	m_data_ptr = (BYTE*)m_mem_data.GetMemBuffer();
	memcpy(m_data_ptr,data_ptr,m_data_size);
	OSUnlockBlock(m_data_blockid);
	
//	m_dump_pos = 0;
//	dump_data_type = (WORD*)&dump_ptr[0];
	dump_ptr = m_data_ptr;
	dump_ptr += 2;	//evitar el tipo de nota
	
	m_last_sig.Length = 0;
	m_last_ptr = dump_ptr;
	return ERR_OK;
}

void CLotusItem::Dump_GetData(void *pbuff, DWORD max_size, BOOL toCanonical)
{

}

//DEL void CLotusItem::Dump_ReadSignature(_SIGNATURE *sig)
//DEL {
//DEL 	ODSReadMemory(&dump_ptr, _WORD, &sig->bsig, 1);
//DEL 	switch (sig->bsig.Length)
//DEL 	{
//DEL 	case (LONGRECORDLENGTH >> 8):
//DEL 		ODSReadMemory(&dump_ptr, _DWORD, &sig->lsig.Length, 1);
//DEL 		sig->type = SIG_LONG;
//DEL 		break;
//DEL 	case (WORDRECORDLENGTH >> 8):
//DEL 		ODSReadMemory(&dump_ptr, _WORD, &sig->wsig.Length, 1);
//DEL 		sig->type = SIG_WORD;
//DEL 		break;
//DEL 	default:
//DEL 		sig->type = SIG_BIG;
//DEL 		break;
//DEL 	}
//DEL 	// el tipo de registro sigue siendo el byte bajo. (bsig.Signature)
//DEL }

DWORD CLotusItem::Dump_Next(_CD *pcd)
{
	int		i;
	struct _sig_dt* sig_size = getSigData();

	m_last_ptr += m_last_sig.Length;
	if ((DWORD)m_last_ptr%2) 
		m_last_ptr++;
	dump_ptr = m_last_ptr;
	
	if (m_last_ptr >= m_data_ptr + m_data_size) return ERR_EOF;

	ODSReadMemory(&dump_ptr, _WORD, &m_last_sig.bsig, 1);
	switch (m_last_sig.bsig.Length)
	{
	case (LONGRECORDLENGTH >> 8):
		ODSReadMemory(&dump_ptr, _DWORD, &m_last_sig.lsig.Length, 1);
		m_last_sig.Signature	= m_last_sig.wsig.Signature;
		m_last_sig.Length		= m_last_sig.lsig.Length;
		break;
	case (WORDRECORDLENGTH >> 8):
		ODSReadMemory(&dump_ptr, _WORD, &m_last_sig.wsig.Length, 1);
		m_last_sig.Signature	= m_last_sig.wsig.Signature;
		m_last_sig.Length		= m_last_sig.wsig.Length;
		break;
	default:
		m_last_sig.Signature	= m_last_sig.bsig.Signature;
		m_last_sig.Length		= m_last_sig.bsig.Length;
		break;
	}
	dump_ptr		= m_last_ptr;
	pcd->Length		= m_last_sig.Length;
	pcd->Signature	= m_last_sig.Signature;

	// Buscar el tipo de estructura y leerla
	for (i=0;(sig_size[i].sig | sig_size[i].size | sig_size[i].ods_type) != 0;i++)
	{
		if (sig_size[i].sig == pcd->Signature) break;
	}
	if (sig_size[i].size != 0) 
	{
		ODSReadMemory(&dump_ptr,sig_size[i].ods_type,&pcd->data,1);
	}
	pcd->Value_size = m_last_ptr + m_last_sig.Length - dump_ptr;
	if (pcd->Value_size > 0)
	{
		_LOG_DATA "CLotusItem::Dump_ReadCD (%d) bytes left to read",pcd->Value_size);
		//memcpy(&pcd->data[sig_size[i].size],dump_ptr,ptr - dump_ptr);
	}
	CheckCDSize(pcd);
	return ERR_OK;
}

DWORD CLotusItem::Dump_LogCD(_CD *pcd)
{
	switch(pcd->Signature)
	{
	case SIG_CD_PABDEFINITION:
		{
#ifdef LOTUS6
			if (pcd->pab_definition.Flags2 && PABFLAG2_MORE_FLAGS)
			{
				ODSReadMemory(&dump_ptr,_DWORD,&dw,1);
				if (dw && EXTENDEDPABFLAGS3) 
				{
					ODSReadMemory(&dump_ptr,_DWORD,&dw,1);
				}
			}
#endif
			_LOG_DATA "*** CDPABDEFINITION ***");
			_LOG_DATA "PABID       = %d",pcd->pab_definition.PABID);
			_LOG_DATA "JustifyMode = %d",pcd->pab_definition.JustifyMode);
			_LOG_DATA "LineSpacing = %d",pcd->pab_definition.LineSpacing);
			_LOG_DATA "LeftMargin  = %d",pcd->pab_definition.LeftMargin);
			_LOG_DATA "RightMargin = %d",pcd->pab_definition.RightMargin);
			_LOG_DATA "Flags2      = %d",pcd->pab_definition.Flags2);
			_LOG_DATA "Flags       = %d",pcd->pab_definition.Flags);
			_LOG_DATA "TabTypes    = %d",pcd->pab_definition.TabTypes);

			_LOG_DATA "FirstLineLeftMargin     = %d",pcd->pab_definition.FirstLineLeftMargin);
			_LOG_DATA "ParagraphSpacingBefore  = %d",pcd->pab_definition.ParagraphSpacingBefore);
			_LOG_DATA "ParagraphSpacingAfter   = %d",pcd->pab_definition.ParagraphSpacingAfter);
			_LOG_DATA "ParagraphSpacingAfter   = %d",pcd->pab_definition.ParagraphSpacingAfter);
			break;
		}
	case SIG_CD_PABREFERENCE:
		{
			_LOG_DATA "*** PABREFERENCE ***");
			_LOG_DATA "PABID = %d",pcd->pab_reference.PABID);
			break;
		}
	case SIG_CD_TEXT: return Dump_CDTEXT(pcd);
		{
			
			break;
		}
	case SIG_CD_BEGIN:
		{
			_LOG_DATA "*** CDBEGIN ***");
			_LOG_DATA "Version   = %d",pcd->begin_record.Version);
			_LOG_DATA "Signature = %d",pcd->begin_record.Signature);
			break;
		}
	case SIG_CD_END:
		{
			_LOG_DATA "*** CDEND ***");
			break;
		}
	case SIG_CD_HOTSPOTBEGIN: return Dump_CDHOTSPOTBEGIN(pcd);
	case SIG_CD_HOTSPOTEND:
		{
			_LOG_DATA "*** HOTSPOTEND ***");
			break;
		}
	case SIG_CD_TEXTEFFECT:
		{
			_LOG_DATA "*** TEXTEFFECT ***");
			_LOG_DATA "FontEffectID = %d",pcd->text_effect.FontEffectID);
			break;
		}
	case SIG_CD_GRAPHIC:
		{
			_LOG_DATA "*** GRAPHIC ***");
			_LOG_DATA "DestSize = (%u,%u)",pcd->graphic.DestSize.width,pcd->graphic.DestSize.height);
			_LOG_DATA "CropSize = (%u,%u)",pcd->graphic.CropSize.width,pcd->graphic.CropSize.height);
			_LOG_DATA "CropOffset = (%u,%u)-(%u,%u)",
				pcd->graphic.CropOffset.left,
				pcd->graphic.CropOffset.top,
				pcd->graphic.CropOffset.right,
				pcd->graphic.CropOffset.bottom);
			_LOG_DATA "fResize = %d",pcd->graphic.fResize);
			_LOG_DATA "Version = %d",pcd->graphic.Version);
			_LOG_DATA "bFlags = %d",pcd->graphic.bFlags);
			_LOG_DATA "wReserved = %d",pcd->graphic.wReserved);
			break;
		}
	case SIG_CD_BITMAPHEADER: return Dump_CDBITMAPHEADER(pcd);
	case SIG_CD_BITMAPSEGMENT: return Dump_CDBITMAPSEGMENT(pcd);
	case SIG_CD_COLORTABLE:
		{
			_LOG_DATA "*** COLORTABLE ***");
			break;			
		}
	case SIG_CD_PATTERNTABLE:
		{
			_LOG_DATA "*** PATTERNTABLE ***");
			break;			
		}
	default:
		{
			_LOG_DATA "*** UNKNOWN SIGNATURE ***");
			_LOG_DATA "Signature = %d",pcd->Signature);
			break;
		}

	}
	return ERR_OK;
}

// CDPABREFERENCE:
//CDTEXT

void CLotusItem::CheckCDSize(_CD *pcd)
{
	switch(pcd->Signature)
	{
	case SIG_CD_HOTSPOTBEGIN:
		{
			//m_last_sig.Length = sizeof(CDHOTSPOTBEGIN) + pcd->hotspot_begin.DataLength;			
			break;
		}
	case SIG_CD_BEGIN:
		{
			//m_last_sig.Length = sizeof(CDBEGINRECORD);
			break;
		}
	}
}

DWORD CLotusItem::Dump_CDHOTSPOTBEGIN(_CD *pcd)
{
	DWORD dwFlags;
	char	str[255];
//	glog.log_strings(LOG_DATA,"*** HOTSPOTBEGIN ***");

	if (SIG_CD_HOTSPOTBEGIN == pcd->Signature) 
		_LOG_DATA "*** HOTSPOTBEGIN ***");
	else if (SIG_CD_V4HOTSPOTBEGIN == pcd->Signature) 
		_LOG_DATA "*** V4HOTSPOTBEGIN ***");
	else if (SIG_CD_V5HOTSPOTBEGIN == pcd->Signature) 
		_LOG_DATA "*** V5HOTSPOTBEGIN ***");
	else if (SIG_CD_V6HOTSPOTBEGIN_CONTINUATION == pcd->Signature) 
		_LOG_DATA "*** V6HOTSPOTBEGIN_CONTINUATION ***");
	else
	{
		_LOG_DATA "*** UNKNOWN HOTSPOT TYPE ***");
		return ERR_OK;
	}
	_LOG_DATA "Type       = %d",pcd->hotspot_begin.Type);
	//glog.log_uint(LOG_DATA,"Flags      =",pcd->hotspot_begin.Flags);
	_LOG_DATA "DataLength = %d",pcd->hotspot_begin.DataLength);

	dwFlags = pcd->hotspot_begin.Flags;
	str[0] = 0;
	if (dwFlags & HOTSPOTREC_RUNFLAG_BEGIN)         strcat(str,"BEGIN " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_END)           strcat(str, "END " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_BOX)           strcat(str, "BOX " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_NOBORDER)      strcat(str, "NOBORDER " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_FORMULA)       strcat(str, "FORMULA " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_MOVIE)         strcat(str, "MOVIE " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_IGNORE)        strcat(str, "IGNORE " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_ACTION)        strcat(str, "ACTION " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_SCRIPT)        strcat(str, "SCRIPT " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_INOTES)        strcat(str, "INOTES " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_ISMAP)         strcat(str, "ISMAP " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_INOTES_AUTO)   strcat(str, "INOTES_AUTO " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_ISMAP_INPUT)   strcat(str, "ISMAP_INPUT " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_SIGNED)        strcat(str, "SIGNED " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_ANCHOR)        strcat(str, "ANCHOR " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_COMPUTED)	    strcat(str, "COMPUTED " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_TEMPLATE)      strcat(str, "TEMPLATE " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_HIGHLIGHT)     strcat(str, "HIGHLIGHT " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_EXTACTION)     strcat(str, "EXTACTION " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_NAMEDELEM)     strcat(str, "NAMEDELEM " );
    if (dwFlags & HOTSPOTREC_RUNFLAG_WEBJAVASCRIPT) strcat(str, "WEBJAVASCRIPT " );
	_LOG_DATA "Flags =(%s)",str);

	if (pcd->hotspot_begin.DataLength == 0) return ERR_OK;

	if (HOTSPOTREC_TYPE_ACTIVEOBJECT == pcd->hotspot_begin.Type)
	{
		_LOG_DATA "    Hot Spot Active Object =");
		//DumpActiveObject (p, cdHotSpot.DataLength);
	}
	else if (HOTSPOTREC_TYPE_OLERICHTEXT == pcd->hotspot_begin.Type)
	{
		_LOG_DATA "    Hot Spot OLE Rich Text Object =");
		//DumpHSOleRichText (p, cdHotSpot.DataLength);
	}
	else if (dwFlags & HOTSPOTREC_RUNFLAG_ACTION)
	{
		_LOG_DATA "    Hot Spot Action =");
		//PrintNotesActions (p, cdHotSpot.DataLength);
	}
	else if (dwFlags & HOTSPOTREC_RUNFLAG_SCRIPT)
	{
			/* Print the Lotus Script source (if available) */
		_LOG_DATA "    Hot Spot Script =" );
	//	PrintScriptSource (p, cdHotSpot.DataLength);
	}
    else if ((dwFlags & HOTSPOTREC_RUNFLAG_FORMULA)
		|| (pcd->hotspot_begin.Type == HOTSPOTREC_TYPE_BUTTON))
	{
			/* Print the formula */
		_LOG_DATA "    Hot Spot Formula =" );
		//PrintFormula ( p, cdHotSpot.DataLength );
	}
    else  /* data is text */
    {
		_LOG_DATA "Hot Spot Text :" );
		Dump_Text((char*)dump_ptr,pcd->hotspot_begin.DataLength);
	//PrintText( (char far *)p,  cdHotSpot.DataLength );
    }
	return ERR_OK;

}

DWORD CLotusItem::Data_Reset(DWORD max_size)
{
	if (max_size == 0) max_size = 1*1024*1024;	//1MB
	m_mem_data.Release();
	m_mem_data.SetMaxMemorySize(max_size);
	m_mem_data.SetElementSize(1);
	m_mem_data.SetSize(1);
	m_data_size = 0;
	m_data_start = (BYTE*)m_mem_data.GetMemBuffer();
	m_data_ptr	= m_data_start;
	data_type = TYPE_COMPOSITE;
	return ERR_OK;
}

DWORD CLotusItem::Data_Add(_CD *pcd,void* pdata)
{
	DWORD	size;
	int		i;
	struct _sig_dt* sig_size = getSigData();

	size = pcd->Length;
	if (size%2) size++;
	m_data_size+= size;
	m_mem_data.SetSize(m_data_size);
	if ((DWORD)m_data_ptr%2) m_data_ptr++;

	for (i=0;(sig_size[i].sig | sig_size[i].size | sig_size[i].ods_type) != 0;i++)
	{
		if (sig_size[i].sig == pcd->Signature) break;
	}
	if (sig_size[i].size == 0)
	{
		sprintf(m_err_msg,"CLotusItem::Data_Add failed ... invalid signature type (%u)",pcd->Signature);
		return ERR_PARAM;
	};
	ODSWriteMemory(&m_data_ptr,sig_size[i].ods_type,pcd->data,1);
	//m_data_ptr+= sig_size[i].size;
	// escribir los datos extras que faltan para completar la signatura
	
	size -= sig_size[i].size;
	if (pdata != NULL) memcpy(m_data_ptr,pdata,size);
	m_data_ptr+= size;
	return ERR_OK;
}

DWORD CLotusItem::AddToNote(char *item_name, WORD item_flags)
{
	if (m_pnote->ItemAdd(item_name,data_type,item_flags,(char*)m_data_start,m_data_size) != ERR_OK) return _LOG_AT;
	return ERR_OK;
}

DWORD CLotusItem::Dump_Text(char *str, DWORD size)
{
	char	*cptr;
	int		i;
	i = 0;
	cptr = str;
	for (;;)
	{
		if (cptr >= str+size) break;
		_LOG_DATA "(%d) = %s ",i,cptr);
		i++;
		cptr = strchr(cptr,0);
		cptr++;
		
	}
	return ERR_OK;
}

DWORD CLotusItem::Dump_CDTEXT(_CD *pcd)
{
	_LOG_DATA "*** TEXT ***");
	_LOG_DATA "FontID = %d",pcd->text.FontID);
	Dump_Text((char*)dump_ptr,pcd->text.Header.Length - sizeof(pcd->text));
	return ERR_OK;
}

DWORD CLotusItem::Dump_LogData()
{
	if ((data_type == TYPE_TEXT) || (data_type == TYPE_TEXT_LIST))
	{
		return Dump_Text((char*)m_last_ptr,m_data_size);
	}
	return ERR_FATAL;	
}

DWORD CLotusItem::Dump_CDBITMAPHEADER(_CD *pcd)
{
	_LOG_DATA "*** BITMAPHEADER ***");
	_LOG_DATA "DestSize = (%u,%u)",pcd->bitmap_header.Dest.width,pcd->bitmap_header.Dest.height);
	_LOG_DATA "Crop = (%u,%u)",pcd->bitmap_header.Crop.width,pcd->bitmap_header.Crop.height);
	_LOG_DATA "Width = %d",pcd->bitmap_header.Width);
	_LOG_DATA "Height = %d",pcd->bitmap_header.Height);
	_LOG_DATA "BitsPerPixel = %d",pcd->bitmap_header.BitsPerPixel);
	_LOG_DATA "SamplesPerPixel = %d",pcd->bitmap_header.SamplesPerPixel);
	_LOG_DATA "SegmentCount = %d",pcd->bitmap_header.SegmentCount);
	_LOG_DATA "BitsPerSample = %d",pcd->bitmap_header.BitsPerSample);
	_LOG_DATA "SegmentCount = %d",pcd->bitmap_header.SegmentCount);
	_LOG_DATA "PatternCount = %d",pcd->bitmap_header.PatternCount);
	return ERR_OK;
}

DWORD CLotusItem::Dump_CDBITMAPSEGMENT(_CD *pcd)
{
	_LOG_DATA "*** BITSEGMENT ***");
	_LOG_DATA "ScanlineCount = %d",pcd->bitmap_segment.ScanlineCount);
	_LOG_DATA "DataSize = %d",pcd->bitmap_segment.DataSize);
	return ERR_OK;
}



struct _sig_dt* CLotusItem::getSigData()
{
	static struct _sig_dt sig_size[] = {
				{SIG_CD_BACKGROUNDCOLOR,	sizeof(CDCOLOR),_CDCOLOR},
				{SIG_CD_BEGIN,				sizeof(CDBEGINRECORD),_CDBEGINRECORD},
				{SIG_CD_BIDI_TEXT,			sizeof(CDTEXT),_CDTEXT},
				{SIG_CD_BIDI_TEXTEFFECT,	sizeof(CDTEXTEFFECT),_CDTEXTEFFECT},
				{SIG_CD_CLIENT_BLOBPART,	sizeof(CDBLOBPART),_CDBLOBPART},
				{SIG_CD_CLIENT_EVENT,		sizeof(CDEVENT),_CDEVENT},
				{SIG_CD_END,				sizeof(CDENDRECORD),_CDENDRECORD},
				{SIG_CD_EVENT_LANGUAGE_ENTRY,sizeof(CDEVENTENTRY),_CDEVENTENTRY},
				{SIG_CD_EXT_EMBEDDEDSCHED,	sizeof(CDEMBEDDEDSCHEDCTLEXTRA),_CDEMBEDDEDSCHEDCTLEXTRA},
				{SIG_CD_FLOATPOSITION,		sizeof(CDFLOAT),_CDFLOAT},
				{SIG_CD_HORIZONTALRULE,		sizeof(CDHRULE),_CDHRULE},
#ifdef LOTUS6
				SIG_SIZE(ACTIONBAREXT),
				SIG_SIZE(ACTIONEXT),
				{SIG_CD_HREFBORDER,			sizeof(CDRESOURCE),_CDRESOURCE},
				{SIG_CD_TABLECELL_HREF,		sizeof(CDRESOURCE),_CDRESOURCE},
				{SIG_CD_TABLECELL_HREF2,	sizeof(CDRESOURCE),_CDRESOURCE},
				{SIG_CD_HREF2,				sizeof(CDRESOURCE),_CDRESOURCE},
#endif
				{SIG_CD_LARGE_PARAGRAPH,	sizeof(CDLARGEPARAGRAPH),_CDLARGEPARAGRAPH},
				{SIG_CD_NESTEDTABLEBEGIN,	sizeof(CDTABLEBEGIN),_CDTABLEBEGIN},
				{SIG_CD_NESTEDTABLECELL,	sizeof(CDTABLECELL),_CDTABLECELL},
				{SIG_CD_NESTEDTABLEEND,		sizeof(CDTABLEEND),_CDTABLEEND},
				{SIG_CD_SPAN_BEGIN,			sizeof(CDSPANRECORD),_CDSPANRECORD},
				{SIG_CD_SPAN_END,			sizeof(CDSPANRECORD),_CDSPANRECORD},
				{SIG_CD_TABLECELL_COLOR,	sizeof(CDCOLOR),_CDCOLOR},

				{SIG_CD_TABLECELL_IDNAME,	sizeof(CDIDNAME),_CDIDNAME},
				{SIG_CD_TARGET_DBLCLK,		sizeof(CDTARGET),_CDTARGET},
				{SIG_CD_V4HOTSPOTBEGIN,		sizeof(CDHOTSPOTBEGIN),_CDHOTSPOTBEGIN},
				{SIG_CD_V5HOTSPOTBEGIN,		sizeof(CDHOTSPOTBEGIN),_CDHOTSPOTBEGIN},
				{SIG_CD_V5HOTSPOTEND,		sizeof(CDHOTSPOTEND),_CDHOTSPOTEND},
				{SIG_CD_V6HOTSPOTBEGIN_CONTINUATION,sizeof(CDHOTSPOTBEGIN),_CDHOTSPOTBEGIN},
				SIG_SIZE(HOTSPOTEND),
				SIG_SIZE(TEXTEFFECT),
				SIG_SIZE(HOTSPOTBEGIN),
				SIG_SIZE(ALTERNATEBEGIN),
				SIG_SIZE(ALTERNATEEND),
				SIG_SIZE(ALTTEXT),
				SIG_SIZE(ANCHOR),
				SIG_SIZE(BACKGROUNDPROPERTIES),
				SIG_SIZE(BACKGROUNDPROPERTIES),
				SIG_SIZE(BAR),
				SIG_SIZE(BAR),
				SIG_SIZE(BITMAPHEADER),
				SIG_SIZE(BITMAPSEGMENT),
				SIG_SIZE(BOXSIZE),
				SIG_SIZE(CAPTION),
				SIG_SIZE(CGMMETA),
				SIG_SIZE(COLORTABLE),
				SIG_SIZE(DATAFLAGS),
				SIG_SIZE(DECSFIELD),
				SIG_SIZE(EMBEDDEDCALCTL),
				SIG_SIZE(FILEHEADER),
				SIG_SIZE(FILESEGMENT),
				SIG_SIZE(GRAPHIC),
				SIG_SIZE(HEADER),
				SIG_SIZE(HTMLBEGIN),
				SIG_SIZE(HTMLEND),
				SIG_SIZE(HTMLFORMULA),
				SIG_SIZE(IDNAME),
				SIG_SIZE(IGNORE),
				SIG_SIZE(IMAGEHEADER),
				SIG_SIZE(IMAGESEGMENT),
				SIG_SIZE(INLINE),
				SIG_SIZE(LAYER),
				SIG_SIZE(LINKCOLORS),
				SIG_SIZE(LINKEXPORT2),
				SIG_SIZE(MACMETAHEADER),
				SIG_SIZE(MACMETASEG),
				SIG_SIZE(PABDEFINITION),
				SIG_SIZE(PABREFERENCE),
				SIG_SIZE(PARAGRAPH),
				SIG_SIZE(PMMETAHEADER),
				SIG_SIZE(PMMETASEG),
				SIG_SIZE(POSITIONING),
				SIG_SIZE(STORAGELINK),
				SIG_SIZE(STYLENAME),
				SIG_SIZE(TABLEBEGIN),
				SIG_SIZE(TABLECELL),
				SIG_SIZE(TABLEDATAEXTENSION),
				SIG_SIZE(TABLEEND),
				SIG_SIZE(TEXT),
				SIG_SIZE(TEXTPROPERTIESTABLE),
				SIG_SIZE(TEXTPROPERTY),
				SIG_SIZE(TRANSPARENTTABLE),
				SIG_SIZE(WINMETAHEADER),
				SIG_SIZE(WINMETASEG),
				SIG_SIZE(COLOR),
				SIG_SIZE(BLOBPART),
				SIG_SIZE(VERTICALALIGN),
				SIG_SIZE(TIMERINFO),
				SIG_SIZE(TABLEROWHEIGHT),
				SIG_SIZE(TABLELABEL),
				/*

#define SIG_CD_			(220 | WORDRECORDLENGTH)
#define SIG_CD_			(221 | BYTERECORDLENGTH)
#define SIG_CD_				(222 | BYTERECORDLENGTH)
#define SIG_CD_	(223 | BYTERECORDLENGTH)
#define SIG_CD_ 	(224 | BYTERECORDLENGTH)

#define SIG_CD_		(225 | BYTERECORDLENGTH)
#define SIG_CD_	(226 | BYTERECORDLENGTH)
#define SIG_CD_		(227 | WORDRECORDLENGTH)
#define SIG_CD_		(228 | WORDRECORDLENGTH)
#define SIG_CD_  (229 | WORDRECORDLENGTH)
#define SIG_CD_REGIONBEGIN		(230 | WORDRECORDLENGTH)
#define SIG_CD_REGIONEND		(231 | WORDRECORDLENGTH)
#define SIG_CD_TRANSITION		(232 | WORDRECORDLENGTH)
#define SIG_CD_FIELDHINT		(233 | WORDRECORDLENGTH)
#define SIG_CD_PLACEHOLDER		(234 | WORDRECORDLENGTH)
#define SIG_CD_EMBEDDEDOUTLINE	(236 | WORDRECORDLENGTH)
#define SIG_CD_EMBEDDEDVIEW		(237 | WORDRECORDLENGTH)
#define SIG_CD_CELLBACKGROUNDDATA	(238 | WORDRECORDLENGTH)

#define SIG_CD_FRAMESETHEADER	(239 | WORDRECORDLENGTH)
#define SIG_CD_FRAMESET			(240 | WORDRECORDLENGTH)
#define SIG_CD_FRAME			(241 | WORDRECORDLENGTH)

#define SIG_CD_TARGET			(242 | WORDRECORDLENGTH)

#define SIG_CD_MAPELEMENT		(244 | WORDRECORDLENGTH)
#define SIG_CD_AREAELEMENT		(245 | WORDRECORDLENGTH)
#define SIG_CD_HREF				(246 | WORDRECORDLENGTH)
#define SIG_CD_EMBEDDEDCTL		(247 | WORDRECORDLENGTH)
#define SIG_CD_HTML_ALTTEXT		(248 | WORDRECORDLENGTH)
#define SIG_CD_EVENT			(249 | WORDRECORDLENGTH)
#define SIG_CD_PRETABLEBEGIN	(251 | WORDRECORDLENGTH)
#define SIG_CD_BORDERINFO		(252 | WORDRECORDLENGTH)
#define SIG_CD_EMBEDDEDSCHEDCTL	(253 | WORDRECORDLENGTH)

#define SIG_CD_EXT2_FIELD		(254 | WORDRECORDLENGTH)	
#define SIG_CD_EMBEDDEDEDITCTL	(255 | WORDRECORDLENGTH)


#define	SIG_CD_DOCUMENT_PRE_26	(128 | BYTERECORDLENGTH)
#define	SIG_CD_FIELD_PRE_36		(132 | WORDRECORDLENGTH)
#define	SIG_CD_FIELD			(138 | WORDRECORDLENGTH)
#define	SIG_CD_DOCUMENT			(134 | BYTERECORDLENGTH)
#define	SIG_CD_METAFILE			(135 | WORDRECORDLENGTH)
#define	SIG_CD_BITMAP			(136 | WORDRECORDLENGTH)
#define	SIG_CD_FONTTABLE		(139 | WORDRECORDLENGTH)
#define	SIG_CD_LINK				(140 | BYTERECORDLENGTH)
#define	SIG_CD_LINKEXPORT		(141 | BYTERECORDLENGTH)
#define	SIG_CD_KEYWORD			(143 | WORDRECORDLENGTH)
#define	SIG_CD_LINK2			(145 | WORDRECORDLENGTH)
#define	SIG_CD_CGM				(147 | WORDRECORDLENGTH)
#define	SIG_CD_TIFF				(148 | LONGRECORDLENGTH)
#define SIG_CD_PATTERNTABLE	    (152 | LONGRECORDLENGTH)
#define SIG_CD_DDEBEGIN			(161 | WORDRECORDLENGTH)
#define SIG_CD_DDEEND			(162 | WORDRECORDLENGTH)
#define SIG_CD_OLEBEGIN			(167 | WORDRECORDLENGTH)
#define SIG_CD_OLEEND			(168 | WORDRECORDLENGTH)
#define SIG_CD_HOTSPOTBEGIN		(169 | WORDRECORDLENGTH)
#define SIG_CD_BUTTON			(171 | WORDRECORDLENGTH)
#define SIG_CD_BAR				(172 | WORDRECORDLENGTH)
#define SIG_CD_V4HOTSPOTBEGIN	(173 | WORDRECORDLENGTH)
#define SIG_CD_V4HOTSPOTEND		(174 | BYTERECORDLENGTH)
#define SIG_CD_EXT_FIELD		(176 | WORDRECORDLENGTH)
#define SIG_CD_LSOBJECT			(177 | WORDRECORDLENGTH)
#define SIG_CD_HTMLHEADER		(178 | WORDRECORDLENGTH)
#define SIG_CD_HTMLSEGMENT		(179 | WORDRECORDLENGTH)
#define SIG_CD_LAYOUT			(183 | BYTERECORDLENGTH)
#define SIG_CD_LAYOUTTEXT		(184 | BYTERECORDLENGTH)
#define SIG_CD_LAYOUTEND		(185 | BYTERECORDLENGTH)
#define SIG_CD_LAYOUTFIELD		(186 | BYTERECORDLENGTH)
#define SIG_CD_PABHIDE			(187 | WORDRECORDLENGTH)
#define SIG_CD_PABFORMREF		(188 | BYTERECORDLENGTH)
#define SIG_CD_ACTIONBAR		(189 | BYTERECORDLENGTH)
#define SIG_CD_ACTION			(190 | WORDRECORDLENGTH)

#define SIG_CD_DOCAUTOLAUNCH	(191 | WORDRECORDLENGTH)
#define SIG_CD_LAYOUTGRAPHIC	(192 | BYTERECORDLENGTH)
#define SIG_CD_OLEOBJINFO		(193 | WORDRECORDLENGTH)
#define SIG_CD_LAYOUTBUTTON		(194 | BYTERECORDLENGTH)
#define SIG_CD_TEXTEFFECT		(195 | WORDRECORDLENGTH)

#define SIG_QUERY_HEADER		(129 | BYTERECORDLENGTH)
#define SIG_QUERY_TEXTTERM		(130 | WORDRECORDLENGTH)
#define SIG_QUERY_BYFIELD		(131 | WORDRECORDLENGTH)
#define SIG_QUERY_BYDATE		(132 | WORDRECORDLENGTH)
#define SIG_QUERY_BYAUTHOR		(133 | WORDRECORDLENGTH)
#define SIG_QUERY_FORMULA		(134 | WORDRECORDLENGTH)
#define SIG_QUERY_BYFORM		(135 | WORDRECORDLENGTH)
#define SIG_QUERY_BYFOLDER		(136 | WORDRECORDLENGTH)
#define SIG_QUERY_USESFORM		(137 | WORDRECORDLENGTH)
#define SIG_QUERY_TOPIC			(138 | WORDRECORDLENGTH)


#define SIG_ACTION_HEADER		(129 | BYTERECORDLENGTH)
#define SIG_ACTION_MODIFYFIELD	(130 | WORDRECORDLENGTH)
#define SIG_ACTION_REPLY		(131 | WORDRECORDLENGTH)
#define SIG_ACTION_FORMULA		(132 | WORDRECORDLENGTH)
#define SIG_ACTION_LOTUSSCRIPT	(133 | WORDRECORDLENGTH)
#define SIG_ACTION_SENDMAIL		(134 | WORDRECORDLENGTH)
#define SIG_ACTION_DBCOPY		(135 | WORDRECORDLENGTH)
#define SIG_ACTION_DELETE		(136 | BYTERECORDLENGTH)
#define SIG_ACTION_BYFORM		(137 | WORDRECORDLENGTH)
#define SIG_ACTION_MARKREAD		(138 | BYTERECORDLENGTH)
#define SIG_ACTION_MARKUNREAD	(139 | BYTERECORDLENGTH)
#define SIG_ACTION_MOVETOFOLDER	(140 | WORDRECORDLENGTH)
#define SIG_ACTION_COPYTOFOLDER	(141 | WORDRECORDLENGTH)
#define SIG_ACTION_REMOVEFROMFOLDER	(142 | WORDRECORDLENGTH)
#define SIG_ACTION_NEWSLETTER	(143 | WORDRECORDLENGTH)
#define SIG_ACTION_RUNAGENT		(144 | WORDRECORDLENGTH)
#define SIG_ACTION_SENDDOCUMENT	(145 | BYTERECORDLENGTH)
#define SIG_ACTION_FORMULAONLY	(146 | WORDRECORDLENGTH)
#define SIG_ACTION_JAVAAGENT	(147 | WORDRECORDLENGTH)
#define SIG_ACTION_JAVA			(148 | WORDRECORDLENGTH)


#define SIG_VIEWMAP_DATASET	(87 | WORDRECORDLENGTH)

#define SIG_CD_VMHEADER			(175 | BYTERECORDLENGTH)
#define SIG_CD_VMBITMAP			(176 | BYTERECORDLENGTH)
#define SIG_CD_VMRECT			(177 | BYTERECORDLENGTH)
#define SIG_CD_VMPOLYGON_BYTE	(178 | BYTERECORDLENGTH)
#define SIG_CD_VMPOLYLINE_BYTE	(179 | BYTERECORDLENGTH)
#define SIG_CD_VMREGION			(180 | BYTERECORDLENGTH)
#define SIG_CD_VMACTION			(181 | BYTERECORDLENGTH)
#define SIG_CD_VMELLIPSE		(182 | BYTERECORDLENGTH)
#define SIG_CD_VMRNDRECT		(184 | BYTERECORDLENGTH)
#define SIG_CD_VMBUTTON			(185 | BYTERECORDLENGTH)
#define SIG_CD_VMACTION_2		(186 | WORDRECORDLENGTH)
#define SIG_CD_VMTEXTBOX		(187 | WORDRECORDLENGTH)
#define SIG_CD_VMPOLYGON 		(188 | WORDRECORDLENGTH)
#define SIG_CD_VMPOLYLINE		(189 | WORDRECORDLENGTH)
#define SIG_CD_VMPOLYRGN		(190 | WORDRECORDLENGTH)
#define SIG_CD_VMCIRCLE			(191 | BYTERECORDLENGTH)
#define SIG_CD_VMPOLYRGN_BYTE	(192 | BYTERECORDLENGTH)


#define SIG_CD_ALTERNATEBEGIN	(198 | WORDRECORDLENGTH)
#define SIG_CD_ALTERNATEEND		(199 | BYTERECORDLENGTH)

#define SIG_CD_OLERTMARKER		(200 | WORDRECORDLENGTH)
*/

				((WORD)0,(BYTE)0,(WORD)0)
				};
				return sig_size;

}
