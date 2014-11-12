// dbObject.h: interface for the CdbObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBOBJECT_H__C1D46CA5_ADE7_4C65_BB9D_D2B9F6EBF9AC__INCLUDED_)
#define AFX_DBOBJECT_H__C1D46CA5_ADE7_4C65_BB9D_D2B9F6EBF9AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "sqlcommand.h"

typedef struct
{
	char	*field_name;	// nombre del campo en la BD
	void	*data_ptr;		// puntero al dato dentro de la clase
	SQLSMALLINT	c_type;		// tipo de dato en c
	SQLSMALLINT sql_type;	// tipo de dato en sql
	SQLINTEGER	data_size;	// tamaño actual del dato obtenido por odbc
	SQLINTEGER	max_size;	// tamaño maximo del dato incluye el 0 en los char*
	BOOL		bmodified;		// indica que el campo ha sido modificado
	DWORD		flags;			// opciones del dato, como no hacer binding, etc
}DB_DATA_DEF;	

class CdbObject : public CbObject  
{
public:
	void to_Date(struct tm *time, DATE_STRUCT *dt);
	void to_DateTime(struct tm *time,TIMESTAMP_STRUCT* dt);
	DWORD DateTime_getCurrent(TIMESTAMP_STRUCT* dt);

	DB_DATA_DEF* Data_Look(char *dt_name);
	DWORD Data_SetSize(char* name,DWORD size);
	void Modified_Clear() { for (WORD j=0;j<m_data_def_count;j++) m_data_def[j].bmodified = false; };
	void SetModified(void* data_ptr,BOOL bmod = true);
	void ClearData();
	void BindDataCheck();
	DWORD LogData();
	DWORD SetData(CSqlCommand *psqlcmd);
	void SetDataDef(DB_DATA_DEF *data_def,WORD max_data_def);
	DWORD AddDataDef(char *field_name, SQLSMALLINT c_type,SQLSMALLINT sql_type, void *data_ptr, SQLINTEGER max_size);
	DWORD BindData(CSqlCommand *psqlcmd);
	CdbObject();
	virtual ~CdbObject();

private:
	WORD	m_data_def_max;

protected:
	DB_DATA_DEF	*m_data_def;
	WORD	m_data_def_count;
	// indica el tipo de elemento y el identificador usado
	char	*m_type;
	char	*m_id;
	
	//indicar la tabla del elemento. el campo id se obtiene comparando el puntero m_id
	char	*m_db_table;
};

#endif // !defined(AFX_DBOBJECT_H__C1D46CA5_ADE7_4C65_BB9D_D2B9F6EBF9AC__INCLUDED_)
