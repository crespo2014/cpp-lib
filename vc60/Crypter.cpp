// Crypter.cpp: implementation of the CCrypter class.
//
//////////////////////////////////////////////////////////////////////

#include "Crypter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCrypter::CCrypter(ITube	*pOutTube)
{
	mOutTube = pOutTube;
}

CCrypter::~CCrypter()
{

}

void CCrypter::SetKey(char *key)
{
	char *cptr = key;
	int i;
	for ( i=0 ; i<256 ; i++ )
	{
		m_rc4.k[i]=*(cptr++);
		if (!*cptr) cptr = key;
	}	
}

void CCrypter::KeyDec(BYTE cant)
{
	WORD i = 256;
	while (i--)
	{
		m_rc4.k[i] = (BYTE)(m_rc4.k[i] - cant);
	}
}

DWORD CCrypter::Push(BYTE b)
{
	BYTE	uc;
	/*
	*/

	m_rc4.i = (BYTE)(m_rc4.i + 1);
    m_rc4.j = (BYTE)(m_rc4.j + m_rc4.s[m_rc4.i]);

	uc = m_rc4.s[m_rc4.i];
	m_rc4.s[m_rc4.i] = m_rc4.s[m_rc4.j];
	m_rc4.s[m_rc4.j] = uc;

	return mOutTube->Push((BYTE)(m_rc4.s[(BYTE)(m_rc4.s[m_rc4.i] + m_rc4.s[m_rc4.j])] ^b));
}

/*
	Inicialización del RC4
*/
DWORD CCrypter::Start()
{
	BYTE	b;
	BYTE	*pb = m_rc4.s;
	WORD i = 256;
	WORD	j;
	
	// generar s
	for(i=0;i<256;i++)
	{
		*(pb++) = (BYTE)i;
	}
	// Mezclar s con la semilla k
	for(j=i=0;i<256;i++)
	{
		j =  (BYTE)(j + m_rc4.k[i] + m_rc4.s[i]);
		b = m_rc4.s[i];
		m_rc4.s[i] = m_rc4.s[j];
		m_rc4.s[j] = b;
	}

	m_rc4.i = m_rc4.j = 0;
	return mOutTube->Start();
}

DWORD CCrypter::End()
{
	return mOutTube->End();
}
