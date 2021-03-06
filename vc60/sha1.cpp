// sha1.cpp: implementation of the Csha1 class.
//
//////////////////////////////////////////////////////////////////////

#include "sha1.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Csha1::Csha1()
{
	m_ver = "Class Csha1 " CLASS_VER;
	Init();
}

Csha1::~Csha1()
{
	
}

void Csha1::Proccess_Buffer(const unsigned char *pbuffer, DWORD length)
{
	if (!length)
	{
		return;
	}

	if (Computed || Corrupted)
	{
		Corrupted = true;
		return;
	}

	while(length-- && !Corrupted)
	{
		Message_Block[Message_Block_Index++] = (*pbuffer & 0xFF);

		Length_Low += 8;
		Length_Low &= 0xFFFFFFFF;				// Force it to 32 bits
		if (Length_Low == 0)
		{
			Length_High++;
			Length_High &= 0xFFFFFFFF;			// Force it to 32 bits
			if (Length_High == 0)
			{
				Corrupted = true;				// Message is too long
			}
		}

		if (Message_Block_Index == 64)
		{
			ProcessMessageBlock();
		}

		pbuffer++;
	}

}

unsigned Csha1::CircularShift(int bits, unsigned word)
{
	return ((word << bits) & 0xFFFFFFFF) | ((word & 0xFFFFFFFF) >> (32-bits));
}

void Csha1::Init()
{
	Length_Low			= 0;
	Length_High			= 0;
	Message_Block_Index	= 0;

	H[0]		= 0x67452301;
	H[1]		= 0xEFCDAB89;
	H[2]		= 0x98BADCFE;
	H[3]		= 0x10325476;
	H[4]		= 0xC3D2E1F0;

	Computed	= false;
	Corrupted	= false;

}

void Csha1::ProcessMessageBlock()
{
	const unsigned K[] = 	{ 				// Constants defined for SHA-1
								0x5A827999,
								0x6ED9EBA1,
								0x8F1BBCDC,
								0xCA62C1D6
							};
	int 		t;							// Loop counter
	unsigned 	temp;						// Temporary word value
	unsigned	W[80];						// Word sequence
	unsigned	A, B, C, D, E;				// Word buffers

	/*
	 *	Initialize the first 16 words in the array W
	 */
	for(t = 0; t < 16; t++)
	{
		W[t] = ((unsigned) Message_Block[t * 4]) << 24;
		W[t] |= ((unsigned) Message_Block[t * 4 + 1]) << 16;
		W[t] |= ((unsigned) Message_Block[t * 4 + 2]) << 8;
		W[t] |= ((unsigned) Message_Block[t * 4 + 3]);
	}

	for(t = 16; t < 80; t++)
	{
	   W[t] = CircularShift(1,W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
	}

	A = H[0];
	B = H[1];
	C = H[2];
	D = H[3];
	E = H[4];

	for(t = 0; t < 20; t++)
	{
		temp = CircularShift(5,A) + ((B & C) | ((~B) & D)) + E + W[t] + K[0];
		temp &= 0xFFFFFFFF;
		E = D;
		D = C;
		C = CircularShift(30,B);
		B = A;
		A = temp;
	}

	for(t = 20; t < 40; t++)
	{
		temp = CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[1];
		temp &= 0xFFFFFFFF;
		E = D;
		D = C;
		C = CircularShift(30,B);
		B = A;
		A = temp;
	}

	for(t = 40; t < 60; t++)
	{
		temp = CircularShift(5,A) +
		 	   ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
		temp &= 0xFFFFFFFF;
		E = D;
		D = C;
		C = CircularShift(30,B);
		B = A;
		A = temp;
	}

	for(t = 60; t < 80; t++)
	{
		temp = CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[3];
		temp &= 0xFFFFFFFF;
		E = D;
		D = C;
		C = CircularShift(30,B);
		B = A;
		A = temp;
	}

	H[0] = (H[0] + A) & 0xFFFFFFFF;
	H[1] = (H[1] + B) & 0xFFFFFFFF;
	H[2] = (H[2] + C) & 0xFFFFFFFF;
	H[3] = (H[3] + D) & 0xFFFFFFFF;
	H[4] = (H[4] + E) & 0xFFFFFFFF;

	Message_Block_Index = 0;
}

/*	
 *	PadMessage
 *
 *	Description:
 *		According to the standard, the message must be padded to an even
 *		512 bits.  The first padding bit must be a '1'.  The last 64 bits
 *		represent the length of the original message.  All bits in between
 *		should be 0.  This function will pad the message according to those
 *		rules by filling the message_block array accordingly.  It will also
 *		call ProcessMessageBlock() appropriately.  When it returns, it
 *		can be assumed that the message digest has been computed.
 *
 *	Parameters:
 *		None.
 *
 *	Returns:
 *		Nothing.
 *
 *	Comments:
 *
 */
void Csha1::PadMessage()
{
	/*
	 *	Check to see if the current message block is too small to hold
	 *	the initial padding bits and length.  If so, we will pad the
	 *	block, process it, and then continue padding into a second block.
	 */
	if (Message_Block_Index > 55)
	{
		Message_Block[Message_Block_Index++] = 0x80;
		while(Message_Block_Index < 64)
		{
			Message_Block[Message_Block_Index++] = 0;
		}

		ProcessMessageBlock();

		while(Message_Block_Index < 56)
		{
			Message_Block[Message_Block_Index++] = 0;
		}
	}
	else
	{
		Message_Block[Message_Block_Index++] = 0x80;
		while(Message_Block_Index < 56)
		{
			Message_Block[Message_Block_Index++] = 0;
		}

	}

	/*
	 *	Store the message length as the last 8 octets
	 */
	Message_Block[56] = (Length_High >> 24) & 0xFF;
	Message_Block[57] = (Length_High >> 16) & 0xFF;
	Message_Block[58] = (Length_High >> 8) & 0xFF;
	Message_Block[59] = (Length_High) & 0xFF;
	Message_Block[60] = (Length_Low >> 24) & 0xFF;
	Message_Block[61] = (Length_Low >> 16) & 0xFF;
	Message_Block[62] = (Length_Low >> 8) & 0xFF;
	Message_Block[63] = (Length_Low) & 0xFF;

	ProcessMessageBlock();
}

DWORD Csha1::GetHash(BYTE *buffer,WORD *size)
{
	char	*fnc_name = "Csha1::GetHash";

	if (Corrupted)		return LOG_TERROR ERR_FATAL,"%s Hash is corrupted ",fnc_name);
	if (size == NULL)	return LOG_TERROR ERR_FATAL,"Size can not be NULL");
	if (buffer == NULL)
	{
		*size = sizeof(H);
		return ERR_OK;
	}
	if (*size < sizeof(H)) return LOG_TERROR ERR_FATAL,"Buffer too short, %d bytes needed",sizeof(H));
	*size = sizeof(H);

	if (!Computed)
	{
		PadMessage();
		Computed = true;
	}
	memcpy(buffer,hash,sizeof(H));
	// invertir los bytes de 4 en 4
	BYTE	*pbl;	// pointer last byte
	BYTE	*pbf;	// pointer fist byte
	BYTE	*pb;
	BYTE	bsize = 4;	// block size;
	BYTE	b;

	pb = buffer;
	for (pb = buffer;(pb - buffer < *size);pb+= bsize)
	{
		pbf = pb;
		pbl = pb + bsize-1;
		while (pbf < pbl)
		{
			b = *pbf;
			*pbf = *pbl;
			*pbl = b;
			pbl--;
			pbf++;
		}
	}
	return ERR_OK;
}
