// _inifile.cpp: implementation of the _inifile class.
//
//////////////////////////////////////////////////////////////////////

#include "_inifile.h"
#include "stdio.h"
#include "string.h"

/*
int main()
{
	printf("Helo everybody ....\n");
	return 0;
}
*/

DWORD _inifileGetFromFile(char* file_path,char* section, char* keyword,char* value, WORD maxlen)
{
	char	line[MAXINILINE];
	FILE*	file;
	char	csection[MAXINILINE];	//current section
	char*	cptr;
	char*	schr;		// start char caracter de inicio 
	char*	key;
	char*	val;
	DWORD	dwr = 1;	// asumir que ha fallado la operacion

	csection[0] = 0;
	value[0] = 0;
	file =	fopen(file_path,"r");
	if (file == NULL)	return 1;	//fallo la operacion
	for (;;)
	{
		cptr = fgets(line,sizeof(line),file); if (cptr == NULL) break;
		cptr = line;
		// analizar al linea obtenidad
		for (;(cptr[0] <= ' ')&&(cptr[0] != 0);cptr++);	// ignorar los espacios y los fines de linea
		if (cptr[0] == 0) continue;		// se termino la linea
		if (cptr[0] == ';')	continue;		// es una linea de comentario

		if (cptr[0] == '[')			// esto es una seccion tomar el nombre
		{
			cptr++;
			schr = cptr;
			for (;(cptr[0] > ' ')&&(cptr[0] != ']');cptr++);		// pasar por alto los caracteres validos
			if (cptr[0] == 0) continue;								// Se termino la linea	bruscamente
			cptr[0] = 0;
			uppercase(schr);
			strcpy(csection,schr);
			continue;	//proxima linea
		}
		if (strcasecmp(csection,section) != 0) continue;
		// no era una seccion es una key + valor
		key = cptr;
		for (;(cptr[0] > ' ')&&(cptr[0] != '=');cptr++);	// recorrer caracteres validos
		if (cptr[0] == 0) continue;		// fin inexperado
		for (;cptr[0] == ' ';cptr[0] = 0,cptr++);		// limpieza de espacios
		if (cptr[0] != '=') continue;		// se esparaba el =
		cptr[0] = 0;cptr++;					// ya tengo la key sin case
		if (strcasecmp(key,keyword) != 0) continue;
		for (;cptr[0] == ' ';cptr++);	// ignorar los espacios antes del valor
		if (cptr[0] == '\"') cptr++;	// la cadena empieza con un " porque tiene espacios delante
		val = cptr;										// tengo el valor
		for (;(cptr[0] >= ' ');cptr++);	// recorrer caracteres validos
		cptr[0] = 0;					// cualquier caracter termina el valor
		// realizar la comparacion a ver si esta es la key que se pidio
		strncpy(value,val,maxlen);
		fclose(file);
		return 0;
		
	}
	fclose(file);
	return 1;	// fallo la operacion
}

void uppercase (char* str)
{
	char*	cptr = str;
	while (cptr[0] != 0)
	{
		if ((cptr[0] >= 'a') && (cptr[0] <= 'z')) cptr[0] -= ('a' -'A');
		if (cptr[0] == 'ñ') cptr[0] = 'Ñ';
		cptr++;
	}
}

DWORD strcasecmp(char* str1,char* str2)
{
	char	c1,c2;
	if ((str1 == NULL) && (str2 == NULL)) return 0;
	if (str1 == NULL) {if (str2[0] == 0) return 0; else return 1;}
	if (str2 == NULL) {if (str1[0] == 0) return 0; else return 1;}
	
	for (;(*str1 != 0) && (*str2 != 0);str1++,str2++)
	{
		if (*str1 == 'Ñ') c1 = 'ñ'; else c1 = *str1;
		if (*str2 == 'Ñ') c2 = 'ñ'; else c2 = *str2;
		if (c1 == c2) continue;

		if (c1 >= 'a') c1 -= 32;
		if (c2 >= 'a') c2 -= 32;
		if ((c1 <= 'Z') && (c1 == c2)) continue;
		return 1;	// no son iguales
	}
	if (*str1 == *str2) return 0;	// si hay una cadena vacia esto evita que sean iguales
	return 1;	

}

DWORD _inifileInit(_INIFILE* pthis)
{
	pthis->keycount = 0;
	return 0;
}

DWORD _inifileRelease(_INIFILE* pthis)
{
	return 0;
}

DWORD _inifileReadFromFile(_INIFILE* pthis,char* file_path)
{
	char	strend;		// caracter de termiancion del valor
	char*	cptr;		// posicion que se esta tratando
	char*	section;	// seccion que se esta tratando
	WORD	keypos;		// key que se esta adicionando
	FILE*	file;
	DWORD	filesize;
	
	pthis->keycount = 0;
	keypos	= 0;

	file = fopen(file_path,"r");								if (file == NULL) return 1;		// error no se pudo abrir el fichero
	filesize = fread(pthis->data,1,sizeof(pthis->data),file);	if (filesize == 0) return 0;	// No hay datos en el fichero
	fclose(file);
	pthis->data[filesize] = 0;

	// se espera inicio de seccio
	section	= NULL;					// Inicialmente no hay seccion
	cptr = pthis->data;

	for (;cptr[0] != 0;)
	{
		for (;(cptr[0] <= ' ')&&(cptr[0] != 0);cptr++);	// ignorar los espacios y los fines de linea
		if (cptr[0] == 0) break;		// se termino el fichero
		if (cptr[0] == ';')
		{
			for (;cptr[0] > ' ';cptr++);
			continue;
		}
		if (cptr[0] == '[')
		{
			// seccion procesarla la seccion termina con un ]
			cptr++;
			section = cptr;
			for (;(cptr[0] > ' ')&&(cptr[0] != ']');cptr++);		// pasar por alto los caracteres validos
			if (cptr[0] == 0) break;	// Se termino el fichero
			cptr[0] = 0;
			uppercase(section);
			continue;
		}
		// key + values
		strend = 0;
		pthis->key[keypos].section = section;
		pthis->key[keypos].name = cptr;
		pthis->key[keypos].value = NULL;
		for (;(cptr[0] > ' ')&&(cptr[0] != '=');cptr++);	// recorrer caracteres validos
		if (cptr[0] == 0) break;		// fin
		if (cptr[0] == '=')
		{
			cptr[0] = 0;
			uppercase(pthis->key[keypos].name);
			// leer valor
			for (;cptr[0] == ' ';cptr++);
			if (cptr[0] == '\"') {strend = '\"';cptr++;}
			
			pthis->key[keypos].value = cptr;
			for (;(cptr[0] >= ' ');cptr++);	// recorrer caracteres validos
			if (cptr[0] == 0) break;		// fin
			cptr[0] = 0;
			cptr++;
		}
		keypos++;
		if (keypos >= MAXINIKEYS) break;
	}
	pthis->keycount = keypos;
	return 0;
}
