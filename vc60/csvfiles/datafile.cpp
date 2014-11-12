// datafile.cpp: implementation of the Cdatafile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "datafile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cdatafile::Cdatafile()
{

}

Cdatafile::~Cdatafile()
{

}

void InitDataFile(_datafile* pthis)
{
	pthis->buffer_count = 0;
	pthis->buffer_pos = 0;
	pthis->colum_delimiter = ';';
	pthis->file_handle = 0;
	pthis->row_delimiter = 10;
}

int GetLine(_datafile* pthis)
{
	// leer una fila de datos completa y colocarla en currline, se termina con un caracter menor que 20
	char* pline;
	char* psrc;
	WORD	pos;

	pos = 0;
	pline = pthis->currline;
	psrc = pthis->buffer + pthis->buffer_pos;
	for (;;)
	{
		if (pos == sizeof(pthis->currline) -1) 
		{
			glog.Log("Line to long");
			break;
		}
		if (pthis->buffer_pos >= pthis->buffer_count)
		{
			if (FillBuffer(pthis) == 0) return 0;	// No se le leyeron datos
			psrc = pthis->buffer;
		}

		if ((*psrc == pthis->row_delimiter) || (*psrc == 13)) break;

		if ((*psrc >= 32) || (*psrc == pthis->colum_delimiter))
		{
			*pline = *psrc;
			pos ++;
			pline ++;
		}
		psrc++;
		pthis->buffer_pos++;
	}
	pthis->buffer_pos++;
	*pline = 0;
	return 1;
}

int FillBuffer(_datafile* pthis)
{
	// leer paquete de datos del fichero y colocarlos en el buffer
	pthis->buffer_count = fread(pthis->buffer,1,sizeof(pthis->buffer),pthis->file_handle);
	pthis->buffer_pos = 0;
	if (pthis->buffer_count == 0) return 0;
	return 1;
}


int ReadRowData(_datafile* pthis)
{
	// Leer una fila de datos y descomponerlos
	char*	pline;
	char*	pvalue;
	WORD	line_pos;
	
	line_pos = 0;
	pthis->value_count = 0;

	if (GetLine(pthis) == 0) return 0;
	strcpy(pthis->data,pthis->currline);
	pline = pthis->data;
	pvalue = pline;
	for (;;)
	{
		if ((*pline == pthis->colum_delimiter)|| (*pline == 0))
		{
			pthis->values[pthis->value_count] = pvalue;
			pthis->value_count++;
			if (*pline == 0) return 1;
			pvalue = pline + 1;
			*pline = 0;
		}
		pline++;
	}
	return 1;
}
