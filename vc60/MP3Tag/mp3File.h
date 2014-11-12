// mp3File.h: interface for the Cmp3File class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MP3FILE_H__DD57FF48_961D_4877_939B_FD24C139BFF6__INCLUDED_)
#define AFX_MP3FILE_H__DD57FF48_961D_4877_939B_FD24C139BFF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

typedef struct 
{
	bool	bvalid;			// indica que la informacion es valida
	char	Title[31];
	char	Artist[31];
	char	Album[31];
	char	Year[5];
	char	Comment[29];
	BYTE	TrackNumber;
	BYTE	Genre;
}ID3_v1;

typedef struct 
{
	bool	bvalid;			// indica que la informacion es valida
	char	title[50];
	char	Artist[50];
	char	Album[50];
	char	Year[50];
	char	Comment[50];
	char	TrackNumber[50];
	char	Genre[50];
}ID3_v2;

// ebn la version 2 del id3 hay que ver el tipo de encode que utiliza.

class Cmp3File : public CbObject  
{
public:
	DWORD FWrite_ID3v1();
	DWORD Make_ID3v1(char* tag);
	DWORD Read_ID3v1();
	DWORD File_Close();
	DWORD File_Open(char *file_apth);
	Cmp3File();
	virtual ~Cmp3File();
private:
	HANDLE	m_hfile;
	char	m_file_path[MAX_PATH];
	int		m_id3_type;
	ID3_v1	m_tag_v1;
	ID3_v2	m_tag_v2;
	BOOL	m_bchange;	//indica que se han cambiado propiedades en el ID3
};

#endif // !defined(AFX_MP3FILE_H__DD57FF48_961D_4877_939B_FD24C139BFF6__INCLUDED_)
