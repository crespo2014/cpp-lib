// ctime.cpp: implementation of the ctime class.
//
//////////////////////////////////////////////////////////////////////

#include "ctime.h"
#include "cstr.h"
#include "iformat.h"

// definicion de tipos de datos a mostrar
#define tfmt_d		0		//time format
#define tfmt_dd		1
#define tfmt_ddd	2
#define tfmt_dddd	3
#define tfmt_h		4
#define tfmt_hh		5
#define tfmt_H		6
#define tfmt_HH		7
#define tfmt_m		8
#define tfmt_mm		9
#define tfmt_M		10
#define tfmt_MM		11
#define tfmt_MMM	12
#define tfmt_MMMM	13
#define tfmt_s		14
#define tfmt_ss		15
#define tfmt_t		16
#define tfmt_tt		17
#define tfmt_y		18
#define tfmt_yy		19
#define tfmt_yyyy	20
#define tfmt_last	21

// tabla con formato funcion correspondiente
struct _tbl_fmt_fnc
{
	BYTE	type;
	BYTE	width;	// ancho minimo
	BYTE	base;
	const char	*fmt;
};

static struct _tbl_fmt_fnc tbl[] = {
		{tfmt_d		,1,10,"d" },
		{tfmt_dd	,2,10,"dd" },
		{tfmt_ddd	,3,10,"ddd" },
		{tfmt_dddd	,4,10,"dddd" },
		{tfmt_h		,1,10,"h" },
		{tfmt_hh	,2,10,"hh" },
		{tfmt_H		,1,10,"H" },
		{tfmt_HH	,2,10,"HH" },
		{tfmt_m		,1,10,"m" },
		{tfmt_mm	,2,10,"mm" },
		{tfmt_M		,1,10,"M" },
		{tfmt_MM	,2,10,"MM" },
		{tfmt_MMM	,3,10,"MMM" },
		{tfmt_MMMM	,4,10,"MMMM" },
		{tfmt_s		,1,10,"s" },
		{tfmt_ss 	,2,10,"ss" },
		{tfmt_t	 	,1,10,"t" },
		{tfmt_tt	,2,10,"tt" },
		{tfmt_y		,1,10,"y" },
		{tfmt_yy	,2,10,"yy" },
		{tfmt_yyyy	,4,10,"yyyy" },
		{0,0,0,NULL}
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

struct	_time_to_text
{
	const char	*abrev;
	const char	*full;
};

static struct	_time_to_text _day_text[] = {
		{ "dom", "domingo" },
		{ "lun", "lunes" },
		{ "mar", "martes" },
		{ "mie", "miercoles" },
		{ "jue", "jueves" },
		{ "vie", "viernes" },
		{ "sab", "sabado" }
};

static struct _time_to_text _month_text[] = {
		{ "ene", "enero" },
		{ "feb", "febrero" },
		{ "mar", "marzo" },
		{ "abr", "abril" },
		{ "may", "mayo" },
		{ "jun", "junio" },
		{ "jul", "julio" },
		{ "ago", "agosto" },
		{ "sep", "septiembre" },
		{ "oct", "octubre" },
		{ "nov", "noviembre" },
		{ "dic", "diciembre" }
};


ctime::ctime()
{

}

ctime::~ctime()
{

}

/*
Definicion del formato de fecha a mostrar con getc
%x% delimitador del dato
\ secuencia de escape de caracteres.

 */

DWORD ctime::set_format(const char *fmt,IFormat *pformat)
{
	static struct {
		BYTE	letter;
		BYTE	value;
	} extend_tbl[] = {
			{ 'a' , 7 },
			{ 'b' , 8 },
			{ 'f' , 0x0C },
			{ 'n' , 0x0A },
			{ 'r' , 0x0D },
			{ 't' , 0x09 },
			{ 'v' , 0x0B },
			{ 0, 0}
	};
	// lo primero que debe recivirse es un % si es un char estamos jodidos
	BYTE	i;
	BYTE	stext_pos = 0;		// posicion del texto estatico
	mstext_start = 0;
	BYTE	bextend = false;	//indica si el caracter esta precidido por '\'

	const char*	ps=NULL;	//inicio del elemento entre %
	char	c;

	mfmt_count = 0;
	do
	{
		c=*fmt;
		switch(c)
		{
		case 0: break;		// END se ha terminado el formato
		case '%' : 
		{
			if (ps == NULL)
				ps = fmt + 1;
			else
			{
				if (mfmt_count >= tfmt_max) return ERR_FATAL;	// no caben mas formatos
				// buscar el indice se utiliza last para indicar no valido
				// last + idx para los indices extendidos del otro objeto
				for (i=0;i<tfmt_last;i++)
				{
					if (cstr::cscmp(ps,fmt-ps,tbl[i].fmt))
					{
						// inicializacion de item formato
						mfmt_item[mfmt_count].idx = i;
						mfmt_item[mfmt_count].scount = 0;
						mfmt_count++;
						break;
					}
				}
				// no esta definido el formato
				if ((i == tfmt_last) && (pformat) && pformat->getIdx(ps,fmt-ps,&mfmt_item[mfmt_count].idx) )
				{
					mfmt_item[mfmt_count].idx += tfmt_last;
					mfmt_item[mfmt_count].scount = 0;
					mfmt_count++;
				}
				ps=NULL;
			}
			break;
		}
		default:
		{
			if (ps != NULL) break;	// se esta leyendo un formateador
			if (bextend)
			{
				bextend = false;
				// convertir el caracter si es posible de lo contrario se deja como esta
				for (i=0;extend_tbl[i].letter != 0;i++)
				{
					if (c == extend_tbl[i].letter)
					{
						c = extend_tbl[i].value;
						break;
					}
				}
			}
			else
			{
				if (c == '\\') { bextend = true; break;  }
			}
			// almacenar el caracter
			if (stext_pos == sizeof(mfmt_stext)) break;	// no hay espacio para mas texto
			mfmt_stext[stext_pos++] = c;
			if (mfmt_count)
				mfmt_item[mfmt_count-1].scount++;
			else
				mstext_start++;
			break;
		}
		}
		fmt++;
	}while (c);
	return ERR_OK;
}


/*
	toma el tiempo del sistema, para su posterior formateo
 */
void ctime::updatetime()
{
	GetLocalTime(&mdate);
}

void ctime::getf(struct _char_buff * buffer,IFormat* pformat)
{
	struct _nfmt		fmt;
	struct _tfmt_item	*pitem = mfmt_item;
	struct _tbl_fmt_fnc	*fnc;
	char	*pst = mfmt_stext;
	WORD	idx=0;

	fmt.sing_on = 0;

	// texto estatico inicial
	if (mstext_start)
	{
		cstr::csappend(pst,mstext_start,buffer);
		pst += mstext_start;
	}
	// recorrer la estructura de formato
	while(idx < mfmt_count)
	{
		if (pitem->idx < tfmt_last)
		{
			fnc = &tbl[pitem->idx];
			fmt.base = fnc->base;
			fmt.pad_left = fnc->width;
			switch(fnc->type)
			{
			case tfmt_d:
			case tfmt_dd:
				cstr::printN(mdate.wDay,&fmt,buffer);
				break;
			case tfmt_ddd:
				cstr::cappend(_day_text[mdate.wDayOfWeek].abrev,buffer);
				break;
			case tfmt_dddd:
				cstr::cappend(_day_text[mdate.wDayOfWeek].full,buffer);
				break;
			case tfmt_M:
			case tfmt_MM:
				cstr::printN(mdate.wMonth,&fmt,buffer);
				break;
			case tfmt_MMM:
				cstr::cappend(_month_text[mdate.wMonth-1].abrev,buffer);
				break;
			case tfmt_MMMM:
				cstr::cappend(_month_text[mdate.wMonth-1].full,buffer);
				break;
			case tfmt_h:
			case tfmt_hh:
				cstr::printN(mdate.wHour % 12,&fmt,buffer);
				break;
			case tfmt_H:
			case tfmt_HH:
				cstr::printN(mdate.wHour,&fmt,buffer);
				break;
			case tfmt_m:
			case tfmt_mm:
				cstr::printN(mdate.wMinute,&fmt,buffer);
				break;
			case tfmt_s:
			case tfmt_ss:
				cstr::printN(mdate.wSecond ,&fmt,buffer);
				break;
			case tfmt_t:
				cstr::cappend((mdate.wHour >= 12) ? "A" : "P",buffer);
				break;
			case tfmt_tt:
				cstr::cappend((mdate.wHour >= 12) ? "AM" : "PM",buffer);
				break;
			case tfmt_y:
				cstr::printN(mdate.wYear %10 ,&fmt,buffer);
				break;
			case tfmt_yy:
				cstr::printN(mdate.wYear %100 ,&fmt,buffer);
				break;
			case tfmt_yyyy:
				cstr::printN(mdate.wYear,&fmt,buffer);
				break;
			}
		} else {
			if (pformat) pformat->getc(buffer,pitem->idx - tfmt_last);

		}
		// imprimir caracteres estaticos
		if (pitem->scount)
		{
			cstr::csappend(pst,pitem->scount,buffer);
			pst += pitem->scount;
		}
		idx++;
		pitem++;
		if (buffer->size == 0) return;
	}
}
