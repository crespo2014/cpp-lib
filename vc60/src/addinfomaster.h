
#if !defined(ADDINFOMASTER_H_INCLUDE_)
#define ADDINFOMASTER_H_INCLUDE_

#include "memstack.h"

/*
	Fichero que maneja el addinfo master de las keywords de CTRL_SA
	Dependencias:
		MemStack - Almacenamiento en memoria de toda la estrutura
*/

struct ADDINFO_KEYWORD
{
	struct ADDINFO_KEYWORD* next;
	char	*val;
	char	key[1];	//posicion del 0 o fin de linea
};

struct _ADDINFO_MASTER
{
	int		binit;					// Indica si la estrutura esta inicializada
	//DWORD	data_size;				// tama�o de la estructura en memoria que mantiene las keywords
	struct ADDINFO_KEYWORD*	first;	// Primera keyword de la estructura
	union {
		struct _MEM_STACK mstack;
		BYTE	data[4000];					// Estructura en memoria con todas la keywords.
	};
};

/*
	Inicializar la estrutura
	Parametros :
		Puntero a la estrutura 
		Tama�a maximo de la memoria a reservar para el almacenamiento de datos
*/
DWORD Addinfo_Init(struct _ADDINFO_MASTER* addinfo, DWORD size);

DWORD Addinfo_SetData(struct _ADDINFO_MASTER* addinfo, char *data);

DWORD Addinfo_getKeyword(struct _ADDINFO_MASTER* addinfo, char* keyword, char **val);

#endif
