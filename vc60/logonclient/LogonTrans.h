// LogonTrans.h: interface for the CLogonTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGONTRANS_H__B223CE97_66F1_4D1C_A66D_4F55A8A36DD4__INCLUDED_)
#define AFX_LOGONTRANS_H__B223CE97_66F1_4D1C_A66D_4F55A8A36DD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_KEYWORDS	20

typedef struct
{
	char*	name;
	char*	value;
}KEYWORD;

typedef struct
{
	WORD	size;		// tamaño de la estructura
	BYTE	cmd;		// comando a ejecutar
	WORD	keycount;	// cantidad de keyword
	char*	fullname;
	char*	shortname;
	char*	oldpass;
	char*	newpass;
	char*	idfilepath;
	KEYWORD	keywords[MAX_KEYWORDS];
} LOGONTRANS;

typedef struct
{
	DWORD	size;			// tamaño en fichero del buffer + status
	WORD	status;
	char	m_keys[2024];		// buffer lineal de keys
} FILEPACK;

// Maneja las transaciones en logon
class CLogonTrans  
{
public:
	DWORD ProcessCmd(char* scmd);
	DWORD AddTransationToFile(FILEPACK* filepack);
	DWORD SetTransactionFile(char* sFilepath);
	DWORD AddToBuffer(char** sptr,char* key,char* value);
	DWORD MakeBuffer(char* cmdstr,char* keys,DWORD* psize);
	DWORD ExtracKeywords(char* keys,KEYWORD* keyword,WORD* maxkeys);
	DWORD OpenFile(char* sFilePath);
	CLogonTrans();
	virtual ~CLogonTrans();
private:
	PLARGE_INTEGER	m_filepos;			// posicion dentro del fichero del paquete actual 

	HANDLE		m_hFile;				// Fichero de transaciones
	char		m_filepath[MAX_PATH];	
	FILEPACK	m_filepack;
	LOGONTRANS	m_trans;				// datos del paquete de fichero descompuesto


};

#endif // !defined(AFX_LOGONTRANS_H__B223CE97_66F1_4D1C_A66D_4F55A8A36DD4__INCLUDED_)
