//#include "..\stdafx.h"
#include ".\rc4.h"
//#include "base64.h"
//#include "utiles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mistrdup (const char * original)
{
        char *copia=(char *)NULL;

        if (!original)
                return (char *)NULL;
// MIEDO EN LAS DOS SIGUIENTES
	//if (original[0]=='\0')
		//return "";

        if ((copia = (char *)malloc(strlen(original) + 1))== NULL)
        	return (char *)NULL;
	

	strcpy( copia, original);
        return copia;
}

rc4::rc4(const char *key): index1(0), index2(0), base64(new Base64())
{
	int i;
	size_t len;
	
	len=strlen(key);

	for (i=0;i<256;i++)
	{
		K[i]=key[i % len];
	}
}

rc4::~rc4()
{
	if (base64) delete base64;
}

rc4::rc4(const rc4 &cp): index1(cp.index1), index2(cp.index2), base64(cp.base64)
{
	int i;

	for (i=0;i<256;i++)
	{
		K[i]=cp.K[i];
	}
}

rc4 & rc4::operator=(const rc4 &cp)
{
	int i;

	index1=cp.index1;
	index2=cp.index2;
	base64=cp.base64;
	for (i=0;i<256;i++)
	{
		K[i]=cp.K[i];
	}
	return *this;
}

pETBinData32 rc4::crypt(ETBinData32 message)
{
	unsigned char t;
	unsigned char swap;
	ETBinData32 *crypted;
	unsigned int i;
	
	if (message.size==0)
		return (ETBinData32 *)NULL;
	if (message.data==NULL)
		return pETBinData32(&message);

	crypted=pETBinData32(malloc(sizeof(ETBinData32)));
	crypted->data=pBYTE(malloc(message.size+2));
	crypted->size=message.size;

	memset(crypted->data,'\0',crypted->size+1);

	for (i=0;i<256;i++)
		S[i]=char(i);

	index1=0;
	for (i=0;i<255;i++)
	{
		index1=(index1+S[i]+K[i]) % 256;
		swap=S[i]; S[i]=S[index1]; S[index1]=swap;
	}
	index1=index2=0;

	for (i=0;i<message.size;i++)
	{
		index1++; index1 %= 256;
		index2 += S[index1]; index2 %= 256;

		swap=S[index1]; S[index1]=S[index2]; S[index2]=swap;
		t=(S[index1]+S[index2]) % 256;

		(crypted->data)[i]=(message.data[i] ^ S[t]);

	}
	return crypted;
}

pchar rc4::base64_decrypt(const char *message)
{
	ETBinData32 temp,*temp_clear;
	char *message_temp;
	int size=0;

	if (message==NULL)
		return pchar(NULL);
	if (message[0]=='\0')
		return pchar(NULL);

	temp.data=pBYTE(malloc(strlen(message)+10));
	memset(temp.data,'\0',strlen(message)+10);
	base64->decode(pchar(temp.data),&size,message,strlen(message));
	temp.size=size;
	temp_clear=crypt(temp); // Symmetric algorithm
	
	if (temp_clear==NULL)
		return pchar(NULL);
	message_temp=mistrdup(pchar(temp_clear->data));

	if (temp_clear->data) free(temp_clear->data);
	if (temp_clear) free(temp_clear);
	if (temp.data) free (temp.data);
	
	return message_temp;
}
pchar rc4::base64_crypt(pchar message)
{
	ETBinData32 temp_clear,*crypted;
	pchar message_temp;

	if (message==NULL)
		return pchar(NULL);
	if (message[0]=='\0')
		return pchar(NULL);

	temp_clear.data=pBYTE(message);
	temp_clear.size=strlen(message);
	crypted=crypt(temp_clear); // Symmetric algorithm
	message_temp=pchar(malloc(strlen(message)*3+10));
	base64->encode(message_temp,pchar(crypted->data),crypted->size);
	
	if (crypted->data) free(crypted->data);
	if (crypted) free(crypted);

	return message_temp;	
}