#ifndef HEADER_SHA_H
#define HEADER_SHA_H

#define SHA_CBLOCK	64
#define SHA_LBLOCK	16
#define SHA_BLOCK	16
#define SHA_LAST_BLOCK  56
#define SHA_LENGTH_BLOCK 8
#define SHA_DIGEST_LENGTH 20

typedef struct SHAstate_st
	{
	unsigned long h0,h1,h2,h3,h4;
	unsigned long Nl,Nh;
	unsigned long data[SHA_LBLOCK];
	int num;
	} SHA_CTX;

#ifndef NOPROTO
void SHA1_Init(SHA_CTX *c);
void SHA1_Update(SHA_CTX *c, unsigned char *data, unsigned long len);
void SHA1_Final(unsigned char *md, SHA_CTX *c);
unsigned char *SHA1(unsigned char *d, unsigned long n,unsigned char *md);
#else
void SHA1_Init();
void SHA1_Update();
void SHA1_Final();
unsigned char *SHA1();
#endif


#endif
