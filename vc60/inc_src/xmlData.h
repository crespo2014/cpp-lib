// xmlData.h: interface for the CxmlData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLDATA_H__CE79EC24_588C_4D2F_9C6A_A55189C300B4__INCLUDED_)
#define AFX_XMLDATA_H__CE79EC24_588C_4D2F_9C6A_A55189C300B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\INC_SRC\bObject.h"
#include "memarray.h"	// Added by ClassView

/*
	Estructura de datos:
	
	los bloques de informacion son de la siguiente forma

  --- Inicio de posicion relativa
	WORD	lbl_size	;tamaño de toda la etiqueta  o ubicacion relativa de la proxima etiqueta
	WORD	lbl_prev	;ubicacion relativa de la etiqueta previa
	WORD	lbl_child	;ubicacion relativa de la primera etiqueta hija
	char[]	datos de la etiqueta separados por ceros
			<nombre><valor> [<atributo><valor>] \0x0
			un atributo nulo es el fin de los atributos

	

El valor cero indica que dicho elemento no existe, las ubicaciones absolutas se obtienen sumando la relativa al comienzo de la etiqueta


*/

#define LABAL_HEAD	0xABCD

typedef enum _BreakType
{
	BRK_TAG_START = 0,
	BRK_TAG_END,
	BRK_TAG_CLOSE,
	BRK_EQUAL,
	BRK_ERROR,
	BRK_END

//	Text = 0,
//	QuotedText,
//	TagStart,		/* "<"			*/
//	TagEnd,			/* "</"			*/
//	CloseTag,		/* ">"			*/
//	Equals,			/* "="			*/
//	Declaration,	/* "<?"			*/
//	ShortHandClose,	/* "/>"			*/
//	Clear,
//	Error
}BreakType;

typedef struct
{
	WORD	lbl_head;	// siempre ABCD para validar que esta estructura es valida
	WORD	lbl_size;	// tamaño de toda la etiqueta  o ubicacion relativa de la proxima etiqueta
	WORD	lbl_prev;	// ubicacion relativa de la etiqueta previa
	WORD	lbl_child;	// ubicacion relativa de la primera etiqueta hija
	WORD	lbl_parent;	// ubicacion relativa de la etiqueta padre
	char	lbl_data[1];	//etiqueta\x0attributo1\x0attr2\x0valor
}XML_LBL;

typedef struct //stack_data
{
	XML_LBL*	curr_lbl;
	WORD		last_op;
	char		*dstart,*dend;	// datos
}_SDATA;

class CxmlData : public CbObject  
{
public:
	DWORD Stack_Push(XML_LBL* curr_lbl,char* data,WORD size);
	char* GetNextBreak(char* start,BreakType* breaktype);
	DWORD	GetAttribute	(DWORD  lbl_index, char *attr,   char **value);
	DWORD	GetPrevLabel	(DWORD *lbl_index, char **label, char **value);
	DWORD	GetParentLabel	(DWORD *lbl_index, char **label, char **value);
	DWORD	GetChildLabel	(DWORD *lbl_index, char **label, char **value);
	DWORD	GetNextLabel	(DWORD *lbl_index, char **label, char **value);
	DWORD	GetFirstLabel	(DWORD *lbl_index, char **label, char **value);
	
	DWORD	GetLabelValue(char* label,char** pval);	// label incluye el arbol de etiqueta separados por \x0 solo se devuelve la primera etiqueta con dicho nombre
	DWORD	ProccessXML(char* xml);

	CxmlData();
	virtual ~CxmlData();

private:
	CMemArray	m_data;
	DWORD		m_data_size;
	
	// para el procesamiento y otras tareas
	XML_LBL	*curr_lbl;
	char	*dt_begin;
	char	*dt_end;
	WORD	*dt_size;
};

#endif // !defined(AFX_XMLDATA_H__CE79EC24_588C_4D2F_9C6A_A55189C300B4__INCLUDED_)
