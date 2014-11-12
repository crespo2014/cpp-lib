// Keywords.cpp: implementation of the CKeywords class.
//
//////////////////////////////////////////////////////////////////////

#include "Keywords.h"

#define _FILENAME_ "Keywords.c"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKeywords::CKeywords()
{
	m_ver = "Class CKeywords " CLASS_VER;
	m_key_count = 0;
	m_bUpperCase = false;
	m_page.SetMaxSize(4000);
}

CKeywords::~CKeywords()
{
	m_page.Release();
}

/*
	Procesa una linea de comando creando un buffer lineal y obteniendo todas las keys
	
	-KEYWORD1 "value1" -KEYWORD2 value2 -KEY4 val4
	se quitan los espacios al comienzo del valor a menos que se especifique "
	la cadena termina con espacio a menos que haya empezado con un signo (")
	el nombre de las keyword se convierte a mayuscula
*/

DWORD CKeywords::ProcessCmdLine(char *cmd_line)
{
	char	*fnc_name = "CKeywords::ProcessCmdLine";
	char*	cptr;
	char*	kptr;
	char*	tptr;
	char	strend;		//delimitador de string
	int		str_len;

	m_key_count = 0;
	str_len = strlen(cmd_line);
	if (m_page.CreatePage(str_len + 1) == NULL) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in CreatePage(%d)",fnc_name,__LINE__,str_len+1);
	m_data_size = m_page.GetSize();

	cptr = cmd_line;
	kptr = (char*)m_page.GetPage();
	for(;;)
	{
		kptr[0] = 0;	//nueva key es cero
		// recorrer espacios hasta -
		for (;cptr[0] == ' ';cptr++);
		
		if (cptr[0] == 0) break;
		if (cptr[0] != '-') break;	// solo se admite esto
		cptr++;
	
		// copiar nombre del key
		tptr = kptr;						// para convertir a mayusculas
		for (;;cptr++,kptr++)
		{
			if (cptr[0] == 0) break;
			if (cptr[0] == ' ')	break;
			kptr[0] = cptr[0];
		}
		kptr[0] = 0;
		kptr++;
		_strupr(tptr);

		// valor
		strend = ' ';
		for (;cptr[0] == ' ';cptr++);	
		
		if (cptr[0] == '-')  {cptr--;break;}			// falta el valor de la variable
		if (cptr[0] == '\"') {strend = '\"';cptr++;}
		if (cptr[0] == 0)	 {cptr--;break;}			//fin key sin valor
		
		BOOL	bflag;
		bflag = false;
		for (;;cptr++,kptr++)
		{
			kptr[0] = cptr[0];		// tomar char sea cual sea
			if (cptr[0] == '\"')
			{
				if (cptr[1] == '\"') {cptr++;continue;}
			}
			if (cptr[0] == strend) break;
			if (cptr[0] == 0) {cptr--;break;}
		}
		kptr[0] = 0;	// fin de la variable
		kptr++;
		cptr++;
	}
	return ExtractKeywords();
}

// Extrae todas las keywords de la estructura lineal que representa m_data
// key valor pareja separada por cero
DWORD CKeywords::ExtractKeywords()
{
	char	*fnc_name = "CKeywords::ExtractKeywords";

	char*	cptr;
	m_key_count = 0;
	cptr = (char*)m_page.GetPage();

	while (cptr[0] != 0)
	{
		if (m_key_count >= MAX_KEYWORDS) return LOG_TERROR ERR_FATAL,"%s keyword count overflow",fnc_name);
		m_keys[m_key_count].name = cptr; if (m_bUpperCase) _strupr(cptr);
		while (cptr[0] != 0) cptr++;	//buscar el valor
		cptr++;
		m_keys[m_key_count].value = cptr;
		while (cptr[0] != 0) cptr++;	//ir al final del valor
		cptr++;
		m_keys[m_key_count].section = "";
		m_key_count++;
	}
	return ERR_OK;
}

/*
	Adiciona una key a una linea de comando y coloca el puntero despues del 0
	si el valor comienza con espacios incorpora un (") al comienzo 
*/

DWORD CKeywords::AddToCmdLine(char **sptr, char *key, char *value)
{
	char*	pcmd;
	char*	kptr;
	WORD	count;
	char	strend;

	strend = ' ';
	pcmd = *sptr;
	count = 0;

	pcmd[0] = 0;
	if (key[0] == 0) return 0;

	pcmd[0] = '-';
	pcmd++;
	kptr = key;
	for (;kptr[0] != 0;pcmd++,kptr++) pcmd[0] = kptr[0];
	pcmd[0] = ' ';
	pcmd++;
	if (value[0] == ' ') {pcmd[0] = '\"';pcmd++;strend = '\"';}

	for (;value[0] != 0;pcmd++,value++) 
	{
		pcmd[0] = value[0];
		if (value[0] == '\"') {pcmd++;pcmd[0]='\"';}
	}
	pcmd[0] = strend;
	pcmd[1] = 0;
	pcmd++;
	*sptr = pcmd;

	return ERR_OK;
}

DWORD CKeywords::LookKeyword(char *keyword,char** cptr,bool trace)
{
	char	*fnc_name = "CKeywords::LookKeyword";
	//Func_Start(fnc_name);

	*cptr = NULL;
	WORD i;
	for (i=0;i<m_key_count;i++)
		if (strcmp(m_keys[i].name,keyword) == 0) 
		{
			*cptr = m_keys[i].value;
			return ERR_OK;
		}
	if (!trace) return ERR_FATAL;
	return LOG_TERROR ERR_FATAL,"%s keyword '%s' not found ",fnc_name,keyword);
}

DWORD CKeywords::GetEnv(char *keyword, char **cptr, bool trace)
{
	*cptr = getenv(keyword);
	if (*cptr != NULL) return ERR_OK;
	if (!trace) return ERR_FATAL;
	return LOG_TERROR ERR_FATAL," variable '%s' not found ",keyword);
}

DWORD CKeywords::ProcessArgLine(char *arg[], int count)
{
	int		pos;
	char	*cptr;
	char	*fnc_name = "CKeywords::ProcessArgLine";
	
	m_key_count = 0;
	m_data_size = 0;
	for (pos=0;pos<count;pos++) 
		m_data_size+= strlen(arg[pos]);
	if (m_page.CreatePage(m_data_size) == NULL) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in CreatePage(%d)",fnc_name,__LINE__,m_data_size);
	m_data_size = m_page.GetSize();
	
	for (pos = 1;pos < count;pos++)
	{
		if (m_key_count >= MAX_KEYWORDS) return LOG_TERROR ERR_FATAL,"%s keyword count overflow",fnc_name);
		cptr = arg[pos];
		if (*cptr != '-') break;	//el campo debe empezar con -
		cptr++;
		if (m_page.addString(cptr,&m_keys[m_key_count].name) != ERR_OK) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in addString(%s)",fnc_name,__LINE__,cptr);
		if (m_bUpperCase) _strupr(m_keys[m_key_count].name);
		pos++;
		if (pos >= count) break;
		if (m_page.addString(arg[pos],&m_keys[m_key_count].value) != ERR_OK) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in addString(%s)",fnc_name,__LINE__,arg[pos]);
		m_key_count++;
	}
	return ERR_OK;
}

DWORD CKeywords::BreakLine(char *line, char delimiter, char **next_line)
{
	char	*cptr;
	if (line[0] == 0) return ERR_EOF;
	cptr = strchr(line,delimiter);
	if (cptr == NULL)
		*next_line = "";
	else
		*next_line = (cptr+1);
	cptr[0] = 0;
	return ERR_OK;
}

DWORD CKeywords::Process_IniFile(char *file_path)
{
	/*
		formato del fichero
		[xxx]		- inicio de secion **** el ] no es obligatorio
		key=val		- key : debe comenzar con un caracter alfanumerico, puede haer espacios o TAB antes de y depues del =
					-		no puede contener espacios no caracteres <32 en el nombre
					- val : solo puede contener caracteres validos ascii >32
					- No usar " para delimitar nada, pues seran tratadas como parte del valor 
	*/
	char	*fnc_name = "CKeywords::Process_IniFile";
	char	line[1050];
	char*	cptr;		// posicion que se esta tratando
	char	*cptr1;
	char	*sptr1;
	char*	section;	// seccion que se esta tratando
	char	*key;
	FILE*	file;

	m_key_count = 0;
	section = "";
	
	file = fopen(file_path,"r");
	if (file == NULL) return LOG_TERROR ERR_FATAL,"%s failed to open file %s",fnc_name,file_path);
	if (m_page.CreatePage(3000) == NULL) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in CreatePage(%d)",fnc_name,__LINE__,3000);
	m_data_size = m_page.GetSize();
		
	while (fgets(SSIZE(line),file) != NULL)
	{
		cptr = line;
		for(;(*cptr > 0)&& (*cptr <= 32);cptr++);	//ignorar caracteres no validos al comienzo de la linea
		if (cptr[0] == '[')
		{
			// inicio de seccion
			cptr++;
			sptr1 = strchr(cptr,']');
			if (sptr1 != NULL)
			{
				*sptr1 = 0;
				m_page.addString(cptr,&section);
				continue;
			}
			for (sptr1=cptr;(*sptr1 >= ' ') || (*sptr1 < 0);sptr1++);*sptr1 = 0;
			m_page.addString(cptr,&section);
			continue;
		}
		if (!isalpha(line[0]) ) continue;	// si no tiene caracteres alfanumericos es un comentario
		// llegado a este punto debemos tener una linea tipo key=val
		if (m_key_count >= MAX_KEYWORDS) return LOG_TERROR ERR_FATAL,"%s keyword count overflow",fnc_name);
		key = cptr;
		cptr = strchr(cptr,'=');if (cptr == NULL) continue;	// si no hay = esta mal
		*cptr = 0;cptr++;

		for (cptr1=key;((*cptr1 > ' ') || (*cptr1 <0));cptr1++);	// solo caracteres validos
		if (m_page.addString(key,&m_keys[m_key_count].name,cptr1-key) != ERR_OK) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in addString",fnc_name,__LINE__);
		_strupr(m_keys[m_key_count].name);
				
		for(;((*cptr <= ' ') && (*cptr > 0));cptr++);		//ignorar espacios y caracteres no validos antes del valor
		if (*cptr == '\"') cptr++;
		cptr1 = cptr;
		for (;((*cptr1 >= ' ') || (*cptr1 <0));cptr1++);	// solo caracteres >=32 para el valor
		if (m_page.addString(cptr,&m_keys[m_key_count].value,cptr1-cptr) != ERR_OK) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in addString",fnc_name,__LINE__);
		m_keys[m_key_count].section = section;
		m_key_count++;
	}
	fclose(file);
	return ERR_OK;
}

DWORD CKeywords::IniParam_Look(char *keyword, char **val, char *section)
{
	int i;
	for (i=0;i<m_key_count;i++)
	{
		if ((section) && (m_keys[i].section) && (strcmp(section,m_keys[i].section) != 0)) continue;
		if (strcmp(keyword,m_keys[i].name) != 0) continue;
		*val = m_keys[i].value;
		return ERR_OK;
	}
	return LOG_TERROR ERR_FATAL," failed to get keyword %s from ini file",keyword);
}

char* CKeywords::GetKey(WORD index)
{
	if (index >= m_key_count) return NULL;
	return m_keys[index].value;
}

DWORD CKeywords::Process_Line(char *line, char delimiter)
{
	char	*fnc_name = "CKeywords::Process_Line";
	int		len;

	m_key_count = 0;
	len = strlen(line);
	if (m_page.CreatePage(len + 1) == NULL) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in CreatePage(%d)",fnc_name,__LINE__,len);
	m_data_size = m_page.GetSize();
	
	char	*cptr;
	cptr = (char*)m_page.GetPage();
	strcpy(cptr,line);

	for (;;)
	{
		if (m_key_count >= MAX_KEYWORDS) return LOG_TERROR ERR_FATAL,"%s keyword count overflow",fnc_name);
		m_keys[m_key_count].value = cptr;
		m_keys[m_key_count].section = "";
		m_keys[m_key_count].name = "";
		m_key_count++;
		cptr = strchr(cptr,delimiter);
		if (cptr == NULL) break;
		*cptr = 0;
		cptr++;
	}
	return ERR_OK;
}

// Linea en formato de unix, donde se admiten parametros en blanco ej. -<param> <["]value["]>
DWORD CKeywords::ProcessCmdLine_UNIX(char *cmd_line)
{
	char	*fnc_name = "CKeywords::ProcessCmdLine_UNIX";
	int		len;

	m_key_count = 0;
	len = strlen(cmd_line);
	if (m_page.CreatePage(len + 1) == NULL) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in CreatePage(%d)",fnc_name,__LINE__,len);
	m_data_size = m_page.GetSize();

	// Transformar la linea de comando en una estructura lineal separada por ceros y actualizar las keys
	char*	cptr;
	char*	kptr;
	char	strend;		//delimitador de string
	cptr = cmd_line;
	kptr = (char*)m_page.GetPage();
	
	for(;;)
	{
		*kptr = 0;	//nueva key es cero
		// recorrer espacios hasta -
		for (;cptr[0] == ' ';cptr++);
		
		if (cptr[0] == 0) break;
		if (cptr[0] != '-') break;	// solo se admite esto
		cptr++;
	
		// copiar nombre del key
		for (;;cptr++,kptr++)
		{
			if (cptr[0] == 0) break;
			if (cptr[0] == ' ')	break;
			kptr[0] = cptr[0];
		}
		kptr[0] = 0;
		kptr++;

		// valor
		strend = ' ';
		for (;cptr[0] == ' ';cptr++);	//ignorar espacios
		
		if ((cptr[0] == '-')	|| (*cptr == 0))			// nuevo parametro o fin de cadena
		{
			// falta el valor de la variable
			*kptr = 0;
			kptr++;
			continue;
		}	
		if (cptr[0] == '\"') {strend = '\"';cptr++;}
		
		for (;;cptr++,kptr++)
		{
			kptr[0] = cptr[0];		// tomar char sea cual sea
			if (cptr[0] == '\"')
			{
				if (cptr[1] == '\"') {cptr++;continue;}	// las comillas dobles se transforman en simples
			}
			if (cptr[0] == strend) break;
			if (cptr[0] == 0) {cptr--;break;}
		}
		kptr[0] = 0;	// fin de la variable
		kptr++;
		cptr++;
	}
	return ExtractKeywords();
}

DWORD CKeywords::GetKeyword(WORD index, char **keyword,char** value,char** section)
{
	if (index >= m_key_count) return ERR_EOF;
	*keyword = m_keys[index].name;
	*value	 = m_keys[index].value;
	if (section != NULL) *section = m_keys[index].section; 
	return ERR_OK;
}


DWORD CKeywords::Key_Get(char *val, WORD valsize, char *key, char *section)
{
	char*	cptr;
	*val = 0;
	if (IniParam_Look(key,&cptr,section) != ERR_OK) return ERR_FATAL;
	strncat(val,cptr,valsize);
	return ERR_OK;
}

/*
	Procesa una linea de un fichero ini, el contenido de la linea es alterado
	por lo que se recomienda tener una copia de la misma si se necesita para uso posterior
*/
DWORD CKeywords::Process_lineV1(char *line, WORD *ltype, char **key, char **val)
{
		/*
		formato de la linea
		[xxx]		- inicio de secion **** el ] no es obligatorio
		key=val		- key : debe comenzar con un caracter alfanumerico, puede haer espacios o TAB antes de y depues del =
					-		no puede contener espacios no caracteres <32 en el nombre
					- val : solo puede contener caracteres validos ascii >32
					- No usar " para delimitar nada, pues seran tratadas como parte del valor 
	*/
	char*	cptr;		// posicion que se esta tratando
	char	*sptr1;
	bool	bval_delim;

	char	*fnc_name = "CKeywords::Process_lineV1";

	*key = "";*val = "";
	cptr = line;
	for(;(*cptr > 0)&&(*cptr <= ' ');cptr++);	//ignorar caracteres no validos al comienzo de la linea
	if (cptr[0] == '[')
	{
		// inicio de seccion
		cptr++;
		*key = cptr;
		sptr1 = strchr(cptr,']');
		if (sptr1 == NULL)
		{
			LOG_TWARNING "%s->Warning ... Sign ']' is missing for line %s",fnc_name,line);
		}
		else
			*sptr1 = 0;
		for (sptr1=cptr;((*sptr1 >= ' ') || (*sptr1 < 0));sptr1++);*sptr1 = 0;
		*ltype = LT_SECTION;
		return ERR_OK;
	}
	if (!isalpha(line[0]) ) 
	{
		*ltype = LT_COMMENT;
		return ERR_OK;
	}
	// key=val
	*key = cptr;
	cptr = strchr(cptr,'=');
	if (cptr == NULL)
	{
		*ltype = LT_ERROR;
		return LOG_TERROR ERR_FATAL,"%s->Sign '=' is missing for line %s",fnc_name,line);
	}
	*cptr = 0;cptr++;
	for (sptr1=*key;*sptr1 != 0;sptr1++)
		if ((*sptr1<=' ') && (*sptr1 >0)) *sptr1=0;			// ignorar espacios y caracteres no validos en key
	_strupr(*key);
	for(;((*cptr <= ' ') &&(*cptr > 0));cptr++);						//ignorar espacios y caracteres no validos antes del valor
	if (*cptr == '\"')
	{
		cptr++;
		bval_delim = true;
	}
	else
		bval_delim = false;
	*val = cptr;
	for (;((*cptr >= ' ') || (*cptr <0));cptr++);*cptr = 0;	// solo caracteres >=32 para el valor
	if ((*cptr == '\"') && bval_delim) *cptr = 0;
	*ltype = LT_KEY;
	return ERR_OK;
}

DWORD CKeywords::IniFile_SetKey(char *file_path, char *key, char *val, char *section)
{
	static char	line[1024];
	static char	tmp_line[1024];
	char	bdoit;				// indica que la key ya ha sido insertada
	FILE*	file_old;
	FILE*	file_new;
	WORD	ltype;
	char	*fkey,*fval;
	char	fsection[100];	//seccion actual

	char	*fnc_name = "CKeywords::IniFile_SetKey";

	sprintf(tmp_line,"%s.%d",file_path,GetCurrentProcessId());
	if (rename(file_path,tmp_line) != 0)
		return LOG_TERROR ERR_FATAL,"%s failed to move file from %s to %s ",fnc_name,file_path,tmp_line);

	file_old = fopen(tmp_line,"r");	if (file_old == NULL) return LOG_TERROR ERR_FATAL,"%s failed to open file %s",fnc_name,tmp_line);
	file_new = fopen(file_path,"w");if (file_new == NULL) return LOG_TERROR ERR_FATAL,"%s failed to open file %s",fnc_name,file_path);
	
	bdoit = false;
	*fsection = 0;
	while (fgets(SSIZE(line),file_old) != NULL)
	{
		if (!bdoit)
		{
			strcpy(tmp_line,line);
			Process_lineV1(tmp_line,&ltype,&fkey,&fval);
			switch (ltype)
			{
			case LT_SECTION:
				{
					// si se va a abandonar la seccion de la key y no se ha encontrado se almacena
					if (strcmp(fsection,section) == 0)
					{
						// antes de abandonar la seccion actual se debe dejar la key
						fprintf(file_new,"%s = %s\n",key,val);
						bdoit = true;
					}
					*fsection = 0;
					strncat(fsection,fkey,sizeof(fsection));
					break;
				}
			case LT_KEY:
				{
					if ((strcmp(fkey,key) == 0) && (strcmp(fsection,section) == 0))
					{
						sprintf(line,"%s = %s\n",key,val);
						bdoit = true;
					}
					break;
				}
			}
		}
		fputs(line,file_new);
	}
	if (!bdoit)
	{
		fprintf(file_new,"[%s]\n",section);
		fprintf(file_new,"%s = %s\n",key,val);
	}
	fclose(file_old);
	fclose(file_new);
	sprintf(tmp_line,"%s.%d",file_path,GetCurrentProcessId());
	remove(tmp_line);
	return ERR_OK;
}

DWORD CKeywords::Process_IniBuffer(char *buffer)
{
	char	line[1024];
	WORD	ltype;
	char	*fkey,*fval;
	char	fsection[100];	//seccion actual
	char	*cptr,*cptr1;
	char	*fnc_name = "CKeywords::Process_IniBuffer";
	char	*section;

	m_key_count = 0;
	if (m_page.CreatePage(3000) == NULL) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in CreatePage(%d)",fnc_name,__LINE__,3000);
	m_data_size = m_page.GetSize();

	*fsection = 0;
	cptr1 = buffer;
	section = "";

	for(;;)
	{
		if (*cptr1 == 0) break;
		cptr = cptr1 + 1;			// saltar el \n encontrado
		cptr1 = strchr(cptr1,'\n');
		if (cptr1 == NULL) cptr1 = strchr(buffer,0);
		if (cptr1 - cptr > sizeof(line)-1) 
		{
			LOG_TERROR ERR_FATAL,"%s line of %d chars too long",fnc_name,cptr1 - cptr);
			continue;
		}
		*line = 0;
		strncat(line,cptr,cptr1-cptr);
		Process_lineV1(line,&ltype,&fkey,&fval);
		switch (ltype)
		{
		case LT_SECTION:
			{
				if (m_page.addString(fkey,&section) != ERR_OK) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in addString",fnc_name,__LINE__);
				continue;
			}
		case LT_KEY:
			{
				if (m_key_count >= MAX_KEYWORDS) return LOG_TERROR ERR_FATAL,"%s keyword count overflow",fnc_name);
				m_keys[m_key_count].section = section;
				if (m_page.addString(fkey,&m_keys[m_key_count].name) != ERR_OK) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in addString",fnc_name,__LINE__);
				_strupr(m_keys[m_key_count].name);
				if (m_page.addString(fval,&m_keys[m_key_count].value) != ERR_OK) return LOG_TERROR ERR_FATAL,"%s:%u Run Time Error in addString",fnc_name,__LINE__);
				m_key_count++;
			}
		}
	}
	return ERR_OK;

}

DWORD CKeywords::Keyword1_Get(char *keyword, char *value, int maxsize, char *defval)
{
	char	*fnc_name = "CKeywords::Keyword1_Get";
	WORD	i;
	
	//m_plog->_log(LOG_FNC,"%s Start",fnc_name);
	*value = 0;
	
	for (i=0;i<m_key_count;i++)
		if (strcmp(m_keys[i].name,keyword) == 0) 
		{
			strncat(value,m_keys[i].value,maxsize);
			return ERR_OK;
		}
	strncat(value,defval,maxsize);
	return LOG_TERROR ERR_FATAL,"%s keyword '%s' not found",fnc_name,keyword);
}

DWORD CKeywords::Keyword2_Get(char *value, int maxsize, char *keyword, char *section, char *defval)
{
	int i;
	char	*fnc_name = "CKeywords::Keyword2_Get";
	//Func_Start(fnc_name);
	for (i=0;i<m_key_count;i++)
	{
		if (strcmp(section,m_keys[i].section) != 0) continue;
		if (strcmp(keyword,m_keys[i].name) != 0) continue;
		strncat(value,m_keys[i].value,maxsize);
		return ERR_OK;
	}
	strncat(value,defval,maxsize);
	return LOG_TERROR ERR_FATAL,"%s keyword '%s' not found in section '%s'",fnc_name,keyword,section);
}

DWORD CKeywords::Keyword_Look(char **val, char *keyword, char *section)
{
	int i;
	char	*fnc_name = "CKeywords::Keyword_Look";
	for (i=0;i<m_key_count;i++)
	{
		if (strcmp(section,m_keys[i].section) != 0) continue;
		if (strcmp(keyword,m_keys[i].name) != 0) continue;
		*val = m_keys[i].value;
		return ERR_OK;
	}
	*val = NULL;
	return LOG_TERROR ERR_FATAL,"%s keyword '%s' not found in section '%s'",fnc_name,keyword,section);
}

DWORD CKeywords::GetLineInfo(char *str_line, WORD line_size,WORD *wtype, char **key_name, WORD *pkey_size, char **val, WORD *pval_size)
{
	char	*fnc_name = "CKeywords::GetLineInfo";
	char	*cptr,*cptr1;
	char	*line_max;
	bool	bval_delim;

	if ((str_line == NULL) ||
		(wtype == NULL) ||
		(key_name == NULL) ||
		(pkey_size == NULL) ||
		(val == NULL) ||
		(pval_size == NULL)) return LOG_TERROR ERR_FATAL,"%s:%u RunTime error",fnc_name,__LINE__);

	*key_name = NULL;*val = NULL;
	*pkey_size = 0;*pval_size = 0;

	if (*str_line == 0) 
	{
		*wtype = LT_NONE;
		return ERR_OK;
	}
	*wtype = LT_ERROR;
	cptr = str_line;
	if (line_size == 0) line_max = cptr + strlen(cptr);
	else
		line_max = cptr + line_size;
	line_max++;	// ralmente es el line_top por eso se compara solo como < y no como <=

	for(;(cptr < line_max)&&(*cptr > 0)&&(*cptr <= 32);cptr++);	//ignorar caracteres no validos al comienzo de la linea
	if (*cptr == '[')
	{
		// inicio de seccion
		cptr++;
		*key_name = cptr;
		for (cptr1=cptr;(((*cptr1 >= ' ') || (*cptr1 < 0)) && (*cptr1 != ']') && (cptr1 < line_max));cptr1++);
		if (*cptr1 != ']')
		{
			LOG_TWARNING "Warning ... Sign ']' is missing");
		}
		*wtype = LT_SECTION;
		*pkey_size = cptr1 - cptr;
		return ERR_OK;
	}
	if (!isalpha(*cptr) ) 
	{
		*wtype = LT_COMMENT;
		return ERR_OK;
	}
	*key_name = cptr;
	for (cptr1=cptr;((*cptr1 > ' ') && (*cptr1 != '=') && (cptr1 < line_max));cptr1++);
	*pkey_size = cptr1 - cptr;
	// localizar el signo =
	for (;((*cptr1 != '=') && (cptr < line_max));cptr1++);
	if (*cptr1 != '=') return LOG_TERROR ERR_FATAL,"Sign '=' is missing");
	cptr1++;
	for (;((*cptr1 <= ' ') && (cptr1 > 0) && (cptr1 < line_max));cptr1++);	//ignorar caracteres no validos
	cptr = cptr1;
	if (*cptr1 == '\"')
	{
		cptr++;
		bval_delim = true;
	}
	else
		bval_delim = false;
	*val = cptr;
	if (cptr1 + 1 >= line_max) return LOG_TERROR ERR_FATAL,"Unexpected End of Line");
	for (;(cptr1 < line_max);cptr1++)
	{
		if ((*cptr1 == '\"') &&  (bval_delim)) break;
		if (*cptr1 < ' ') break;
	}
	//if (cptr1 == line_max)  return LOG_TERROR ERR_FATAL,"%s:%u End of Line",fnc_name,__LINE__);

	*wtype = LT_KEY;
	*pval_size = cptr1 - cptr;

	return ERR_OK;
}

DWORD CKeywords::Load_Res(char *res_ptr, S_KWD_DEF *key, int max_key)
{
	// procesar linea por linea. las lineas terminan con el caracter cero
	char	*line;
	WORD	line_size;
	char	*key_name,*val;
	WORD	ltype,key_size,val_size;
//	char	*cptr;
	char	section[100];
	int		i;
	int		n;
	S_KWD_VAL	*keyval;

	line = res_ptr;
	line_size = 0;
	for(;;)
	{
		line = line + line_size;
		line_size = strlen(line);		// se puede buscar el fin de linea CR LF
		if (*line == 0) break;
		GetLineInfo(line,line_size,&ltype,&key_name,&key_size,&val,&val_size);
		line_size++;
		if (ltype == LT_SECTION)
		{
			if (key_size > sizeof(section)) return LOG_TERROR ERR_FATAL," Overflow by %d bytes",key_size);
			*section = 0;
			strncat(section,key_name,key_size);
			continue;
		}
		if (ltype == LT_KEY)
		{
			// encontrar la llave en la configuracion
			for (i=0;i<max_key;i++)
			{
				if (strncmp(key_name,key[i].name,key_size) != 0) continue;
				if (key[i].name[key_size] != 0) continue;
				break;
			}
			if (i == max_key) 
			{
				LOG_TWARNING "Keyword not found %s",key_name);
				continue;
			}
			keyval = (S_KWD_VAL*)key[i].value;
			switch(key[i].type)
			{
			case KW_TYP_I1_P:
				{
					keyval->pc = val;
					break;
				}
			case KW_TYP_I4:
				{
					n = sscanf(val,"%d",&keyval->l);
					if (n != 1) return LOG_TERROR ERR_FATAL,"Invalid data type for %s in %s",key[i].name,val);
					break;
				}
			}
		}
	}
	return ERR_OK;
}

DWORD CKeywords::Process_IniFile_Buffer(char *file_buffer, WORD file_size, S_KWD_DEF *keyword, WORD max_keyword, CMemPage *pMemPage)
{
	if (pMemPage == NULL)
	{
		m_page.Release();
		pMemPage = &m_page;
	}

	return ERR_OK;
}

DWORD CKeywords::Process_IniFile(char *file_name, S_KWD_DEF *keyword, WORD max_keyword, CMemPage *pMemPage)
{
	/*
		formato del fichero
		[xxx]		- inicio de secion **** el ] no es obligatorio
		key=val		- key : debe comenzar con un caracter alfanumerico, puede haer espacios o TAB antes de y depues del =
					-		no puede contener espacios no caracteres <32 en el nombre
					- val : solo puede contener caracteres validos ascii >32
					- No usar " para delimitar nada, pues seran tratadas como parte del valor 
	*/
	char	line[1024];
	char	section[50];	// seccion que se esta tratando
	FILE*	file;
	DWORD	dwr;

	if (pMemPage == NULL)
	{
		m_page.Release();
		pMemPage = &m_page;
	}
	*section = 0;
	
	file = fopen(file_name,"r");
	if (file == NULL) return LOG_TERROR ERR_FATAL,"Failed to open file %s",file_name);
		
	while (fgets(SSIZE(line),file) != NULL)
	{
		dwr = StrLine_Process(line,section,sizeof(section),keyword,max_keyword,pMemPage);
		if (dwr != ERR_OK) 
		{
			LOG_TERROR ERR_FATAL,"Failed to Process line");
			continue;
		}
	}
	fclose(file);
	return ERR_OK;
}

DWORD CKeywords::StrLine_Process(char *str,char *section,WORD section_size,S_KWD_DEF *keyword, WORD max_keyword, CMemPage *pMemPage)
{
	/*
		formato de la linea
		[xxx]		- inicio de secion **** el ] no es obligatorio
		key=val		- key : debe comenzar con un caracter alfanumerico, puede haer espacios o TAB antes de y depues del =
					-		no puede contener espacios no caracteres <32 en el nombre
					- val : solo puede contener caracteres validos ascii >32
					- No usar " para delimitar nada, pues seran tratadas como parte del valor 
	*/

	char	*fnc_name = "CKeywords::Process_Str";
	char	*key_name;
	char	*val;
	int		i,n;
	WORD	key_type;
	DWORD	dwr;
	S_KWD_VAL	*keyval;

	dwr = StrLine_GetInfo(str,&key_type,&key_name,&val);
	if (dwr != ERR_OK) return LOG_TERROR dwr,"%s:%u Error",fnc_name,__LINE__);

	if (key_type == LT_SECTION)
	{
		*section = 0;
		strncat(section,key_name,section_size);
		i = strlen(key_name);
		if (i+1 > section_size) return LOG_TERROR ERR_FATAL,"%s:%u Section Name Overflow by %d bytes",fnc_name,__LINE__,i);
		return ERR_OK;
	}
	if (key_type == LT_KEY)
	{	
		// encontrar la llave en la configuracion
		for (i=0;i<max_keyword;i++)
		{
			if (_stricmp(key_name,keyword[i].name) == 0) break;
		}
		if (i == max_keyword) 
		{
			LOG_TERROR ERR_FATAL,"Keyword not found %s",key_name);
		}
		keyval = (S_KWD_VAL*)keyword[i].value;
		switch(keyword[i].type)
		{
		case KW_TYP_I1_P:
			{
				if (keyword[i].flags & KW_FLG_LOG_FILE)
				{
					m_plog->CreateFile(val);
					break;
				}
				// almacenar en la pagina de memoria la keyword.
				if (pMemPage->addString(val,&keyval->pc) != ERR_OK) return _LOG_EXIT(ERR_FATAL);
				break;
			}
		case KW_TYP_UI2:
			{
				n = sscanf(val,"%d",&keyval->ui2);
				if (n != 1) return LOG_TERROR ERR_FATAL,"Invalid data type for %s in %s",keyword[i].name,val);
				break;
			}
		case KW_TYP_I4:
		case KW_TYP_BOOL:
			{
				n = sscanf(val,"%d",&keyval->l);
				if (n != 1) return LOG_TERROR ERR_FATAL,"Invalid data type for %s in %s",keyword[i].name,val);
				break;
			}
		}
		
		if (keyword[i].flags & KW_FLG_LOG_LEVEL) m_plog->SetLevel(keyval->l);
	}
	return ERR_OK;
}

DWORD CKeywords::StrLine_GetInfo(char *str_line, WORD *wtype, char **key_name, char **val)
{
	char	*fnc_name = "CKeywords::StrLine_GetInfo";
	WORD	key_size;
	WORD	val_size;

	if (GetLineInfo(str_line,strlen(str_line),wtype,key_name,&key_size,val,&val_size) != ERR_OK) return _LOG_EXIT(ERR_FATAL);

	if (*key_name != NULL)  key_name[0][key_size] = 0;
	if (*val != NULL)		val[0][val_size] = 0;

	return ERR_OK;
}

DWORD CKeywords::ParseIniFile(const char *file_name,IConf*	conf)
{
	FNC_START

	char	line[1024];
	FILE*	file;
	DWORD	dwr;
	char	*key_name;
	char	*val;
	WORD	key_type;

	conf->Conf_Reset();
	file = fopen(file_name,"r");
	if (file == NULL) return LOG_TERROR ERR_FATAL,"Failed to open file %s",file_name);
	dwr = ERR_OK;
	while ((fgets(SSIZE(line),file) != NULL) &&
		   (dwr == ERR_OK))
	{
		dwr = StrLine_GetInfo(line,&key_type,&key_name,&val);
		if (dwr != ERR_OK) break;
		switch (key_type)
		{
		case LT_SECTION:
			if (conf->Conf_NewSection(key_name,strlen(key_name)) != ERR_OK)
			{
				dwr = _LOG_EXIT(ERR_FATAL);
			}
			break;
		case LT_KEY:
			if (conf->Conf_NewKey(key_name,strlen(key_name),val,strlen(val))  != ERR_OK)
			{
				dwr = _LOG_EXIT(ERR_FATAL);
			}
			break;
		default:
			//dwr = conf->Conf_NewLine(line);
			break;
		}
	}
	fclose(file);
	if (dwr != ERR_OK) return dwr;
	conf->Conf_Log();
	return ERR_OK;
}

DWORD CKeywords::ParseFileBuffer(const char *file,WORD len, IConf *conf)
{
	BYTE	*cptr;
	BYTE	*m1;
	BYTE	*file_top;
	WORD	stat;
	WORD	ltype;
	char	*key;
	char	*val;
	WORD	key_len;
	WORD	val_len;
	DWORD	dwr;
	FNC_START

	file_top = (BYTE*)(file + len);
	stat = 0;		// se espara un caracter valido para dar inicio a la linea

	dwr = ERR_OK;
	for(cptr = (BYTE*)file;;cptr++)
	{
		if (stat == 0) 
		{
			if (cptr == file_top) break;		// fin del fichero no hay datos que procesar
			if (*cptr > ' ') 
			{
				m1 = cptr;
				stat = 1;
			}
			continue;
		}
		if (stat == 1) 
		{
			if ((*cptr == '\r') || (*cptr == '\n') || (cptr == file_top))
			{
				stat = 0;
				// Procesar la linea obtenida
				if (ParseLine((char*)m1,cptr-m1,&ltype,&key,&key_len,&val,&val_len) != ERR_OK) break;
				switch (ltype)
				{
				case LT_SECTION:
					dwr = conf->Conf_NewSection(key,key_len);if (dwr != ERR_OK) _LOG_EXIT(ERR_FATAL);
					break;
				case LT_KEY:
					dwr = conf->Conf_NewKey(key,key_len,val,val_len);if (dwr != ERR_OK) _LOG_EXIT(ERR_FATAL);
					break;
				case LT_COMMENT: break;
				case LT_ERROR:	break;
				default:
					break;
				}
			}
			// el caracter se considera valido aunque sea <32
		}
		if (cptr == file_top) break;
	}
	if (dwr != ERR_OK) return dwr;
	conf->Conf_Log();
	return ERR_OK;
}

DWORD CKeywords::ParseLine(const char *str_line, WORD line_size, WORD *wtype, char **key_name, WORD *pkey_size, char **val, WORD *pval_size)
{
	BYTE	*line_max;
	bool	bval_delim;
	BYTE	*cptr;
	BYTE	*cptr1;
	FNC_START

	if ((str_line == NULL) ||
		(wtype == NULL) ||
		(key_name == NULL) ||
		(pkey_size == NULL) ||
		(val == NULL) ||
		(pval_size == NULL)) return LOG_TERROR ERR_FATAL,"Null Pointer");

	*key_name = NULL;*val = NULL;
	*pkey_size = 0;*pval_size = 0;

	if (*str_line == 0) 
	{
		*wtype = LT_NONE;
		return ERR_OK;
	}
	*wtype = LT_ERROR;
	cptr = (BYTE*)str_line;
	if (line_size == 0) line_max = cptr + strlen(str_line);
	else
		line_max = cptr + line_size;
	line_max++;	// ralmente es el line_top por eso se compara solo como < y no como <=

	for(;(cptr < line_max)&&(*cptr > 0)&&(*cptr <= 32);cptr++);	//ignorar caracteres no validos al comienzo de la linea
	if (*cptr == '[')
	{
		// inicio de seccion
		cptr++;
		*key_name = (char*)cptr;
		for (cptr1=cptr;(((*cptr1 >= ' ') || (*cptr1 < 0)) && (*cptr1 != ']') && (cptr1 < line_max));cptr1++);
		if (*cptr1 != ']')
		{
			LOG_TWARNING "Warning ... Sign ']' is missing");
		}
		*wtype = LT_SECTION;
		*pkey_size = cptr1 - cptr;
		return ERR_OK;
	}
	if (!isalpha(*cptr) ) 
	{
		*wtype = LT_COMMENT;
		return ERR_OK;
	}
	*key_name = (char*)cptr;
	for (cptr1=cptr;((*cptr1 > ' ') && (*cptr1 != '=') && (cptr1 < line_max));cptr1++);
	*pkey_size = cptr1 - cptr;
	// localizar el signo =
	for (;((*cptr1 != '=') && (cptr1 < line_max));cptr1++);
	if (cptr1 == line_max) return LOG_TERROR ERR_FATAL,"Sign '=' is missing");
	cptr1++;
	for (;((*cptr1 <= ' ') && (cptr1 < line_max));cptr1++);	//ignorar caracteres no validos
	//if (cptr1 == line_max) return LOG_TERROR ERR_FATAL,"Sign '=' is missing");
	cptr = cptr1;
	if (*cptr1 == '\"')
	{
		cptr++;
		bval_delim = true;
	}
	else
		bval_delim = false;
	*val = (char*)cptr;
	if (cptr1 + 1 >= line_max) return LOG_TERROR ERR_FATAL,"Unexpected End of Line");
	for (;(cptr1 < line_max);cptr1++)
	{
		if ((*cptr1 == '\"') &&  (bval_delim)) break;
		if (*cptr1 < ' ') break;
	}
	//if (cptr1 == line_max)  return LOG_TERROR ERR_FATAL,"%s:%u End of Line",fnc_name,__LINE__);

	*wtype = LT_KEY;
	*pval_size = cptr1 - cptr;

	return ERR_OK;
}
