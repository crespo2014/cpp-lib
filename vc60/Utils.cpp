// Utils.cpp: implementation of the CUtils class.
//
//////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "time.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUtils	gutils;

CUtils::CUtils()
{

}

CUtils::~CUtils()
{

}

void CUtils::Window_Center(HWND hwnd)
{
	RECT	prect;
	RECT	wrect;
	int		Xo,Yo;
	HWND	phwnd;
	if (hwnd == NULL) return;
	phwnd = ::GetParent(hwnd); 
	if (phwnd == NULL) phwnd = GetDesktopWindow();
	if (phwnd == NULL) return;
	if (!::GetWindowRect(phwnd,&prect)) return;
	if (!::GetWindowRect(hwnd,&wrect)) return;
	Xo = ((prect.right - prect.left) - (wrect.right - wrect.left))/2;
	Yo = ((prect.bottom - prect.top) - (wrect.bottom - wrect.top))/2;
	::MoveWindow(hwnd,Xo,Yo,wrect.right - wrect.left,wrect.bottom - wrect.top,false);	
}

char* CUtils::File_GetName(char *file_path)
{
	char*	file_name;
	char*	cptr;
	cptr = file_path;
	for (;;)
	{
		file_name = cptr;
		cptr = strstr(cptr,"\\");
		if (cptr == NULL) break;
		cptr++;
	}
	return file_name;	
}

DWORD CUtils::File_GetInformation(FILEDATA* file_data)
{
	struct _stat	data;
	if (_stat(file_data->file_path,&data) == 0)
	{
		file_data->accessed = data.st_atime;
		file_data->created	= data.st_ctime;
		file_data->modified = data.st_mtime;
		return ERR_OK;
	}
	return SetError(false,ERR_API,"CUtils::GetFileInformation -> _stat(%s) ... failed",file_data->file_path);
}

char* CUtils::File_ClearName(char *file_path)
{
	char*	cptr;
	char*	cptr2;
	cptr = strstr(file_path,"\\");if (cptr == NULL) return NULL;
	for (;;)
	{
		cptr2 = cptr + 1;
		cptr2 = strstr(cptr2,"\\");
		if (cptr2 == NULL) 
		{
			*cptr = 0;
			cptr ++;
			return cptr;
		}
		cptr = cptr2;
	}
//	return NULL;	
}

DWORD CUtils::Resource_ToFile(char *res_type, char* res_name, char *file_path, HMODULE hModule)
{
	HRSRC	hres;
	HGLOBAL	hglobal;
	void	*res_data;
	DWORD	res_size;
	DWORD	file_size;
	FILE*	hfile;

	hres = FindResource(hModule,res_name,res_type);
	if (hres == NULL) return SetError_Add_W32_code_msg(false,ERR_API,GetLastError(),"CUtils::ResourceToFile ->FindResource (%s,%s) ",res_name,res_type);
	hglobal = LoadResource(hModule,hres);
	if (hglobal == NULL) return SetError_Add_W32_code_msg(false,ERR_API,GetLastError(),"CUtils::ResourceToFile ->LoadResource ");
	res_data = LockResource(hglobal);
	res_size = SizeofResource(hModule,hres);
	hfile = fopen(file_path,"wb");
	if (hfile == NULL)	return SetError(false,ERR_API,"CUtils::ResourceToFile -> fopen (%s) ",file_path);
	file_size = fwrite(res_data,1,res_size,hfile);
	fclose(hfile);
	if (file_size != res_size) return SetError(false,ERR_API,"CUtils::ResourceToFile -> fwrite failed by %u bytes",res_size-file_size);
	return ERR_OK;
}

DWORD CUtils::File_Delete(char *file_path)
{
	if (::DeleteFile(file_path)) return ERR_OK;
	return SetError_Add_W32_code_msg(false,ERR_API,GetLastError(),"CUtils::DeleteFile (%s) failed ",file_path);
}

DWORD CUtils::File_IsValid(char *file_path)
{
	DWORD	fa;
	fa = GetFileAttributes(file_path);
	if (fa == INVALID_FILE_ATTRIBUTES) return ERR_FATAL;
	if (fa & FILE_ATTRIBUTE_DIRECTORY) return ERR_FATAL;
	return ERR_OK;
}

DWORD CUtils::Folder_Create(char *folder_path)
{
	DWORD	dwr;
	dwr = GetFileAttributes(folder_path); 
	if (dwr == INVALID_FILE_ATTRIBUTES)
	{
		// no esta la carpeta
		if (!CreateDirectory(folder_path,NULL)) return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CUtils::Folder_Create CreateDirectory(%s) ... ",folder_path);
		return ERR_OK;
	}
	if (dwr & FILE_ATTRIBUTE_DIRECTORY) return ERR_OK;
	return SetError(true,ERR_FATAL,"%s is not a File Folder",folder_path);
}

DWORD CUtils::WChar_Get(char *cstr, unsigned short *ustr, int maxsize)
{
	int	i;
	//int	len = strlen(cstr);
	i = MultiByteToWideChar(CP_ACP,0,cstr,-1/*len*/,ustr,maxsize);
	if ( i == 0) 
	{
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CUtils::GetWChar ... failed ");
	}
	ustr[i] = 0;	// fin de la cadena
	return ERR_OK;
}

DWORD CUtils::Char_Get(unsigned short *u_str, char *str, int maxsize, int u_size)
{
	int	i;
	str[0] = 0;
	if (u_str == NULL) return ERR_OK;
	i = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)u_str,u_size,str,maxsize,NULL,NULL);
	if ((i == 0) || (i ==  maxsize))
	{
		return SetError(true,ERR_FATAL,"CUtils::GetChar ... WideCharToMultiByte string has been truncate");
	}
	if (u_size != -1) str[i] = 0;
	return ERR_OK;
}

DWORD CUtils::CoInitialize()
{
	HRESULT	hr;
	hr = ::CoInitialize(NULL);
	if (hr != S_OK) return SetError(true,ERR_API,"CUtils::CoInitialize ... failed with code %X",hr);
	return ERR_OK;
}

void CUtils::Big_Div_8(BYTE *dividend, BYTE dsize, BYTE divisor, BYTE *quotient, BYTE *remainder)
{
	BYTE	num_size;
	BYTE	reminder;
	memset(quotient,0,dsize);

	_asm
	{
		mov dh,0;
		xor ecx,ecx;
		mov cl,dsize;
		mov eax,dividend;
		mov dl,0;
loop_0:
		cmp [eax],byte ptr 0;
		je nxt_0;
		mov dh,dl;
nxt_0:
		inc eax;
		inc dl;
		loop loop_0;
		inc dh;
		mov num_size,dh	//cantidad de bytes validos * 8 cantidad de bits
		mov al,8;
		mul dh;
		mov cx,ax		// tamaño en bits del numero	
		mov bl,divisor	//divisor
		mov bh,0	// reminder
loop_1:
		// rotar el dividendo y pasar el bit al reminder
		clc;
		mov eax,dividend;
		call rot_19;
		rcl bh,1;
		// comparar los numeros
		cmp bh,bl;
		jb menor;
		sub bh,bl;
		stc;
		jmp rotar
menor:
		clc;
rotar:		
		mov eax,quotient;
		call rot_19;
		loop loop_1;
		jmp end_;

rot_19:	//rotar los dl numeros apuntados por eax a traves del CF
		push cx;
		mov ecx,0
		mov cl,num_size;
l_1:
		rcl byte ptr [eax],1;
		inc eax;
		loop l_1;
		pop cx;
		ret;
end_:
		mov reminder,bh;
	}
	*remainder = reminder;

}

void CUtils::Big_GetDecimal(BYTE *number, BYTE dsize, char *decimal, BYTE max)
{
	BYTE is0;
	BYTE res[20];
	BYTE resto;
	char str[40];
	int	i,k;
	k = 0;
	if (dsize > sizeof(res)) dsize = sizeof(res);
	do
	{
		Big_Div_8(number,dsize,10,res,&resto);
		str[k] = (char)(resto+0x30);
		k++;
		if (k == sizeof(str)) break;
	_asm{
			lea eax,[res];
			mov ecx,0
			mov cl,dsize;
			mov bh,0;
	lp_1:
			or bh,[eax];
			inc eax;
			loop lp_1;
			mov is0,bh;		
		}
		memcpy(number,res,dsize);
	} while (is0 != 0);
	i = 0;
	
	while (k>0)
	{
		k--;
		decimal[i] = str[k];
		i++;
		if (i == max-1) break;
		
	}
	decimal[i] = 0;

}

void CUtils::Big_HEX_to_Number(char *hex_num, BYTE *number, BYTE max)
{
	char	*cptr;
	BYTE	val;
	int		i,j;

	memset(number,0,max);
	i = strlen(hex_num);
	i--;
	j = 0;
	cptr = hex_num;
	while (i >= 0)
	{
		val = (char)(hex_num[i] - 0x30);
		if (val > 9) val = (char)(hex_num[i] - 'A'+10);
		if (val > 15) return;	// error en el caracter recivido se aborta
		number[j] = val;
		i--; 
		if (i < 0) break;
		val = (char)(hex_num[i] - 0x30);
		if (val > 9) val = (char)(hex_num[i] - 'A'+10);
		if (val > 15) return;	// error en el caracter recivido se aborta
		number[j] = (char)(number[j] + val*16);
		i--;
		j++;
	}
}

void CUtils::Char_Rtrim(char *str)
{
	if (str[0] == 0) return;
	int i = strlen(str)-1;
	for(;i>0;i--)
	{
		if (str[i] != ' ') break;
		str[i] = 0;
	}

}

DWORD CUtils::File_Copy(char *source, char *dest, BOOL overwrite)
{
	if (::CopyFile(source,dest,!overwrite)) return ERR_OK;
	return SetError_Add_W32_code_msg(false,ERR_API,GetLastError(),"CUtils::CopyFile(%s->%s) failed ",source,dest);
}

DWORD CUtils::Buffer_to_File(char *file_path, BYTE *buffer, DWORD size)
{
	DWORD	file_size;
	FILE*	hfile;

	hfile = fopen(file_path,"wb");
	if (hfile == NULL)	return SetError(false,ERR_API,"CUtils::ResourceToFile -> fopen (%s) ",file_path);
	file_size = fwrite(buffer,1,size,hfile);
	fclose(hfile);
	if (file_size != size) return SetError(false,ERR_API,"CUtils::Buffer_to_File -> fwrite failed by %u bytes",size-file_size);
	return ERR_OK;
}

BSTR CUtils::BSTR_Get(char *str)
{
	BSTR	bstr;
	if (str[0] == 0) return NULL;
	int	i;
	int	len = strlen(str);
	bstr = SysAllocStringByteLen(NULL,(len)*2);
	if (bstr == NULL) return NULL;
	i = MultiByteToWideChar(CP_ACP,0,str,len,bstr,len);
	if (i == len) return bstr;
	m_plog->log_strings(LOG_ERROR,"FATAL ERROR :: MultiByteToWideChar Failed");
	SysFreeString(bstr);
	return NULL;
}

void CUtils::CharGet_FreeBSTR(BSTR bstr, char *str, int maxsize)
{
	Char_Get(bstr,str,maxsize,SysStringLen(bstr));
	SysFreeString(bstr);
}

DWORD CUtils::App_Execute(char *path, char *arg)
{
	char*	fnc_name = "CUtils::App_Execute";

	BOOL	br;
	STARTUPINFO			si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si));
	si.cb			= sizeof(si);
	si.dwFlags		= 0;
	si.wShowWindow  = SW_SHOW;
	ZeroMemory( &pi, sizeof(pi));

	br = CreateProcess(path,arg,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi); //CREATE_NEW_PROCESS_GROUP|CREATE_NO_WINDOW|CREATE_NEW_CONSOLE
	if (!br) return SetError_Add_W32_code_msg(false,ERR_FATAL,GetLastError(),"%s->CreateProcess '%s'... failed ",fnc_name,path);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return ERR_OK;

}

DWORD CUtils::Byte_to_hex(BYTE *data, DWORD size, char *str, DWORD slen)
{
	char*	fnc_name = "CUtils::Byte_to_hex";
	DWORD	i;
	char	*cptr;

	if (size*2 > slen -1) return SetError(true,ERR_FATAL,"%s str buffer to short most be %d bytes",fnc_name,size*2);
	cptr = str;
	for (i=0;i<size;i++)
	{
		*cptr = (data[i] / 16) + '0'; if (*cptr > '9') *cptr += ('A'-'9'-1);
		cptr++;
		*cptr = (data[i] & 0x0F) + '0'; if (*cptr > '9') *cptr += ('A'-'9'-1);
 		cptr++;
	}
	*cptr = 0;
	return ERR_OK;
}

DWORD CUtils::DateTime_get_Current(char *dt_str, DWORD size)
{
	char	*fnc_name = "CUtils::DateTime_get_Current";
	struct tm *time;
    time_t long_time;
	::time(&long_time);
	time = localtime(&long_time);
	if (time == NULL)	return SetError(true,ERR_FATAL,"%s Failed to get convert time with localtime ",fnc_name);
	_snprintf(dt_str,size,"%.4d/%.2u/%.2u %.2u:%.2u:%.2u",1900+time->tm_year,time->tm_mon+1,time->tm_mday,time->tm_hour,time->tm_min,time->tm_sec);
	return ERR_OK;
}

DWORD CUtils::Date_to_Str(struct tm *time, char *dt_str, int size)
{
	dt_str[0] = 0;
	if (time->tm_mday == 0) return ERR_FATAL;
	_snprintf(dt_str,size,"%.4d/%.2u/%.2u",1900+time->tm_year,time->tm_mon+1,time->tm_mday);
	return ERR_OK;
}

DWORD CUtils::DateTime_to_Str(struct tm *time, char *dt_str, int size)
{
	dt_str[0] = 0;
	if (time->tm_mday == 0) return ERR_FATAL;
	_snprintf(dt_str,size,"%.4d/%.2u/%.2u %.2u:%.2u:%.2u",1900+time->tm_year,time->tm_mon+1,time->tm_mday,time->tm_hour,time->tm_min,time->tm_sec);
	return ERR_OK;
}
