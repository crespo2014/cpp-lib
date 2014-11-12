#ifndef BASE64_H
#define BASE64_H

typedef unsigned char byte;	      /* Byte type */

//#if defined(WIN32)
//__declspec(dllexport)
//#endif
class Base64 {
	byte etable[256];	      /* Encode table */
	byte dtable[256];	      /* Decode table */
public:
	Base64();
	char * encode(char *out,const char *buffer,int buflen);
	void decode(char *out,int *outlen,const char *buffer,int buflen);
};


/*  ENCODE  --	Encode in base64 the binary data from buffer of length buflen into out  */
//#if defined(WIN32)
//__declspec(dllexport)
//#endif
char * encode(char *out,const char *buffer,int buflen);
/*  DECODE  --	Decode base64 to out starting in out[outlen] and returns
	in outlen the length */
//#if defined(WIN32)
//__declspec(dllexport)
//#endif
void decode(char *out,int *outlen,const char *buffer,int buflen);

#endif

