// Utils.h: interface for the CUtils class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTILS_H__49D258DE_EF9D_44F8_8D9E_EE2B37E435F8__INCLUDED_)
#define AFX_UTILS_H__49D258DE_EF9D_44F8_8D9E_EE2B37E435F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bobject.h"
#include "sys/stat.h"

typedef struct
{
	char	file_path[MAX_PATH];
	time_t	accessed;
	time_t	modified;
	time_t	created;
}FILEDATA;

class CUtils  : public CbObject
{
public:
	DWORD DateTime_to_Str(struct tm *time, char *dt_str, int size);
	DWORD Date_to_Str(struct tm *time,char *dt_str,int size);
	DWORD DateTime_get_Current(char* dt_str,DWORD size);
	DWORD Byte_to_hex(BYTE* data,DWORD size,char* str,DWORD slen);
	DWORD App_Execute(char *path, char *arg);
	void CharGet_FreeBSTR(BSTR bstr,char* str,int maxsize);
	BSTR BSTR_Get(char* str);
	DWORD Buffer_to_File(char* file_path,BYTE *buffer, DWORD size);
	DWORD File_Copy(char* source,char* dest,BOOL overwrite = true);
	void	Char_Rtrim(char* str);
	void	Big_HEX_to_Number(char* hex_num,BYTE* number, BYTE max);
	void	Big_GetDecimal(BYTE *number, BYTE dsize, char *decimal, BYTE max);
	void	Big_Div_8(BYTE *dividend, BYTE dsize, BYTE divisor, BYTE *quotient, BYTE *remainder);
	DWORD	CoInitialize();
	DWORD	Char_Get(unsigned short *u_str,char* str,int maxsize,int u_size = -1);
	DWORD	WChar_Get(char* cstr, unsigned short *ustr, int maxsize);
	DWORD	Folder_Create(char* folder_path);
	DWORD	File_IsValid(char *file_path);
	DWORD	File_Delete(char* file_path);
	DWORD	Resource_ToFile(char* res_type,char* res_name,char* file_path, HMODULE hModule = NULL);
	char*	File_ClearName(char* file_path);
	char*	File_GetName(char *file_path);
	void	Window_Center(HWND hwnd);
	DWORD	File_GetInformation(FILEDATA* file_data);

	CUtils();
	virtual ~CUtils();

};

extern CUtils	gutils;

#endif // !defined(AFX_UTILS_H__49D258DE_EF9D_44F8_8D9E_EE2B37E435F8__INCLUDED_)
