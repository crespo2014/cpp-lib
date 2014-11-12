// B64Encode.cpp: implementation of the Cb64 class.
//
//////////////////////////////////////////////////////////////////////

#include "b64.h"

#define _FILENAME_ "b64.c"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cb64::Cb64(ITube *pOutTube,bool encode)
{
	mOutTube = pOutTube;
	mbEncode = encode;
}

Cb64::~Cb64()
{

}

DWORD	Cb64::Start()
{
	mindex = 0;
	return mOutTube->Start();
}

DWORD	Cb64::End()
{
	if (mbEncode)
	{
		encode();
	}
	else
	{
		if (mindex == 4) decode();
		else
			if (mindex) return _LOG_ERROR ERR_EOF,"Unexpected end of data");
	}
	return mOutTube->End();
}

DWORD	Cb64::Push(BYTE b)
{
	mcache[mindex++] = b;
	if (mbEncode && mindex == 3) encode();
	if (!mbEncode && mindex == 4) return decode();
	return ERR_OK;

}

void Cb64::encode()
{
	const static char *tbl = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	BYTE out[4];
	// tomar la cache y convertir a 64
	/*
		si no hay datos no se hace nada
		llenar con ceros los datos que no estan presentes
	*/
	if (!mindex) return;
	if (mindex < 3) 
	{ 
		if (mindex < 2) 
		{ 
			mcache[1] = 0; 
			out[2] = '='; 
		}
		mcache[2] = 0; 
		out[3] = '='; 
	}
	out[0] = tbl[mcache[0] >> 2];
	out[1] = tbl[((mcache[0] & 0x03) << 4) | (mcache[1] >> 4)];
	if (mindex > 1)
	{
		out[2] = tbl[((mcache[1] & 0xF) << 2) | (mcache[2] >> 6)];
	}
	if (mindex > 2)
	{
		out[3] = tbl[mcache[2] & 0x3F];
	}
	mOutTube->Push(out[0]);
	mOutTube->Push(out[1]);
	mOutTube->Push(out[2]);
	mOutTube->Push(out[3]);	
	mindex = 0;
}


DWORD Cb64::decode()
{
#define NS	0xFF		// no base 64 symbol

	const static BYTE decode_tbl[] = 
	/*			0	1	2	3	4	5	6	7	8	9	0	11	12	13	14	15	16	17	18	19	*/ 

	/*   0 */ {	NS,	NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,	NS,	NS, NS, NS, NS, NS, NS, NS, NS,
	
	/*  20 */ 	NS,	NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,	NS,	NS, NS, NS, NS, NS, NS, NS, NS,
	
	/*  40 */ 	NS,	NS, NS, 63, NS, NS, NS, 64, 53, 54, 55,	56,	57, 58, 59, 60, 61, 62, NS, NS,
	
	/*  60 */ 	NS,	NS, NS, NS, NS, 1,  2 , 3 , 4 , 5,  6 ,	7 ,	8 , 9 , 10, 11, 12, 13, 14, 15,
	
	/*  80 */ 	16,	17, 18, 19, 20, 21, 22, 23, 24, 25, 26,	NS,	NS, NS, NS, NS, NS, 27, 28, 29,
	
	/* 100 */ 	30,	31, 32, 33, 34, 35, 36, 37, 38, 39, 40,	41,	42, 43, 44, 45, 46, 47, 48, 49,
	
	/* 120 */ 	50,	51, 52, NS, NS, NS, NS, NS, NS, NS, NS,	NS,	NS, NS, NS, NS, NS, NS, NS, NS,
	
	/* 140 */ 	NS,	NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,	NS,	NS, NS, NS, NS, NS, NS, NS, NS,
	
	/* 160 */ 	NS,	NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,	NS,	NS, NS, NS, NS, NS, NS, NS, NS,
	
	/* 180 */ 	NS,	NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,	NS,	NS, NS, NS, NS, NS, NS, NS, NS,
	
	/* 200 */ 	NS,	NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,	NS,	NS, NS, NS, NS, NS, NS, NS, NS, 

	/* 220 */ 	NS,	NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,	NS,	NS, NS, NS, NS, NS, NS, NS, NS, 

	/* 240 */ 	NS,	NS, NS, NS, NS, NS, NS, NS, NS, NS, NS,	NS,	NS, NS, NS, NS  };

	/*
	const static char *tbl = "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x3E\x80\x3F\x80\x80\x34\x35"
					  "\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x80\x80"
					  "\x80\xFF\x80\x80\x80\x00\x01\x02\x03\x04"
					  "\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E"
					  "\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18"
					  "\x19\x80\x80\x80\x80\x80\x80\x1A\x1B\x1C"
					  "\x1D\x1E\x1F\x20\x21\x22\x23\x24\x25\x26"
					  "\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F\x30"
					  "\x31\x32\x33\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
					  "\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80";
					  */

	BYTE	i;
	i = 4;
	if (mcache[3] == '=') { i = 3; mcache[3]=0xFF; }
	if (mcache[2] == '=') { i = 2; mcache[2]=0xFF; }

	while (i--)
	{
		mcache[i] = decode_tbl[mcache[i]];
		if (mcache[i] == NS) return _LOG_ERROR ERR_FATAL,"Invalid b64 symbol x%0x",mcache[i]);
	}
	// ya tengo los 4 indices del b64 a convertirlos en 3 bytes
	mOutTube->Push((BYTE)((mcache[0] << 2) | (mcache[1] >> 4)));
	if (mcache[2] != 0xFF)
	{
		mOutTube->Push((BYTE)((mcache[1] << 4) | (mcache[2] >> 2)));
	}
	if (mcache[3] != 0xFF)
	{
		mOutTube->Push((BYTE)((mcache[2] << 6) | mcache[3]));
	}
	mindex = 0;
	return ERR_OK;
}

