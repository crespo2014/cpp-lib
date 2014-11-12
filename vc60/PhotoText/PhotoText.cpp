// PhotoText.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

struct color {
	BYTE b;
	BYTE g;
	BYTE r;
};

// Fichero leido en memoria
LONG	lwidth;
LONG	lheight;
DWORD	dwBytesWidth;		// cantidad de bytes que ocupa una fila del bmp alineada 4 bytes
BYTE*	bmpbits = NULL;		// puntero a los bits del bitmap
color*	colortbl = NULL;
DWORD	ctblsize;

char* filename = "photo.bmp";

// Declaracion de funciones
DWORD LoadBmpFile(char* lpname);
DWORD GetColor(DWORD x, DWORD y, color* lpcolor);
DWORD CreateRTFFile(char* lpname);


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	DWORD	result = false;
	DWORD	dwr;
	do
	{
		dwr = LoadBmpFile(filename);
		if (dwr == false) break;
		dwr = CreateRTFFile("photo.rtf");
		result = true;
	} while (false);

	if (result) 
		::MessageBox(NULL,"Operation success ","File convertion BMP to RTF",MB_OK);
	else 
		::MessageBox(NULL,"Operation failed","File convertion BMP to RTF",MB_OK);

	delete bmpbits;
	return 0;
}

DWORD LoadBmpFile(char* lpname)
{
	HANDLE	hfile;
	DWORD	dwBytesRead;
	BOOL	br;
	DWORD	result = false;
	DWORD	dwr;

	BITMAPFILEHEADER	bfh;
	BITMAPINFOHEADER	bih;

	do
	{
		hfile = ::CreateFile(lpname,GENERIC_READ,FILE_SHARE_READ,NULL,
						OPEN_EXISTING,FILE_FLAG_RANDOM_ACCESS,NULL);
		if (hfile == INVALID_HANDLE_VALUE) break;
		/*{
			dwr = ::GetLastError();
			break;
		}*/

		// Read bitmap file header
		br = ::ReadFile(hfile,&bfh,sizeof(bfh),&dwBytesRead,NULL);
		if ((br == 0) || (dwBytesRead != sizeof(bfh))) break;

		// read bitmap info header
		br = ::ReadFile(hfile,&bih,sizeof(bih),&dwBytesRead,NULL);
		if ((br == 0) || (dwBytesRead != sizeof(bih))) break;
		lwidth = bih.biWidth;
		lheight = bih.biHeight;
		//dwBytesWidth = 4-(lwidth*3)%4 + (lwidth*3);
		dwBytesWidth = bih.biSizeImage / bih.biHeight;
		
		// desplazar puntero del fichero si bfh.bfOffBits
		dwr = ::SetFilePointer(hfile,bfh.bfOffBits,NULL,FILE_BEGIN);
		if (dwr != bfh.bfOffBits) break;
		

		// read bitmap pixels
		bmpbits = new BYTE[bih.biSizeImage];
		br = ::ReadFile(hfile,bmpbits,bih.biSizeImage,&dwBytesRead,NULL);
		if ((br == 0) || (dwBytesRead != bih.biSizeImage)) break;
		result = true;

	} while(false);

	::CloseHandle(hfile);
	return result;

}

// Devolver el color del punto x,y eje en el upper-left corner del bmp
DWORD GetColor(DWORD x, DWORD y, color* lpcolor)
{
	DWORD offset;
	color* cptr;
	offset = (lheight-y-1)*dwBytesWidth + x*3;
	cptr = (color*)&bmpbits[offset];
	*lpcolor = *cptr;
	return true;
}

// Busca o adiciona el color en la tabla de colores
// Devuelve la posicion del color
// el primer color se omite porque es el color por defecto
/*
DWORD AddColor(color* lpcolor)
{
	DWORD i = ctblsize;

	for (i=1;i<ctblsize;i++)
	{
		if ((colortbl[i].b == lpcolor->b) &&
			(colortbl[i].r == lpcolor->r) &&
			(colortbl[i].g == lpcolor->g))		return i;
	}

	
	colortbl[i] = *lpcolor;
	ctblsize++;
	return i;
}
*/

DWORD AddToRTF(HANDLE hfile,char* lpstr)
{
	static WORD linepos = 0;
	BOOL	br;
	WORD	wsize;
	DWORD	dwBytesWritten;

	// ver si cabe la cadena nueva
	wsize = strlen(lpstr);
	if (linepos + wsize > 250)
	{
		br = ::WriteFile(hfile,"\r\n",2,&dwBytesWritten,NULL);
		linepos = 0;
	}
	br = ::WriteFile(hfile,lpstr,wsize,&dwBytesWritten,NULL);
	linepos += wsize;
	return br;
}

// toma la tabla de colores colortbl, la convierte en str y adiciona al rtf
DWORD AddColorToRTF(HANDLE hfile)
{
	char	str[27];
	DWORD	i;

	for (i=1;i<ctblsize;i++)
	{
		sprintf(str,"\\red%d\\green%d\\blue%d;",colortbl[i].r,colortbl[i].g,colortbl[i].b);
		AddToRTF(hfile,str);
	}
	AddToRTF(hfile,"}");
	return TRUE;
}

// Rellena el RTF con caracteres de colores diversos
DWORD FillRTF(HANDLE hfile)
{
	DWORD	x,y,i;
	color	cl;
	char	str[30];
	DWORD	dwcol = 0;

	AddToRTF(hfile,"{\\fs16");

	for (y=0;y<lheight;y++)
		for (x=0;x<lwidth;x++)
		{
			GetColor(x,y,&cl);
			i = y*lwidth+x+2;	// la tabla de colores comienza con 1 y no se usa
			//i = AddColor(&cl) + 2;
			sprintf(str,"\\cf%d \\u9608\\'a6",i);
			AddToRTF(hfile,str);
			dwcol ++;
			if (dwcol == lwidth) 
			{
				AddToRTF(hfile,"\\par");
				dwcol = 0;
			}
			
		}

	AddToRTF(hfile,"}{\\par}}");
	return 0;
}

DWORD CreateRTFFile(char* lpname)
{
	// partes de un fichero RTF
	char* h1 = "{\\rtf1\\ansi\\ansicpg1252\\uc1 \\deff0\\deflang1033\\deflangfe1033 {\\fonttbl{\\f0\\fmodern\\fcharset0\\fprq1{\\*\\panose 020b0609040504020204}Lucida Console;}}";
	char* h2 = "{\\colortbl;\\red255\\green0\\blue0;";
	char* h3 = "{\\stylesheet{\\ql \\li0\\ri0\\widctlpar\\aspalpha\\aspnum\\faauto\\adjustright\\rin0\\lin0\\itap0\\fs16\\lang1033\\langfe1033\\cgrid\\langnp1033\\langfenp1033 \\snext0 Normal;}{\\*\\cs10 \\additive Default Paragraph Font;}}";
	char* h4 = "\\margl0\\margr0\\margt0\\margb0 \\widowctrl\\ftnbj\\aenddoc\\noxlattoyen\\expshrtn\\noultrlspc\\dntblnsbdb\\nospaceforul\\hyphcaps0\\horzdoc\\dghspace120\\dgvspace120\\dghorigin1701\\dgvorigin1984\\dghshow0\\dgvshow3";
	char* h5 = "\\jcompress\\viewkind1\\viewscale200\\nolnhtadjtbl \\fet0\\sectd \\linex0\\sectdefaultcl";
	char* h6 = "{\\fs16\\cf2 \\u9608\\'a6 \\cf4 \\u9608\\'a6 \\cf17 \\u9608\\'a6 \\cf18 \\u9608\\'a6}";
	//char* h7 = "{\\par}}";

	HANDLE hfile;
	DWORD	result = false;
	DWORD	x,y;
	do
	{
		hfile = ::CreateFile(lpname,GENERIC_WRITE,FILE_SHARE_READ,NULL,
						CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if (hfile == INVALID_HANDLE_VALUE) break;
		
		// crear tabla de colores
		colortbl = new color[lwidth*lheight+2];
		ctblsize = 1;
		for (y=0;y<lheight;y++)
			for (x=0;x<lwidth;x++)
			{
				color cl;
				GetColor(x,y,&cl);
				colortbl[ctblsize] = cl;
				ctblsize++;
			}

		// Crear el rtf
		AddToRTF(hfile,h1);
		AddToRTF(hfile,h2);
		AddColorToRTF(hfile);
		AddToRTF(hfile,h3);
		AddToRTF(hfile,h4);
		AddToRTF(hfile,h5);
		FillRTF(hfile);
		//AddToRTF(hfile,h7);

		result = true;
	} while (false);
	
	CloseHandle(hfile);
	delete colortbl;
	return result;
}



