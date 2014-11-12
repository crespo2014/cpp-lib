// Utils.cpp: implementation of the CUtils class.
//
//////////////////////////////////////////////////////////////////////

#include "Utils.h"
#include "time.h"

#define _FILENAME_ "util.c"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CUtils	gutils;

static struct	
{
	UINT	w32_message;
	char*	w32_message_text;
}S_W32_MessageText[] = {
	{WM_CREATE                 ,"WM_CREATE"},					//0x0001
	{WM_DESTROY                ,"WM_DESTROY"},					//0x0002
	{WM_MOVE                   ,"WM_MOVE"},						//0x0003
	{WM_SIZE                   ,"WM_SIZE"},						//0x0005
	{WM_ACTIVATE               ,"WM_ACTIVATE"},					//0x0006
	{WM_SETFOCUS               ,"WM_SETFOCUS"},					//0x0007
	{WM_KILLFOCUS              ,"WM_KILLFOCUS"},				//0x0008
	{WM_ENABLE                 ,"WM_ENABLE"},					//0x000A
	{WM_SETREDRAW              ,"WM_SETREDRAW"},				//0x000B
	{WM_SETTEXT                ,"WM_SETTEXT"},					//0x000C
	{WM_GETTEXT                ,"WM_GETTEXT"},					//0x000D
	{WM_GETTEXTLENGTH          ,"WM_GETTEXTLENGTH"},			//0x000E
	{WM_PAINT                  ,"WM_PAINT"},					//0x000F
	{WM_CLOSE                  ,"WM_CLOSE"},					//0x0010
	{WM_QUERYENDSESSION        ,"WM_QUERYENDSESSION"},			//0x0011
	{WM_QUIT                   ,"WM_QUIT"},						//0x0012
	{WM_QUERYOPEN              ,"WM_QUERYOPEN"},				//0x0013
	{WM_ERASEBKGND             ,"WM_ERASEBKGND"},				//0x0014
	{WM_SYSCOLORCHANGE         ,"WM_SYSCOLORCHANGE"},			//0x0015
	{WM_ENDSESSION             ,"WM_ENDSESSION"},				//0x0016
	{WM_SHOWWINDOW             ,"WM_SHOWWINDOW"},				//0x0018
	{WM_WININICHANGE           ,"WM_WININICHANGE"},				//0x001A
	{WM_DEVMODECHANGE          ,"WM_DEVMODECHANGE"},			//0x001B
	{WM_ACTIVATEAPP            ,"WM_ACTIVATEAPP"},				//0x001C
	{WM_FONTCHANGE             ,"WM_FONTCHANGE"},				//0x001D
	{WM_TIMECHANGE             ,"WM_TIMECHANGE"},				//0x001E
	{WM_CANCELMODE             ,"WM_CANCELMODE"},				//0x001F
	{WM_SETCURSOR              ,"WM_SETCURSOR"},				//0x0020
	{WM_MOUSEACTIVATE          ,"WM_MOUSEACTIVATE"},			//0x0021
	{WM_CHILDACTIVATE          ,"WM_CHILDACTIVATE"},			//0x0022
	{WM_QUEUESYNC              ,"WM_QUEUESYNC"},				//0x0023
	{WM_GETMINMAXINFO          ,"WM_GETMINMAXINFO"},			//0x0024
	{WM_PAINTICON              ,"WM_PAINTICON"},				//0x0026
	{WM_ICONERASEBKGND         ,"WM_ICONERASEBKGND"},			//0x0027
	{WM_NEXTDLGCTL             ,"WM_NEXTDLGCTL"},				//0x0028
	{WM_SPOOLERSTATUS          ,"WM_SPOOLERSTATUS"},			//0x002A
	{WM_DRAWITEM               ,"WM_DRAWITEM"},					//0x002B
	{WM_MEASUREITEM            ,"WM_MEASUREITEM"},				//0x002C
	{WM_DELETEITEM             ,"WM_DELETEITEM"},				//0x002D
	{WM_VKEYTOITEM             ,"WM_VKEYTOITEM"},				//0x002E
	{WM_CHARTOITEM             ,"WM_CHARTOITEM"},				//0x002F
	{WM_SETFONT                ,"WM_SETFONT"},					//0x0030
	{WM_GETFONT                ,"WM_GETFONT"},					//0x0031
	{WM_SETHOTKEY              ,"WM_SETHOTKEY"},				//0x0032
	{WM_GETHOTKEY              ,"WM_GETHOTKEY"},				//0x0033
	{WM_QUERYDRAGICON          ,"WM_QUERYDRAGICON"},			//0x0037
	{WM_COMPAREITEM            ,"WM_COMPAREITEM"},				//0x0039
	{0x003D						,"WM_GETOBJECT"},				//0x003D
	{WM_COMPACTING             ,"WM_COMPACTING"},				//0x0041
	{WM_COMMNOTIFY             ,"WM_COMMNOTIFY"},				//0x0044  /* no longer suported */
	{WM_WINDOWPOSCHANGING      ,"WM_WINDOWPOSCHANGING"},		//0x0046
	{WM_WINDOWPOSCHANGED       ,"WM_WINDOWPOSCHANGED"},			//0x0047
	{WM_POWER                  ,"WM_POWER"},					//0x0048
	{WM_COPYDATA               ,"WM_COPYDATA"},					//0x004A
	{WM_CANCELJOURNAL          ,"WM_CANCELJOURNAL"},			//0x004B
	{WM_NOTIFY                 ,"WM_NOTIFY"},					//0x004E
	{WM_INPUTLANGCHANGEREQUEST ,"WM_INPUTLANGCHANGEREQUEST"},	//0x0050
	{WM_INPUTLANGCHANGE        ,"WM_INPUTLANGCHANGE"},			//0x0051
	{WM_TCARD                  ,"WM_TCARD"},					//0x0052
	{WM_HELP                   ,"WM_HELP"},						//0x0053
	{WM_USERCHANGED            ,"WM_USERCHANGED"},				//0x0054
	{WM_NOTIFYFORMAT           ,"WM_NOTIFYFORMAT"},				//0x0055
	{WM_CONTEXTMENU            ,"WM_CONTEXTMENU"},				//0x007B
	{WM_STYLECHANGING          ,"WM_STYLECHANGING"},			//0x007C
	{WM_STYLECHANGED           ,"WM_STYLECHANGED"},				//0x007D
	{WM_DISPLAYCHANGE          ,"WM_DISPLAYCHANGE"},			//0x007E
	{WM_GETICON                ,"WM_GETICON"},					//0x007F
	{WM_SETICON                ,"WM_SETICON"},					//0x0080
	{WM_NCCREATE               ,"WM_NCCREATE"},					//0x0081
	{WM_NCDESTROY              ,"WM_NCDESTROY"},				//0x0082
	{WM_NCCALCSIZE             ,"WM_NCCALCSIZE"},				//0x0083
	{WM_NCHITTEST              ,"WM_NCHITTEST"},				//0x0084
	{WM_NCPAINT                ,"WM_NCPAINT"},					//0x0085
	{WM_NCACTIVATE             ,"WM_NCACTIVATE"},				//0x0086
	{WM_GETDLGCODE             ,"WM_GETDLGCODE"},				//0x0087
	{WM_SYNCPAINT              ,"WM_SYNCPAINT"},				//0x0088
	{WM_NCMOUSEMOVE            ,"WM_NCMOUSEMOVE"},				//0x00A0
	{WM_NCLBUTTONDOWN          ,"WM_NCLBUTTONDOWN"},			//0x00A1
	{WM_NCLBUTTONUP            ,"WM_NCLBUTTONUP"},				//0x00A2
	{WM_NCLBUTTONDBLCLK        ,"WM_NCLBUTTONDBLCLK"},			//0x00A3
	{WM_NCRBUTTONDOWN          ,"WM_NCRBUTTONDOWN"},			//0x00A4
	{WM_NCRBUTTONUP            ,"WM_NCRBUTTONUP"},				//0x00A5
	{WM_NCRBUTTONDBLCLK        ,"WM_NCRBUTTONDBLCLK"},			//0x00A6
	{WM_NCMBUTTONDOWN          ,"WM_NCMBUTTONDOWN"},			//0x00A7
	{WM_NCMBUTTONUP            ,"WM_NCMBUTTONUP"},				//0x00A8
	{WM_NCMBUTTONDBLCLK        ,"WM_NCMBUTTONDBLCLK"},			//0x00A9
	{WM_KEYFIRST               ,"WM_KEYFIRST"},					//0x0100
	{WM_KEYDOWN                ,"WM_KEYDOWN"},					//0x0100
	{WM_KEYUP                  ,"WM_KEYUP"},					//0x0101
	{WM_CHAR                   ,"WM_CHAR"},						//0x0102
	{WM_DEADCHAR               ,"WM_DEADCHAR"},					//0x0103
	{WM_SYSKEYDOWN             ,"WM_SYSKEYDOWN"},				//0x0104
	{WM_SYSKEYUP               ,"WM_SYSKEYUP"},					//0x0105
	{WM_SYSCHAR                ,"WM_SYSCHAR"},					//0x0106
	{WM_SYSDEADCHAR            ,"WM_SYSDEADCHAR"},				//0x0107
	{WM_KEYLAST                ,"WM_KEYLAST"},					//0x0108
	{WM_IME_STARTCOMPOSITION   ,"WM_IME_STARTCOMPOSITION"},		//0x010D
	{WM_IME_ENDCOMPOSITION     ,"WM_IME_ENDCOMPOSITION"},		//0x010E
	{WM_IME_COMPOSITION        ,"WM_IME_COMPOSITION"},			//0x010F
	{WM_IME_KEYLAST            ,"WM_IME_KEYLAST"},				//0x010F
	{WM_INITDIALOG             ,"WM_INITDIALOG"},				//0x0110
	{WM_COMMAND                ,"WM_COMMAND"},					//0x0111
	{WM_SYSCOMMAND             ,"WM_SYSCOMMAND"},				//0x0112
	{WM_TIMER                  ,"WM_TIMER"},					//0x0113
	{WM_HSCROLL                ,"WM_HSCROLL"},					//0x0114
	{WM_VSCROLL                ,"WM_VSCROLL"},					//0x0115
	{WM_INITMENU               ,"WM_INITMENU"},					//0x0116
	{WM_INITMENUPOPUP          ,"WM_INITMENUPOPUP"},			//0x0117
	{WM_MENUSELECT             ,"WM_MENUSELECT"},				//0x011F
	{WM_MENUCHAR               ,"WM_MENUCHAR"},					//0x0120
	{WM_ENTERIDLE              ,"WM_ENTERIDLE"},				//0x0121
	{0x0122			          ,"WM_MENURBUTTONUP"},			//0x0122
	{0x0123               ,"WM_MENUDRAG"},					//0x0123
	{0x0124          ,"WM_MENUGETOBJECT"},			//0x0124
	{0x0125        ,"WM_UNINITMENUPOPUP"},			//0x0125
	{0x0126            ,"WM_MENUCOMMAND"},				//0x0126
	{0x0127					,"WM_CHANGEUISTATE"},                //0x0127
	{0x0128					,"WM_UPDATEUISTATE"},                //0x0128
	{0x0129					,"WM_QUERYUISTATE"},                 //0x0129
	{WM_CTLCOLORMSGBOX         ,"WM_CTLCOLORMSGBOX"},			//0x0132
	{WM_CTLCOLOREDIT           ,"WM_CTLCOLOREDIT"},				//0x0133
	{WM_CTLCOLORLISTBOX        ,"WM_CTLCOLORLISTBOX"},			//0x0134
	{WM_CTLCOLORBTN            ,"WM_CTLCOLORBTN"},				//0x0135
	{WM_CTLCOLORDLG            ,"WM_CTLCOLORDLG"},				//0x0136
	{WM_CTLCOLORSCROLLBAR      ,"WM_CTLCOLORSCROLLBAR"},		//0x0137
	{WM_CTLCOLORSTATIC         ,"WM_CTLCOLORSTATIC"},			//0x0138
	{WM_MOUSEFIRST             ,"WM_MOUSEFIRST"},				//0x0200
	{WM_MOUSEMOVE              ,"WM_MOUSEMOVE"},				//0x0200
	{WM_LBUTTONDOWN            ,"WM_LBUTTONDOWN"},				//0x0201
	{WM_LBUTTONUP              ,"WM_LBUTTONUP"},				//0x0202
	{WM_LBUTTONDBLCLK          ,"WM_LBUTTONDBLCLK"},			//0x0203
	{WM_RBUTTONDOWN            ,"WM_RBUTTONDOWN"},				//0x0204
	{WM_RBUTTONUP              ,"WM_RBUTTONUP"},				//0x0205
	{WM_RBUTTONDBLCLK          ,"WM_RBUTTONDBLCLK"},			//0x0206
	{WM_MBUTTONDOWN            ,"WM_MBUTTONDOWN"},				//0x0207
	{WM_MBUTTONUP              ,"WM_MBUTTONUP"},				//0x0208
	{WM_MBUTTONDBLCLK          ,"WM_MBUTTONDBLCLK"},			//0x0209
	{0x020A             ,"WM_MOUSEWHEEL"},				//0x020A
	{WM_MOUSELAST              ,"WM_MOUSELAST"},				//0x020A
	{WM_MOUSELAST              ,"WM_MOUSELAST"},				//0x0209
	{WM_PARENTNOTIFY           ,"WM_PARENTNOTIFY"},				//0x0210
	{WM_ENTERMENULOOP          ,"WM_ENTERMENULOOP"},			//0x0211
	{WM_EXITMENULOOP           ,"WM_EXITMENULOOP"},				//0x0212
	{WM_NEXTMENU               ,"WM_NEXTMENU"},					//0x0213
	{WM_SIZING                 ,"WM_SIZING"},					//0x0214
	{WM_CAPTURECHANGED         ,"WM_CAPTURECHANGED"},			//0x0215
	{WM_MOVING                 ,"WM_MOVING"},					//0x0216
	{WM_POWERBROADCAST         ,"WM_POWERBROADCAST"},			//0x0218      // r_winuser pbt
	{WM_DEVICECHANGE           ,"WM_DEVICECHANGE"},				//0x0219
	{WM_MDICREATE              ,"WM_MDICREATE"},				//0x0220
	{WM_MDIDESTROY             ,"WM_MDIDESTROY"},				//0x0221
	{WM_MDIACTIVATE            ,"WM_MDIACTIVATE"},				//0x0222
	{WM_MDIRESTORE             ,"WM_MDIRESTORE"},				//0x0223
	{WM_MDINEXT                ,"WM_MDINEXT"},					//0x0224
	{WM_MDIMAXIMIZE            ,"WM_MDIMAXIMIZE"},				//0x0225
	{WM_MDITILE                ,"WM_MDITILE"},					//0x0226
	{WM_MDICASCADE             ,"WM_MDICASCADE"},				//0x0227
	{WM_MDIICONARRANGE         ,"WM_MDIICONARRANGE"},			//0x0228
	{WM_MDIGETACTIVE           ,"WM_MDIGETACTIVE"},				//0x0229
	{WM_MDISETMENU             ,"WM_MDISETMENU"},				//0x0230
	{WM_ENTERSIZEMOVE          ,"WM_ENTERSIZEMOVE"},			//0x0231
	{WM_EXITSIZEMOVE           ,"WM_EXITSIZEMOVE"},				//0x0232
	{WM_DROPFILES              ,"WM_DROPFILES"},				//0x0233
	{WM_MDIREFRESHMENU         ,"WM_MDIREFRESHMENU"},			//0x0234
	{WM_IME_SETCONTEXT         ,"WM_IME_SETCONTEXT"},			//0x0281
	{WM_IME_NOTIFY             ,"WM_IME_NOTIFY"},				//0x0282
	{WM_IME_CONTROL            ,"WM_IME_CONTROL"},				//0x0283
	{WM_IME_COMPOSITIONFULL    ,"WM_IME_COMPOSITIONFULL"},		//0x0284
	{WM_IME_SELECT             ,"WM_IME_SELECT"},				//0x0285
	{WM_IME_CHAR               ,"WM_IME_CHAR"},					//0x0286
	{0x0288            ,"WM_IME_REQUEST"},				//0x0288
	{WM_IME_KEYDOWN            ,"WM_IME_KEYDOWN"},				//0x0290
	{WM_IME_KEYUP              ,"WM_IME_KEYUP"},				//0x0291
	{0x02A1             ,"WM_MOUSEHOVER"},				//0x02A1
	{0x02A3             ,"WM_MOUSELEAVE"},				//0x02A3
	{WM_CUT                    ,"WM_CUT"},						//0x0300
	{WM_COPY                   ,"WM_COPY"},						//0x0301
	{WM_PASTE                  ,"WM_PASTE"},					//0x0302
	{WM_CLEAR                  ,"WM_CLEAR"},					//0x0303
	{WM_UNDO                   ,"WM_UNDO"},						//0x0304
	{WM_RENDERFORMAT           ,"WM_RENDERFORMAT"},				//0x0305
	{WM_RENDERALLFORMATS       ,"WM_RENDERALLFORMATS"},			//0x0306
	{WM_DESTROYCLIPBOARD       ,"WM_DESTROYCLIPBOARD"},			//0x0307
	{WM_DRAWCLIPBOARD          ,"WM_DRAWCLIPBOARD"},			//0x0308
	{WM_PAINTCLIPBOARD         ,"WM_PAINTCLIPBOARD"},			//0x0309
	{WM_VSCROLLCLIPBOARD       ,"WM_VSCROLLCLIPBOARD"},			//0x030A
	{WM_SIZECLIPBOARD          ,"WM_SIZECLIPBOARD"},			//0x030B
	{WM_ASKCBFORMATNAME        ,"WM_ASKCBFORMATNAME"},			//0x030C
	{WM_CHANGECBCHAIN          ,"WM_CHANGECBCHAIN"},			//0x030D
	{WM_HSCROLLCLIPBOARD       ,"WM_HSCROLLCLIPBOARD"},			//0x030E
	{WM_QUERYNEWPALETTE        ,"WM_QUERYNEWPALETTE"},			//0x030F
	{WM_PALETTEISCHANGING      ,"WM_PALETTEISCHANGING"},		//0x0310
	{WM_PALETTECHANGED         ,"WM_PALETTECHANGED"},			//0x0311
	{WM_HOTKEY                 ,"WM_HOTKEY"},					//0x0312
	{WM_PRINT                  ,"WM_PRINT"},					//0x0317
	{WM_PRINTCLIENT            ,"WM_PRINTCLIENT"},				//0x0318
	{WM_HANDHELDFIRST          ,"WM_HANDHELDFIRST"},			//0x0358
	{WM_HANDHELDLAST           ,"WM_HANDHELDLAST"},				//0x035F
	{WM_AFXFIRST               ,"WM_AFXFIRST"},					//0x0360
	{WM_AFXLAST                ,"WM_AFXLAST"},					//0x037F
	{WM_PENWINFIRST            ,"WM_PENWINFIRST"},				//0x0380
	{WM_PENWINLAST             ,"WM_PENWINLAST"},				//0x038F
	{WM_APP                    ,"WM_APP"},						//0x8000
	{WM_USER                   ,"WM_USER"},						//0x0400
	{WM_NULL					,""}    
	

	};

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
	return ERR_API;
	//return LOG_TERROR ERR_API,"CUtils::GetFileInformation -> _stat(%s) ... failed",file_data->file_path);
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

	hres = FindResourceA(hModule,res_name,res_type);
	if (hres == NULL) 
	{
		return LOG_TW32_ERROR GetLastError(),ERR_API,"FindResource (%s,%s) failed",res_name,res_type);
	}
	hglobal = LoadResource(hModule,hres);
	if (hglobal == NULL) 
	{
		return LOG_TW32_ERROR GetLastError(),ERR_API,"LoadResource ");
	}
	res_data = LockResource(hglobal);
	res_size = SizeofResource(hModule,hres);
	hfile = fopen(file_path,"wb");
	if (hfile == NULL)	
	{
		return LOG_TERROR ERR_API,"fopen (%s) ",file_path);
	}
	file_size = fwrite(res_data,1,res_size,hfile);
	fclose(hfile);
	if (file_size != res_size) 
	{
		return LOG_TERROR ERR_API,"fwrite failed by %u bytes",res_size-file_size);
	}
	return ERR_OK;
}

DWORD CUtils::File_Delete(char *file_path)
{
	if (::DeleteFileA(file_path)) return ERR_OK;
	return LOG_TW32_ERROR GetLastError(),ERR_API,"DeleteFile(%s) ",file_path);
}

DWORD CUtils::File_IsValid(char *file_path)
{
	DWORD	fa;
	fa = GetFileAttributesA(file_path);
	if (fa == INVALID_FILE_ATTRIBUTES) return ERR_FATAL;
	if (fa & FILE_ATTRIBUTE_DIRECTORY) return ERR_FATAL;
	return ERR_OK;
}

DWORD CUtils::Folder_Create(char *folder_path)
{
	DWORD	dwr;

	dwr = GetFileAttributesA(folder_path); 
	if (dwr == INVALID_FILE_ATTRIBUTES)
	{
		// no esta la carpeta
		if (!CreateDirectoryA(folder_path,NULL)) 
			return LOG_TW32_ERROR GetLastError(),ERR_API,"CreateDirectory(%s) ",folder_path);
		return ERR_OK;
	}
	if (dwr & FILE_ATTRIBUTE_DIRECTORY) return ERR_OK;
	return LOG_TERROR ERR_FATAL,"%s is not a File Folder",folder_path);
}

DWORD CUtils::WChar_Get(char *cstr, unsigned short *ustr, int maxsize)
{
	int	i;
	//int	len = strlen(cstr);
	i = MultiByteToWideChar(CP_ACP,0,cstr,-1/*len*/,(LPWSTR)ustr,maxsize);
	if ( i == 0) 
	{
		return LOG_TW32_ERROR GetLastError(),ERR_API,"MultiByteToWideChar ");
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
		return LOG_TERROR ERR_FATAL,"WideCharToMultiByte string has been truncate");
	}
	if (u_size != -1) str[i] = 0;
	return ERR_OK;
}

DWORD CUtils::CoInitialize()
{
	HRESULT	hr;
	hr = ::CoInitialize(NULL);
	if (hr != S_OK) return LOG_TERROR ERR_API,"CoInitialize failed with code %X",hr);
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
	if (::CopyFileA(source,dest,!overwrite)) return ERR_OK;
	return LOG_TW32_ERROR GetLastError(),ERR_API,"CopyFile(%s->%s) ",source,dest);
}

DWORD CUtils::Buffer_to_File(char *file_path, BYTE *buffer, DWORD size)
{
	DWORD	file_size;
	FILE*	hfile;

	hfile = fopen(file_path,"wb");
	if (hfile == NULL)	return LOG_TERROR ERR_API,"fopen (%s) ",file_path);
	file_size = fwrite(buffer,1,size,hfile);
	fclose(hfile);
	if (file_size != size) return LOG_TERROR ERR_API,"fwrite failed by %u bytes",size-file_size);
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
	LOG_TW32_ERROR GetLastError(),ERR_API,"MultiByteToWideChar");
	SysFreeString(bstr);
	return NULL;
}

void CUtils::CharGet_FreeBSTR(BSTR bstr, char *str, int maxsize)
{
	Char_Get((unsigned short*)bstr,str,maxsize,SysStringLen(bstr));
	SysFreeString(bstr);
}

DWORD CUtils::App_Execute(char *path, char *arg)
{
	BOOL	br;
	STARTUPINFOA		si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si));
	si.cb			= sizeof(si);
	si.dwFlags		= 0;
	si.wShowWindow  = SW_SHOW;
	ZeroMemory( &pi, sizeof(pi));

	br = CreateProcessA(path,arg,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi); //CREATE_NEW_PROCESS_GROUP|CREATE_NO_WINDOW|CREATE_NEW_CONSOLE
	if (!br) return LOG_TW32_ERROR  GetLastError(),ERR_FATAL,"CreateProcess '%s' ",path);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return ERR_OK;

}

DWORD CUtils::Byte_to_hex(BYTE *data, DWORD size, char *str, DWORD slen)
{
	DWORD	i;
	char	*cptr;

	if (size*2 > slen -1) return LOG_TERROR ERR_FATAL," str buffer to short most be %d bytes",size*2);
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
	struct tm *time;
    time_t long_time;
	::time(&long_time);
	time = localtime(&long_time);
	if (time == NULL)	return LOG_TERROR ERR_FATAL," Failed to get convert time with localtime ");
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

char* CUtils::GetW32_MessageText(UINT uMsg)
{
	int	i;
	for (i=0;S_W32_MessageText[i].w32_message != 0;i++)
		if (S_W32_MessageText[i].w32_message == uMsg) return S_W32_MessageText[i].w32_message_text;
	return "";
}
