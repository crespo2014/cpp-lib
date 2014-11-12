/*
Parser de XML. analiza y carga en memoria el contenido de  un fichero XML
esta implementado como una maquina de estados. cada estado corresponde a una 
funcion que procesa los datos del fichero. Por ello se utiliza un ptr a la 
funcion que actualmente esta procesando los datos. Los caracteres se leen del
fichero xml y se envian uno a uno al parser para que la funcion correspondiente
lo analize y decida que hacer con el.
hay que optimizar la lectura de datos del fichero, por ello se debe cargar un
bloque de 4kb de una vez e ir leyendo datos de 32bits enviando al parser en 4
veces. Es posible que el parser pueda recivir los datos de 32bits y se ocuparia 
de optimizar su uso. Si el utlimo dato no es multiplo de 4 debe ser enviado en
3 2 o 1 parte. La api del OS ya bufferea el acceso a ficheros (Verificar).
Hay que implementar un objeto de memoria que permita manejar un buffer temporal 
que puede ser desechado o utilizado segun interese. Este buffer debe admitir
agregar caracteres uno o uno formando un bloque de memoria indivisible
El xml se almacena en memoria como nodos. con la siguiente definicion
next *   ;proximo nodo de mismo nivel
parent*  ;nodo padre todo los nodos next comparten el padre
name	 ;nombre del nodo
attributes; estructura con los datos de los atributos
namespace ; si el nombre contiene : se separa el namespace del nombre

Los atributos se almacenan en una estructura de la forma.
next	;proximo atributo de la lista.
name	;nombre del atributo
namespace ; si dispone de el se almacena aqui
value	; valor del atributo

Especificaciones XML

los caracteres validos son : ::=   	#x9 | #xA | #xD | [#x20-#xD7FF] | [#xE000-#xFFFD] | [#x10000-#x10FFFF]
no pueden contener la cadena xml en lowercase
los nombres deben comenzar con una letra

[4]   	NameStartChar	   ::=   	":" | [A-Z] | "_" | [a-z] | [#xC0-#xD6] | [#xD8-#xF6] | [#xF8-#x2FF] | [#x370-#x37D] | [#x37F-#x1FFF] | [#x200C-#x200D] | [#x2070-#x218F] | [#x2C00-#x2FEF] | [#x3001-#xD7FF] | [#xF900-#xFDCF] | [#xFDF0-#xFFFD] | [#x10000-#xEFFFF]
[4a]   	NameChar	   ::=   	NameStartChar | "-" | "." | [0-9] | #xB7 | [#x0300-#x036F] | [#x203F-#x2040]
[5]   	Name	   ::=   	NameStartChar (NameChar)*
[6]   	Names	   ::=   	Name (#x20 Name)*
[7]   	Nmtoken	   ::=   	(NameChar)+
[8]   	Nmtokens	   ::=   	Nmtoken (#x20 Nmtoken)*


*/
#include "sys.c"


struct _ATTR
{
	char	*name;
	char	*namespace;
	char	*value;
	struct _ATTR *pnext;
};

struct _NODE
{
	char	*name;
	char	*namespace;
	struct _NODE	*pnext,*pparent;
	struct _ATTR*	pattr;
};

struct _XML_PARSER
{
	int size;		// tamaño actual de los datos.
};

DWORD parseWaitNode(char pChar)
{
    // ignorar caracteres de control
   if ((pChar & 0x70 == 0) || (pChar == 0x20)) return ERR_OK; 
   if (pChar != '<') return ERR_FATAL;
   return ERR_OK;
} 

DWORD parseNodeName(char c)
{
	char *name;
	// No se admiten espacios en el nombre del nodo
	if (pChar & 0x70 == 0) return ERR_FATAL;
	if (c == ':')
	{
		if (size == 0) return ERR_FATAL;
		
	}
	if (c == 0x20)
	{
		if (size == 0) return ERR_FATAL;
		mem_commit(&name);
		mem_new(node);
		node->name = name;
		
	}
	mem_pushChar(c);
}

/*
	Se ha leido el nombre del nodo o un atributo 
	y se espera el nombre de otro attributo
	el fin del nodo > o el fin /
*/
DWORD parseWaitAttrName(char c)
{
	if isletter(c)
	{
	}
	if (c == 
}





