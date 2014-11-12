#ifndef RC4_H
#define RC4_H

#include "base64.h"
#include "entrust\entapi.h"

typedef ETBinData32 * pETBinData32;
typedef BYTE* pBYTE;
typedef char* pchar;

class rc4
{
	unsigned char S[256];
	unsigned char K[256];
	unsigned int index1,index2;
	Base64 *base64;
public:
	rc4(const char *key);
	rc4(const rc4 &cp);
	rc4 & operator=(const rc4 &cp);
	~rc4();
	ETBinData32 *crypt(ETBinData32 message);
	char *base64_crypt(char *message);
	char *base64_decrypt(const char *message);
};

#endif
