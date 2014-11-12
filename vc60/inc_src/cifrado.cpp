#include <stdio.h>
#include "Cifrado.h"

//char CLAVE[255]= "Coged las rosas mientras podais veloz el tiempo vuela la misma flor que hoy admirais mañana estara muerta";



//////////////////////////////////////////////////////////////////////
// CCifrado Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCifrado::~CCifrado()
{

}

void CCifrado::Init_RC4()
{
	int i;
	unsigned int len;
	len=strlen(m_key);
	for ( i=0 ; i<256 ; i++ )
	{
		m_rc4.k[i]=m_key[i%len];
	}	
}

DWORD CCifrado::Descifrar(char *cifrado, char **descifrado)
{
	if (m_key[0] == 0) return ERR_FATAL;
	Init_B64();
	Init_RC4();
	m_in_size = strlen(cifrado);
	memcpy(m_in,cifrado,m_in_size+1);	// poner el texto cifrado en m_in,m_in_size
	m_out_size = 0;
	Decode();
	memcpy(m_in,m_out,m_out_size);
	m_in_size = m_out_size;
	Crypt();
	*descifrado = (char*)m_out;
	return ERR_OK;
}

DWORD CCifrado::Cifrar(char *str, char **cifrado)
{
	if (m_key[0] == 0) return ERR_FATAL;
	Init_B64();
	Init_RC4();
	m_in_size = strlen(str);
	memcpy(m_in,str,m_in_size+1);	// poner el texto claro en m_in,m_in_size
	m_out_size = 0;
	Crypt();
	memcpy(m_in,m_out,m_out_size);
	m_in_size = m_out_size;
	Encode();
	*cifrado = (char*)m_out;
	return ERR_OK;
}

void CCifrado::Init_B64()
{
	int i;
	for ( i=0 ; i<255 ; i++ )
	{
		m_b64.etable[i]=0;
	}
	for ( i=0 ; i<26 ; i++ )
	{
		m_b64.etable[i]='A'+i;
		m_b64.etable[26+i]='a'+i;
	}
	for ( i=0 ; i<10 ; i++ )
	{
		m_b64.etable[52+i]='0'+i;
	}
	m_b64.etable[62]='+';
	m_b64.etable[63]='/';
	for ( i=0 ; i<255 ; i++ )
	{
		m_b64.dtable[i]=0x80;
	}
	for ( i='A' ; i<='Z' ; i++ )
	{
		m_b64.dtable[i]=0+(i-'A');
	}
	for ( i='a' ; i<='z' ; i++ )
	{
		m_b64.dtable[i]=26+(i-'a');
	}
	for ( i='0' ; i<='9' ; i++ )
	{
		m_b64.dtable[i]=52+(i-'0');
	}
	m_b64.dtable['+']=62;
	m_b64.dtable['/']=63;
	m_b64.dtable['=']=0;
}

void CCifrado::Crypt()
{
	unsigned char t;
	unsigned char swap;
	unsigned int i;

	if(m_in_size==0) return;
	m_out_size = m_in_size;
	memset(m_out,0,sizeof(m_out));
	for ( i=0 ; i<256;i++) m_rc4.s[i]=i;

	m_rc4.index1=0;	
	for(i=0;i<255;i++)
	{
		m_rc4.index1=(m_rc4.index1+m_rc4.s[i]+m_rc4.k[i])%256;
		swap=m_rc4.s[i];
		m_rc4.s[i]=m_rc4.s[m_rc4.index1];
		m_rc4.s[m_rc4.index1]=swap;
	}
	m_rc4.index1=m_rc4.index2=0;
	for ( i=0 ; i<m_in_size ; i++ )
	{
		m_rc4.index1++;
		m_rc4.index1%=256;
		m_rc4.index2+=m_rc4.s[m_rc4.index1];
		m_rc4.index2%=256;
		swap=m_rc4.s[m_rc4.index1];
		m_rc4.s[m_rc4.index1]=m_rc4.s[m_rc4.index2];
		m_rc4.s[m_rc4.index2]=swap;
		t=(m_rc4.s[m_rc4.index1]+m_rc4.s[m_rc4.index2])%256;
		m_out[i]=(m_in[i] ^ m_rc4.s[t]);
	}
}

void CCifrado::Encode()
{
	m_out_size = 0;
	int i,hiteof=FALSE;
	int bufpos=0,outlen=0;
	byte igroup[3],ogroup[4];
	int c,n;
	
	if (m_in_size <= 0)	return;

	while (!hiteof)
	{
		igroup[0]=igroup[1]=igroup[2]=0;
		for ( n=0 ; n<3 ; n++)
		{
			if ( bufpos>=m_in_size )
			{
				hiteof=TRUE; 
				break;
			}
			else
			{
				c=m_in[bufpos];
				bufpos++;
			}
			igroup[n]=c;
		}			
		if ( n>0 )
		{
			ogroup[0]=m_b64.etable[igroup[0] >> 2];
			ogroup[1]=m_b64.etable[((igroup[0] & 3) << 4) |
				(igroup[1] >> 4)];
			ogroup[2]=m_b64.etable[((igroup[1] & 0xF) << 2) |
				(igroup[2] >> 6)];
			ogroup[3]=m_b64.etable[igroup[2] & 0x3F];
			if ( n<3 )
			{
				ogroup[3]='=';
				if ( n<2 )
					ogroup[2]='=';
			}
			for ( i=0 ; i<4 ; i++ )
			{
				if ( (outlen>0) && (outlen % 80==0) )
				{
					m_out[outlen]=0x0D;
					m_out[outlen+1]=0x0A;
					outlen+=2;
				}
				m_out[m_out_size]=ogroup[i];
				m_out_size++;
			}
		}
	}
	m_out[m_out_size]='\0';
}

void CCifrado::Decode()
{
	int i,j;
	int bufpos=0;
	int c;
	byte a[4],b[4],o[3];
	if (m_in_size<=0 ) return;

	for ( ; ; )
	{
		for ( i=0 ; i<4 ; i++ )
		{
			if ( bufpos>m_in_size )
				c=EOF;
			else
			{
				c=m_in[bufpos];
				bufpos++;
			}
			if ( c==EOF )
			{
				return;
			}
			if ( m_b64.dtable[c] & 0x80)
			{
				i--;
				continue;
			}
			a[i]=c;
			b[i]=m_b64.dtable[c];
		}
		o[0]=(b[0] << 2) | (b[1] >> 4);
		o[1]=(b[1] << 4) | (b[2] >> 2);
		o[2]=(b[2] << 6) | b[3];
		i=a[2]=='=' ? 1 : (a[3]=='=' ? 2 : 3);
		for ( j=0 ; j<i ; j++ )
		{
			m_out[m_out_size]=o[j];
			m_out_size++;
		}
		if ( i<3 )
		{
			return;
		}
	}
}

void CCifrado::SetKey(const char *key)
{
	*m_key = 0;
	strncat(m_key,key,sizeof(m_key));
}
