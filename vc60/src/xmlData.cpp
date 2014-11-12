// xmlData.cpp: implementation of the CxmlData class.
//
//////////////////////////////////////////////////////////////////////

#include "xmlData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CxmlData::CxmlData()
{
	m_data.SetMaxMemorySize(4*1024*1024);  //4MB of ram max for xml data
}

CxmlData::~CxmlData()
{

}

char *firstchar(char* ch) 
{
	while ((*ch != 0) && (*ch < ' ')) ch++;
	return ch;
}

void nextchar (char** ch)
{
	while ((**ch != 0) && (**ch < ' ')) (*ch)++;
}

DWORD CxmlData::ProccessXML(char *xml)
{
	// Hacer una maquina de estados, analizando para cada estado el caracter recibido
	// tener cuidado con los cambiso de linea, pueden imposibilitar tener el datoc ompleto
	// hay que tener cuidado con el formato de caracteres, se debe ir tomando los caracteres de uno en uno
	// en funcion del tipo de dato

	/*
	DWORD	lbl_curr;	//etiqueta actual
	DWORD	lbl_prev;	
	DWORD	lbl_parent;
	char*	cptr1;
	char	*ch,*cstart,*cend;
	WORD	csize;

	BOOL	b_instr;	// indica que estamos leyendo un string entre comillas "
	char	*str_start;	// es el comienzo de un string que puede ser cualquier cosa

	m_data_size = 0;
	ch = xml;

	XML_LBL *curr_lbl,*prev_lbl;
	m_data.Release();

	m_data.SetSize(10000);
	cptr1 = xml;

	str_start = NULL;
	for (;*ch != 0;ch++)
	{
		if (*ch < ' ') continue;		//caracteres bajos y espacios ignorados, si estamos en medio antes o despues de un texto da igual
		// si estamos entre " hay que esperar hasta encontrar otro "
		if (b_instr) 
		{
			if (*ch == '\\') 
			{

				continue;	// revisar el proximo caracter
			}
			if (*ch != '\"') continue;
		}
		if ((*ch = ' ') && (str_start != NULL))		// esto puede ser el fin de un texto
		{
			// indicar el fin del elemento previamente abierto
		}
		if (str_start == NULL) str_start = ch;	//aqui comienza este texto



	//while ((*cptr1 != 0) && (*cptr1 != '<')) cptr1++;
	switch (*ch)
	{
		case '<': 
			// inicio de etiqueta

			*breaktype = BRK_TAG_START;
			*cptr = 0;
			cptr++;
			break;
		case '>':
			*breaktype = BRK_TAG_END;
			return cptr;
		case '\"':
			// validar si es el primero o que 
		default:
			do_next = true;
			break;
		}
		if (strncmp(cptr,"\\>",2)== 0)
		{
			*cptr = 0;
			*cptr += 2;
			*breaktype = BRK_TAG_END;
			break;
		}

	}
	

	for (;;)
	{
		if (*cptr1 == '<') break;
		cptr1++;
	}

	// ir al proximo byte valido
	while ((*ch != 0) && (*ch < ' ')) ch++;

	*/
	return ERR_OK;
}

DWORD CxmlData::GetLabelValue(char *label, char **pval)
{
	return ERR_OK;
}

DWORD CxmlData::GetFirstLabel(DWORD *lbl_index, char **label, char **value)
{
	XML_LBL	*plbl;
	BYTE	*pbuff;
	*lbl_index = 0;
	pbuff = (BYTE*)m_data.GetMemBuffer();
	pbuff+= *lbl_index;
	plbl = (XML_LBL*)pbuff;
	*label = plbl->lbl_data;
	*value = *label;
	(*value)  += (strlen(*label)+1);

	return ERR_OK;
}

DWORD CxmlData::GetNextLabel(DWORD *lbl_index, char **label, char **value)
{
	return ERR_OK;
}

DWORD CxmlData::GetChildLabel(DWORD *lbl_index, char **label, char **value)
{
	return ERR_OK;
}

DWORD CxmlData::GetParentLabel(DWORD *lbl_index, char **label, char **value)
{
	return ERR_OK;
}

DWORD CxmlData::GetPrevLabel(DWORD *lbl_index, char **label, char **value)
{
	return ERR_OK;
}

DWORD CxmlData::GetAttribute(DWORD lbl_index, char *attr, char **value)
{
	return ERR_OK;
}

char* CxmlData::GetNextBreak(char *start, BreakType *breaktype)
{
	char*	cptr = start;
	BOOL	do_next;
	do
	{
		do_next = false;
		switch (*cptr)
		{
		case '0':
			*breaktype = BRK_END;

		case '<': 
			*breaktype = BRK_TAG_START;
			*cptr = 0;
			cptr++;
			break;
		case '>':
			*breaktype = BRK_TAG_END;
			return cptr;
		case '\"':
			// validar si es el primero o que 
		default:
			do_next = true;
			break;
		}
		if (strncmp(cptr,"\\>",2)== 0)
		{
			*cptr = 0;
			*cptr += 2;
			*breaktype = BRK_TAG_END;
			break;
		}
	} while ((*cptr != 0) && do_next);
	return cptr;
}

DWORD CxmlData::Stack_Push(XML_LBL *curr_lbl, char *data, WORD size)
{
	return ERR_OK;

}
