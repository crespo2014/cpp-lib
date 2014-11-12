// DNParse.cpp: implementation of the CDNParse class.
//
//////////////////////////////////////////////////////////////////////

#include "DNParse.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDNParse::CDNParse()
{
	m_key_count = 0;
}

CDNParse::~CDNParse()
{
}

char* CDNParse::GetKey(char *key, char *defval)
{
	WORD	i;
	char	*fnc_name = "CDNParse::GetKey";
	for (i=0;i<m_key_count;i++)
	{
		if (strcmp(key,m_key[i].key) == 0) return m_key[i].val;
	}
	SetError(true,ERR_FATAL,"%s key '%s' not found",fnc_name,key);
	return defval;
}

void CDNParse::LogData()
{
	WORD	i;
	//char	*fnc_name = "CDNParse::LogData";
	m_plog->_log(LOG_DATA,"CDNParse showing data");
	for (i=0;i<m_key_count;i++)
	{
		m_plog->_log(LOG_DATA,"%s = %s",m_key[i].key,m_key[i].val);
	}
}

DWORD CDNParse::Parse_String(char *str)
{
	char	*fnc_name = "CDNParse::Parse_String";
	char	*cptr;
	char	*cptr1;
	char	cbreak = ',';
	char	cend;

	/*
		Formato del DN debe cumplir la  siguiente norma
		<key>=<valor><separador><espacio>
		el valor puede ir entrecomillado
		no puede haber espacios entre el separdor y el valor porque seran considerados parte del valor
		puede haber o no un espacio entre el separador y el proximo atributo
		no hay espacios entre el signo igual y el atributo ni entre este y el valor, pero puede haberlos

	*/
	if (*str == 0) return SetError(true,ERR_FATAL,"%s Empty string not allowed ",fnc_name);
	m_data_size = strlen(str);
	m_data = (char*)m_page.CreatePage(&m_data_size);
	if (m_data == NULL) return SetError_Add_W32_code_msg(true,ERR_FATAL,GetLastError(),"%s Memory alloc failed",fnc_name);

	cptr = str;
	m_key_count = 0;
	m_data_ptr = m_data;

	while (*cptr != 0)
	{
		//for(;(*cptr != 0)&&(*cptr <= 32);cptr++);	//ignorar caracteres no validos al comienzo de la linea
		cptr1 = cptr;
		cptr = strchr(cptr,'=');
		if (cptr == NULL)
		{
			return SetError(true,ERR_FATAL,"%s->Sign '=' is missing in ket No. %d",fnc_name,m_key_count);
		}
		if (Data_AddStr(cptr1,&m_key[m_key_count].key,fnc_name,cptr-cptr1) != ERR_OK) return ERR_FATAL;
		// leer el valor
		cptr++;
		if (*cptr == '\"') 
		{
			cptr++;
			cend = '\"';
		}
		else
		{
			cend = cbreak;
		}
		cptr1 = cptr;
		cptr = strchr(cptr,cend);
		if (cptr == NULL) 
		{
			if (cend != cbreak) return SetError(true,ERR_FATAL,"%s terminator char '%c' not found",fnc_name,cend);
			cptr = strchr(cptr1,0);
		}
		if (Data_AddStr(cptr1,&m_key[m_key_count].val,fnc_name,cptr-cptr1) != ERR_OK) return ERR_FATAL;
		m_key_count++;
		// saltar el caracter de separacion, las comillas y el espacio
		for (;*cptr!=0;cptr++)
		{
			if (*cptr == 32) continue;
			if (*cptr == cend) continue;
			if (*cptr == cbreak) continue;
			break;
		}
	}
	return ERR_OK;
}

DWORD CDNParse::Key_Get(char *key, char *val, WORD maxsize)
{
	WORD	i;
	char	*fnc_name = "CDNParse::Key_Get";
	for (i=0;i<m_key_count;i++)
	{
		if (strcmp(key,m_key[i].key) == 0)
		{
			*val = 0;
			strncat(val,m_key[i].val,maxsize);
			return ERR_OK;
		}
	}
	return SetError(true,ERR_FATAL,"%s key '%s' not found",fnc_name,key);
}

DWORD CDNParse::Key_Look(char *key, char **val)
{
	WORD	i;
	char	*fnc_name = "CDNParse::Key_Look";
	for (i=0;i<m_key_count;i++)
	{
		if (strcmp(key,m_key[i].key) == 0)
		{
			*val = m_key[i].val;
			return ERR_OK;
		}
	}
	return SetError(true,ERR_FATAL,"%s key '%s' not found",fnc_name,key);
}

DWORD CDNParse::Data_GetBuffer(char **buff, WORD len,char* fnc_name)
{
	DWORD remained = sizeof(m_data) - (m_data_ptr - m_data);

	if (remained < len) return SetError(true,ERR_FATAL,"%s failed to get %d bytes from buffer, %d bytes remined",fnc_name,len,remained);
	*buff = m_data_ptr;
	m_data_ptr += len;
	return ERR_OK;
}

/*
	adiciona un string o un buffer de bytes o devuelve un buffer de datos
	si len = 0 se utiliza la longitud de la cadena indicada en str
	si str = NULL, solo se devuelve el buffer y no se copia el contenido

*/
DWORD CDNParse::Data_AddStr(char *str, char **pos, char *fnc_name, DWORD len)
{
	if ((str == NULL) && (len == 0))
	{
		*pos = NULL;
		return SetError(true,ERR_FATAL,"%s Invalid params in Data_AddStr",fnc_name);
	}

	DWORD remained = m_data_size - (m_data_ptr - m_data);
	if (len == 0) len = strlen(str);
	if (remained < len+1) return SetError(true,ERR_FATAL,"%s failed to get %d bytes from buffer, %d bytes remined",fnc_name,len,remained);
	*pos = m_data_ptr;
	if (str != NULL) memcpy(m_data_ptr,str,len);
	m_data_ptr += (len+1);
	m_data_ptr[-1] = 0;
	return ERR_OK;
}

DWORD CDNParse::Key_ByIndex(WORD index, _DNKEY **pdnkey)
{
	char	*fnc_name = "CDNParse::Key_ByIndex";
	if (index >= m_key_count) return SetError(true,ERR_FATAL,"%s index out of bound",fnc_name);
	*pdnkey = &m_key[index];
	return ERR_OK;
}

