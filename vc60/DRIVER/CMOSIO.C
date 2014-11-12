// CMOSIO.C - read/write routines for CMOS RAM / Real-time Clock
// Copyright (c) 1995 Vireo Software, Inc.

#include <vtoolsd.h>
#include "cmosio.h"

// Function
//	ReadCMOS - read CMOS register
//
// Input
//	reg		number of register (0 to 0x7f) to read
//
// Remarks
//	Reads a byte of the CMOS RAM. The RTC registers are in the CMOS
//	RAM.
//
// Returns
//	Returns the value of the specified register.
//
BYTE ReadCMOS(BYTE reg)
{
	BYTE r;

	_asm {
		pushfd
		cli
		mov	al, reg
		or	al, 80h
		out	70h, al
		jmp	_1
	}
_1:
	_asm	jmp	_2
_2:
	_asm {
		in	al, 71h
		mov	r, al
		jmp	_3
	}
_3:
	_asm	jmp	_4
_4:
	_asm {
		xor	al, al
		out	70h, al
		popfd
	}

	return r;	
}


// Function
//	WriteCMOS - write a CMOS RAM location
//
// Input
//	reg		CMOS register to write
//	value		Value to write to register
//
// Remarks
//	Writes a CMOS RAM location. The RTC registers are in the CMOS
//	RAM.
//
VOID WriteCMOS(BYTE reg, BYTE value)
{
	_asm {
		pushfd
		cli
		mov	al, reg
		or	al, 80h
		out	70h, al
		jmp	_1
		}
_1:
	_asm	jmp	_2
_2:
	_asm {
		mov	al, value
		out	71h, al
		jmp	_3
	}
_3:
	_asm	jmp	_4
_4:
	_asm {
		xor	al, al
		out	70h, al
		popfd
	}
}

