
#include "log.h"

struct _LOG	glog;




/*
	Definir el comienzo o cabecera de las trazas enviadas al fichero de log
	Parametros:
*/

char* log_getheader(struct _LOG *plog,char *cstr, WORD size, WORD level,const char *file, const char* fnc, int line)
{
	int	i,len;
	char	*cptr = cstr;
	char	*pchr;
	int		tid;
	int	pid;

#ifdef WIN32
	SYSTEMTIME date;

	pid = GetCurrentProcessId();
	tid = GetCurrentThreadId();
#else
	struct tm 	*newtime;
    time_t 		long_time;

	pid = getpid();
	//tid = (unsigned int)pthread_self();
	tid=0;
	
#endif

	for (;;)
	{
		len = cstr + size - cptr-1;
#ifdef WIN32
		//**********************************************************
		if (plog->show_flag & LOG_SHOW_DATETIME) GetLocalTime(&date);

		if (plog->show_flag & LOG_SHOW_DATE)
		{
			i = GetDateFormatA(LOCALE_SYSTEM_DEFAULT,0,&date,"yyyy/MM/dd",cptr,len);
			if ((i<0) || (i > len)) break;
			cptr += (i-1);
			len -= i;
		}
		if (plog->show_flag & LOG_SHOW_TIME)
		{
			i = GetTimeFormatA(0,TIME_FORCE24HOURFORMAT,&date," hh:mm:ss ",cptr,len);
			if ((i<0) || (i > len)) break;
			cptr += (i-1);
			len -= i;
		}
		if (plog->show_flag & LOG_SHOW_DATETIME)
		{
			i = snprintf(cptr,len,"\t");
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}
#else
		time( &long_time );
		newtime = localtime( &long_time );

		if (plog->show_flag & LOG_SHOW_DATE)
		{
			i= snprintf(cptr, len,"%04d/%02d/%02d",newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday);
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}
		if (plog->show_flag & LOG_SHOW_TIME)
		{
			i = snprintf(cptr, len," %02d:%02d:%02d ",newtime->tm_hour,newtime->tm_min,newtime->tm_sec);
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}
		if (plog->show_flag & LOG_SHOW_DATETIME)
		{
			i = snprintf(cptr,len,"\t");
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}
#endif
		//**********************************************************
		if (plog->show_flag & LOG_SHOW_LEVEL)
		{
			i = snprintf(cptr,len,"%u\t",level);
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}
		//**********************************************************
		if (plog->show_flag & LOG_SHOW_PID)
		{
			i = snprintf(cptr,len,"P%08X\t",pid);
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}
		//**********************************************************
		if (plog->show_flag & LOG_SHOW_THREAD)
		{
			i = snprintf(cptr,len,"T%08X\t",tid);
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}
		//**********************************************************
		if (plog->show_flag & LOG_SHOW_FILE_NAME)
		{
			// Se puede cojer solo el nombre del fichero
			pchr = strrchr(file,'\\');
			if (pchr != NULL) file = pchr + 1;
			i = snprintf(cptr,len,"%s ",file);
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}

		if (plog->show_flag & LOG_SHOW_FNC_NAME)
		{
			i = snprintf(cptr,len," %s",fnc);
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}

		if (plog->show_flag & LOG_SHOW_FILE_LINE)
		{
			i = snprintf(cptr,len,":%d",line);
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}

		if (plog->show_flag & (LOG_SHOW_FILE_LINE|LOG_SHOW_FNC_NAME|LOG_SHOW_FILE_NAME) )
		{
			i = snprintf(cptr,len,"\t");
			if ((i<0) || (i > len)) break;
			cptr += i;
			len -= i;
		}
		//**********************************************************
		break;
	}
	return cptr;
}

DWORD log_isActiveOutPut(struct _LOG *plog)
{
	return 1;
}
/*
	Enviar la traza a las salidas activas
*/
DWORD log_send(struct _LOG *plog, DWORD retval, void *pBuffer, DWORD size)
{
	if ((plog->file_path != NULL) && (*plog->file_path != 0))
	{
		plog->hfile = fopen(plog->file_path,"a");
	}
	if (plog->hfile != NULL)
    {
		fwrite(pBuffer,size,1,plog->hfile);
		fflush(plog->hfile);
		fclose(plog->hfile);
    }
    if (plog->bconsole_ouput == 1) fputs(pBuffer,stdout);

	return retval;
}

/*
	Esta funcion se invoca para dejar una traza en el sistema.
	Utiliza el nivel de log, el fichero fuente, la linea, el nombre de la funcion ,
	el valor a devolver, y el texto de log
*/
DWORD log_write(struct _LOG *plog,WORD level,const char *file,const char* fnc_name,int line,DWORD retval,const char *format, ...)
{
	char	msg[2048];
	char	*cptr;
	int		i;
	va_list arg_ptr;
	WORD	len;
	if ((plog == NULL) || (level > plog->level) || (!log_isActiveOutPut(plog))) return retval;

	*msg = 0;
	len = sizeof(msg);
	cptr = log_getheader(plog,msg,len,level,file,fnc_name,line);
	for (;;)
	{
		va_start(arg_ptr, format);
		len = sizeof(msg)- (cptr-msg-2);
		i = vsnprintf(cptr,len,format,arg_ptr);
		va_end(arg_ptr);
		if ((i<0) || (i > len)) break;
		cptr += i;
		len -= i;
		if (plog->show_flag & LOG_SHOW_UNIX)
			i = snprintf(cptr,len,"\n");
		else
			i = snprintf(cptr,len,"\r\n");
		if ((i<0) || (i > len)) break;
		cptr += i;
		len -= i;
		break;
	}
	len = strlen(msg);
	return log_send(plog,retval,msg,len);
}

