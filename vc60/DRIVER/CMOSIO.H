// CMOSIO.H - read/write routines for CMOS RAM / Real-time Clock
// Copyright (c) 1995 Vireo Software, Inc.

// Required CMOS port definitions 

#define STATREG_A	0xA
#define STATREG_B	0xB
#define STATREG_C	0xC

// Status Register B flags

#define ENABLE_INTERRUPT 0x40	

VOID WriteCMOS(BYTE reg, BYTE value);
BYTE ReadCMOS(BYTE reg);
