
#include "addinfomaster.h"

/*
	Fichero que maneja el addinfo master de las keywords de CTRL_SA
	Dependencias:
		MemStack - Almacenamiento en memoria de toda la estrutura
*/

/*
	Liberar los datos dinamicos de la estrutura e Inicializar sus valores
*/
void Addinfo_Release(struct _ADDINFO_MASTER*	addinfo)
{
	if (addinfo->binit) 
	{
		//if (addinfo->mstack != NULL) free(addinfo->mstack);		
	}
	memset(addinfo,0,sizeof(struct _ADDINFO_MASTER));
}

/*
	Inicializar la estrutura
	Parametros :
		Puntero a la estrutura 
		Tama�a maximo de la memoria a reservar para el almacenamiento de datos
*/
DWORD Addinfo_Init(struct _ADDINFO_MASTER* addinfo, DWORD size)
{
	char* fnc_name = "Addinfo_Init";
	Addinfo_Release(addinfo);
	//if (size <= sizeof(struct MEM_STACK)) return LOG_TERROR "size for data insuficient min is %d",sizeof(struct MEM_STACK));
	//addinfo->mstack = malloc(size);
	//if (addinfo->data == NULL) return LOG_TERROR "Call to malloc with %d bytes failed",size);
	if (MemStack_Init(&addinfo->mstack,sizeof(addinfo->data)) != ERR_OK) return LOG_TSTACK;
	//addinfo->data_size = size;
	return ERR_OK;
}

DWORD Addinfo_SetData(struct _ADDINFO_MASTER* addinfo, char *data)
{
	char*	fnc_name = "Addinfo_SetData";
	char*	cptr;
	char	*key_s,*key_e;
	char	*val_s,*val_e;
	//DWORD	dwr;
	DWORD	i;
	struct ADDINFO_KEYWORD	*keyword;
	struct ADDINFO_KEYWORD	**plast_keyword;
	
	if (!addinfo->binit) return LOG_TERROR ERR_FATAL,"Failed for uninitialize object");
	if (MemStack_Init(&addinfo->mstack,sizeof(addinfo->data)) != ERR_OK) return LOG_TSTACK;			// limpiar los datos actuales
	addinfo->first = NULL;
	plast_keyword = &addinfo->first;
	cptr = data;
	key_s = NULL;
	key_e = NULL;
	val_s = NULL;

	for (;;cptr++)
	{
		if (key_s == NULL)  key_s = cptr;		// el primer caracter es el nombre de la keyword, a menos que ya se tenga un comienzo
		if (*cptr == '=')	key_e = cptr;		// el siguiente caracter despues del = es el valor de la keyword
		if ((key_e != NULL) && 
			(*cptr != '=')) val_s = cptr;		// si ya se tiene un final de key y se pasa el = esto es el valor
		if ((*cptr == 0) || (*cptr == ';'))		// fin de linea o de keyword
		{
			val_e = cptr;
			if ((val_s != val_e) && (key_s != key_e))	// se ha obtenido un valor
			{
				i = key_e - key_s + val_e - val_s + 1 + sizeof(struct ADDINFO_KEYWORD) ;
				if (MemStack_Get(&addinfo->mstack,i,(void**)&keyword,true) != ERR_OK) return LOG_TSTACK;
				keyword->next = NULL;
				*plast_keyword = keyword;
				plast_keyword = &keyword->next;
				keyword->val = keyword->key + (key_e - key_s + 1);
				keyword->val[0] = 0;
				keyword->key[0] = 0;
				strncat(keyword->key,key_s,key_s - key_e);
				strncat(keyword->val,val_s,val_s - val_e);
			}
			key_s = NULL; key_e = NULL;
			val_s = NULL; val_e = NULL;
		}
		if (*cptr == 0) break;
	} // END for
	return ERR_OK;
}


DWORD Addinfo_getKeyword(struct _ADDINFO_MASTER* addinfo, char* keyword, char **val)
{
	char*	fnc_name = "Addinfo_getKeyword";

	struct ADDINFO_KEYWORD	*pkeyword;
	for (pkeyword = addinfo->first;pkeyword != NULL; pkeyword = pkeyword->next)
	{
		if (strcmp(keyword,pkeyword->key) == 0)
		{
			*val = pkeyword->val;
			return ERR_OK;
		}
	}
	return LOG_TERROR ERR_NOT_FOUND,"Key %s not found",keyword);
}
