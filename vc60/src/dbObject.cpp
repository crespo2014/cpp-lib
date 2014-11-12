// dbObject.cpp: implementation of the CdbObject class.
//
//////////////////////////////////////////////////////////////////////

#include "dbObject.h"
#include "time.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CdbObject::CdbObject()
{
	m_data_def_count = 0;
	m_data_def = NULL;
	m_data_def_max = 0;
	m_type	= "Unknown";
	m_id	= "";
}

CdbObject::~CdbObject()
{

}

/*


DWORD CctsEntity::LogData()
{
	WORD	j;
 	DWORD	dwr;
	char*	name;
	char*	val;
	char	tmp_str[50];
 	
	C_VARIANT	*variant;

	m_plog->_log(LOG_DATA,"Login data for %s <%s>",m_type,m_id);

	for (j=0;j<m_data_def_count;j++)
	{
		if (m_data_def[j].data_ptr == m_id) continue;	// no se muestra el identificador de la entidad
	
		name = NULL;
		name = m_data_def[j].field_name;
		if (name == NULL) name = m_data_def[j].keyword_name;
		if (name == NULL)
		{
			m_plog->log_uint(LOG_ERROR,"CctsEntity::B_LogData -> Invalid name for data in index ",j);
			continue;
		}
		variant = (C_VARIANT*)m_data_def[j].data_ptr;
		val = tmp_str;
		switch (m_data_def[j].db_c_type)
		{
		case SQL_C_TYPE_TIMESTAMP:
			DT_sp_datetime(&variant->tss,SSIZE(tmp_str));
			break;

		case SQL_C_TYPE_DATE:
			DT_sp_date(&variant->dts,SSIZE(tmp_str));
			break;

		case SQL_C_CHAR:
			val = variant->ca;
			break;
		case SQL_C_SSHORT:	_snprintf(SSIZE(tmp_str),"%d",variant->si);break;
		case SQL_C_USHORT:	_snprintf(SSIZE(tmp_str),"%u",variant->usi);break;
		case SQL_C_SLONG:	_snprintf(SSIZE(tmp_str),"%d",variant->li);break;
		case SQL_C_ULONG:	_snprintf(SSIZE(tmp_str),"%u",variant->uli);break;
		case SQL_C_FLOAT:	_snprintf(SSIZE(tmp_str),"%f",variant->f);break;
		case SQL_C_DOUBLE:	_snprintf(SSIZE(tmp_str),"%g",variant->usi);break;
		case SQL_C_STINYINT:_snprintf(SSIZE(tmp_str),"%d",variant->sc);break;
		case SQL_C_UTINYINT:
		case SQL_C_BIT:		_snprintf(SSIZE(tmp_str),"%u",variant->uc);break;
		case SQL_C_SBIGINT: _snprintf(SSIZE(tmp_str),"%d",variant->i64);break;
		case SQL_C_UBIGINT: _snprintf(SSIZE(tmp_str),"%u",variant->ui64);break;
		default:
			{
				dwr = I_LogData(j);
				if (dwr == ERR_OK) continue; 
				m_plog->log_sint(LOG_WARNING,"CctsEntity::B_LogData Unknown C Type = ",m_data_def[j].db_c_type," for dbfield = ",name);
				continue;
			}
		}
		m_plog->_log(LOG_DATA,"<%s> = <%s>",name,val);
	}
	return ERR_OK;
public:
	DWORD to_Date(struct tm *time,DATE_STRUCT* dt);
}



*/

DWORD CdbObject::BindData(CSqlCommand *psqlcmd)
{
	char	*fnc_name = "CdbObject::BindData";
	char	colname[100];
	WORD	i,j;
	DWORD	dwr;

	SQLSMALLINT namesize;	//tamaño maximo del nombre de la columna
	SQLSMALLINT coltype;
	SQLUINTEGER	coldatasize;

	for (i=1;;i++)
	{
		namesize = sizeof(colname);
		dwr = psqlcmd->GetColumnNameType(i,colname,&namesize,&coltype,&coldatasize);
		if (dwr == ERR_EOF) break;
		if (dwr == ERR_FATAL) return ERR_FATAL;
		strupr(colname);

		for (j=0;j<m_data_def_count;j++)
		{
			if (m_data_def[j].field_name == NULL) continue;
			if (strcmp(colname,m_data_def[j].field_name) == 0)
			{
				dwr = psqlcmd->BindColumn(i,m_data_def[j].c_type,m_data_def[j].data_ptr,m_data_def[j].max_size,&m_data_def[j].data_size);
				break;
			}
		}
		if (j != m_data_def_count) continue;
		m_plog->_log(LOG_WARNING,"%s not binding for column name = '%s' , type = %d",fnc_name,colname,coltype);
	}
	return ERR_OK;
}

DWORD CdbObject::AddDataDef(char *field_name, SQLSMALLINT c_type,SQLSMALLINT sql_type, void *data_ptr, SQLINTEGER max_size)
{
	char	*fnc_name = "CdbObject::AddDataDef";
	if ((m_data_def == NULL)||(m_data_def_max == m_data_def_count)) return SetError(true,ERR_FATAL,"%s ... failed",fnc_name);

	m_data_def[m_data_def_count].bmodified = false;
	m_data_def[m_data_def_count].field_name = field_name;
	m_data_def[m_data_def_count].sql_type = sql_type;
	m_data_def[m_data_def_count].c_type = c_type;
	m_data_def[m_data_def_count].data_ptr = data_ptr;
	m_data_def[m_data_def_count].max_size = max_size;
	m_data_def[m_data_def_count].data_size = 0;
	m_data_def_count ++;	
	return ERR_OK;
}

void CdbObject::SetDataDef(DB_DATA_DEF *data_def, WORD max_data_def)
{
	m_data_def = data_def;
	m_data_def_count = 0;
	m_data_def_max = max_data_def;	
}

DWORD CdbObject::SetData(CSqlCommand *psqlcmd)
{
	char	*fnc_name = "CdbObject::SetData";
	char	colname[100];
	WORD	i,j;
	DWORD	dwr;

	SQLSMALLINT namesize;	//tamaño maximo del nombre de la columnsa
	SQLSMALLINT coltype;
	SQLUINTEGER	coldatasize;

	for (i=1;;i++)
	{
		namesize = sizeof(colname);
		dwr = psqlcmd->GetColumnNameType(i,colname,&namesize,&coltype,&coldatasize);
		if (dwr == ERR_EOF) break;
		if (dwr == ERR_FATAL) return ERR_FATAL;
		strupr(colname);

		for (j=0;j<m_data_def_count;j++)
		{
			if (m_data_def[j].field_name == NULL) continue;
			if (m_data_def[j].field_name[0] == 0) continue;
			if (strcmp(colname,m_data_def[j].field_name) == 0)
			{
				dwr = psqlcmd->GetData(i,m_data_def[j].c_type,m_data_def[j].data_ptr,m_data_def[j].max_size,&m_data_def[j].data_size);
				if (dwr != ERR_OK) m_plog->_log(LOG_WARNING,"%s for column %s -> %s",fnc_name,colname,psqlcmd->GetErrorMsg());
				break;
			}
		}
		if (j != m_data_def_count) continue;
		m_plog->_log(LOG_ERROR,"%s Invalid column type = %d , name = %s ",fnc_name,coltype,colname);
	}
	return ERR_OK;
}

DWORD CdbObject::LogData()
{
	return ERR_OK;
}

void CdbObject::BindDataCheck()
{
	WORD	j;
	for (j=0;j<m_data_def_count;j++)
	{
		if (m_data_def[j].field_name == NULL) continue;
		if (m_data_def[j].field_name[0] == 0) continue;
		if (m_data_def[j].data_size == SQL_NULL_DATA) 
		{
			m_plog->_log(LOG_TRACE,"DB field %s is NULL",m_data_def[j].field_name);
			continue;
		}
		if (m_data_def[j].data_size == SQL_NO_TOTAL) 
		{
			m_plog->_log(LOG_TRACE,"DB field %s has been TRUNC",m_data_def[j].field_name);
			continue;
		}
		m_plog->_log(LOG_TRACE,"%u "" bytes for DB field %s ",m_data_def[j].data_size,m_data_def[j].field_name);
	}
}

void CdbObject::ClearData()
{
	WORD	j;
 	for (j=0;j<m_data_def_count;j++) 
 	{
 		memset(m_data_def[j].data_ptr,0,m_data_def[j].max_size);
		m_data_def[j].bmodified = true;
 	}
}

void CdbObject::SetModified(void *data_ptr, BOOL bmod)
{
	WORD	j;
	//if (data_ptr == NULL) return;
	if (data_ptr == NULL)
	{
		for (j=0;j<m_data_def_count;j++) m_data_def[j].bmodified = bmod;
 		return;
	}
 	for (j=0;j<m_data_def_count;j++) 
 	{
		if (m_data_def[j].data_ptr == data_ptr)
		{
			m_data_def[j].bmodified = bmod;
			break;
		}
 	}
}


DWORD CdbObject::Data_SetSize(char *name, DWORD size)
{
	DB_DATA_DEF*	dt_def;
	dt_def = Data_Look(name);if (dt_def == NULL) return ERR_FATAL;
	dt_def->data_size = size;	
	return ERR_OK;
}

DB_DATA_DEF* CdbObject::Data_Look(char *dt_name)
{
	WORD j;
	for (j=0;j<m_data_def_count;j++) 
 	{
		if (strcmp(dt_name,m_data_def[j].field_name) == 0) return &m_data_def[j];
 	}
	SetError(true,ERR_FATAL,"CdbObject field not found '%s'",dt_name);
	return NULL;
}

DWORD CdbObject::DateTime_getCurrent(TIMESTAMP_STRUCT *dt)
{
	char	*fnc_name = "CdbObject::DateTime_getCurrent";
	struct tm *time;
    time_t long_time;
	::time(&long_time);
	time = localtime(&long_time);
	if (time == NULL)	return SetError(true,ERR_FATAL,"%s Failed to get convert time with localtime ",fnc_name);
	dt->day = time->tm_mday;
	dt->fraction = 0;
	dt->hour = time->tm_hour;
	dt->minute = time->tm_min;
	dt->month = time->tm_mon+1;
	dt->second = time->tm_sec;
	dt->year = 1900+time->tm_year;
	return ERR_OK;
}

void CdbObject::to_DateTime(tm *time, TIMESTAMP_STRUCT *dt)
{
	dt->day = time->tm_mday;
	dt->fraction = 0;
	dt->hour = time->tm_hour;
	dt->minute = time->tm_min;
	dt->month = time->tm_mon+1;
	dt->second = time->tm_sec;
	dt->year = 1900+time->tm_year;
}

void CdbObject::to_Date(tm *time, DATE_STRUCT *dt)
{
	dt->day = time->tm_mday;
	dt->month = time->tm_mon+1;
	dt->year = 1900+time->tm_year;
}

DWORD CdbObject::getString_name(const char *field_name, char *val, DWORD maxsize)
{
	DB_DATA_DEF	*data_def;
	S_VARIANT	*variant;

	if (val == NULL) return ERR_PARAM;
	data_def = getDataDef_name(field_name);   if (data_def == NULL) return ERR_NOT_FOUND;

	variant = (S_VARIANT*)data_def->data_ptr;

	switch (data_def->c_type)
	{
		/*
	case SQL_C_TYPE_TIMESTAMP:
		DT_sp_datetime(&variant->tss,val,maxsize);
		break;

	case SQL_C_TYPE_DATE:
		DT_sp_date(&variant->dts,SSIZE(tmp_str));
		break;
		*/

	case SQL_C_CHAR:
		{
			*val = 0;
			strncat(val,variant->ca,maxsize-1);
			break;
		}
	case SQL_C_SSHORT:	_snprintf(val,maxsize,"%d",variant->si);break;
	case SQL_C_USHORT:	_snprintf(val,maxsize,"%u",variant->usi);break;
	case SQL_C_SLONG:	_snprintf(val,maxsize,"%d",variant->li);break;
	case SQL_C_ULONG:	_snprintf(val,maxsize,"%u",variant->uli);break;
	case SQL_C_FLOAT:	_snprintf(val,maxsize,"%f",variant->f);break;
	case SQL_C_DOUBLE:	_snprintf(val,maxsize,"%g",variant->usi);break;
	case SQL_C_STINYINT:_snprintf(val,maxsize,"%d",variant->sc);break;
	case SQL_C_UTINYINT:
	case SQL_C_BIT:		_snprintf(val,maxsize,"%u",variant->uc);break;
	case SQL_C_SBIGINT: _snprintf(val,maxsize,"%d",variant->i64);break;
	case SQL_C_UBIGINT: _snprintf(val,maxsize,"%u",variant->ui64);break;
	default: 
		{
			return SetError(true,ERR_FATAL,"Invalid c data type %d for column %s",data_def->c_type,data_def->field_name);
		}
	}
	return ERR_OK;

}

DB_DATA_DEF* CdbObject::getDataDef_name(const char *field_name)
{
	if ((field_name == NULL) ||
		(*field_name == 0)) return NULL;

	WORD	j;
 	for (j=0;j<m_data_def_count;j++) 
 	{
		if (_stricmp(field_name,m_data_def[j].field_name) == 0)	return &m_data_def[j];
 	}
	return NULL;
}

DWORD CdbObject::BindParameter(SQLUSMALLINT index, SQLSMALLINT inout_type, DB_DATA_DEF *data_def)
{
	return ERR_FATAL;
}
