// Cifrado.h: interface for the CCifrado class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIFRADO_H__CCECEC36_D831_49BA_ACAF_7A8C35EF76D0__INCLUDED_)
#define AFX_CIFRADO_H__CCECEC36_D831_49BA_ACAF_7A8C35EF76D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logclient.h"

typedef struct 
{
	unsigned char etable[256];
	unsigned char dtable[256];
} base64;

typedef struct 
{
	unsigned char s[256];
	unsigned char k[256];
	unsigned int index1,index2;
	//base64 *base;
} rc4;


class CCifrado  
{
public:
	void SetKey(const char* key);
	void Key_Dec(BYTE cant = 1)	{ for (char* cptr = m_key;*cptr != 0;*cptr = (char)(*cptr-cant),cptr++); };
	void Key_Upper() { _strupr(m_key); };
	//void SetKey(const char* key) {strncpy(m_key,key,sizeof(m_key));};
	DWORD Cifrar(char *str,char** cifrado);
	DWORD Descifrar(char* cifrado,char** descifrado);
	CCifrado()			{ SetKey("");};
	CCifrado(char* key) { SetKey(key);};
	virtual ~CCifrado();
private:
	void Decode();
	void Encode();
	void Crypt();
	void Init_B64();
	void Init_RC4();

	rc4		m_rc4;
	base64	m_b64;	// base 64 para la encryptacion
	BYTE	m_in[300];
	BYTE	m_out[300];
	int		m_in_size;		
	int		m_out_size;
	char	m_key[300];
};

#endif // !defined(AFX_CIFRADO_H__CCECEC36_D831_49BA_ACAF_7A8C35EF76D0__INCLUDED_)
