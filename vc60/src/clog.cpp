// LogClient.cpp: implementation of the CLogClient class.
//
//////////////////////////////////////////////////////////////////////

#include "ctime.h"
#include "clog.h"
#include "stdio.h"
#include "utils.h"
#include "csys.h"

#define _FILENAME_ "log.c"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define LOGCONSEVENT	"Global\\logconsoleevent"	// Usado para activar la pantalla de consola
#define LOGFILEEVENT	"Global\\logfileevent"	// Usado para activar la pantalla de consola


// objeto log estatico para la aplicación, se utilizara cuando no se dispone de mlog y en invocacion estatica
clog	slog;

// definicion de tipos de datos a mostrar en el header del log
#define tfmt_Th		0		//thread id hexadecimal
#define tfmt_TTh	1		// full hexadecimal threadID
#define tfmt_Td		2		// decimal threadID
#define tfmt_To		3		// octal
#define tfmt_TTo	4		// full octal
#define tfmt_Ph		5
#define tfmt_PPh	6
#define tfmt_Pd		7
#define tfmt_Po		8
#define tfmt_PPo	9
#define tfmt_lh		10		// hex line
#define tfmt_llh	11		// full hex line
#define tfmt_ld		12		// decimal line
#define	tfmt_f		13		// file name
#define tfmt_lv		14		// log level decimal
#define tfmt_last	15

// tabla con datos de cada salida o formato
struct _item
{
	BYTE	type;
	BYTE	width;	// ancho minimo
	BYTE	base;
	const char	*fmt;
};
static struct _item tbl[] = {
		{tfmt_Th 	,1,10,	"Th"  },
		{tfmt_TTh	,4,16,	"TTH" },
		{tfmt_Td	,1,10,	"Td"  },
		{tfmt_To	,1,8,	"To"  },
		{tfmt_TTo	,4,8,	"TTo" },
		{tfmt_Ph	,1,16,	"Ph"  },
		{tfmt_PPh	,4,16,	"PPH" },
		{tfmt_Pd	,1,10,	"Pd"  },
		{tfmt_Po	,1,8,	"Po"  },
		{tfmt_PPo	,6,8,	"PPo" },
		{tfmt_lh	,1,16,	"lh"},
		{tfmt_llh	,4,16,	"llh" },
		{tfmt_ld	,1,10,	"ld"},
		{tfmt_f		,0,0,	"f"},
		{tfmt_lv	,1,10,	"lv"},
		{0,0,0,NULL}
};

class cloghead : public IFormat
{
public:
	// obtener el indice correspondiente al formato true si es valido
	virtual bool getIdx(const char* fmt,WORD size,BYTE* idx);

	// obtener la cadena de caracteres dado el indice del formato
	virtual void getc(struct _char_buff * buffer,BYTE idx);

	inline cloghead(DWORD pid,DWORD tid,DWORD line,const char* file,WORD level)
	{
		mpid = pid;
		mtid = tid;
		mline = line;
		mfile = file;
		mlevel = level;
	};
	inline IFormat	*getIFormat() { return this; }
private:
	DWORD	mpid;
	DWORD	mtid;
	DWORD	mline;
	WORD	mlevel;
	const char *mfile;
};

bool cloghead::getIdx(const char* fmt,WORD size,BYTE* idx)
{
	WORD	i;
	for (i=0;i<tfmt_last;i++)
	{
		if (cstr::cscmp(fmt,size,tbl[i].fmt))
		{
			*idx = i;
			return true;
		}
	}
	return false;
}

void cloghead::getc(struct _char_buff * buffer,BYTE idx)
{
	if (idx >= tfmt_last) return;

	struct _item *ptbl = &tbl[idx];
	struct _nfmt fmt;

	fmt.sing_on = 0;
	fmt.base = ptbl->base;
	fmt.pad_left = ptbl->width;

	switch(idx)
	{
	case tfmt_Th:
	case tfmt_TTh:
	case tfmt_Td:
	case tfmt_To:
	case tfmt_TTo:
	{
		cstr::printN(mtid,&fmt,buffer);
		break;
	}
	case tfmt_Ph:
	case tfmt_PPh:
	case tfmt_Pd:
	case tfmt_Po:
	case tfmt_PPo:
	{
		cstr::printN(mpid,&fmt,buffer);
		break;
	}
	case tfmt_lh:
	case tfmt_llh:
	case tfmt_ld:
	{
		cstr::printN(mline,&fmt,buffer);
		break;
	}
	case tfmt_lv:
	{
		cstr::printN(mlevel,&fmt,buffer);
		break;
	}
	case tfmt_f:
	{
		cstr::cappend(mfile,buffer);
		break;
	}
	}
}

clog::clog()
{
	//	Crear evento de disparo de la consola
	m_bAddEndFile	= false;
	m_log_level		= LOG_LERROR;
	m_ilog	= NULL;
	mOnFile = false;
	mOnConsole = false;

	CreateEvents();
}

clog::~clog()
{
	EventsClose();
	mfile.close();
	mconsole.close();
}


// Revisar los eventos para permitir el envio de logs a consola y fichero
DWORD clog::CheckEvents()
{
	DWORD	dwr;
	/*
	if ((m_hconsoleevent != NULL) && (!m_bconsole_ouput)) 
	{
		dwr = WaitForSingleObject(m_hconsoleevent,0);
		if (dwr == WAIT_OBJECT_0) 
		{
			m_log_level = LOG_LLAST;
			mconsole.open();
		}
		else
			mconsole.close();
	}
	 */
	/*
	if (mbeventfile)
	{
		dwr = WaitForSingleObject(m_hfileevent,0);
		switch (dwr)
		{
		case WAIT_OBJECT_0: 
			if (mfile.isOpen()) break;
			createLogFile();
			m_bCloseFile = true;
			m_log_level = LOG_LLAST;
			break;
		default:
			mfile.close();
			break;
		}
	}
	 */
	return ERR_OK;
}

DWORD clog::CreateEvents()
{
	m_hconsoleevent = CreateEventA(NULL,true,false,LOGCONSEVENT);
	m_hfileevent	= CreateEventA(NULL,true,false,LOGFILEEVENT);
	return ERR_OK;
}

DWORD clog::SetEvent(HANDLE m_hevent, BOOL bstate)
{
	if (m_hevent == NULL)	return ERR_HANDLE;
	if (bstate)
		::SetEvent(m_hevent);
	else
		::ResetEvent(m_hevent);
	return ERR_OK;
}



DWORD clog::EventsClose()
{
	if (m_hconsoleevent != NULL) CloseHandle(m_hconsoleevent);
	if (m_hfileevent != NULL)	 CloseHandle(m_hfileevent);
	m_hconsoleevent = NULL;
	m_hfileevent	= NULL;
	return ERR_OK;
}

void clog::consoleEnable()
{
	if (mOnConsole) return;
	mOnConsole = (mconsole.open() == ERR_OK);
}

void clog::consoleDisable()
{
	if (!mOnConsole) return;
	mconsole.close();
	mOnConsole = false;
}

/*
DWORD CLogClient::log_buffer(WORD level, byte *buffer, WORD size, byte width, byte base, char separator, bool browpos)
{
	int		i;
	int		col;
	int		row;
	char	msg[2048];
	char	*cptr;

	DWORD	len;

	if (!IsActiveLogOutput())	return ERR_FATAL;
	if (level > m_log_level)	return ERR_FATAL;
	log(level,"",0,ERR_OK,"Showing %d bytes of data",size); 
	cptr = msg;
	col = 0;
	row = 0;
	for (i = 0;i<(size + 1);i++,col++)
	{
		if (i == size) cptr += sprintf(cptr,"\r\n");
		if ((cptr - msg > (sizeof(msg) - 10)) ||
			(i == size))
		{
			len = strlen(msg);
			log(level,"",0,ERR_OK,"%s",msg); 
			cptr = msg;
		}
		if (i == size) break;

		if (col == width) 
		{
			cptr += sprintf(cptr,"\r\n");
			col = 0;
			row++;
		}
		if ((col == 0) && (browpos)) cptr += sprintf(cptr,"%04X ",i);
		// imprimir el numero en i
		switch (base)
		{
		case 10: cptr += sprintf(cptr,"%03d",buffer[i]);break;
		//case 10: cptr += sprintf(cptr,"%03d",buffer[i]);break;
		case 255: 
			{
				if (buffer[i] < ' ') *cptr = '.'; else *cptr = buffer[i];
				cptr++; *cptr=0;
				break;
			}
		default:
		case 16: cptr += sprintf(cptr,"%02X",buffer[i]);break;
		}

		if (separator != 0) { *cptr = separator; cptr++; *cptr = 0;}
	}
	return ERR_FATAL;
}
 */

/*
 * Metodo seguro para escribir un log. se valida this
 */
DWORD clog::log(WORD level,const char *file, DWORD line, DWORD retval,IText *ptext,const char* format , ...)
{
	if (!this) return retval;
	char	msg[2048];
	int		i;
	struct _char_buff	buff;

	buff.buff = msg;
	buff.size = sizeof(msg);

	va_list arg_ptr;
	*msg = 0;
	do
	{
		// Imprimir el header utilizando ctime
		time.updatetime();
		time.getf(&buff,cloghead(csys::getPID(),csys::getTID(),line,file,level).getIFormat());
		if (!buff.size) break;
		va_start(arg_ptr, format);
		i = _vsnprintf(buff.buff,buff.size,format,arg_ptr);
		va_end(arg_ptr);
		if (i < 0  || i >= buff.size ) break;
		buff.size -= i;
		buff.buff += i;
		if (buff.size <= 2) break;
		*buff.buff++	= '\r';
		*buff.buff++ = '\n';
		buff.size -= 2;
		break;
	} while(false);
	// Enviar el log a las salidas activas
	if (mOnFile) 	mfile.write(msg,buff.buff - msg);
	if (mOnConsole) mconsole.write(msg,buff.buff - msg);
	return retval;

}

DWORD clog::setFilePath(const char *file_path, BOOL tryOpen)
{
	DWORD	rc = mfile.open(file_path,FF_ADD|FF_WR|FF_SH_RD);
	mOnFile = ( rc == ERR_OK);
	return rc;
}

/*
	Generar nombre aleatorio para fichero de logs
 */
DWORD clog::createLogFile()
{
	char path[MAX_PATH];
	char *pbuff = path;
	// carpeta raiz de windows sin el separador
	pbuff = (char*)csys::gettmpFolder(pbuff,path + sizeof(path) - pbuff);
	if (pbuff == NULL) return ERR_NOMEMORY;
	*pbuff = csys::getFileSeparator();
	pbuff++;
	if (pbuff >= path + sizeof(path)) return ERR_FATAL;
	//pegar el nombre del ficher
	return 0;
}

DWORD	clog::setHeadFormat(const char* fmt)
{
	return time.set_format(fmt,cloghead(0,0,0,"",0).getIFormat());
};




