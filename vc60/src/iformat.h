#if !defined(iformat)
#define iformat
/*
 * Los datos que seran mostrado en el formato deben ser almacenados en el objeto
 */
class IFormat
{
public:
	// obtener el indice correspondiente al formato true si es valido
	virtual bool getIdx(const char* fmt,WORD size,BYTE* idx) = 0;
	// obtener la cadena de caracteres dado el indice del formato
	virtual void getc(struct _char_buff * buffer,BYTE idx) = 0;
};

#endif
