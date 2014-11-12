// mp3File.cpp: implementation of the Cmp3File class.
//
//////////////////////////////////////////////////////////////////////

#include "mp3File.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cmp3File::Cmp3File()
{
	m_hfile = NULL;
	m_id3_type = 0;
	m_bchange = false;
	ZERO(m_tag_v1);
	ZERO(m_tag_v2);

}

Cmp3File::~Cmp3File()
{
	File_Close();
}

DWORD Cmp3File::File_Open(char *file_path)
{
	char	*fnc_name = "Cmp3File::File_Open";
	char	tag[150];
	DWORD	count;
	bool	berr;

	File_Close();
	m_hfile = CreateFile(file_path,GENERIC_WRITE|GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (m_hfile == INVALID_HANDLE_VALUE) 
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s->CreateFile for %s ",fnc_name,file_path);
	
	Read_ID3v1();
	File_Close();
	return ERR_OK;
}

DWORD Cmp3File::File_Close()
{
	if (m_hfile != NULL) CloseHandle(m_hfile);
	m_hfile = NULL;
	return ERR_OK;	
}

DWORD Cmp3File::Read_ID3v1()
{
	char	*fnc_name = "Cmp3File::Read_ID3v1";
	char	tag[129];
	DWORD	count;

	ZERO(m_tag_v1);
	SetFilePointer(m_hfile,-128,0,FILE_END);
	if (!ReadFile(m_hfile,tag,128,&count,NULL)) 
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s->ReadFile 128 bytes ",fnc_name);;
	if (count != 128) 
		return 	SetError(true,ERR_FATAL,"%s readed %d bytes of 128",fnc_name,count);
	if (strncmp(tag,"TAG",3) != 0)
	{
		m_plog->_log(LOG_TRACE,"%s ID3v1 is Missing",fnc_name);
		return ERR_FATAL;
	}

	strncat(m_tag_v1.Title,		tag+3,	sizeof(m_tag_v1.Title)-1);
	strncat(m_tag_v1.Artist,	tag+33,	sizeof(m_tag_v1.Artist)-1);
	strncat(m_tag_v1.Album,		tag+63,	sizeof(m_tag_v1.Album)-1);
	strncat(m_tag_v1.Year,		tag+93,	sizeof(m_tag_v1.Year)-1);
	strncat(m_tag_v1.Comment,	tag+97,	sizeof(m_tag_v1.Comment)-1);
	m_tag_v1.TrackNumber = (BYTE)tag[126];
	m_tag_v1.Genre = (BYTE)tag[127];
	m_tag_v1.bvalid = true;
	m_id3_type = 1;
		
	return ERR_OK;
}

DWORD Cmp3File::Make_ID3v1(char *tag)
{
	char	*fnc_name = "Cmp3File::Make_ID3v1";

	memset(tag,128,0);
	if (!m_tag_v1.bvalid) 
		return SetError(true,ERR_FATAL,"%s ID3 Tag v1 is invalid",fnc_name);
	strcpy(tag,"TAG");
	strcpy(tag+3,m_tag_v1.Title);
	strcpy(tag+33,m_tag_v1.Artist);
	strcpy(tag+63,m_tag_v1.Album);
	strcpy(tag+93,m_tag_v1.Year);
	strcpy(tag+97,m_tag_v1.Comment);
	tag[126] = m_tag_v1.TrackNumber;
	tag[127] = m_tag_v1.Genre;
	return ERR_OK;
}

/*
	escribir en el fichero la informacion del ID3
*/
DWORD Cmp3File::FWrite_ID3v1()
{
	char	buf[5];
	char	*fnc_name = "Cmp3File::FWrite_ID3v1";
	DWORD	count;

	if (m_hfile == NULL) return SetError(true,ERR_FATAL,"%s file is closed",fnc_name);
	if (m_bchange == 0) return ERR_OK;
	SetFilePointer(m_hfile,-128,0,FILE_END);
	if (!ReadFile(m_hfile,buf,3,&count,NULL)) 
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s->ReadFile 3 bytes ",fnc_name);
	if (strcmp(buf,"TAG") != 0)
	{
		// el fichero no tiene definido un TAG
		SetFilePointer(m_hfile,0,0,FILE_END);
		if (!WriteFile(m_hfile,"TAG",3,&count,NULL)) 
			return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s->WriteFile 3 bytes ",fnc_name);
	}
	if (!WriteFile
	return ERR_OK;
}
