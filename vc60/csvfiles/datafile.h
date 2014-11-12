// datafile.h: interface for the Cdatafile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAFILE_H__3CDC2F39_5AF4_4071_B5CB_619A432230AD__INCLUDED_)
#define AFX_DATAFILE_H__3CDC2F39_5AF4_4071_B5CB_619A432230AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include "logclient.h"

class Cdatafile  
{
public:
	Cdatafile();
	virtual ~Cdatafile();

};

// estructuras usadas en el fichero

typedef struct
{
	FILE*	file_handle;
	char	row_delimiter;
	char	colum_delimiter;
	char	file_path[256];		// Ruta y nombre del fichero
	char	buffer[1024];	// buffer de lectura del fichero
	WORD	buffer_count;			// cantidad de datos en el buffer
	WORD	buffer_pos;
	WORD	row_pos;			// numero de fila en procesamiento
	char	currline[2048];		// linea actual en procesamiento 
	char	data[2048];			// datos separados por 0
	char*	values[255];		// valores dentro de data
	char	value_count;		// cantidad de datos obtenidos (columnas)

}_datafile;

int ReadRowData(_datafile* pthis);
void InitDataFile(_datafile* pthis);
int FillBuffer(_datafile* pthis);
int GetLine(_datafile* pthis);

#endif // !defined(AFX_DATAFILE_H__3CDC2F39_5AF4_4071_B5CB_619A432230AD__INCLUDED_)
