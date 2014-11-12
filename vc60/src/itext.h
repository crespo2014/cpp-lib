

#if !defined(ITEXT_INC)
#define ITEXT_INC


/*
	interfaz utilizada para obtener texto tipo char* 
	Utilidad en logs con mensajes obtenidos del so y otros.
*/

#include "cstr.h"


class IText  
{
public:
	virtual char* getc(char* buff,WORD size) = 0;
	virtual void putc(struct _char_buff *buff) {};

};

#endif // !defined(ITEXT_INC)
