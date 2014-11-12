/*
	Encode or decode file as MIME base64 (RFC 1341)
*/

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "base64.h"

#define TRUE  1
#define FALSE 0

#define LINELEN 72		      /* Encoded line length (max 76) */

//  ENCODE  --	Encode binary data into base64.

char * encode(char *out,const char *buffer,int buflen)
{
	int i, hiteof = FALSE;
	int bufpos=0,outlen=0;
	byte dtable[256];	      // Encode / decode table

	if (buffer==NULL)
		return out;
	if (buflen<=0)
		return out;

    //	Fill dtable with character encodings. 

    for (i = 0; i < 26; i++) {
        dtable[i] = 'A' + i;
        dtable[26 + i] = 'a' + i;
    }
    for (i = 0; i < 10; i++) {
        dtable[52 + i] = '0' + i;
    }
    dtable[62] = '+';
    dtable[63] = '/';

    while (!hiteof) 
	{
		byte igroup[3], ogroup[4];
		int c, n;

		igroup[0] = igroup[1] = igroup[2] = 0;
		for (n = 0; n < 3; n++) 
		{
			if (bufpos>=buflen)
			{
				hiteof=TRUE; //c=EOF;
				break;
			}
			else
			{
				c = buffer[bufpos];	bufpos++;
			}
			igroup[n] = byte(c);
		}
	if (n > 0) {
	    ogroup[0] = dtable[igroup[0] >> 2];
	    ogroup[1] = dtable[((igroup[0] & 3) << 4) | (igroup[1] >> 4)];
	    ogroup[2] = dtable[((igroup[1] & 0xF) << 2) | (igroup[2] >> 6)];
	    ogroup[3] = dtable[igroup[2] & 0x3F];

            // Replace characters in output stream with "=" pad
	    //   characters if fewer than three characters were
	    //   read from the end of the input stream.

	    if (n < 3) {
                ogroup[3] = '=';
		if (n < 2) {
                    ogroup[2] = '=';
		}
	    }
	    for (i = 0; i < 4; i++) 
		{
			if ((outlen>0) && (outlen % 80==0))
			{
				out[outlen]=0x0D;
				out[outlen+1]=0x0A;
				outlen+=2;

			}
			out[outlen]=ogroup[i]; outlen++;
	    }
	}
    }
	out[outlen]='\0';
	return out;
}


//  DECODE  --	Decode base64.	

void decode(char *out,int *outlen,const char *buffer,int buflen)
{
	int i,j;
	int bufpos=0;
	byte dtable[256];	      // Encode / decode table

	if (buffer==NULL)
		return;
	if (buflen<=0)
		return;

    for (i = 0; i < 255; i++) {
	dtable[i] = 0x80;
    }
    for (i = 'A'; i <= 'Z'; i++) {
        dtable[i] = 0 + (i - 'A');
    }
    for (i = 'a'; i <= 'z'; i++) {
        dtable[i] = 26 + (i - 'a');
    }
    for (i = '0'; i <= '9'; i++) {
        dtable[i] = 52 + (i - '0');
    }
    dtable[int('+')] = 62;
    dtable[int('/')] = 63;
    dtable[int('=')] = 0;

    //CONSTANTCONDITION
    	for (;;) 
	{
	byte a[4], b[4], o[3];

	for (i = 0; i < 4; i++) 
	{
	    int c;

		if (bufpos>buflen)
			c=EOF;
		else
		{
			c = buffer[bufpos];	bufpos++;
		}

		if (c == EOF) 
			return;
		if (dtable[c] & 0x80) 
		{
			// Ignoring errors: discard invalid character. 
			i--;
			continue;
	    }
	    a[i] = byte(c);
	    b[i] = byte(dtable[c]);
	}
	o[0] = (b[0] << 2) | (b[1] >> 4);
	o[1] = (b[1] << 4) | (b[2] >> 2);
	o[2] = (b[2] << 6) | b[3];
        i = a[2] == '=' ? 1 : (a[3] == '=' ? 2 : 3);
	for (j=0;j<i;j++)
	{
		out[*outlen]=o[j];
		(*outlen)++;
	}

	if (i < 3)
	{
	    return;
	}
    }
}


Base64::Base64()
{
	int i;
    //	Fill etable with character encodings.  

    for (i = 0; i < 255; i++) {
	etable[i]=0;
    }
    for (i = 0; i < 26; i++) {
        etable[i] = 'A' + i;
        etable[26 + i] = 'a' + i;
    }
    for (i = 0; i < 10; i++) {
        etable[52 + i] = '0' + i;
    }
    etable[62] = '+';
    etable[63] = '/';

    for (i = 0; i < 255; i++) {
	dtable[i] = 0x80;
    }
    for (i = 'A'; i <= 'Z'; i++) {
        dtable[i] = 0 + (i - 'A');
    }
    for (i = 'a'; i <= 'z'; i++) {
        dtable[i] = 26 + (i - 'a');
    }
    for (i = '0'; i <= '9'; i++) {
        dtable[i] = 52 + (i - '0');
    }
    dtable[int('+')] = 62;
    dtable[int('/')] = 63;
    dtable[int('=')] = 0;

}

//  ENCODE  --	Encode binary data into base64.  
char * Base64::encode(char *out,const char *buffer,int buflen)
{
	int i, hiteof = FALSE;
	int bufpos=0,outlen=0;

	if (buffer==NULL)
		return out;
	if (buflen<=0)
		return out;

    while (!hiteof) 
	{
		byte igroup[3], ogroup[4];
		int c, n;

		igroup[0] = igroup[1] = igroup[2] = 0;
		for (n = 0; n < 3; n++) 
		{
			if (bufpos>=buflen)
			{
				hiteof=TRUE; //c=EOF;
				break;
			}
			else
			{
				c = buffer[bufpos];	bufpos++;
			}
			igroup[n] = byte(c);
		}
	if (n > 0) {
	    ogroup[0] = etable[igroup[0] >> 2];
	    ogroup[1] = etable[((igroup[0] & 3) << 4) | (igroup[1] >> 4)];
	    ogroup[2] = etable[((igroup[1] & 0xF) << 2) | (igroup[2] >> 6)];
	    ogroup[3] = etable[igroup[2] & 0x3F];

            // Replace characters in output stream with "=" pad
	    //   characters if fewer than three characters were
	    //   read from the end of the input stream.

	    if (n < 3) {
                ogroup[3] = '=';
		if (n < 2) {
                    ogroup[2] = '=';
		}
	    }
	    for (i = 0; i < 4; i++) 
		{
			if ((outlen>0) && (outlen % 80==0))
			{
				out[outlen]=0x0D;
				out[outlen+1]=0x0A;
				outlen+=2;

			}
			out[outlen]=ogroup[i]; outlen++;
	    }
	}
    }
	out[outlen]='\0';
	return out;
}

//  DECODE  --	Decode base64.	

void Base64::decode(char *out,int *outlen,const char *buffer,int buflen)
{
	int i,j;
	int bufpos=0;

	if (buffer==NULL)
		return;
	if (buflen<=0)
		return;

    //CONSTANTCONDITION
    	for (;;) 
	{
	byte a[4], b[4], o[3];

	for (i = 0; i < 4; i++) 
	{
	    int c;

		if (bufpos>buflen)
			c=EOF;
		else
		{
			c = buffer[bufpos];	bufpos++;
		}

		if (c == EOF) 
			return;
		if (dtable[c] & 0x80) 
		{
			// Ignoring errors: discard invalid character. 
			i--;
			continue;
	    }
	    a[i] = byte(c);
	    b[i] = byte(dtable[c]);
	}
	o[0] = (b[0] << 2) | (b[1] >> 4);
	o[1] = (b[1] << 4) | (b[2] >> 2);
	o[2] = (b[2] << 6) | b[3];
        i = a[2] == '=' ? 1 : (a[3] == '=' ? 2 : 3);
	for (j=0;j<i;j++)
	{
		out[*outlen]=o[j];
		(*outlen)++;
	}

	if (i < 3)
	{
	    return;
	}
    }
}

