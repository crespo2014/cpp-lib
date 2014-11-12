// Keywords.cpp: implementation of the CKeywords class.
//
//////////////////////////////////////////////////////////////////////

#include "Keywords.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




CKeywords::CKeywords()
{
	m_key_count = 0;
	m_bUpperCase = false;
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

	m_key_count = 0;
	m_data_size = strlen(cmd_line) + 1;
	if (m_page.CreatePage(&m_data_size) == NULL) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());

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
		if (m_key_count >= MAX_KEYWORDS) return SetError(true,ERR_FATAL,"%s keyword count overflow",fnc_name);
		m_keys[m_key_count].name = cptr; if (m_bUpperCase) _strupr(cptr);
		while (cptr[0] != 0) cptr++;	//buscar el valor
		cptr++;
		m_keys[m_key_count].value = cptr;
		while (cptr[0] != 0) cptr++;	//ir al final del valor
		cptr++;
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

	return SetError(trace,ERR_FATAL,"%s keyword '%s' not found ",fnc_name,keyword);
}

DWORD CKeywords::GetEnv(char *keyword, char **cptr, bool trace)
{
	char	*fnc_name = "CKeywords::GetEnv";

	*cptr = getenv(keyword);
	if (*cptr != NULL) return ERR_OK;
	return SetError(trace,ERR_FATAL,"%s variable '%s' not found ",fnc_name,keyword);
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
	if (m_page.CreatePage(&m_data_size) == NULL) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());
	
	for (pos = 1;pos < count;pos++)
	{
		if (m_key_count >= MAX_KEYWORDS) return SetError(true,ERR_FATAL,"%s keyword count overflow",fnc_name);
		cptr = arg[pos];
		if (*cptr != '-') break;	//el campo debe empezar con -
		cptr++;
		if (m_page.AddStr(cptr,&m_keys[m_key_count].name) != ERR_OK) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());
		if (m_bUpperCase) _strupr(m_keys[m_key_count].name);
		pos++;
		if (pos >= count) break;
		if (m_page.AddStr(arg[pos],&m_keys[m_key_count].value) != ERR_OK) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());
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
	if (file == NULL) return SetError(true,ERR_FATAL,"%s failed to open file %s",fnc_name,file_path);
	m_data_size = 3000;
	if (m_page.CreatePage(&m_data_size) == NULL) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());
		
	while (fgets(SSIZE(line),file) != NULL)
	{
		cptr = line;
		for(;(*cptr != 0)&& (*cptr <= 32);cptr++);	//ignorar caracteres no validos al comienzo de la linea
		if (cptr[0] == '[')
		{
			// inicio de seccion
			cptr++;
			sptr1 = strchr(cptr,']');
			if (sptr1 != NULL)
			{
				*sptr1 = 0;
				m_page.AddStr(cptr,&section);
				continue;
			}
			for (sptr1=cptr;*sptr1 >= ' ';sptr1++);*sptr1 = 0;
			m_page.AddStr(cptr,&section);
			continue;
		}
		if (!isalpha(line[0]) ) continue;	// si no tiene caracteres alfanumericos es un comentario
		// llegado a este punto debemos tener una linea tipo key=val
		if (m_key_count >= MAX_KEYWORDS) return SetError(true,ERR_FATAL,"%s keyword count overflow",fnc_name);
		key = cptr;
		cptr = strchr(cptr,'=');if (cptr == NULL) continue;	// si no hay = esta mal
		*cptr = 0;cptr++;

		for (cptr1=key;(*cptr1 > ' ');cptr1++);	// ignorar espacios y caracteres no validos en key
		if (m_page.AddStr(key,&m_keys[m_key_count].name,cptr1-key) != ERR_OK) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());
		_strupr(m_keys[m_key_count].name);
				
		for(;((*cptr <= ' ') &&(*cptr != 0));cptr++);		//ignorar espacios y caracteres no validos antes del valor
		if (*cptr == '\"') cptr++;
		cptr1 = cptr;
		for (;(*cptr1 >= ' ');cptr1++);	// solo caracteres >=32 para el valor
		if (m_page.AddStr(cptr,&m_keys[m_key_count].value,cptr1-cptr) != ERR_OK) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());
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
		if (strcmp(section,m_keys[i].section) != 0) continue;
		if (strcmp(keyword,m_keys[i].name) != 0) continue;
		*val = m_keys[i].value;
		return ERR_OK;
	}
	return SetError(false,ERR_FATAL,"CKeywords::IniParam_Look failed to get keyword %s from ini file");
}

char* CKeywords::GetKey(WORD index)
{
	if (index >= m_key_count) return NULL;
	return m_keys[index].value;
}

DWORD CKeywords::Process_Line(char *line, char delimiter)
{
	char	*fnc_name = "CKeywords::Process_Line";

	m_key_count = 0;
	m_data_size = strlen(line) + 1;
	if (m_page.CreatePage(&m_data_size) == NULL) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());
	
	char	*cptr;
	cptr = (char*)m_page.GetPage();
	strcpy(cptr,line);

	for (;;)
	{
		if (m_key_count >= MAX_KEYWORDS) return SetError(true,ERR_FATAL,"%s keyword count overflow",fnc_name);
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

	m_key_count = 0;
	m_data_size = strlen(cmd_line) + 1;
	if (m_page.CreatePage(&m_data_size) == NULL) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());

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

DWORD CKeywords::Process_IniFile2(char *file_path, KEYWORD_DF *keys,char* defval)
{
	// carga solo las keywords indicadas y solo almacena el valor en la estructura de datos
	// se indica el valor por defecto que tomaran las keywords no encontradas
	return ERR_OK;
}

//DEL DWORD CKeywords::Process_ini_line(char *line, WORD *ltype, char *key, WORD keymaxsize, char *val, WORD valmaxsize)
//DEL {
//DEL 	char*	cptr;		// posicion que se esta tratando
//DEL 	char	*cptr1;
//DEL 	char	*sptr1;
//DEL 	char	*k,*v;
//DEL 	char	*fnc_name = "CKeywords::Process_ini_line";
//DEL 
//DEL 	*key = 0;
//DEL 	*val = 0;
//DEL 	cptr = line;
//DEL 	for(;(*cptr != 0)&& (*cptr <= 32);cptr++);	//ignorar caracteres no validos al comienzo de la linea
//DEL 	if (cptr[0] == '[')
//DEL 	{
//DEL 		// inicio de seccion
//DEL 		cptr++;
//DEL 		sptr1 = strchr(cptr,']');
//DEL 		if (sptr1 == NULL) sptr1 = cptr + strlen(cptr);
//DEL 		if (sptr1 - cptr >= keymaxsize))
//DEL 		{
//DEL 			ltype = LT_ERROR;
//DEL 			return SetError(true,ERR_FATAL,"%s->key buffer of %d is overflow with section (%s)",keymaxsize,cptr);
//DEL 		}
//DEL 		*key = 0;
//DEL 		strncat(key,cptr,keymaxsize-1);
//DEL 		cptr = strchr(key,']'); if (cptr != NULL)	*cptr = 0;
//DEL 		for (sptr1=key;*sptr1 >= ' ';sptr1++);*sptr1 = 0;
//DEL 		ltype = LT_SECTION;
//DEL 		return ERR_OK;
//DEL 	}
//DEL 	if (!isalpha(line[0]) ) 
//DEL 	{
//DEL 		ltype = LT_COMMENT;
//DEL 		return ERR_OK;
//DEL 	}
//DEL 	// key=val
//DEL 	k = cptr;
//DEL 	cptr = strchr(cptr,'=');
//DEL 	if (cptr == NULL)
//DEL 	{
//DEL 		ltype = LT_ERROR;
//DEL 		return SetError(true,ERR_FATAL,"%s->Sign = is missing for line %s",line);
//DEL 	}
//DEL 	if (cptr - k >= keymaxsize)
//DEL 	{
//DEL 		ltype = LT_ERROR;
//DEL 		return SetError(true,ERR_FATAL,"%s->key buffer of %d is overflow with key (%s)",keymaxsize,k);
//DEL 	}
//DEL 	strncat(key,k,cptr - k);
//DEL 	cptr1 = strchr(cptr,'='); if (cptr1 != NULL) *cptr1 = 0;
//DEL 	for (cptr1=key;*cptr1 != 0;cptr1++)
//DEL 		if (*cptr1<=32) *cptr1=0;			// ignorar espacios y caracteres no validos en key
//DEL 	_strupr(key);
//DEL 
//DEL 	cptr++;
//DEL 	for(;((*cptr <= ' ') &&(*cptr != 0));cptr++);						//ignorar espacios y caracteres no validos antes del valor
//DEL 	if (*cptr == '\"') cptr++;
//DEL 	v = cptr;
//DEL 	for (;*cptr >= ' ';cptr++);*cptr = 0;	// solo caracteres >=32 para el valor
//DEL 	cptr = dt_ptr;
//DEL 	dt_ptr += sprintf(dt_ptr,"%s%c",key,0);
//DEL 	key = cptr;
//DEL 	cptr = dt_ptr;
//DEL 	dt_ptr += sprintf(dt_ptr,"%s%c",val,0);
//DEL 	val = cptr;
//DEL 
//DEL 
//DEL 	return ERR_OK;
//DEL }

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
	for(;(*cptr != 0)&& (*cptr <= 32);cptr++);	//ignorar caracteres no validos al comienzo de la linea
	if (cptr[0] == '[')
	{
		// inicio de seccion
		cptr++;
		*key = cptr;
		sptr1 = strchr(cptr,']');
		if (sptr1 == NULL)
		{
			SetError(true,ERR_FATAL,"%s->Warning ... Sign ']' is missing for line %s",fnc_name,line);
		}
		else
			*sptr1 = 0;
		for (sptr1=cptr;*sptr1 >= ' ';sptr1++);*sptr1 = 0;
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
		return SetError(true,ERR_FATAL,"%s->Sign '=' is missing for line %s",fnc_name,line);
	}
	*cptr = 0;cptr++;
	for (sptr1=*key;*sptr1 != 0;sptr1++)
		if (*sptr1<=32) *sptr1=0;			// ignorar espacios y caracteres no validos en key
	_strupr(*key);
	for(;((*cptr <= ' ') &&(*cptr != 0));cptr++);						//ignorar espacios y caracteres no validos antes del valor
	if (*cptr == '\"')
	{
		cptr++;
		bval_delim = true;
	}
	else
		bval_delim = false;
	*val = cptr;
	for (;*cptr >= ' ';cptr++);*cptr = 0;	// solo caracteres >=32 para el valor
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
		return SetError(false,ERR_FATAL,"%s failed to move file from %s to %s ",fnc_name,file_path,tmp_line);

	file_old = fopen(tmp_line,"r");	if (file_old == NULL) return SetError(false,ERR_FATAL,"%s failed to open file %s",fnc_name,tmp_line);
	file_new = fopen(file_path,"w");if (file_new == NULL) return SetError(false,ERR_FATAL,"%s failed to open file %s",fnc_name,file_path);
	
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
	m_data_size = 3000;
	if (m_page.CreatePage(&m_data_size) == NULL) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());

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
			SetError(true,ERR_FATAL,"%s line of %d chars too long",fnc_name,cptr1 - cptr);
			continue;
		}
		*line = 0;
		strncat(line,cptr,cptr1-cptr);
		Process_lineV1(line,&ltype,&fkey,&fval);
		switch (ltype)
		{
		case LT_SECTION:
			{
				if (m_page.AddStr(fkey,&section) != ERR_OK) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());
				continue;
			}
		case LT_KEY:
			{
				if (m_key_count >= MAX_KEYWORDS) return SetError(true,ERR_FATAL,"%s keyword count overflow",fnc_name);
				m_keys[m_key_count].section = section;
				if (m_page.AddStr(fkey,&m_keys[m_key_count].name) != ERR_OK) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());
				_strupr(m_keys[m_key_count].name);
				if (m_page.AddStr(fval,&m_keys[m_key_count].value) != ERR_OK) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,m_page.GetErrorMsg());
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
	return SetError(true,ERR_FATAL,"%s keyword '%s' not found",fnc_name,keyword);
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
	return SetError(false,ERR_FATAL,"%s keyword '%s' not found in section '%s'",fnc_name,keyword,section);
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
	return SetError(false,ERR_FATAL,"%s keyword '%s' not found in section '%s'",fnc_name,keyword,section);
}

//DEL DWORD CKeywords::Data_AddStr(char *str, char **pos, char *fnc_name,DWORD len)
//DEL {
//DEL 	DWORD remained = m_data_size - (m_data_ptr - m_data);
//DEL 	if (len == 0) len = strlen(str);
//DEL 
//DEL 	if (remained < len+1) return SetError(true,ERR_FATAL,"%s failed to get %d bytes from buffer, %d bytes remined",fnc_name,len,remained);
//DEL 	*pos = m_data_ptr;
//DEL 	memcpy(m_data_ptr,str,len+1);
//DEL 	m_data_ptr += (len+1);
//DEL 	return ERR_OK;
//DEL }
